/* 
 * File:   TriangulationMinimizationOrderingAlgorithm.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_CPP
#define HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TriangulationMinimizationOrderingAlgorithm.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IMutableMultiHypergraph.hpp>
#include <htd/GraphFactory.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/VertexOrdering.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/EnhancedMaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>

#include <algorithm>
#include <numeric>
#include <stack>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::TriangulationMinimizationOrderingAlgorithm.
 */
struct htd::TriangulationMinimizationOrderingAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), orderingAlgorithm_(manager->orderingAlgorithmFactory().createInstance())
    {

    }

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), orderingAlgorithm_(original.orderingAlgorithm_->clone())
    {

    }
#else
    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), orderingAlgorithm_(original.orderingAlgorithm_->cloneOrderingAlgorithm())
    {

    }
#endif

    virtual ~Implementation()
    {
        delete orderingAlgorithm_;
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The ordering algorithm which shall be used to compute the initial vertex elimination ordering.
     */
    htd::IOrderingAlgorithm * orderingAlgorithm_;

    /**
     *  Internal data structure representing a triangulated graph.
     */
    class TriangulatedGraph : public htd::IGraphStructure
    {
        public:
            /**
             *  Constructor for a triangulated graph.
             *
             *  @param[in] graph                The graph which shall be triangulated.
             *  @param[in] eliminationSequence  A vertex elimination ordering for the given graph.
             */
            TriangulatedGraph(const htd::IMultiHypergraph & graph, const std::vector<htd::vertex_t> & eliminationSequence) : names_(), internalNames_(), vertices_(graph.vertexCount()), neighborhood_(graph.vertexCount()), edgeCount_(), positions_(graph.vertexCount()), fillEdges_(graph.vertexCount())
            {
                initialize(graph);

                triangulate(eliminationSequence);

                std::iota(vertices_.begin(), vertices_.end(), 0);
            }

            /**
             *  Copy constructor for a triangulated graph.
             *
             *  @param[in] original The original triangulated graph.
             */
            TriangulatedGraph(const TriangulatedGraph & original) : names_(original.names_), internalNames_(original.internalNames_), vertices_(original.vertices_), neighborhood_(original.neighborhood_), edgeCount_(original.edgeCount_), positions_(original.positions_), fillEdges_(original.fillEdges_)
            {

            }

            /**
             *  Destructor for a triangulated graph.
             */
            virtual ~TriangulatedGraph()
            {

            }

            std::size_t vertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return neighborhood_.size();
            }

            std::size_t edgeCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return edgeCount_;
            }

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                return neighborCount(vertex);
            }

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE
            {
                return htd::ConstCollection<htd::vertex_t>::getInstance(vertices_);
            }

            void copyVerticesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE
            {
                target.insert(target.end(), vertices_.begin(), vertices_.end());
            }

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE
            {
                HTD_ASSERT(index < vertices_.size())

                return vertices_[index];
            }

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                return vertex < vertexCount();
            }

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE
            {
                std::size_t ret = 0;

                for (const std::vector<htd::vertex_t> & currentNeighborhood : neighborhood_)
                {
                    if (currentNeighborhood.empty())
                    {
                        ret++;
                    }
                }

                return ret;
            }

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE
            {
                htd::VectorAdapter<htd::vertex_t> ret;

                auto & result = ret.container();

                for (htd::vertex_t vertex : vertices_)
                {
                    if (neighborhood_[vertex].empty())
                    {
                        result.push_back(vertex);
                    }
                }

                return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
            }

            htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE
            {
                const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

                HTD_ASSERT(index < isolatedVertexCollection.size())

                htd::ConstIterator<htd::vertex_t> it = isolatedVertexCollection.begin();

                std::advance(it, index);

                return *it;
            }

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return neighborhood_[vertex].empty();
            }

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return neighborhood_[vertex].size();
            }

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return htd::ConstCollection<htd::vertex_t>::getInstance(neighborhood_[vertex]);
            }

            void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                const std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[vertex];

                target.insert(target.end(), currentNeighborhood.begin(), currentNeighborhood.end());
            }

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                const std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[vertex];

                HTD_ASSERT(index < currentNeighborhood.size())

                return currentNeighborhood[index];
            }

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

                const std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[vertex];

                return std::binary_search(currentNeighborhood.begin(), currentNeighborhood.end(), neighbor);
            }

            bool isConnected(void) const HTD_OVERRIDE
            {
                bool ret = true;

                if (!vertices_.empty())
                {
                    std::stack<htd::vertex_t> originStack;

                    std::unordered_set<htd::vertex_t> visitedVertices;

                    htd::vertex_t currentVertex = vertices_[0];

                    originStack.push(currentVertex);

                    while (!originStack.empty())
                    {
                        currentVertex = originStack.top();

                        if (visitedVertices.count(currentVertex) == 0)
                        {
                            visitedVertices.insert(currentVertex);

                            originStack.pop();

                            for (htd::vertex_t neighbor : neighborhood_[currentVertex])
                            {
                                if (visitedVertices.count(neighbor) == 0)
                                {
                                    originStack.push(neighbor);
                                }
                            }
                        }
                        else
                        {
                            originStack.pop();
                        }
                    }

                    ret = visitedVertices.size() == vertices_.size();
                }
                else
                {
                    ret = true;
                }

                return ret;
            }

            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

                bool ret = false;

                if (vertex1 == vertex2)
                {
                    ret = true;
                }
                else
                {
                    std::vector<htd::vertex_t> newVertices;
                    std::vector<htd::vertex_t> tmpVertices;

                    std::vector<bool> reachableVertices(vertices_.size());

                    reachableVertices[vertex1] = true;

                    newVertices.push_back(vertex1);

                    while (!ret && !newVertices.empty())
                    {
                        std::swap(tmpVertices, newVertices);

                        newVertices.resize(0);

                        for (auto it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
                        {
                            const std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[*it];

                            for (auto it2 = currentNeighborhood.begin(); !ret && it2 != currentNeighborhood.end(); ++it2)
                            {
                                htd::vertex_t neighbor = *it2;

                                if (!reachableVertices[neighbor])
                                {
                                    reachableVertices[neighbor] = true;

                                    newVertices.push_back(neighbor);

                                    if (neighbor == vertex2)
                                    {
                                        ret = true;
                                    }
                                }
                            }
                        }
                    }
                }

                return ret;
            }

            /**
             *  Getter for the actual identifiers of the vertices.
             *
             *  @return The actual identifiers of the vertices.
             */
            const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT
            {
                return names_;
            }

            /**
             *  Getter for the actual identifier of the given vertex.
             *
             *  @param[in] vertex   The internal name of the vertex whose position shall be returned.
             *
             *  @return The actual identifier of the given vertex.
             */
            htd::vertex_t vertexName(htd::vertex_t vertex) const
            {
                HTD_ASSERT(vertex < names_.size());

                return names_[vertex];
            }

            /**
             *  Getter for the internal identifier of the given vertex.
             *
             *  @param[in] vertex   The name of the vertex whose internal identifier shall be returned.
             *
             *  @return The internal identifier of the given vertex.
             */
            htd::vertex_t internalVertexName(htd::vertex_t vertex) const
            {
                return internalNames_.at(vertex);
            }

            /**
             *  Getter for the position of the given vertex in the underlying vertex elimination ordering.
             *
             *  @param[in] vertex   The internal name of the vertex whose position shall be returned.
             *
             *  @return The position of the given vertex in the underlying vertex elimination ordering.
             */
            htd::index_t position(htd::vertex_t vertex) const
            {
                HTD_ASSERT(vertex < names_.size());

                return positions_[vertex];
            }

            /**
             *  Updatable getter for the vector containing the preprocessed neighborhood of each of the vertices.
             *
             *  @note The neighborhood of each vertex returned by this data structure does not include the respective vertex itself.
             *
             *  @return The updatable vector containing the preprocessed neighborhood of each of the vertices.
             */
            std::vector<std::vector<htd::vertex_t>> & neighborhood(void) HTD_NOEXCEPT
            {
                return neighborhood_;
            }

            /**
             *  Getter for the vector containing the preprocessed neighborhood of each of the vertices.
             *
             *  @note The neighborhood of each vertex returned by this data structure does not include the respective vertex itself.
             *
             *  @return The vector containing the preprocessed neighborhood of each of the vertices.
             */
            const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT
            {
                return neighborhood_;
            }

            /**
             *  Updatable getter for the vector containing the preprocessed neighborhood of a vertex.
             *
             *  @note The neighborhood returned by this data structure does not include the vertex itself.
             *
             *  @param[in] vertex   The vertex whose neighborhood shall be returned.
             *
             *  @return The updatable vector containing the preprocessed neighborhood of the requested vertex.
             */
            std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex)
            {
                HTD_ASSERT(vertex < names_.size());

                return neighborhood_[vertex];
            }

            /**
             *  Getter for the vector containing the preprocessed neighborhood of a vertex.
             *
             *  @note The neighborhood returned by this data structure does not include the vertex itself.
             *
             *  @param[in] vertex   The vertex whose neighborhood shall be returned.
             *
             *  @return The vector containing the preprocessed neighborhood of the requested vertex.
             */
            const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const
            {
                HTD_ASSERT(vertex < names_.size());

                return neighborhood_[vertex];
            }

            /**
             *  Remove an edge from the graph.
             *
             *  @param[in] vertex1      The first endpoint of the edge.
             *  @param[in] vertex2      The second endpoint of the edge.
             *  @param[in] activeVertex The currently investigated vertex.
             */
            void removeFillEdge(htd::vertex_t vertex1, htd::vertex_t vertex2, htd::vertex_t activeVertex)
            {
                HTD_ASSERT(vertex1 < names_.size() && vertex2 < names_.size());

                std::vector<htd::vertex_t> & neighborhood1 = neighborhood_[vertex1];
                std::vector<htd::vertex_t> & neighborhood2 = neighborhood_[vertex2];

                auto position = std::lower_bound(neighborhood1.begin(), neighborhood1.end(), vertex2);

                if (position != neighborhood1.end() && *position == vertex2)
                {
                    neighborhood1.erase(position);
                    neighborhood2.erase(std::lower_bound(neighborhood2.begin(), neighborhood2.end(), vertex1));
                }

                std::vector<std::pair<htd::vertex_t, htd::vertex_t>> & relevantEdges = fillEdges_[activeVertex];

                auto edgePosition =
                    std::find_if(relevantEdges.begin(), relevantEdges.end(), [&](const std::pair<htd::vertex_t, htd::vertex_t> & currentFillEdge)
                    {
                       return currentFillEdge.first == vertex1 && currentFillEdge.second == vertex2;
                    });

                if (edgePosition != relevantEdges.end())
                {
                    relevantEdges.erase(edgePosition);
                }
            }

            /**
             *  Getter for the fill edges which are introduced by the elimination of the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The fill edges which are introduced by the elimination of the given vertex.
             */
            const std::vector<std::pair<htd::vertex_t, htd::vertex_t>> & fillEdges(htd::vertex_t vertex) const
            {
                HTD_ASSERT(vertex < names_.size());

                return fillEdges_[vertex];
            }

            /**
             *  Recompute the number of edges in the graph to update the result of the function edgeCount().
             */
            void updateEdgeCount(void)
            {
                edgeCount_ = 0;

                for (const std::vector<htd::vertex_t> & currentNeighborhood : neighborhood_)
                {
                    edgeCount_ += currentNeighborhood.size();
                }

                edgeCount_ = edgeCount_ >> 1;
            }

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current graph structure.
             *
             *  @return A new TriangulatedGraph object identical to the current graph structure.
             */
            TriangulatedGraph * clone(void) const
            {
                return new TriangulatedGraph(*this);
            }

            htd::IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE
            {
                return clone();
            }
