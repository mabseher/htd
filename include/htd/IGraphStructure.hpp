/* 
 * File:   IGraphStructure.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_IGRAPHSTRUCTURE_HPP
#define HTD_HTD_IGRAPHSTRUCTURE_HPP

#include <htd/Globals.hpp>
#include <htd/ConstCollection.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for classes which represent a graph structure.
     */
    class IGraphStructure
    {
        public:
            virtual ~IGraphStructure() = 0;

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
             *  Write the collection of all vertices in the graph to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the vertices shall be appended.
             */
            virtual void copyVerticesTo(std::vector<htd::vertex_t> & target) const = 0;

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
             *  @param[in] index    The position of the isolated vertex.
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
             *  @param[in] vertex   The vertex for which the number of neighbors shall be computed.
             *
             *  @return The number of neighbors of the given vertex in the graph.
             */
            virtual std::size_t neighborCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all neighbors of a given vertex in the graph.
             *
             *  @param[in] vertex   The vertex for which the collection of neighbors shall be returned.
             *
             *  @return The collection of all neighbors of the given vertex in the graph in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const = 0;

            /**
             *  Write the collection of all neighbors of a given vertex to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the neighbors shall be appended.
             */
            virtual void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the neighbor at the specific position.
             *
             *  @param[in] vertex    The vertex for which the neighbor shall be returned.
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
             *  Getter for the number of edges in the graph containing a specific vertex.
             *
             *  @param[in] vertex   The vertex which shall be contained in the edges.
             *
             *  @return The number of edges in the graph containing the specific vertex.
             */
            virtual std::size_t edgeCount(htd::vertex_t vertex) const = 0;

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
             *  @param[in] vertex   The vertex.
             *  @param[in] neighbor The potential neighbor.
             *
             *  @return True if the two vertices are neighbors, false otherwise.
             */
            virtual bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current graph structure.
             *
             *  @return A new IGraphStructure object identical to the current graph structure.
             */
            virtual IGraphStructure * clone(void) const = 0;
#else
            /**
             *  Create a deep copy of the current graph structure.
             *
             *  @return A new IGraphStructure object identical to the current graph structure.
             */
            virtual IGraphStructure * cloneGraphStructure(void) const = 0;
#endif
    };

    inline htd::IGraphStructure::~IGraphStructure() { }
}

#endif /* HTD_HTD_IGRAPHSTRUCTURE_HPP */
