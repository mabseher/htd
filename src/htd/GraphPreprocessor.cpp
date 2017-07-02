/*
 * File:   GraphPreprocessor.cpp
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

#ifndef HTD_HTD_GRAPHPREPROCESSOR_CPP
#define HTD_HTD_GRAPHPREPROCESSOR_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/GraphPreprocessor.hpp>

#include <htd/PreprocessedGraph.hpp>
#include <htd/BiconnectedComponentAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/CliqueMinimalSeparatorAlgorithm.hpp>

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    /**
     *  This class is designed to hold the information of a connected component of a preprocessed graph.
     */
    class PreprocessedGraphComponent : public htd::IPreprocessedGraph
    {
        public:
            /**
             *  Constructor for a new, preprocessed graph component data structure.
             *
             *  @param[in] preprocessedGraph    The base graph containing the component represented by the new graph component data structure.
             *  @param[in] remainingVertices    The set of vertices which were not eliminated during the preprocessing phase.
             *  @param[in] minTreeWidth         The lower bound for the treewidth of the preprocessed graph component.
             */
            PreprocessedGraphComponent(const htd::IPreprocessedGraph & preprocessedGraph,
                                       std::vector<htd::vertex_t> && remainingVertices,
                                       std::size_t minTreeWidth) : baseGraph_(preprocessedGraph), remainingVertices_(std::move(remainingVertices)), eliminationSequence_(), minTreeWidth_(minTreeWidth), edgeCount_(0)
            {
                updateEdgeCount();
            }

            /**
             *  Copy constructor for a preprocessed graph component data structure.
             *
             *  @param[in] original  The original preprocessed graph component data structure.
             */
            PreprocessedGraphComponent(const htd::PreprocessedGraphComponent & original) : baseGraph_(original.baseGraph_), remainingVertices_(original.remainingVertices_), eliminationSequence_(original.eliminationSequence_), minTreeWidth_(original.minTreeWidth_), edgeCount_(original.edgeCount_)
            {

            }

            /**
             *  Destructor for a preprocessed graph component data structure.
             */
            virtual ~PreprocessedGraphComponent()
            {

            }

            std::size_t vertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return remainingVertices_.size();
            }

            std::size_t inputGraphVertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseGraph_.inputGraphVertexCount();
            }

            std::size_t edgeCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return edgeCount_;
            }

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                return neighborCount(vertex);
            }

            std::size_t inputGraphEdgeCount(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseGraph_.inputGraphEdgeCount();
            }

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE
            {
                return htd::ConstCollection<htd::vertex_t>::getInstance(remainingVertices_);
            }

            void copyVerticesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE
            {
                target.insert(target.end(), remainingVertices_.begin(), remainingVertices_.end());
            }

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE
            {
                HTD_ASSERT(index < remainingVertices_.size())

                return remainingVertices_[index];
            }

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                return std::binary_search(remainingVertices_.begin(),
                                          remainingVertices_.end(),
                                          vertex);
            }

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE
            {
                std::size_t ret = 0;

                for (htd::vertex_t vertex : remainingVertices_)
                {
                    if (baseGraph_.neighborhood(vertex).empty())
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

                for (htd::vertex_t vertex : remainingVertices_)
                {
                    if (baseGraph_.neighborhood(vertex).empty())
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

                return baseGraph_.isIsolatedVertex(vertex);
            }

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return baseGraph_.neighborCount(vertex);
            }

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return baseGraph_.neighbors(vertex);
            }

            void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                baseGraph_.copyNeighborsTo(vertex, target);
            }

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return baseGraph_.neighborAtPosition(vertex, index);
            }

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

                return baseGraph_.isNeighbor(vertex, neighbor);
            }

            bool isConnected(void) const HTD_OVERRIDE
            {
                return true;
            }

            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE
            {
                HTD_UNUSED(vertex1)
                HTD_UNUSED(vertex2)

                HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

                return true;
            }

            const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseGraph_.vertexNames();
            }

            htd::vertex_t vertexName(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return baseGraph_.vertexName(vertex);
            }

            const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseGraph_.neighborhood();
            }

            const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const HTD_OVERRIDE
            {
                HTD_ASSERT(isVertex(vertex))

                return baseGraph_.neighborhood(vertex);
            }

            const std::vector<htd::vertex_t> & eliminationSequence(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return eliminationSequence_;
            }

            const std::vector<htd::vertex_t> & remainingVertices(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return remainingVertices_;
            }

            std::size_t minTreeWidth(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return minTreeWidth_;
            }

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            PreprocessedGraphComponent * clone(void) const HTD_OVERRIDE
            {
                return new htd::PreprocessedGraphComponent(*this);
            }
    #else
            /**
             *  Create a deep copy of the current preprocessed graph component.
             *
             *  @return A new PreprocessedGraphComponent object identical to the current preprocessed graph component.
             */
            PreprocessedGraphComponent * clone(void) const
            {
                return new htd::PreprocessedGraphComponent(*this);
            }

            htd::IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE
            {
                return clone();
            }
    #endif

        private:
            /**
             *  The base graph containing the component represented by this graph component data structure.
             */
            const htd::IPreprocessedGraph & baseGraph_;

            /**
             *  The set of vertices which were not eliminated during the preprocessing phase.
             */
            std::vector<htd::vertex_t> remainingVertices_;

            /**
             *  A partial vertex elimination ordering computed during the preprocessing phase.
             */
            std::vector<htd::vertex_t> eliminationSequence_;

            /**
             *  The lower bound of the treewidth of the input graph.
             */
            std::size_t minTreeWidth_;

            /**
             *  The number of edges in the preprocessed graph.
             */
            std::size_t edgeCount_;

            /**
             *  Recompute the number of edges in the graph to update the result of the function edgeCount().
             */
            void updateEdgeCount(void)
            {
                edgeCount_ = 0;

                for (htd::vertex_t vertex : remainingVertices_)
                {
                    edgeCount_ += baseGraph_.neighborhood(vertex).size();
                }

                edgeCount_ = edgeCount_ >> 1;
            }
    };
}

/**
 *  Private implementation details of class htd::GraphPreprocessor.
 */
