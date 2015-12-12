/* 
 * File:   MinDegreeOrderingAlgorithm.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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
#include <htd/IHypergraph.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>

#include <cstdlib>
#include <set>
#include <vector>
#include <stdexcept>

//TODO Remove
#include <iostream>

htd::MinDegreeOrderingAlgorithm::MinDegreeOrderingAlgorithm(void)
{
    
}
            
htd::MinDegreeOrderingAlgorithm::~MinDegreeOrderingAlgorithm()
{
    
}

void htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IHypergraph & graph, std::vector<htd::vertex_t>& result) const
{
    std::size_t size = graph.vertexCount();

    std::size_t tmp = 0;

    std::size_t minDegree = (std::size_t)-1;
    
    std::unordered_set<htd::vertex_t> pool(size);

    std::vector<htd::vertex_t> vertices;
    vertices.reserve(size);

    std::copy(graph.vertices().begin(), graph.vertices().end(), std::back_inserter(vertices));

    std::vector<htd::vertex_container> neighborhood(size, htd::vertex_container());

    htd::vertex_container newNeighborhood;
    
    htd::vertex_container affectedVertices;
    affectedVertices.reserve(size);
    
    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex - htd::Vertex::FIRST];
        
        currentNeighborhood.reserve(graph.neighborCount(vertex));
        
        graph.getNeighbors(vertex, currentNeighborhood);
        
        auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);
        
        if (position == currentNeighborhood.end() || *position != vertex)
        {
            currentNeighborhood.insert(position, vertex);
        }
    }
    
    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex - htd::Vertex::FIRST];
        
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
        std::size_t neighborhoodSize = currentNeighborhood.size();
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
                tmp = neighborhood[vertex - htd::Vertex::FIRST].size() - 1;

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
        
        //TODO
        std::vector<htd::vertex_t> minDegreePool(pool.begin(), pool.end());
        std::sort(minDegreePool.begin(), minDegreePool.end());
        
        htd::vertex_t selectedVertex = minDegreePool[rand() % minDegreePool.size()];
        auto & selectedNeighborhood = neighborhood[selectedVertex - htd::Vertex::FIRST];
        
        pool.erase(pool.find(selectedVertex));
        
        affectedVertices.clear();
        
        if (neighborhood[selectedVertex - htd::Vertex::FIRST].size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    auto & currentNeighborhood = neighborhood[neighbor - htd::Vertex::FIRST];
                    
                    set_union(currentNeighborhood, selectedNeighborhood, selectedVertex, newNeighborhood);

                    std::swap(currentNeighborhood, newNeighborhood);

                    newNeighborhood.clear();
                    
                    if (currentNeighborhood.size() - 1 > minDegree)
                    {
                        auto position = pool.find(neighbor);
                        
                        if (position != pool.end())
                        {
                            pool.erase(position);
                        }
                    }
                }
            }
        }
        
        selectedNeighborhood.clear();
        
        vertices.erase(std::lower_bound(vertices.begin(), vertices.end(), selectedVertex));
        
        size--;

        result.push_back(selectedVertex);
    }
}

//TODO Refactor
void htd::MinDegreeOrderingAlgorithm::set_union(const std::vector<htd::vertex_t> & set1,
                                                const std::vector<htd::vertex_t> & set2,
                                                htd::vertex_t ignoredVertex,
                                                std::vector<htd::vertex_t> & result) const
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();
    auto last1 = set1.end();
    auto last2 = set2.end();
    
    std::size_t count1 = set1.size();
    std::size_t count2 = set2.size();

    htd::index_t index1 = 0;
    htd::index_t index2 = 0;
    
    while (index1 < count1 && index2 < count2)
    {
        auto value1 = *first1;
        auto value2 = *first2;

        if (value1 < value2) 
        {
            if (value1 != ignoredVertex) 
            {
                result.push_back(value1);
            }

            index1++;
            ++first1;
        }
        else if (value2 < value1) 
        {
            if (value2 != ignoredVertex) 
            {
                result.push_back(value2);
            }

            index2++;
            ++first2; 
        }
        else 
        {
            if (value1 != ignoredVertex) 
            {
                result.push_back(value1);
            }

            index1++;
            ++first1;

            //Skip common value in set 2.
            index2++;
            ++first2;
        }
    }

    if (index1 < count1)
    {
        if (*first1 <= ignoredVertex)
        {
            std::copy_if(first1, last1, std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first1, last1, std::back_inserter(result));
        }
    }
    else if (index2 < count2)
    {
        if (*first2 <= ignoredVertex)
        {
            std::copy_if(first2, last2, std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first2, last2, std::back_inserter(result));
        }
    }
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP */
