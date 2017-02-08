/*
 * File:   IVertexSelectionStrategy.hpp
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

#ifndef HTD_HTD_IVERTEXSELECTIONSTRATEGY_HPP
#define HTD_HTD_IVERTEXSELECTIONSTRATEGY_HPP

#include <htd/Globals.hpp>

#include <htd/IMultiHypergraph.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for algorithms which select certain vertices from a given input graph.
     */
    class IVertexSelectionStrategy
    {
        public:
            virtual ~IVertexSelectionStrategy() = 0;

            /**
             *  Select a subset of the vertices of a graph and append them to a given target vector.
             *
             *  @param[in] graph    The graph from which the vertices shall be selected.
             *  @param[out] target  The target vector to which the selected vertices shall be appended.
             */
            virtual void selectVertices(const htd::IMultiHypergraph & graph, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Create a deep copy of the current vertex selection strategy.
             *
             *  @return A new IVertexSelectionStrategy object identical to the current vertex selection strategy.
             */
            virtual IVertexSelectionStrategy * clone(void) const = 0;
    };
    
    inline htd::IVertexSelectionStrategy::~IVertexSelectionStrategy() { }
}

#endif /* HTD_HTD_IVERTEXSELECTIONSTRATEGY_HPP */
