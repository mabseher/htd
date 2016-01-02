/* 
 * File:   IPathDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_IPATHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_IPATHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IPathDecomposition.hpp>

#include <vector>

namespace htd
{
    class IPathDecompositionAlgorithm : public virtual htd::ITreeDecompositionAlgorithm
    {
        public:
            virtual ~IPathDecompositionAlgorithm() = 0;
            
            virtual htd::IPathDecomposition * computeDecomposition(const htd::IHypergraph & graph) const HTD_OVERRIDE = 0;

            virtual htd::IPathDecomposition * computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE = 0;

            virtual IPathDecompositionAlgorithm * clone(void) const = 0;
    };

    inline htd::IPathDecompositionAlgorithm::~IPathDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IPATHDECOMPOSITIONALGORITHM_HPP */
