/*
 * File:   SingleNeighborVertexSelectionStrategy.cpp
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

#ifndef HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_CPP
#define HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_CPP

#include <htd/Globals.hpp>

#include <htd/SingleNeighborVertexSelectionStrategy.hpp>

#include <algorithm>
#include <random>

htd::SingleNeighborVertexSelectionStrategy::SingleNeighborVertexSelectionStrategy(void) : limit_((std::size_t)-1)
{

}

htd::SingleNeighborVertexSelectionStrategy::SingleNeighborVertexSelectionStrategy(std::size_t limit) : limit_(limit)
{

}

htd::SingleNeighborVertexSelectionStrategy::~SingleNeighborVertexSelectionStrategy()
{

}

void htd::SingleNeighborVertexSelectionStrategy::selectVertices(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const
{
    std::vector<htd::vertex_t> vertices;

    for (htd::vertex_t vertex : graph.vertices())
    {
        if (graph.neighborCount(vertex) == 1)
        {
            vertices.push_back(vertex);
        }
    }

    if (vertices.size() > limit_)
    {
        std::shuffle(vertices.begin(), vertices.end(), std::default_random_engine());

        vertices.erase(vertices.begin() + limit_, vertices.end());
    }

    target.insert(target.end(), vertices.begin(), vertices.end());
}

htd::SingleNeighborVertexSelectionStrategy * htd::SingleNeighborVertexSelectionStrategy::clone(void) const
{
    return new htd::SingleNeighborVertexSelectionStrategy();
}

#endif /* HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_CPP */
