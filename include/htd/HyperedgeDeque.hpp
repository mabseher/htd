/*
 * File:   HyperedgeDeque.hpp
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

#ifndef HTD_HTD_HYPEREDGEDEQUE_HPP
#define	HTD_HTD_HYPEREDGEDEQUE_HPP

#include <htd/Globals.hpp>
#include <htd/IHyperedgeCollection.hpp>

#include <memory>
#include <deque>

namespace htd
{
    /**
     *  Wrapper for existing deques of hyperedges.
     */
    class HyperedgeDeque : public htd::IHyperedgeCollection
    {
        public:
            /**
             *  Constructor for a HyperedgeDeque.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgeDeque(const std::deque<htd::Hyperedge> & baseCollection);

            /**
             *  Constructor for a HyperedgeDeque.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgeDeque(std::deque<htd::Hyperedge> && baseCollection);

            /**
             *  Constructor for a HyperedgeDeque.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgeDeque(std::shared_ptr<std::deque<htd::Hyperedge>> baseCollection);

            /**
             *  Copy constructor for a HyperedgeDeque object.
             *
             *  @param[in] original  The original HyperedgeDeque object.
             */
            HyperedgeDeque(const HyperedgeDeque & original);

            /**
             *  Move constructor for a HyperedgeDeque object.
             *
             *  @param[in] original  The original HyperedgeDeque object.
             */
            HyperedgeDeque(HyperedgeDeque && original);

            /**
             *  Destructor for a HyperedgeDeque object.
             */
            virtual ~HyperedgeDeque();

            bool empty(void) const HTD_OVERRIDE;

            std::size_t size(void) const HTD_OVERRIDE;

            const htd::Hyperedge & at(htd::index_t index) const HTD_OVERRIDE;

            htd::ConstIterator<htd::Hyperedge> begin(void) const HTD_OVERRIDE;

            htd::ConstIterator<htd::Hyperedge> end(void) const HTD_OVERRIDE;

            const htd::Hyperedge & operator[](htd::index_t index) const HTD_OVERRIDE;

            bool operator==(const htd::IHyperedgeCollection & rhs) const HTD_OVERRIDE;

            bool operator!=(const htd::IHyperedgeCollection & rhs) const HTD_OVERRIDE;

            HyperedgeDeque * clone(void) const HTD_OVERRIDE;

        private:
            std::shared_ptr<std::deque<htd::Hyperedge>> baseCollection_;
    };
}

#endif /* HTD_HTD_HYPEREDGEDEQUE_HPP */
