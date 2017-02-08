/* 
 * File:   TreeDecomposition.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITION_HPP
#define HTD_HTD_TREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/LabeledTree.hpp>

#include <unordered_map>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableTreeDecomposition interface.
     */
    class TreeDecomposition : public htd::LabeledTree, public virtual htd::IMutableTreeDecomposition
    {
        public:
            /**
             *  Constructor for a tree decomposition.
             */
            HTD_API TreeDecomposition(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a tree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HTD_API TreeDecomposition(const TreeDecomposition & original);

            /**
             *  Copy constructor for a tree decomposition.
             *
             *  @param[in] original  The original tree.
             */
            HTD_API TreeDecomposition(const htd::ITree & original);

            /**
             *  Copy constructor for a tree decomposition.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API TreeDecomposition(const htd::ILabeledTree & original);

            /**
             *  Copy constructor for a tree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HTD_API TreeDecomposition(const htd::ITreeDecomposition & original);
            
            HTD_API virtual ~TreeDecomposition();

            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeSubtree(htd::vertex_t subtreeRoot) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(void) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            HTD_API std::size_t joinNodeCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> joinNodes(void) const HTD_OVERRIDE;

            HTD_API void copyJoinNodesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t joinNodeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isJoinNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t forgetNodeCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> forgetNodes(void) const HTD_OVERRIDE;

            HTD_API void copyForgetNodesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t forgetNodeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isForgetNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t introduceNodeCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> introduceNodes(void) const HTD_OVERRIDE;

            HTD_API void copyIntroduceNodesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t introduceNodeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isIntroduceNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t exchangeNodeCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> exchangeNodes(void) const HTD_OVERRIDE;

            HTD_API void copyExchangeNodesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t exchangeNodeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isExchangeNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t bagSize(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::vector<htd::vertex_t> & mutableBagContent(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API const std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::FilteredHyperedgeCollection & mutableInducedHyperedges(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API const htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t forgottenVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API void copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API void copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::vertex_t forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API htd::vertex_t forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const HTD_OVERRIDE;

            HTD_API bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API std::size_t introducedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API void copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API void copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::vertex_t introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API htd::vertex_t introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const HTD_OVERRIDE;

            HTD_API bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API std::size_t rememberedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API void copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API void copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API htd::vertex_t rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API htd::vertex_t rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const HTD_OVERRIDE;

            HTD_API bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            HTD_API std::size_t minimumBagSize(void) const HTD_OVERRIDE;

            HTD_API std::size_t maximumBagSize(void) const HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API TreeDecomposition * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable tree decomposition.
             *
             *  @return A new TreeDecomposition object identical to the current mutable tree decomposition.
             */
            HTD_API TreeDecomposition * clone(void) const;

            HTD_API htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            HTD_API htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * cloneTreeDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphDecomposition * cloneGraphDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableTree * cloneMutableTree(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledTree * cloneMutableLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableTreeDecomposition * cloneMutableTreeDecomposition(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable tree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HTD_API TreeDecomposition & operator=(const TreeDecomposition & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API TreeDecomposition & operator=(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API TreeDecomposition & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HTD_API TreeDecomposition & operator=(const htd::ITreeDecomposition & original) HTD_OVERRIDE;
#else
            HTD_API TreeDecomposition & operator=(const htd::ITree & original);

            HTD_API TreeDecomposition & operator=(const htd::ILabeledTree & original);

            HTD_API TreeDecomposition & operator=(const htd::ITreeDecomposition & original);

            HTD_API void assign(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ITreeDecomposition & original) HTD_OVERRIDE;
#endif

        protected:
            /**
             *  Compute the set union of all child bags of a given vertex.
             *
             *  @param[in] vertex   The vertex for which the set union of its children shall be computed.
             *  @param[out] target  The target vector to which the resulting set union shall be appended.
             */
            void getChildBagSetUnion(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const;

        private:
            std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> bagContent_;

            std::unordered_map<htd::vertex_t, htd::FilteredHyperedgeCollection> inducedEdges_;
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_TREEDECOMPOSITION_HPP */
