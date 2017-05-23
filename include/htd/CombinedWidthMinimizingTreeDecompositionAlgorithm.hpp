/* 
 * File:   CombinedWidthMinimizingTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IWidthMinimizingTreeDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionFitnessFunction.hpp>

#include <vector>
#include <functional>

namespace htd
{
    /**
     *  Implementation of the IWidthMinimizingTreeDecompositionAlgorithm interface based on repeated construction of a
     *  tree decomposition of the same input graph with different base decomposition algorithms. After finishing the
     *  last iteration (or being interrupted by a call to htd::LibraryInstance::terminate()), the algorithm returns
     *  the decomposition with lowest width that was found so far. In case that this algorithm is interrupted before
     *  the first iteration is finished, the return value of computeDecomposition() will be nullptr.
     *
     *  @note The algorithm always returns a valid tree decomposition according to the provided base
     *  decomposition algorithms and the given manipulations (or nullptr) also if it was interrupted
     *  by a call to htd::LibraryInstance::terminate().
     *
     *  @note The base algorithms must be assigned before the optional manipulation operations!
     */
    class CombinedWidthMinimizingTreeDecompositionAlgorithm : public htd::IWidthMinimizingTreeDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a new width-improving tree decomposition algorithm.
             *
             *  @param[in] manager  The management instance to which the new algorithm belongs.
             */
            HTD_API CombinedWidthMinimizingTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a width-improving tree decomposition algorithm.
             *
             *  @param[in] original  The original width-improving tree decomposition algorithm.
             */
            HTD_API CombinedWidthMinimizingTreeDecompositionAlgorithm(const CombinedWidthMinimizingTreeDecompositionAlgorithm & original);

            HTD_API virtual ~CombinedWidthMinimizingTreeDecompositionAlgorithm();

            /**
             *  Add a new decomposition algorithm to the list of base algorithms which shall be used.
             *
             *  @param[in] algorithm    The new decomposition algorithm which will be added to the list of base algorithms.
             *
             *  @note When calling this method the control over the memory region of the provided algorithm is transferred to the
             *  decomposition algorithm. Deleting the algorithm provided to this method outside the decomposition algorithm or
             *  assigning the same base algorithm multiple times will lead to undefined behavior.
             */
            HTD_API void addDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm);

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const htd::IPreprocessedGraph & preprocessedGraph,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const htd::IPreprocessedGraph & preprocessedGraph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const htd::IPreprocessedGraph & preprocessedGraph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] preprocessedGraph            The input graph in preprocessed format.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] maxBagSize                   The upper bound for the maximum bag size of the computed decomposition.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
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
            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, int manipulationOperationCount, ...) const;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                        The input graph to decompose.
             *  @param[in] preprocessedGraph            The input graph in preprocessed format.
             *  @param[in] maxBagSize                   The upper bound for the maximum bag size of the computed decomposition.
             *  @param[in] manipulationOperationCount   The number of manipulation operations which are provided to this function.
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
            HTD_API htd::ITreeDecomposition * computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, int manipulationOperationCount, ...) const;

            HTD_API void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            HTD_API void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API bool isSafelyInterruptible(void) const HTD_OVERRIDE;

            HTD_API bool isComputeInducedEdgesEnabled(void) const HTD_OVERRIDE;

            HTD_API void setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled) HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API CombinedWidthMinimizingTreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a width-improving tree decomposition algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            CombinedWidthMinimizingTreeDecompositionAlgorithm & operator=(const CombinedWidthMinimizingTreeDecompositionAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_HPP */
