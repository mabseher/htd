/*
 * File:   IGraphSeparatorAlgorithm.hpp
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

#ifndef HTD_HTD_IGRAPHSEPARATORALGORITHM_HPP
#define HTD_HTD_IGRAPHSEPARATORALGORITHM_HPP

#include <htd/IGraphStructure.hpp>
#include <htd/LibraryInstance.hpp>

namespace htd
{
    /**
     *  Interface for algorithms which determine separating vertex sets of a given graph.
     */
    class IGraphSeparatorAlgorithm
    {
        public:
            /**
             *  Destructor of a graph separator algorithm.
             */
            virtual ~IGraphSeparatorAlgorithm() = 0;

            /**
             *  Compute a separating vertex set of the given graph.
             *
             *  @param[in] graph    The graph for which a separating vertex set shall be computed.
             *
             *  @return A vector containing a separating vertex set of the given graph in ascending order.
             */
            virtual std::vector<htd::vertex_t> * computeSeparator(const htd::IGraphStructure & graph) const = 0;

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
             *  Create a deep copy of the current graph separator algorithm.
             *
             *  @return A new IGraphSeparatorAlgorithm object identical to the current graph separator algorithm.
             */
            virtual IGraphSeparatorAlgorithm * clone(void) const = 0;
    };

    inline htd::IGraphSeparatorAlgorithm::~IGraphSeparatorAlgorithm() { }
}

#endif /* HTD_HTD_IGRAPHSEPARATORALGORITHM_HPP */
