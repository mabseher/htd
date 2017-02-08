/* 
 * File:   ITree.hpp
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

#ifndef HTD_HTD_ITREE_HPP
#define HTD_HTD_ITREE_HPP

#include <htd/Globals.hpp>
#include <htd/IGraph.hpp>
#include <htd/ConstCollection.hpp>

namespace htd
{
    /**
     * Interface for classes which represent trees.
     */
    class ITree : public virtual htd::IGraph
    {
        public:
            using htd::IGraph::vertexCount;

            virtual ~ITree() = 0;

            /**
             *  Getter for the number of vertices in the subtree.
             *
             *  @param[in] subtreeRoot  The root of the subtree.
             *
             *  @return The number of vertices in the subtree.
             */
            virtual std::size_t vertexCount(htd::vertex_t subtreeRoot) const = 0;

            /**
             *  Getter for the root of the tree.
             *
             *  @return The ID of the root vertex of the tree.
             */
            virtual htd::vertex_t root(void) const = 0;

            /**
             *  Check whether a vertex is the root node of the tree.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the the vertex is the root node of the tree, false otherwise.
             */
            virtual bool isRoot(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of leaf nodes of the tree.
             *
             *  @return The number of leaf nodes of the tree.
             */
            virtual std::size_t leafCount(void) const HTD_NOEXCEPT = 0;

            /**
             *  Access the collection of all leaf nodes of the tree.
             *
             *  @return The collection of all leaf nodes of the tree in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> leaves(void) const = 0;

            /**
             *  Get the collection of all leaf nodes of the tree and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the leaves shall be appended.
             */
            virtual void copyLeavesTo(std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the leaf node at the specific position.
             *
             *  @param[in] index    The position of the leaf node.
             *
             *  @return The leaf node at the specific position.
             */
            virtual htd::vertex_t leafAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is a leaf node of the tree.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the the vertex is a leaf node of the tree, false otherwise.
             */
            virtual bool isLeaf(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the parent of a vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The ID of the parent of the vertex.
             */
            virtual htd::vertex_t parent(htd::vertex_t vertex) const = 0;

            /**
             *  Check whether a vertex is the parent of another.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] parent   The potential parent.
             *
             *  @return True if the the potential parent is indeed the parent of the given vertex, false otherwise.
             */
            virtual bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const = 0;

            /**
             *  Getter for the number of children of a vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The number of children of the vertex.
             */
            virtual std::size_t childCount(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all children of a given vertex in the graph.
             *
             *  @param[in] vertex   The vertex for which the collection of children shall be returned.
             *
             *  @return The collection of all children of the given vertex in the graph in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> children(htd::vertex_t vertex) const = 0;

            /**
             *  Get the collection of all children of a given vertex in the graph and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex for which the collection of children shall be returned.
             *  @param[out] target  The target vector to which the children of the vertex shall be appended.
             */
            virtual void copyChildrenTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the child at the specific position.
             *
             *  @param[in] vertex   The vertex for which the child shall be returned.
             *  @param[in] index    The position of the child.
             *
             *  @return The child at the specific position.
             */
            virtual htd::vertex_t childAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is a child of another.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The potential child.
             *
             *  @return True if the the potential child is indeed a child of the given vertex, false otherwise.
             */
            virtual bool isChild(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Getter for the height of the tree.
             *
             *  @return The height of the tree.
             */
            virtual std::size_t height(void) const = 0;

            /**
             *  Getter for the height of a given vertex withing the tree.
             *
             *  @param[in] vertex   The vertex which's height shall be returned.
             *
             *  @return The height of the given vertex withing the tree.
             */
            virtual std::size_t height(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the depth of a given vertex withing the tree.
             *
             *  @param[in] vertex   The vertex which's depth shall be returned.
             *
             *  @return The depth of the given vertex withing the tree.
             */
            virtual std::size_t depth(htd::vertex_t vertex) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current tree.
             *
             *  @return A new ITree object identical to the current tree.
             */
            virtual ITree * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current tree.
             *
             *  @return A new ITree object identical to the current tree.
             */
            virtual ITree * cloneTree(void) const = 0;
#endif
    };

    inline htd::ITree::~ITree() { }
}

#endif /* HTD_HTD_ITREE_HPP */
