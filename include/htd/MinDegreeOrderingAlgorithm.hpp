/* 
 * File:   MinDegreeOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_MINDEGREEORDERINGALGORITHM_HPP
#define	HTD_HTD_MINDEGREEORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

#include <vector>
#include <algorithm>
#include <unordered_set>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface based on the minimum-degree elimination ordering algorithm.
     */
    class MinDegreeOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            MinDegreeOrderingAlgorithm(void);
            
            ~MinDegreeOrderingAlgorithm();
            
            htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph) const HTD_OVERRIDE;

            void writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            MinDegreeOrderingAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            MinDegreeOrderingAlgorithm & operator=(const MinDegreeOrderingAlgorithm &) { return *this; }
    };
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_HPP */
