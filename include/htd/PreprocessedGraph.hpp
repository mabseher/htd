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
             *  @param[in] minTreeWidth         The lower bound for the treewidth of the original input graph.
             */
            HTD_API PreprocessedGraph(std::vector<htd::vertex_t> && vertexNames,
                                      std::vector<std::vector<htd::vertex_t>> && neighborhood,
                                      std::vector<htd::vertex_t> && eliminationSequence,
                                      std::vector<htd::vertex_t> && remainingVertices,
                                      std::size_t minTreeWidth);

            /**
             *  Destructor for a preprocessed graph data structure.
             */
            HTD_API virtual ~PreprocessedGraph();

            HTD_API std::size_t vertexCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::vertex_t vertexName(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & eliminationSequence(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & remainingVertices(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API std::size_t minTreeWidth(void) const HTD_NOEXCEPT HTD_OVERRIDE;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_PREPROCESSEDGRAPH_HPP */
