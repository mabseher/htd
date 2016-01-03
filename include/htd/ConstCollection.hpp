/* 
 * File:   ConstCollection.hpp
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

#ifndef HTD_HTD_CONSTCOLLECTION_HPP
#define HTD_HTD_CONSTCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/Iterator.hpp>

#include <algorithm>
#include <iterator>

namespace htd
{
    template <typename T>
    class ConstCollection
    {
        public:
            typedef T value_type;

            ConstCollection(void) : begin_(), end_()
            {

            }

            ConstCollection(const htd::ConstIterator<T> & begin, const htd::ConstIterator<T> & end) : begin_(begin), end_(end)
            {

            }

            template <typename CollectionType>
            ConstCollection(const CollectionType & collection) : begin_(std::begin(collection)), end_(std::end(collection))
            {

            }

            ~ConstCollection()
            {

            }

            bool empty() const
            {
                return begin_ == end_;
            }

            std::size_t size() const
            {
                return std::distance(begin(), end());
            }

            htd::ConstIterator<T> begin(void) const
            {
                return begin_;
            }

            htd::ConstIterator<T> end(void) const
            {
                return end_;
            }

            const T & operator[](htd::index_t index) const
            {
                htd::ConstIterator<T> position = begin_;

                std::advance(position, index);

                return *position;
            }

            ConstCollection<T> & operator=(const ConstCollection<T> & rhs)
            {
                begin_ = rhs.begin_;
                end_ = rhs.end_;

                return *this;
            }

            template <typename CollectionType>
            ConstCollection<T> & operator=(CollectionType & rhs)
            {
                begin_ = rhs.begin();
                end_ = rhs.end();

                return *this;
            }

            inline bool operator==(const htd::ConstCollection<T> & rhs) const
            {
                return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
            }

            inline bool operator!=(const htd::ConstCollection<T> & rhs) const
            {
                return !(*this == rhs);
            }

        private:
            htd::ConstIterator<T> begin_;
            htd::ConstIterator<T> end_;
    };
}

#endif /* HTD_HTD_CONSTCOLLECTION_HPP */
