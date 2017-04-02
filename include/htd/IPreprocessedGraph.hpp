/* 
 * File:   IPreprocessedGraph.hpp
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

#ifndef HTD_HTD_IPREPROCESSEDGRAPH_HPP
#define HTD_HTD_IPREPROCESSEDGRAPH_HPP

#include <htd/Globals.hpp>

#include <htd/IGraphStructure.hpp>

namespace htd
{
    /**
     *  This interface is designed to hold the information of preprocessed graphs.
     *
     *  In the preprocessing phase, it has to be ensured that the vertices stored in this
     *  container are numbered from 0 to n-1 where n denotes the total number of vertices
     *  in the graph.
     *
     *  @note The vertices stored in this data structure use (in contrast to the remainder
     *  of classes provided by the htd framework) 0-based vertex names, i.e., the first
     *  vertex is assigned the ID 0. This allows for efficient storage and data handling
     *  based on arrays and vectors.
     */
    class IPreprocessedGraph : public virtual htd::IGraphStructure
    {
        public:
            virtual ~IPreprocessedGraph() = 0;

            /**
             *  Getter for the vertex count of the input graph.
             *
             *  @return The vertex count of the input graph.
             */
            virtual std::size_t inputGraphVertexCount(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the edge count of the input graph.
             *
             *  @return The edge count of the input graph.
             */
            virtual std::size_t inputGraphEdgeCount(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the actual identifiers of the vertices.
             *
             *  @return The actual identifiers of the vertices.
             */
            virtual const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the actual identifier of the given vertex.
             *
             *  @return The actual identifier of the given vertex.
             */
            virtual htd::vertex_t vertexName(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the vector containing the preprocessed neighborhood of each of the vertices.
             *
             *  @note The neighborhood of each vertex returned by this data structure does not include the respective vertex itself.
             *
             *  @return The vector containing the preprocessed neighborhood of each of the vertices.
             */
            virtual const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the vector containing the preprocessed neighborhood of a vertex.
             *
             *  @note The neighborhood returned by this data structure does not include the vertex itself.
             *
             *  @param[in] vertex   The vertex whose neighborhood shall be returned.
             *
             *  @return The vector containing the preprocessed neighborhood of the requested vertex.
             */
            virtual const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the partial vertex elimination ordering computed during the preprocessing phase.
             *
             *  @return The partial vertex elimination ordering computed during the preprocessing phase.
             */
            virtual const std::vector<htd::vertex_t> & eliminationSequence(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the set of vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             *
             *  @return The set of vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             */
            virtual const std::vector<htd::vertex_t> & remainingVertices(void) const HTD_NOEXCEPT = 0;

            /**
             *  Getter for the lower bound of the treewidth of the input graph.
             *
             *  @return The lower bound of the treewidth of the input graph.
             */
            virtual std::size_t minTreeWidth(void) const HTD_NOEXCEPT = 0;
    };

    inline htd::IPreprocessedGraph::~IPreprocessedGraph() { }
}

#endif /* HTD_HTD_IPREPROCESSEDGRAPH_HPP */
