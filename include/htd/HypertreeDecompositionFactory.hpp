/*
 * File:   HypertreeDecompositionFactory.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableHypertreeDecomposition interface.
     */
    class HypertreeDecompositionFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~HypertreeDecompositionFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static HypertreeDecompositionFactory & instance(void);

            /**
             *  Create a new IMutableHypertreeDecomposition object.
             *
             *  @return A new IMutableHypertreeDecomposition object.
             */
            htd::IMutableHypertreeDecomposition * getHypertreeDecomposition(void);

            /**
             *  Create a new IMutableHypertreeDecomposition object.
             *
             *  @param[in] original The original hypertree decomposition acting as template for the created graph.
             *
             *  @return A new IMutableHypertreeDecomposition object identical to the given original graph.
             */
            htd::IMutableHypertreeDecomposition * getHypertreeDecomposition(const htd::ITreeDecomposition & original);

            /**
             *  Set the default implementation of the IMutableHypertreeDecomposition interface.
             *
             *  @param[in] original The new default implementation of the IMutableHypertreeDecomposition interface.
             */
            void setConstructionTemplate(htd::IMutableHypertreeDecomposition * original);

            /**
             *  Access the mutable interface of a given hypertree decomposition.
             *
             *  @return The mutable interface of the given hypertree decomposition.
             */
            htd::IMutableHypertreeDecomposition & accessMutableHypertreeDecomposition(htd::IHypertreeDecomposition & original);

            /**
             *  Access the mutable interface of a given hypertree decomposition.
             *
             *  @return The mutable interface of the given hypertree decomposition.
             */
            const htd::IMutableHypertreeDecomposition & accessMutableHypertreeDecomposition(const htd::IHypertreeDecomposition & original);

        private:
            /**
             *  A pointer to a clean instance of the default implementation.
             */
            htd::IMutableHypertreeDecomposition * constructionTemplate_;

            /**
             *  Constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            HypertreeDecompositionFactory(void);

            /**
             *  Copy constructor for the factory class.
             *
             *  @note This constructor is private to prevent creating multiple instances of the factory.
             */
            HypertreeDecompositionFactory(const HypertreeDecompositionFactory & original);

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @note This operator is private to prevent assignments to the factory class.
             */
            HypertreeDecompositionFactory & operator=(const HypertreeDecompositionFactory & original);
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP */
