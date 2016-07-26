/* 
 * File:   MinFillOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_MINFILLORDERINGALGORITHM_HPP
#define	HTD_HTD_MINFILLORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface based on the minimum-fill elimination ordering algorithm.
     */
    class HTD_API MinFillOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            MinFillOrderingAlgorithm(void);
            
            ~MinFillOrderingAlgorithm();
            
            htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            void writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_NOEXCEPT HTD_OVERRIDE;

            MinFillOrderingAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            MinFillOrderingAlgorithm & operator=(const MinFillOrderingAlgorithm &) { return *this; }

        private:
            std::size_t computeEdgeCount(const std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> & availableNeighborhoods, const std::vector<htd::vertex_t> & vertices) const HTD_NOEXCEPT;

            void decompose_sets(const std::vector<htd::vertex_t> & set1,
                                const std::vector<htd::vertex_t> & set2,
                                htd::vertex_t ignoredVertex,
                                std::vector<htd::vertex_t> & resultOnlySet1,
                                std::vector<htd::vertex_t> & resultOnlySet2,
                                std::vector<htd::vertex_t> & resultIntersection) const HTD_NOEXCEPT;
    };
}

#endif /* HTD_HTD_MINFILLORDERINGALGORITHM_HPP */
