/* 
 * File:   VectorAdapter.hpp
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

#ifndef HTD_HTD_VECTORADAPTER_HPP
#define HTD_HTD_VECTORADAPTER_HPP

#include <htd/Globals.hpp>

#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/VectorAdapterIteratorWrapper.hpp>
#include <htd/VectorAdapterConstIteratorWrapper.hpp>

#include <htd/Algorithm.hpp>

#include <memory>
#include <vector>

namespace htd
{
    /**
     *  Adapter for instances of std::vector.
     *
     *  @note This adapter is necessary when it is desired to return a vector hidden behind an
     *  instance of htd::Collection and htd::ConstCollection from a function because otherwise
     *  the iterators used inside the collection wrappers are invalidated.
     */
    template <typename T, class Allocator = std::allocator<T>>
    class VectorAdapter
    {
        public:
            /**
             *  Constructor for an adapter of an empty vector.
             */
            VectorAdapter(void) : container_(std::make_shared<std::vector<T, Allocator>>())
            {

            }

            /**
             *  Constructor for an adapter of a vector.
             *
             *  @param[in] collection   The vector which shall be copied to the new adapter.
             */
            VectorAdapter(const std::vector<T> & collection) : container_(std::make_shared<std::vector<T, Allocator>>(collection))
            {

            }

            /**
             *  Constructor for an adapter of a vector.
             *
             *  @param[in] collection   The vector which shall be transferred to the new adapter.
             */
            VectorAdapter(std::vector<T> && collection) : container_(std::make_shared<std::vector<T, Allocator>>())
            {
                std::swap(collection, *container_);
            }

            /**
             *  Constructor for an adapter of a vector.
             *
             *  @param[in] collection   The vector which shall be copied to the new adapter.
             */
            VectorAdapter(const htd::ConstCollection<T> & collection) : container_(std::make_shared<std::vector<T, Allocator>>(collection.begin(), collection.end()))
            {

            }

            /**
             *  Copy constructor for an adapter of a vector.
             *
             *  @param[in] original  The original vector adapter.
             */
            VectorAdapter(const VectorAdapter<T> & original) : container_(original.container_)
            {

            }

            /**
             *  Move constructor for an adapter of a vector.
             *
             *  @param[in] original  The original vector adapter.
             */
            VectorAdapter(VectorAdapter<T> && original) : container_(std::move(original.container_))
            {

            }

            /**
             *  Destructor for a VectorAdapter object.
             */
            virtual ~VectorAdapter()
            {

            }

            /**
             *  Check whether the vector contains no elements.
             *
             *  @return True if the vector contains no elements, false otherwise.
             */
            bool empty(void) const
            {
                return container_->empty();
            }

            /**
             *  Getter for the number of elements of the vector.
             *
             *  @return The number of elements of the vector.
             */
            std::size_t size(void) const
            {
                return container_->size();
            }

            /**
             *  Access the underlying vector wrapped by the adapter.
             *
             *  @return The underlying vector wrapped by the adapter.
             */
            std::vector<T, Allocator> & container(void)
            {
                return *container_;
            }

            /**
             *  Access the underlying vector wrapped by the adapter.
             *
             *  @return The underlying vector wrapped by the adapter.
             */
            const std::vector<T, Allocator> & container(void) const
            {
                return *container_;
            }

            /**
             *  Getter for an iterator pointing to the first element in the vector.
             *
             *  @return An iterator pointing to the first element in the vector.
             */
            htd::Iterator<T> begin(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T, Allocator>::iterator, T, Allocator>(container_, container_->begin());
            }

            /**
             *  Getter for a const_iterator pointing to the first element in the vector.
             *
             *  @return A const_iterator pointing to the first element in the vector.
             */
            htd::ConstIterator<T> begin(void) const
            {
                return htd::ConstIterator<T>(static_cast<htd::ConstIteratorBase<T> *>(new htd::VectorAdapterConstIteratorWrapper<typename std::vector<T, Allocator>::const_iterator, T, Allocator>(container_, container_->begin())));
            }

            /**
             *  Getter for an iterator pointing to the end of the elements in the vector.
             *
             *  @return An iterator pointing to the end of the elements in the vector.
             */
            htd::Iterator<T> end(void)
            {
                return htd::VectorAdapterIteratorWrapper<typename std::vector<T, Allocator>::iterator, T, Allocator>(container_, container_->end());
            }

            /**
             *  Getter for a const_iterator pointing to the end of the elements in the vector.
             *
             *  @return A const_iterator pointing to the end of the elements in the vector.
             */
            htd::ConstIterator<T> end(void) const
            {
                return htd::ConstIterator<T>(static_cast<htd::ConstIteratorBase<T> *>(new htd::VectorAdapterConstIteratorWrapper<typename std::vector<T, Allocator>::const_iterator, T, Allocator>(container_, container_->end())));
            }

            /**
             *  Access the element at the specific position within the vector.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            T & operator[](htd::index_t index)
            {
                return container_->at(index);
            }

            /**
             *  Access the element at the specific position within the vector.
             *
             *  @param[in] index    The position of the element.
             *
             *  @return The element at the specific position.
             */
            const T & operator[](htd::index_t index) const
            {
                return container_->at(index);
            }

            /**
             *  Move assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original vector.
             */
            VectorAdapter<T, Allocator> & operator=(std::vector<T, Allocator> && original)
            {
                std::swap(original, *container_);

                return *this;
            }

            /**
             *  Copy assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original vector.
             */
            VectorAdapter<T, Allocator> & operator=(const VectorAdapter<T, Allocator> & original)
            {
                std::swap(original, *container_);

                return *this;
            }

            /**
             *  Move assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original vector.
             */
            VectorAdapter<T, Allocator> & operator=(VectorAdapter<T, Allocator> && original)
            {
                container_ = std::move(original.container_);

                return *this;
            }

            /**
             *  Copy assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original collection.
             */
            VectorAdapter<T, Allocator> & operator=(const htd::Collection<T> & original)
            {
                container_->clear();

                container_->insert(container_->end(), original.begin(), original.end());

                return *this;
            }

            /**
             *  Copy assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original collection.
             */
            VectorAdapter<T, Allocator> & operator=(const htd::ConstCollection<T> & original)
            {
                container_->clear();

                container_->insert(container_->end(), original.begin(), original.end());

                return *this;
            }

            /**
             *  Copy assignment operator for an adapter of a vector.
             *
             *  @param[in] original  The original collection.
             */
            template <typename CollectionType>
            VectorAdapter<T, Allocator> & operator=(const CollectionType & original)
            {
                container_->clear();

                container_->insert(container_->end(), original.begin(), original.end());

                return *this;
            }

            /**
             *  Equality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is equal to
             *          the collection at the right-hand side of the operator, false otherwise.
             */
            inline bool operator==(const VectorAdapter<T, Allocator> & rhs) const
            {
                return *container_ == *(rhs.container_);
            }

            /**
             *  Equality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is equal to
             *          the collection at the right-hand side of the operator, false otherwise.
             */
            inline bool operator==(const htd::Collection<T> & rhs) const
            {
                return size() == rhs.size() && htd::equal(begin(), end(), rhs.begin(), rhs.end());
            }

            /**
             *  Equality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is equal to
             *          the collection at the right-hand side of the operator, false otherwise.
             */
            inline bool operator==(const htd::ConstCollection<T> & rhs) const
            {
                return size() == rhs.size() && htd::equal(begin(), end(), rhs.begin(), rhs.end());
            }

            /**
             *  Inequality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is not equal
             *          to the collection at the right-hand side of the operator, false
             *          otherwise.
             */
            inline bool operator!=(const VectorAdapter<T, Allocator> & rhs) const
            {
                return *container_ != *(rhs.container_);
            }

            /**
             *  Inequality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is not equal
             *          to the collection at the right-hand side of the operator, false
             *          otherwise.
             */
            inline bool operator!=(const htd::Collection<T> & rhs) const
            {
                return !(*this == rhs);
            }

            /**
             *  Inequality operator for an adapter of a vector.
             *
             *  @param[in] rhs  The collection at the right-hand side of the operator.
             *
             *  @return True if the collection of elements in the wrapped vector is not equal
             *          to the collection at the right-hand side of the operator, false
             *          otherwise.
             */
            inline bool operator!=(const htd::ConstCollection<T> & rhs) const
            {
                return !(*this == rhs);
            }

        private:
            std::shared_ptr<std::vector<T, Allocator>> container_;
    };
}

#endif /* HTD_HTD_VECTORADAPTER_HPP */
