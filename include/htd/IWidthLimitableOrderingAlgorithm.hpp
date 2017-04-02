/* 
 * File:   IWidthLimitableOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_IWIDTHLIMITABLEORDERINGALGORITHM_HPP
#define HTD_HTD_IWIDTHLIMITABLEORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IWidthLimitedVertexOrdering.hpp>

namespace htd
{
    /**
     * Interface for algorithms which can be used to compute vertex orderings.
     */
    class IWidthLimitableOrderingAlgorithm : public htd::IOrderingAlgorithm
    {
        public:
            using htd::IOrderingAlgorithm::computeOrdering;

            virtual ~IWidthLimitableOrderingAlgorithm() = 0;

            /**
             *  Compute the vertex ordering of a given graph.
             *
             *  @param[in] graph                The input graph for which the vertex ordering shall be computed.
             *  @param[in] maxBagSize           The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
             *  @param[in] maxIterationCount    The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which an empty ordering is returned.
             *
             *  @return The vertex ordering of the given graph.
             */
            virtual htd::IWidthLimitedVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT = 0;

            /**
             *  Compute the vertex ordering of a given graph.
             *
             *  @param[in] graph                The input graph for which the vertex ordering shall be computed.
             *  @param[in] preprocessedGraph    The input graph in preprocessed format.
             *  @param[in] maxBagSize           The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
             *  @param[in] maxIterationCount    The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which an empty ordering is returned.
             *
             *  @return The vertex ordering of the given graph.
             */
            virtual htd::IWidthLimitedVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current ordering algorithm.
             *
             *  @return A new IWidthLimitableOrderingAlgorithm object identical to the current ordering algorithm.
             */
            virtual IWidthLimitableOrderingAlgorithm * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current ordering algorithm.
             *
             *  @return A new IWidthLimitableOrderingAlgorithm object identical to the current ordering algorithm.
             */
            virtual IWidthLimitableOrderingAlgorithm * cloneWidthLimitableOrderingAlgorithm(void) const = 0;
#endif
    };

    inline htd::IWidthLimitableOrderingAlgorithm::~IWidthLimitableOrderingAlgorithm() { }
}

#endif /* HTD_HTD_IWIDTHLIMITABLEORDERINGALGORITHM_HPP */
