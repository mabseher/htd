/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

#include <vector>
#include <unordered_set>

namespace htd
{
    class BucketEliminationTreeDecompositionAlgorithm : public virtual htd::ITreeDecompositionAlgorithm
    {
        public:
            BucketEliminationTreeDecompositionAlgorithm(bool compressed = true);

            BucketEliminationTreeDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, bool compressed = true);

            ~BucketEliminationTreeDecompositionAlgorithm();
            
            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            BucketEliminationTreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            BucketEliminationTreeDecompositionAlgorithm & operator=(const BucketEliminationTreeDecompositionAlgorithm &) { return *this; }

        private:
            bool compressed_;

            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

            htd::IMutableTreeDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph) const;
    };
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP */
