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

            /**
             *  Getter for the number of vertices in the graph.
             *
             *  @return The number of vertices in the graph.
             */
            virtual std::size_t vertexCount(void) const = 0;

            /**
             *  Access the collection of all vertices in the graph.
             *
             *  @return The collection of all vertices in the graph sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> vertices(void) const = 0;
            
            /**
             *  Access the vertex at the specific position.
             *
             *  @param[in] index     The position of the vertex.
             *
             *  @return The vertex at the specific position.
             */
            virtual htd::vertex_t vertexAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a given vertex is part of the graph.
             *
             *  @param[in] vertex   The vertex to test for existence.
             *
             *  @return True if the vertex is part of the graph, false otherwise.
             */
            virtual bool isVertex(htd::vertex_t vertex) const = 0;

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] edgeId   The ID of the edge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
            virtual bool isEdge(htd::id_t edgeId) const = 0;

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] vertex1  The first endpoint of the edge.
             *  @param[in] vertex2  The second endpoint of the edge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
            virtual bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
            virtual bool isEdge(const std::vector<htd::vertex_t> & elements) const = 0;

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
            virtual bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const = 0;

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] vertex1  The first endpoint of the edge.
             *  @param[in] vertex2  The second endpoint of the edge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const = 0;

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            virtual htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const = 0;

            /**
             *  Getter for the number of isolated vertices in the graph.
             *
             *  @return The number of isolated vertices in the graph.
             */
            virtual std::size_t isolatedVertexCount(void) const = 0;

            /**
             *  Access the collection of all isolated vertices in the graph.
             *
             *  @return The collection of all isolated vertices in the graph sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const = 0;

            /**
             *  Access the isolated vertex at the specific position.
             *
             *  @param[in] index     The position of the isolated vertex.
             *
             *  @return The isolated vertex at the specific position.
             */
            virtual htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a given vertex is isolated.
             *
             *  @param[in] vertex   The vertex to test for isolation.
             *
             *  @return True if the vertex has no neighbors in the graph, false otherwise.
             */
            virtual bool isIsolatedVertex(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of neighbors of a given vertex in the graph.
             *
             *  @param[in] vertex   The vertex for which the number of neighbors should be computed.
             *
             *  @return The number of neighbors of the given vertex in the graph.
             */
            virtual std::size_t neighborCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all neighbors of a given vertex in the graph.
             *
             *  @param[in] vertex   The vertex for which the collection of neighbors should be returned.
             *
             *  @return The collection of all neighbors of the given vertex in the graph in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const = 0;

            virtual void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const = 0;

            /**
             *  Access the neighbor at the specific position.
             *
             *  @param[in] vertex    The vertex for which the neighbor should be returned.
             *  @param[in] index     The position of the neighbor.
             *
             *  @return The neighbor of the given vertex at the specific position.
             */
            virtual htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Getter for the number of edges in the graph.
             *
             *  @return The number of edges in the graph.
             */
            virtual std::size_t edgeCount(void) const = 0;

            /**
             *  Access the collection of all hyperedges in the graph.
             *
             *  @return The collection of all hyperedges in the graph sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::Hyperedge> hyperedges(void) const = 0;

            /**
             *  Access the hyperedge with a specific ID.
             *
             *  @return The hyperedge with the specific ID.
             */
            virtual const htd::Hyperedge & hyperedge(htd::id_t edgeId) const = 0;

            /**
             *  Access the hyperedge at the specific position.
             *
             *  @param[in] index     The position of the hyperedge.
             *
             *  @return The hyperedge at the specific position.
             */
            virtual const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const = 0;

            /**
             *  Access the hyperedges at the specific positions.
             *
             *  @param[in] indices  The positions of the hyperedges.
             *
             *  @return A collection of the hyperedges at the specific positions.
             */
            virtual htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const = 0;

            /**
             *  Access the hyperedges at the specific positions.
             *
             *  @param[in] indices  The positions of the hyperedges.
             *
             *  @return A collection of the hyperedges at the specific positions.
             */
            virtual htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const = 0;

            /**
             *  Getter for the number of edges in the graph containing a specific vertex.
             *
             *  @param[in] vertex   The vertex which should be contained in the edges.
             *
             *  @return The number of edges in the graph containing the specific vertex.
             */
            virtual std::size_t edgeCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all hyperedges containing a specific vertex.
             *
             *  @param[in] vertex   The vertex which should be contained in the edges.
             *
             *  @return The collection of all hyperedges containing the specific vertex sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const = 0;

            /**
             *  Access the hyperedge at the specific position.
             *
             *  @param[in] index     The position of the hyperedge.
             *
             *  @return The hyperedge at the specific position.
             */
            virtual const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const = 0;

            /**
             *  Check whether the graph is connected.
             *
             *  @return True if the graph is connected, false otherwise.
             */
            virtual bool isConnected(void) const = 0;

            /**
             *  Check whether two vertices are contained in the same connected component.
             *
             *  @param[in] vertex1  The first vertex.
             *  @param[in] vertex2  The second vertex.
             *
             *  @return True if the two vertices are contained in the same connected component, false otherwise.
             */
            virtual bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

            /**
             *  Check whether two vertices are neighbors.
             *
             *  @param[in] vertex1  The first vertex.
             *  @param[in] vertex2  The second vertex.
             *
             *  @return True if the two vertices are neighbors, false otherwise.
             */
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
