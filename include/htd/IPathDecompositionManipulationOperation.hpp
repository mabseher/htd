/*
 * File:   IPathDecompositionManipulationOperation.hpp
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

#ifndef HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP
#define	HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

namespace htd
{
    class IPathDecompositionManipulationOperation : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~IPathDecompositionManipulationOperation() = 0;

            virtual void apply(htd::IMutablePathDecomposition & decomposition) const = 0;

            virtual void apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const = 0;

            /**
             *  Create a deep copy the current path decomposition manipulation operation.
             *
             *  @return A new IPathDecompositionManipulationOperation object identical to the current path decomposition manipulation operation.
             */
            virtual IPathDecompositionManipulationOperation * clone(void) const HTD_OVERRIDE = 0;
    };
    
    inline htd::IPathDecompositionManipulationOperation::~IPathDecompositionManipulationOperation() { }
}

#endif /* HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP */
