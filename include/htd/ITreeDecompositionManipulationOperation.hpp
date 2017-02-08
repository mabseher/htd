/*
 * File:   ITreeDecompositionManipulationOperation.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITIONMANIPULATIONOPERATION_HPP
#define HTD_HTD_ITREEDECOMPOSITIONMANIPULATIONOPERATION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

namespace htd
{
    /**
     * Interface for algorithms which manipulate a given tree decomposition.
     */
    class ITreeDecompositionManipulationOperation : public virtual htd::IDecompositionManipulationOperation
    {
        public:
            virtual ~ITreeDecompositionManipulationOperation() = 0;

            /**
             *  Apply the manipulation operation to the given tree decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition    The tree decomposition which shall be modified.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const = 0;

            /**
             *  Apply the manipulation operation to the given tree decomposition under the assumption that only certain vertices need to be manipulated.
             *
             *  @note The provided collection of vertices acts only as a hint for the algorithm underlying the manipulation operation at hand. That is,
             *  it only indicates which vertices of the decomposition shall be considered at least. Depending on its implementation, an algorithm may
             *  also manipulate the complete decomposition.
             *
             *  @param[in] graph            The graph from which the decomposition was computed.
             *  @param[in] decomposition    The tree decomposition which shall be modified.
             *  @param[in] relevantVertices The collection of vertices to which the manipulation shall be applied.
             *  @param[out] createdVertices A vector of vertices which were created by the manipulation operation.
             *  @param[out] removedVertices A vector of vertices which were removed by the manipulation operation.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const = 0;

            /**
             *  Apply the manipulation operation to the given tree decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition        The tree decomposition which shall be modified.
             *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const = 0;

            /**
             *  Apply the manipulation operation to the given tree decomposition under the assumption that only certain vertices need to be manipulated.
             *
             *  @note The provided collection of vertices acts only as a hint for the algorithm underlying the manipulation operation at hand. That is,
             *  it only indicates which vertices of the decomposition shall be considered at least. Depending on its implementation, an algorithm may
             *  also manipulate the complete decomposition.
             *
             *  @param[in] graph                The graph from which the decomposition was computed.
             *  @param[in] decomposition        The tree decomposition which shall be modified.
             *  @param[in] relevantVertices     The collection of vertices to which the manipulation shall be applied.
             *  @param[in] labelingFunctions    A vector of labeling functions which shall be applied after the modifications.
             *  @param[out] createdVertices     A vector of vertices which were created by the manipulation operation.
             *  @param[out] removedVertices     A vector of vertices which were removed by the manipulation operation.
             */
            virtual void apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const = 0;

            /**
             *  Check whether the manipulation operation - when given a set of relevant vertices - only applies to those vertices and their direct neighbors.
             *
             *  @return True if the manipulation operation - when given a set of relevant vertices - only applies to those vertices and their direct neighbors, false otherwise.
             */
            virtual bool isLocalOperation(void) const = 0;

            /**
             *  Check whether the manipulation operation potentially creates new tree decomposition nodes.
             *
             *  @return True if the manipulation operation potentially creates new tree decomposition nodes, false otherwise.
             */
            virtual bool createsTreeNodes(void) const = 0;

            /**
             *  Check whether the manipulation operation potentially removes existing tree decomposition nodes.
             *
             *  @return True if the manipulation operation potentially removes existing tree decomposition nodes, false otherwise.
             */
            virtual bool removesTreeNodes(void) const = 0;

            /**
             *  Check whether the manipulation operation modifies the bag content of existing tree decomposition nodes.
             *
             *  @return True if the manipulation operation modifies the bag content of existing tree decomposition nodes, false otherwise.
             */
            virtual bool modifiesBagContents(void) const = 0;

            /**
             *  Check whether the manipulation operation may create subset maximal bags.
             *
             *  @return True if the manipulation operation may create subset maximal bags, false otherwise.
             */
            virtual bool createsSubsetMaximalBags(void) const = 0;

            /**
             *  Check whether the manipulation operation creates labels which are dependend on the position or neighbors of a
             *  vertex within the decomposition (in case of vertex labels) or the endpoints of an edge (in case of edge labels).
             *
             *  @return True if the manipulation operation creates labels which are dependend on the position or neighbors of a
             *  vertex within the decomposition (in case of vertex labels) or the endpoints of an edge (in case of edge labels), false otherwise.
             */
            virtual bool createsLocationDependendLabels(void) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current tree decomposition manipulation operation.
             *
             *  @return A new ITreeDecompositionManipulationOperation object identical to the current tree decomposition manipulation operation.
             */
            virtual ITreeDecompositionManipulationOperation * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current tree decomposition manipulation operation.
             *
             *  @return A new ITreeDecompositionManipulationOperation object identical to the current tree decomposition manipulation operation.
             */
            virtual ITreeDecompositionManipulationOperation * cloneTreeDecompositionManipulationOperation(void) const = 0;
#endif
    };
    
    inline htd::ITreeDecompositionManipulationOperation::~ITreeDecompositionManipulationOperation() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITIONMANIPULATIONOPERATION_HPP */
