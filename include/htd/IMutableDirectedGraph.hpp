/* 
 * File:   IMutableDirectedGraph.hpp
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

#ifndef HTD_HTD_IMUTABLEDIRECTEDGRAPH_HPP
#define	HTD_HTD_IMUTABLEDIRECTEDGRAPH_HPP

#include <htd/IDirectedGraph.hpp>
#include <htd/IDirectedMultiGraph.hpp>

namespace htd
{
    class IMutableDirectedGraph : public virtual htd::IDirectedGraph
    {
        public:
            /**
             *  Destructor for an IMutableDirectedGraph object.
             */
            virtual ~IMutableDirectedGraph() = 0;

            /**
             *  Add a new vertex to the directed graph.
             *
             *  @return The ID of the new vertex.
             */
            virtual htd::vertex_t addVertex(void) = 0;

            virtual htd::ConstCollection<htd::vertex_t> addVertices(std::size_t count) = 0;

            /**
             *  Remove a vertex from the directed graph.
             *
             *  @param[in] vertex   The ID of the vertex which should be removed.
             */
            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void removeEdge(htd::id_t edgeId) = 0;

            virtual void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Create a deep copy the current mutable directed graph.
             *
             *  @return A new IMutableDirectedGraph object identical to the current mutable directed graph.
             */
            virtual IMutableDirectedGraph * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable directed graph.
             *
             *  @param[in] original  The original directed graph.
             */
            virtual IMutableDirectedGraph & operator=(const htd::IDirectedGraph & original) = 0;

            /**
             *  Copy assignment operator for a mutable directed graph.
             *
             *  @param[in] original  The original directed multi-graph.
             */
            virtual IMutableDirectedGraph & operator=(const htd::IDirectedMultiGraph & original) = 0;
    };

    inline htd::IMutableDirectedGraph::~IMutableDirectedGraph() { }
}

#endif /* HTD_HTD_IMUTABLEDIRECTEDGRAPH_HPP */
