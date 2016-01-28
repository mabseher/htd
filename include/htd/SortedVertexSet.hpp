/*
 * File:   SortedVertexSet.hpp
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

#ifndef HTD_HTD_SORTEDVERTEXSET_HPP
#define	HTD_HTD_SORTEDVERTEXSET_HPP

#include <htd/Globals.hpp>

#include <htd/ConstCollection.hpp>

#include <array>
#include <vector>

namespace htd
{
    class SortedVertexSet
    {
        private:

            class Container
            {
                public:
                    static constexpr const std::size_t MAXIMUM_CONTAINER_SIZE = 64;

                    Container(Container * prev, Container * next);

                    virtual ~Container();

                    std::size_t size_;

                    Container * prev_;
                    Container * next_;

                    std::array<htd::vertex_t, MAXIMUM_CONTAINER_SIZE> elements_;
            };

            std::size_t size_;

            std::size_t capacity_;

            Container * first_;
            Container * last_;

        public:
            typedef htd::vertex_t value_type;

            class SortedVertexSetConstIterator
            {
                    public:
                    typedef std::ptrdiff_t difference_type;
                    typedef htd::vertex_t value_type;
                    typedef const htd::vertex_t & reference;
                    typedef const htd::vertex_t * pointer;
                    typedef const htd::vertex_t & const_reference;
                    typedef const htd::vertex_t * const_pointer;
                    typedef std::random_access_iterator_tag iterator_category;

                    SortedVertexSetConstIterator(void);

                    SortedVertexSetConstIterator(Container * container);

                    SortedVertexSetConstIterator(Container * container, htd::index_t position);

                    SortedVertexSetConstIterator(const SortedVertexSetConstIterator & original);

                    SortedVertexSetConstIterator(SortedVertexSetConstIterator && original);

                    ~SortedVertexSetConstIterator();

                    SortedVertexSetConstIterator & operator++(void);

                    SortedVertexSetConstIterator operator++(int);

                    SortedVertexSetConstIterator & operator+=(std::size_t positions);

                    SortedVertexSetConstIterator & operator--(void);

                    SortedVertexSetConstIterator operator--(int);

                    SortedVertexSetConstIterator & operator-=(std::size_t positions);

                    std::size_t operator-(const SortedVertexSetConstIterator & rhs);

                    SortedVertexSetConstIterator & operator=(const SortedVertexSetConstIterator & original);

                    SortedVertexSetConstIterator & operator=(SortedVertexSetConstIterator && original);

                    bool operator==(const SortedVertexSetConstIterator & rhs) const;

                    bool operator!=(const SortedVertexSetConstIterator & rhs) const;

                    const htd::vertex_t * operator->(void) const;

                    const htd::vertex_t & operator*(void) const;

                private:
                    Container * container_;

                    htd::index_t position_;
            };

            SortedVertexSet(void);

            virtual ~SortedVertexSet();

            std::size_t size(void) const;

            std::size_t capacity(void) const;

            void insert(htd::vertex_t vertex);

            void erase(htd::vertex_t vertex);

            void merge(const std::vector<htd::vertex_t> & input);

            void merge(const htd::ConstCollection<htd::vertex_t> & input);

            void erase(const std::vector<htd::vertex_t> & input);

            void erase(const htd::ConstCollection<htd::vertex_t> & input);

            void shrink(void);

            void clear(void);

            SortedVertexSetConstIterator begin(void) const;

            SortedVertexSetConstIterator end(void) const;

        private:
            void insert(htd::vertex_t vertex, Container * container);

            Container * erase(htd::vertex_t vertex, Container * container);
    };
}

#endif /* HTD_HTD_SORTEDVERTEXSET_HPP */
