/*
 * File:   LimitMaximumIntroducedVertexCountOperation.hpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP
#define HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Implementation of the IDecompositionManipulationOperation interface which manipulates given
     *  tree and path decompositions in such a way that for each decomposition node the cardinality
     *  of the set difference between the node's bag and the set union of the node's child bags is
     *  bounded by the given limit.
     */
    class LimitMaximumIntroducedVertexCountOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constructor for a new manipulation operation of type LimitMaximumIntroducedVertexCountOperation.
             *
             *  @param[in] manager                           The management instance to which the new manipulation operation belongs.
             *  @param[in] limit                            The maximum number of introduced vertices for a decomposition node.
             *  @param[in] treatLeafNodesAsIntroduceNodes   A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
             */
            HTD_API LimitMaximumIntroducedVertexCountOperation(const htd::LibraryInstance * const manager, std::size_t limit, bool treatLeafNodesAsIntroduceNodes = false);

            HTD_API virtual ~LimitMaximumIntroducedVertexCountOperation();

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

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LimitMaximumIntroducedVertexCountOperation * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new LimitMaximumIntroducedVertexCountOperation object identical to the current decomposition manipulation operation.
             */
            HTD_API LimitMaximumIntroducedVertexCountOperation * clone(void) const;

            HTD_API htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::IPathDecompositionManipulationOperation * clonePathDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP */
