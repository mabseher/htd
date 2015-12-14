/*
 * File:   TreeDecompositionAlgorithmFactory.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

namespace htd
{
    class TreeDecompositionAlgorithmFactory
    {
        public:
            ~TreeDecompositionAlgorithmFactory();

            static TreeDecompositionAlgorithmFactory & instance(void);

            htd::ITreeDecompositionAlgorithm * getTreeDecompositionAlgorithm(void);

            void setConstructionTemplate(htd::ITreeDecompositionAlgorithm * original);

        private:
            htd::ITreeDecompositionAlgorithm * constructionTemplate_;

            TreeDecompositionAlgorithmFactory(void);

            TreeDecompositionAlgorithmFactory(const TreeDecompositionAlgorithmFactory & original);

            TreeDecompositionAlgorithmFactory & operator=(const TreeDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_TREEDECOMPOSITIONALGORITHMFACTORY_HPP */
