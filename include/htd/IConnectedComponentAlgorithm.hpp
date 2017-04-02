/* 
 * File:   IConnectedComponentAlgorithm.hpp
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

#ifndef HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP
#define HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP

#include <htd/Globals.hpp>

#include <htd/IGraphStructure.hpp>
#include <htd/LibraryInstance.hpp>

namespace htd
{
    /**
     * Interface for algorithms which determine the connected components of a given graph.
     */
    class IConnectedComponentAlgorithm
    {
        public:
            virtual ~IConnectedComponentAlgorithm() = 0;

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
             *  Determine the connected components of the given graph.
             *
             *  @param[in] graph     The graph which's components shall be determinded.
             *  @param[out] target   The target vector to which the determined components shall be appended.
             */
            virtual void determineComponents(const htd::IGraphStructure & graph, std::vector<std::vector<htd::vertex_t>> & target) const = 0;

            /**
             *  Determine the connected component of the given graph where a given vertex resides.
             *
             *  @param[in] graph            The graph which's components shall be determinded.
             *  @param[in] startingVertex   The specific vertex from which the algorithm shall start.
             *  @param[out] target          The target vector to which the determined component shall be appended.
             */
            virtual void determineComponent(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Create a deep copy of the current connected component algorithm.
             *
             *  @return A new IConnectedComponentAlgorithm object identical to the current connected component algorithm.
             */
            virtual IConnectedComponentAlgorithm * clone(void) const = 0;
    };

    inline htd::IConnectedComponentAlgorithm::~IConnectedComponentAlgorithm() { }
}

#endif /* HTD_HTD_ICONNECTEDCOMPONENTALGORITHM_HPP */
