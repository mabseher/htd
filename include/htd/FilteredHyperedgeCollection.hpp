/*
 * File:   FilteredHyperedgeCollection.hpp
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

#ifndef HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP
#define	HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP

#include <htd/Globals.hpp>

#include <htd/Hyperedge.hpp>
#include <htd/ConstCollection.hpp>

#include <array>
#include <memory>
#include <vector>

namespace htd
{
    class FilteredHyperedgeCollection
    {
        public:
            typedef htd::Hyperedge value_type;

            class FilteredHyperedgeCollectionConstIterator
            {
                public:
                    typedef std::ptrdiff_t difference_type;
                    typedef htd::Hyperedge value_type;
                    typedef const htd::Hyperedge & reference;
                    typedef const htd::Hyperedge * pointer;
                    typedef const htd::Hyperedge & const_reference;
                    typedef const htd::Hyperedge * const_pointer;
                    typedef std::random_access_iterator_tag iterator_category;

                    FilteredHyperedgeCollectionConstIterator(const FilteredHyperedgeCollection & collection, htd::index_t position);

                    FilteredHyperedgeCollectionConstIterator(const FilteredHyperedgeCollectionConstIterator & original);

                    FilteredHyperedgeCollectionConstIterator(FilteredHyperedgeCollectionConstIterator && original);

                    ~FilteredHyperedgeCollectionConstIterator();

                    FilteredHyperedgeCollectionConstIterator & operator++(void);

                    FilteredHyperedgeCollectionConstIterator operator++(int);

                    FilteredHyperedgeCollectionConstIterator & operator+=(std::size_t positions);

                    FilteredHyperedgeCollectionConstIterator & operator--(void);

                    FilteredHyperedgeCollectionConstIterator operator--(int);

                    FilteredHyperedgeCollectionConstIterator & operator-=(std::size_t positions);

                    long operator-(const FilteredHyperedgeCollectionConstIterator & rhs);

                    FilteredHyperedgeCollectionConstIterator & operator=(const FilteredHyperedgeCollectionConstIterator & original);

                    FilteredHyperedgeCollectionConstIterator & operator=(FilteredHyperedgeCollectionConstIterator && original);

                    bool operator==(const FilteredHyperedgeCollectionConstIterator & rhs) const;

                    bool operator!=(const FilteredHyperedgeCollectionConstIterator & rhs) const;

                    const htd::Hyperedge * operator->(void) const;

                    const htd::Hyperedge & operator*(void) const;

                private:
                    std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection_;

                    std::shared_ptr<std::vector<htd::index_t>> relevantIndices_;

                    htd::index_t position_;
            };

            FilteredHyperedgeCollection(void);

            FilteredHyperedgeCollection(const std::vector<htd::Hyperedge> & baseCollection, const std::vector<htd::index_t> & relevantIndices);

            FilteredHyperedgeCollection(std::vector<htd::Hyperedge> && baseCollection, std::vector<htd::index_t> && relevantIndices);

            FilteredHyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection, const std::vector<htd::index_t> & relevantIndices);

            FilteredHyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection, std::vector<htd::index_t> && relevantIndices);

            FilteredHyperedgeCollection(const FilteredHyperedgeCollection & hyperedges);

            FilteredHyperedgeCollection(FilteredHyperedgeCollection && hyperedges);

            virtual ~FilteredHyperedgeCollection();

            std::size_t size(void) const;

            FilteredHyperedgeCollectionConstIterator begin(void) const;

            FilteredHyperedgeCollectionConstIterator end(void) const;

            FilteredHyperedgeCollection & operator=(const FilteredHyperedgeCollection & rhs);

            FilteredHyperedgeCollection & operator=(FilteredHyperedgeCollection && rhs);

            bool operator==(const FilteredHyperedgeCollection & rhs) const;

            bool operator!=(const FilteredHyperedgeCollection & rhs) const;

            void restrictTo(const std::vector<htd::vertex_t> & vertices);

        private:
            bool written_;

            std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection_;

            std::shared_ptr<std::vector<htd::index_t>> relevantIndices_;
    };
}

#endif /* HTD_HTD_FILTEREDHYPEREDGECOLLECTION_HPP */
