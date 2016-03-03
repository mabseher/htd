/*
 * File:   WeakNormalizationOperation.hpp
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

#ifndef HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP
#define	HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    class WeakNormalizationOperation : public virtual htd::IPathDecompositionManipulationOperation, public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            WeakNormalizationOperation(void);

            WeakNormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent);

            virtual ~WeakNormalizationOperation();

            virtual void apply(htd::IMutablePathDecomposition & decomposition) const HTD_OVERRIDE;

            virtual void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            virtual void apply(htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            virtual void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            bool emptyRootRequired(void) const;

            bool emptyLeavesRequired(void) const;

            bool identicalJoinNodeParentRequired(void) const;

            WeakNormalizationOperation * clone(void) const HTD_OVERRIDE;

        private:
            bool emptyRoot_;

            bool emptyLeaves_;

            bool identicalJoinNodeParent_;
    };
}

#endif /* HTD_HTD_WEAKNORMALIZATIONOPERATION_HPP */
