/*
 * File:   MinFillOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MINFILLORDERINGALGORITHM_CPP
#define HTD_HTD_MINFILLORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/OrderingAlgorithmPreprocessor.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::AdvancedMinFillOrderingAlgorithm.
 */
struct htd::MinFillOrderingAlgorithm::Implementation
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
     *  Update the pool of vertices with minimum fill value.
     *
     *  @param[in] vertex           The vertex whose fill value shall be updated.
     *  @param[in] fillValue        The new fill value of the given vertex.
     *  @param[in] pool             The pool of vertices with minimum fill value.
     *  @param[in,out] minFill    A reference to a variable representing the minimum fill value. This information is updated if fillValue < minFill.
     */
    static void updatePool(htd::vertex_t vertex, std::size_t fillValue, std::unordered_set<htd::vertex_t> & pool, std::size_t & minFill);

    /**
     *  Structure representing the pre-processed input for the algorithm.
     *
     *  The pre-processing step consists of replacing the vertex identifiers by indices starting at 0 so that vectors
     *  instead of maps can be used for efficiently accessing information. Additionally, the initial fill value for
     *  each vertex is computed and the pool of vertices with minimum fill value is initialized.
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
         *  Compute the number of edges between a set of vertices.
         *
         *  @param[in] availableNeighborhoods   The neighborhoods of the provided vertices.
         *  @param[in] vertices                 The vertices for which the number of edges shall be returned.
         *
         *  @return The number of edges between the provided vertices.
         */
        std::size_t computeEdgeCount(const std::vector<std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices)
        {
            std::size_t ret = 0;

            std::size_t remainder = vertices.size();

            for (auto it = vertices.begin(); remainder > 0; --remainder)
            {
                htd::vertex_t vertex = *it;

                const std::vector<htd::vertex_t> & currentNeighborhood = availableNeighborhoods[vertex];

                ++it;

                ret += htd::set_intersection_size(it, vertices.end(), std::upper_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex), currentNeighborhood.end());
            }

            return ret;
        }

        /**
         *  Contructor for the PreparedInput data structure.
         *
         *  @param[in] managementInstance   The management instance to which the new algorithm belongs.
         *  @param[in] preparedInput        The input graph in pre-processed format.
         */
        PreparedInput(const htd::LibraryInstance & managementInstance, const htd::PreparedOrderingAlgorithmInput & preparedInput) : minFill((std::size_t)-1), totalFill(0), fillValue(), pool()
        {
            HTD_UNUSED(managementInstance)

            std::size_t size = preparedInput.vertexCount();

            fillValue.resize(size, 0);

            for (htd::vertex_t vertex : preparedInput.remainingVertices())
            {
                const std::vector<htd::vertex_t> & currentNeighborhood = preparedInput.neighborhood(vertex);

                std::size_t currentFillValue = ((currentNeighborhood.size() * (currentNeighborhood.size() - 1)) / 2) - computeEdgeCount(preparedInput.neighborhood(), currentNeighborhood);

                updatePool(vertex, currentFillValue, pool, minFill);

                fillValue[vertex] = currentFillValue;

                totalFill += currentFillValue;
            }
        }

        ~PreparedInput()
        {

        }

        /**
         *  The minimum fill value of all vertices.
         */
        std::size_t minFill;

        /**
         *  The total sum of the fill value of all vertices.
         */
        std::size_t totalFill;

        /**
         *  A vector containing the fill value for each vertex.
         */
        std::vector<std::size_t> fillValue;

        /**
         *  The pool of vertices with minimum fill value.
         */
        std::unordered_set<htd::vertex_t> pool;
    };

    /**
     *  Compute the vertex ordering of a given graph and write it to the end of a given vector.
     *
     *  @param[in] preparedInput        The input graph in pre-processed format.
     *  @param[in] input                The pre-processed, algorithm-specific input data.
     *  @param[out] target              The target vector to which the computed ordering shall be appended.
     *  @param[in] maxBagSize           The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
     *
     *  @return The maximum bag size of the decomposition which is obtained via bucket elimination using the input graph and the resulting ordering.
     */
    std::size_t writeOrderingTo(const htd::PreparedOrderingAlgorithmInput & preparedInput, const PreparedInput & input, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT;
};

htd::MinFillOrderingAlgorithm::MinFillOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::MinFillOrderingAlgorithm::~MinFillOrderingAlgorithm()
{

}

htd::VertexOrdering * htd::MinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    return computeOrdering(graph, (std::size_t)-1, 1);
}

