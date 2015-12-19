/* 
 * File:   PostProcessingPathDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>

#include <cstdarg>
#include <vector>

namespace htd
{
    class PostProcessingPathDecompositionAlgorithm : public virtual htd::IPathDecompositionAlgorithm
    {
        public:
            PostProcessingPathDecompositionAlgorithm(void);

            PostProcessingPathDecompositionAlgorithm(const std::vector<htd::ILabelingFunction *> & labelingFunctions);

            ~PostProcessingPathDecompositionAlgorithm();
            
            htd::IPathDecomposition * computeDecomposition(const htd::IHypergraph & graph) const HTD_OVERRIDE;

            htd::IPathDecomposition * computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            htd::IPathDecomposition * computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const; //TODO HTD_OVERRIDE;

            PostProcessingPathDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            PostProcessingPathDecompositionAlgorithm & operator=(const PostProcessingPathDecompositionAlgorithm &) { return *this; }
    };
}

#endif /* HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_HPP */
