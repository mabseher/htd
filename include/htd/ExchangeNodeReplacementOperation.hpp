/*
 * File:   ExchangeNodeReplacementOperation.hpp
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

#ifndef HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_HPP
#define	HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     *  Implementation of the IDecompositionManipulationOperation interface which manipulates
     *  given tree and path decompositions in such a way that there is no bag which contains
     *  introduced and forgotten vertices at the same time.
     */
    class ExchangeNodeReplacementOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            ExchangeNodeReplacementOperation(void);

            ~ExchangeNodeReplacementOperation();

            void apply(htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const HTD_OVERRIDE;

            void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const HTD_OVERRIDE;

            bool isLocalOperation(void) const HTD_OVERRIDE;

            bool createsTreeNodes(void) const HTD_OVERRIDE;

            bool removesTreeNodes(void) const HTD_OVERRIDE;

            bool modifiesBagContents(void) const HTD_OVERRIDE;

            bool createsLocationDependendLabels(void) const HTD_OVERRIDE;

            ExchangeNodeReplacementOperation * clone(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_HPP */
