/*
 * File:   HyperedgePointerVector.hpp
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

#ifndef HTD_HTD_HYPEREDGEPOINTERVECTOR_HPP
#define HTD_HTD_HYPEREDGEPOINTERVECTOR_HPP

#include <htd/Globals.hpp>
#include <htd/IHyperedgeCollection.hpp>

#include <memory>
#include <vector>

namespace htd
{
    /**
     *  Wrapper for existing vectors of hyperedges.
     */
    class HyperedgePointerVector : public htd::IHyperedgeCollection
    {
        public:
            /**
             *  Constructor for a HyperedgePointerVector.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgePointerVector(const std::vector<htd::Hyperedge *> & baseCollection);

            /**
             *  Constructor for a HyperedgePointerVector.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgePointerVector(std::vector<htd::Hyperedge *> && baseCollection);

            /**
             *  Constructor for a HyperedgePointerVector.
             *
             *  @param[in] baseCollection   The underlying hyperedge collection.
             */
            HyperedgePointerVector(const std::shared_ptr<std::vector<htd::Hyperedge *>> & baseCollection);

            /**
             *  Copy constructor for a HyperedgePointerVector object.
             *
             *  @param[in] original  The original HyperedgePointerVector object.
             */
            HyperedgePointerVector(const HyperedgePointerVector & original);

            /**
             *  Move constructor for a HyperedgePointerVector object.
             *
             *  @param[in] original  The original HyperedgePointerVector object.
             */
            HyperedgePointerVector(HyperedgePointerVector && original);

            /**
             *  Destructor for a HyperedgeVector object.
             */
            virtual ~HyperedgePointerVector();

            bool empty(void) const HTD_OVERRIDE;

            std::size_t size(void) const HTD_OVERRIDE;

            const htd::Hyperedge & at(htd::index_t index) const HTD_OVERRIDE;

            htd::ConstIterator<htd::Hyperedge> begin(void) const HTD_OVERRIDE;

            htd::ConstIterator<htd::Hyperedge> end(void) const HTD_OVERRIDE;

            const htd::Hyperedge & operator[](htd::index_t index) const HTD_OVERRIDE;

            bool operator==(const htd::IHyperedgeCollection & rhs) const HTD_OVERRIDE;

            bool operator!=(const htd::IHyperedgeCollection & rhs) const HTD_OVERRIDE;

            HyperedgePointerVector * clone(void) const HTD_OVERRIDE;

        private:
            std::shared_ptr<std::vector<htd::Hyperedge *>> baseCollection_;
    };
}

#endif /* HTD_HTD_HYPEREDGEPOINTERVECTOR_HPP */
