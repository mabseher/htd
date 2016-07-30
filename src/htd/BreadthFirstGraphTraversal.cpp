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

/**
 *  Private implementation details of class htd::BreadthFirstGraphTraversal.
 */
struct htd::BreadthFirstGraphTraversal::Implementation
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

htd::BreadthFirstGraphTraversal::BreadthFirstGraphTraversal(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
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

            const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(currentVertex);

            std::size_t neighborCount = graph.neighborCount(currentVertex);

            auto it = neighborCollection.begin();

            for (htd::index_t index = 0; index < neighborCount; ++index)
            {
                htd::vertex_t neighbor = *it;

                if (visitedVertices.count(neighbor) == 0)
                {
                    originDeque.push_back(std::make_tuple(neighbor, currentVertex, currentDistance + 1));
                }

                ++it;
            }
        }

        originDeque.pop_front();
    }
}

#endif /* HTD_HTD_BREADTHFIRSTGRAPHTRAVERSAL_CPP */
