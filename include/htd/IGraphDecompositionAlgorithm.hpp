/* 
 * File:   IGraphDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP
#define HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IGraphDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>
#include <htd/IPreprocessedGraph.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for algorithms which can be used to compute graph decompositions of a given graph.
     */
    class IGraphDecompositionAlgorithm
    {
        public:
            virtual ~IGraphDecompositionAlgorithm() = 0;

            /**
             *  Getter for the associated management class.
             *
             *  @return The associated management class.
             */
            virtual const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT = 0;

            /**
             *  Set a new management class for the library object.
             *
             *  @param[in] manager   The new management class for the library object.
             */
            virtual void setManagementInstance(const htd::LibraryInstance * const manager) = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph    The input graph to decompose.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const = 0;

            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph                The input graph to decompose.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it. The manipulation operations are applied in the given order.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] preprocessedGraph        The input graph in preprocessed format.
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
             *
             *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const = 0;

            /**
             *  Set the manipulations which are applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            virtual void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) = 0;

            /**
             *  Add a new manipulation operation which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory region of the manipulation operation is transferred to the decomposition
             *  algorithm. Deleting the manipulation operation provided to this method outside the decomposition algorithm or assigning the same
             *  manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperation    The manipulation operation which shall be applied globally to each decomposition generated by the algorithm.
             */
            virtual void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) = 0;

            /**
             *  Add additional manipulation operations which shall be applied globally to each decomposition generated by the algorithm. The manipulation operations are applied in the given order.
             *
             *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
             *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
             *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
             *
             *  @param[in] manipulationOperations   The manipulation operations which shall be applied globally to each decomposition generated by the algorithm.
             */
            virtual void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) = 0;

            /**
             *  Check whether the algorithm always returns a valid decomposition (or nulltpr) in case it is interrupted.
             *
             *  @return True if the algorithm always returns a valid decomposition (or nulltpr) in case it is interrupted, false otherwise.
             */
            virtual bool isSafelyInterruptible(void) const = 0;

            /**
             *  Check whether the edges induced by the bag contents shall be computed.
             *
             *  @return A boolean flag indicating whether the edges induced by the bag contents shall be computed.
             */
            virtual bool isComputeInducedEdgesEnabled(void) const = 0;

            /**
             *  Set whether the edges induced by the bag contents shall be computed.
             *
             *  @param[in] computeInducedEdgesEnabled   A boolean flag indicating whether the edges induced by the bag contents shall be computed.
             */
            virtual void setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled) = 0;

            /**
             *  Create a deep copy of the current graph decomposition algorithm.
             *
             *  @return A new IGraphDecompositionAlgorithm object identical to the current graph decomposition algorithm.
             */
            virtual IGraphDecompositionAlgorithm * clone(void) const = 0;
    };

    inline htd::IGraphDecompositionAlgorithm::~IGraphDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP */
