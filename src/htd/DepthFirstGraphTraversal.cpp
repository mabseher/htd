/*
 * File:   DepthFirstGraphTraversal.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP
#define HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstGraphTraversal.hpp>

#include <stack>
#include <tuple>
#include <stdexcept>
#include <unordered_set>

/**
 *  Private implementation details of class htd::DepthFirstGraphTraversal.
 */
struct htd::DepthFirstGraphTraversal::Implementation
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
};

htd::DepthFirstGraphTraversal::DepthFirstGraphTraversal(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::DepthFirstGraphTraversal::~DepthFirstGraphTraversal()
{

}

void htd::DepthFirstGraphTraversal::traverse(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    HTD_ASSERT(graph.isVertex(startingVertex))

    std::deque<std::tuple<htd::vertex_t, htd::vertex_t, std::size_t>> originDeque;

    std::unordered_set<htd::vertex_t> visitedVertices;

    std::size_t currentDistance = 0;
    htd::vertex_t currentVertex = startingVertex;

    originDeque.emplace_back(currentVertex, htd::Vertex::UNKNOWN, currentDistance);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    while (!originDeque.empty() && !managementInstance.isTerminated())
    {
        currentVertex = std::get<0>(originDeque.front());

        if (visitedVertices.count(currentVertex) == 0)
        {
            currentDistance = std::get<2>(originDeque.front());

            targetFunction(currentVertex, std::get<1>(originDeque.front()), currentDistance);

            visitedVertices.insert(currentVertex);

            originDeque.pop_front();

            const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(currentVertex);

            auto it = neighborCollection.begin();

            for (std::size_t remainder = neighborCollection.size(); remainder > 0; --remainder)
            {
                htd::vertex_t neighbor = *it;

                if (visitedVertices.count(neighbor) == 0)
                {
                    originDeque.emplace_back(neighbor, currentVertex, currentDistance + 1);
                }

                ++it;
            }
        }
        else
        {
            originDeque.pop_front();
        }
    }
}

#endif /* HTD_HTD_DEPTHFIRSTGRAPHTRAVERSAL_CPP */
