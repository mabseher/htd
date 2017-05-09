/* 
 * File:   PreprocessedGraph.hpp
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

#ifndef HTD_HTD_PREPROCESSEDGRAPH_HPP
#define HTD_HTD_PREPROCESSEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IPreprocessedGraph.hpp>

#include <vector>
#include <memory>

namespace htd
{
    /**
     *  This class is designed to hold the information of preprocessed graphs.
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
    class PreprocessedGraph : public htd::IPreprocessedGraph
    {
        public:
            /**
             *  Constructor for a new, preprocessed graph data structure.
             *
             *  @param[in] vertexNames          The actual identifiers of the vertices.
             *  @param[in] neighborhood         A vector containing the preprocessed neighborhood of each of the vertices.
             *  @param[in] eliminationSequence  A partial vertex elimination ordering computed during the preprocessing phase.
             *  @param[in] remainingVertices    The set of vertices which were not eliminated during the preprocessing phase.
             *  @param[in] inputGraphEdgeCount  The number of edges in the input graph.
             *  @param[in] minTreeWidth         The lower bound for the treewidth of the original input graph.
             */
            HTD_API PreprocessedGraph(std::vector<htd::vertex_t> && vertexNames,
                                      std::vector<std::vector<htd::vertex_t>> && neighborhood,
                                      std::vector<htd::vertex_t> && eliminationSequence,
                                      std::vector<htd::vertex_t> && remainingVertices,
                                      std::size_t inputGraphEdgeCount,
                                      std::size_t minTreeWidth);

            /**
             *  Copy constructor for a preprocessed graph data structure.
             *
             *  @param[in] original  The original preprocessed graph data structure.
             */
            HTD_API PreprocessedGraph(const htd::PreprocessedGraph & original);

            /**
             *  Destructor for a preprocessed graph data structure.
             */
            HTD_API virtual ~PreprocessedGraph();

            HTD_API std::size_t vertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API std::size_t inputGraphVertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t inputGraphEdgeCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            HTD_API void copyVerticesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            HTD_API htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            HTD_API bool isConnected(void) const HTD_OVERRIDE;

            HTD_API bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::vertex_t vertexName(htd::vertex_t vertex) const HTD_OVERRIDE;

            /**
             *  Updatable getter for the vector containing the preprocessed neighborhood of each of the vertices.
             *
             *  @note The neighborhood of each vertex returned by this data structure does not include the respective vertex itself.
             *
             *  @return The updatable vector containing the preprocessed neighborhood of each of the vertices.
             */
            HTD_API std::vector<std::vector<htd::vertex_t>> & neighborhood(void) HTD_NOEXCEPT;

            HTD_API const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            /**
             *  Updatable getter for the vector containing the preprocessed neighborhood of a vertex.
             *
             *  @note The neighborhood returned by this data structure does not include the vertex itself.
             *
             *  @param[in] vertex   The vertex whose neighborhood shall be returned.
             *
             *  @return The updatable vector containing the preprocessed neighborhood of the requested vertex.
             */
            HTD_API std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex);

            HTD_API const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const HTD_OVERRIDE;

            /**
             *  Remove a vertex from the graph.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            HTD_API void removeVertex(htd::vertex_t vertex);

            /**
             *  Recompute the number of edges in the graph to update the result of the function edgeCount().
             */
            HTD_API void updateEdgeCount(void);

            /**
             *  Updatable getter for the partial vertex elimination ordering computed during the preprocessing phase.
             *
             *  @return The updatable partial vertex elimination ordering computed during the preprocessing phase.
             */
            HTD_API std::vector<htd::vertex_t> & eliminationSequence(void) HTD_NOEXCEPT;

            HTD_API const std::vector<htd::vertex_t> & eliminationSequence(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & remainingVertices(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            /**
             *  Set the vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             *
             *  @param[in] remainingVertices    The set of vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             */
            HTD_API void setRemainingVertices(const std::vector<htd::vertex_t> & remainingVertices);

            /**
             *  Set the vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             *
             *  @param[in] remainingVertices    The set of vertices (with 0-based IDs) which were not eliminated during the preprocessing phase.
             */
            HTD_API void setRemainingVertices(std::vector<htd::vertex_t> && remainingVertices);

            /**
             *  Updatable getter for the lower bound of the treewidth of the input graph.
             *
             *  @return The updatable lower bound of the treewidth of the input graph.
             */
            HTD_API std::size_t & minTreeWidth(void) HTD_NOEXCEPT;

            HTD_API std::size_t minTreeWidth(void) const HTD_NOEXCEPT HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API PreprocessedGraph * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current preprocessed graph.
             *
             *  @return A new PreprocessedGraph object identical to the current preprocessed graph.
             */
            HTD_API PreprocessedGraph * clone(void) const;

            HTD_API htd::IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_PREPROCESSEDGRAPH_HPP */
