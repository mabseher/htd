/* 
 * File:   IGraphPreprocessor.hpp
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

#ifndef HTD_HTD_IGRAPHPREPROCESSOR_HPP
#define HTD_HTD_IGRAPHPREPROCESSOR_HPP

#include <htd/Globals.hpp>

#include <htd/IMultiHypergraph.hpp>
#include <htd/IPreprocessedGraph.hpp>
#include <htd/LibraryInstance.hpp>

namespace htd
{
    /**
     *  Interface for graph preprocessors.
     */
    class IGraphPreprocessor
    {
        public:
            virtual ~IGraphPreprocessor() = 0;

            /**
             *  Prepare the given graph so that the resulting data structure
             *  allows for efficient decomposition of the graph in following
             *  algorithms.
             *
             *  The resulting data structure contains the graph in the form of an adjacency
             *  list and it is guaranteed that the vertices are numbered between 0 and n-1
             *  where n is the total number of vertices in the given graph. This allows for
             *  efficient use of arrays and vectors within algorithms.
             *
             *  @param[in] graph    The input graph which shall be prepared.
             *
             *  @return A preprocessed version of the input graph.
             */
            virtual htd::IPreprocessedGraph * prepare(const htd::IMultiHypergraph & graph) const = 0;

            /**
             *  Getter for the associated management class.
             *
             *  @return The associated management class.
             */
            virtual const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT = 0;

            /**
             *  Set a new management class for the library object.
             *
             *  @param[in] manager   The new management class for the library object.
             */
            virtual void setManagementInstance(const htd::LibraryInstance * const manager) = 0;

            /**
             *  Create a deep copy of the current graph preprocessor.
             *
             *  @return A new IGraphPreprocessor object identical to the current graph preprocessor.
             */
            virtual IGraphPreprocessor * clone(void) const = 0;
    };

    inline htd::IGraphPreprocessor::~IGraphPreprocessor() { }
}

#endif /* HTD_HTD_IGRAPHPREPROCESSOR_HPP */
