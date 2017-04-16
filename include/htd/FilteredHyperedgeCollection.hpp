/*
 * File:   FilteredHyperedgeCollection.hpp
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

#ifndef HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP
#define HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP

#include <htd/Globals.hpp>

#include <htd/Hyperedge.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/IHyperedgeCollection.hpp>

#include <array>
#include <memory>
#include <vector>

namespace htd
{
    /**
     *  Class for the efficient storage of hyperedge collections based on existing vectors of hyperedges.
     */
    class FilteredHyperedgeCollection
    {
        public:
            /**
             *  The value type of the collection.
             */
            typedef htd::Hyperedge value_type;

            /**
             *  Custom read-only iterator for hyperedge collections.
             */
            class FilteredHyperedgeCollectionConstIterator
            {
                public:
                    /**
                     *  The difference type between two iterators.
                     */
                    typedef std::ptrdiff_t difference_type;

                    /**
                     *  The value type of the iterator.
                     */
                    typedef htd::Hyperedge value_type;

                    /**
                     *  The reference type of the iterator.
                     */
                    typedef const htd::Hyperedge & reference;

                    /**
                     *  The pointer type of the iterator.
                     */
                    typedef const htd::Hyperedge * pointer;

                    /**
                     *  The const_reference type of the iterator.
                     */
                    typedef const htd::Hyperedge & const_reference;

                    /**
                     *  The const_pointer type of the iterator.
                     */
                    typedef const htd::Hyperedge * const_pointer;

                    /**
                     *  The category of the iterator.
                     */
                    typedef std::random_access_iterator_tag iterator_category;

                    /**
                     *  Constructor for an iterator.
                     *
                     *  @param[in] collection   The underlying collection.
                     *  @param[in] position     The position of the new iterator within the collection.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator(const FilteredHyperedgeCollection & collection, htd::index_t position);

                    /**
                     *  Copy constructor for a FilteredHyperedgeCollectionConstIterator object.
                     *
                     *  @param[in] original  The original FilteredHyperedgeCollectionConstIterator object.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator(const FilteredHyperedgeCollectionConstIterator & original);

                    /**
                     *  Move constructor for a FilteredHyperedgeCollectionConstIterator object.
                     *
                     *  @param[in] original  The original FilteredHyperedgeCollectionConstIterator object.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator(FilteredHyperedgeCollectionConstIterator && original);

                    /**
                     *  Destructor for a FilteredHyperedgeCollectionConstIterator object.
                     */
                    HTD_API virtual ~FilteredHyperedgeCollectionConstIterator();

                    /**
                     *  Increment the iterator.
                     *
                     *  @return A reference to the incremented iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator++(void);

                    /**
                     *  Increment the iterator.
                     *
                     *  @return A copy of the iterator reflecting the state before the increment operation took place.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator operator++(int);

                    /**
                     *  Increment the iterator.
                     *
                     *  @param[in] positions    The number of positions the iterator shall be incremented.
                     *
                     *  @return A reference to the incremented iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator+=(std::size_t positions);

                    /**
                     *  Decrement the iterator.
                     *
                     *  @return A reference to the decremented iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator--(void);

                    /**
                     *  Decrement the iterator.
                     *
                     *  @return A copy of the iterator reflecting the state before the decrement operation took place.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator operator--(int);

                    /**
                     *  Decrement the iterator.
                     *
                     *  @param[in] positions    The number of positions the iterator shall be decremented.
                     *
                     *  @return A reference to the decremented iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator-=(std::size_t positions);

                    /**
                     *  Compute the distance between two iterators.
                     *
                     *  The distance is given by the difference between the position of the iterator at the
                     *  right-hand side of the operator and the position of the iterator at the left-hand
                     *  side of the operator.
                     *
                     *  @param[in] rhs  The iterator at the right-hand side of the operator.
                     *
                     *  @return The distance between two iterators.
                     */
                    HTD_API long operator-(const FilteredHyperedgeCollectionConstIterator & rhs);

                    /**
                     *  Copy assignment operator for an iterator.
                     *
                     *  @param[in] original  The original iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator=(const FilteredHyperedgeCollectionConstIterator & original);

                    /**
                     *  Move assignment operator for an iterator.
                     *
                     *  @param[in] original  The original iterator.
                     */
                    HTD_API FilteredHyperedgeCollectionConstIterator & operator=(FilteredHyperedgeCollectionConstIterator && original);

                    /**
                     *  Equality operator for an iterator.
                     *
                     *  @param[in] rhs  The iterator at the right-hand side of the operator.
                     *
                     *  @return True if the iterator points to the same element as the iterator at the right-hand side of the operator, false otherwise.
                     */
                    HTD_API bool operator==(const FilteredHyperedgeCollectionConstIterator & rhs) const;

                    /**
                     *  Inequality operator for an iterator.
                     *
                     *  @param[in] rhs  The iterator at the right-hand side of the operator.
                     *
                     *  @return True if the iterator does not point to the same element as the iterator at the right-hand side of the operator, false otherwise.
                     */
                    HTD_API bool operator!=(const FilteredHyperedgeCollectionConstIterator & rhs) const;

                    /**
                     *  Dereference the iterator.
                     *
                     *  @return A pointer to the element at the current iterator position.
                     */
                    HTD_API const htd::Hyperedge * operator->(void) const;

                    /**
                     *  Dereference the iterator.
                     *
                     *  @return A reference to the element at the current iterator position.
                     */
                    HTD_API const htd::Hyperedge & operator*(void) const;

                private:
                    std::shared_ptr<htd::IHyperedgeCollection> baseCollection_;

                    std::shared_ptr<std::vector<htd::index_t>> relevantIndices_;

                    htd::index_t position_;
            };

            /**
             *  Constructor for a FilteredHyperedgeCollection object representing an empty collection.
             */
            HTD_API FilteredHyperedgeCollection(void) HTD_NOEXCEPT;

            /**
             *  Constructor for a FilteredHyperedgeCollection.
             *
             *  @param[in] baseCollection   A pointer to a wrapper of the underlying hyperedge collection.
             *  @param[in] relevantIndices  The relevant indices within the hyperedge collection.
             *
             *  @note When calling this constructor the control over the pointer to the wrapper of the base collection
             *  is taken over by the hyperedge collection. The pointer of the provided wrapper of the base collection
             *  must not be freed outside the context of the hyperedge collection.
             */
            HTD_API FilteredHyperedgeCollection(htd::IHyperedgeCollection * baseCollection, const std::vector<htd::index_t> & relevantIndices);

            /**
             *  Constructor for a FilteredHyperedgeCollection.
             *
             *  @param[in] baseCollection   A pointer to a wrapper of the underlying hyperedge collection.
             *  @param[in] relevantIndices  The relevant indices within the hyperedge collection.
             *
             *  @note When calling this constructor the control over the pointer to the wrapper of the base collection
             *  is taken over by the hyperedge collection. The pointer of the provided wrapper of the base collection
             *  must not be freed outside the context of the hyperedge collection.
             */
            HTD_API FilteredHyperedgeCollection(htd::IHyperedgeCollection * baseCollection, std::vector<htd::index_t> && relevantIndices);

            /**
             *  Constructor for a FilteredHyperedgeCollection.
             *
             *  @param[in] baseCollection   A pointer to a wrapper of the underlying hyperedge collection.
             *  @param[in] relevantIndices  The relevant indices within the hyperedge collection.
             *
             *  @note When calling this constructor the control over the pointer to the wrapper of the base collection
             *  is taken over by the hyperedge collection. The pointer of the provided wrapper of the base collection
             *  must not be freed outside the context of the hyperedge collection.
             */
            HTD_API FilteredHyperedgeCollection(std::shared_ptr<htd::IHyperedgeCollection> baseCollection, const std::vector<htd::index_t> & relevantIndices);

            /**
             *  Constructor for a FilteredHyperedgeCollection.
             *
             *  @param[in] baseCollection   A pointer to a wrapper of the underlying hyperedge collection.
             *  @param[in] relevantIndices  The relevant indices within the hyperedge collection.
             *
             *  @note When calling this constructor the control over the pointer to the wrapper of the base collection
             *  is taken over by the hyperedge collection. The pointer of the provided wrapper of the base collection
             *  must not be freed outside the context of the hyperedge collection.
             */
            HTD_API FilteredHyperedgeCollection(std::shared_ptr<htd::IHyperedgeCollection> baseCollection, std::vector<htd::index_t> && relevantIndices);

            /**
             *  Copy constructor for a FilteredHyperedgeCollection object.
             *
             *  @param[in] original  The original FilteredHyperedgeCollection object.
             */
            HTD_API FilteredHyperedgeCollection(const FilteredHyperedgeCollection & original) HTD_NOEXCEPT;

            /**
             *  Move constructor for a FilteredHyperedgeCollection object.
             *
             *  @param[in] original  The original FilteredHyperedgeCollection object.
             */
            HTD_API FilteredHyperedgeCollection(FilteredHyperedgeCollection && original) HTD_NOEXCEPT;

            /**
             *  Destructor for a FilteredHyperedgeCollection object.
             */
            HTD_API virtual ~FilteredHyperedgeCollection();

            /**
             *  Getter for the size of the collection.
             *
             *  @return The size of the collection.
             */
            HTD_API std::size_t size(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            HTD_API FilteredHyperedgeCollectionConstIterator begin(void) const HTD_NOEXCEPT;

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            HTD_API FilteredHyperedgeCollectionConstIterator end(void) const HTD_NOEXCEPT;

            /**
             *  Copy assignment operator for a FilteredHyperedgeCollection object.
             *
             *  @param[in] original  The original FilteredHyperedgeCollection object.
             */
            HTD_API FilteredHyperedgeCollection & operator=(const FilteredHyperedgeCollection & original) HTD_NOEXCEPT;

            /**
             *  Move assignment operator for a FilteredHyperedgeCollection object.
             *
             *  @param[in] original  The original FilteredHyperedgeCollection object.
             */
            HTD_API FilteredHyperedgeCollection & operator=(FilteredHyperedgeCollection && original) HTD_NOEXCEPT;

            /**
             *  Equality operator for a hyperedge collection.
             *
             *  @param[in] rhs  The hyperedge collection at the right-hand side of the operator.
             *
             *  @return True if the hyperedge collection is equal to the hyperedge collection at the right-hand side of the operator, false otherwise.
             */
            HTD_API bool operator==(const FilteredHyperedgeCollection & rhs) const HTD_NOEXCEPT;

            /**
             *  Inequality operator for a hyperedge collection.
             *
             *  @param[in] rhs  The hyperedge collection at the right-hand side of the operator.
             *
             *  @return True if the hyperedge collection is not equal to the hyperedge collection at the right-hand side of the operator, false otherwise.
             */
            HTD_API bool operator!=(const FilteredHyperedgeCollection & rhs) const HTD_NOEXCEPT;

            /**
             *  Remove all hyperedges from the collection which contain also other vertices than those provided to this method.
             *
             *  @note The copy will contain only those hyperedges whose endpoints are a subset of the relevant vertices.
             *
             *  @param[in] vertices The vertices which act as a filter for the hyperedges in the collection.
             */
            HTD_API void restrictTo(const std::vector<htd::vertex_t> & vertices);

            /**
             *  Create a deep copy of the current hyperedge collection.
             *
             *  @return A new FilteredHyperedgeCollection object identical to the current hyperedge collection.
             */
            HTD_API FilteredHyperedgeCollection * clone(void) const;

            /**
             *  Create a deep copy of the current hyperedge collection.
             *
             *  @note The copy will contain only those hyperedges whose endpoints are a subset of the relevant vertices.
             *
             *  @param[in] relevantVertices The set of relevant vertices, sorted in strictly ascending order.
             *
             *  @return A new FilteredHyperedgeCollection object whose content is restricted to the relevant vertices.
             */
            HTD_API FilteredHyperedgeCollection * clone(const std::vector<htd::vertex_t> & relevantVertices) const;

            /**
             *  Swap the contents of a FilteredHyperedgeCollection object and another.
             *
             *  @param[in] other    The FilteredHyperedgeCollection object which shall be swapped with this object.
             */
            HTD_API void swap(FilteredHyperedgeCollection & other);

        private:
            std::shared_ptr<htd::IHyperedgeCollection> baseCollection_;

            std::shared_ptr<std::vector<htd::index_t>> relevantIndices_;
    };
}

#endif /* HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP */
