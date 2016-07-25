/*
 * File:   IntroducedSubgraphLabelingOperation.hpp
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

#ifndef HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_HPP
#define	HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/Label.hpp>

#include <utility>

namespace htd
{
    /**
     *  Implementation of the ILabelingFunction interface which returns labels containing the hyperedges induced by the given bag which are not already introduced by a child bag.
     */
    class IntroducedSubgraphLabelingOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constant for the identifier of the induced subgraph label.
             */
            static constexpr const char * INTRODUCED_SUBGRAPH_LABEL_IDENTIFIER = "Introduced Subgraph";

            /**
             *  Constructor for a new manipulation operation of type InducedSubgraphLabelingOperation.
             *
             *  @param[in] graph    The graph from which the introduced edges for the induced subgraph of each bag shall be computed.
             */
            IntroducedSubgraphLabelingOperation(const htd::IMultiHypergraph & graph);

            ~IntroducedSubgraphLabelingOperation();

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

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            IntroducedSubgraphLabelingOperation * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current decomposition manipulation operation.
             *
             *  @return A new IntroducedSubgraphLabelingOperation object identical to the current decomposition manipulation operation.
             */
            IntroducedSubgraphLabelingOperation * clone(void) const;

            htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            htd::IPathDecompositionManipulationOperation * clonePathDecompositionManipulationOperation(void) const HTD_OVERRIDE;

            htd::ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const HTD_OVERRIDE;
#endif
        private:
            const htd::IMultiHypergraph & graph_;
    };
}

#endif /* HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_HPP */