htd::VertexOrdering * htd::MinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT
{
    htd::OrderingAlgorithmPreprocessor preprocessor(implementation_->managementInstance_);

    htd::PreparedOrderingAlgorithmInput * preparedInput = preprocessor.prepare(graph, false);

    htd::VertexOrdering * ret = computeOrdering(graph, *preparedInput, maxBagSize, maxIterationCount);

    delete preparedInput;

    return ret;
}

htd::VertexOrdering * htd::MinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::PreparedOrderingAlgorithmInput & preparedInput) const HTD_NOEXCEPT
{
    return computeOrdering(graph, preparedInput, (std::size_t)-1, 1);
}

htd::VertexOrdering * htd::MinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::PreparedOrderingAlgorithmInput & preparedInput, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT
{
    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(graph.vertexCount());

    htd::MinFillOrderingAlgorithm::Implementation::PreparedInput input(managementInstance, preparedInput);

    std::size_t iterations = 0;

    std::size_t currentMaxBagSize = (std::size_t)-1;

    do
    {
        ordering.clear();

        currentMaxBagSize = implementation_->writeOrderingTo(preparedInput, input, ordering, maxBagSize);

        ++iterations;
    }
    while (currentMaxBagSize > maxBagSize && iterations < maxIterationCount && !managementInstance.isTerminated());

    if (maxIterationCount == 0 && currentMaxBagSize > maxBagSize)
    {
        ordering.clear();
    }

    return new htd::VertexOrdering(std::move(ordering), iterations);
}

