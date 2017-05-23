/*
 * File:   CliqueMinimalSeparatorAlgorithm.cpp
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

#ifndef HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_CPP
#define HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_CPP

#include <htd/Helpers.hpp>
#include <htd/CliqueMinimalSeparatorAlgorithm.hpp>

#include <htd/MultiGraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <numeric>
#include <stack>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::CliqueMinimalSeparatorAlgorithm.
 */
struct htd::CliqueMinimalSeparatorAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  Internal data structure representing a triangulated graph.
     */
    class TriangulatedGraph : public htd::IGraphStructure
    {
        public:
            /**
             *  Constructor for a triangulated graph.
             *
             *  @param[in] graph    The graph which shall be triangulated.
             */
            TriangulatedGraph(const htd::IGraphStructure & graph) : names_(), internalNames_(), vertices_(graph.vertexCount()), neighborhood_(graph.vertexCount()), edgeCount_()
            {
                initialize(graph);

                std::iota(vertices_.begin(), vertices_.end(), 0);
            }

            /**
             *  Copy constructor for a triangulated graph.
             *
             *  @param[in] original The original triangulated graph.
             */
            TriangulatedGraph(const TriangulatedGraph & original) : names_(original.names_), internalNames_(original.internalNames_), vertices_(original.vertices_), neighborhood_(original.neighborhood_), edgeCount_(original.edgeCount_)
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
             *  Remove a vertex from the graph.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            void removeVertex(htd::vertex_t vertex)
            {
                HTD_ASSERT(vertex < names_.size());

                std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood_[vertex];

                edgeCount_ -= selectedNeighborhood.size();

                for (htd::vertex_t neighbor : selectedNeighborhood)
                {
                    std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[neighbor];

                    /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'currentNeighborhood'. */
                    // coverity[use_iterator]
                    currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex));
                }

                std::vector<htd::vertex_t>().swap(selectedNeighborhood);
            }

            /**
             *  Add a new edge to the graph.
             *
             *  @param[in] vertex1  The first endpoint of the edge.
             *  @param[in] vertex2  The second endpoint of the edge.
             */
            void addTriangulationEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
            {
                HTD_ASSERT(vertex1 != vertex2)
                HTD_ASSERT(vertex1 < names_.size() && vertex2 < names_.size());

                std::vector<htd::vertex_t> & neighborhood1 = neighborhood_[vertex1];

                auto position = std::lower_bound(neighborhood1.begin(), neighborhood1.end(), vertex2);

                if (position == neighborhood1.end() || *position != vertex2)
                {
                    neighborhood1.insert(position, vertex2);

                    std::vector<htd::vertex_t> & neighborhood2 = neighborhood_[vertex2];

                    neighborhood2.insert(std::lower_bound(neighborhood2.begin(), neighborhood2.end(), vertex1), vertex1);
                }

                ++edgeCount_;
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
            void initialize(const htd::IGraphStructure & graph)
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
                    else if (graph.vertexAtPosition(size - 1) == static_cast<htd::vertex_t>(size - 1))
                    {
                        for (htd::index_t index = 0; index < size; ++index)
                        {
                            htd::vertex_t vertex = static_cast<htd::vertex_t>(index);

                            names_.push_back(vertex);

                            internalNames_[vertex] = vertex;

                            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_[vertex];

                            graph.copyNeighborsTo(vertex, currentNeighborhood);

                            auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

                            if (position != currentNeighborhood.end() && *position == vertex)
                            {
                                currentNeighborhood.erase(position);
                            }
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

                updateEdgeCount();
            }
    };

    /**
     *  Fill the pool of vertices having maximum weight.
     *
     *  @param[in] vertices The set of vertices which shall be considered.
     *  @param[in] weights  A vector containing the weights associated with each of the vertices.
     *  @param[out] pool    The vertex pool which shall be filled with all vertices of maximum weight.
     */
    void fillMaxCardinalityPool(const std::unordered_set<htd::vertex_t> & vertices, const std::vector<std::size_t> & weights, std::vector<htd::vertex_t> & pool) const HTD_NOEXCEPT
    {
        std::size_t max = 0;

        pool.clear();

        for (htd::vertex_t vertex : vertices)
        {
            std::size_t tmp = weights[vertex];

            if (tmp >= max)
            {
                if (tmp > max)
                {
                    max = tmp;

                    pool.clear();
                }

                pool.push_back(vertex);
            }
        }
    }

    /**
     *  Check whether the given set of vertices forms a clique.
     *
     *  @param[in] graph    The graph.
     *  @param[in] vertices The set of vertices.
     *
     *  @return True if the given set of vertices forms a clique, false otherwise.
     */
    bool isComplete(const TriangulatedGraph & graph, const std::vector<htd::vertex_t> & vertices) const
    {
        bool ret = true;

        for (auto it = vertices.begin(); ret && it != vertices.end(); ++it)
        {
            const std::vector<htd::vertex_t> & currentNeighborhood = graph.neighborhood(*it);

            ret = htd::set_intersection_size(currentNeighborhood.begin(), currentNeighborhood.end(), vertices.begin(), vertices.end()) >= vertices.size() - 1;
        }

        return ret;
    }

    /**
     *  Determine the connected component of the graph separated by the provided separator which contains the given vertex.
     *
     *  @param[in] graph        The graph.
     *  @param[in] separator    A set of vertices separating the given graph.
     *  @param[in] vertex       The vertex.
     *
     *  @return The connected component of the graph separated by the provided separator which contains the given vertex.
     */
    std::vector<htd::vertex_t> * determineComponent(const TriangulatedGraph & graph, const std::vector<htd::vertex_t> & separator, htd::vertex_t vertex)
    {
        HTD_ASSERT(graph.isVertex(vertex))

        std::vector<htd::vertex_t> * ret =
            new std::vector<htd::vertex_t>();

        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices(separator.begin(), separator.end());

        htd::vertex_t currentVertex = vertex;

        originStack.push(currentVertex);

        while (!originStack.empty() && !managementInstance_->isTerminated())
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                ret->push_back(currentVertex);

                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : graph.neighborhood(currentVertex))
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

        std::sort(ret->begin(), ret->end());

        return ret;
    }
};

