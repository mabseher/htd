/* 
 * File:   ILabeledDirectedGraph.hpp
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

#ifndef HTD_HTD_ILABELEDDIRECTEDGRAPH_HPP
#define HTD_HTD_ILABELEDDIRECTEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IDirectedGraph.hpp>
#include <htd/ILabeledGraph.hpp>
#include <htd/ILabeledDirectedMultiGraph.hpp>

#include <string>

namespace htd
{
    /**
     * Interface for classes which represent labeled directed graphss.
     */
    class ILabeledDirectedGraph : public virtual htd::IDirectedGraph, public virtual htd::ILabeledGraph, public virtual htd::ILabeledDirectedMultiGraph
    {
        public:
            virtual ~ILabeledDirectedGraph() = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current labeled directed graph.
             *
             *  @return A new ILabeledDirectedGraph object identical to the current labeled directed graph.
             */
            virtual ILabeledDirectedGraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current labeled directed graph.
             *
             *  @return A new ILabeledDirectedGraph object identical to the current labeled directed graph.
             */
            virtual ILabeledDirectedGraph * cloneLabeledDirectedGraph(void) const = 0;
#endif
    };

    inline htd::ILabeledDirectedGraph::~ILabeledDirectedGraph() { }
}

#endif /* HTD_HTD_ILABELEDDIRECTEDGRAPH_HPP */
