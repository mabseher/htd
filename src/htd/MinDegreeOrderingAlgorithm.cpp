/* 
 * File:   MinDegreeOrderingAlgorithm.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP
#define HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::MinDegreeOrderingAlgorithm.
 */
struct htd::MinDegreeOrderingAlgorithm::Implementation
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
     *  Update the pool of vertices with minimum degree.
     *
     *  @param[in] vertex           The vertex whose degree shall be updated.
     *  @param[in] degree           The new degree of the given vertex.
     *  @param[in] pool             The pool of vertices with minimum degree.
     *  @param[in,out] minDegree    A reference to a variable representing the minimum degree. This information is updated if degree < minDegree.
     */
    static void updatePool(htd::vertex_t vertex, std::size_t degree, std::unordered_set<htd::vertex_t> & pool, std::size_t & minDegree);

    /**
     *  Structure representing the pre-processed input for the algorithm.
     *
     *  The pre-processing step consists of replacing the vertex identifiers by indices starting at 0 so that vectors
     *  instead of maps can be used for efficiently accessing information. Additionally, the pool of vertices with
     *  minimum degree is initialized.
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

                        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

                        auto position = neighborCollection.begin();

                        currentNeighborhood.reserve(neighborCollection.size() + 1);

                        for (std::size_t remainder = neighborCollection.size(); remainder > 0; --remainder)
                        {
                            currentNeighborhood.push_back((*position) - 1);

                            ++position;
                        }

                        auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), mappedVertex);

                        if (position2 == currentNeighborhood.end() || *position2 != mappedVertex)
                        {
                            currentNeighborhood.insert(position2, mappedVertex);
                        }
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

                        if (position3 == currentNeighborhood.end() || *position3 != mappedVertex)
                        {
                            currentNeighborhood.insert(position3, mappedVertex);
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
         *  @param[in] graph                The input graph which shall be pre-processed.
         */
        PreparedInput(const htd::LibraryInstance & managementInstance, const htd::IMultiHypergraph & graph) : minDegree((std::size_t)-1), vertexNames(), pool(), neighborhood()
        {
            HTD_UNUSED(managementInstance)

            std::size_t size = graph.vertexCount();

            vertexNames.reserve(size);

            neighborhood.resize(size);

            initialize(graph, vertexNames, neighborhood);

            for (htd::vertex_t vertex = 0; vertex < size; ++vertex)
            {
                updatePool(vertex, neighborhood[vertex].size(), pool, minDegree);
            }
        }

        ~PreparedInput()
        {

        }

        /**
         *  The minimum degree of all vertices.
         */
        std::size_t minDegree;

        /**
         *  The actual identifiers of the vertices.
         */
        std::vector<htd::vertex_t> vertexNames;

        /**
         *  The pool of vertices with minimum degree.
         */
        std::unordered_set<htd::vertex_t> pool;

        /**
         *  A vector containing the neighborhood of each of the vertices.
         */
        std::vector<std::vector<htd::vertex_t>> neighborhood;
    };

    /**
     *  Compute the vertex ordering of a given graph and write it to the end of a given vector.
     *
     *  @param[in] input                The pre-processed input data for which the vertex ordering shall be computed.
     *  @param[out] target              The target vector to which the computed ordering shall be appended.
     *  @param[in] maxBagSize           The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
     *
     *  @return The maximum bag size of the decomposition which is obtained via bucket elimination using the input graph and the resulting ordering.
     */
    std::size_t writeOrderingTo(const PreparedInput & input, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT;
};

