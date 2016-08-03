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
             *  Constructor for the factory class.
             */
            HTD_API MultiHypergraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API MultiHypergraphFactory(const MultiHypergraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API MultiHypergraphFactory & operator=(const MultiHypergraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~MultiHypergraphFactory();

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @return A new IMutableMultiHypergraph object.
             */
            HTD_API htd::IMutableMultiHypergraph * getMultiHypergraph(void) const;

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableMultiHypergraph object of the given size.
             */
            HTD_API htd::IMutableMultiHypergraph * getMultiHypergraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableMultiHypergraph object.
             *
             *  @param[in] original The original multi-hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableMultiHypergraph object identical to the given original graph.
             */
            HTD_API htd::IMutableMultiHypergraph * getMultiHypergraph(const htd::IMultiHypergraph & original) const;

            /**
             *  Set the default implementation of the IMutableMultiHypergraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableMultiHypergraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableMultiHypergraph * original);

            /**
             *  Access the mutable interface of a given multi-hypergraph.
             *
             *  @return The mutable interface of the given multi-hypergraph.
             */
            HTD_API htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(htd::IMultiHypergraph & original) const;

            /**
             *  Access the mutable interface of a given multi-hypergraph.
             *
             *  @return The mutable interface of the given multi-hypergraph.
             */
            HTD_API const htd::IMutableMultiHypergraph & accessMutableMultiHypergraph(const htd::IMultiHypergraph & original) const;

        private:
            HTD_IMPLEMENTATION Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_MULTIHYPERGRAPHFACTORY_HPP */
