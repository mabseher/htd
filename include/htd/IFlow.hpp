/* 
 * File:   IFlow.hpp
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

#ifndef HTD_HTD_IFLOW_HPP
#define HTD_HTD_IFLOW_HPP

#include <htd/Globals.hpp>

#include <vector>

namespace htd
{
    /**
     *  Interface for classes which represent the flow in a flow network.
     */
    class IFlow
    {
        public:
            /**
             *  Destructor of a flow data structure.
             */
            virtual ~IFlow() = 0;

            /**
             *  Getter for the number of vertices contained in the flow data structure.
             *
             *  @return The number of vertices contained in the flow data structure.
             */
            virtual std::size_t vertexCount(void) const = 0;

            /**
             *  Getter for the source vertex of the flow.
             *
             *  @return The source vertex of the flow.
             */
            virtual htd::vertex_t source(void) const = 0;

            /**
             *  Getter for the target vertex of the flow.
             *
             *  @return The target vertex of the flow.
             */
            virtual htd::vertex_t target(void) const = 0;

            /**
             *  Getter for the value of the flow.
             *
             *  @return The value of the flow.
             */
            virtual std::size_t value(void) const = 0;

            /**
             *  Get the current flow between the source vertex and the target vertex.
             *
             *  @param[in] source   The source vertex.
             *  @param[in] target   The target vertex.
             *
             *  @return The current flow between the source vertex and the target vertex.
             */
            virtual long long flow(htd::vertex_t source, htd::vertex_t target) const = 0;

            /**
             *  Create a deep copy of the current flow.
             *
             *  @return A new IFlow object identical to the current flow.
             */
            virtual IFlow * clone(void) const = 0;
    };

    inline htd::IFlow::~IFlow() { }
}

#endif /* HTD_HTD_IFLOW_HPP */
