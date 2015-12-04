/* 
 * File:   IteratorBase.hpp
 * 
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_ITERATORBASE_HPP
#define HTD_HTD_ITERATORBASE_HPP

#include <htd/Globals.hpp>

#include <iterator>

namespace htd
{
    template <typename T>
    class IteratorBase
    {
        public:
            virtual ~IteratorBase<T>() = 0;

            virtual IteratorBase<T> & operator++(void) = 0;

            virtual const T * operator->(void) const = 0;

            virtual const T & operator*(void) const = 0;

            virtual bool operator==(const IteratorBase<T> & other) const = 0;

            virtual bool operator!=(const IteratorBase<T> & other) const = 0;

            virtual IteratorBase<T> * clone(void) const = 0;
    };

    template <typename T>
    inline htd::IteratorBase<T>::~IteratorBase() { }
}

#endif /* HTD_HTD_ITERATORBASE_HPP */
