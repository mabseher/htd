/* 
 * File:   IteratorWrapper.hpp
 * 
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_ITERATORWRAPPER_HPP
#define HTD_HTD_ITERATORWRAPPER_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    template <typename Iter, typename T = typename Iter::value_type>
    class IteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public virtual htd::IteratorBase<T>
    {
        public:
            IteratorWrapper(Iter baseIterator) : baseIterator_(baseIterator)
            {

            }

            IteratorWrapper<Iter, T>(const IteratorWrapper<Iter, T> & original) : baseIterator_(original.baseIterator_)
            {

            }

            virtual ~IteratorWrapper()
            {

            }

            IteratorWrapper & operator=(IteratorWrapper & original)
            {
                baseIterator_ = original.baseIterator_;

                return *this;
            }

            IteratorWrapper<Iter, T> & operator++(void) HTD_OVERRIDE
            {
                ++baseIterator_;

                return *this;
            }

            IteratorWrapper<Iter, T> operator++(int)
            {
                IteratorWrapper<Iter, T> ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const htd::ConstIteratorBase<T> & rhs) const HTD_OVERRIDE
            {
                const IteratorWrapper<Iter, T> * o = dynamic_cast<const IteratorWrapper<Iter, T> *>(&rhs);

                return o != nullptr && baseIterator_ == o->baseIterator_;
            }

            bool operator==(const IteratorWrapper<Iter, T> & rhs) const
            {
                return baseIterator_ == rhs.baseIterator_;
            }

            bool operator!=(const htd::ConstIteratorBase<T> & rhs) const HTD_OVERRIDE
            {
                const IteratorWrapper<Iter, T> * o = dynamic_cast<const IteratorWrapper<Iter, T> *>(&rhs);

                return o != nullptr && baseIterator_ != o->baseIterator_;
            }

            bool operator!=(const IteratorWrapper<Iter, T> & rhs) const
            {
                return baseIterator_ != rhs.baseIterator_;
            }

            T * operator->(void) HTD_OVERRIDE
            {
                return &(*baseIterator_);
            }

            const T * operator->(void) const HTD_OVERRIDE
            {
                return &(*baseIterator_);
            }

            T & operator*(void) HTD_OVERRIDE
            {
                return *baseIterator_;
            }

            const T & operator*(void) const HTD_OVERRIDE
            {
                return *baseIterator_;
            }

            IteratorWrapper<Iter, T> * clone(void) const HTD_OVERRIDE
            {
                return new IteratorWrapper<Iter, T>(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_ITERATORWRAPPER_HPP */

