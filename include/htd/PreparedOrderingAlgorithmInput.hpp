/* 
 * File:   PreparedOrderingAlgorithmInput.hpp
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

#ifndef HTD_HTD_PREPAREDORDERINGALGORITHMINPUT_HPP
#define HTD_HTD_PREPAREDORDERINGALGORITHMINPUT_HPP

#include <htd/Globals.hpp>

#include <vector>
#include <memory>

namespace htd
{
    /**
     *  This class is designed to hold the pre-processed input for vertex elimination ordering algorithms.
     *
     *  In the pre-processing phase, it has to be ensured that the vertices stored in this
     *  container are numbered from 0 to n-1 where n denotes the total number of vertices
     *  in the graph.
     *
     *  @note The vertices stored in this data structure use (in contrast to the remainder
     *  of classes provided by the htd framework) 0-based vertex names, i.e., the first
     *  vertex is assigned the ID 0. This allows for efficient storage and data handling
     *  based on arrays and vectors.
     */
    class PreparedOrderingAlgorithmInput
    {
        public:
            /**
             *  Constructor for a new ordering algorithm input data structure.
             *
             *  @param[in] vertexNames                      The actual identifiers of the vertices.
             *  @param[in] neighborhood                     A vector containing the neighborhood of each of the vertices.
             *  @param[in] preprocessedEliminationOrdering  A partial vertex elimination ordering computed during the pre-processing phase.
             *  @param[in] remainingVertices                The set of vertices which were not eliminated during the pre-processing phase.
             *  @param[in] minTreeWidth                     The lower bound for the treewidth of the original input graph.
             */
            HTD_API PreparedOrderingAlgorithmInput(std::vector<htd::vertex_t> && vertexNames,
                                                   std::vector<std::vector<htd::vertex_t>> && neighborhood,
                                                   std::vector<htd::vertex_t> && preprocessedEliminationOrdering,
                                                   std::vector<htd::vertex_t> && remainingVertices,
                                                   std::size_t minTreeWidth);

            /**
             *  Destructor for an ordering algorithm input data structure.
             */
            HTD_API virtual ~PreparedOrderingAlgorithmInput();

            /**
             *  Getter for the vertex count of the input graph.
             *
             *  @return The vertex count of the input graph.
             */
            HTD_API std::size_t vertexCount(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the actual identifiers of the vertices.
             *
             *  @return The actual identifiers of the vertices.
             */
            HTD_API const std::vector<htd::vertex_t> & vertexNames(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the actual identifier of the given vertex.
             *
             *  @return The actual identifier of the given vertex.
             */
            HTD_API htd::vertex_t vertexName(htd::vertex_t vertex) const;

            /**
             *  Getter for the vector containing the neighborhood of each of the vertices.
             *
             *  @note The neighborhood of each vertex returned by this data structure does not include the respective vertex itself.
             *
             *  @return The vector containing the neighborhood of each of the vertices.
             */
            HTD_API const std::vector<std::vector<htd::vertex_t>> & neighborhood(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the vector containing the neighborhood of each of the vertices.
             *
             *  @note The neighborhood returned by this data structure does not include the vertex itself.
             *
             *  @param[in] vertex   The vertex whose neighborhood shall be returned.
             *
             *  @return The vector containing the neighborhood of the requested vertex.
             */
            HTD_API const std::vector<htd::vertex_t> & neighborhood(htd::vertex_t vertex) const;

            /**
             *  Getter for the partial vertex elimination ordering computed during the pre-processing phase.
             *
             *  @return The partial vertex elimination ordering computed during the pre-processing phase.
             */
            HTD_API const std::vector<htd::vertex_t> & preprocessedEliminationOrdering(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the set of vertices (with 0-based IDs) which were not eliminated during the pre-processing phase.
             *
             *  @return The set of vertices (with 0-based IDs) which were not eliminated during the pre-processing phase.
             */
            HTD_API const std::vector<htd::vertex_t> & remainingVertices(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the lower bound of the treewidth of the input graph.
             *
             *  @return The lower bound of the treewidth of the input graph.
             */
            HTD_API std::size_t minTreeWidth(void) const HTD_NOEXCEPT;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_PREPAREDORDERINGALGORITHMINPUT_HPP */
