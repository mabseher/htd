/* 
 * File:   MinFillOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MINFILLORDERINGALGORITHM_CPP
#define	HTD_HTD_MINFILLORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

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
     *  Compute the number of edges between a set of vertices.
     *
     *  @param[in] availableNeighborhoods   The neighborhoods of the provided vertices.
     *  @param[in] vertices                 The vertices for which the number of edges shall be returned.
     *
     *  @return The number of edges between the provided vertices.
     */
    std::size_t computeEdgeCount(const std::vector<std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices) const HTD_NOEXCEPT;
};

htd::MinFillOrderingAlgorithm::MinFillOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}

htd::MinFillOrderingAlgorithm::~MinFillOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::MinFillOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::VectorAdapter<htd::vertex_t> ret;

    writeOrderingTo(graph, ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t registerVertex(htd::vertex_t vertex, std::unordered_map<htd::vertex_t, htd::vertex_t> & mapping, std::vector<htd::vertex_t> & reverseMapping)
{
    auto result = mapping.emplace(vertex, reverseMapping.size());

    if (result.second)
    {
        reverseMapping.push_back(vertex);
    }

    return result.first->second;
}

void initialize(const htd::IMultiHypergraph & graph,
                std::unordered_set<htd::vertex_t> & vertices,
                std::vector<std::vector<htd::vertex_t>> & neighborhood,
                std::vector<htd::vertex_t> & vertexNames)
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

                vertices.insert(mappedVertex);

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

                vertices.insert(mappedVertex);

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

void updatePool(htd::vertex_t vertex, std::size_t fillValue, std::unordered_set<htd::vertex_t> & pool, std::size_t & minFill /*, std::size_t & minDegree, const std::vector<std::vector<htd::vertex_t>> & neighborhood*/)
{
    if (fillValue <= minFill)
    {
        //std::size_t currentVertexDegree = neighborhood[vertex].size() - 1;

        if (fillValue < minFill)
        {
            minFill = fillValue;

            //minDegree = currentVertexDegree;

            pool.clear();
        }

        /*
        if (currentVertexDegree <= minDegree)
        {
            if (currentVertexDegree < minDegree)
            {
                minDegree = currentVertexDegree;

                pool.clear();
            }

            pool.insert(vertex);
        }
        */

        pool.insert(vertex);
    }
}

void htd::MinFillOrderingAlgorithm::writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_NOEXCEPT
{
    std::size_t size = graph.vertexCount();

    std::size_t minFill = (std::size_t)-1;
    //std::size_t minDegree = (std::size_t)-1;

    std::unordered_set<htd::vertex_t> pool;

    std::unordered_set<htd::vertex_t> vertices(size);

    std::vector<htd::vertex_t> vertexNames;
    vertexNames.reserve(size);

    std::vector<htd::state_t> updateStatus(size, 0);

    std::vector<std::size_t> fillValue(size, 0);
    
    std::vector<std::vector<htd::vertex_t>> neighborhood(size);

    std::vector<std::vector<htd::vertex_t>> existingNeighbors(size);
    std::vector<std::vector<htd::vertex_t>> additionalNeighbors(size);
    std::vector<std::vector<htd::vertex_t>> unaffectedNeighbors(size);

    std::vector<htd::vertex_t> affectedVertices;
    affectedVertices.reserve(size);

    std::size_t totalFill = 0;

    initialize(graph, vertices, neighborhood, vertexNames);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = vertices.begin(); it != vertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];
        
        std::size_t currentFillValue = ((currentNeighborhood.size() * (currentNeighborhood.size() - 1)) / 2) - implementation_->computeEdgeCount(neighborhood, currentNeighborhood);

        updatePool(vertex, currentFillValue, pool, minFill/*, minDegree, neighborhood*/);

        fillValue[vertex] = currentFillValue;

        DEBUGGING_CODE_LEVEL2(
        std::cout << "Vertex " << vertex << ":" << std::endl;
        htd::print(currentNeighborhood, std::cout, false);
        std::cout << std::endl;
        std::size_t neighborhoodSize = currentNeighborhood.size();
        std::cout << "   INITIAL EDGE COUNT " << vertex << ": " << computeEdgeCount(neighborhood, neighborhood[vertex]) << std::endl;
        std::cout << "   MAXIMUM EDGE COUNT " << vertex << ": " << (neighborhoodSize * (neighborhoodSize - 1)) / 2 << std::endl;
        std::cout << "   INITIAL FILL VALUE " << vertex << ": " << requiredFillAmount[vertex] << std::endl;
        )

        totalFill += currentFillValue;
    }
    
    while (totalFill > 0 && !managementInstance.isTerminated())
    {
        if (pool.empty())
        {
            minFill = (std::size_t)-1;

            //minDegree = (std::size_t)-1;

            for (htd::vertex_t vertex : vertices)
            {
                updatePool(vertex, fillValue[vertex], pool, minFill/*, minDegree, neighborhood*/);
            }
        }

        htd::vertex_t selectedVertex = selectRandomElement<htd::vertex_t>(pool);

        std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood[selectedVertex];

        pool.erase(selectedVertex);

        updateStatus[selectedVertex] = 4;
        
        affectedVertices.clear();

        totalFill -= minFill;

        if (fillValue[selectedVertex] == 0)
        {
            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                if (vertex != selectedVertex)
                {
                    std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

                    std::size_t fillReduction = htd::set_difference_size(currentNeighborhood.begin(), currentNeighborhood.end(), selectedNeighborhood.begin(), selectedNeighborhood.end());

                    fillValue[vertex] -= fillReduction;

                    totalFill -= fillReduction;

                    /* Because 'vertex' is a neighbor of 'selectedVertex', std::lower_bound will always find 'selectedVertex' in 'currentNeighborhood'. */
                    // coverity[use_iterator]
                    currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));
                }
            }
        }
        else
        {
            selectedNeighborhood.erase(std::lower_bound(selectedNeighborhood.begin(), selectedNeighborhood.end(), selectedVertex));

            for (htd::vertex_t neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
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
                        htd::state_t currentUpdateStatus = updateStatus[affectedVertex];

                        if (currentUpdateStatus < 2)
                        {
                            if (currentUpdateStatus == 0)
                            {
                                std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[affectedVertex];

                                auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex);

                                if (position != currentNeighborhood.end() && *position == selectedVertex)
                                {
                                    currentNeighborhood.erase(position);
                                }

                                htd::decompose_sets(selectedNeighborhood, currentNeighborhood,
                                                    additionalNeighbors[affectedVertex],
                                                    unaffectedNeighbors[affectedVertex],
                                                    existingNeighbors[affectedVertex]);
                            }

                            affectedVertices.push_back(affectedVertex);
                            
                            updateStatus[affectedVertex] |= 2;
                        }
                    }
                }
            }

            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                if (vertex != selectedVertex)
                {
                    std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];
                    std::vector<htd::vertex_t> & currentUnaffectedNeighborhood = unaffectedNeighbors[vertex];
                    std::vector<htd::vertex_t> & currentAdditionalNeighborhood = additionalNeighbors[vertex];

                    std::size_t additionalNeighborCount = currentAdditionalNeighborhood.size();

                    if (additionalNeighborCount > 0)
                    {
                        if (additionalNeighborCount == 1)
                        {
                            htd::vertex_t newVertex = currentAdditionalNeighborhood[0];

                            currentNeighborhood.insert(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), newVertex), newVertex);
                        }
                        else
                        {
                            std::size_t middle = currentNeighborhood.size();

                            std::copy(currentAdditionalNeighborhood.begin(), currentAdditionalNeighborhood.end(), std::back_inserter(currentNeighborhood));

                            std::inplace_merge(currentNeighborhood.begin(),
                                               currentNeighborhood.begin() + middle,
                                               currentNeighborhood.end());
                        }
                    }

                    std::size_t tmp = fillValue[vertex];

                    if (additionalNeighborCount > 0 || tmp > 0)
                    {
                        std::size_t unaffectedNeighborCount = currentUnaffectedNeighborhood.size();

                        if (unaffectedNeighborCount > 0)
                        {
                            if (additionalNeighborCount == 0)
                            {
                                std::vector<htd::vertex_t> & relevantNeighborhood = existingNeighbors[vertex];

                                std::size_t remainder = relevantNeighborhood.size();
    
                                for (auto it = relevantNeighborhood.begin(); remainder > 0 && tmp > unaffectedNeighborCount; --remainder)
                                {
                                    htd::vertex_t vertex2 = *it;

                                    std::vector<htd::vertex_t> & currentAdditionalNeighborhood2 = additionalNeighbors[vertex2];

                                    ++it;

                                    std::size_t fillReduction = htd::set_intersection_size(it, relevantNeighborhood.end(), std::upper_bound(currentAdditionalNeighborhood2.begin(), currentAdditionalNeighborhood2.end(), vertex2), currentAdditionalNeighborhood2.end());

                                    tmp -= fillReduction;

                                    totalFill -= fillReduction;
                                }

                                tmp -= unaffectedNeighborCount;

                                totalFill -= unaffectedNeighborCount;

                                //TODO
                                updateStatus[vertex] = 0;

                                updatePool(vertex, tmp, pool, minFill/*, minDegree, neighborhood*/);
                            }
                            else
                            {
                                std::size_t fillIncrease = 0;

                                for (htd::vertex_t unaffectedVertex : currentUnaffectedNeighborhood)
                                {
                                    const std::vector<htd::vertex_t> & affectedVertices = existingNeighbors[unaffectedVertex];

                                    fillIncrease += htd::set_difference_size(currentAdditionalNeighborhood.begin(),
                                                                             currentAdditionalNeighborhood.end(),
                                                                             affectedVertices.begin(),
                                                                             affectedVertices.end()) - 1;
                                }

                                if (fillIncrease > 0)
                                {
                                    pool.erase(vertex);

                                    tmp += fillIncrease;

                                    totalFill += fillIncrease;
                                }

                                updateStatus[vertex] &= ~1;

                                if (updateStatus[vertex] == 0)
                                {
                                    updatePool(vertex, tmp, pool, minFill/*, minDegree, neighborhood*/);
                                }
                            }
                        }
                        else
                        {
                            totalFill -= tmp;

                            tmp = 0;

                            //TODO
                            updateStatus[vertex] = 0;

                            updatePool(vertex, tmp, pool, minFill/*, minDegree, neighborhood*/);
                        }

                        fillValue[vertex] = tmp;
                    }
                    else
                    {
                        updateStatus[vertex] = 0;
                    }
                }
            }

            for (htd::vertex_t vertex : affectedVertices)
            {
                if (updateStatus[vertex] == 2)
                {
                    std::size_t tmp = fillValue[vertex];

                    if (unaffectedNeighbors[vertex].size() > 0 && tmp > 0)
                    {
                        std::vector<htd::vertex_t> & relevantNeighborhood = existingNeighbors[vertex];

                        auto last = relevantNeighborhood.end();

                        for (auto it = relevantNeighborhood.begin(); it != last && tmp > 0;)
                        {
                            htd::vertex_t vertex2 = *it;

                            std::vector<htd::vertex_t> & currentAdditionalNeighborhood2 = additionalNeighbors[vertex2];

                            ++it;

                            std::size_t fillReduction = htd::set_intersection_size(it, last, std::upper_bound(currentAdditionalNeighborhood2.begin(), currentAdditionalNeighborhood2.end(), vertex2), currentAdditionalNeighborhood2.end());

                            tmp -= fillReduction;

                            totalFill -= fillReduction;
                        }

                        updatePool(vertex, tmp, pool, minFill/*, minDegree, neighborhood*/);
                    }
                    else
                    {
                        totalFill -= tmp;

                        tmp = 0;

                        updatePool(vertex, tmp, pool, minFill/*, minDegree, neighborhood*/);
                    }

                    fillValue[vertex] = tmp;
                }
            }

            for (htd::vertex_t vertex : selectedNeighborhood)
            {
                additionalNeighbors[vertex].clear();
                unaffectedNeighbors[vertex].clear();
                existingNeighbors[vertex].clear();
            }

            for (htd::vertex_t vertex : affectedVertices)
            {
                if (updateStatus[vertex] == 2)
                {
                    additionalNeighbors[vertex].clear();
                    unaffectedNeighbors[vertex].clear();
                    existingNeighbors[vertex].clear();

                    updateStatus[vertex] = 0;
                }
            }
        }

        selectedNeighborhood.clear();
        
        vertices.erase(selectedVertex);

        target.push_back(vertexNames[selectedVertex]);

        size--;

