/*
 * File:   TreeDecompositionOptimizationOperation.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_HPP
#define HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionFitnessFunction.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/IVertexSelectionStrategy.hpp>

#include <vector>

namespace htd
{
    /**
     *  Implementation of the IDecompositionManipulationOperation interface which manipulates
     *  given tree decompositions in such a way that the fitness value of the resulting tree 
     *  decomposition is maximal.
     */
    class TreeDecompositionOptimizationOperation : public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constructor for a new manipulation operation of type TreeDecompositionOptimizationOperation.
             *
             *  @param[in] manager           The management instance to which the new manipulation operation belongs.
             *
             *  @note This constructor creates an optimization operation which actually does not perform any optimization tasks
             *  due to the lack of a fitness function. That is, applying the constructed operation to a decomposition will only
             *  apply the desired manipulation operations and add requested labels.
             */
            HTD_API TreeDecompositionOptimizationOperation(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a new manipulation operation of type TreeDecompositionOptimizationOperation.
             *
             *  @note When calling this method the control over the memory regions of the fitness function are transferred
             *  to the manipulation operation. Deleting the fitness function provided to this constructor outside the
             *  manipulation operation will lead to undefined behavior.
             *
             *  @param[in] manager                  The management instance to which the new manipulation operation belongs.
             *  @param[in] fitnessFunction          The fitness function which is used to determine the quality of tree decompositions.
             *  @param[in] enforceNaiveOptimization A boolean flag to enforce that each iteration of the optimization algorithm starts from scratch with a copy of the given decomposition.
             */
            HTD_API TreeDecompositionOptimizationOperation(const htd::LibraryInstance * const manager, htd::ITreeDecompositionFitnessFunction * fitnessFunction, bool enforceNaiveOptimization = false);

            HTD_API virtual ~TreeDecompositionOptimizationOperation();

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            HTD_API bool isLocalOperation(void) const HTD_OVERRIDE;

            HTD_API bool createsTreeNodes(void) const HTD_OVERRIDE;

            HTD_API bool removesTreeNodes(void) const HTD_OVERRIDE;

            HTD_API bool modifiesBagContents(void) const HTD_OVERRIDE;

            HTD_API bool createsSubsetMaximalBags(void) const HTD_OVERRIDE;

            HTD_API bool createsLocationDependendLabels(void) const HTD_OVERRIDE;

            /**
             *  Set the manipulations which are applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  optimization operation. Deleting a manipulation operation provided to this method outside the optimization operation or
             *  assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void setManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations);

            /**
             *  Add a new manipulation operation which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory region of the manipulation operation is transferred to the optimization
             *  operation. Deleting the manipulation operation provided to this method outside the optimization operation or assigning the same
             *  manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperation    The manipulation operation which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void addManipulationOperation(htd::ITreeDecompositionManipulationOperation * manipulationOperation);

            /**
             *  Add additional manipulation operations which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  optimization operation. Deleting a manipulation operation provided to this method outside the optimization operation or
             *  assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            HTD_API void addManipulationOperations(const std::vector<htd::ITreeDecompositionManipulationOperation *> & manipulationOperations);

            /**
             *  Set the strategy defining which vertices shall be considered as root of the tree decomposition.
             *
             *  @note When calling this method the control over the memory regions of the vertex selection strategy is transferred to the
             *  optimization operation. Deleting the vertex selection strategy provided to this method outside the optimization operation
             *  or assigning the same the vertex selection strategy multiple times will lead to undefined behavior.
             *
             *  @param[in] strategy The new vertex selection strategy which shall be used.
             */
            HTD_API void setVertexSelectionStrategy(htd::IVertexSelectionStrategy * strategy);

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API TreeDecompositionOptimizationOperation * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new TreeDecompositionOptimizationOperation object identical to the current decomposition manipulation operation.
             */
            HTD_API TreeDecompositionOptimizationOperation * clone(void) const;

            HTD_API htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_HPP */
