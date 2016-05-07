/* 
 * File:   IMultiHypergraph.hpp
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

#ifndef HTD_HTD_IMULTIHYPERGRAPH_HPP
#define	HTD_HTD_IMULTIHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/FilteredHyperedgeCollection.hpp>
#include <htd/Hyperedge.hpp>

#include <cstdlib>
#include <vector>

namespace htd
{
    class IMultiHypergraph
    {
        public:
            virtual ~IMultiHypergraph() = 0;

            virtual std::size_t vertexCount(void) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> vertices(void) const = 0;
            
            virtual htd::vertex_t vertexAtPosition(htd::index_t index) const = 0;

            virtual bool isVertex(htd::vertex_t vertex) const = 0;

            virtual bool isEdge(htd::id_t edgeId) const = 0;

            virtual bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual bool isEdge(const std::vector<htd::vertex_t> & elements) const = 0;

            virtual bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const = 0;

            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const = 0;

            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const = 0;

            virtual std::size_t isolatedVertexCount(void) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const = 0;

            virtual htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const = 0;

            virtual bool isIsolatedVertex(htd::vertex_t vertex) const = 0;

            virtual std::size_t neighborCount(htd::vertex_t vertex) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const = 0;

            virtual void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const = 0;

            virtual htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual std::size_t edgeCount(void) const = 0;

            virtual htd::ConstCollection<htd::Hyperedge> hyperedges(void) const = 0;

            virtual const htd::Hyperedge & hyperedge(htd::id_t edgeId) const = 0;

            virtual const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const = 0;

            virtual htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const = 0;

            virtual htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const = 0;

            virtual std::size_t edgeCount(htd::vertex_t vertex) const = 0;

            virtual htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const = 0;

            virtual const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const = 0;

            virtual bool isConnected(void) const = 0;

            virtual bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            virtual bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

            /**
             *  Create a deep copy the current multi-hypergraph.
             *
             *  @return A new IMultiHypergraph object identical to the current multi-hypergraph.
             */
            virtual IMultiHypergraph * clone(void) const = 0;
    };

    inline htd::IMultiHypergraph::~IMultiHypergraph() { }
}

#endif /* HTD_HTD_IMULTIHYPERGRAPH_HPP */
