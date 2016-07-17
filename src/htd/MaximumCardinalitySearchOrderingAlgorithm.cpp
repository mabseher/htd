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
#include <htd/Helpers.hpp>
#include <htd/MaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

htd::MaximumCardinalitySearchOrderingAlgorithm::MaximumCardinalitySearchOrderingAlgorithm(void) : htd::LibraryObject()
{
    
}
            
htd::MaximumCardinalitySearchOrderingAlgorithm::~MaximumCardinalitySearchOrderingAlgorithm()
{
    
}

htd::ConstCollection<htd::vertex_t> htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    writeOrderingTo(graph, ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::MaximumCardinalitySearchOrderingAlgorithm::writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const
{
    std::size_t size = graph.vertexCount();

    std::size_t minDegree = (std::size_t)-1;

    std::unordered_set<htd::vertex_t> pool(size);

    std::unordered_set<htd::vertex_t> vertices(graph.vertices().begin(), graph.vertices().end());

    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> neighborhood(size);

    std::unordered_map<htd::vertex_t, std::size_t> weights(size);

    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex];

        graph.copyNeighborsTo(currentNeighborhood, vertex);

        weights[vertex] = 0;

        std::size_t tmp = currentNeighborhood.size();

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

    while (size > 0 && !isTerminated())
    {
        if (pool.size() == 0)
        {
            std::size_t maxCardinality = 0;

            for (htd::vertex_t vertex : vertices)
            {
                std::size_t tmp = weights.at(vertex);

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

        /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
        // coverity[dont_call]
        std::advance(it, std::rand() % pool.size());

        htd::vertex_t selectedVertex = *it;

        auto & selectedNeighborhood = neighborhood.at(selectedVertex);

        pool.erase(selectedVertex);

        if (selectedNeighborhood.size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    if (vertices.count(neighbor) == 1)
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

        target.push_back(selectedVertex);
    }
}

htd::MaximumCardinalitySearchOrderingAlgorithm * htd::MaximumCardinalitySearchOrderingAlgorithm::clone(void) const
{
    return new htd::MaximumCardinalitySearchOrderingAlgorithm();
}

#endif /* HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP */
