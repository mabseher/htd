/*
 * File:   BreadthFirstGraphTraversal.cpp
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

#ifndef HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_CPP
#define	HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BreadthFirstGraphTraversal.hpp>

#include <deque>
#include <tuple>
#include <stdexcept>
#include <unordered_set>

htd::BreadthFirstGraphTraversal::BreadthFirstGraphTraversal(void)
{

}

htd::BreadthFirstGraphTraversal::~BreadthFirstGraphTraversal()
{

}

void htd::BreadthFirstGraphTraversal::traverse(const htd::IMultiHypergraph & graph, htd::vertex_t startingVertex, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    HTD_ASSERT(graph.isVertex(startingVertex))

    std::deque<std::tuple<htd::vertex_t, htd::vertex_t, std::size_t>> originDeque;

    std::unordered_set<htd::vertex_t> visitedVertices;

    std::size_t currentDistance = 0;
    htd::vertex_t currentVertex = startingVertex;

    originDeque.push_back(std::make_tuple(currentVertex, htd::Vertex::UNKNOWN, currentDistance));

    while (!originDeque.empty())
    {
        currentVertex = std::get<0>(originDeque.front());

        if (visitedVertices.count(currentVertex) == 0)
        {
            currentDistance = std::get<2>(originDeque.front());

            targetFunction(currentVertex, std::get<1>(originDeque.front()), currentDistance);

            visitedVertices.insert(currentVertex);

            for (htd::vertex_t neighbor : graph.neighbors(currentVertex))
            {
                if (visitedVertices.count(neighbor) == 0)
                {
                    originDeque.push_back(std::make_tuple(neighbor, currentVertex, currentDistance + 1));
                }
            }
        }

        originDeque.pop_front();
    }
}

#endif /* HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_CPP */