htd::MinDegreeOrderingAlgorithm::MinDegreeOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::MinDegreeOrderingAlgorithm::~MinDegreeOrderingAlgorithm()
{
    
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    return computeOrdering(graph, (std::size_t)-1, 1);
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT
{
    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(graph.vertexCount());

    htd::MinDegreeOrderingAlgorithm::Implementation::PreparedInput input(managementInstance, graph);

    std::size_t iterations = 0;

    std::size_t currentMaxBagSize = (std::size_t)-1;

    do
    {
        ordering.clear();

        currentMaxBagSize = implementation_->writeOrderingTo(input, ordering, maxBagSize);

        ++iterations;
    }
    while (currentMaxBagSize > maxBagSize && iterations < maxIterationCount && !managementInstance.isTerminated());

    if (maxIterationCount == 0 && currentMaxBagSize > maxBagSize)
    {
        ordering.clear();
    }

    return new htd::VertexOrdering(std::move(ordering), iterations);
}

std::size_t htd::MinDegreeOrderingAlgorithm::Implementation::writeOrderingTo(const PreparedInput & input, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    std::size_t size = input.vertexNames.size();

    std::size_t minDegree = input.minDegree;

    std::unordered_set<htd::vertex_t> pool(input.pool.begin(), input.pool.end());

    std::unordered_set<htd::vertex_t> vertices(size);

    for (htd::vertex_t vertex = 0; vertex < size; ++vertex)
    {
        vertices.insert(vertex);
    }

    std::vector<htd::vertex_t> vertexNames(input.vertexNames.begin(), input.vertexNames.end());

    std::vector<std::vector<htd::vertex_t>> neighborhood(input.neighborhood.begin(), input.neighborhood.end());

    std::vector<htd::vertex_t> newNeighborhood;

    std::vector<htd::vertex_t> difference;

    while (size > 0 && ret <= maxBagSize && !managementInstance_->isTerminated())
    {
        if (pool.empty())
        {
            minDegree = (std::size_t)-1;
    
            for (htd::vertex_t vertex : vertices)
            {
                updatePool(vertex, neighborhood[vertex].size(), pool, minDegree);
            }
        }

        DEBUGGING_CODE_LEVEL2(
        std::cout << "POOL (DEGREE=" << min << "): ";
        htd::print(pool, false);
        std::cout << std::endl;
        )

        htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

        auto & selectedNeighborhood = neighborhood[selectedVertex];

        if (selectedNeighborhood.size() > ret)
        {
            ret = selectedNeighborhood.size();
        }

        pool.erase(selectedVertex);
        
        if (selectedNeighborhood.size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    auto & currentNeighborhood = neighborhood[neighbor];

                    htd::set_difference(selectedNeighborhood, currentNeighborhood, difference);
                    
                    if (!difference.empty())
                    {
                        if (difference.size() == 1)
                        {
                            auto first = currentNeighborhood.begin();
                            auto last = currentNeighborhood.end();

                            htd::vertex_t newVertex = difference[0];

                            if (newVertex < selectedVertex)
                            {
                                if (selectedVertex - newVertex == 1)
                                {
                                    *std::lower_bound(first, last, selectedVertex) = newVertex;
                                }
                                else
                                {
                                    auto position = std::lower_bound(first, last, selectedVertex);

                                    // coverity[use_iterator]
                                    position = currentNeighborhood.erase(position);

                                    currentNeighborhood.insert(std::lower_bound(first, position, newVertex), newVertex);
                                }
                            }
                            else
                            {
                                if (newVertex - selectedVertex == 1)
                                {
                                    *std::lower_bound(first, last, selectedVertex) = newVertex;
                                }
                                else
                                {
                                    auto position = std::lower_bound(first, last, selectedVertex);

                                    // coverity[use_iterator]
                                    position = currentNeighborhood.erase(position);

                                    currentNeighborhood.insert(std::lower_bound(position, currentNeighborhood.end(), newVertex), newVertex);
                                }
                            }
                        }
                        else
                        {
                            htd::set_union(currentNeighborhood, difference, selectedVertex, newNeighborhood);

                            std::swap(currentNeighborhood, newNeighborhood);

                            newNeighborhood.clear();

                            if (currentNeighborhood.size() - 1 > minDegree)
                            {
                                pool.erase(neighbor);
                            }
                        }

                        difference.clear();
                    }
                    else
                    {
                        currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));

                        updatePool(neighbor, currentNeighborhood.size(), pool, minDegree);
                    }
                }
            }
        }
        
        selectedNeighborhood.clear();
        
        vertices.erase(selectedVertex);

        size--;

        target.push_back(vertexNames[selectedVertex]);
    }

    return ret;
}

const htd::LibraryInstance * htd::MinDegreeOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MinDegreeOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MinDegreeOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::clone(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}

htd::IWidthLimitableOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::cloneWidthLimitableOrderingAlgorithm(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

void htd::MinDegreeOrderingAlgorithm::Implementation::updatePool(htd::vertex_t vertex, std::size_t degree, std::unordered_set<htd::vertex_t> & pool, std::size_t & minDegree)
{
    if (degree <= minDegree)
    {
        if (degree < minDegree)
        {
            minDegree = degree;

            pool.clear();
        }

        pool.insert(vertex);
    }
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP */
