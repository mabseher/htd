/* 
 * File:   ILabeledGraph.hpp
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

#ifndef HTD_HTD_ILABELEDGRAPH_HPP
#define HTD_HTD_ILABELEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/ILabeledMultiGraph.hpp>

namespace htd
{
    /**
     * Interface for classes which represent labeled graphs.
     */
    class ILabeledGraph : public virtual htd::IGraph, public virtual htd::ILabeledHypergraph, public virtual htd::ILabeledMultiGraph
    {
        public:
            virtual ~ILabeledGraph() = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current labeled graph.
             *
             *  @return A new ILabeledGraph object identical to the current labeled graph.
             */
            virtual ILabeledGraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current labeled graph.
             *
             *  @return A new ILabeledGraph object identical to the current labeled graph.
             */
            virtual ILabeledGraph * cloneLabeledGraph(void) const = 0;
#endif
    };

    inline htd::ILabeledGraph::~ILabeledGraph() { }
}

#endif /* HTD_HTD_ILABELEDGRAPH_HPP */
