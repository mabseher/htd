/* 
 * File:   IMutableTree.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_IMUTABLETREE_HPP
#define	HTD_HTD_IMUTABLETREE_HPP

#include <htd/Globals.hpp>
#include <htd/ITree.hpp>

namespace htd
{
    class IMutableTree : public virtual htd::ITree
    {
        public:
            /**
             *  Destructor for an IMutableTree object.
             */
            virtual ~IMutableTree() = 0;

            /**
             *  Remove a vertex from the tree.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            virtual void removeVertex(htd::vertex_t vertex) = 0;

            /**
             *  Remove a subtree from the tree.
             *
             *  @param[in] subtreeRoot  The root of the subtree.
             */
            virtual void removeSubtree(htd::vertex_t subtreeRoot) = 0;

            /**
             *  Insert the root of the tree if it does not already exist.
             *
             *  @return The ID of the root of the tree.
             */
            virtual htd::vertex_t insertRoot(void) = 0;

            virtual void makeRoot(htd::vertex_t vertex) = 0;

            virtual htd::vertex_t addChild(htd::vertex_t vertex) = 0;
            
            virtual void removeChild(htd::vertex_t vertex, htd::vertex_t child) = 0;

            virtual htd::vertex_t addParent(htd::vertex_t vertex) = 0;

            virtual void setParent(htd::vertex_t vertex, htd::vertex_t newParent) = 0;

            /**
             *  Create a deep copy the current mutable tree.
             *
             *  @return A new IMutableTree object identical to the current mutable tree.
             */
            virtual IMutableTree * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable tree.
             *
             *  @param[in] original  The original tree.
             */
            virtual IMutableTree & operator=(const htd::ITree & original) = 0;
    };

    inline htd::IMutableTree::~IMutableTree() { }
}

#endif /* HTD_HTD_IMUTABLETREE_HPP */
