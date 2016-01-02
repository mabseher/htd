/*
 * File:   PathDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_PATHDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_PATHDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

namespace htd
{
    class PathDecompositionAlgorithmFactory
    {
        public:
            ~PathDecompositionAlgorithmFactory();

            static PathDecompositionAlgorithmFactory & instance(void);

            htd::IPathDecompositionAlgorithm * getPathDecompositionAlgorithm(void);

            void setConstructionTemplate(htd::IPathDecompositionAlgorithm * original);

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

        private:
            htd::IPathDecompositionAlgorithm * constructionTemplate_;

            PathDecompositionAlgorithmFactory(void);

            PathDecompositionAlgorithmFactory(const PathDecompositionAlgorithmFactory & original);

            PathDecompositionAlgorithmFactory & operator=(const PathDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_PATHDECOMPOSITIONALGORITHMFACTORY_HPP */
