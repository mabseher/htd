/*
 * File:   ILabelCollection.hpp
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

#ifndef HTD_HTD_ILABELCOLLECTION_HPP
#define HTD_HTD_ILABELCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>
#include <htd/ConstCollection.hpp>

namespace htd
{
    /**
     * Interface for classes which represent collections of labels.
     */
    class ILabelCollection
    {
        public:
            virtual ~ILabelCollection() = 0;

            /**
             *  Getter for the number of different label names.
             *
             *  @return The number of different label names.
             */
            virtual std::size_t labelCount(void) const = 0;

            /**
             *  Access the collection of all label names.
             *
             *  @return The collection of all label names sorted in ascending order.
             */
            virtual htd::ConstCollection<std::string> labelNames(void) const = 0;

            /**
             *  Access the label name at the specific position.
             *
             *  @param[in] index    The position of the label name.
             *
             *  @return The label name at the specific position.
             */
            virtual const std::string & labelNameAtPosition(htd::index_t index) const = 0;

            /**
             *  Access the label with the given name.
             *
             *  @param[in] labelName    The name of the label.
             *
             *  @return The label with the given name.
             */
            virtual htd::ILabel & label(const std::string & labelName) = 0;

            /**
             *  Access the label with the given name.
             *
             *  @param[in] labelName    The name of the label.
             *
             *  @return The label with the given name.
             */
            virtual const htd::ILabel & label(const std::string & labelName) const = 0;

            /**
             *  Set the label with the given name.
             *
             *  If a label with the same name already exists in the label collection, the
             *  existing label will be replaced and the memory of the previous label is
             *  freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the label
             *  collection. Deleting the label outside the label collection or inserting the same label object with multiple
             *  names will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new labeling.
             *  @param[in] label        The new label.
             */
            virtual void setLabel(const std::string & labelName, htd::ILabel * label) = 0;

            /**
             *  Remove the label with the given name.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             */
            virtual void removeLabel(const std::string & labelName) = 0;

            /**
             *  Create a deep copy of the current label collection.
             *
             *  @return A new ILabelCollection object identical to the current label collection.
             */
            virtual ILabelCollection * clone(void) const = 0;
    };

    inline htd::ILabelCollection::~ILabelCollection() { }
}

#endif /* HTD_HTD_ILABELCOLLECTION_HPP */
