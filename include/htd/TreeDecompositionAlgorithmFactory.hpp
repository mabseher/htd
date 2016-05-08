/*
 * File:   TreeDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    class TreeDecompositionAlgorithmFactory
    {
        public:
            /**
             *  Destructor of the factory class.
             */
            ~TreeDecompositionAlgorithmFactory();

            /**
             *  Access the singleton instance of the factory class.
             *
             *  @return The singleton instance of the factory class.
             */
            static TreeDecompositionAlgorithmFactory & instance(void);

            htd::ITreeDecompositionAlgorithm * getTreeDecompositionAlgorithm(void);

            void setConstructionTemplate(htd::ITreeDecompositionAlgorithm * original);

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation);

            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

        private:
            htd::ITreeDecompositionAlgorithm * constructionTemplate_;

            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

            TreeDecompositionAlgorithmFactory(void);

            TreeDecompositionAlgorithmFactory(const TreeDecompositionAlgorithmFactory & original);

            TreeDecompositionAlgorithmFactory & operator=(const TreeDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP */
