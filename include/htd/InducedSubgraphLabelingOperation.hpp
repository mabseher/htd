/*
 * File:   InducedSubgraphLabelingOperation.hpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_HPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/Label.hpp>

#include <utility>

namespace htd
{
    class InducedSubgraphLabelingOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            /**
             *  Constant for the identifier of the induced subgraph label.
             */
            static constexpr const char * INDUCED_SUBGRAPH_LABEL_IDENTIFIER = "Induced Subgraph";

            InducedSubgraphLabelingOperation(const htd::IHypergraph & graph);

            ~InducedSubgraphLabelingOperation();

            void apply(htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            InducedSubgraphLabelingOperation * clone(void) const HTD_OVERRIDE;

        private:
            const htd::IHypergraph & graph_;

            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> & hyperedges) const;
    };
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_HPP */
