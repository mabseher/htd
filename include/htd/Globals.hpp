/* 
 * File:   Globals.hpp
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

#ifndef HTD_HTD_GLOBALS_HPP
#define HTD_HTD_GLOBALS_HPP

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <htd/CompilerDetection.hpp>

namespace htd
{
    /**
     *  Datatype for IDs.
     */
    typedef std::size_t id_t;
    
    /**
     *  Datatype for indices.
     */
    typedef std::size_t index_t;
    
    /**
     *  Datatype for vertices.
     */
    typedef std::size_t vertex_t;
    
    /**
     *  Datatype for edges.
     */
    typedef std::pair<vertex_t, vertex_t> edge_t;
    
    /**
     *  Datatype for hyperedges.
     */
    typedef std::vector<vertex_t> hyperedge_t;
    
    /**
     *  Datatype for storing vertices.
     */
    typedef std::vector<vertex_t> vertex_container;
    
    /**
     *  Datatype for storing edges.
     */
    typedef std::vector<edge_t> edge_container;
    
    /**
     *  Datatype for storing hyperedges.
     */
    typedef std::vector<hyperedge_t> hyperedge_container;

    /**
     *  Constant for first identifier.
     */
    const htd::id_t first_id = (htd::id_t)1;

    /**
     *  Constant for first index.
     */
    const htd::index_t first_index = (htd::index_t)1;

    /**
     *  Constant for first index.
     */
    const htd::vertex_t first_vertex = (htd::vertex_t)1;

    /**
     *  Constant for unknown identifiers.
     */
    const htd::id_t unknown_id = (htd::id_t)0;
    
    /**
     *  Constant for unknown indices.
     */
    const htd::index_t unknown_index = (htd::index_t)0;
    
    /**
     *  Constant for unknown vertices.
     */
    const htd::vertex_t unknown_vertex = (htd::vertex_t)0;

    /**
     *  Constant for the name of the bag label.
     */
    const std::string bag_label_name = "Bag";

    /**
     *  Constant for the name of the name label.
     */
    const std::string name_label_name = "Name";

    /**
     *  Constant for the name of the edge label.
     */
    const std::string edge_label_name = "Edges";

    /**
     *  Constant for the name of the induced subgraph label.
     */
    const std::string induced_subgraph_label_name = "Induced Subgraph";
}

#endif /* HTD_HTD_GLOBALS_HPP */
