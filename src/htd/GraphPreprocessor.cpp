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

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

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
                                                                 applyPreprocessing4_(false)
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
        void initialize(const htd::IMultiHypergraph & graph,
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
        PreparedInput(const htd::LibraryInstance & managementInstance, const htd::IMultiHypergraph & graph) : vertexNames(), neighborhood()
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
     *  @param[in] vertices     The set of all available vertices.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] neighborhood The neighborhood relation of the remaining graph.
     *  @param[in] ordering     The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    bool eliminateVerticesOfDegreeLessThanTwo(std::unordered_set<htd::vertex_t> & vertices,
                                              std::unordered_set<htd::vertex_t> & vertexGroup1,
                                              std::unordered_set<htd::vertex_t> & vertexGroup2,
                                              std::unordered_set<htd::vertex_t> & vertexGroup3,
                                              std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                              std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices of degree 2 from the graph.
     *
     *  @param[in] vertices     The set of all available vertices.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] neighborhood The neighborhood relation of the remaining graph.
     *  @param[in] ordering     The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    bool contractPaths(std::unordered_set<htd::vertex_t> & vertices,
                       std::unordered_set<htd::vertex_t> & vertexGroup1,
                       std::unordered_set<htd::vertex_t> & vertexGroup2,
                       std::unordered_set<htd::vertex_t> & vertexGroup3,
                       std::vector<std::vector<htd::vertex_t>> & neighborhood,
                       std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices of degree 3 from the graph in
     *  case that at least two of its neighbors are adjacent.
     *
     *  @param[in] vertices     The set of all available vertices.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] neighborhood The neighborhood relation of the remaining graph.
     *  @param[in] ordering     The resulting, partial vertex elimination ordering.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    bool shrinkTriangles(std::unordered_set<htd::vertex_t> & vertices,
                         std::unordered_set<htd::vertex_t> & vertexGroup1,
                         std::unordered_set<htd::vertex_t> & vertexGroup2,
                         std::unordered_set<htd::vertex_t> & vertexGroup3,
                         std::vector<std::vector<htd::vertex_t>> & neighborhood,
                         std::vector<htd::vertex_t> & ordering);

    /**
     *  Eliminate all vertices from the graph for which
     *  it holds that all its neighbors form a clique.
     *
     *  @param[in] vertices     The set of all available vertices.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] neighborhood The neighborhood relation of the remaining graph.
     *  @param[in] ordering     The resulting, partial vertex elimination ordering.
     *  @param[in] maxDegree    The degree up to which a vertex shall be considered for this preprocessing.
     *  @param[in] minTreeWidth The lower bound for the treewidth of the given graph.
     *
     *  @return True if at least one vertex was removed due to this preprocessing step, false otherwise.
     */
    bool eliminateSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                     std::unordered_set<htd::vertex_t> & vertexGroup1,
                                     std::unordered_set<htd::vertex_t> & vertexGroup2,
                                     std::unordered_set<htd::vertex_t> & vertexGroup3,
                                     std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                     std::vector<htd::vertex_t> & ordering,
                                     std::size_t maxDegree,
                                     std::size_t & minTreeWidth);

    /**
     *  Update the group to which the given vertex belongs.
     *
     *  @param[in] vertex       The vertex which shall be assigned to a group.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] newDegree    The new degree of the vertex.
     *  @param[in] oldDegree    The old degree of the vertex.
     */
    void assignVertexToGroup(htd::vertex_t vertex,
                             std::unordered_set<htd::vertex_t> & vertexGroup1,
                             std::unordered_set<htd::vertex_t> & vertexGroup2,
                             std::unordered_set<htd::vertex_t> & vertexGroup3,
                             std::size_t newDegree,
                             std::size_t oldDegree);

    /**
     *  Update the group to which the given vertex belongs.
     *
     *  @param[in] vertex       The vertex which shall be assigned to a group.
     *  @param[in] vertexGroup1 The set of all vertices of degree <= 2.
     *  @param[in] vertexGroup2 The set of all vertices of degree 2.
     *  @param[in] vertexGroup3 The set of all vertices of degree 3.
     *  @param[in] newDegree    The new degree of the vertex.
     */
    void assignVertexToGroup(htd::vertex_t vertex,
                             std::unordered_set<htd::vertex_t> & vertexGroup1,
                             std::unordered_set<htd::vertex_t> & vertexGroup2,
                             std::unordered_set<htd::vertex_t> & vertexGroup3,
                             std::size_t newDegree);
};

