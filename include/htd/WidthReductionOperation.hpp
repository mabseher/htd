/*
 * File:   WidthReductionOperation.hpp
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

#ifndef HTD_HTD_WIDTHREDUCTIONOPERATION_HPP
#define HTD_HTD_WIDTHREDUCTIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/IGraphSeparatorAlgorithm.hpp>

namespace htd
{
    /**
     *  Implementation of a manipulation operation which tries to reduce the width of tree 
     *  decompositions by computing minimum separating vertex sets of the subgraph induced 
     *  by the bags.
     */
    class WidthReductionOperation : public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constructor for a new manipulation operation of type WidthReductionOperation.
             *
             *  @param[in] manager  The management instance to which the new manipulation operation belongs.
             */
            HTD_API WidthReductionOperation(const htd::LibraryInstance * const manager);

            HTD_API virtual ~WidthReductionOperation();

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

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            /**
             *  Check whether only the largest bags of the decomposition shall be considered or all of them.
             *
             *  @return A boolean flag indicating whether only the largest bags of the decomposition shall be considered or all of them.
             */
            HTD_API bool isRestrictedToLargestBags(void) const;

            /**
             *  Set whether whether only the largest bags of the decomposition shall be considered.
             *
             *  @param[in] restrictedToLargestBags  A boolean flag indicating whether only the largest bags of the decomposition shall be considered or all of them.
             */
            HTD_API void setRestrictedToLargestBags(bool restrictedToLargestBags);

            /**
             *  Set the graph separator algorithm which shall be used.
             *
             *  @param[in] algorithm    The graph separator algorithm which shall be used.
             *
             *  @note When calling this method the control over the memory region of the graph separator algorithm is transferred to the manipulation
             *  operation. Deleting the graph separator algorithm provided to this method outside the manipulation operation or assigning the same
             *  graph separator algorithm multiple times will lead to undefined behavior.
             */
            HTD_API void setGraphSeparatorAlgorithm(htd::IGraphSeparatorAlgorithm * algorithm);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API WidthReductionOperation * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new WidthReductionOperation object identical to the current decomposition manipulation operation.
             */
            HTD_API WidthReductionOperation * clone(void) const;

            HTD_API htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_WIDTHREDUCTIONOPERATION_HPP */
