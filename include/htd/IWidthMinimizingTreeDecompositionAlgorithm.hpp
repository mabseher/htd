/* 
 * File:   IWidthMinimizingTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_IWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_IWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ICustomizedTreeDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionFitnessFunction.hpp>

#include <vector>
#include <functional>

namespace htd
{
    /**
     *  Interface for tree decomposition algorithms which return tree decompositions of low width.
     *
     *  After finishing the computations (or being interrupted by a call to htd::LibraryInstance::terminate()),
     *  the algorithms implementing this interface are required to return the decomposition of lowest width
     *  found so far.
     */
    class IWidthMinimizingTreeDecompositionAlgorithm : public htd::ICustomizedTreeDecompositionAlgorithm
    {
        public:
            virtual ~IWidthMinimizingTreeDecompositionAlgorithm() = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph        The input graph to decompose.
             *  @param[in] maxBagSize   The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph            The input graph to decompose.
             *  @param[in] progressCallback A callback function which is invoked in each iteration after the new decomposition was computed.
             *  @param[in] maxBagSize       The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] progressCallback         A callback function which is invoked for each new decomposition.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph                The input graph to decompose.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *  @param[in] maxBagSize           The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph                The input graph to decompose.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *  @param[in] progressCallback     A callback function which is invoked for each new decomposition.
             *  @param[in] maxBagSize           The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] progressCallback         A callback function which is invoked for each new decomposition.
             *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
             *
             *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const = 0;

            virtual IWidthMinimizingTreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE = 0;
    };

    inline htd::IWidthMinimizingTreeDecompositionAlgorithm::~IWidthMinimizingTreeDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP */
