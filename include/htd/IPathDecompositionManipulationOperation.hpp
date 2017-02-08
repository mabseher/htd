/*
 * File:   IPathDecompositionManipulationOperation.hpp
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

#ifndef HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP
#define HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     * Interface for algorithms which manipulate a given path decomposition.
     */
    class IPathDecompositionManipulationOperation : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~IPathDecompositionManipulationOperation() = 0;

            /**
             *  Apply the manipulation operation to the given path decomposition.
             *
             *  @param[in] graph            The graph from which the decomposition was computed.
             *  @param[in] decomposition    The path decomposition which shall be modified.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const = 0;

            /**
             *  Apply the manipulation operation to the given path decomposition under the assumption that only certain vertices need to be manipulated.
             *
             *  @note The provided collection of vertices acts only as a hint for the algorithm underlying the manipulation operation at hand. That is,
             *  it only indicates which vertices of the decomposition shall be considered at least. Depending on its implementation, an algorithm may
             *  also manipulate the complete decomposition.
             *
             *  @param[in] graph            The graph from which the decomposition was computed.
             *  @param[in] decomposition    The path decomposition which shall be modified.
             *  @param[in] relevantVertices The collection of vertices to which the manipulation shall be applied.
             *  @param[out] createdVertices A vector of vertices which were created by the manipulation operation.
             *  @param[out] removedVertices A vector of vertices which were removed by the manipulation operation.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const = 0;

            /**
             *  Apply the manipulation operation to the given path decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition        The path decomposition which shall be modified.
             *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const = 0;

            /**
             *  Apply the manipulation operation to the given path decomposition under the assumption that only certain vertices need to be manipulated.
             *
             *  @note The provided collection of vertices acts only as a hint for the algorithm underlying the manipulation operation at hand. That is,
             *  it only indicates which vertices of the decomposition shall be considered at least. Depending on its implementation, an algorithm may
             *  also manipulate the complete decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition        The path decomposition which shall be modified.
             *  @param[in] relevantVertices     The collection of vertices to which the manipulation shall be applied.
             *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
             *  @param[out] createdVertices     A vector of vertices which were created by the manipulation operation.
             *  @param[out] removedVertices     A vector of vertices which were removed by the manipulation operation.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current path decomposition manipulation operation.
             *
             *  @return A new IPathDecompositionManipulationOperation object identical to the current path decomposition manipulation operation.
             */
            virtual IPathDecompositionManipulationOperation * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current path decomposition manipulation operation.
             *
             *  @return A new IPathDecompositionManipulationOperation object identical to the current path decomposition manipulation operation.
             */
            virtual IPathDecompositionManipulationOperation * clonePathDecompositionManipulationOperation(void) const = 0;
#endif
    };
    
    inline htd::IPathDecompositionManipulationOperation::~IPathDecompositionManipulationOperation() { }
}

#endif /* HTD_HTD_IPATHDECOMPOSITIONMANIPULATIONOPERATION_HPP */