struct htd::GraphPreprocessor::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager),
                                                                 applyPreprocessing1_(false),
                                                                 applyPreprocessing2_(false),
                                                                 applyPreprocessing3_(false),
                                                                 applyPreprocessing4_(false),
                                                                 iterationCount_(1),
                                                                 nonImprovementLimit_(0),
                                                                 orderingAlgorithm_(new htd::MinFillOrderingAlgorithm(manager))
    {

    }

    virtual ~Implementation()
    {
        delete orderingAlgorithm_;
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  A boolean flag indicating whether all vertices
     *  of degree less than 2 should be removed from
     *  an input graph.
     */
    bool applyPreprocessing1_;

    /**
     *  A boolean flag indicating whether all paths
     *  in an input graph should be contracted.
     */
    bool applyPreprocessing2_;

    /**
     *  A boolean flag indicating whether all vertices
     *  of degree 3 should be eliminated from a given
     *  input graph in case that at least two of its
     *  neighbors are adjacent.
     */
    bool applyPreprocessing3_;

    /**
     *  A boolean flag indicating whether all vertices,
     *  for which it holds that all its neighbors form
     *  a clique, should be removed from a given input
     *  graph.
     */
    bool applyPreprocessing4_;

    /**
     *  The number of iterations of the base ordering algorithm which shall be performed for each component.
     */
    std::size_t iterationCount_;

    /**
     *  The maximum number of iterations of the base ordering algorithm without improvement after which the algorithm shall terminate.
     */
    std::size_t nonImprovementLimit_;

    /**
     *  The base ordering algorithm which shall be used to eliminate all but the largest biconnected component.
     */
    htd::IWidthLimitableOrderingAlgorithm * orderingAlgorithm_;

    /**
     *  Structure representing the preprocessed input for the algorithm.
     *
     *  The preprocessing step consists of replacing the vertex identifiers by indices starting
     *  at 0 so that vectors instead of maps can be used for efficiently accessing information.
     */
    struct PreparedInput
    {
        /**
         *  Register a given vertex and return its index.
         *
         *  @param[in] vertex           The vertex which shall be registered.
         *  @param[in,out] mapping      A map which maps to each vertex its corresponding index. This information is updated when the given vertex is registered for the first time.
         *  @param[in,out] vertexNames  A vector which holds the vertex identifier corresponding to an index. This information is updated when the given vertex is registered for the first time.
         *
         *  @return The index of the vertex within the (updated) vector vertexNames.
         */
        htd::vertex_t registerVertex(htd::vertex_t vertex, std::unordered_map<htd::vertex_t, htd::vertex_t> & mapping, std::vector<htd::vertex_t> & vertexNames)
        {
            auto result = mapping.emplace(vertex, vertexNames.size());

            if (result.second)
            {
                vertexNames.push_back(vertex);
            }

            return result.first->second;
        }

        /**
         *  Inititialize the data structure.
         *
         *  @param[in] graph            The input graph.
         *  @param[in,out] vertexNames  A vector which holds the vertex identifier corresponding to an index. This information is initialized by the function.
         *  @param[in,out] neighborhood The neighborhood relation of the input graph where the vertex identifiers are replaced by their zero-based indices. This information is initialized by the function.
         */
        void initialize(const htd::IGraphStructure & graph,
                        std::vector<htd::vertex_t> & vertexNames,
                        std::vector<std::vector<htd::vertex_t>> & neighborhood)
        {
            std::size_t size = graph.vertexCount();

            if (size > 0)
            {
                if (graph.vertexAtPosition(size - 1) == static_cast<htd::vertex_t>(size))
                {
                    for (htd::index_t index = 0; index < size; ++index)
                    {
                        htd::vertex_t vertex = static_cast<htd::vertex_t>(index) + 1;

                        htd::vertex_t mappedVertex = static_cast<htd::vertex_t>(index);

                        vertexNames.push_back(vertex);

                        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[mappedVertex];

                        graph.copyNeighborsTo(vertex, currentNeighborhood);

                        auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

                        if (position != currentNeighborhood.end() && *position == vertex)
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

                        vertexNames.push_back(vertex);

                        graph.copyNeighborsTo(vertex, neighborhood[vertex]);
                    }
                }
                else
                {
                    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

                    auto position = vertexCollection.begin();

                    std::unordered_map<htd::vertex_t, htd::vertex_t> mapping(vertexCollection.size());

                    for (std::size_t remainder = vertexCollection.size(); remainder > 0; --remainder)
                    {
                        htd::vertex_t vertex = *position;

                        htd::vertex_t mappedVertex = registerVertex(vertex, mapping, vertexNames);

                        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[mappedVertex];

                        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

                        auto position2 = neighborCollection.begin();

                        currentNeighborhood.reserve(neighborCollection.size() + 1);

                        for (std::size_t remainder2 = neighborCollection.size(); remainder2 > 0; --remainder2)
                        {
                            currentNeighborhood.push_back(registerVertex(*position2, mapping, vertexNames));

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
         *  Contructor for the PreparedInput data structure.
         *
         *  @param[in] managementInstance   The management instance to which the new algorithm belongs.
         *  @param[in] graph                The input graph which shall be preprocessed.
         */
        PreparedInput(const htd::LibraryInstance & managementInstance, const htd::IGraphStructure & graph) : vertexNames(), neighborhood()
        {
            HTD_UNUSED(managementInstance)

            std::size_t size = graph.vertexCount();

            vertexNames.reserve(size);

            neighborhood.resize(size);

            initialize(graph, vertexNames, neighborhood);
        }

        ~PreparedInput()
        {

        }

        /**
         *  The actual identifiers of the vertices.
         */
        std::vector<htd::vertex_t> vertexNames;

        /**
         *  A vector containing the neighborhood of each of the vertices.
         */
        std::vector<std::vector<htd::vertex_t>> neighborhood;
    };

    /**
     *  Eliminate all vertices of degree less than 2 from the graph.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool eliminateVerticesOfDegreeLessThanTwo(std::unordered_set<htd::vertex_t> & vertices,
                                                     std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                     std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                     std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices of degree 2 from the graph.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool contractPaths(std::unordered_set<htd::vertex_t> & vertices,
                              std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                              std::vector<std::vector<htd::vertex_t>> & neighborhood,
                              std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices of degree 3 from the graph in
     *  case that at least two of its neighbors are adjacent.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool shrinkTriangles(std::unordered_set<htd::vertex_t> & vertices,
                                std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                std::vector<htd::vertex_t> & ordering);

    /**
     *  If two vertices of degree 3 have exactly the same neighbors,
     *  eliminate both of them and connect the three neighbors so
     *  that they form a triangle.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool handleBuddies(std::unordered_set<htd::vertex_t> & vertices,
                              std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                              std::vector<std::vector<htd::vertex_t>> & neighborhood,
                              std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices from the graph for which
     *  it holds that all its neighbors form a clique.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *  @param[in] maxDegree        The degree up to which a vertex shall be considered for this preprocessing.
     *  @param[in,out] minTreeWidth The lower bound for the treewidth of the given graph.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool eliminateSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                            std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                            std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                            std::vector<htd::vertex_t> & ordering,
                                            std::size_t maxDegree,
                                            std::size_t & minTreeWidth);

    /**
     *  Eliminate all vertices from the graph for which it
     *  holds that at least all but one of its neighbors
     *  form a clique.
     *
     *  @param[in] vertices         The set of all available vertices.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] neighborhood     The neighborhood relation of the remaining graph.
     *  @param[in] ordering         The resulting, partial vertex elimination ordering.
     *  @param[in,out] minTreeWidth The lower bound for the treewidth of the given graph.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    static bool eliminateAlmostSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                                  std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                  std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                  std::vector<htd::vertex_t> & ordering,
                                                  std::size_t & minTreeWidth);

    /**
     *  Update the group to which the given vertex belongs.
     *
     *  @param[in] vertex           The vertex which shall be assigned to a group.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] newDegree        The new degree of the vertex.
     *  @param[in] oldDegree        The old degree of the vertex.
     */
    static void assignVertexToGroup(htd::vertex_t vertex,
                                    std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                    std::size_t newDegree,
                                    std::size_t oldDegree);

    /**
     *  Update the group to which the given vertex belongs.
     *
     *  @param[in] vertex           The vertex which shall be assigned to a group.
     *  @param[in] verticesByDegree A vector of vertex sets. The degree of each vertex in a given set is equal to the index of the set within the vector.
     *  @param[in] newDegree        The new degree of the vertex.
     */
    static void assignVertexToGroup(htd::vertex_t vertex,
                                    std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                    std::size_t newDegree);

    /**
     *  Decompose two sets of vertices into vertices only in the first set and vertices in both sets.
     *
     *  @param[in] set1                 The first set of vertices, sorted in ascending order.
     *  @param[in] set2                 The second set of vertices, sorted in ascending order.
     *  @param[out] resultOnlySet1      The set of vertices which are found only in the first set, sorted in ascending order.
     *  @param[out] resultIntersection  The set of vertices which are found in both sets, sorted in ascending order.
     */
    void splitSets(const std::vector<htd::vertex_t> & set1,
                   const std::vector<htd::vertex_t> & set2,
                   std::vector<htd::vertex_t> & resultOnlySet1,
                   std::vector<htd::vertex_t> & resultIntersection) const HTD_NOEXCEPT;

    /**
     *  Compute largest biconnected component of the given graph and eliminate all vertices contained in the remainder.
     *
     *  @param[in] graph                The graph which shall be preprocessed.
     *  @param[in] preprocessedGraph    The preprocessed graph which shall be updated.
     *  @param[in] vertices             The set of all available vertices.
     */
    void applyBiconnectedComponentPreprocessing(const htd::IMultiHypergraph & graph,
                                                htd::PreprocessedGraph & preprocessedGraph,
                                                std::unordered_set<htd::vertex_t> & vertices) const;

    /**
     *  Eliminate a connected component from the given preprocessed graph and update the preprocessed graph's elimination sequence.
     *
     *  @param[in] graph                The graph underlying the operation.
     *  @param[in] vertices             The vertices which shall be eliminated.
     *  @param[in] preprocessedGraph    The preprocessed graph which shall be updated.
     *  @param[in,out] minTreeWidth     The lower bound for the treewidth of the given graph component.
     */
    void eliminateVertices(const htd::IMultiHypergraph & graph,
                           const std::unordered_set<htd::vertex_t> & vertices,
                           htd::PreprocessedGraph & preprocessedGraph,
                           std::size_t & minTreeWidth) const;

    /**
     *  Iteratively compute the clique minimal separators of the given graph and remove them from the graph.
     *
     *  @param[in] preprocessedGraph    The preprocessed graph which shall be updated.
     *  @param[in] vertices             The set of all available vertices.
     */
    void applyCliqueSeparatorPreprocessing(htd::PreprocessedGraph & preprocessedGraph,
                                           std::unordered_set<htd::vertex_t> & vertices) const;
};

htd::GraphPreprocessor::GraphPreprocessor(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::GraphPreprocessor::~GraphPreprocessor()
{

}

htd::IPreprocessedGraph * htd::GraphPreprocessor::prepare(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::PreprocessedGraph * ret = nullptr;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    htd::GraphPreprocessor::Implementation::PreparedInput input(managementInstance, graph);

    std::size_t size = input.vertexNames.size();

    std::vector<htd::vertex_t> vertexNames(input.vertexNames.begin(), input.vertexNames.end());

    std::vector<std::vector<htd::vertex_t>> neighborhood(input.neighborhood.begin(), input.neighborhood.end());

    if (implementation_->applyPreprocessing1_ || implementation_->applyPreprocessing2_ || implementation_->applyPreprocessing3_ || implementation_->applyPreprocessing4_)
    {
        std::unordered_set<htd::vertex_t> vertices(size);

        std::vector<std::unordered_set<htd::vertex_t>> verticesByDegree(4);

        std::vector<htd::vertex_t> ordering;
        ordering.reserve(size);

        std::size_t minTreeWidth = 0;

        for (htd::vertex_t vertex = 0; vertex < size; ++vertex)
        {
            vertices.insert(vertex);

            implementation_->assignVertexToGroup(vertex, verticesByDegree, neighborhood[vertex].size());
        }

        while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, verticesByDegree, neighborhood, ordering))
        {

        }

        bool ok = false;

        if (!vertices.empty() && implementation_->applyPreprocessing2_)
        {
            minTreeWidth = 2;

            while (implementation_->contractPaths(vertices, verticesByDegree, neighborhood, ordering))
            {
                ok = true;
            }

            if (ok)
            {
                while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, verticesByDegree, neighborhood, ordering))
                {

                }
            }
        }

        if (!vertices.empty() && implementation_->applyPreprocessing3_)
        {
            minTreeWidth = 3;

            while (implementation_->shrinkTriangles(vertices, verticesByDegree, neighborhood, ordering))
            {
                ok = false;

                while (implementation_->contractPaths(vertices, verticesByDegree, neighborhood, ordering))
                {
                    ok = true;
                }

                if (ok)
                {
                    while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, verticesByDegree, neighborhood, ordering))
                    {

                    }
                }
            }
        }

        if (!vertices.empty() && implementation_->applyPreprocessing4_)
        {
            if (implementation_->eliminateSimplicialVertices(vertices, verticesByDegree, neighborhood, ordering, 64, minTreeWidth))
            {
                while (implementation_->shrinkTriangles(vertices, verticesByDegree, neighborhood, ordering))
                {
                    ok = false;

                    while (implementation_->contractPaths(vertices, verticesByDegree, neighborhood, ordering))
                    {
                        ok = true;
                    }

                    if (ok)
                    {
                        while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, verticesByDegree, neighborhood, ordering))
                        {

                        }
                    }
                }

                while (implementation_->eliminateAlmostSimplicialVertices(vertices, verticesByDegree, neighborhood, ordering, minTreeWidth))
                {
                    while (implementation_->shrinkTriangles(vertices, verticesByDegree, neighborhood, ordering))
                    {
                        ok = false;

                        while (implementation_->contractPaths(vertices, verticesByDegree, neighborhood, ordering))
                        {
                            ok = true;
                        }

                        if (ok)
                        {
                            while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, verticesByDegree, neighborhood, ordering))
                            {

                            }
                        }
                    }
                }
            }
        }

        for (htd::index_t index = 0; index < ordering.size(); ++index)
        {
            ordering[index] = vertexNames[ordering[index]];
        }

        std::vector<htd::vertex_t> remainingVertices(vertices.begin(), vertices.end());

        std::sort(remainingVertices.begin(), remainingVertices.end());

        ret = new htd::PreprocessedGraph(std::move(vertexNames), std::move(neighborhood), std::move(ordering), std::move(remainingVertices), graph.edgeCount(), minTreeWidth);

        if (implementation_->applyPreprocessing4_)
        {
            //TODO
            //implementation_->applyBiconnectedComponentPreprocessing(graph, *ret, vertices);

            //TODO
            //implementation_->applyCliqueSeparatorPreprocessing(*ret, vertices);
        }
    }
    else
    {
        std::vector<htd::vertex_t> remainingVertices(size);

        std::iota(remainingVertices.begin(), remainingVertices.end(), 0);

        ret = new htd::PreprocessedGraph(std::move(vertexNames), std::move(neighborhood), std::vector<htd::vertex_t>(), std::move(remainingVertices), graph.edgeCount(), 0);
    }

    return ret;
}

