/* 
 * File:   IMutableTree.hpp
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

#ifndef HTD_HTD_IMUTABLETREE_HPP
#define HTD_HTD_IMUTABLETREE_HPP

#include <htd/Globals.hpp>
#include <htd/ITree.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable trees.
     */
    class IMutableTree : public virtual htd::ITree
    {
        public:
            /**
             *  Destructor for an IMutableTree object.
             */
            virtual ~IMutableTree() = 0;

            /**
             *  Getter for the next vertex identifier.
             *
             *  @return The ID the next vertex added to the graph will get.
             */
            virtual htd::vertex_t nextVertex(void) const = 0;

            /**
             *  Getter for the next edge identifier.
             *
             *  @return The ID the next edge added to the graph will get.
             */
            virtual htd::id_t nextEdgeId(void) const = 0;

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

            /**
             *  Change the root of the tree to the given vertex.
             *
             *  @param[in] vertex   The vertex which shall be the new root.
             */
            virtual void makeRoot(htd::vertex_t vertex) = 0;

            /**
             *  Add a new child to the given vertex.
             *
             *  @param[in] vertex   The vertex which shall get a new child.
             *
             *  @return The ID of the new child.
             */
            virtual htd::vertex_t addChild(htd::vertex_t vertex) = 0;

            /**
             *  Remove the child of a vertex from the tree.
             *
             *  @param[in] vertex   The ID of the vertex which's child shall be removed.
             *  @param[in] child    The ID of the vertex which shall be removed.
             *
             *  @note This operation retains the tree structure by connecting the neighbors of the removed vertex in a valid way.
             */
            virtual void removeChild(htd::vertex_t vertex, htd::vertex_t child) = 0;

            /**
             *  Add a new parent to the given vertex.
             *
             *  @param[in] vertex   The vertex which shall get a new parent.
             *
             *  @return The ID of the new parent.
             *
             *  @note If the given vertex already has a parent, the old parent will be attached to the new vertex in order to keep the tree structure valid.
             */
            virtual htd::vertex_t addParent(htd::vertex_t vertex) = 0;

            /**
             *  Attach the given vertex (together with its subtree) to a new parent.
             *
             *  @param[in] vertex       The vertex which shall get a new parent.
             *  @param[in] newParent    The desired parent.
             */
            virtual void setParent(htd::vertex_t vertex, htd::vertex_t newParent) = 0;

            /**
             *  Swap the positions of a vertex and its parent.
             *
             *  @param[in] vertex   The vertex which's position shall be swapped with its parent.
             */
            virtual void swapWithParent(htd::vertex_t vertex) = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current mutable tree.
             *
             *  @return A new IMutableTree object identical to the current mutable tree.
             */
            virtual IMutableTree * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current mutable tree.
             *
             *  @return A new IMutableTree object identical to the current mutable tree.
             */
            virtual IMutableTree * cloneMutableTree(void) const = 0;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a mutable tree.
             *
             *  @param[in] original  The original tree.
             */
            virtual IMutableTree & operator=(const htd::ITree & original) = 0;
#else
            /**
             *  Copy assignment operator for a mutable tree.
             *
             *  @param[in] original  The original tree.
             */
            virtual void assign(const htd::ITree & original) = 0;
#endif
    };

    inline htd::IMutableTree::~IMutableTree() { }
}

#endif /* HTD_HTD_IMUTABLETREE_HPP */
