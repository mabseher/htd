/*
 * File:   IWidthLimitedVertexOrdering.hpp
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

#ifndef HTD_HTD_IWIDTHLIMITEDVERTEXORDERING_HPP
#define HTD_HTD_IWIDTHLIMITEDVERTEXORDERING_HPP

#include <htd/Globals.hpp>
#include <htd/IVertexOrdering.hpp>

#include <memory>
#include <vector>

namespace htd
{
    /**
     *  Interface for orderings of graph vertices for which the width of
     *  the resulting decomposition constructed by bucket elimination is
     *  already known.
     */
    class IWidthLimitedVertexOrdering : public htd::IVertexOrdering
    {
        public:
            /**
             *  Destructor for a IWidthLimitedVertexOrdering object.
             */
            virtual ~IWidthLimitedVertexOrdering() = 0;

            /**
             *  Getter for the maximum bag size a decomposition based on bucket elimination and the computed ordering will have.
             *
             *  @return The maximum bag size a decomposition based on bucket elimination and the computed ordering will have.
             */
            virtual std::size_t maximumBagSize(void) const = 0;
    };

    inline htd::IWidthLimitedVertexOrdering::~IWidthLimitedVertexOrdering() { }
}

#endif /* HTD_HTD_IWIDTHLIMITEDVERTEXORDERING_HPP */
