/* 
 * File:   IMutableHypergraph.hpp
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

#ifndef HTD_HTD_IMUTABLEHYPERGRAPH_HPP
#define HTD_HTD_IMUTABLEHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable hypergraphs.
     */
    class IMutableHypergraph : public virtual htd::IHypergraph
    {
        public:
            /**
             *  Destructor for an IMutableHypergraph object.
             */
            virtual ~IMutableHypergraph() = 0;

            /**
             *  Getter for the next vertex identifier.
             *
             *  @return The ID the next vertex added to the graph will get.
             */
            virtual htd::vertex_t nextVertex(void) const = 0;

            /**
             *  Getter for the next edge identifier.
             *
             *  @return The ID the next edge added to the graph will get.
             */
            virtual htd::id_t nextEdgeId(void) const = 0;

            /**
             *  Add a new vertex to the hypergraph.
             *
             *  @return The ID of the new vertex.
             */
            virtual htd::vertex_t addVertex(void) = 0;

            /**
             *  Add new vertices to the hypergraph.
             *
             *  @param[in] count    The number of vertices which shall be added.
             *
             *  @return The ID of the first vertex which was added to the graph. If the number of vertices to add is greater than 1,
             *          the additional vertices are numbered in ascending order and without gaps starting from the returned ID + 1.
             *          If the number of new vertices is 0, the returned value is the ID of the last vertex added to the graph.
             */
            virtual htd::vertex_t addVertices(std::size_t count) = 0;

            /**
             *  Remove a vertex from the hypergraph.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            virtual void removeVertex(htd::vertex_t vertex) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] vertex1  The first endpoint of the edge.
             *  @param[in] vertex2  The second endpoint of the edge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(const std::vector<htd::vertex_t> & elements) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(std::vector<htd::vertex_t> && elements) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(const htd::ConstCollection<htd::vertex_t> & elements) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] hyperedge    The template hyperedge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(const htd::Hyperedge & hyperedge) = 0;

            /**
             *  Add a new edge to the hypergraph if it does not already exist.
             *
             *  @param[in] hyperedge    The template hyperedge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            virtual htd::id_t addEdge(htd::Hyperedge && hyperedge) = 0;

            /**
             *  Remove an edge from the hypergraph.
             *
             *  @param[in] edgeId   The ID of the edge which shall be removed.
             */
            virtual void removeEdge(htd::id_t edgeId) = 0;

            /**
             *  Remove an edge from the hypergraph.
             *
             *  @param[in] vertex1  The first endpoint of the edge.
             *  @param[in] vertex2  The second endpoint of the edge.
             */
            virtual void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Remove an edge from the hypergraph.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             */
            virtual void removeEdge(const std::vector<htd::vertex_t> & elements) = 0;

            /**
             *  Remove an edge from the hypergraph.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             */
            virtual void removeEdge(const htd::ConstCollection<htd::vertex_t> & elements) = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current mutable hypergraph.
             *
             *  @return A new IMutableHypergraph object identical to the current mutable hypergraph.
             */
            virtual IMutableHypergraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current mutable hypergraph.
             *
             *  @return A new IMutableHypergraph object identical to the current mutable hypergraph.
             */
            virtual IMutableHypergraph * cloneMutableHypergraph(void) const = 0;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a mutable hypergraph.
             *
             *  @param[in] original  The original hypergraph.
             */
            virtual IMutableHypergraph & operator=(const htd::IHypergraph & original) = 0;
#else
            /**
             *  Copy assignment operator for a mutable hypergraph.
             *
             *  @param[in] original  The original hypergraph.
             */
            virtual void assign(const htd::IHypergraph & original) = 0;
#endif
    };

    inline htd::IMutableHypergraph::~IMutableHypergraph() { }
}

#endif /* HTD_HTD_IMUTABLEHYPERGRAPH_HPP */
