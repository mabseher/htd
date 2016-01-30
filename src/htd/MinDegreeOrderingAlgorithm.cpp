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

htd::MinDegreeOrderingAlgorithm::MinDegreeOrderingAlgorithm(void)
{
    
}
            
htd::MinDegreeOrderingAlgorithm::~MinDegreeOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    std::vector<htd::vertex_t> & ordering = ret.container();

    std::size_t size = graph.vertexCount();

    std::size_t tmp = 0;

    std::size_t minDegree = (std::size_t)-1;
    
    std::unordered_set<htd::vertex_t> pool(size);

    std::unordered_set<htd::vertex_t> vertices(graph.vertices().begin(), graph.vertices().end());

    std::unordered_map<htd::vertex_t, htd::vertex_container> neighborhood(size);

    htd::vertex_container newNeighborhood;
    htd::vertex_container difference;

    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex];

        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

        currentNeighborhood.reserve(neighborCollection.size());

        std::copy(neighborCollection.begin(), neighborCollection.end(), std::back_inserter(currentNeighborhood));

        auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);
        
        if (position == currentNeighborhood.end() || *position != vertex)
        {
            currentNeighborhood.insert(position, vertex);
        }

        tmp = currentNeighborhood.size() - 1;

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
    
    while (size > 0)
    {
        if (pool.size() == 0)
        {
            minDegree = (std::size_t)-1;
    
            for (htd::vertex_t vertex : vertices)
            {
                tmp = neighborhood.at(vertex).size() - 1;

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

        auto it = pool.begin();

        std::advance(it, rand() % pool.size());

        htd::vertex_t selectedVertex = *it;

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
                                    htd::index_t position1 = std::distance(first, std::lower_bound(first, last, newVertex));
                                    htd::index_t position2 = std::distance(first, std::lower_bound(first + position1, last, selectedVertex));

                                    currentNeighborhood.erase(first + position2);
                                    currentNeighborhood.insert(currentNeighborhood.begin() + position1, newVertex);
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
                                    htd::index_t position1 = std::distance(first, std::lower_bound(first, last, selectedVertex));
                                    htd::index_t position2 = std::distance(first, std::lower_bound(first + position1, last, newVertex));

                                    currentNeighborhood.erase(first + position1);
                                    currentNeighborhood.insert(currentNeighborhood.begin() + position2 - 1, newVertex);
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

        ordering.push_back(selectedVertex);
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::MinDegreeOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::clone(void) const
{
    return new htd::MinDegreeOrderingAlgorithm();
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP */
