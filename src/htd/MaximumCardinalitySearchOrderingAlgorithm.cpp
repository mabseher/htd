/* 
 * File:   MaximumCardinalitySearchOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP
#define	HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/MaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

//TODO Remove!
#include <iostream>

htd::MaximumCardinalitySearchOrderingAlgorithm::MaximumCardinalitySearchOrderingAlgorithm(void)
{
    
}
            
htd::MaximumCardinalitySearchOrderingAlgorithm::~MaximumCardinalitySearchOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    std::vector<htd::vertex_t> & ordering = ret.container();

    std::size_t size = graph.vertexCount();

    std::size_t tmp = 0;

    std::size_t maxCardinality = 0;

    std::unordered_set<htd::vertex_t> selected(size);

    std::unordered_set<htd::vertex_t> vertices(graph.vertices().begin(), graph.vertices().end());

    std::unordered_map<htd::vertex_t, htd::vertex_container> neighborhood(size);

    std::unordered_map<htd::vertex_t, std::size_t> weights(size);

    std::unordered_set<htd::vertex_t> pool(vertices);

    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex];

        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

        currentNeighborhood.reserve(neighborCollection.size());

        std::copy(neighborCollection.begin(), neighborCollection.end(), std::back_inserter(currentNeighborhood));

        weights[vertex] = 0;
    }

    while (size > 0)
    {
        if (pool.size() == 0)
        {
            maxCardinality = 0;

            for (htd::vertex_t vertex : vertices)
            {
                tmp = weights.at(vertex);

                if (tmp >= maxCardinality)
                {
                    if (tmp > maxCardinality)
                    {
                        maxCardinality = tmp;

                        pool.clear();
                    }

                    pool.insert(vertex);
                }
            }
        }

        auto it = pool.begin();

        std::advance(it, rand() % pool.size());

        htd::vertex_t selectedVertex = *it;

        auto & selectedNeighborhood = neighborhood.at(selectedVertex);

        pool.erase(selectedVertex);

        selected.insert(selectedVertex);

        if (selectedNeighborhood.size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    if (selected.count(neighbor) == 0)
                    {
                        weights[neighbor] += 1;

                        pool.erase(neighbor);
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

htd::MaximumCardinalitySearchOrderingAlgorithm * htd::MaximumCardinalitySearchOrderingAlgorithm::clone(void) const
{
    return new htd::MaximumCardinalitySearchOrderingAlgorithm();
}

#endif /* HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP */
