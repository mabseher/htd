/* 
 * File:   Collection.hpp
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

#ifndef HTD_HTD_COLLECTION_HPP
#define HTD_HTD_COLLECTION_HPP

#include <htd/Globals.hpp>

#include <htd/Iterator.hpp>

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

            template <typename CollectionType>
            Collection(const CollectionType & collection) : begin_(std::begin(collection)), end_(std::end(collection))
            {

            }

            virtual ~Collection()
            {

            }

            std::size_t size() const
            {
                return std::distance(begin(), end());
            }

            htd::Iterator<T> begin(void)
            {
                return begin_;
            }

            const htd::Iterator<T> begin(void) const
            {
                return begin_;
            }

            htd::Iterator<T> end(void)
            {
                return end_;
            }

            const htd::Iterator<T> end(void) const
            {
                return end_;
            }

        private:
            Iterator<T> begin_;
            Iterator<T> end_;
    };
}

#endif /* HTD_HTD_COLLECTION_HPP */