std::size_t htd::MinFillOrderingAlgorithm::Implementation::writeOrderingTo(const htd::PreparedOrderingAlgorithmInput & preparedInput, const PreparedInput & input, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    std::size_t size = preparedInput.vertexCount();

    std::size_t minFill = input.minFill;

    std::unordered_set<htd::vertex_t> pool(input.pool.begin(), input.pool.end());

    std::unordered_set<htd::vertex_t> vertices(size);

    htd::fillSet(preparedInput.remainingVertices(), vertices);

    std::vector<std::size_t> fillValue(input.fillValue.begin(), input.fillValue.end());

    std::vector<std::vector<htd::vertex_t>> neighborhood(preparedInput.neighborhood().begin(), preparedInput.neighborhood().end());

    std::size_t totalFill = input.totalFill;

    std::vector<htd::state_t> updateStatus(size, 0);

    std::vector<std::vector<htd::vertex_t>> existingNeighbors(size);
    std::vector<std::vector<htd::vertex_t>> additionalNeighbors(size);
    std::vector<std::vector<htd::vertex_t>> unaffectedNeighbors(size);

    std::vector<htd::vertex_t> affectedVertices;
    affectedVertices.reserve(size);

    target.insert(target.end(),
                  preparedInput.preprocessedEliminationOrdering().begin(),
                  preparedInput.preprocessedEliminationOrdering().end());

    ret = preparedInput.minTreeWidth() + 1;

    size = preparedInput.remainingVertices().size();

    for (htd::vertex_t vertex : vertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        currentNeighborhood.insert(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex), vertex);
    }

    while (totalFill > 0 && ret <= maxBagSize && !managementInstance_->isTerminated())
    {
        if (pool.empty())
        {
            minFill = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                updatePool(vertex, fillValue[vertex], pool, minFill);
            }
        }

        htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

        std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood[selectedVertex];

        if (selectedNeighborhood.size() > ret)
        {
            ret = selectedNeighborhood.size();
        }

        pool.erase(selectedVertex);

        vertices.erase(selectedVertex);

        affectedVertices.clear();

        totalFill -= minFill;

        if (pool.empty())
        {
            minFill = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                updatePool(vertex, fillValue[vertex], pool, minFill);
            }
        }

        selectedNeighborhood.erase(std::lower_bound(selectedNeighborhood.begin(), selectedNeighborhood.end(), selectedVertex));

        if (fillValue[selectedVertex] == 0)
        {
            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

                /* Because 'vertex' is a neighbor of 'selectedVertex', std::lower_bound will always find 'selectedVertex' in 'currentNeighborhood'. */
                // coverity[use_iterator]
                currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));

                std::size_t tmp = fillValue[vertex];

                if (tmp > 0)
                {
                    std::size_t fillReduction = htd::set_difference_size(currentNeighborhood.begin(), currentNeighborhood.end(),
                                                                         selectedNeighborhood.begin(), selectedNeighborhood.end());

                    if (fillReduction > 0)
                    {
                        tmp -= fillReduction;

                        totalFill -= fillReduction;

                        fillValue[vertex] = tmp;

                        updatePool(vertex, tmp, pool, minFill);
                    }
                }
            }
        }
        else
        {
            for (htd::vertex_t neighbor : selectedNeighborhood)
            {
                if (updateStatus[neighbor] == 0)
                {
                    std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[neighbor];

                    currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));

                    htd::decompose_sets(selectedNeighborhood, currentNeighborhood,
                                        additionalNeighbors[neighbor],
                                        unaffectedNeighbors[neighbor],
                                        existingNeighbors[neighbor]);
                }

                updateStatus[neighbor] |= 1;

                for (htd::vertex_t affectedVertex : neighborhood[neighbor])
                {
                    htd::state_t & currentUpdateStatus = updateStatus[affectedVertex];

                    if (currentUpdateStatus < 2)
                    {
                        if (currentUpdateStatus == 0)
                        {
                            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[affectedVertex];

                            auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex);

                            if (position != currentNeighborhood.end() && *position == selectedVertex)
                            {
                                currentNeighborhood.erase(position);

                                htd::decompose_sets(selectedNeighborhood, currentNeighborhood,
                                                    additionalNeighbors[affectedVertex],
                                                    unaffectedNeighbors[affectedVertex],
                                                    existingNeighbors[affectedVertex]);
                            }
                            else
                            {
                                std::set_intersection(selectedNeighborhood.begin(), selectedNeighborhood.end(),
                                                      currentNeighborhood.begin(), currentNeighborhood.end(),
                                                      std::back_inserter(existingNeighbors[affectedVertex]));

                                affectedVertices.push_back(affectedVertex);
                            }
                        }

                        currentUpdateStatus |= 2;
                    }
                }
            }

            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                std::vector<htd::vertex_t> & currentExistingNeighborhood = existingNeighbors[vertex];
                std::vector<htd::vertex_t> & currentAdditionalNeighborhood = additionalNeighbors[vertex];
                std::vector<htd::vertex_t> & currentUnaffectedNeighborhood = unaffectedNeighbors[vertex];

                std::size_t additionalNeighborCount = currentAdditionalNeighborhood.size();
                std::size_t unaffectedNeighborCount = currentUnaffectedNeighborhood.size();

                if (additionalNeighborCount > 0)
                {
                    std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

                    if (additionalNeighborCount <= 8)
                    {
                        auto it = currentNeighborhood.begin();

                        for (htd::vertex_t newNeighbor : currentAdditionalNeighborhood)
                        {
                            it = currentNeighborhood.insert(std::lower_bound(it, currentNeighborhood.end(), newNeighbor), newNeighbor) + 1;
                        }
                    }
                    else
                    {
                        std::size_t middle = currentNeighborhood.size();

                        currentNeighborhood.insert(currentNeighborhood.end(), currentAdditionalNeighborhood.begin(), currentAdditionalNeighborhood.end());

                        std::inplace_merge(currentNeighborhood.begin(),
                                           currentNeighborhood.begin() + middle,
                                           currentNeighborhood.end());
                    }
                }

                std::size_t tmp = fillValue[vertex];

                if (unaffectedNeighborCount > 0)
                {
                    long fillUpdate = -(static_cast<long>(unaffectedNeighborCount));

                    if (additionalNeighborCount > 0)
                    {
                        for (htd::vertex_t additionalVertex : currentAdditionalNeighborhood)
                        {
                            const std::vector<htd::vertex_t> & affectedVertices2 = unaffectedNeighbors[additionalVertex];

                            fillUpdate += static_cast<long>(unaffectedNeighborCount);

                            fillUpdate -= static_cast<long>(htd::set_intersection_size(std::lower_bound(affectedVertices2.begin(),
                                                                                                        affectedVertices2.end(),
                                                                                                        currentUnaffectedNeighborhood[0]),
                                                                                       affectedVertices2.end(),
                                                                                       std::lower_bound(currentUnaffectedNeighborhood.begin(),
                                                                                                        currentUnaffectedNeighborhood.end(),
                                                                                                        affectedVertices2[0]),
                                                                                       currentUnaffectedNeighborhood.end()));
                        }
                    }

                    auto neighborhoodEnd = currentExistingNeighborhood.end();

                    for (auto it = currentExistingNeighborhood.begin(); it != neighborhoodEnd && tmp + fillUpdate > 0;)
                    {
                        const std::vector<htd::vertex_t> & currentAdditionalNeighborhood2 = additionalNeighbors[*it];

                        ++it;

                        if (!currentAdditionalNeighborhood2.empty() && it != neighborhoodEnd)
                        {
                            if (currentAdditionalNeighborhood2.size() == 1)
                            {
                                htd::vertex_t additionalNeighbor = currentAdditionalNeighborhood2[0];

                                auto position = std::lower_bound(it, neighborhoodEnd, additionalNeighbor);

                                if (position != neighborhoodEnd && *position == additionalNeighbor)
                                {
                                    --fillUpdate;
                                }
                            }
                            else
                            {
                                std::size_t fillReduction = htd::set_intersection_size(std::lower_bound(it,
                                                                                                        neighborhoodEnd,
                                                                                                        currentAdditionalNeighborhood2[0]),
                                                                                       neighborhoodEnd,
                                                                                       std::lower_bound(currentAdditionalNeighborhood2.begin(),
                                                                                                        currentAdditionalNeighborhood2.end(),
                                                                                                        *it),
                                                                                       currentAdditionalNeighborhood2.end());

                                fillUpdate -= static_cast<long>(fillReduction);
                            }
                        }
                    }

                    if (fillUpdate != 0)
                    {
                        tmp += fillUpdate;

                        totalFill += fillUpdate;

                        fillValue[vertex] = tmp;

                        if (fillUpdate > 0)
                        {
                            pool.erase(vertex);

                            if (pool.empty())
                            {
                                minFill = (std::size_t)-1;

                                for (htd::vertex_t vertex : vertices)
                                {
                                    updatePool(vertex, fillValue[vertex], pool, minFill);
                                }
                            }
                        }
                        else
                        {
                            updatePool(vertex, tmp, pool, minFill);
                        }
                    }
                }
                else
                {
                    totalFill -= tmp;

                    fillValue[vertex] = 0;

                    updatePool(vertex, 0, pool, minFill);
                }

                updateStatus[vertex] = 0;
            }

            for (htd::vertex_t vertex : affectedVertices)
            {
                const std::vector<htd::vertex_t> & relevantNeighborhood = existingNeighbors[vertex];

                if (relevantNeighborhood.size() > 1)
                {
                    std::size_t tmp = fillValue[vertex];

                    std::size_t fillReduction = 0;

                    auto neighborhoodEnd = relevantNeighborhood.end();

                    for (auto it = relevantNeighborhood.begin(); it != neighborhoodEnd && tmp - fillReduction > 0;)
                    {
                        const std::vector<htd::vertex_t> & currentAdditionalNeighborhood2 = additionalNeighbors[*it];

                        ++it;

                        if (!currentAdditionalNeighborhood2.empty() && it != neighborhoodEnd)
                        {
                            if (currentAdditionalNeighborhood2.size() == 1)
                            {
                                htd::vertex_t additionalNeighbor = currentAdditionalNeighborhood2[0];

                                auto position = std::lower_bound(it, neighborhoodEnd, additionalNeighbor);

                                if (position != neighborhoodEnd && *position == additionalNeighbor)
                                {
                                    ++fillReduction;
                                }
                            }
                            else
                            {
                                fillReduction += htd::set_intersection_size(std::lower_bound(it,
                                                                                             neighborhoodEnd,
                                                                                             currentAdditionalNeighborhood2[0]),
                                                                            neighborhoodEnd,
                                                                            std::lower_bound(currentAdditionalNeighborhood2.begin(),
                                                                                             currentAdditionalNeighborhood2.end(),
                                                                                             *it),
                                                                            currentAdditionalNeighborhood2.end());
                            }
                        }
                    }

                    if (fillReduction > 0)
                    {
                        tmp -= fillReduction;

                        totalFill -= fillReduction;

                        fillValue[vertex] = tmp;

                        updatePool(vertex, tmp, pool, minFill);
                    }
                }

                existingNeighbors[vertex].clear();

                updateStatus[vertex] = 0;
            }

            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                additionalNeighbors[vertex].clear();
                unaffectedNeighbors[vertex].clear();
                existingNeighbors[vertex].clear();
            }
        }

        std::vector<htd::vertex_t>().swap(selectedNeighborhood);
        std::vector<htd::vertex_t>().swap(additionalNeighbors[selectedVertex]);
        std::vector<htd::vertex_t>().swap(unaffectedNeighbors[selectedVertex]);
        std::vector<htd::vertex_t>().swap(existingNeighbors[selectedVertex]);

        target.push_back(preparedInput.vertexName(selectedVertex));

        --size;

        //std::cout << "ORDERING: " << selectedVertex << std::endl;

