/* 
 * File:   TreeDecomposition.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITION_HPP
#define	HTD_HTD_TREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelingCollection.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    class TreeDecomposition : public virtual htd::IMutableTreeDecomposition
    {
        public:
            TreeDecomposition(void);
            
            TreeDecomposition(const htd::ILabeledTree & original);
            
            TreeDecomposition(const htd::TreeDecomposition & original);
            
            ~TreeDecomposition();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            htd::vertex_t vertex(htd::vertex_t index) const HTD_OVERRIDE;
            
            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;
            
            void getNeighbors(htd::vertex_t vertex, vertex_container& output) const HTD_OVERRIDE;
            
            htd::vertex_t neighbor(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex1, htd::vertex_t neighbor) const HTD_OVERRIDE;

            htd::Collection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            void getIsolatedVertices(htd::vertex_container & output) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertex(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            void getEdges(htd::edge_container & output) const HTD_OVERRIDE;

            void getEdges(htd::edge_container & output, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::edge_t & edge(htd::index_t index) const HTD_OVERRIDE;

            const htd::edge_t & edge(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::Collection<htd::hyperedge_t> hyperedges(void) const HTD_OVERRIDE;

            void getHyperedges(htd::hyperedge_container & output, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::hyperedge_t & hyperedge(htd::index_t index) const HTD_OVERRIDE;

            const htd::hyperedge_t & hyperedge(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE;

            const htd::ILabel & label(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & label(const std::string & labelName, const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            void setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label) HTD_OVERRIDE;

            void removeLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            void removeLabel(const std::string & labelName, const htd::hyperedge_t & edge) HTD_OVERRIDE;

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            void swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            htd::vertex_t root(void) const HTD_OVERRIDE;

            bool isRoot(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t leafNodeCount(void) const HTD_OVERRIDE;

            void getLeafNodes(htd::vertex_container & output) const HTD_OVERRIDE;

            htd::vertex_t leafNode(htd::index_t index) const HTD_OVERRIDE;

            bool isLeafNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t parent(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const HTD_OVERRIDE;

            std::size_t childCount(htd::vertex_t vertex) const HTD_OVERRIDE;
            
            void getChildren(htd::vertex_t vertex, htd::vertex_container & output) const HTD_OVERRIDE;
            
            htd::vertex_t child(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isChild(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeSubtree(htd::vertex_t subtreeRoot) HTD_OVERRIDE;

            htd::vertex_t insertRoot(void) HTD_OVERRIDE;
            
            void removeRoot(void) HTD_OVERRIDE;
            
            htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::vertex_t addIntermediateParent(htd::vertex_t vertex) HTD_OVERRIDE;
            
            void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            std::size_t joinNodeCount(void) const HTD_OVERRIDE;

            void getJoinNodes(htd::vertex_container & output) const HTD_OVERRIDE;

            htd::vertex_t joinNode(htd::index_t index) const HTD_OVERRIDE;

            bool isJoinNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgetNodeCount(void) const HTD_OVERRIDE;

            void getForgetNodes(htd::vertex_container & output) const HTD_OVERRIDE;

            htd::vertex_t forgetNode(htd::index_t index) const HTD_OVERRIDE;

            bool isForgetNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introduceNodeCount(void) const HTD_OVERRIDE;

            void getIntroduceNodes(htd::vertex_container & output) const HTD_OVERRIDE;

            htd::vertex_t introduceNode(htd::index_t index) const HTD_OVERRIDE;

            bool isIntroduceNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::Collection<htd::vertex_t> bagContent(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void getForgottenVertices(htd::vertex_t vertex, htd::vertex_container & output) const HTD_OVERRIDE;

            void getForgottenVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void getIntroducedVertices(htd::vertex_t vertex, htd::vertex_container & output) const HTD_OVERRIDE;

            void getIntroducedVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void getRememberedVertices(htd::vertex_t vertex, htd::vertex_container & output) const HTD_OVERRIDE;

            void getRememberedVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t minimumBagSize(void) const HTD_OVERRIDE;

            std::size_t maximumBagSize(void) const HTD_OVERRIDE;

            TreeDecomposition & operator=(const TreeDecomposition & other);

            TreeDecomposition * clone(void) const HTD_OVERRIDE;

        protected:

            struct TreeNode
            {
                htd::id_t id;

                htd::vertex_t parent;

                htd::vertex_container children;

                TreeNode(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), children()
                {

                }
            };

            std::size_t size_;

            htd::vertex_t root_;

            htd::vertex_t next_vertex_;

            htd::vertex_container vertices_;

            std::vector<TreeNode *> nodes_;

            std::unordered_set<htd::vertex_t> deletions_;

            htd::ILabelingCollection * labelings_;

            std::size_t size(htd::TreeDecomposition::TreeNode * start) const;

            void getChildrenVertexLabelSetUnion(htd::vertex_t vertex, htd::vertex_container & output) const;

            void deleteSubtree(htd::TreeDecomposition::TreeNode * start);

            void deleteNode(htd::TreeDecomposition::TreeNode * node);

            void copy(const htd::ILabeledTree& original, htd::vertex_t vertex);
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITION_HPP */
