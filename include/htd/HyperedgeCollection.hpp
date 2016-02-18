/*
 * File:   HyperedgeCollection.hpp
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

#ifndef HTD_HTD_HYPEREDGECOLLECTION_HPP
#define	HTD_HTD_HYPEREDGECOLLECTION_HPP

#include <htd/Globals.hpp>

#include <htd/Hyperedge.hpp>
#include <htd/ConstCollection.hpp>

#include <array>
#include <memory>
#include <vector>

namespace htd
{
    class HyperedgeCollection
    {
        public:
            typedef htd::Hyperedge value_type;

            class HyperedgeCollectionConstIterator
            {
                public:
                    typedef std::ptrdiff_t difference_type;
                    typedef htd::Hyperedge value_type;
                    typedef const htd::Hyperedge & reference;
                    typedef const htd::Hyperedge * pointer;
                    typedef const htd::Hyperedge & const_reference;
                    typedef const htd::Hyperedge * const_pointer;
                    typedef std::random_access_iterator_tag iterator_category;

                    HyperedgeCollectionConstIterator(const HyperedgeCollection & collection, htd::index_t position);

                    HyperedgeCollectionConstIterator(const HyperedgeCollectionConstIterator & original);

                    HyperedgeCollectionConstIterator(HyperedgeCollectionConstIterator && original);

                    ~HyperedgeCollectionConstIterator();

                    HyperedgeCollectionConstIterator & operator++(void);

                    HyperedgeCollectionConstIterator operator++(int);

                    HyperedgeCollectionConstIterator & operator+=(std::size_t positions);

                    HyperedgeCollectionConstIterator & operator--(void);

                    HyperedgeCollectionConstIterator operator--(int);

                    HyperedgeCollectionConstIterator & operator-=(std::size_t positions);

                    std::size_t operator-(const HyperedgeCollectionConstIterator & rhs);

                    HyperedgeCollectionConstIterator & operator=(const HyperedgeCollectionConstIterator & original);

                    HyperedgeCollectionConstIterator & operator=(HyperedgeCollectionConstIterator && original);

                    bool operator==(const HyperedgeCollectionConstIterator & rhs) const;

                    bool operator!=(const HyperedgeCollectionConstIterator & rhs) const;

                    const htd::Hyperedge * operator->(void) const;

                    const htd::Hyperedge & operator*(void) const;

                private:
                    std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection_;

                    htd::index_t position_;
            };

            HyperedgeCollection(void);

            HyperedgeCollection(const std::vector<htd::Hyperedge> & baseCollection);

            HyperedgeCollection(std::vector<htd::Hyperedge> && baseCollection);

            HyperedgeCollection(std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection);

            virtual ~HyperedgeCollection();

            std::size_t size(void) const;

            HyperedgeCollectionConstIterator begin(void) const;

            HyperedgeCollectionConstIterator end(void) const;

            bool operator==(const HyperedgeCollection & rhs) const;

            bool operator!=(const HyperedgeCollection & rhs) const;

        private:
            std::shared_ptr<std::vector<htd::Hyperedge>> baseCollection_;
    };
}

#endif /* HTD_HTD_HYPEREDGECOLLECTION_HPP */
