/*
 * File:   PathDecompositionFactory.hpp
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

#ifndef HTD_HTD_PATHDECOMPOSITIONFACTORY_HPP
#define HTD_HTD_PATHDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IPathDecomposition.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutablePathDecomposition interface.
     */
    class PathDecompositionFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~PathDecompositionFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static PathDecompositionFactory & instance(void);

            /**
             *  Create a new IMutablePathDecomposition object.
             *
             *  @return A new IMutablePathDecomposition object.
             */
            htd::IMutablePathDecomposition * getPathDecomposition(void);

            /**
             *  Create a new IMutablePathDecomposition object.
             *
             *  @param[in] original The original path decomposition acting as template for the created graph.
             *
             *  @return A new IMutablePathDecomposition object identical to the given original graph.
             */
            htd::IMutablePathDecomposition * getPathDecomposition(const htd::IPathDecomposition & original);

            /**
             *  Set the default implementation of the IMutablePathDecomposition interface.
             *
             *  @param[in] original The new default implementation of the IMutablePathDecomposition interface.
             */
            void setConstructionTemplate(htd::IMutablePathDecomposition * original);

            /**
             *  Access the mutable interface of a given path decomposition.
             *
             *  @return The mutable interface of the given path decomposition.
             */
            htd::IMutablePathDecomposition & accessMutablePathDecomposition(htd::IPathDecomposition & original);

            /**
             *  Access the mutable interface of a given path decomposition.
             *
             *  @return The mutable interface of the given path decomposition.
             */
            const htd::IMutablePathDecomposition & accessMutablePathDecomposition(const htd::IPathDecomposition & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutablePathDecomposition * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            PathDecompositionFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            PathDecompositionFactory(const PathDecompositionFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            PathDecompositionFactory & operator=(const PathDecompositionFactory & original);
    };
}

#endif /* HTD_HTD_PATHDECOMPOSITIONFACTORY_HPP */