//#define VERIFY
#ifdef VERIFY
        std::cout << "CHECK (ELIMINATED=" << selectedVertex << ", FILL=" << requiredFillAmount[selectedVertex] << "): " << std::endl;
        
        std::size_t minFill2 = (std::size_t)-1;

        std::size_t totalFill2 = 0;

        for (htd::vertex_t vertex : vertices)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

            std::size_t neighborCount = currentNeighborhood.size();

            long actual = requiredFillAmount[vertex];

            long maximumEdges = (neighborCount * (neighborCount - 1)) / 2;
            long existingEdges = computeEdgeCount(neighborhood, currentNeighborhood);

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

            if (actual < minFill2 && !pool.empty())
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

        for (htd::vertex_t vertex : pool)
        {
            std::cout << "POOL VERTEX: " << vertex << "   " << requiredFillAmount[vertex] << std::endl;
        }

        std::cout << "TOTAL FILL: " << totalFill << std::endl;

        std::cout << std::endl << std::endl;
#endif
    }

    while (size > 0)
    {
        htd::vertex_t vertex = htd::selectRandomElement<htd::vertex_t>(vertices);

        target.push_back(vertexNames[vertex]);

        vertices.erase(vertex);

        --size;
    }

    DEBUGGING_CODE_LEVEL2(std::cout << std::endl;)
}

std::size_t htd::MinFillOrderingAlgorithm::Implementation::computeEdgeCount(const std::vector<std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices) const HTD_NOEXCEPT
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

#endif /* HTD_HTD_MINFILLORDERINGALGORITHM_CPP */
