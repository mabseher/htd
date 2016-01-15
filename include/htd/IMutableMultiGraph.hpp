/* 
 * File:   IMutableMultiGraph.hpp
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

#ifndef HTD_HTD_IMUTABLEMULTIGRAPH_HPP
#define	HTD_HTD_IMUTABLEMULTIGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiGraph.hpp>

namespace htd
{
    class IMutableMultiGraph : public virtual htd::IMultiGraph
    {
        public:
            virtual ~IMutableMultiGraph() = 0;

            virtual htd::vertex_t addVertex(void) = 0;

            virtual htd::ConstCollection<htd::vertex_t> addVertices(std::size_t count) = 0;

            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;
            
            virtual htd::id_t addEdge(const htd::edge_t & edge) = 0;
            
            virtual void removeEdge(htd::id_t edgeId) = 0;

            virtual IMutableMultiGraph * clone(void) const = 0;

            virtual IMutableMultiGraph & operator=(const htd::IMultiGraph & original) = 0;
    };

    inline htd::IMutableMultiGraph::~IMutableMultiGraph() { }
}

#endif /* HTD_HTD_IMUTABLEMULTIGRAPH_HPP */
