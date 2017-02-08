/*
 * File:   ExhaustiveVertexSelectionStrategy.hpp
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

#ifndef HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_HPP
#define HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_HPP

#include <htd/Globals.hpp>

#include <htd/IVertexSelectionStrategy.hpp>

namespace htd
{
    /**
     * Vertex selection strategy selecting each vertex of a given input graph.
     */
    class ExhaustiveVertexSelectionStrategy : public htd::IVertexSelectionStrategy
    {
        public:
            HTD_API ExhaustiveVertexSelectionStrategy(void);

            HTD_API virtual ~ExhaustiveVertexSelectionStrategy();

            HTD_API void selectVertices(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            /**
             *  Create a deep copy of the current vertex selection strategy.
             *
             *  @return A new ExhaustiveVertexSelectionStrategy object identical to the current vertex selection strategy.
             */
            HTD_API ExhaustiveVertexSelectionStrategy * clone(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_EXHAUSTIVEVERTEXSELECTIONSTRATEGY_HPP */
