/* 
 * File:   ITreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_ITREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ITreeDecomposition.hpp>

#include <vector>

namespace htd
{
    class ITreeDecompositionAlgorithm : public virtual htd::IGraphDecompositionAlgorithm
    {
        public:
            virtual ~ITreeDecompositionAlgorithm() = 0;
            
            virtual htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph) const HTD_OVERRIDE = 0;

            virtual htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE = 0;

            //virtual htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const HTD_OVERRIDE = 0;

            virtual ITreeDecompositionAlgorithm * clone(void) const = 0;
    };

    inline htd::ITreeDecompositionAlgorithm::~ITreeDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITIONALGORITHM_HPP */