void htd::GraphPreprocessor::setPreprocessingStrategy(std::size_t level)
{
    if (level == 0)
    {
        implementation_->applyPreprocessing1_ = false;
        implementation_->applyPreprocessing2_ = false;
        implementation_->applyPreprocessing3_ = false;
        implementation_->applyPreprocessing4_ = false;
    }
    else if (level == 1)
    {
        implementation_->applyPreprocessing1_ = true;
        implementation_->applyPreprocessing2_ = true;
        implementation_->applyPreprocessing3_ = false;
        implementation_->applyPreprocessing4_ = false;
    }
    else if (level == 2)
    {
        implementation_->applyPreprocessing1_ = true;
        implementation_->applyPreprocessing2_ = true;
        implementation_->applyPreprocessing3_ = true;
        implementation_->applyPreprocessing4_ = false;
    }
    else if (level > 2)
    {
        implementation_->applyPreprocessing1_ = true;
        implementation_->applyPreprocessing2_ = true;
        implementation_->applyPreprocessing3_ = true;
        implementation_->applyPreprocessing4_ = true;
    }
}

const htd::LibraryInstance * htd::GraphPreprocessor::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::GraphPreprocessor::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

std::size_t htd::GraphPreprocessor::iterationCount(void) const
{
    return implementation_->iterationCount_;
}

