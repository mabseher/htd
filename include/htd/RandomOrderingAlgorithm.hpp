/* 
 * File:   RandomOrderingAlgorithm.hpp
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

#ifndef HTD_HTD_RANDOMORDERINGALGORITHM_HPP
#define HTD_HTD_RANDOMORDERINGALGORITHM_HPP

#include <vector>

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IOrderingAlgorithm.hpp>

namespace htd
{
    /**
     *  Implementation of the IOrderingAlgorithm interface returning the vertices of the given graph in ascending order.
     */
    class RandomOrderingAlgorithm : public virtual htd::IOrderingAlgorithm
    {
        public:
            /**
             *  Constructor for a new ordering algorithm of type RandomOrderingAlgorithm.
             *
             *  @param[in] manager   The management instance to which the new algorithm belongs.
             */
            HTD_API RandomOrderingAlgorithm(const htd::LibraryInstance * const manager);
            
            HTD_API virtual ~RandomOrderingAlgorithm();
            
            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API htd::IVertexOrdering * computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            HTD_API void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API RandomOrderingAlgorithm * clone(void) const HTD_OVERRIDE;
#else
            HTD_API RandomOrderingAlgorithm * clone(void) const;

            HTD_API htd::IOrderingAlgorithm * cloneOrderingAlgorithm(void) const HTD_OVERRIDE;
#endif

        protected:
            /**
             *  Copy assignment operator for an ordering algorithm.
             *
             *  @note This operator is protected to prevent assignments to an already initialized algorithm.
             */
            RandomOrderingAlgorithm & operator=(const RandomOrderingAlgorithm &) { return *this; }

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_RANDOMORDERINGALGORITHM_HPP */
