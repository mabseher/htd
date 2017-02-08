/* 
 * File:   PathDecomposition.hpp
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

#ifndef HTD_HTD_PATHDECOMPOSITION_HPP
#define HTD_HTD_PATHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/LabeledPath.hpp>

#include <unordered_map>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutablePathDecomposition interface.
     */
    class PathDecomposition : public htd::LabeledPath, public virtual htd::IMutablePathDecomposition
    {
        public:
            /**
             *  Constructor for a path decomposition.
             */
            HTD_API PathDecomposition(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            HTD_API PathDecomposition(const PathDecomposition & original);

            /**
             *  Copy constructor for a path decomposition.
             *
             *  @param[in] original  The original path.
             */
            HTD_API PathDecomposition(const htd::IPath & original);

            /**
             *  Copy constructor for a path decomposition.
             *
             *  @param[in] original  The original labeled path.
             */
            HTD_API PathDecomposition(const htd::ILabeledPath & original);

            /**
             *  Copy constructor for a path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            HTD_API PathDecomposition(const htd::IPathDecomposition & original);
            
            HTD_API virtual ~PathDecomposition();

            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeSubpath(htd::vertex_t subpathRoot) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(void) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) HTD_OVERRIDE;

            HTD_API htd::vertex_t addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) HTD_OVERRIDE;

            HTD_API void removeChild(htd::vertex_t vertex) HTD_OVERRIDE;

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
            HTD_API PathDecomposition * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable path decomposition.
             *
             *  @return A new PathDecomposition object identical to the current mutable path decomposition.
             */
            HTD_API PathDecomposition * clone(void) const;

            HTD_API htd::IPath * clonePath(void) const HTD_OVERRIDE;

            HTD_API htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            HTD_API htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledPath * cloneLabeledPath(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IPathDecomposition * clonePathDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::ITreeDecomposition * cloneTreeDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphDecomposition * cloneGraphDecomposition(void) const HTD_OVERRIDE;

            HTD_API htd::IMutablePath * cloneMutablePath(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledPath * cloneMutableLabeledPath(void) const HTD_OVERRIDE;

            HTD_API htd::IMutablePathDecomposition * cloneMutablePathDecomposition(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable path decomposition.
             *
             *  @param[in] original  The original path decomposition.
             */
            HTD_API PathDecomposition & operator=(const PathDecomposition & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API PathDecomposition & operator=(const htd::IPath & original) HTD_OVERRIDE;

            HTD_API PathDecomposition & operator=(const htd::ILabeledPath & original) HTD_OVERRIDE;

            HTD_API PathDecomposition & operator=(const htd::IPathDecomposition & original) HTD_OVERRIDE;
#else
            HTD_API PathDecomposition & operator=(const htd::IPath & original);

            HTD_API PathDecomposition & operator=(const htd::ILabeledPath & original);

            HTD_API PathDecomposition & operator=(const htd::IPathDecomposition & original);

            HTD_API void assign(const htd::IPath & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledPath & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::IPathDecomposition & original) HTD_OVERRIDE;
#endif

        private:
            std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> bagContent_;

            std::unordered_map<htd::vertex_t, htd::FilteredHyperedgeCollection> inducedEdges_;
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_PATHDECOMPOSITION_HPP */
