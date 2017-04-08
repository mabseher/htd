/* 
 * File:   IFlowNetworkStructure.hpp
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

#ifndef HTD_HTD_IFLOWNETWORKSTRUCTURE_HPP
#define HTD_HTD_IFLOWNETWORKSTRUCTURE_HPP

#include <htd/IGraphStructure.hpp>

namespace htd
{
    /**
     * Interface for classes which represent a flow network.
     */
    class IFlowNetworkStructure : public htd::IGraphStructure
    {
        public:
            /**
             *  Destructor of a flow network structure.
             */
            virtual ~IFlowNetworkStructure() = 0;

            /**
             *  Getter for the capacity of the edges connecting the source to the target vertex.
             *
             *  @param[in] source   The source vertex.
             *  @param[in] target   The target vertex.
             *
             *  @return The capacity of the edges connecting the source to the target vertex.
             */
            virtual std::size_t capacity(htd::vertex_t source, htd::vertex_t target) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current flow network structure.
             *
             *  @return A new IMultiHypergraph object identical to the current flow network structure.
             */
            virtual IFlowNetworkStructure * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current flow network structure.
             *
             *  @return A new IMultiHypergraph object identical to the current flow network structure.
             */
            virtual IFlowNetworkStructure * cloneFlowNetworkStructure(void) const = 0;
#endif
    };

    inline htd::IFlowNetworkStructure::~IFlowNetworkStructure() { }
}

#endif /* HTD_HTD_IFLOWNETWORKSTRUCTURE_HPP */
