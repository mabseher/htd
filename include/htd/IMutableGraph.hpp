/* 
 * File:   IMutableGraph.hpp
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

#ifndef HTD_HTD_IMUTABLEGRAPH_HPP
#define	HTD_HTD_IMUTABLEGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>

namespace htd
{
    class IMutableGraph : public virtual htd::IGraph
    {
        public:
            virtual ~IMutableGraph() = 0;

            virtual htd::vertex_t addVertex(void) = 0;

            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;
            
            virtual htd::id_t addEdge(const htd::edge_t & edge) = 0;
            
            virtual void removeEdge(htd::id_t edgeId) = 0;

            virtual IMutableGraph * clone(void) const = 0;
    };

    inline htd::IMutableGraph::~IMutableGraph() { }
}

#endif /* HTD_HTD_IMUTABLEGRAPH_HPP */
