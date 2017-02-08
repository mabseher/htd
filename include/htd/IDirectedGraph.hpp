/* 
 * File:   IDirectedGraph.hpp
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

#ifndef HTD_HTD_IDIRECTEDGRAPH_HPP
#define HTD_HTD_IDIRECTEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/IDirectedMultiGraph.hpp>

namespace htd
{
    /**
     * Interface for classes which represent directed graphs.
     */
    class IDirectedGraph : public virtual htd::IGraph, public virtual htd::IDirectedMultiGraph
    {
        public:
            virtual ~IDirectedGraph() = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current directed graph.
             *
             *  @return A new IDirectedGraph object identical to the current directed graph.
             */
            virtual IDirectedGraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current directed graph.
             *
             *  @return A new IDirectedGraph object identical to the current directed graph.
             */
            virtual IDirectedGraph * cloneDirectedGraph(void) const = 0;
#endif
    };

    inline htd::IDirectedGraph::~IDirectedGraph() { }
}

#endif /* HTD_HTD_IDIRECTEDGRAPH_HPP */
