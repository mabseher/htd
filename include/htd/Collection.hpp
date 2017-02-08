/*
 * File:   Collection.hpp
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

#ifndef HTD_HTD_COLLECTION_HPP
#define HTD_HTD_COLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>

#include <htd/Algorithm.hpp>

#include <iterator>

namespace htd
{
    /**
     *  Wrapper for collections.
     */
    template <typename T>
    class Collection
    {
        public:
            /**
             *  The value type of the collection.
             */
            typedef T value_type;

            /**
             *  Constructor for a Collection object representing an empty collection.
             */
            Collection(void) : begin_(), end_()
            {

            }

            /**
             *  Constructor for a Collection object wrapping the given region of a collection.
             *
             *  @param[in] begin    The begin of the collection to be wrapped.
             *  @param[in] end      The end of the collection to be wrapped.
             */
            Collection(const Iterator<T> & begin, const Iterator<T> & end) : begin_(begin), end_(end)
            {

            }

            /**
             *  Copy constructor for a Collection object.
             *
             *  @param[in] original  The original Collection object.
             */
            Collection(const htd::Collection<T> & original) : begin_(original.begin_), end_(original.end_)
            {

            }

            /**
             *  Move constructor for a Collection object.
             *
             *  @param[in] original  The original Collection object.
             */
            Collection(htd::Collection<T> && original) : begin_(std::move(original.begin_)), end_(std::move(original.end_))
            {

            }

            /**
             *  Destructor for a Collection object.
             */
            virtual ~Collection()
            {

            }

            /**
             *  Check whether the collection is emtpy.
             *
             *  @return True if the collection is empty, false otherwise.
             */
            bool empty() const
            {
                return begin_ == end_;
            }

            /**
             *  Getter for the size of the collection.
             *
             *  @return The size of the collection.
             */
            std::size_t size() const
            {
                return std::distance(begin_, end_);
            }

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            htd::Iterator<T> begin(void)
            {
                return begin_;
            }

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            htd::ConstIterator<T> begin(void) const
            {
                return begin_;
            }

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            htd::Iterator<T> end(void)
            {
                return end_;
            }

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            htd::ConstIterator<T> end(void) const
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
            T & operator[](htd::index_t index)
            {
                htd::Iterator<htd::vertex_t> position = begin_;

                std::advance(position, index);

                return *position;
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
                htd::Iterator<htd::vertex_t> position = begin_;

                std::advance(position, index);

                return *position;
            }

            /**
             *  Copy assignment operator for a Collection object.
             *
             *  @param[in] original  The original Collection object.
             */
            Collection<T> & operator=(const Collection<T> & original)
            {
                begin_ = original.begin_;
                end_ = original.end_;

                return *this;
            }

            /**
             *  Move assignment operator for a Collection object.
             *
             *  @param[in] original  The original Collection object.
             */
            Collection<T> & operator=(Collection<T> && original)
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
            Collection<T> & operator=(CollectionType & original)
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
            inline bool operator==(const Collection<T> & rhs) const
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
            inline bool operator!=(const Collection<T> & rhs) const
            {
                return !(*this == rhs);
            }

            /**
             *  Create a new Collection object wrapping the provided collection.
             *
             *  @param[in] collection   The collection which shall be wrapped.
             */
            template <typename CollectionType>
            static Collection<T> getInstance(CollectionType & collection)
            {
                return Collection<T>(std::begin(collection), std::end(collection));
            }

        private:
            /**
             *  An iterator to the first element of the collection.
             */
            htd::Iterator<T> begin_;

            /**
             *  An iterator to the end of the collection.
             */
            htd::Iterator<T> end_;
    };
}

#endif /* HTD_HTD_COLLECTION_HPP */
