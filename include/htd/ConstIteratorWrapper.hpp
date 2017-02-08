/* 
 * File:   ConstIteratorWrapper.hpp
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

#ifndef HTD_HTD_CONSTITERATORWRAPPER_HPP
#define HTD_HTD_CONSTITERATORWRAPPER_HPP

#include <htd/Globals.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Implementation of a wrapper for iterators of immutable collections.
     */
    template <typename Iter, typename T = typename Iter::value_type>
    class ConstIteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public htd::ConstIteratorBase<T>
    {
        public:
            /**
             *  Constructor for an iterator wrapper.
             *
             *  @param[in] baseIterator The underlying iterator which shall be wrapped.
             */
            ConstIteratorWrapper(Iter baseIterator) HTD_NOEXCEPT : baseIterator_(baseIterator)
            {

            }

            /**
             *  Copy constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper<Iter, T>(const ConstIteratorWrapper<Iter, T> & original) HTD_NOEXCEPT : baseIterator_(original.baseIterator_)
            {

            }

            /**
             *  Move constructor for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper<Iter, T>(ConstIteratorWrapper<Iter, T> && original) HTD_NOEXCEPT : baseIterator_(std::move(original.baseIterator_))
            {

            }

            virtual ~ConstIteratorWrapper()
            {

            }

            /**
             *  Copy assignment operator for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper & operator=(ConstIteratorWrapper & original) HTD_NOEXCEPT
            {
                baseIterator_ = original.baseIterator_;

                return *this;
            }

            /**
             *  Move assignment operator for an iterator wrapper.
             *
             *  @param[in] original  The original iterator wrapper.
             */
            ConstIteratorWrapper & operator=(ConstIteratorWrapper && original) HTD_NOEXCEPT
            {
                baseIterator_ = std::move(original.baseIterator_);

                return *this;
            }

            ConstIteratorWrapper<Iter, T> & operator++(void) HTD_NOEXCEPT HTD_OVERRIDE
            {
                ++baseIterator_;

                return *this;
            }

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            ConstIteratorWrapper<Iter, T> operator++(int) HTD_NOEXCEPT
            {
                ConstIteratorWrapper<Iter, T> ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const ConstIteratorBase<T> & rhs) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseIterator_ == static_cast<const ConstIteratorWrapper<Iter, T> *>(&rhs)->baseIterator_;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const ConstIteratorWrapper<Iter, T> & rhs) const HTD_NOEXCEPT
            {
                return baseIterator_ == rhs.baseIterator_;
            }

            bool operator!=(const ConstIteratorBase<T> & rhs) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return baseIterator_ != static_cast<const ConstIteratorWrapper<Iter, T> *>(&rhs)->baseIterator_;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const ConstIteratorWrapper<Iter, T> & rhs) const HTD_NOEXCEPT
            {
                return baseIterator_ != rhs.baseIterator_;
            }

            const T * operator->(void) const HTD_OVERRIDE
            {
                return &(*baseIterator_);
            }

            const T & operator*(void) const HTD_OVERRIDE
            {
                return *baseIterator_;
            }

            ConstIteratorWrapper<Iter, T> * clone(void) const HTD_NOEXCEPT HTD_OVERRIDE
            {
                return new ConstIteratorWrapper<Iter, T>(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_CONSTITERATORWRAPPER_HPP */
