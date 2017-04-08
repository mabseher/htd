/* 
 * File:   IMaxFlowAlgorithm.hpp
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

#ifndef HTD_HTD_IMAXFLOWALGORITHM_HPP
#define HTD_HTD_IMAXFLOWALGORITHM_HPP

#include <htd/Globals.hpp>

#include <htd/IFlow.hpp>
#include <htd/IFlowNetworkStructure.hpp>
#include <htd/LibraryInstance.hpp>

namespace htd
{
    /**
     *  Interface for algorithms which compute the maximum flow within a flow network.
     */
    class IMaxFlowAlgorithm
    {
        public:
            virtual ~IMaxFlowAlgorithm() = 0;

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
             *  Determine the maximum flow between the source and the target vertex in the given flow network.
             *
             *  @param[in] flowNetwork  The flow network.
             *  @param[in] source       The source vertex.
             *  @param[in] target       The target vertex.
             */
            virtual htd::IFlow * determineMaximumFlow(const htd::IFlowNetworkStructure & flowNetwork, htd::vertex_t source, htd::vertex_t target) const = 0;

            /**
             *  Create a deep copy of the current maximum flow algorithm.
             *
             *  @return A new IMaxFlowAlgorithm object identical to the current maximum flow algorithm.
             */
            virtual IMaxFlowAlgorithm * clone(void) const = 0;
    };

    inline htd::IMaxFlowAlgorithm::~IMaxFlowAlgorithm() { }
}

#endif /* HTD_HTD_IMAXFLOWALGORITHM_HPP */
