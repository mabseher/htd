/* 
 * File:   Graph.hpp
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

#ifndef HTD_HTD_GRAPH_HPP
#define	HTD_HTD_GRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableGraph.hpp>

#include <unordered_set>
#include <vector>

namespace htd
{
    class Graph : public IMutableGraph
    {
        public:
            Graph(void);

            Graph(size_t size);
            
            ~Graph();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            htd::vertex_t vertex(htd::index_t index) const HTD_OVERRIDE;
            
            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;
            
            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;
            
            void getNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const HTD_OVERRIDE;
            
            htd::vertex_t neighbor(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertex(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            void getEdges(htd::edge_container & output) const HTD_OVERRIDE;

            void getEdges(htd::edge_container & output, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::edge_t & edge(htd::index_t index) const HTD_OVERRIDE;

            const htd::edge_t & edge(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::hyperedge_t> hyperedges(void) const HTD_OVERRIDE;

            const htd::Collection<htd::hyperedge_t> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::hyperedge_t & hyperedge(htd::index_t index) const HTD_OVERRIDE;

            const htd::hyperedge_t & hyperedge(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t addVertex(void) HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;
            
            void removeVertex(htd::vertex_t vertex, bool addNeighborClique) HTD_OVERRIDE;
            
            void addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;
            
            void addEdge(const htd::edge_t & edge) HTD_OVERRIDE;
            
            void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;
            
            void removeEdge(const htd::edge_t & edge) HTD_OVERRIDE;

            Graph * clone(void) const HTD_OVERRIDE;

        protected:
            Graph & operator=(const Graph &) { return *this; }

        private:
            std::size_t size_;

            htd::vertex_t next_vertex_;

            htd::vertex_container vertices_;

            std::unordered_set<htd::vertex_t> deletions_;

            std::vector<htd::vertex_container> neighborhood_;
    };
}

#endif /* HTD_HTD_GRAPH_HPP */