void htd::GraphPreprocessor::setIterationCount(std::size_t iterationCount)
{
    implementation_->iterationCount_ = iterationCount;
}

std::size_t htd::GraphPreprocessor::nonImprovementLimit(void) const
{
    return implementation_->nonImprovementLimit_;
}

void htd::GraphPreprocessor::setNonImprovementLimit(std::size_t nonImprovementLimit)
{
    implementation_->nonImprovementLimit_ = nonImprovementLimit;
}

void htd::GraphPreprocessor::setOrderingAlgorithm(htd::IWidthLimitableOrderingAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    delete implementation_->orderingAlgorithm_;

    implementation_->orderingAlgorithm_ = algorithm;
}

htd::GraphPreprocessor * htd::GraphPreprocessor::clone(void) const
{
    return new htd::GraphPreprocessor(implementation_->managementInstance_);
}

void htd::GraphPreprocessor::Implementation::assignVertexToGroup(htd::vertex_t vertex,
                                                                 std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                                 std::size_t newDegree)
{
    if (newDegree < verticesByDegree.size())
    {
        verticesByDegree[newDegree].insert(vertex);
    }
}

void htd::GraphPreprocessor::Implementation::assignVertexToGroup(htd::vertex_t vertex,
                                                                 std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                                 std::size_t newDegree,
                                                                 std::size_t oldDegree)
{
    if (oldDegree < verticesByDegree.size())
    {
        verticesByDegree[oldDegree].erase(vertex);
    }

    assignVertexToGroup(vertex, verticesByDegree, newDegree);
}