#else
            TriangulatedGraph * clone(void) const HTD_OVERRIDE
            {
                return new TriangulatedGraph(*this);
            }
#endif

        private:
            /**
             *  The actual identifiers of the vertices.
             */
            std::vector<htd::vertex_t> names_;

            /**
             *  A map which maps to each vertex its internal counterpart.
             */
            std::unordered_map<htd::vertex_t, htd::vertex_t> internalNames_;

            /**
             *  The vertices of the triangulated graph.
             */
            std::vector<htd::vertex_t> vertices_;

            /**
             *  A vector containing the neighborhood of each of the vertices.
             */
            std::vector<std::vector<htd::vertex_t>> neighborhood_;

            /**
             *  The number of edges in the triangulated graph.
             */
            std::size_t edgeCount_;

            /**
             *  The positions of the vertices within the elimination ordering.
             */
            std::vector<htd::index_t> positions_;

            /**
             *  A vector containing the fill edges introduced by eliminating the vertex corresponding to the index within the vector.
             */
            std::vector<std::vector<std::pair<htd::vertex_t, htd::vertex_t>>> fillEdges_;

            /**
             *  Register a given vertex and return its index.
             *
             *  @param[in] vertex   The vertex which shall be registered.
             *
             *  @return The index of the vertex within the (updated) vector vertexNames.
             */
            htd::vertex_t registerVertex(htd::vertex_t vertex)
            {
                auto result = internalNames_.emplace(vertex, names_.size());

                if (result.second)
                {
                    names_.push_back(vertex);
                }

                return result.first->second;
            }

            /**
             *  Inititialize the data structure.
             *
             *  @param[in] graph    The input graph.
             */
            void initialize(const htd::IMultiHypergraph & graph)
            {
                std::size_t size = graph.vertexCount();

                if (size > 0)
                {
                    names_.reserve(size);

                    if (graph.vertexAtPosition(size - 1) == static_cast<htd::vertex_t>(size))
                    {
                        for (htd::index_t index = 0; index < size; ++index)
                        {
                            htd::vertex_t vertex = static_cast<htd::vertex_t>(index) + 1;

                            htd::vertex_t mappedVertex = static_cast<htd::vertex_t>(index);

                            names_.push_back(vertex);

                            internalNames_[vertex] = mappedVertex;

                            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[mappedVertex];

                            graph.copyNeighborsTo(vertex, currentNeighborhood);

                            auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

                            if (position != currentNeighborhood.end() && *position == mappedVertex)
                            {
                                currentNeighborhood.erase(position);
                            }

                            std::for_each(currentNeighborhood.begin(), currentNeighborhood.end(), [](htd::vertex_t & neighbor){ --neighbor; });
                        }
                    }
                    else
                    {
                        const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

                        auto position = vertexCollection.begin();

                        for (std::size_t remainder = vertexCollection.size(); remainder > 0; --remainder)
                        {
                            htd::vertex_t vertex = *position;

                            htd::vertex_t mappedVertex = registerVertex(vertex);

                            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[mappedVertex];

                            const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

                            auto position2 = neighborCollection.begin();

                            currentNeighborhood.reserve(neighborCollection.size() + 1);

                            for (std::size_t remainder2 = neighborCollection.size(); remainder2 > 0; --remainder2)
                            {
                                currentNeighborhood.push_back(registerVertex(*position2));

                                ++position2;
                            }

                            std::sort(currentNeighborhood.begin(), currentNeighborhood.end());

                            auto position3 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), mappedVertex);

                            if (position3 != currentNeighborhood.end() && *position3 == mappedVertex)
                            {
                                currentNeighborhood.erase(position3);
                            }

                            ++position;
                        }
                    }
                }
            }

            /**
             *  Triangulate the graph.
             *
             *  @param[in] eliminationSequence  A vertex elimination ordering for the given graph.
             */
            void triangulate(const std::vector<htd::vertex_t> & eliminationSequence)
            {
                HTD_ASSERT(eliminationSequence.size() == vertexCount())

                htd::index_t position = 0;

                for (htd::vertex_t vertex : eliminationSequence)
                {
                    positions_[internalNames_.at(vertex)] = position;

                    ++position;
                }

                for (htd::vertex_t vertex : eliminationSequence)
                {
                    htd::vertex_t internalVertex = internalNames_.at(vertex);

                    htd::index_t currentPosition = positions_[internalVertex];

                    std::vector<htd::vertex_t> relevantNeighbors;

                    for (htd::vertex_t neighbor : neighborhood_[internalVertex])
                    {
                        if (positions_[neighbor] > currentPosition)
                        {
                            relevantNeighbors.push_back(neighbor);
                        }
                    }

                    if (relevantNeighbors.size() > 1)
                    {
                        for (auto it = relevantNeighbors.begin(); it != relevantNeighbors.end(); ++it)
                        {
                            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[*it];

                            std::vector<htd::vertex_t> missingNeighbors;

                            std::set_difference(it + 1, relevantNeighbors.end(), currentNeighborhood.begin(), currentNeighborhood.end(), std::back_inserter(missingNeighbors));

                            if (!missingNeighbors.empty())
                            {
                                htd::inplace_merge(currentNeighborhood, missingNeighbors);

                                for (htd::vertex_t missingNeighbor : missingNeighbors)
                                {
                                    fillEdges_[internalVertex].emplace_back(*it, missingNeighbor);

                                    std::vector<htd::vertex_t> & currentNeighborhood2 = neighborhood_[missingNeighbor];

                                    currentNeighborhood2.insert(std::lower_bound(currentNeighborhood2.begin(), currentNeighborhood2.end(), *it), *it);
                                }
                            }
                        }
                    }
                }
            }
    };

    /**
     *  Check whether the given fill edge is a candidate for removal from the given triangulated graph.
     *
     *  @param[in] vertex1      The first endpoint of the edge.
     *  @param[in] vertex2      The second endpoint of the edge.
     *  @param[in] activeVertex The currently investigated vertex.
     *  @param[in] position     The position of the currently investigated vertex within the elimination ordering.
     *  @param[in] graph        The triangulated graph.
     *
     *  @return True if the given fill edge is a candidate for removal from the given triangulated graph, false otherwise.
     */
    bool isCandidateEdge(htd::vertex_t vertex1, htd::vertex_t vertex2, htd::vertex_t activeVertex, htd::index_t position, const TriangulatedGraph & graph) const
    {
        bool ret = true;

        for (htd::vertex_t neighbor : graph.neighborhood(vertex1))
        {
            if (graph.position(neighbor) > position && graph.isNeighbor(vertex2, neighbor) && !graph.isNeighbor(activeVertex, neighbor))
            {
                ret = false;
            }
        }

        return ret;
    }

    /**
     *  Compute the set of fill edges which can be safely removed.
     *
     *  @param[in] graph                    The input graph.
     *  @param[in] candidateFillEdges       The fill edges which shall be checked.
     *  @param[in] vertices                 The actual identifier (as used for the candidate fill edges) of the vertices of the input graph.
     *  @param[in,out] redundantFillEdges   The vector of redundant fill edges which shall be updated.
     */
    void computeRedundantFillEdges(const htd::IGraph & graph, const std::vector<std::pair<htd::vertex_t, htd::vertex_t>> & candidateFillEdges, const std::vector<htd::vertex_t> & vertices, std::vector<std::pair<htd::vertex_t, htd::vertex_t>> & redundantFillEdges) const
    {
        htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm algorithm(managementInstance_);

        htd::IVertexOrdering * ordering = algorithm.computeOrdering(graph);

        TriangulatedGraph triangulatedGraph(graph, ordering->sequence());

        delete ordering;

        std::vector<std::pair<htd::vertex_t, htd::vertex_t>> fillEdges;

        for (htd::vertex_t vertex : triangulatedGraph.vertices())
        {
            for (const std::pair<htd::vertex_t, htd::vertex_t> & fillEdge : triangulatedGraph.fillEdges(vertex))
            {
                fillEdges.push_back(std::make_pair(vertices[fillEdge.first], vertices[fillEdge.second]));
            }
        }

        std::sort(fillEdges.begin(), fillEdges.end());

        for (const std::pair<htd::vertex_t, htd::vertex_t> & fillEdge : candidateFillEdges)
        {
            if (!std::binary_search(fillEdges.begin(), fillEdges.end(), fillEdge))
            {
                redundantFillEdges.push_back(fillEdge);
            }
        }
    }
};

