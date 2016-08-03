/*
 * File:   LabeledTreeFactory.hpp
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

#ifndef HTD_HTD_LABELEDTREEFACTORY_HPP
#define HTD_HTD_LABELEDTREEFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledTree.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableLabeledTree interface.
     */
    class LabeledTreeFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             */
            HTD_API LabeledTreeFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             */
            HTD_API LabeledTreeFactory(const LabeledTreeFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             */
            HTD_API LabeledTreeFactory & operator=(const LabeledTreeFactory & original);

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~LabeledTreeFactory();

            /**
             *  Create a new IMutableLabeledTree object.
             *
             *  @return A new IMutableLabeledTree object.
             */
            HTD_API htd::IMutableLabeledTree * getLabeledTree(void) const;

            /**
             *  Create a new IMutableLabeledTree object.
             *
             *  @param[in] original The original labeled tree acting as template for the created graph.
             *
             *  @return A new IMutableLabeledTree object identical to the given original graph.
             */
            HTD_API htd::IMutableLabeledTree * getLabeledTree(const htd::ILabeledTree & original) const;

            /**
             *  Set the default implementation of the IMutableLabeledTree interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableLabeledTree interface.
             */
            HTD_API void setConstructionTemplate(htd::IMutableLabeledTree * original);

            /**
             *  Access the mutable interface of a given labeled tree.
             *
             *  @return The mutable interface of the given labeled tree.
             */
            HTD_API htd::IMutableLabeledTree & accessMutableLabeledTree(htd::ILabeledTree & original) const;

            /**
             *  Access the mutable interface of a given labeled tree.
             *
             *  @return The mutable interface of the given labeled tree.
             */
            HTD_API const htd::IMutableLabeledTree & accessMutableLabeledTree(const htd::ILabeledTree & original) const;

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableLabeledTree * constructionTemplate_;
    };
}

#endif /* HTD_HTD_LABELEDTREEFACTORY_HPP */
