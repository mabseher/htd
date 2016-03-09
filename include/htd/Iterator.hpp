/* 
 * File:   Iterator.hpp
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

#ifndef HTD_HTD_ITERATOR_HPP
#define HTD_HTD_ITERATOR_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/IteratorWrapper.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <memory>

namespace htd
{
    template <typename T>
    class Iterator : public virtual htd::IteratorBase<T>
    {
        public:
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T & reference;
            typedef T * pointer;
            typedef const T & const_reference;
            typedef const T * const_pointer;
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

            Iterator<T>(Iterator<T> && original) : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = std::move(original.baseIterator_);

                    original.baseIterator_ = nullptr;
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

            Iterator<T> & operator=(const Iterator<T> & original)
            {
                if (baseIterator_!= nullptr)
                {
                    delete baseIterator_;
                }

                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = original.baseIterator_->clone();
                }

                return *this;
            }

            Iterator<T> & operator=(Iterator<T> && original)
            {
                if (baseIterator_!= nullptr)
                {
                    delete baseIterator_;
                }

                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = std::move(original.baseIterator_);

                    original.baseIterator_ = nullptr;
                }

                return *this;
            }

            bool operator==(const htd::IteratorBase<T> & rhs) const HTD_OVERRIDE
            {
                bool ret = false;

                const Iterator<T> * o = dynamic_cast<const Iterator<T> *>(&rhs);

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

            bool operator==(const Iterator<T> & rhs) const
            {
                bool ret = false;

                if (baseIterator_ == nullptr)
                {
                    ret = rhs.baseIterator_ == nullptr;
                }
                else if (rhs.baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ == *(rhs.baseIterator_ );
                }

                return ret;
            }

            bool operator!=(const htd::IteratorBase<T> & rhs) const HTD_OVERRIDE
            {
                return !(*this == rhs);
            }

            bool operator!=(const Iterator<T> & rhs) const
            {
                return !(*this == rhs);
            }

            T * operator->(void) HTD_OVERRIDE
            {
                return &(*(*(baseIterator_)));
            }

            const T * operator->(void) const
            {
                return &(*(*(baseIterator_)));
            }

            T & operator*(void) HTD_OVERRIDE
            {
                return *(*baseIterator_);
            }

            const T & operator*(void) const
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