htd::GraphPreprocessor::GraphPreprocessor(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::GraphPreprocessor::~GraphPreprocessor()
{
    
}

htd::IPreprocessedGraph * htd::GraphPreprocessor::prepare(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::IPreprocessedGraph * ret = nullptr;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    htd::GraphPreprocessor::Implementation::PreparedInput input(managementInstance, graph);

    std::size_t size = input.vertexNames.size();

    std::vector<htd::vertex_t> vertexNames(input.vertexNames.begin(), input.vertexNames.end());

    std::vector<std::vector<htd::vertex_t>> neighborhood(input.neighborhood.begin(), input.neighborhood.end());

    if (implementation_->applyPreprocessing1_ || implementation_->applyPreprocessing2_ || implementation_->applyPreprocessing3_ || implementation_->applyPreprocessing4_)
    {
        std::unordered_set<htd::vertex_t> vertices(size);

        std::unordered_set<htd::vertex_t> vertexGroup1;
        std::unordered_set<htd::vertex_t> vertexGroup2;
        std::unordered_set<htd::vertex_t> vertexGroup3;

        std::vector<htd::vertex_t> ordering;
        ordering.reserve(size);

        std::size_t minTreeWidth = 0;

        for (htd::vertex_t vertex = 0; vertex < size; ++vertex)
        {
            vertices.insert(vertex);

            implementation_->assignVertexToGroup(vertex, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood[vertex].size());
        }

        while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
        {

        }

        bool ok = false;

        if (!vertices.empty())
        {
            minTreeWidth = 2;

            while (implementation_->contractPaths(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
            {
                ok = true;
            }

            if (ok)
            {
                while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                {

                }
            }
        }

        if (!vertices.empty())
        {
            minTreeWidth = 3;

            while (implementation_->shrinkTriangles(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
            {
                ok = false;

                while (implementation_->contractPaths(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                {
                    ok = true;
                }

                if (ok)
                {
                    while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                    {

                    }
                }
            }
        }

        if (!vertices.empty())
        {
            while (implementation_->eliminateSimplicialVertices(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering, 16, minTreeWidth))
            {
                while (implementation_->shrinkTriangles(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                {
                    ok = false;

                    while (implementation_->contractPaths(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                    {
                        ok = true;
                    }

                    if (ok)
                    {
                        while (implementation_->eliminateVerticesOfDegreeLessThanTwo(vertices, vertexGroup1, vertexGroup2, vertexGroup3, neighborhood, ordering))
                        {

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

htd::GraphPreprocessor * htd::GraphPreprocessor::clone(void) const
{
    return new htd::GraphPreprocessor(implementation_->managementInstance_);
}

void htd::GraphPreprocessor::Implementation::assignVertexToGroup(htd::vertex_t vertex,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                                 std::size_t newDegree)
{
    switch (newDegree)
    {
        case 0:
        case 1:
        {
            vertexGroup1.insert(vertex);

            break;
        }
        case 2:
        {
            vertexGroup2.insert(vertex);

            break;
        }
        case 3:
        {
            vertexGroup3.insert(vertex);

            break;
        }
    }
}

void htd::GraphPreprocessor::Implementation::assignVertexToGroup(htd::vertex_t vertex,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                                 std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                                 std::size_t newDegree,
                                                                 std::size_t oldDegree)
{
    switch (oldDegree)
    {
        case 0:
        case 1:
        {
            vertexGroup1.erase(vertex);

            break;
        }
        case 2:
        {
            vertexGroup2.erase(vertex);

            break;
        }
        case 3:
        {
            vertexGroup3.erase(vertex);

            break;
        }
    }

    assignVertexToGroup(vertex, vertexGroup1, vertexGroup2, vertexGroup3, newDegree);
}

bool htd::GraphPreprocessor::Implementation::eliminateVerticesOfDegreeLessThanTwo(std::unordered_set<htd::vertex_t> & vertices,
                                                                                  std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                                                  std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                                                  std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                                                  std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                                                  std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    if (applyPreprocessing1_)
    {
        std::vector<htd::vertex_t> relevantVertices(vertexGroup1.begin(), vertexGroup1.end());

        for (htd::vertex_t vertex : relevantVertices)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

            if (currentNeighborhood.size() == 1)
            {
                htd::vertex_t neighbor = currentNeighborhood[0];

                std::vector<htd::vertex_t> & otherNeighborhood = neighborhood[neighbor];

                otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));

                assignVertexToGroup(neighbor, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood.size(), otherNeighborhood.size() + 1);
            }

            currentNeighborhood.clear();

            ordering.push_back(vertex);
        }

        for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
        {
            vertices.erase(*it);

            vertexGroup1.erase(*it);
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::contractPaths(std::unordered_set<htd::vertex_t> & vertices,
                                                           std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                           std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                           std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                           std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                           std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    if (applyPreprocessing2_)
    {
        std::vector<htd::vertex_t> relevantVertices(vertexGroup2.begin(), vertexGroup2.end());

        for (htd::vertex_t vertex : relevantVertices)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

            if (currentNeighborhood.size() == 2)
            {
                htd::vertex_t neighbor1 = currentNeighborhood[0];
                htd::vertex_t neighbor2 = currentNeighborhood[1];

                std::vector<htd::vertex_t> & otherNeighborhood1 = neighborhood[neighbor1];
                std::vector<htd::vertex_t> & otherNeighborhood2 = neighborhood[neighbor2];

                otherNeighborhood1.erase(std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), vertex));
                otherNeighborhood2.erase(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), vertex));

                auto position = std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), neighbor2);

                if (position != otherNeighborhood1.end() && *position == neighbor2)
                {
                    assignVertexToGroup(neighbor1, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood1.size(), otherNeighborhood1.size() + 1);
                    assignVertexToGroup(neighbor2, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood2.size(), otherNeighborhood2.size() + 1);
                }
                else
                {
                    otherNeighborhood1.insert(position, neighbor2);
                    otherNeighborhood2.insert(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), neighbor1), neighbor1);
                }

                currentNeighborhood.clear();

                ordering.push_back(vertex);
            }
        }

        for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
        {
            vertices.erase(*it);

            vertexGroup2.erase(*it);
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::shrinkTriangles(std::unordered_set<htd::vertex_t> & vertices,
                                                             std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                             std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                             std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                             std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                             std::vector<htd::vertex_t> & ordering)
{
    std::size_t oldOrderingSize = ordering.size();

    if (applyPreprocessing3_)
    {
        std::vector<htd::vertex_t> relevantVertices(vertexGroup3.begin(), vertexGroup3.end());

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
                std::size_t neighborDegree2 = otherNeighborhood1.size();
                std::size_t neighborDegree3 = otherNeighborhood1.size();

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
                    otherNeighborhood1.erase(std::lower_bound(otherNeighborhood1.begin(), otherNeighborhood1.end(), vertex));
                    otherNeighborhood2.erase(std::lower_bound(otherNeighborhood2.begin(), otherNeighborhood2.end(), vertex));
                    otherNeighborhood3.erase(std::lower_bound(otherNeighborhood3.begin(), otherNeighborhood3.end(), vertex));

                    if (neighborDegree1 != otherNeighborhood1.size())
                    {
                        assignVertexToGroup(neighbor1, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood1.size(), neighborDegree1);
                    }

                    if (neighborDegree2 != otherNeighborhood2.size())
                    {
                        assignVertexToGroup(neighbor2, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood2.size(), neighborDegree2);
                    }

                    if (neighborDegree3 != otherNeighborhood3.size())
                    {
                        assignVertexToGroup(neighbor3, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood3.size(), neighborDegree3);
                    }

                    currentNeighborhood.clear();

                    ordering.push_back(vertex);
                }
            }
        }

        for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
        {
            vertices.erase(*it);

            vertexGroup3.erase(*it);
        }
    }

    return ordering.size() > oldOrderingSize;
}

bool htd::GraphPreprocessor::Implementation::eliminateSimplicialVertices(std::unordered_set<htd::vertex_t> & vertices,
                                                                         std::unordered_set<htd::vertex_t> & vertexGroup1,
                                                                         std::unordered_set<htd::vertex_t> & vertexGroup2,
                                                                         std::unordered_set<htd::vertex_t> & vertexGroup3,
                                                                         std::vector<std::vector<htd::vertex_t>> & neighborhood,
                                                                         std::vector<htd::vertex_t> & ordering,
                                                                         std::size_t maxDegree,
                                                                         std::size_t & minTreewidth)
{
    std::size_t oldOrderingSize = ordering.size();

    if (applyPreprocessing4_)
    {
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

                        otherNeighborhood.erase(std::lower_bound(otherNeighborhood.begin(), otherNeighborhood.end(), vertex));

                        assignVertexToGroup(neighbor, vertexGroup1, vertexGroup2, vertexGroup3, otherNeighborhood.size(), otherNeighborhood.size() + 1);
                    }

                    minTreewidth = std::max(minTreewidth, currentNeighborhood.size());

                    currentNeighborhood.clear();

                    ordering.push_back(vertex);
                }
            }
        }

        for (auto it = ordering.begin() + oldOrderingSize; it != ordering.end(); ++it)
        {
            vertices.erase(*it);

            vertexGroup1.erase(*it);
            vertexGroup2.erase(*it);
            vertexGroup3.erase(*it);
        }
    }

    return ordering.size() > oldOrderingSize;
}

#endif /* HTD_HTD_GRAPHPREPROCESSOR_CPP */
