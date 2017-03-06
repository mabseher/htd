/* 
 * File:   IHypertreeDecompositionAlgorithm.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_IHYPERTREEDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_IHYPERTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/IHypertreeDecomposition.hpp>

namespace htd
{
    /**
     * Interface for algorithms which can be used to compute hypertree decompositions of a given graph.
     */
    class IHypertreeDecompositionAlgorithm : public htd::ITreeDecompositionAlgorithm
    {
        public:
            virtual ~IHypertreeDecompositionAlgorithm() = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph    The input graph to decompose.
             *
             *  @return A new IHypertreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IHypertreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *
             *  @return A new IHypertreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IHypertreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph                The input graph to decompose.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *
             *  @return A new IHypertreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IHypertreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_OVERRIDE = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *
             *  @return A new IHypertreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IHypertreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE = 0;

            /**
             *  Create a deep copy of the current hypertree decomposition algorithm.
             *
             *  @return A new IHypertreeDecompositionAlgorithm object identical to the current hypertree decomposition algorithm.
             */
            virtual IHypertreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE = 0;
    };

    inline htd::IHypertreeDecompositionAlgorithm::~IHypertreeDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IHYPERTREEDECOMPOSITIONALGORITHM_HPP */
