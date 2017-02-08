/*
 * File:   ILabel.hpp
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

#ifndef HTD_HTD_ILABEL_HPP
#define HTD_HTD_ILABEL_HPP

#include <htd/PreprocessorDefinitions.hpp>

#include <ostream>

namespace htd
{
    /**
     * Interface for classes which can be used as label for vertices and edges of a graph.
     */
    class ILabel
    {
        public:
            virtual ~ILabel() = 0;

            /**
             *  Getter for the hash code of the label.
             *
             *  @return The hash code of the label.
             */
            virtual std::size_t hash(void) const = 0;

            /**
             *  Create a deep copy of the current label.
             *
             *  @return A new ILabel object identical to the current label.
             */
            virtual ILabel * clone(void) const = 0;

            /**
             *  Equality operator for a label.
             *
             *  @param[in] rhs  The label at the right-hand side of the operator.
             *
             *  @return True if the label value is equal to the value of the label at the right-hand side of the operator, false otherwise.
             */
            virtual bool operator==(const ILabel & rhs) const = 0;

            /**
             *  Print the label to the given output stream.
             *
             *  @param[in] stream   The output stream to which the label shall be written.
             */
            virtual void print(std::ostream & stream) const = 0;
    };

    inline htd::ILabel::~ILabel() { }
}

#endif /* HTD_HTD_ILABEL_HPP */
