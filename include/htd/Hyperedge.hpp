/* 
 * File:   Hyperedge.hpp
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

#ifndef HTD_HTD_HYPEREDGE_HPP
#define	HTD_HTD_HYPEREDGE_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/Iterator.hpp>

#include <vector>

namespace htd
{
    class Hyperedge
    {
        public:
            typedef htd::vertex_t value_type;

            Hyperedge(htd::id_t id);

            Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2);

            Hyperedge(htd::id_t id, const htd::Collection<htd::vertex_t> & elements);

            ~Hyperedge();

            htd::id_t id() const;

            htd::Collection<htd::vertex_t> elements();

            const htd::Collection<htd::vertex_t> elements() const;

            bool empty() const;

            bool containsVertex(htd::vertex_t vertex) const;

            void push_back(htd::vertex_t vertex);

            void erase(htd::vertex_t vertex);

            std::size_t size() const;

            htd::Iterator<htd::vertex_t> begin(void);

            const htd::Iterator<htd::vertex_t> begin(void) const;

            htd::Iterator<htd::vertex_t> end(void);

            const htd::Iterator<htd::vertex_t> end(void) const;

            const htd::vertex_t & operator[](htd::index_t index) const;

            Hyperedge & operator=(const Hyperedge & other);

            bool operator<(const Hyperedge & other) const;

            bool operator==(const Hyperedge & other) const;

        private:
            htd::id_t id_;

            htd::vertex_container elements_;
    };

    /**
     *  Datatype for storing hyperedges.
     */
    typedef std::vector<Hyperedge> hyperedge_container;
}

#endif /* HTD_HTD_HYPEREDGE_HPP */
