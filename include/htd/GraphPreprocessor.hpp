/* 
 * File:   GraphPreprocessor.hpp
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

#ifndef HTD_HTD_GRAPHPREPROCESSOR_HPP
#define HTD_HTD_GRAPHPREPROCESSOR_HPP

#include <htd/Globals.hpp>
#include <htd/LibraryInstance.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IPreprocessedGraph.hpp>

namespace htd
{
    /**
     *  Preprocessor for graphs.
     */
    class GraphPreprocessor
    {
        public:
            /**
             *  Constructor for a graph preprocessor.
             *
             *  @param[in] manager   The management instance to which the new preprocessor belongs.
             */
            HTD_API GraphPreprocessor(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~GraphPreprocessor();

            /**
             *  Prepare the given graph so that the resulting data structure
             *  allows for efficient decomposition of the graph in following
             *  algorithms.
             *
             *  The resulting data structure contains the graph in the form of an
             *  adjacency list and it is guaranteed that the vertices are numbered
             *  between 0 and n-1 where n is the total number of vertices in the
             *  given graph. This allows for efficient use of arrays and vectors
             *  within algorithms.
             *
             *  @param[in] graph                The input graph which shall be prepared.
             *  @param[in] applyPreprocessing   A boolean flag indicating whether the input graph shall be
             *                                  preprocessed in order to increase efficiency of algorithms.
             *                                  The preprocessing does not increase the width of the
             *                                  resulting decompositions.
             *
             *  @return A preprocessed version of the input graph.
             */
            HTD_API htd::IPreprocessedGraph * prepare(const htd::IMultiHypergraph & graph, bool applyPreprocessing = true) const HTD_NOEXCEPT;

            /**
             *  Getter for the associated management class.
             *
             *  @return The associated management class.
             */
            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT;

            /**
             *  Set a new management class for the library object.
             *
             *  @param[in] manager   The new management class for the library object.
             */
            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager);

            /**
             *  Create a deep copy of the current graph preprocessor.
             *
             *  @return A new GraphPreprocessor object identical to the current graph preprocessor.
             */
            HTD_API GraphPreprocessor * clone(void) const;

        protected:
            /**
             *  Copy assignment operator for a graph preprocessor.
             *
             *  @note This operator is protected to prevent assignments to an already initialized preprocessor.
             */
            GraphPreprocessor & operator=(const GraphPreprocessor &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_ORDERINGALGORITHMPREPROCESSOR_HPP */
