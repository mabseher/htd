/*
 * File:   MultiHypergraphFactory.hpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP
#define HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableMultiHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableMultiHypergraph interface.
     */
    class MultiHypergraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~MultiHypergraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static MultiHypergraphFactory & instance(void);

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @return A new IMutableMultiHypergraph object.
             */
            htd::IMutableMultiHypergraph * getMultiHypergraph(void);

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableMultiHypergraph object of the given size.
             */
            htd::IMutableMultiHypergraph * getMultiHypergraph(std::size_t initialSize);

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @param[in] original The original multi-hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableMultiHypergraph object identical to the given original graph.
             */
            htd::IMutableMultiHypergraph * getMultiHypergraph(const htd::IMultiHypergraph & original);

            /**
             *  Set the default implementation of the IMutableMultiHypergraph interface.
             *
             *  @param[in] original The new default implementation of the IMutableMultiHypergraph interface.
             */
            void setConstructionTemplate(htd::IMutableMultiHypergraph * original);

            /**
             *  Access the mutable interface of a given multi-hypergraph.
             *
             *  @return The mutable interface of the given multi-hypergraph.
             */
            htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(htd::IMultiHypergraph & original);

            /**
             *  Access the mutable interface of a given multi-hypergraph.
             *
             *  @return The mutable interface of the given multi-hypergraph.
             */
            const htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(const htd::IMultiHypergraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableMultiHypergraph * constructionTemplate_;

            MultiHypergraphFactory(void);

            MultiHypergraphFactory(const MultiHypergraphFactory & original);

            MultiHypergraphFactory & operator=(const MultiHypergraphFactory & original);
    };
}

#endif /* HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP */
