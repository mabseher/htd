/*
 * File:   HypertreeDecompositionFactory.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/GraphTypeFactory.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the IMutableHypertreeDecomposition interface.
     */
    class HypertreeDecompositionFactory : public htd::GraphTypeFactory<htd::IHypertreeDecomposition, htd::IMutableHypertreeDecomposition>
    {
        public:
            using htd::GraphTypeFactory<htd::IHypertreeDecomposition, htd::IMutableHypertreeDecomposition>::createInstance;

            /**
             *  Constructor for the factory class.
             *
             *  @param[in] manager   The management instance to which the new factory class belongs.
             */
            HTD_API HypertreeDecompositionFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API HypertreeDecompositionFactory(const HypertreeDecompositionFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API HypertreeDecompositionFactory & operator=(const HypertreeDecompositionFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~HypertreeDecompositionFactory();

            /**
             *  Create a new IMutableHypertreeDecomposition object.
             *
             *  @return A new IMutableHypertreeDecomposition object.
             */
            HTD_API htd::IMutableHypertreeDecomposition * createInstance(void) const;

            /**
             *  Create a new IMutableTreeDecomposition object.
             *
             *  @param[in] original The original tree decomposition acting as template for the created decomposition.
             *
             *  @return A new IMutableTreeDecomposition object.
             */
            HTD_API htd::IMutableHypertreeDecomposition * createInstance(const htd::ITreeDecomposition & original) const;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP */
