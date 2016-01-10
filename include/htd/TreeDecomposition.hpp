/* 
 * File:   TreeDecomposition.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITION_HPP
#define	HTD_HTD_TREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/LabeledTree.hpp>

namespace htd
{
    class TreeDecomposition : public htd::LabeledTree, public virtual htd::IMutableTreeDecomposition
    {
        public:
            TreeDecomposition(void);

            TreeDecomposition(const TreeDecomposition & original);

            TreeDecomposition(const htd::ITree & original);

            TreeDecomposition(const htd::ILabeledTree & original);

            TreeDecomposition(const htd::ITreeDecomposition & original);
            
            ~TreeDecomposition();

            std::size_t joinNodeCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> joinNodes(void) const HTD_OVERRIDE;

            htd::vertex_t joinNode(htd::index_t index) const HTD_OVERRIDE;

            bool isJoinNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgetNodeCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> forgetNodes(void) const HTD_OVERRIDE;

            htd::vertex_t forgetNode(htd::index_t index) const HTD_OVERRIDE;

            bool isForgetNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introduceNodeCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> introduceNodes(void) const HTD_OVERRIDE;

            htd::vertex_t introduceNode(htd::index_t index) const HTD_OVERRIDE;

            bool isIntroduceNode(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t bagSize(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> bagContent(htd::vertex_t vertex) const HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content) HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content) HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const HTD_OVERRIDE;

            bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const HTD_OVERRIDE;

            bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const HTD_OVERRIDE;

            bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t minimumBagSize(void) const HTD_OVERRIDE;

            std::size_t maximumBagSize(void) const HTD_OVERRIDE;

            TreeDecomposition * clone(void) const HTD_OVERRIDE;

            TreeDecomposition & operator=(const TreeDecomposition & original);

            TreeDecomposition & operator=(const htd::ITree & original) HTD_OVERRIDE;

            TreeDecomposition & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;

            TreeDecomposition & operator=(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

        protected:

            void getChildrenVertexLabelSetUnion(htd::vertex_t vertex, htd::vertex_container & output) const;
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITION_HPP */
