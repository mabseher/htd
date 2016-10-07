/* 
 * File:   IWidthLimitableOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_IWIDTHLIMITABLEORDERINGALGORITHM_HPP
#define	HTD_HTD_IWIDTHLIMITABLEORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

namespace htd
{
    /**
     * Interface for algorithms which can be used to compute vertex orderings.
     */
    class IWidthLimitableOrderingAlgorithm : public htd::IOrderingAlgorithm
    {
        public:
            virtual ~IWidthLimitableOrderingAlgorithm() = 0;

            /**
             *  Compute the vertex ordering of a given graph.
             *
             *  @param[in] graph        The input graph for which the vertex ordering shall be computed.
             *  @param[in] maxBagSize   The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
             *
             *  @return The vertex ordering of the given graph.
             */
            virtual htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize) const HTD_NOEXCEPT = 0;

            /**
             *  Compute the vertex ordering of a given graph and write it to the end of a given vector.
             *
             *  @param[in] graph        The input graph for which the vertex ordering shall be computed.
             *  @param[in] maxBagSize   The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
             *  @param[out] target      The target vector to which the ordering shall be appended.
             */
            virtual void writeOrderingTo(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::vector<htd::vertex_t> & target) const HTD_NOEXCEPT = 0;

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