htd::TriangulationMinimizationOrderingAlgorithm::TriangulationMinimizationOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}

htd::TriangulationMinimizationOrderingAlgorithm::TriangulationMinimizationOrderingAlgorithm(const htd::TriangulationMinimizationOrderingAlgorithm & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::TriangulationMinimizationOrderingAlgorithm::~TriangulationMinimizationOrderingAlgorithm()
{
    
}

htd::IVertexOrdering * htd::TriangulationMinimizationOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::IVertexOrdering * ret = computeOrdering(graph, *preprocessedGraph);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::IVertexOrdering * htd::TriangulationMinimizationOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    htd::IVertexOrdering * ordering = implementation_->orderingAlgorithm_->computeOrdering(graph, preprocessedGraph);

    htd::TriangulationMinimizationOrderingAlgorithm::Implementation::TriangulatedGraph triangulatedGraph(graph, ordering->sequence());

    htd::index_t position = ordering->sequence().size() - 1;

    bool fillEdgeRemoved = false;

    for (auto it = ordering->sequence().rbegin(); it != ordering->sequence().rend(); ++it)
    {
        htd::vertex_t vertex = triangulatedGraph.internalVertexName(*it);

        const std::vector<std::pair<htd::vertex_t, htd::vertex_t>> & fillEdges = triangulatedGraph.fillEdges(vertex);

        std::unordered_set<htd::vertex_t> candidateVertices;

        std::vector<std::pair<htd::vertex_t, htd::vertex_t>> candidateEdges;

        for (const std::pair<htd::vertex_t, htd::vertex_t> & fillEdge : fillEdges)
        {
            if (implementation_->isCandidateEdge(fillEdge.first, fillEdge.second, vertex, position, triangulatedGraph))
            {
                candidateEdges.push_back(fillEdge);

                candidateVertices.insert(fillEdge.first);
                candidateVertices.insert(fillEdge.second);
            }
        }

        if (!candidateEdges.empty())
        {
            std::vector<htd::vertex_t> relevantVertices(candidateVertices.begin(), candidateVertices.end());

            std::sort(relevantVertices.begin(), relevantVertices.end());

            htd::IMutableGraph * localGraph = implementation_->managementInstance_->graphFactory().createInstance(relevantVertices.size());

            std::unordered_map<htd::vertex_t, htd::vertex_t> localMapping;

            htd::index_t localPosition = 1;

            for (htd::vertex_t relevantVertex : relevantVertices)
            {
                localMapping.emplace(relevantVertex, localPosition);

                ++localPosition;
            }

            for (auto it2 = relevantVertices.begin(); it2 != relevantVertices.end(); ++it2)
            {
                for (auto it3 = it2 + 1; it3 != relevantVertices.end(); ++it3)
                {
                    localGraph->addEdge(localMapping.at(*it2), localMapping.at(*it3));
                }
            }

            for (const std::pair<htd::vertex_t, htd::vertex_t> & candidate : candidateEdges)
            {
                localGraph->removeEdge(localMapping.at(candidate.first), localMapping.at(candidate.second));
            }

            std::vector<std::pair<htd::vertex_t, htd::vertex_t>> redundantFillEdges;

            implementation_->computeRedundantFillEdges(*localGraph, candidateEdges, relevantVertices, redundantFillEdges);

            for (const std::pair<htd::vertex_t, htd::vertex_t> & candidate : redundantFillEdges)
            {
                triangulatedGraph.removeFillEdge(candidate.first, candidate.second, vertex);

                fillEdgeRemoved = true;
            }

            delete localGraph;
        }

        --position;
    }

    htd::IVertexOrdering * ret = nullptr;

    if (fillEdgeRemoved)
    {
        delete ordering;

        htd::IMutableMultiHypergraph * optimizedGraph = implementation_->managementInstance_->multiHypergraphFactory().createInstance(graph);

        for (htd::vertex_t vertex : triangulatedGraph.vertices())
        {
            for (const std::pair<htd::vertex_t, htd::vertex_t> & fillEdge : triangulatedGraph.fillEdges(vertex))
            {
                htd::vertex_t vertex1 = triangulatedGraph.vertexName(fillEdge.first);
                htd::vertex_t vertex2 = triangulatedGraph.vertexName(fillEdge.second);

                optimizedGraph->addEdge(vertex1, vertex2);
            }
        }

        htd::MinFillOrderingAlgorithm finalOrderingAlgorithm(implementation_->managementInstance_);

        ret = finalOrderingAlgorithm.computeOrdering(*optimizedGraph);

        delete optimizedGraph;
    }
    else
    {
        ret = ordering;
    }

    return ret;
}

const htd::LibraryInstance * htd::TriangulationMinimizationOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::TriangulationMinimizationOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

void htd::TriangulationMinimizationOrderingAlgorithm::setOrderingAlgorithm(htd::IOrderingAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    delete implementation_->orderingAlgorithm_;

    implementation_->orderingAlgorithm_ = algorithm;
}

htd::TriangulationMinimizationOrderingAlgorithm * htd::TriangulationMinimizationOrderingAlgorithm::clone(void) const
{
    return new htd::TriangulationMinimizationOrderingAlgorithm(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::TriangulationMinimizationOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::TriangulationMinimizationOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_TRIANGULATIONMINIMIZATIONORDERINGALGORITHM_CPP */