//#define VERIFY
#ifdef VERIFY
        std::cout << "CHECK (ELIMINATED=" << selectedVertex << ", FILL=" << fillValue[selectedVertex] << "): " << std::endl;

        std::size_t minFill2 = (std::size_t)-1;

        std::size_t totalFill2 = 0;

        for (htd::vertex_t vertex : vertices)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

            std::size_t neighborCount = currentNeighborhood.size();

            long actual = fillValue[vertex];

            long maximumEdges = (neighborCount * (neighborCount - 1)) / 2;
            long existingEdges = 0;

            std::size_t remainder = currentNeighborhood.size();

            for (auto it = currentNeighborhood.begin(); remainder > 0; --remainder)
            {
                htd::vertex_t vertex = *it;

                const std::vector<htd::vertex_t> & currentNeighborhood2 = neighborhood[vertex];

                ++it;

                existingEdges += htd::set_intersection_size(it, currentNeighborhood.end(), std::upper_bound(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex), currentNeighborhood2.end());
            }

            long expected = maximumEdges - existingEdges;

            if (actual != expected)
            {
                std::cout << "ERROR!!! Vertex " << vertex << " (Expected: " << expected << ", Actual: " << actual << ")" << std::endl;

                std::cout << "VERTEX " << vertex << ":" << std::endl;
                std::cout << "   NEIGHBORHOOD:   ";
                htd::print(currentNeighborhood, false);
                std::cout << std::endl;
                for (htd::vertex_t vertex2 : currentNeighborhood)
                {
                    if (vertex2 != vertex)
                    {
                        std::cout << "   NEIGHBORHOOD " << vertex2 << ": ";
                        htd::print(neighborhood[vertex2], false);
                        std::cout << std::endl;
                    }
                }
                std::cout << "EDGES " << vertex << ": " << existingEdges << "/" << maximumEdges << std::endl;

                std::exit(1);
            }

            if (((std::size_t)actual) < minFill2 && !pool.empty())
            {
                minFill2 = actual;
            }

            totalFill2 += expected;
        }

        if (minFill != minFill2 && !pool.empty())
        {
            std::cout << "ERROR: MIN FILL " << minFill << " != " << minFill2 << std::endl;

            std::exit(1);
        }

        if (totalFill != totalFill2)
        {
            std::cout << "ERROR: TOTAL FILL " << totalFill << " != " << totalFill2 << std::endl;

            std::exit(1);
        };

        /*
        for (htd::vertex_t vertex : pool)
        {
            std::cout << "POOL VERTEX: " << vertex << "   " << fillValue[vertex] << std::endl;
        }
        */

        std::cout << "TOTAL FILL: " << totalFill << std::endl;

        std::cout << std::endl << std::endl;
