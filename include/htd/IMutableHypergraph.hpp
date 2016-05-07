/* 
 * File:   IMutableHypergraph.hpp
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

#ifndef HTD_HTD_IMUTABLEHYPERGRAPH_HPP
#define	HTD_HTD_IMUTABLEHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>

namespace htd
{
    class IMutableHypergraph : public virtual htd::IHypergraph
    {
        public:
            virtual ~IMutableHypergraph() = 0;

            virtual htd::vertex_t addVertex(void) = 0;

            virtual htd::ConstCollection<htd::vertex_t> addVertices(std::size_t count) = 0;

            virtual void removeVertex(htd::vertex_t vertex) = 0;

            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual htd::id_t addEdge(const std::vector<htd::vertex_t> & elements) = 0;

            virtual htd::id_t addEdge(std::vector<htd::vertex_t> && elements) = 0;

            virtual htd::id_t addEdge(const htd::ConstCollection<htd::vertex_t> & elements) = 0;

            virtual htd::id_t addEdge(const htd::Hyperedge & hyperedge) = 0;

            virtual htd::id_t addEdge(htd::Hyperedge && hyperedge) = 0;

            virtual void removeEdge(htd::id_t edgeId) = 0;

            virtual void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void removeEdge(const std::vector<htd::vertex_t> & elements) = 0;

            virtual void removeEdge(const htd::ConstCollection<htd::vertex_t> & elements) = 0;

            virtual void removeEdge(const htd::Hyperedge & hyperedge) = 0;

            /**
             *  Create a deep copy the current mutable hypergraph.
             *
             *  @return A new IMutableHypergraph object identical to the current mutable hypergraph.
             */
            virtual IMutableHypergraph * clone(void) const = 0;

            virtual IMutableHypergraph & operator=(const htd::IHypergraph & original) = 0;

            virtual IMutableHypergraph & operator=(const htd::IMultiHypergraph & original) = 0;
    };

    inline htd::IMutableHypergraph::~IMutableHypergraph() { }
}

#endif /* HTD_HTD_IMUTABLEHYPERGRAPH_HPP */
