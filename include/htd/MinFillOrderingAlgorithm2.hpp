/* 
 * File:   MinFillOrderingAlgorithm2.hpp
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

#ifndef HTD_HTD_MINFILLORDERINGALGORITHM2_HPP
#define	HTD_HTD_MINFILLORDERINGALGORITHM2_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/SortedVertexSet.hpp>

#include <vector>
#include <algorithm>
#include <unordered_map>

namespace htd
{
    class MinFillOrderingAlgorithm2 : public virtual htd::IOrderingAlgorithm
    {
        public:
            MinFillOrderingAlgorithm2(void);
            
            ~MinFillOrderingAlgorithm2();
            
            htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            MinFillOrderingAlgorithm2 * clone(void) const HTD_OVERRIDE;

        protected:
            MinFillOrderingAlgorithm2 & operator=(const MinFillOrderingAlgorithm2 &) { return *this; }

        private:
            std::size_t computeEdgeCount(const std::unordered_map<htd::vertex_t, htd::SortedVertexSet> & availableNeighborhoods, const htd::SortedVertexSet & vertices) const;

            void decompose_sets(const htd::SortedVertexSet & set1,
                                const htd::SortedVertexSet & set2,
                                htd::vertex_t ignoredVertex,
                                std::vector<htd::vertex_t> & resultOnlySet1,
                                std::vector<htd::vertex_t> & resultOnlySet2,
                                std::vector<htd::vertex_t> & resultIntersection) const;
    };
}

#endif /* HTD_HTD_MINFILLORDERINGALGORITHM2_HPP */
