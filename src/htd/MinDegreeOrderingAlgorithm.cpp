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
#define	HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

htd::MinDegreeOrderingAlgorithm::MinDegreeOrderingAlgorithm(void) : htd::LibraryObject()
{
    
}
            
htd::MinDegreeOrderingAlgorithm::~MinDegreeOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    writeOrderingTo(graph, ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::MinDegreeOrderingAlgorithm::writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const
{
    std::size_t size = graph.vertexCount();

    std::size_t minDegree = (std::size_t)-1;
    
    std::unordered_set<htd::vertex_t> pool(size);

    std::unordered_set<htd::vertex_t> vertices(graph.vertices().begin(), graph.vertices().end());

    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> neighborhood(size);

    std::vector<htd::vertex_t> newNeighborhood;

    std::vector<htd::vertex_t> difference;

    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex];

        graph.copyNeighborsTo(currentNeighborhood, vertex);

        auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);
        
        if (position == currentNeighborhood.end() || *position != vertex)
        {
            currentNeighborhood.insert(position, vertex);
        }

        std::size_t tmp = currentNeighborhood.size() - 1;

        if (tmp <= minDegree)
        {
            if (tmp < minDegree)
            {
                minDegree = tmp;

                pool.clear();
            }

            pool.insert(vertex);
        }

        DEBUGGING_CODE_LEVEL2(
        std::cout << "Vertex " << vertex << ":" << std::endl;
        htd::print(currentNeighborhood, false);
        std::cout << std::endl;
        std::cout << "   INITIAL DEGREE " << vertex << ": " << (currentNeighborhood.size() - 1) << std::endl;
        )
    }
    
    while (size > 0 && !isTerminated())
    {
        if (pool.size() == 0)
        {
            minDegree = (std::size_t)-1;
    
            for (htd::vertex_t vertex : vertices)
            {
                std::size_t tmp = neighborhood.at(vertex).size() - 1;

                if (tmp <= minDegree)
                {
                    if (tmp < minDegree)
                    {
                        minDegree = tmp;

                        pool.clear();
                    }

                    pool.insert(vertex);
                } 
            }
        }

        DEBUGGING_CODE_LEVEL2(
        std::cout << "POOL (DEGREE=" << min << "): ";
        htd::print(pool, false);
        std::cout << std::endl;
        )

        htd::vertex_t selectedVertex = selectRandomElement<htd::vertex_t>(pool);

        auto & selectedNeighborhood = neighborhood[selectedVertex];
        
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
                    }
                }
            }
        }
        
        selectedNeighborhood.clear();
        
        vertices.erase(selectedVertex);
        
        size--;

        target.push_back(selectedVertex);
    }
}

htd::MinDegreeOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::clone(void) const
{
    htd::MinDegreeOrderingAlgorithm * ret = new htd::MinDegreeOrderingAlgorithm();

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP */
