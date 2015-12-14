/*
 * File:   HypertreeDecompositionFactory.hpp
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

#ifndef HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP
#define HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    class HypertreeDecompositionFactory
    {
        public:
            ~HypertreeDecompositionFactory();

            static HypertreeDecompositionFactory & instance(void);

            htd::IMutableHypertreeDecomposition * getHypertreeDecomposition(void);

            htd::IMutableHypertreeDecomposition * getHypertreeDecomposition(const htd::ITreeDecomposition & original);

            void setConstructionTemplate(htd::IMutableHypertreeDecomposition * original);

        private:
            htd::IMutableHypertreeDecomposition * constructionTemplate_;

            HypertreeDecompositionFactory(void);

            HypertreeDecompositionFactory(const HypertreeDecompositionFactory & original);

            HypertreeDecompositionFactory & operator=(const HypertreeDecompositionFactory & original);
    };
}

#endif /* HTD_HYPERTREEDECOMPOSITIONFACTORY_HPP */
