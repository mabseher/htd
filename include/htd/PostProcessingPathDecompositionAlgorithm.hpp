/* 
 * File:   PostProcessingPathDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>

#include <cstdarg>
#include <vector>

namespace htd
{
    class PostProcessingPathDecompositionAlgorithm : public virtual htd::IPathDecompositionAlgorithm
    {
        public:
            PostProcessingPathDecompositionAlgorithm(void);

            PostProcessingPathDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            ~PostProcessingPathDecompositionAlgorithm();
            
            htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            htd::IPathDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            PostProcessingPathDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            PostProcessingPathDecompositionAlgorithm & operator=(const PostProcessingPathDecompositionAlgorithm &) { return *this; }

            htd::IMutablePathDecomposition * toPathDecomposition(const htd::ITreeDecomposition & decomposition) const;

        private:
            std::vector<htd::ILabelingFunction *> labelingFunctions_;

            std::vector<htd::IPathDecompositionManipulationOperation *> postProcessingOperations_;
    };
}

#endif /* HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP */
