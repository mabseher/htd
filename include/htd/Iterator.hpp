/* 
 * File:   Iterator.hpp
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

#ifndef HTD_HTD_ITERATOR_HPP
#define HTD_HTD_ITERATOR_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/IteratorWrapper.hpp>

#include <memory>

namespace htd
{
    template <typename T>
    class Iterator : public virtual IteratorBase<T>
    {
        public:
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef const T & reference;
            typedef const T * pointer;
            typedef std::forward_iterator_tag iterator_category;

            Iterator(void) : baseIterator_(nullptr)
            {

            }

            template <class Iter>
            Iterator(Iter iterator) : baseIterator_(new IteratorWrapper<Iter, T>(iterator))
            {

            }

            Iterator<T>(const Iterator<T> & original) : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = original.baseIterator_->clone();
                }
            }

            virtual ~Iterator()
            {
                if (baseIterator_ != nullptr)
                {
                    delete baseIterator_;

                    baseIterator_ = nullptr;
                }
            }

            Iterator & operator=(Iterator & other)
            {
                if (baseIterator_ != nullptr)
                {
                    delete baseIterator_;

                    baseIterator_ = nullptr;
                }

                if (other.baseIterator_ != nullptr)
                {
                    baseIterator_ = other.baseIterator_->clone();
                }

                return *this;
            }

            Iterator<T> & operator++(void) HTD_OVERRIDE
            {
                if (baseIterator_!= nullptr)
                {
                    ++(*baseIterator_);
                }

                return *this;
            }

            Iterator<T> operator++(int)
            {
                Iterator<T> ret(*baseIterator_);

                operator++();

                return ret;
            }

            bool operator==(const IteratorBase<T> & other) const HTD_OVERRIDE
            {
                bool ret = false;

                const Iterator<T> * o = dynamic_cast<const Iterator<T> *>(&other);

                if (o != nullptr)
                {
                    if (baseIterator_ == nullptr)
                    {
                        ret = o->baseIterator_ == nullptr;
                    }
                    else if (o->baseIterator_ != nullptr)
                    {
                        ret = *baseIterator_ == *(o->baseIterator_ );
                    }
                }

                return ret;
            }

            bool operator==(const Iterator<T> & other) const
            {
                bool ret = false;

                if (baseIterator_ == nullptr)
                {
                    ret = other.baseIterator_ == nullptr;
                }
                else if (other.baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ == *(other.baseIterator_ );
                }

                return ret;
            }

            bool operator!=(const IteratorBase<T> & other) const HTD_OVERRIDE
            {
                return !(*this == other);
            }

            bool operator!=(const Iterator<T> & other) const
            {
                return !(*this == other);
            }

            const T * operator->(void) const HTD_OVERRIDE
            {
                return &(*(*(baseIterator_)));
            }

            const T & operator*(void) const HTD_OVERRIDE
            {
                return *(*baseIterator_);
            }

            Iterator<T> * clone(void) const HTD_OVERRIDE
            {
                Iterator<T> * ret = nullptr;

                if (baseIterator_ == nullptr)
                {
                    return new Iterator<T>();
                }
                else
                {
                    return new Iterator<T>(*this);
                }

                return ret;
            }

        private:
            htd::IteratorBase<T> * baseIterator_;

            Iterator<T>(const htd::IteratorBase<T> & original) : baseIterator_(original.clone())
            {

            }
    };
}

#endif /* HTD_HTD_ITERATOR_HPP */
