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
#include <unordered_set>

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

    std::unordered_set<htd::vertex_t> pool(size);

    std::vector<std::size_t> weights(size, 0);

    std::vector<htd::vertex_t> vertices;
    vertices.reserve(size);

    std::copy(graph.vertices().begin(), graph.vertices().end(), std::back_inserter(vertices));

    std::vector<htd::vertex_container> neighborhood(size, htd::vertex_container());

    for (htd::vertex_t vertex : vertices)
    {
        auto & currentNeighborhood = neighborhood[vertex - htd::Vertex::FIRST];

        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(vertex);

        currentNeighborhood.reserve(neighborCollection.size());

        std::copy(neighborCollection.begin(), neighborCollection.end(), std::back_inserter(currentNeighborhood));

        pool.insert(vertex);
    }

    while (size > 0)
    {
        if (pool.size() == 0)
        {
            maxCardinality = 0;

            for (htd::vertex_t vertex : vertices)
            {
                tmp = weights[vertex - htd::Vertex::FIRST];

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

        auto & selectedNeighborhood = neighborhood[selectedVertex - htd::Vertex::FIRST];

        pool.erase(pool.find(selectedVertex));

        if (selectedNeighborhood.size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    weights[neighbor - htd::Vertex::FIRST] += 1;

                    auto position = pool.find(neighbor);

                    if (position != pool.end())
                    {
                        pool.erase(position);
                    }
                }
            }
        }

        selectedNeighborhood.clear();

        vertices.erase(std::lower_bound(vertices.begin(), vertices.end(), selectedVertex));

        size--;

        ordering.push_back(selectedVertex);
    }

    std::reverse(ordering.begin(), ordering.end());

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::MaximumCardinalitySearchOrderingAlgorithm * htd::MaximumCardinalitySearchOrderingAlgorithm::clone(void) const
{
    return new htd::MaximumCardinalitySearchOrderingAlgorithm();
}

#endif /* HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP */
