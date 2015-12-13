/* 
 * File:   Hypergraph.hpp
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

#ifndef HTD_HTD_IHYPERGRAPH_HPP
#define	HTD_HTD_IHYPERGRAPH_HPP

#include <htd/Globals.hpp>

#include <htd/Collection.hpp>

#include <cstdlib>

namespace htd
{
    class IHypergraph
    {
        public:
            virtual ~IHypergraph() = 0;

            virtual std::size_t vertexCount(void) const = 0;

            virtual const htd::Collection<htd::vertex_t> vertices(void) const = 0;
            
            virtual htd::vertex_t vertex(htd::index_t index) const = 0;

            virtual bool isVertex(htd::vertex_t vertex) const = 0;

            virtual bool isEdge(const htd::hyperedge_t & edge) const = 0;

            virtual std::size_t isolatedVertexCount(void) const = 0;

            virtual void getIsolatedVertices(htd::vertex_container & output) const = 0;

            virtual htd::vertex_t isolatedVertex(htd::index_t index) const = 0;

            virtual bool isIsolatedVertex(htd::vertex_t vertex) const = 0;

            virtual std::size_t neighborCount(htd::vertex_t vertex) const = 0;

            virtual void getNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const = 0;

            virtual htd::vertex_t neighbor(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual std::size_t edgeCount(void) const = 0;

            virtual const htd::Collection<htd::hyperedge_t> hyperedges(void) const = 0;

            virtual const htd::hyperedge_t & hyperedge(htd::index_t index) const = 0;

            virtual std::size_t edgeCount(htd::vertex_t vertex) const = 0;

            virtual const htd::Collection<htd::hyperedge_t> hyperedges(htd::vertex_t vertex) const = 0;

            virtual const htd::hyperedge_t & hyperedge(htd::index_t index, htd::vertex_t vertex) const = 0;

            virtual bool isConnected(void) const = 0;

            virtual bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual bool isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual IHypergraph * clone(void) const = 0;
    };

    inline htd::IHypergraph::~IHypergraph() { }
}

#endif /* HTD_HTD_IHYPERGRAPH_HPP */
