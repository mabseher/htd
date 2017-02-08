/* 
 * File:   ConstCollection.hpp
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

#ifndef HTD_HTD_CONSTCOLLECTION_HPP
#define HTD_HTD_CONSTCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ConstIterator.hpp>

#include <htd/Algorithm.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Wrapper for immutable collections.
     */
    template <typename T>
    class ConstCollection
    {
        public:
            /**
             *  The value type of the collection.
             */
            typedef T value_type;

            /**
             *  Constructor for a ConstCollection object representing an empty collection.
             */
            ConstCollection(void) HTD_NOEXCEPT : begin_(), end_(), size_(0)
            {

            }

            /**
             *  Constructor for a ConstCollection object wrapping the given region of a collection.
             *
             *  @param[in] begin    The begin of the collection to be wrapped.
             *  @param[in] end      The end of the collection to be wrapped.
             */
            ConstCollection(const htd::ConstIterator<T> & begin, const htd::ConstIterator<T> & end) HTD_NOEXCEPT : begin_(begin), end_(end), size_(std::distance(begin, end))
            {

            }

            /**
             *  Copy constructor for a ConstCollection object.
             *
             *  @param[in] original  The original ConstCollection object.
             */
            ConstCollection(const htd::ConstCollection<T> & original) HTD_NOEXCEPT : begin_(original.begin_), end_(original.end_), size_(original.size_)
            {

            }

            /**
             *  Move constructor for a ConstCollection object.
             *
             *  @param[in] original  The original ConstCollection object.
             */
            ConstCollection(htd::ConstCollection<T> && original) HTD_NOEXCEPT : begin_(std::move(original.begin_)), end_(std::move(original.end_)), size_(original.size_)
            {

            }

            /**
             *  Destructor for a ConstCollection object.
             */
            virtual ~ConstCollection()
            {

            }

            /**
             *  Check whether the collection is emtpy.
             *
             *  @return True if the collection is empty, false otherwise.
             */
            bool empty(void) const HTD_NOEXCEPT
            {
                return begin_ == end_;
            }

            /**
             *  Getter for the size of the collection.
             *
             *  @return The size of the collection.
             */
            std::size_t size(void) const HTD_NOEXCEPT
            {
                return size_;
            }

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            htd::ConstIterator<T> begin(void) const HTD_NOEXCEPT
            {
                return begin_;
            }

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            htd::ConstIterator<T> end(void) const HTD_NOEXCEPT
            {
                return end_;
            }

            /**
             *  Access the element at the specific position within the collection.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            const T & operator[](htd::index_t index) const
            {
                htd::ConstIterator<T> position = begin_;

                std::advance(position, index);

                return *position;
            }

            /**
             *  Copy assignment operator for a ConstCollection object.
             *
             *  @param[in] original  The original ConstCollection object.
             */
            ConstCollection<T> & operator=(const ConstCollection<T> & original) HTD_NOEXCEPT
            {
                begin_ = original.begin_;
                end_ = original.end_;

                return *this;
            }

            /**
             *  Move assignment operator for a ConstCollection object.
             *
             *  @param[in] original  The original ConstCollection object.
             */
            ConstCollection<T> & operator=(ConstCollection<T> && original) HTD_NOEXCEPT
            {
                begin_ = std::move(original.begin_);
                end_ = std::move(original.end_);

                return *this;
            }

            /**
             *  Copy assignment operator for a ConstCollection object.
             *
             *  @param[in] original  The original collection.
             */
            template <typename CollectionType>
            ConstCollection<T> & operator=(CollectionType & original)
            {
                begin_ = original.begin();
                end_ = original.end();

                return *this;
            }

            /**
             *  Equality operator for a collection.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection is equal to the collection at the right-hand side of the operator, false otherwise.
             */
            inline bool operator==(const htd::ConstCollection<T> & rhs) const HTD_NOEXCEPT
            {
                return size() == rhs.size() && htd::equal(begin(), end(), rhs.begin(), rhs.end());
            }

            /**
             *  Inequality operator for a collection.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection is not equal to the collection at the right-hand side of the operator, false otherwise.
             */
            inline bool operator!=(const htd::ConstCollection<T> & rhs) const HTD_NOEXCEPT
            {
                return size() != rhs.size() || !htd::equal(begin(), end(), rhs.begin(), rhs.end());
            }

            /**
             *  Create a new ConstCollection object wrapping the provided collection.
             *
             *  @param[in] collection   The collection which shall be wrapped.
             */
            template <typename CollectionType>
            static ConstCollection<T> getInstance(const CollectionType & collection)
            {
                return ConstCollection<T>(std::begin(collection), std::end(collection), collection.size());
            }

        private:
            /**
             *  An iterator to the first element of the collection.
             */
            htd::ConstIterator<T> begin_;

            /**
             *  An iterator to the end of the collection.
             */
            htd::ConstIterator<T> end_;

            std::size_t size_;

            ConstCollection(const htd::ConstIterator<T> & begin, const htd::ConstIterator<T> & end, std::size_t size) : begin_(begin), end_(end), size_(size)
            {

            }

            ConstCollection(htd::ConstIterator<T> && begin, htd::ConstIterator<T> && end, std::size_t size) : begin_(std::move(begin)), end_(std::move(end)), size_(size)
            {

            }
    };
}

#endif /* HTD_HTD_CONSTCOLLECTION_HPP */
