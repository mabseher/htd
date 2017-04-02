/*
 * File:   IVertexOrdering.hpp
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

#ifndef HTD_HTD_IVERTEXORDERING_HPP
#define HTD_HTD_IVERTEXORDERING_HPP

#include <htd/Globals.hpp>

#include <memory>
#include <vector>

namespace htd
{
    /**
     *  Interface for orderings of graph vertices.
     */
    class IVertexOrdering
    {
        public:
            /**
             *  Destructor for a IVertexOrdering object.
             */
            virtual ~IVertexOrdering() = 0;

            /**
             *  Getter for the sequence of vertices.
             *
             *  @return The sequence of vertices.
             */
            virtual const std::vector<htd::vertex_t> & sequence(void) const = 0;

            /**
             *  Getter for the number of iterations which was needed to find the sequence of vertices at hand.
             *
             *  @return The number of iterations which was needed to find the sequence of vertices at hand.
             */
            virtual std::size_t requiredIterations(void) const = 0;
    };

    inline htd::IVertexOrdering::~IVertexOrdering() { }
}

#endif /* HTD_HTD_IVERTEXORDERING_HPP */
