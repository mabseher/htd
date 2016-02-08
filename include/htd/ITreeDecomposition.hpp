/* 
 * File:   ITreeDecomposition.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITION_HPP
#define	HTD_HTD_ITREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/IGraphDecomposition.hpp>

#include <vector>

namespace htd
{
    class ITreeDecomposition : public virtual htd::ILabeledTree, public virtual htd::IGraphDecomposition
    {
        public:
            /**
             *  Constant for the identifier of the bag label.
             */
            static constexpr const char * BAG_LABEL_IDENTIFIER = "Bag";

            virtual ~ITreeDecomposition() = 0;

            virtual std::size_t joinNodeCount(void) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> joinNodes(void) const = 0;

            virtual htd::vertex_t joinNodeAtPosition(htd::index_t index) const = 0;

            virtual bool isJoinNode(htd::vertex_t vertex) const = 0;

            virtual std::size_t forgetNodeCount(void) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> forgetNodes(void) const = 0;

            virtual htd::vertex_t forgetNodeAtPosition(htd::index_t index) const = 0;

            virtual bool isForgetNode(htd::vertex_t vertex) const = 0;

            virtual std::size_t introduceNodeCount(void) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> introduceNodes(void) const = 0;

            virtual htd::vertex_t introduceNodeAtPosition(htd::index_t index) const = 0;

            virtual bool isIntroduceNode(htd::vertex_t vertex) const = 0;

            virtual std::size_t forgottenVertexCount(htd::vertex_t vertex) const = 0;

            virtual std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual void copyForgottenVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const = 0;

            virtual void copyForgottenVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual htd::vertex_t forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            virtual bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const = 0;

            virtual bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const = 0;

            virtual std::size_t introducedVertexCount(htd::vertex_t vertex) const = 0;

            virtual std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual void copyIntroducedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const = 0;

            virtual void copyIntroducedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual htd::vertex_t introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            virtual bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const = 0;

            virtual bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const = 0;

            virtual std::size_t rememberedVertexCount(htd::vertex_t vertex) const = 0;

            virtual std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex) const = 0;

            virtual htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual void copyRememberedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const = 0;

            virtual void copyRememberedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const = 0;

            virtual htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index) const = 0;

            virtual htd::vertex_t rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            virtual bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const = 0;

            virtual bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const = 0;

            virtual ITreeDecomposition * clone(void) const = 0;
    };

    inline htd::ITreeDecomposition::~ITreeDecomposition() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITION_HPP */
