/* 
 * File:   MinDegreeOrderingAlgorithm.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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
#include <htd/IHypergraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>

#include <vector>
#include <algorithm>
#include <unordered_set>

#include <iostream>

namespace htd
{
    class MinDegreeOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            MinDegreeOrderingAlgorithm(void);
            
            ~MinDegreeOrderingAlgorithm();
            
            void computeOrdering(const IHypergraph& graph, std::vector<htd::vertex_t>& result) const HTD_OVERRIDE;

            MinDegreeOrderingAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            MinDegreeOrderingAlgorithm & operator=(const MinDegreeOrderingAlgorithm &) { return *this; }

        private:
            void set_union(const std::vector<htd::vertex_t> & set1,
                           const std::vector<htd::vertex_t> & set2,
                           htd::vertex_t ignoredVertex,
                           std::vector<htd::vertex_t> & result) const;
    };
}

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_HPP */
