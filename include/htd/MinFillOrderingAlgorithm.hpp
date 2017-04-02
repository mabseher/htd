/* 
 * File:   MinFillOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_MINFILLORDERINGALGORITHM_HPP
#define HTD_HTD_MINFILLORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IWidthLimitableOrderingAlgorithm.hpp>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface based on the minimum-fill elimination ordering algorithm.
     */
    class MinFillOrderingAlgorithm : public htd::IWidthLimitableOrderingAlgorithm
    {
        public:
            /**
             *  Constructor for a new ordering algorithm of type AdvancedMinFillOrderingAlgorithm.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API MinFillOrderingAlgorithm(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~MinFillOrderingAlgorithm();

            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::IWidthLimitedVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::IWidthLimitedVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API MinFillOrderingAlgorithm * clone(void) const HTD_OVERRIDE;
#else
            HTD_API MinFillOrderingAlgorithm * clone(void) const;

            HTD_API htd::IOrderingAlgorithm * cloneOrderingAlgorithm(void) const HTD_OVERRIDE;

            HTD_API htd::IWidthLimitableOrderingAlgorithm * cloneWidthLimitableOrderingAlgorithm(void) const HTD_OVERRIDE;
#endif

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            MinFillOrderingAlgorithm & operator=(const MinFillOrderingAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_MINFILLORDERINGALGORITHM2_HPP */
