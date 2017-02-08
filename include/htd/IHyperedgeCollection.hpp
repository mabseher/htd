/*
 * File:   IHyperedgeCollection.hpp
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

#ifndef HTD_HTD_IHYPEREDGECOLLECTION_HPP
#define HTD_HTD_IHYPEREDGECOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/Hyperedge.hpp>
#include <htd/ConstIterator.hpp>

namespace htd
{
    /**
     *  Interface for hyperedge collections.
     */
    class IHyperedgeCollection
    {
        public:
            /**
             *  The value type of the collection.
             */
            typedef htd::Hyperedge value_type;

            virtual ~IHyperedgeCollection() = 0;

            /**
             *  Check whether the collection is emtpy.
             *
             *  @return True if the collection is empty, false otherwise.
             */
            virtual bool empty(void) const = 0;

            /**
             *  Getter for the size of the collection.
             *
             *  @return The size of the collection.
             */
            virtual std::size_t size(void) const = 0;

            /**
             *  Access the hyperedge at the specific position within the collection.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The hyperedge at the specific position.
             */
            virtual const htd::Hyperedge & at(htd::index_t index) const = 0;

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            virtual htd::ConstIterator<htd::Hyperedge> begin(void) const = 0;

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            virtual htd::ConstIterator<htd::Hyperedge> end(void) const = 0;

            /**
             *  Access the hyperedge at the specific position within the collection.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The hyperedge at the specific position.
             */
            virtual const htd::Hyperedge & operator[](htd::index_t index) const = 0;

            /**
             *  Equality operator for a hyperedge collection.
             *
             *  @param[in] rhs  The hyperedge collection at the right-hand side of the operator.
             *
             *  @return True if the hyperedge collection is equal to the hyperedge collection at the right-hand side of the operator, false otherwise.
             */
            virtual bool operator==(const IHyperedgeCollection & rhs) const = 0;

            /**
             *  Inequality operator for a hyperedge collection.
             *
             *  @param[in] rhs  The hyperedge collection at the right-hand side of the operator.
             *
             *  @return True if the hyperedge collection is not equal to the hyperedge collection at the right-hand side of the operator, false otherwise.
             */
            virtual bool operator!=(const IHyperedgeCollection & rhs) const = 0;

            /**
             *  Create a deep copy of the current hyperedge collection.
             *
             *  @return A new IHyperedgeCollection object identical to the current hyperedge collection.
             */
            virtual IHyperedgeCollection * clone(void) const = 0;
    };

    inline htd::IHyperedgeCollection::~IHyperedgeCollection() { }
}

#endif /* HTD_HTD_IHYPEREDGECOLLECTION_HPP */
