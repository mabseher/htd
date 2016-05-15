/* 
 * File:   IGraphDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IGraphDecomposition.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>

#include <vector>

namespace htd
{
    class IGraphDecompositionAlgorithm
    {
        public:
            virtual ~IGraphDecompositionAlgorithm() = 0;
            
            /**
             *  Compute a decomposition of the given graph.
             *
             *  @param[in] graph    The input graph to decompose.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph) const = 0;

            /**
             *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
             *
             *  @param[in] graph                    The input graph to decompose.
             *  @param[in] manipulationOperations   The manipulation operations which should be applied.
             *
             *  @return A new IGraphDecomposition object representing the decomposition of the given graph.
             */
            virtual htd::IGraphDecomposition * computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const = 0;

            virtual void setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) = 0;

            virtual void addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation) = 0;

            virtual void addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) = 0;

            /**
             *  Create a deep copy the current graph decomposition algorithm.
             *
             *  @return A new IGraphDecompositionAlgorithm object identical to the current graph decomposition algorithm.
             */
            virtual IGraphDecompositionAlgorithm * clone(void) const = 0;
    };

    inline htd::IGraphDecompositionAlgorithm::~IGraphDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP */
