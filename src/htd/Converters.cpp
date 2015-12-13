/* 
 * File:   Converters.cpp
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

#ifndef HTD_HTD_CONVERTERS_CPP
#define	HTD_HTD_CONVERTERS_CPP

#include <htd/Converters.hpp>
#include <htd/IDirectedGraph.hpp>
#include <htd/IGraph.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableGraph.hpp>

namespace htd
{
    htd::IMutableGraph * toMutableGraph(const htd::IGraph & graph)
    {
        htd::IMutableGraph * ret = htd::getDefaultGraph(graph.vertexCount());

        for (auto & edge : graph.edges())
        {
            ret->addEdge(edge.first, edge.second);
        }
        
        return ret;
    }
    
    htd::IMutableGraph * toMutableGraph(const htd::IHypergraph & graph)
    {
        htd::IMutableGraph * ret = htd::getDefaultGraph(graph.vertexCount());

        for (const htd::hyperedge_t & edge : graph.hyperedges())
        {
            for (htd::vertex_t vertex1 : edge)
            {
                for (htd::vertex_t vertex2 : edge)
                {
                    if (vertex1 != vertex2)
                    {
                        ret->addEdge(vertex1, vertex2);
                    }
                }
            }
        }
        
        return ret;
    }
}

#endif /* HTD_HTD_CONVERTERS_CPP */
