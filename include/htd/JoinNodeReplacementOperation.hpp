/*
 * File:   JoinNodeReplacementOperation.hpp
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

#ifndef HTD_HTD_JOINNODEREPLACEMENTOPERATION_HPP
#define	HTD_HTD_JOINNODEREPLACEMENTOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>

namespace htd
{
    class JoinNodeReplacementOperation : public virtual htd::ITreeDecompositionManipulationOperation
    {
        public:
            JoinNodeReplacementOperation(void);

            ~JoinNodeReplacementOperation();

            void apply(htd::IMutableTreeDecomposition & decomposition) const HTD_OVERRIDE;

            void apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            JoinNodeReplacementOperation * clone(void) const HTD_OVERRIDE;

        private:
            void getChildrenVertexLabelSetUnion(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex, htd::vertex_container & output) const;
    };
}

#endif /* HTD_HTD_JOINNODEREPLACEMENTOPERATION_HPP */
