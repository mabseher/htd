/* 
 * File:   AdvancedMinFillOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_HPP
#define	HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IOrderingAlgorithm.hpp>

#include <vector>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface based on the minimum-fill elimination ordering algorithm.
     *  If there are multiple vertices with the same, minimal fill value during an elimination step this algorithm
     *  will select a vertex with minimum degree from the pool of vertices with minimum fill value.
     */
    class AdvancedMinFillOrderingAlgorithm : public htd::IOrderingAlgorithm
    {
        public:
            /**
             *  Constructor for a new ordering algorithm of type AdvancedMinFillOrderingAlgorithm.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API AdvancedMinFillOrderingAlgorithm(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~AdvancedMinFillOrderingAlgorithm();
            
            HTD_API htd::ConstCollection<htd::vertex_t> computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void writeOrderingTo(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

            HTD_API AdvancedMinFillOrderingAlgorithm * clone(void) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            AdvancedMinFillOrderingAlgorithm & operator=(const AdvancedMinFillOrderingAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_ADVANCEDMINFILLORDERINGALGORITHM_HPP */
