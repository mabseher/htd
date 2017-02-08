/* 
 * File:   IDirectedMultiGraph.hpp
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

#ifndef HTD_HTD_IDIRECTEDMULTIGRAPH_HPP
#define HTD_HTD_IDIRECTEDMULTIGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiGraph.hpp>

namespace htd
{
    /**
     * Interface for classes which represent directed graphs with potentially duplicated edges.
     */
    class IDirectedMultiGraph : public virtual htd::IMultiGraph
    {
        public:
            virtual ~IDirectedMultiGraph() = 0;

            /**
             *  Getter for the number of neighbors having an outgoing edge to the given vertex.
             *
             *  @param[in] vertex   The vertex for which the number of incoming neighbors shall be computed.
             *
             *  @return The number of neighbors having an outgoing edge to the given vertex.
             */
            virtual std::size_t incomingNeighborCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all neighbors having an outgoing edge to the given vertex.
             *
             *  @param[in] vertex   The vertex for which the collection of incoming neighbors shall be returned.
             *
             *  @return The collection of all neighbors having an outgoing edge to the given vertex in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> incomingNeighbors(htd::vertex_t vertex) const = 0;

            /**
             *  Access the incoming neighbor at the specific position.
             *
             *  @param[in] vertex    The vertex for which the incoming neighbor shall be returned.
             *  @param[in] index     The position of the incoming neighbor.
             *
             *  @return The incoming neighbor of the given vertex at the specific position.
             */
            virtual htd::vertex_t incomingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Check whether there exists a directed edge from one vertex to another.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] neighbor The potential incoming neighbor.
             *
             *  @return True if there indeed exists a directed edge from the potential neighbor to the given vertex, false otherwise.
             */
            virtual bool isIncomingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

            /**
             *  Getter for the number of neighbors having an incoming edge from the given vertex.
             *
             *  @param[in] vertex   The vertex for which the number of outgoing neighbors shall be computed.
             *
             *  @return The number of neighbors having an incoming edge from the given vertex.
             */
            virtual std::size_t outgoingNeighborCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all neighbors having an incoming edge from the given vertex.
             *
             *  @param[in] vertex   The vertex for which the collection of outgoing neighbors shall be returned.
             *
             *  @return The collection of all neighbors having an incoming edge from the given vertex in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> outgoingNeighbors(htd::vertex_t vertex) const = 0;

            /**
             *  Access the outgoing neighbor at the specific position.
             *
             *  @param[in] vertex    The vertex for which the outgoing neighbor shall be returned.
             *  @param[in] index     The position of the outgoing neighbor.
             *
             *  @return The outgoing neighbor of the given vertex at the specific position.
             */
            virtual htd::vertex_t outgoingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Check whether there exists a directed edge from one vertex to another.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] neighbor The potential outgoing neighbor.
             *
             *  @return True if there indeed exists a directed edge from the given vertex to the potential neighbor, false otherwise.
             */
            virtual bool isOutgoingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const = 0;

            /**
             *  Check whether one vertex is reachable from another via a directed path.
             *
             *  @param[in] vertex1  The starting vertex.
             *  @param[in] vertex2  The target vertex.
             *
             *  @return True if the target vertex is reachable from the starting vertex via a directed path, false otherwise.
             */
            virtual bool isReachable(htd::vertex_t vertex1, htd::vertex_t vertex2) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current directed multi-graph.
             *
             *  @return A new IDirectedMultiGraph object identical to the current directed multi-graph.
             */
            virtual IDirectedMultiGraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current directed multi-graph.
             *
             *  @return A new IDirectedMultiGraph object identical to the current directed multi-graph.
             */
            virtual IDirectedMultiGraph * cloneDirectedMultiGraph(void) const = 0;
#endif
    };

    inline htd::IDirectedMultiGraph::~IDirectedMultiGraph() { }
}

#endif /* HTD_HTD_IDIRECTEDMULTIGRAPH_HPP */
