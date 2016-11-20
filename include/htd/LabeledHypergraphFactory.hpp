/*
 * File:   LabeledHypergraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDHYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledHypergraph interface.
     */
    class LabeledHypergraphFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API LabeledHypergraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledHypergraphFactory(const LabeledHypergraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledHypergraphFactory & operator=(const LabeledHypergraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledHypergraphFactory();

            /**
             *  Create a new IMutableLabeledHypergraph object.
             *
             *  @return A new IMutableLabeledHypergraph object.
             */
            HTD_API htd::IMutableLabeledHypergraph * getLabeledHypergraph(void) const;

            /**
             *  Create a new IMutableLabeledHypergraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledHypergraph object of the given size.
             */
            HTD_API htd::IMutableLabeledHypergraph * getLabeledHypergraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableLabeledHypergraph object.
             *
             *  @param[in] original The original labeled hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledHypergraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledHypergraph * getLabeledHypergraph(const htd::ILabeledHypergraph & original) const;

            /**
             *  Create a new IMutableLabeledHypergraph object.
             *
             *  @param[in] original The original labeled multi-hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledHypergraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledHypergraph * getLabeledHypergraph(const htd::ILabeledMultiHypergraph & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledHypergraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledHypergraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledHypergraph * original);

            /**
             *  Access the mutable interface of a given labeled hypergraph.
             *
             *  @return The mutable interface of the given labeled hypergraph.
             */
            HTD_API htd::IMutableLabeledHypergraph & accessMutableLabeledHypergraph(htd::ILabeledHypergraph & original) const;

            /**
             *  Access the mutable interface of a given labeled hypergraph.
             *
             *  @return The mutable interface of the given labeled hypergraph.
             */
            HTD_API const htd::IMutableLabeledHypergraph & accessMutableLabeledHypergraph(const htd::ILabeledHypergraph & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledHypergraph * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDHYPERGRAPHFACTORY_HPP */
