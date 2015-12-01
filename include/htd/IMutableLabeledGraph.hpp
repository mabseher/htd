/* 
 * File:   IMutableLabeledGraph.hpp
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

#ifndef HTD_HTD_IMUTABLELABELEDGRAPH_HPP
#define	HTD_HTD_IMUTABLELABELEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/ILabeledGraph.hpp>

namespace htd
{
    class IMutableLabeledGraph : public virtual htd::ILabeledGraph, public virtual htd::IMutableGraph
    {
        public:
            virtual ~IMutableLabeledGraph() = 0;

            virtual void setLabel(std::string labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void swapLabel(std::string labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;
	    
            virtual void removeLabel(std::string labelName, htd::vertex_t vertex) = 0;
    };

    inline htd::IMutableLabeledGraph::~IMutableLabeledGraph() { }
}

#endif /* HTD_HTD_IMUTABLELABELEDGRAPH_HPP */
