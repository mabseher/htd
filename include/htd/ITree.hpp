/* 
 * File:   ITree.hpp
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

#ifndef HTD_HTD_ITREE_HPP
#define	HTD_HTD_ITREE_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/Collection.hpp>

namespace htd
{
    class ITree : public virtual htd::IGraph
    {
        public:
            virtual ~ITree() = 0;
            
            virtual htd::vertex_t root(void) const = 0;

            virtual bool isRoot(htd::vertex_t vertex) const = 0;

            virtual std::size_t leafNodeCount(void) const = 0;

            virtual void getLeafNodes(htd::vertex_container & output) const = 0;

            virtual htd::vertex_t leafNode(htd::index_t index) const = 0;

            virtual bool isLeafNode(htd::vertex_t vertex) const = 0;

            virtual htd::vertex_t parent(htd::vertex_t vertex) const = 0;

            virtual bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const = 0;
            
            virtual std::size_t childCount(htd::vertex_t vertex) const = 0;
            
            virtual const htd::Collection<htd::vertex_t> children(htd::vertex_t vertex) const = 0;
            
            virtual htd::vertex_t child(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual bool isChild(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual ITree * clone(void) const = 0;
    };

    inline htd::ITree::~ITree() { }
}

#endif /* HTD_HTD_ITREE_HPP */
