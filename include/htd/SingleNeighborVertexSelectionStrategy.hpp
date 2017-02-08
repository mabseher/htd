/*
 * File:   SingleNeighborVertexSelectionStrategy.hpp
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

#ifndef HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_HPP
#define HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_HPP

#include <htd/Globals.hpp>

#include <htd/IVertexSelectionStrategy.hpp>

namespace htd
{
    /**
     * Vertex selection strategy selecting each vertex of a given input graph which has exactly one neighbor.
     */
    class SingleNeighborVertexSelectionStrategy : public htd::IVertexSelectionStrategy
    {
        public:
            /**
             *  Constructor for a new selection strategy of type SingleNeighborVertexSelectionStrategy.
             */
            HTD_API SingleNeighborVertexSelectionStrategy(void);

            /**
             *  Constructor for a new selection strategy of type SingleNeighborVertexSelectionStrategy.
             *
             *  @param[in] limit    The maximum number of vertices which shall be selected from a given input graph.
             */
            HTD_API SingleNeighborVertexSelectionStrategy(std::size_t limit);

            HTD_API virtual ~SingleNeighborVertexSelectionStrategy();

            HTD_API void selectVertices(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            /**
             *  Create a deep copy of the current vertex selection strategy.
             *
             *  @return A new SingleNeighborVertexSelectionStrategy object identical to the current vertex selection strategy.
             */
            HTD_API SingleNeighborVertexSelectionStrategy * clone(void) const HTD_OVERRIDE;

        private:
            std::size_t limit_;
    };
}

#endif /* HTD_HTD_SINGLENEIGHBORVERTEXSELECTIONSTRATEGY_HPP */
