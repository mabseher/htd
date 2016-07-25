/*
 * File:   HypergraphFactory.hpp
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

#ifndef HTD_HTD_HYPERGRAPHFACTORY_HPP
#define HTD_HTD_HYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableHypergraph interface.
     */
    class HTD_API HypergraphFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~HypergraphFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static HypergraphFactory & instance(void);

            /**
             *  Create a new IMutableHypergraph object.
             *
             *  @return A new IMutableHypergraph object.
             */
            htd::IMutableHypergraph * getHypergraph(void);

            /**
             *  Create a new IMutableHypergraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableHypergraph object of the given size.
             */
            htd::IMutableHypergraph * getHypergraph(std::size_t initialSize);

            /**
             *  Create a new IMutableHypergraph object.
             *
             *  @param[in] original The original hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableHypergraph object identical to the given original graph.
             */
            htd::IMutableHypergraph * getHypergraph(const htd::IHypergraph & original);

            /**
             *  Create a new IMutableHypergraph object.
             *
             *  @param[in] original The original multi-hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableHypergraph object identical to the given original graph.
             */
            htd::IMutableHypergraph * getHypergraph(const htd::IMultiHypergraph & original);

            /**
             *  Set the default implementation of the IMutableHypergraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableHypergraph interface.
             */
            void setConstructionTemplate(htd::IMutableHypergraph * original);

            /**
             *  Access the mutable interface of a given hypergraph.
             *
             *  @return The mutable interface of the given hypergraph.
             */
            htd::IMutableHypergraph & accessMutableHypergraph(htd::IHypergraph & original);

            /**
             *  Access the mutable interface of a given hypergraph.
             *
             *  @return The mutable interface of the given hypergraph.
             */
            const htd::IMutableHypergraph & accessMutableHypergraph(const htd::IHypergraph & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableHypergraph * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            HypergraphFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            HypergraphFactory(const HypergraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            HypergraphFactory & operator=(const HypergraphFactory & original);
    };
}

#endif /* HTD_HTD_HYPERGRAPHFACTORY_HPP */
