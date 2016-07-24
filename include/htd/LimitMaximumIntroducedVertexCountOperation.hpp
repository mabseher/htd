/*
 * File:   LimitMaximumIntroducedVertexCountOperation.hpp
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

#ifndef HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP
#define	HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP

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
            using htd::IPathDecompositionManipulationOperation::clone;
            using htd::ITreeDecompositionManipulationOperation::clone;

            /**
             *  Constructor for a new manipulation operation of type LimitMaximumIntroducedVertexCountOperation.
             *
             *  @param[in] limit    The maximum number of introduced vertices for a decomposition node.
             *
             *  @note Leaf nodes are not treated as introduce nodes by default, i.e. the provided limit does not apply to leaf nodes.
             */
            LimitMaximumIntroducedVertexCountOperation(std::size_t limit);

            /**
             *  Constructor for a new manipulation operation of type LimitMaximumIntroducedVertexCountOperation.
             *
             *  @param[in] limit                            The maximum number of introduced vertices for a decomposition node.
             *  @param[in] treatLeafNodesAsIntroduceNodes   A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
             */
            LimitMaximumIntroducedVertexCountOperation(std::size_t limit, bool treatLeafNodesAsIntroduceNodes);

            ~LimitMaximumIntroducedVertexCountOperation();

            void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            bool isLocalOperation(void) const HTD_OVERRIDE;

            bool createsTreeNodes(void) const HTD_OVERRIDE;

            bool removesTreeNodes(void) const HTD_OVERRIDE;

            bool modifiesBagContents(void) const HTD_OVERRIDE;

            bool createsSubsetMaximalBags(void) const HTD_OVERRIDE;

            bool createsLocationDependendLabels(void) const HTD_OVERRIDE;

            LimitMaximumIntroducedVertexCountOperation * clone(void) const HTD_OVERRIDE;

        private:
            std::size_t limit_;

            bool treatLeafNodesAsIntroduceNodes_;
    };
}

#endif /* HTD_HTD_LIMITMAXIMUMINTRODUCEDVERTEXCOUNTOPERATION_HPP */
