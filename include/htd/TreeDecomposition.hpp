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

            TreeDecomposition(const TreeDecomposition & original);

            TreeDecomposition(const htd::ITreeDecomposition & original);
            
            ~TreeDecomposition();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isEdge(const htd::Collection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            const htd::Collection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            const htd::Collection<htd::id_t> associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::vertex_t vertexAtPosition(htd::vertex_t index) const HTD_OVERRIDE;

            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t neighbor(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertex(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::edge_t> edges(void) const HTD_OVERRIDE;

            const htd::Collection<htd::edge_t> edges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::edge_t & edgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::edge_t & edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            const htd::Collection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            const htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE;

            bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) HTD_OVERRIDE;

            void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

            void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            htd::vertex_t root(void) const HTD_OVERRIDE;

            bool isRoot(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t leafNodeCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> leafNodes(void) const HTD_OVERRIDE;

            htd::vertex_t leafNode(htd::index_t index) const HTD_OVERRIDE;

            bool isLeafNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t parent(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const HTD_OVERRIDE;

            std::size_t childCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> children(htd::vertex_t vertex) const HTD_OVERRIDE;
            
            htd::vertex_t child(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isChild(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeSubtree(htd::vertex_t subtreeRoot) HTD_OVERRIDE;

            htd::vertex_t insertRoot(void) HTD_OVERRIDE;
            
            void removeRoot(void) HTD_OVERRIDE;
            
            htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            void setParent(htd::vertex_t vertex, htd::vertex_t newParent) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            std::size_t joinNodeCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> joinNodes(void) const HTD_OVERRIDE;

            htd::vertex_t joinNode(htd::index_t index) const HTD_OVERRIDE;

            bool isJoinNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgetNodeCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> forgetNodes(void) const HTD_OVERRIDE;

            htd::vertex_t forgetNode(htd::index_t index) const HTD_OVERRIDE;

            bool isForgetNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introduceNodeCount(void) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> introduceNodes(void) const HTD_OVERRIDE;

            htd::vertex_t introduceNode(htd::index_t index) const HTD_OVERRIDE;

            bool isIntroduceNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t bagSize(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> bagContent(htd::vertex_t vertex) const HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const htd::vertex_container & content) HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const htd::Collection<htd::vertex_t> & content) HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> introducedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Collection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t minimumBagSize(void) const HTD_OVERRIDE;

            std::size_t maximumBagSize(void) const HTD_OVERRIDE;

            TreeDecomposition & operator=(const TreeDecomposition & other);

            TreeDecomposition & operator=(const htd::ITreeDecomposition & other);

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
