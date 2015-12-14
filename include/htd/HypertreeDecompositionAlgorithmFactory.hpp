/*
 * File:   HypertreeDecompositionAlgorithmFactory.hpp
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

#ifndef HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP
#define HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>

namespace htd
{
    class HypertreeDecompositionAlgorithmFactory
    {
        public:
            ~HypertreeDecompositionAlgorithmFactory();

            static HypertreeDecompositionAlgorithmFactory & instance(void);

            htd::IHypertreeDecompositionAlgorithm * getHypertreeDecompositionAlgorithm(void);

            void setConstructionTemplate(htd::IHypertreeDecompositionAlgorithm * original);

        private:
            htd::IHypertreeDecompositionAlgorithm * constructionTemplate_;

            HypertreeDecompositionAlgorithmFactory(void);

            HypertreeDecompositionAlgorithmFactory(const HypertreeDecompositionAlgorithmFactory & original);

            HypertreeDecompositionAlgorithmFactory & operator=(const HypertreeDecompositionAlgorithmFactory & original);
    };
}

#endif /* HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_HPP */