#endif
    }

    while (size > 0 && ret <= maxBagSize && !managementInstance_->isTerminated())
    {
        htd::vertex_t vertex = htd::selectRandomElement<htd::vertex_t>(vertices);

        std::size_t neighborhoodSize = neighborhood[vertex].size();

        if (neighborhoodSize > ret)
        {
            ret = neighborhoodSize;
        }

        target.push_back(preparedInput.vertexName(vertex));

        vertices.erase(vertex);

        --size;

        //std::cout << "ORDERING: " << vertexNames[vertex] << std::endl;
    }

    DEBUGGING_CODE_LEVEL2(std::cout << std::endl;)

    return ret;
}

const htd::LibraryInstance * htd::MinFillOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MinFillOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MinFillOrderingAlgorithm * htd::MinFillOrderingAlgorithm::clone(void) const
{
    return new htd::MinFillOrderingAlgorithm(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::MinFillOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::MinFillOrderingAlgorithm(implementation_->managementInstance_);
}

htd::IWidthLimitableOrderingAlgorithm * htd::MinFillOrderingAlgorithm::cloneWidthLimitableOrderingAlgorithm(void) const
{
    return new htd::MinFillOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

void htd::MinFillOrderingAlgorithm::Implementation::updatePool(htd::vertex_t vertex, std::size_t fillValue, std::unordered_set<htd::vertex_t> & pool, std::size_t & minFill)
{
    if (fillValue <= minFill)
    {
        if (fillValue < minFill)
        {
            minFill = fillValue;

            pool.clear();
        }

        pool.insert(vertex);
    }
}

#endif /* HTD_HTD_MINFILLORDERINGALGORITHM_CPP */
