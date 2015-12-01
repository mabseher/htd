/* 
 * File:   IMutableHypergraph.hpp
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

#ifndef HTD_HTD_IMUTABLEHYPERGRAPH_HPP
#define	HTD_HTD_IMUTABLEHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>

namespace htd
{
    class IMutableHypergraph : public virtual IHypergraph
    {
        public:
            virtual htd::vertex_t addVertex(void) = 0;

            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual void removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge) = 0;
            
            virtual void addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;
            
            virtual void addEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end) = 0;
            
            virtual void addEdge(const htd::edge_t & edge) = 0;
            
            virtual void addEdge(const htd::hyperedge_t & edge) = 0;
            
            virtual void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;
            
            virtual void removeEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end) = 0;
            
            virtual void removeEdge(const htd::edge_t & edge) = 0;
            
            virtual void removeEdge(const htd::hyperedge_t & edge) = 0;
    };
}

#endif /* HTD_HTD_IMUTABLEHYPERGRAPH_HPP */
