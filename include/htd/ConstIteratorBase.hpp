/* 
 * File:   ConstIteratorBase.hpp
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

#ifndef HTD_HTD_CONSTITERATORBASE_HPP
#define HTD_HTD_CONSTITERATORBASE_HPP

#include <htd/Globals.hpp>

namespace htd
{
    /**
     *  Wrapper for iterators of immutable collections.
     */
    template <typename T>
    class ConstIteratorBase
    {
        public:
            virtual ~ConstIteratorBase<T>() = 0;

            /**
             *  Increment the iterator.
             *
             *  @return A reference to the incremented iterator.
             */
            virtual ConstIteratorBase<T> & operator++(void) HTD_NOEXCEPT = 0;

            /**
             *  Dereference the iterator.
             *
             *  @return A pointer to the element at the current iterator position.
             */
            virtual const T * operator->(void) const = 0;

            /**
             *  Dereference the iterator.
             *
             *  @return A reference to the element at the current iterator position.
             */
            virtual const T & operator*(void) const = 0;

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            virtual bool operator==(const ConstIteratorBase<T> & rhs) const HTD_NOEXCEPT = 0;

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            virtual bool operator!=(const ConstIteratorBase<T> & rhs) const HTD_NOEXCEPT = 0;

            /**
             *  Create a deep copy of the current iterator.
             *
             *  @return A new ConstIteratorBase<T> object identical to the current iterator.
             */
            virtual ConstIteratorBase<T> * clone(void) const HTD_NOEXCEPT = 0;
    };

    template <typename T>
    inline htd::ConstIteratorBase<T>::~ConstIteratorBase() { }
}

#endif /* HTD_HTD_CONSTITERATORBASE_HPP */
