/*
 * File:   WeakNormalizationOperation.hpp
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

#ifndef HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP
#define HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Implementation of the IDecompositionManipulationOperation interface which manipulates
     *  given tree and path decompositions such that each child of a join node has the same
     *  bag content as the join node itself.
     */
    class WeakNormalizationOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constructor for a new manipulation operation of type WeakNormalizationOperation.
             *
             *  @param[in] manager   The management instance to which the new manipulation operation belongs.
             */
            HTD_API WeakNormalizationOperation(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a new manipulation operation of type WeakNormalizationOperation.
             *
             *  @param[in] manager                   The management instance to which the new manipulation operation belongs.
             *  @param[in] emptyRoot                A boolean flag whether the decomposition shall have a root node with empty bag.
             *  @param[in] emptyLeaves              A boolean flag whether the decomposition's leave nodes shall have an empty bag.
             *  @param[in] identicalJoinNodeParent  A boolean flag whether each join node shall have a parent with equal bag content.
             */
            HTD_API WeakNormalizationOperation(const htd::LibraryInstance * const manager, bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent);

            HTD_API virtual ~WeakNormalizationOperation();

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            HTD_API void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

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
             *  Check whether the flag is set that the decomposition shall have a root node with empty bag.
             *
             *  @return True if the decomposition shall have a root node with empty bag, false otherwise.
             */
            HTD_API bool emptyRootRequired(void) const;

            /**
             *  Check whether the flag is set that the decomposition's leave nodes shall have an empty bag.
             *
             *  @return True if the decomposition's leave nodes shall have an empty bag, false otherwise.
             */
            HTD_API bool emptyLeavesRequired(void) const;

            /**
             *  Check whether the flag is set that each join node shall have a parent with equal bag content.
             *
             *  @return True if each join node shall have a parent with equal bag content, false otherwise.
             */
            HTD_API bool identicalJoinNodeParentRequired(void) const;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API WeakNormalizationOperation * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new WeakNormalizationOperation object identical to the current decomposition manipulation operation.
             */
            HTD_API WeakNormalizationOperation * clone(void) const;

            HTD_API htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::IPathDecompositionManipulationOperation * clonePathDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP */
