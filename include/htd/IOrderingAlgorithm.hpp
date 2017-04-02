/* 
 * File:   IOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_IORDERINGALGORITHM_HPP
#define HTD_HTD_IORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IVertexOrdering.hpp>
#include <htd/IPreprocessedGraph.hpp>

namespace htd
{
    /**
     * Interface for algorithms which can be used to compute vertex orderings.
     */
    class IOrderingAlgorithm
    {
        public:
            virtual ~IOrderingAlgorithm() = 0;

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
             *  Compute the vertex ordering of a given graph.
             *
             *  @param[in] graph    The input graph for which the vertex ordering shall be computed.
             *
             *  @return The vertex ordering of the given graph.
             */
            virtual htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT = 0;

            /**
             *  Compute the vertex ordering of a given graph.
             *
             *  @param[in] graph                The input graph for which the vertex ordering shall be computed.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *
             *  @return The vertex ordering of the given graph.
             */
            virtual htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current ordering algorithm.
             *
             *  @return A new IOrderingAlgorithm object identical to the current ordering algorithm.
             */
            virtual IOrderingAlgorithm * clone(void) const = 0;
#else
            /**
             *  Create a deep copy of the current ordering algorithm.
             *
             *  @return A new IOrderingAlgorithm object identical to the current ordering algorithm.
             */
            virtual IOrderingAlgorithm * cloneOrderingAlgorithm(void) const = 0;
#endif
    };

    inline htd::IOrderingAlgorithm::~IOrderingAlgorithm() { }
}

#endif /* HTD_HTD_IORDERINGALGORITHM_HPP */
