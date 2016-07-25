/*
 * File:   TreeDecompositionFactory.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONFACTORY_HPP
#define HTD_HTD_TREEDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableTreeDecomposition.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableTreeDecomposition interface.
     */
    class HTD_API TreeDecompositionFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~TreeDecompositionFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static TreeDecompositionFactory & instance(void);

            /**
             *  Create a new IMutableTreeDecomposition object.
             *
             *  @return A new IMutableTreeDecomposition object.
             */
            htd::IMutableTreeDecomposition * getTreeDecomposition(void);

            /**
             *  Create a new IMutableTreeDecomposition object.
             *
             *  @param[in] original The original tree decomposition acting as template for the created graph.
             *
             *  @return A new IMutableTreeDecomposition object identical to the given original graph.
             */
            htd::IMutableTreeDecomposition * getTreeDecomposition(const htd::ITreeDecomposition & original);

            /**
             *  Set the default implementation of the IMutableTreeDecomposition interface.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the IMutableTreeDecomposition interface.
             */
            void setConstructionTemplate(htd::IMutableTreeDecomposition * original);

            /**
             *  Access the mutable interface of a given tree decomposition.
             *
             *  @return The mutable interface of the given tree decomposition.
             */
            htd::IMutableTreeDecomposition & accessMutableTreeDecomposition(htd::ITreeDecomposition & original);

            /**
             *  Access the mutable interface of a given tree decomposition.
             *
             *  @return The mutable interface of the given tree decomposition.
             */
            const htd::IMutableTreeDecomposition & accessMutableTreeDecomposition(const htd::ITreeDecomposition & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableTreeDecomposition * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            TreeDecompositionFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            TreeDecompositionFactory(const TreeDecompositionFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            TreeDecompositionFactory & operator=(const TreeDecompositionFactory & original);
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONFACTORY_HPP */