htd::CliqueMinimalSeparatorAlgorithm::CliqueMinimalSeparatorAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::CliqueMinimalSeparatorAlgorithm::~CliqueMinimalSeparatorAlgorithm(void)
{

}

std::vector<htd::vertex_t> * htd::CliqueMinimalSeparatorAlgorithm::computeSeparator(const htd::IGraphStructure & graph) const
{
    std::size_t size = graph.vertexCount();

    std::vector<htd::vertex_t> * ret = new std::vector<htd::vertex_t>();

    if (size > 0)
    {
        htd::CliqueMinimalSeparatorAlgorithm::Implementation::TriangulatedGraph referenceGraph(graph);

        htd::CliqueMinimalSeparatorAlgorithm::Implementation::TriangulatedGraph eliminationGraph(referenceGraph);

        htd::CliqueMinimalSeparatorAlgorithm::Implementation::TriangulatedGraph triangulatedGraph(referenceGraph);

        std::unordered_set<htd::vertex_t> vertices(size);

        htd::fillSet(eliminationGraph.vertices(), vertices);

        std::vector<htd::vertex_t> pool;

        std::vector<std::size_t> labels(graph.vertexCount());

        std::unordered_set<htd::vertex_t> reached;

        std::unordered_map<std::size_t, std::vector<htd::vertex_t>> reachable;

        std::vector<htd::vertex_t> generators;

        const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

        std::vector<htd::vertex_t> ordering;
        ordering.reserve(graph.vertexCount());

        std::size_t lastLabel = (std::size_t)-1;

        for (htd::index_t index = 0; index < size; ++index)
        {
            labels[index] = 0;
        }

        while (size > 0 && !managementInstance.isTerminated())
        {
            implementation_->fillMaxCardinalityPool(vertices, labels, pool);

            htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

            const std::vector<htd::vertex_t> & selectedNeighborhood = eliminationGraph.neighborhood(selectedVertex);

            if (lastLabel != (std::size_t)-1 && labels[selectedVertex] <= lastLabel)
            {
                htd::insertSorted(generators, selectedVertex);
            }

            lastLabel = labels[selectedVertex];

            std::vector<htd::vertex_t> triangulationNeighbors(eliminationGraph.neighborhood(selectedVertex));

            ordering.push_back(selectedVertex);

            vertices.erase(selectedVertex);

            pool.clear();

            --size;

            reached.insert(selectedVertex);

            for (htd::index_t index = 0; index <= size; ++index)
            {
                reachable[index].clear();
            }

            for (htd::vertex_t neighbor : selectedNeighborhood)
            {
                reached.insert(neighbor);

                reachable[labels[neighbor]].push_back(neighbor);
            }

            for (htd::index_t index = 0; index <= size; ++index)
            {
                std::vector<htd::vertex_t> & currentlyReachableVertices = reachable[index];

                while (!currentlyReachableVertices.empty())
                {
                    htd::vertex_t reachableVertex = htd::selectRandomElement<htd::vertex_t>(currentlyReachableVertices);

                    currentlyReachableVertices.erase(std::lower_bound(currentlyReachableVertices.begin(),
                                                                      currentlyReachableVertices.end(),
                                                                      reachableVertex));

                    for (htd::vertex_t neighbor : eliminationGraph.neighborhood(reachableVertex))
                    {
                        if (reached.count(neighbor) == 0)
                        {
                            reached.insert(neighbor);

                            if (labels[neighbor] > index)
                            {
                                triangulationNeighbors.push_back(neighbor);

                                htd::insertSorted(reachable[labels[neighbor]], neighbor);
                            }
                            else
                            {
                                htd::insertSorted(currentlyReachableVertices, neighbor);
                            }
                        }
                    }
                }
            }

            for (htd::vertex_t neighbor : triangulationNeighbors)
            {
                triangulatedGraph.addTriangulationEdge(selectedVertex, neighbor);

                labels[neighbor]++;
            }

            eliminationGraph.removeVertex(selectedVertex);

            reached.clear();
        }

        std::reverse(ordering.begin(), ordering.end());

        htd::CliqueMinimalSeparatorAlgorithm::Implementation::TriangulatedGraph referenceGraph2(referenceGraph);

        std::vector<std::vector<htd::vertex_t>> cliqueSeparators;

        for (htd::vertex_t vertex : ordering)
        {
            if (std::binary_search(generators.begin(), generators.end(), vertex))
            {
                const std::vector<htd::vertex_t> & currentNeighborhood = triangulatedGraph.neighborhood(vertex);

                if (!currentNeighborhood.empty())
                {
                    if (implementation_->isComplete(referenceGraph, currentNeighborhood))
                    {
                        std::vector<htd::vertex_t> * component = implementation_->determineComponent(referenceGraph2, currentNeighborhood, vertex);

                        for (htd::vertex_t componentVertex : *component)
                        {
                            referenceGraph2.removeVertex(componentVertex);
                        }

                        cliqueSeparators.push_back(currentNeighborhood);

                        delete component;
                    }
                }
            }

            triangulatedGraph.removeVertex(vertex);
        }

        std::sort(cliqueSeparators.begin(), cliqueSeparators.end());

        cliqueSeparators.erase(std::unique(cliqueSeparators.begin(), cliqueSeparators.end()), cliqueSeparators.end());

        if (!cliqueSeparators.empty())
        {
            const std::vector<htd::vertex_t> & separator = htd::selectRandomElement<std::vector<htd::vertex_t>>(cliqueSeparators);

            for (htd::vertex_t vertex : separator)
            {
                ret->push_back(referenceGraph.vertexName(vertex));
            }
        }
    }

    return ret;
}

const htd::LibraryInstance * htd::CliqueMinimalSeparatorAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::CliqueMinimalSeparatorAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::CliqueMinimalSeparatorAlgorithm * htd::CliqueMinimalSeparatorAlgorithm::clone(void) const
{
    return new htd::CliqueMinimalSeparatorAlgorithm(managementInstance());
}

#endif /* HTD_HTD_CLIQUEMINIMALSEPARATORALGORITHM_CPP */
