/* 
 * File:   IterativeImprovementTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>

#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionFitnessFunction.hpp>

#include <vector>
#include <functional>

namespace htd
{
    /**
     *  Implementation of the ITreeDecompositionAlgorithm interface based on repeated construction of a tree
     *  decomposition of the same input graph. After finishing the last iteration (or being interrupted by a
     *  call to htd::LibraryInstance::terminate()), the algorithm returns the best decomposition found so
     *  far based on the provided fitness function. In case that this algorithm is interrupted before the
     *  first iteration is finished, the return value of computeDecomposition() will be nullptr.
     *
     *  @note The algorithm always returns a valid tree decomposition according to the provided base
     *  decomposition algorithm and the given manipulations (or nullptr) also if it was interrupted
     *  by a call to htd::LibraryInstance::terminate().
     */
    class IterativeImprovementTreeDecompositionAlgorithm : public htd::ITreeDecompositionAlgorithm
    {
        public:
            /**
             *  Constructor for a new iterative improvement tree decomposition algorithm.
             *
             *  @param[in] manager          The management instance to which the new algorithm belongs.
             *  @param[in] algorithm        The decomposition algorithm which will be called repeatedly.
             *  @param[in] fitnessFunction  The fitness function which will be used to evaluate the constructed tree decompositions.
             */
            HTD_API IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, const htd::ITreeDecompositionAlgorithm & algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction);

            /**
             *  Constructor for a new iterative improvement tree decomposition algorithm.
             *
             *  @note When calling this method the control over the memory regions of the base decomposition algorithm is transferred
             *  to the decomposition algorithm. Deleting the base decomposition algorithm provided to this constructor outside the
             *  decomposition algorithm will lead to undefined behavior.
             *
             *  @param[in] manager          The management instance to which the new algorithm belongs.
             *  @param[in] algorithm        The decomposition algorithm which will be called repeatedly.
             *  @param[in] fitnessFunction  The fitness function which will be used to evaluate the constructed tree decompositions.
             */
            HTD_API IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, htd::ITreeDecompositionAlgorithm * algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction);

            /**
             *  Constructor for a new iterative improvement tree decomposition algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manager                  The management instance to which the new algorithm belongs.
             *  @param[in] algorithm                The decomposition algorithm which will be called repeatedly.
             *  @param[in] fitnessFunction          The fitness function which will be used to evaluate the constructed tree decompositions.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, const htd::ITreeDecompositionAlgorithm & algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            /**
             *  Constructor for a new iterative improvement tree decomposition algorithm.
             *
             *  @note When calling this method the control over the memory regions of the the base decomposition algorithm and the manipulation
             *  operations is transferred to the decomposition algorithm. Deleting the base decomposition algorithm or a manipulation operation
             *  provided to this method outside the decomposition algorithm or assigning the same manipulation operation multiple times will
             *  lead to undefined behavior.
             *
             *  @param[in] manager                  The management instance to which the new algorithm belongs.
             *  @param[in] algorithm                The decomposition algorithm which will be called repeatedly.
             *  @param[in] fitnessFunction          The fitness function which will be used to evaluate the constructed tree decompositions.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, htd::ITreeDecompositionAlgorithm * algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations);

            HTD_API virtual ~IterativeImprovementTreeDecompositionAlgorithm();

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph            The input graph to decompose.
             *  @param[in] progressCallback A callback function which is invoked in each iteration after the new decomposition was computed.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const;

            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const HTD_OVERRIDE;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *  @param[in] progressCallback         A callback function which is invoked in each iteration after the new decomposition was computed.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
             */
            HTD_API htd::ITreeDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                   const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                   const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const;

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

            HTD_API void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) HTD_OVERRIDE;

            HTD_API void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) HTD_OVERRIDE;

            HTD_API bool isSafelyInterruptible(void) const HTD_OVERRIDE;

            /**
             *  Getter for the number of iterations which shall be performed (0=infinite).
             *
             *  @return The number of iterations which shall be performed.
             */
            HTD_API std::size_t iterationCount(void) const;

            /**
             *  Set the number of iterations which shall be performed (0=infinite).
             *
             *  @param[in] iterationCount   The number of iterations which shall be performed.
             */
            HTD_API void setIterationCount(std::size_t iterationCount);

            /**
             *  Getter for the maximum number of iterations without improvement after which the algorithm shall terminate (0=return after first non-improving decomposition was found).
             *
             *  @note The current non-improvement count is reset to 0 after each iteration resulting in an improved decomposition.
             *
             *  @return The maximum number of iterations without improvement after which the algorithm shall terminate.
             */
            HTD_API std::size_t nonImprovementLimit(void) const;

            /**
             *  Set the maximum number of iterations without improvement after which the algorithm shall terminate (0=return after first non-improving decomposition was found).
             *
             *  @note The current non-improvement count is reset to 0 after each iteration resulting in an improved decomposition.
             *
             *  @param[in] nonImprovementLimit  The maximum number of iterations without improvement after which the algorithm shall terminate.
             */
            HTD_API void setNonImprovementLimit(std::size_t nonImprovementLimit);

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API IterativeImprovementTreeDecompositionAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a tree decomposition algorithm based on bucket elimination.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            IterativeImprovementTreeDecompositionAlgorithm & operator=(const IterativeImprovementTreeDecompositionAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_HPP */
