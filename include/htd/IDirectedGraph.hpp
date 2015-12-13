/* 
 * File:   IDirectedGraph.hpp
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

#ifndef HTD_HTD_IDIRECTEDGRAPH_HPP
#define	HTD_HTD_IDIRECTEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>

namespace htd
{
    class IDirectedGraph : public virtual htd::IGraph
    {
        public:
            virtual ~IDirectedGraph() = 0;

            virtual std::size_t incomingNeighborCount(htd::vertex_t vertex) const = 0;

            virtual const htd::Collection<htd::vertex_t> incomingNeighbors(htd::vertex_t vertex) const = 0;

            virtual htd::vertex_t incomingNeighbor(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual bool isIncomingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

            virtual std::size_t outgoingNeighborCount(htd::vertex_t vertex) const = 0;

            virtual const htd::Collection<htd::vertex_t> outgoingNeighbors(htd::vertex_t vertex) const = 0;

            virtual htd::vertex_t outgoingNeighbor(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual bool isOutgoingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

            virtual bool isReachable(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual IDirectedGraph * clone(void) const = 0;
    };

    inline htd::IDirectedGraph::~IDirectedGraph() { }
}

#endif /* HTD_HTD_IDIRECTEDGRAPH_HPP */
