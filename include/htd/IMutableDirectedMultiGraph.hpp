/* 
 * File:   IMutableDirectedMultiGraph.hpp
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

#ifndef HTD_HTD_IMUTABLEDIRECTEDMULTIGRAPH_HPP
#define	HTD_HTD_IMUTABLEDIRECTEDMULTIGRAPH_HPP

#include <htd/IDirectedMultiGraph.hpp>

namespace htd
{
    class IMutableDirectedMultiGraph : public virtual htd::IDirectedMultiGraph
    {
        public:
            virtual ~IMutableDirectedMultiGraph() = 0;

            virtual htd::vertex_t addVertex(void) = 0;

            virtual htd::ConstCollection<htd::vertex_t> addVertices(std::size_t count) = 0;

            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void removeEdge(htd::id_t edgeId) = 0;

            /**
             *  Create a deep copy the current mutable directed multi-graph.
             *
             *  @return A new IMutableDirectedMultiGraph object identical to the current mutable directed multi-graph.
             */
            virtual IMutableDirectedMultiGraph * clone(void) const = 0;

            virtual IMutableDirectedMultiGraph & operator=(const htd::IDirectedMultiGraph & original) = 0;
    };

    inline htd::IMutableDirectedMultiGraph::~IMutableDirectedMultiGraph() { }
}

#endif /* HTD_HTD_IMUTABLEDIRECTEDMULTIGRAPH_HPP */
