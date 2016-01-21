/*
 * File:   Collection.hpp
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

#ifndef HTD_HTD_COLLECTION_HPP
#define HTD_HTD_COLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>

#include <algorithm>
#include <iterator>

namespace htd
{
    template <typename T>
    class Collection
    {
        public:
            typedef T value_type;

            Collection(void) : begin_(), end_()
            {

            }

            Collection(const Iterator<T> & begin, const Iterator<T> & end) : begin_(begin), end_(end)
            {

            }

            Collection(const htd::Collection<T> & original) : begin_(original.begin_), end_(original.end_)
            {

            }

            Collection(htd::Collection<T> && original) : begin_(std::move(original.begin_)), end_(std::move(original.end_))
            {

            }

            ~Collection()
            {

            }

            bool empty() const
            {
                return begin_ == end_;
            }

            std::size_t size() const
            {
                return std::distance(begin_, end_);
            }

            htd::Iterator<T> begin(void)
            {
                return begin_;
            }

            htd::ConstIterator<T> begin(void) const
            {
                return begin_;
            }

            htd::Iterator<T> end(void)
            {
                return end_;
            }

            htd::ConstIterator<T> end(void) const
            {
                return end_;
            }

            T & operator[](htd::index_t index)
            {
                htd::Iterator<htd::vertex_t> position = begin_;

                std::advance(position, index);

                return *position;
            }

            const T & operator[](htd::index_t index) const
            {
                htd::Iterator<htd::vertex_t> position = begin_;

                std::advance(position, index);

                return *position;
            }

            Collection<T> & operator=(Collection<T> & rhs)
            {
                begin_ = rhs.begin_;
                end_ = rhs.end_;

                return *this;
            }

            template <typename CollectionType>
            Collection<T> & operator=(CollectionType & rhs)
            {
                begin_ = rhs.begin();
                end_ = rhs.end();

                return *this;
            }

            inline bool operator==(const Collection<T> & rhs) const
            {
                return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
            }

            inline bool operator!=(const Collection<T> & rhs) const
            {
                return !(*this == rhs);
            }

            template <typename CollectionType>
            static Collection<T> getInstance(CollectionType & collection)
            {
                return Collection<T>(std::begin(collection), std::end(collection));
            }

        private:
            htd::Iterator<T> begin_;
            htd::Iterator<T> end_;
    };
}

#endif /* HTD_HTD_COLLECTION_HPP */
