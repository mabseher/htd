/*
 * File:   LabeledMultiHypergraphFactory.hpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP
#define HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledMultiHypergraph.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledMultiHypergraph interface.
     */
    class LabeledMultiHypergraphFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API LabeledMultiHypergraphFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledMultiHypergraphFactory(const LabeledMultiHypergraphFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API LabeledMultiHypergraphFactory & operator=(const LabeledMultiHypergraphFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledMultiHypergraphFactory();

            /**
             *  Create a new IMutableLabeledMultiHypergraph object.
             *
             *  @return A new IMutableLabeledMultiHypergraph object.
             */
            HTD_API htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(void) const;

            /**
             *  Create a new IMutableLabeledMultiHypergraph object.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             *
             *  @return A new IMutableLabeledMultiHypergraph object of the given size.
             */
            HTD_API htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(std::size_t initialSize) const;

            /**
             *  Create a new IMutableLabeledMultiHypergraph object.
             *
             *  @param[in] original The original labeled multi-hypergraph acting as template for the created graph.
             *
             *  @return A new IMutableLabeledMultiHypergraph object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledMultiHypergraph * getLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledMultiHypergraph interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledMultiHypergraph interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledMultiHypergraph * original);

            /**
             *  Access the mutable interface of a given labeled multi-hypergraph.
             *
             *  @return The mutable interface of the given labeled multi-hypergraph.
             */
            HTD_API htd::IMutableLabeledMultiHypergraph & accessMutableLabeledMultiHypergraph(htd::ILabeledMultiHypergraph & original) const;

            /**
             *  Access the mutable interface of a given labeled multi-hypergraph.
             *
             *  @return The mutable interface of the given labeled multi-hypergraph.
             */
            HTD_API const htd::IMutableLabeledMultiHypergraph & accessMutableLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledMultiHypergraph * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_HPP */
