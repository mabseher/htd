/* 
 * File:   Iterator.hpp
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

#ifndef HTD_HTD_ITERATOR_HPP
#define HTD_HTD_ITERATOR_HPP

#include <htd/Globals.hpp>

#include <htd/IteratorBase.hpp>
#include <htd/IteratorWrapper.hpp>
#include <htd/ConstIteratorBase.hpp>

#include <memory>

namespace htd
{
    /**
     *  Wrapper for iterators of immutable collections.
     */
    template <typename T>
    class Iterator : public htd::IteratorBase<T>
    {
        public:
            /**
             *  The difference type between two iterators.
             */
            typedef std::ptrdiff_t difference_type;

            /**
             *  The value type of the iterator.
             */
            typedef T value_type;

            /**
             *  The reference type of the iterator.
             */
            typedef T & reference;

            /**
             *  The pointer type of the iterator.
             */
            typedef T * pointer;

            /**
             *  The const_reference type of the iterator.
             */
            typedef const T & const_reference;

            /**
             *  The const_pointer type of the iterator.
             */
            typedef const T * const_pointer;

            /**
             *  The category of the iterator.
             */
            typedef std::forward_iterator_tag iterator_category;

            /**
             *  Constructor for an iterator pointing nowhere.
             */
            Iterator(void) : baseIterator_(nullptr)
            {

            }

            /**
             *  Constructor for an iterator.
             *
             *  @param[in] iterator The underlying iterator.
             */
            template <class Iter>
            Iterator(Iter iterator) : baseIterator_(new IteratorWrapper<Iter, T>(iterator))
            {

            }

            /**
             *  Copy constructor for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            Iterator<T>(const Iterator<T> & original) : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = original.baseIterator_->clone();
                }
            }

            /**
             *  Move constructor for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
            Iterator<T>(Iterator<T> && original) : baseIterator_(nullptr)
            {
                if (original.baseIterator_ != nullptr)
                {
                    baseIterator_ = std::move(original.baseIterator_);

                    original.baseIterator_ = nullptr;
                }
            }

            /**
             *  Destructor for an Iterator object.
             */
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

            /**
             *  Increment the iterator.
             *
             *  @return A copy of the iterator reflecting the state before the increment operation took place.
             */
            Iterator<T> operator++(int)
            {
                Iterator<T> ret(*baseIterator_);

                operator++();

                return ret;
            }

            /**
             *  Copy assignment operator for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
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

            /**
             *  Move assignment operator for an iterator.
             *
             *  @param[in] original  The original iterator.
             */
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

                const Iterator<T> * o = static_cast<const Iterator<T> *>(&rhs);

                if (baseIterator_ == nullptr)
                {
                    ret = o->baseIterator_ == nullptr;
                }
                else if (o->baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ == *(o->baseIterator_ );
                }

                return ret;
            }

            /**
             *  Equality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
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
                bool ret = false;

                const Iterator<T> * o = static_cast<const Iterator<T> *>(&rhs);

                if (baseIterator_ == nullptr)
                {
                    ret = o->baseIterator_ != nullptr;
                }
                else if (o->baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ != *(o->baseIterator_ );
                }

                return ret;
            }

            /**
             *  Inequality operator for an iterator.
             *
             *  @param[in] rhs  The iterator at the right-hand side of the operator.
             *
             *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
             */
            bool operator!=(const Iterator<T> & rhs) const
            {
                bool ret = false;

                if (baseIterator_ == nullptr)
                {
                    ret = rhs.baseIterator_ != nullptr;
                }
                else if (rhs.baseIterator_ != nullptr)
                {
                    ret = *baseIterator_ != *(rhs.baseIterator_ );
                }

                return ret;
            }

            T * operator->(void) HTD_OVERRIDE
            {
                return baseIterator_->operator->();
            }

            /**
             *  Dereference the iterator.
             *
             *  @return A pointer to the element at the current iterator position.
             */
            const T * operator->(void) const
            {
                return baseIterator_->operator->();
            }

            T & operator*(void) HTD_OVERRIDE
            {
                return baseIterator_->operator*();
            }

            /**
             *  Dereference the iterator.
             *
             *  @return A reference to the element at the current iterator position.
             */
            const T & operator*(void) const
            {
                return baseIterator_->operator*();
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
