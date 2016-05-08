/* 
 * File:   IMutableGraph.hpp
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

#ifndef HTD_HTD_IMUTABLEGRAPH_HPP
#define	HTD_HTD_IMUTABLEGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/IMultiGraph.hpp>

namespace htd
{
    class IMutableGraph : public virtual htd::IGraph
    {
        public:
            /**
             *  Destructor for an IMutableGraph object.
             */
            virtual ~IMutableGraph() = 0;

            /**
             *  Add a new vertex to the graph.
             *
             *  @return The ID of the new vertex.
             */
            virtual htd::vertex_t addVertex(void) = 0;

            virtual htd::ConstCollection<htd::vertex_t> addVertices(std::size_t count) = 0;

            /**
             *  Remove a vertex from the graph.
             *
             *  @param[in] vertex   The ID of the vertex which should be removed.
             */
            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void removeEdge(htd::id_t edgeId) = 0;

            virtual void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Create a deep copy the current mutable graph.
             *
             *  @return A new IMutableGraph object identical to the current mutable graph.
             */
            virtual IMutableGraph * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable graph.
             *
             *  @param[in] original  The original graph.
             */
            virtual IMutableGraph & operator=(const htd::IGraph & original) = 0;

            /**
             *  Copy assignment operator for a mutable graph.
             *
             *  @param[in] original  The original multi-graph.
             */
            virtual IMutableGraph & operator=(const htd::IMultiGraph & original) = 0;
    };

    inline htd::IMutableGraph::~IMutableGraph() { }
}

#endif /* HTD_HTD_IMUTABLEGRAPH_HPP */
