/* 
 * File:   ConstIteratorWrapper.hpp
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

#ifndef HTD_HTD_CONSTITERATORWRAPPER_HPP
#define HTD_HTD_CONSTITERATORWRAPPER_HPP

#include <htd/Globals.hpp>

#include <htd/ConstIteratorBase.hpp>

#include <iterator>

namespace htd
{
    template <typename Iter, typename T = typename Iter::value_type>
    class ConstIteratorWrapper : public std::iterator<std::forward_iterator_tag, T>, public virtual htd::ConstIteratorBase<T>
    {
        public:
            ConstIteratorWrapper(Iter baseIterator) : baseIterator_(baseIterator)
            {

            }

            ConstIteratorWrapper<Iter, T>(const ConstIteratorWrapper<Iter, T> & original) : baseIterator_(original.baseIterator_)
            {

            }

            virtual ~ConstIteratorWrapper()
            {

            }

            ConstIteratorWrapper & operator=(ConstIteratorWrapper & other)
            {
                baseIterator_ = other.baseIterator_;

                return *this;
            }

            ConstIteratorWrapper<Iter, T> & operator++(void) HTD_OVERRIDE
            {
                ++baseIterator_;

                return *this;
            }

            ConstIteratorWrapper<Iter, T> operator++(int)
            {
                ConstIteratorWrapper<Iter, T> ret(*this);

                operator++();

                return ret;
            }

            bool operator==(const ConstIteratorBase<T> & other) const
            {
                const ConstIteratorWrapper<Iter, T> * o = dynamic_cast<const ConstIteratorWrapper<Iter, T> *>(&other);

                return o != nullptr && baseIterator_ == o->baseIterator_;
            }

            bool operator==(const ConstIteratorWrapper<Iter, T> & other) const
            {
                return baseIterator_ == other.baseIterator_;
            }

            bool operator!=(const ConstIteratorBase<T> & other) const
            {
                const ConstIteratorWrapper<Iter, T> * o = dynamic_cast<const ConstIteratorWrapper<Iter, T> *>(&other);

                return o != nullptr && baseIterator_ != o->baseIterator_;
            }

            bool operator!=(const ConstIteratorWrapper<Iter, T> & other) const
            {
                return baseIterator_ != other.baseIterator_;
            }

            const T * operator->(void) const HTD_OVERRIDE
            {
                return &(*baseIterator_);
            }

            const T & operator*(void) const HTD_OVERRIDE
            {
                return *baseIterator_;
            }

            ConstIteratorWrapper<Iter, T> * clone(void) const HTD_OVERRIDE
            {
                return new ConstIteratorWrapper<Iter, T>(*this);
            }

        private:
            Iter baseIterator_;
    };
}

#endif /* HTD_HTD_CONSTITERATORWRAPPER_HPP */
