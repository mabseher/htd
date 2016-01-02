/* 
 * File:   VectorAdapter.hpp
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

#ifndef HTD_HTD_VECTORADAPTER_HPP
#define HTD_HTD_VECTORADAPTER_HPP

#include <htd/Globals.hpp>

#include <htd/ConstCollection.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/VectorAdapterIteratorWrapper.hpp>
#include <htd/VectorAdapterConstIteratorWrapper.hpp>

#include <memory>
#include <vector>

namespace htd
{
    template <typename T, class Allocator = std::allocator<T>>
    class VectorAdapter
    {
        public:
            VectorAdapter(void) : container_(std::make_shared<std::vector<T, Allocator>>())
            {

            }

            VectorAdapter(const std::vector<T> & collection) : container_(std::make_shared<std::vector<T, Allocator>>(collection))
            {

            }

            VectorAdapter(const htd::ConstCollection<T> & collection) : container_(std::make_shared<std::vector<T, Allocator>>(collection.begin(), collection.end()))
            {

            }

            virtual ~VectorAdapter()
            {

            }

            bool empty() const
            {
                return container_->empty();
            }

            std::size_t size() const
            {
                return container_->size();
            }

            std::vector<T, Allocator> & container()
            {
                return *container_;
            }

            const std::vector<T, Allocator> & container() const
            {
                return *container_;
            }

            htd::Iterator<T> begin(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T, Allocator>::iterator, T, Allocator>(container_, container_->begin());
            }

            const htd::ConstIterator<T> begin(void) const
            {
                return htd::VectorAdapterConstIteratorWrapper<typename std::vector<T, Allocator>::const_iterator, T, Allocator>(container_, container_->begin());
            }

            htd::Iterator<T> end(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T, Allocator>::iterator, T, Allocator>(container_, container_->end());
            }

            const htd::ConstIterator<T> end(void) const
            {
                return htd::VectorAdapterConstIteratorWrapper<typename std::vector<T, Allocator>::const_iterator, T, Allocator>(container_, container_->end());
            }

            T & operator[](htd::index_t index)
            {
                return container_->at(index);
            }

            const T & operator[](htd::index_t index) const
            {
                return container_->at(index);
            }

            VectorAdapter<T, Allocator> & operator=(htd::Collection<T> & rhs)
            {
                container_->clear();

                std::copy(rhs.begin(), rhs.end(), std::back_inserter(*container_));

                return *this;
            }

            VectorAdapter<T, Allocator> & operator=(const htd::ConstCollection<T> & rhs)
            {
                container_->clear();

                std::copy(rhs.begin(), rhs.end(), std::back_inserter(*container_));

                return *this;
            }

            template <typename CollectionType>
            VectorAdapter<T, Allocator> & operator=(const CollectionType & rhs)
            {
                container_->clear();

                std::copy(rhs.begin(), rhs.end(), std::back_inserter(*container_));

                return *this;
            }

            inline bool operator==(const htd::Collection<T> & rhs) const
            {
                return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
            }

            inline bool operator!=(const htd::Collection<T> & rhs) const
            {
                return !(*this == rhs);
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
            std::shared_ptr<std::vector<T, Allocator>> container_;
    };
}

#endif /* HTD_HTD_VECTORADAPTER_HPP */