bool htd::GraphPreprocessor::Implementation::eliminateVerticesOfDegreeLessThanTwo(std::unordered_set<htd::vertex_t> & vertices,
                                                                                  std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                                                  std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                                                  std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    std::unordered_set<htd::vertex_t> & verticesDegree0 = verticesByDegree[0];

    for (htd::vertex_t vertex : verticesDegree0)
    {
        ordering.push_back(vertex);
    }

    verticesDegree0.clear();

    std::unordered_set<htd::vertex_t> & verticesDegree1 = verticesByDegree[1];

    std::vector<htd::vertex_t> relevantVertices(verticesDegree1.begin(), verticesDegree1.end());

    for (htd::vertex_t vertex : relevantVertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        if (currentNeighborhood.size() == 1)
        {
            htd::vertex_t neighbor = currentNeighborhood[0];

            std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[neighbor];

            /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood'. */
            // coverity[use_iterator]
            otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));

            assignVertexToGroup(neighbor, verticesByDegree, otherNeighborhood.size(), otherNeighborhood.size() + 1);

            std::vector<htd::vertex_t>().swap(currentNeighborhood);

            verticesDegree1.erase(vertex);
        }
        else
        {
            verticesDegree0.erase(vertex);
        }

        ordering.push_back(vertex);
    }

    for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
    {
        vertices.erase(*it);
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::contractPaths(std::unordered_set<htd::vertex_t> & vertices,
                                                           std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                           std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                           std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    std::unordered_set<htd::vertex_t> & verticesDegree2 = verticesByDegree[2];

    std::vector<htd::vertex_t> relevantVertices(verticesDegree2.begin(), verticesDegree2.end());

    for (htd::vertex_t vertex : relevantVertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        if (currentNeighborhood.size() == 2)
        {
            htd::vertex_t neighbor1 = currentNeighborhood[0];
            htd::vertex_t neighbor2 = currentNeighborhood[1];

            std::vector<htd::vertex_t> & otherNeighborhood1 = neighborhood[neighbor1];
            std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor2];

            /* Because 'neighbor1' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood1'. */
            // coverity[use_iterator]
            otherNeighborhood1.erase(std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), vertex));

            /* Because 'neighbor2' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood2'. */
            // coverity[use_iterator]
            otherNeighborhood2.erase(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), vertex));

            auto position = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor2);

            if (position != otherNeighborhood1.end() && *position == neighbor2)
            {
                assignVertexToGroup(neighbor1, verticesByDegree, otherNeighborhood1.size(), otherNeighborhood1.size() + 1);
                assignVertexToGroup(neighbor2, verticesByDegree, otherNeighborhood2.size(), otherNeighborhood2.size() + 1);
            }
            else
            {
                otherNeighborhood1.insert(position, neighbor2);
                otherNeighborhood2.insert(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor1), neighbor1);
            }

            std::vector<htd::vertex_t>().swap(currentNeighborhood);

            verticesDegree2.erase(vertex);

            ordering.push_back(vertex);

            vertices.erase(vertex);
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::shrinkTriangles(std::unordered_set<htd::vertex_t> & vertices,
                                                             std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                             std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                             std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    std::unordered_set<htd::vertex_t> & verticesDegree3 = verticesByDegree[3];

    std::vector<htd::vertex_t> relevantVertices(verticesDegree3.begin(), verticesDegree3.end());

    for (htd::vertex_t vertex : relevantVertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        if (currentNeighborhood.size() == 3)
        {
            htd::vertex_t neighbor1 = currentNeighborhood[0];
            htd::vertex_t neighbor2 = currentNeighborhood[1];
            htd::vertex_t neighbor3 = currentNeighborhood[2];

            std::vector<htd::vertex_t> & otherNeighborhood1 = neighborhood[neighbor1];
            std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor2];
            std::vector<htd::vertex_t> & otherNeighborhood3 = neighborhood[neighbor3];

            std::size_t neighborDegree1 = otherNeighborhood1.size();
            std::size_t neighborDegree2 = otherNeighborhood2.size();
            std::size_t neighborDegree3 = otherNeighborhood3.size();

            bool preprocessingApplicable = false;

            if (std::binary_search(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor2))
            {
                auto position1 = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor3);

                if (position1 == otherNeighborhood1.end() || *position1 != neighbor3)
                {
                    otherNeighborhood1.insert(position1, neighbor3);
                    otherNeighborhood3.insert(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), neighbor1), neighbor1);
                }

                auto position2 = std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor3);

                if (position2 == otherNeighborhood2.end() || *position2 != neighbor3)
                {
                    otherNeighborhood2.insert(position2, neighbor3);
                    otherNeighborhood3.insert(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), neighbor2), neighbor2);
                }

                preprocessingApplicable = true;
            }
            else if (std::binary_search(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor3))
            {
                auto position1 = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor2);

                if (position1 == otherNeighborhood1.end() || *position1 != neighbor2)
                {
                    otherNeighborhood1.insert(position1, neighbor2);
                    otherNeighborhood2.insert(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor1), neighbor1);
                }

                auto position2 = std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor3);

                if (position2 == otherNeighborhood2.end() || *position2 != neighbor3)
                {
                    otherNeighborhood2.insert(position2, neighbor3);
                    otherNeighborhood3.insert(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), neighbor2), neighbor2);
                }

                preprocessingApplicable = true;
            }
            else if (std::binary_search(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor3))
            {
                auto position1 = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor2);

                if (position1 == otherNeighborhood1.end() || *position1 != neighbor2)
                {
                    otherNeighborhood1.insert(position1, neighbor2);
                    otherNeighborhood2.insert(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor1), neighbor1);
                }

                auto position2 = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor3);

                if (position2 == otherNeighborhood1.end() || *position2 != neighbor3)
                {
                    otherNeighborhood1.insert(position2, neighbor3);
                    otherNeighborhood3.insert(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), neighbor1), neighbor1);
                }

                preprocessingApplicable = true;
            }

            if (preprocessingApplicable)
            {
                /* Because 'neighbor1' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood1'. */
                // coverity[use_iterator]
                otherNeighborhood1.erase(std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), vertex));

                /* Because 'neighbor2' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood2'. */
                // coverity[use_iterator]
                otherNeighborhood2.erase(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), vertex));

                /* Because 'neighbor3' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood3'. */
                // coverity[use_iterator]
                otherNeighborhood3.erase(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), vertex));

                if (neighborDegree1 != otherNeighborhood1.size())
                {
                    assignVertexToGroup(neighbor1, verticesByDegree, otherNeighborhood1.size(), neighborDegree1);
                }

                if (neighborDegree2 != otherNeighborhood2.size())
                {
                    assignVertexToGroup(neighbor2, verticesByDegree, otherNeighborhood2.size(), neighborDegree2);
                }

                if (neighborDegree3 != otherNeighborhood3.size())
                {
                    assignVertexToGroup(neighbor3, verticesByDegree, otherNeighborhood3.size(), neighborDegree3);
                }

                std::vector<htd::vertex_t>().swap(currentNeighborhood);

                verticesDegree3.erase(vertex);

                ordering.push_back(vertex);

                vertices.erase(vertex);
            }
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::handleBuddies(std::unordered_set<htd::vertex_t> & vertices,
                                                           std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                           std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                           std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    std::unordered_set<htd::vertex_t> & verticesDegree3 = verticesByDegree[3];

    std::vector<htd::vertex_t> relevantVertices(verticesDegree3.begin(), verticesDegree3.end());

    if (relevantVertices.size() > 1)
    {
        for (auto it1 = relevantVertices.begin(); it1 != relevantVertices.end() - 1;)
        {
            /* Because 'relevantVertices' has more than one element, 'it1' will always point to a valid element. */
            // coverity[deref_iterator]
            htd::vertex_t vertex1 = *it1;

            std::vector<htd::vertex_t> & currentNeighborhood1 = neighborhood[vertex1];

            ++it1;

            if (currentNeighborhood1.size() == 3)
            {
                bool matchFound = false;

                for (auto it2 = it1; !matchFound && it2 != relevantVertices.end(); ++it2)
                {
                    htd::vertex_t vertex2 = *it2;

                    std::vector<htd::vertex_t> & currentNeighborhood2 = neighborhood[vertex2];

                    if (currentNeighborhood2.size() == 3)
                    {
                        if (currentNeighborhood1 == currentNeighborhood2)
                        {
                            htd::vertex_t neighbor1 = currentNeighborhood1[0];
                            htd::vertex_t neighbor2 = currentNeighborhood1[1];
                            htd::vertex_t neighbor3 = currentNeighborhood1[2];

                            std::vector<htd::vertex_t> & otherNeighborhood1 = neighborhood[neighbor1];
                            std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor2];
                            std::vector<htd::vertex_t> & otherNeighborhood3 = neighborhood[neighbor3];

                            std::size_t neighborDegree1 = otherNeighborhood1.size();
                            std::size_t neighborDegree2 = otherNeighborhood2.size();
                            std::size_t neighborDegree3 = otherNeighborhood3.size();

                            for (htd::vertex_t vertex : currentNeighborhood1)
                            {
                                std::vector<htd::vertex_t> & currentNeighborhood3 = neighborhood[vertex];

                                /* Because 'vertex' is a neighbor of 'vertex1', std::lower_bound will always find 'vertex1' in 'currentNeighborhood3'. */
                                // coverity[use_iterator]
                                currentNeighborhood3.erase(std::lower_bound(currentNeighborhood3.begin(), currentNeighborhood3.end(), vertex1));

                                /* Because 'vertex' is a neighbor of 'vertex2', std::lower_bound will always find 'vertex2' in 'currentNeighborhood3'. */
                                // coverity[use_iterator]
                                currentNeighborhood3.erase(std::lower_bound(currentNeighborhood3.begin(), currentNeighborhood3.end(), vertex2));
                            }

                            for (auto it3 = currentNeighborhood1.begin(); it3 != currentNeighborhood1.end() - 1; ++it3)
                            {
                                htd::vertex_t neighbor1 = *it3;

                                std::vector<htd::vertex_t> & currentNeighborhood3 = neighborhood[neighbor1];

                                for (auto it4 = it3 + 1; it4 != currentNeighborhood1.end(); ++it4)
                                {
                                    htd::vertex_t neighbor2 = *it4;

                                    std::vector<htd::vertex_t> & currentNeighborhood4 = neighborhood[neighbor2];

                                    auto position1 = std::lower_bound(currentNeighborhood3.begin(), currentNeighborhood3.end(), neighbor2);

                                    if (position1 == currentNeighborhood3.end() || *position1 != neighbor2)
                                    {
                                        currentNeighborhood3.insert(position1, neighbor2);

                                        auto position2 = std::lower_bound(currentNeighborhood4.begin(), currentNeighborhood4.end(), neighbor1);

                                        currentNeighborhood4.insert(position2, neighbor1);
                                    }
                                }
                            }

                            assignVertexToGroup(neighbor1, verticesByDegree, neighborhood[neighbor1].size(), neighborDegree1);
                            assignVertexToGroup(neighbor2, verticesByDegree, neighborhood[neighbor2].size(), neighborDegree2);
                            assignVertexToGroup(neighbor3, verticesByDegree, neighborhood[neighbor3].size(), neighborDegree3);

                            std::vector<htd::vertex_t>().swap(currentNeighborhood1);
                            std::vector<htd::vertex_t>().swap(currentNeighborhood2);

                            ordering.push_back(vertex1);
                            ordering.push_back(vertex2);

                            matchFound = true;
                        }
                    }
                }
            }
        }

        for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
        {
            vertices.erase(*it);

            verticesDegree3.erase(*it);
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::eliminateSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                                                         std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                                         std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                                         std::vector<htd::vertex_t> & ordering,
                                                                         std::size_t maxDegree,
                                                                         std::size_t & minTreewidth)
{
    std::size_t oldOrderingSize = ordering.size();

    for (htd::vertex_t vertex : vertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        if (currentNeighborhood.size() <= maxDegree)
        {
            bool ok = true;

            for (auto it = currentNeighborhood.begin(); ok && it != currentNeighborhood.end(); ++it)
            {
                const std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[*it];

                ok = htd::set_intersection_size(otherNeighborhood.begin(), otherNeighborhood.end(), currentNeighborhood.begin(), currentNeighborhood.end()) == currentNeighborhood.size() - 1;
            }

            if (ok)
            {
                for (htd::vertex_t neighbor : currentNeighborhood)
                {
                    std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[neighbor];

                    /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood'. */
                    // coverity[use_iterator]
                    otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));

                    assignVertexToGroup(neighbor, verticesByDegree, otherNeighborhood.size(), otherNeighborhood.size() + 1);
                }

                minTreewidth = std::max(minTreewidth, currentNeighborhood.size());

                std::vector<htd::vertex_t>().swap(currentNeighborhood);

                ordering.push_back(vertex);
            }
        }
    }

    std::unordered_set<htd::vertex_t> & verticesDegree0 = verticesByDegree[0];
    std::unordered_set<htd::vertex_t> & verticesDegree1 = verticesByDegree[1];
    std::unordered_set<htd::vertex_t> & verticesDegree2 = verticesByDegree[2];
    std::unordered_set<htd::vertex_t> & verticesDegree3 = verticesByDegree[3];

    for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
    {
        vertices.erase(*it);

        verticesDegree0.erase(*it);
        verticesDegree1.erase(*it);
        verticesDegree2.erase(*it);
        verticesDegree3.erase(*it);
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::eliminateAlmostSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                                                               std::vector<std::unordered_set<htd::vertex_t>> & verticesByDegree,
                                                                               std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                                               std::vector<htd::vertex_t> & ordering,
                                                                               std::size_t & minTreeWidth)
{
    std::size_t oldOrderingSize = ordering.size();

    for (htd::vertex_t vertex : vertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        if (currentNeighborhood.size() > 1 && currentNeighborhood.size() <= minTreeWidth)
        {
            bool ok = true;

            std::size_t oldMissingVertexCount = 0;

            std::vector<htd::vertex_t> missingVertices;

            for (auto it = currentNeighborhood.begin(); ok && it != currentNeighborhood.end(); ++it)
            {
                const std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[*it];

                std::set_difference(currentNeighborhood.begin(), currentNeighborhood.end(), otherNeighborhood.begin(), otherNeighborhood.end(), std::back_inserter(missingVertices));

                missingVertices.erase(std::lower_bound(missingVertices.begin() + oldMissingVertexCount, missingVertices.end(), *it));

                std::inplace_merge(missingVertices.begin(), missingVertices.begin() + oldMissingVertexCount, missingVertices.end());

                oldMissingVertexCount = missingVertices.size();
            }

            if (missingVertices.empty())
            {
                for (htd::vertex_t neighbor : currentNeighborhood)
                {
                    std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[neighbor];

                    /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood'. */
                    // coverity[use_iterator]
                    otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));

                    assignVertexToGroup(neighbor, verticesByDegree, otherNeighborhood.size(), otherNeighborhood.size() + 1);
                }

                minTreeWidth = std::max(minTreeWidth, currentNeighborhood.size());

                std::vector<htd::vertex_t>().swap(currentNeighborhood);

                ordering.push_back(vertex);
            }
            else
            {
                auto it = missingVertices.begin();

                auto duplicate =  missingVertices.end();

                for (auto next = it; ++next != missingVertices.end() && duplicate == missingVertices.end(); ++it)
                {
                    if (*it == *next)
                    {
                        duplicate = it;
                    }
                }

                if (duplicate != missingVertices.end())
                {
                    htd::vertex_t culprit = *it;

                    missingVertices.erase(duplicate, std::upper_bound(duplicate, missingVertices.end(), culprit));

                    if (htd::is_sorted_and_duplicate_free(missingVertices.begin(), missingVertices.end()))
                    {
                        std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[culprit];

                        std::vector<htd::vertex_t> missingVertices2;

                        std::set_difference(currentNeighborhood.begin(), currentNeighborhood.end(), otherNeighborhood.begin(), otherNeighborhood.end(), std::back_inserter(missingVertices2));

                        missingVertices2.erase(std::lower_bound(missingVertices2.begin(), missingVertices2.end(), culprit));

                        if (htd::set_difference_size(missingVertices.begin(), missingVertices.end(), missingVertices2.begin(), missingVertices2.end()) == 0)
                        {
                            for (htd::vertex_t neighbor : missingVertices2)
                            {
                                std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor];

                                otherNeighborhood2.insert(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), culprit), culprit);

                                assignVertexToGroup(neighbor, verticesByDegree, otherNeighborhood2.size(), otherNeighborhood2.size() - 1);
                            }

                            std::size_t middle = otherNeighborhood.size();

                            otherNeighborhood.insert(otherNeighborhood.end(), missingVertices2.begin(), missingVertices2.end());

                            std::inplace_merge(otherNeighborhood.begin(), otherNeighborhood.begin() + middle, otherNeighborhood.end());

                            assignVertexToGroup(culprit, verticesByDegree, otherNeighborhood.size(), middle);

                            for (htd::vertex_t neighbor : currentNeighborhood)
                            {
                                std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor];

                                /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood2'. */
                                // coverity[use_iterator]
                                otherNeighborhood2.erase(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), vertex));

                                assignVertexToGroup(neighbor, verticesByDegree, otherNeighborhood2.size(), otherNeighborhood2.size() + 1);
                            }

                            std::vector<htd::vertex_t>().swap(currentNeighborhood);

                            ordering.push_back(vertex);
                        }
                    }
                }
            }
        }
    }

    std::unordered_set<htd::vertex_t> & verticesDegree0 = verticesByDegree[0];
    std::unordered_set<htd::vertex_t> & verticesDegree1 = verticesByDegree[1];
    std::unordered_set<htd::vertex_t> & verticesDegree2 = verticesByDegree[2];
    std::unordered_set<htd::vertex_t> & verticesDegree3 = verticesByDegree[3];

    for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
    {
        vertices.erase(*it);

        verticesDegree0.erase(*it);
        verticesDegree1.erase(*it);
        verticesDegree2.erase(*it);
        verticesDegree3.erase(*it);
    }

    return ordering.size() > oldOrderingSize;
}

