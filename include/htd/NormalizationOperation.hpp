/*
 * File:   NormalizationOperation.hpp
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

#ifndef HTD_HTD_NORMALIZATIONOPERATION_HPP
#define	HTD_HTD_NORMALIZATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    class NormalizationOperation : public htd::SemiNormalizationOperation
    {
        public:
            NormalizationOperation(void);

            NormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent, bool treatLeafNodesAsIntroduceNodes);

            virtual ~NormalizationOperation();

            void apply(htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            NormalizationOperation * clone(void) const HTD_OVERRIDE;

        private:
            bool emptyRoot_;

            bool emptyLeaves_;

            bool identicalJoinNodeParent_;

            bool treatLeafNodesAsIntroduceNodes_;
    };
}

#endif /* HTD_HTD_NORMALIZATIONOPERATION_HPP */
