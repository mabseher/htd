/* 
 * File:   Tree.hpp
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

#ifndef HTD_HTD_TREE_HPP
#define	HTD_HTD_TREE_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableTree.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace htd
{
    class Tree : public virtual htd::IMutableTree
    {
        public:
            Tree(void);

            Tree(const Tree & original);

            Tree(const htd::ITree & original);
            
            ~Tree();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t vertexCount(htd::vertex_t subtreeRoot) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isEdge(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const HTD_OVERRIDE;

            htd::vertex_t root(void) const HTD_OVERRIDE;

            bool isRoot(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t leafCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> leaves(void) const HTD_OVERRIDE;

            htd::vertex_t leafAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isLeaf(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t parent(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const HTD_OVERRIDE;

            std::size_t childCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> children(htd::vertex_t vertex) const HTD_OVERRIDE;
            
            htd::vertex_t childAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isChild(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeSubtree(htd::vertex_t subtreeRoot) HTD_OVERRIDE;

            htd::vertex_t insertRoot(void) HTD_OVERRIDE;

            void makeRoot(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeRoot(void) HTD_OVERRIDE;
            
            htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            void setParent(htd::vertex_t vertex, htd::vertex_t newParent) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            Tree * clone(void) const HTD_OVERRIDE;

            Tree & operator=(const Tree & original);

            Tree & operator=(const htd::ITree & original) HTD_OVERRIDE;

        protected:

            struct Node
            {
                htd::id_t id;

                htd::vertex_t parent;

                htd::vertex_container children;

                Node(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), children()
                {

                }

                Node(const Node & original) : id(original.id), parent(original.parent), children(original.children)
                {

                }

                Node(Node && original) : id(original.id), parent(original.parent), children(std::move(original.children))
                {

                }
            };

            /**
             *  The size of the tree.
             */
            std::size_t size_;

            /**
             *  The root vertex of the tree.
             */
            htd::vertex_t root_;

            /**
             *  The ID the next edge added to the tree will get.
             */
            htd::id_t next_edge_;

            /**
             *  The ID the next vertex added to the tree will get.
             */
            htd::vertex_t next_vertex_;

            /**
             *  The collection of all vertices of the tree in ascending order.
             */
            htd::vertex_container vertices_;

            /**
             *  The map of pointers to all tree nodes. It maps vertex IDs to the corresponding node information.
             */
            std::unordered_map<htd::id_t, std::unique_ptr<Node>> nodes_;

            /**
             *  The collection of all hyperedges which exist in the tree.
             */
            std::shared_ptr<htd::hyperedge_container> edges_;

            /**
             *  The ID of the signal handler associated to the tree.
             */
            htd::id_t signalHandlerId_;

            /**
             *  Delete a node of the tree and perform an update of the internal state.
             *
             *  @param[in] node The node of the tree which shall be removed.
             */
            void deleteNode(const std::unique_ptr<Node> & node);

            /**
             *  Handle an incoming signal.
             *
             *  @param[in] signal   The signal which was received.
             */
            void handleSignal(int signal);
    };
}

#endif /* HTD_HTD_TREE_HPP */