void htd::GraphPreprocessor::Implementation::splitSets(const std::vector<htd::vertex_t> & set1,
                                                       const std::vector<htd::vertex_t> & set2,
                                                       std::vector<htd::vertex_t> & resultOnlySet1,
                                                       std::vector<htd::vertex_t> & resultIntersection) const HTD_NOEXCEPT
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            resultOnlySet1.push_back(*first1);

            ++first1;
        }
        else if (*first2 < *first1)
        {
            ++first2;
        }
        else
        {
            resultIntersection.push_back(*first1);

            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    if (first1 != last1)
    {
        resultOnlySet1.insert(resultOnlySet1.end(), first1, last1);
    }
}

void htd::GraphPreprocessor::Implementation::applyBiconnectedComponentPreprocessing(const htd::IMultiHypergraph & graph,
                                                                                    htd::PreprocessedGraph & preprocessedGraph,
                                                                                    std::unordered_set<htd::vertex_t> & vertices) const
{
    htd::BiconnectedComponentAlgorithm biconnectedComponentAlgorithm(managementInstance_);

    std::vector<htd::vertex_t> articulationPoints;

    std::vector<std::vector<htd::vertex_t>> components;

    biconnectedComponentAlgorithm.determineComponents(preprocessedGraph, components, articulationPoints);

    if (components.size() > 1)
    {
        std::vector<htd::index_t> pool;
        htd::index_t index = 0;
        std::size_t max = 0;
        for (const std::vector<htd::vertex_t> & component : components)
        {
            std::size_t size = component.size();

            if (size >= max)
            {
                if (size > max)
                {
                    max = size;

                    pool.clear();
                }

                pool.push_back(index);
            }

            ++index;
        }

        const std::vector<htd::vertex_t> & selectedComponent = components[htd::selectRandomElement<htd::index_t>(pool)];

        std::vector<htd::vertex_t> relevantArticulationPoints;

        std::set_intersection(selectedComponent.begin(), selectedComponent.end(),
                              articulationPoints.begin(), articulationPoints.end(),
                              std::back_inserter(relevantArticulationPoints));

        for (htd::vertex_t vertex : relevantArticulationPoints)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = preprocessedGraph.neighborhood(vertex);

            std::vector<htd::vertex_t> newNeighborhood;
            std::vector<htd::vertex_t> otherNeighbors;

            splitSets(currentNeighborhood, selectedComponent, otherNeighbors, newNeighborhood);

            currentNeighborhood.swap(newNeighborhood);

            for (htd::vertex_t neighbor : otherNeighbors)
            {
                std::vector<htd::vertex_t> & otherNeighborhood = preprocessedGraph.neighborhood(neighbor);

                /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'otherNeighborhood'. */
                // coverity[use_iterator]
                otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));
            }
        }

        preprocessedGraph.updateEdgeCount();

        htd::IConnectedComponentAlgorithm * connectedComponentAlgorithm = managementInstance_->connectedComponentAlgorithmFactory().createInstance();

        std::vector<std::vector<htd::vertex_t>> connectedComponents;

        connectedComponentAlgorithm->determineComponents(preprocessedGraph, connectedComponents);

        delete connectedComponentAlgorithm;

        auto position = std::find_if(connectedComponents.begin(), connectedComponents.end(),
                                     [&](const std::vector<htd::vertex_t> & component)
        {
            return std::binary_search(component.begin(), component.end(), selectedComponent[0]);
        });

        HTD_ASSERT(position != connectedComponents.end())

        /*
         * After separating the largest biconnected component from the remainder of the graph,
         * it forms a connected component of the graph, i.e., the iterator 'position' always
         * points to a valid position within the set of connected components.
         */
        // coverity[deref_iterator]
        position->swap(*(connectedComponents.rbegin()));

        std::sort(connectedComponents.begin(), connectedComponents.end() - 1,
                  [](const std::vector<htd::vertex_t> & component1, const std::vector<htd::vertex_t> & component2)
        {
           return component1.size() < component2.size();
        });

        for (const std::vector<htd::vertex_t> & component : connectedComponents)
        {
            std::vector<std::unordered_set<htd::vertex_t>> verticesByDegree(4);

            std::size_t oldOrderingSize = preprocessedGraph.eliminationSequence().size();

            std::unordered_set<htd::vertex_t> componentVertices(component.begin(), component.end());

            std::size_t minTreeWidth = 0;

            for (htd::vertex_t vertex : component)
            {
                assignVertexToGroup(vertex, verticesByDegree, preprocessedGraph.neighborhood(vertex).size());
            }

            while (eliminateVerticesOfDegreeLessThanTwo(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
            {

            }

            bool ok = false;

            if (!componentVertices.empty())
            {
                minTreeWidth = 2;

                while (contractPaths(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                {
                    ok = true;
                }

                if (ok)
                {
                    while (eliminateVerticesOfDegreeLessThanTwo(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                    {

                    }
                }
            }

            if (!componentVertices.empty())
            {
                minTreeWidth = 3;

                while (shrinkTriangles(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                {
                    ok = false;

                    while (contractPaths(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                    {
                        ok = true;
                    }

                    if (ok)
                    {
                        while (eliminateVerticesOfDegreeLessThanTwo(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                        {

                        }
                    }
                }
            }

            if (!componentVertices.empty())
            {
                if (eliminateSimplicialVertices(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence(), 64, minTreeWidth))
                {
                    while (shrinkTriangles(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                    {
                        ok = false;

                        while (contractPaths(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                        {
                            ok = true;
                        }

                        if (ok)
                        {
                            while (eliminateVerticesOfDegreeLessThanTwo(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                            {

                            }
                        }
                    }

                    while (eliminateAlmostSimplicialVertices(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence(), minTreeWidth))
                    {
                        while (shrinkTriangles(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                        {
                            ok = false;

                            while (contractPaths(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                            {
                                ok = true;
                            }

                            if (ok)
                            {
                                while (eliminateVerticesOfDegreeLessThanTwo(componentVertices, verticesByDegree, preprocessedGraph.neighborhood(), preprocessedGraph.eliminationSequence()))
                                {

                                }
                            }
                        }
                    }
                }
            }

            for (auto it = preprocessedGraph.eliminationSequence().begin() + oldOrderingSize; it != preprocessedGraph.eliminationSequence().end(); ++it)
            {
                vertices.erase(*it);

                *it = preprocessedGraph.vertexName(*it);
            }

            if (!std::binary_search(component.begin(), component.end(), selectedComponent[0]))
            {
                oldOrderingSize = preprocessedGraph.eliminationSequence().size();

                eliminateVertices(graph, componentVertices, preprocessedGraph, minTreeWidth);

                for (auto it = componentVertices.begin(); it != componentVertices.end(); ++it)
                {
                    vertices.erase(*it);
                }
            }
            else
            {
                std::vector<htd::vertex_t> remainingVertices(componentVertices.begin(), componentVertices.end());

                std::sort(remainingVertices.begin(), remainingVertices.end());

                preprocessedGraph.setRemainingVertices(std::move(remainingVertices));
            }

            preprocessedGraph.minTreeWidth() = std::max(preprocessedGraph.minTreeWidth(), minTreeWidth);
        }
    }
}

void htd::GraphPreprocessor::Implementation::eliminateVertices(const htd::IMultiHypergraph & graph,
                                                               const std::unordered_set<htd::vertex_t> & vertices,
                                                               htd::PreprocessedGraph & preprocessedGraph,
                                                               std::size_t & minTreeWidth) const
{
    std::vector<htd::vertex_t> remainingComponentVertices(vertices.begin(), vertices.end());

    std::sort(remainingComponentVertices.begin(), remainingComponentVertices.end());

    htd::PreprocessedGraphComponent component(preprocessedGraph, std::move(remainingComponentVertices), minTreeWidth);

    htd::IWidthLimitedVertexOrdering * optimalOrdering = nullptr;

    std::size_t bestMaxBagSize = 0;

    htd::index_t iteration = 0;

    while ((iteration == 0 || iterationCount_ == 0 || iteration < iterationCount_) && !managementInstance_->isTerminated())
    {
        std::size_t remainingIterations = iterationCount_ - iteration;

        if (nonImprovementLimit_ < (std::size_t)-1)
        {
            remainingIterations = std::min(remainingIterations, nonImprovementLimit_);
        }

        htd::IWidthLimitedVertexOrdering * currentOrdering = orderingAlgorithm_->computeOrdering(graph, component, bestMaxBagSize - 1, remainingIterations);

        if (currentOrdering->requiredIterations() < nonImprovementLimit_)
        {
            iteration += currentOrdering->requiredIterations();
        }
        else
        {
            iteration = (std::size_t)-1;
        }

        std::size_t currentMaxBagSize = currentOrdering->maximumBagSize();

        if (!managementInstance_->isTerminated())
        {
            if ((iteration == 1 && bestMaxBagSize == 0) || currentMaxBagSize < bestMaxBagSize)
            {
                if (iteration > 1)
                {
                    delete optimalOrdering;
                }

                optimalOrdering = currentOrdering;

                bestMaxBagSize = currentMaxBagSize;
            }
            else
            {
                delete currentOrdering;
            }
        }
        else
        {
            delete currentOrdering;
        }
    }

    if (optimalOrdering != nullptr)
    {
        preprocessedGraph.eliminationSequence().insert(preprocessedGraph.eliminationSequence().end(), optimalOrdering->sequence().begin(), optimalOrdering->sequence().end());

        preprocessedGraph.minTreeWidth() = std::max(preprocessedGraph.minTreeWidth(), optimalOrdering->maximumBagSize() - 1);

        delete optimalOrdering;
    }
}

void htd::GraphPreprocessor::Implementation::applyCliqueSeparatorPreprocessing(htd::PreprocessedGraph & preprocessedGraph,
                                                                               std::unordered_set<htd::vertex_t> & vertices) const
{
    htd::CliqueMinimalSeparatorAlgorithm algorithm(managementInstance_);

    std::vector<htd::vertex_t> * separator = algorithm.computeSeparator(preprocessedGraph);

    while (separator != nullptr && !separator->empty())
    {
        for (htd::vertex_t vertex : *separator)
        {
            preprocessedGraph.removeVertex(vertex);

            vertices.erase(vertex);
        }

        delete separator;

        separator = algorithm.computeSeparator(preprocessedGraph);
    }

    if (separator != nullptr)
    {
        delete separator;
    }
}

#endif /* HTD_HTD_GRAPHPREPROCESSOR_CPP */
