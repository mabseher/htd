/* 
 * File:   IGraphTraversalAlgorithm.hpp
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

#ifndef HTD_HTD_IGRAPHTRAVERSAL_HPP
#define HTD_HTD_IGRAPHTRAVERSAL_HPP

#include <htd/Globals.hpp>

#include <htd/IGraphStructure.hpp>

#include <functional>

namespace htd
{
    /**
     * Interface for algorithms traversing a given input graph.
     */
    class IGraphTraversal
    {
        public:
            virtual ~IGraphTraversal() = 0;

            /**
             *  Traverse the given graph and call the provided function for each vertex.
             *
             *  @param[in] graph            The graph which shall be traversed.
             *  @param[in] startingVertex   The vertex from which the traversal will be started.
             *  @param[in] targetFunction   The function which will be called for each vertex found during the traversal. The parameters passed to the function are the following:
             *                                  -# The current vertex.
             *                                  -# The immediate predecessor of the current vertex in the traversal process.
             *                                  -# The distance between the current vertex and the starting vertex of the traversal.
             */
            virtual void traverse(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const = 0;
    };

    inline htd::IGraphTraversal::~IGraphTraversal() { }
}

#endif /* HTD_HTD_IGRAPHTRAVERSAL_HPP */
