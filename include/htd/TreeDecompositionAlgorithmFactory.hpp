/*
 * File:   TreeDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/AlgorithmFactory.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

namespace htd
{
    /**
     *  Factory class for the default implementation of the ITreeDecompositionAlgorithm interface.
     */
    class TreeDecompositionAlgorithmFactory : public htd::AlgorithmFactory<htd::ITreeDecompositionAlgorithm>
    {
        public:
            /**
             *  Constructor for the factory class.
             *
             *  @param[in] manager   The management instance to which the new factory class belongs.
             */
            HTD_API TreeDecompositionAlgorithmFactory(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API TreeDecompositionAlgorithmFactory(const TreeDecompositionAlgorithmFactory & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            HTD_API TreeDecompositionAlgorithmFactory & operator=(const TreeDecompositionAlgorithmFactory & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            HTD_API virtual ~TreeDecompositionAlgorithmFactory();

            /**
             *  Create a new ITreeDecompositionAlgorithm object.
             *
             *  @return A new ITreeDecompositionAlgorithm object.
             */
            HTD_API htd::ITreeDecompositionAlgorithm * createInstance(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP */
