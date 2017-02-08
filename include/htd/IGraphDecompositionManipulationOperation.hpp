/*
 * File:   IGraphDecompositionManipulationOperation.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITIONMANIPULATIONOPERATION_HPP
#define HTD_HTD_IGRAPHDECOMPOSITIONMANIPULATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableGraphDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     * Interface for algorithms which manipulate a given graph decomposition.
     */
    class IGraphDecompositionManipulationOperation : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~IGraphDecompositionManipulationOperation() = 0;

            /**
             *  Apply the manipulation operation to the given graph decomposition.
             *
             *  @param[in] graph            The graph from which the decomposition was computed.
             *  @param[in] decomposition    The graph decomposition which shall be modified.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableGraphDecomposition & decomposition) const = 0;

            /**
             *  Apply the manipulation operation to the given graph decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition        The graph decomposition which shall be modified.
             *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableGraphDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current graph decomposition manipulation operation.
             *
             *  @return A new IGraphDecompositionManipulationOperation object identical to the current graph decomposition manipulation operation.
             */
            virtual IGraphDecompositionManipulationOperation * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current graph decomposition manipulation operation.
             *
             *  @return A new IGraphDecompositionManipulationOperation object identical to the current graph decomposition manipulation operation.
             */
            virtual IGraphDecompositionManipulationOperation * cloneGraphDecompositionManipulationOperation(void) const = 0;
#endif
    };
    
    inline htd::IGraphDecompositionManipulationOperation::~IGraphDecompositionManipulationOperation() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITIONMANIPULATIONOPERATION_HPP */
