/*
 * File:   DepthFirstGraphTraversal.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP
#define	HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/DepthFirstGraphTraversal.hpp>

#include <stack>
#include <tuple>
#include <stdexcept>
#include <unordered_set>

htd::DepthFirstGraphTraversal::DepthFirstGraphTraversal(void)
{

}

htd::DepthFirstGraphTraversal::~DepthFirstGraphTraversal()
{

}

void htd::DepthFirstGraphTraversal::traverse(const htd::IHypergraph & graph, htd::vertex_t startingVertex, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    if (!graph.isVertex(startingVertex))
    {
        throw std::logic_error("void htd::DepthFirstGraphTraversal::traverse(const htd::IHypergraph &, htd::vertex_t, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const");
    }

    std::stack<std::tuple<htd::vertex_t, htd::vertex_t, std::size_t>> originStack;

    std::unordered_set<htd::vertex_t> visitedVertices;

    std::size_t currentDistance = 0;
    htd::vertex_t currentVertex = startingVertex;

    originStack.push(std::make_tuple(currentVertex, htd::Vertex::UNKNOWN, currentDistance));

    while (!originStack.empty())
    {
        currentVertex = std::get<0>(originStack.top());

        if (visitedVertices.count(currentVertex) == 0)
        {
            currentDistance = std::get<2>(originStack.top());

            targetFunction(currentVertex, std::get<1>(originStack.top()), currentDistance);

            visitedVertices.insert(currentVertex);

            originStack.pop();

            for (htd::vertex_t neighbor : graph.neighbors(currentVertex))
            {
                if (visitedVertices.count(neighbor) == 0)
                {
                    originStack.push(std::make_tuple(neighbor, currentVertex, currentDistance + 1));
                }
            }
        }
        else
        {
            originStack.pop();
        }
    }
}

#endif /* HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP */
