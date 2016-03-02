/* 
 * File:   Hyperedge.hpp
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

#ifndef HTD_HTD_HYPEREDGE_HPP
#define	HTD_HTD_HYPEREDGE_HPP

#include <htd/Globals.hpp>
#include <htd/Iterator.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>

#include <vector>
#include <memory>

namespace htd
{
    class Hyperedge
    {
        public:
            typedef htd::vertex_t value_type;

            Hyperedge(htd::id_t id, htd::vertex_t vertex1, htd::vertex_t vertex2);

            Hyperedge(htd::id_t id, const std::vector<htd::vertex_t> & elements);

            Hyperedge(htd::id_t id, std::vector<htd::vertex_t> && elements) HTD_NOEXCEPT;

            Hyperedge(htd::id_t id, const htd::ConstCollection<htd::vertex_t> & elements);

            Hyperedge(const Hyperedge & original);

            Hyperedge(Hyperedge && original) HTD_NOEXCEPT;

            ~Hyperedge();

            htd::id_t id() const;

            void setId(htd::id_t newId);

            const std::vector<htd::vertex_t> & elements() const;

            const std::vector<htd::vertex_t> & sortedElements() const;

            bool empty() const;

            std::size_t size() const;

            bool containsVertex(htd::vertex_t vertex) const;

            void erase(htd::vertex_t vertex);

            std::vector<htd::vertex_t>::const_iterator begin(void) const;

            std::vector<htd::vertex_t>::const_iterator end(void) const;

            const htd::vertex_t & operator[](htd::index_t index) const;

            Hyperedge & operator=(const Hyperedge & original);

            Hyperedge & operator=(Hyperedge && original) HTD_NOEXCEPT;

            bool operator<(const Hyperedge & rhs) const;

            bool operator>(const Hyperedge & rhs) const;

            bool operator==(const Hyperedge & rhs) const;

            bool operator!=(const Hyperedge & rhs) const;

        private:
            htd::id_t id_;

            std::shared_ptr<std::vector<htd::vertex_t>> elements_;

            std::shared_ptr<std::vector<htd::vertex_t>> sortedElements_;
    };

    /**
     *  Datatype for storing hyperedges.
     */
    typedef std::vector<Hyperedge> hyperedge_container;
}

#endif /* HTD_HTD_HYPEREDGE_HPP */
