/* 
 * File:   ITreeDecomposition.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITION_HPP
#define HTD_HTD_ITREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/IGraphDecomposition.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for classes which represent tree decompositions.
     */
    class ITreeDecomposition : public virtual htd::ILabeledTree, public virtual htd::IGraphDecomposition
    {
        public:
            virtual ~ITreeDecomposition() = 0;

            /**
             *  Getter for the number of join nodes of the decomposition.
             *
             *  @return The number of join nodes of the decomposition.
             */
            virtual std::size_t joinNodeCount(void) const = 0;

            /**
             *  Access the collection of all join nodes in the decomposition.
             *
             *  @return The collection of all join nodes in the decomposition sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> joinNodes(void) const = 0;

            /**
             *  Get the collection of all join nodes and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the join nodes shall be appended.
             */
            virtual void copyJoinNodesTo(std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the join node at the specific position.
             *
             *  @param[in] index     The position of the join node.
             *
             *  @return The ID of the join node at the specific position.
             */
            virtual htd::vertex_t joinNodeAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is a join node in the decomposition.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex is a join node in the decomposition, false otherwise.
             */
            virtual bool isJoinNode(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of forget nodes of the decomposition.
             *
             *  @return The number of forget nodes of the decomposition.
             */
            virtual std::size_t forgetNodeCount(void) const = 0;

            /**
             *  Access the collection of all forget nodes in the decomposition.
             *
             *  @return The collection of all forget nodes in the decomposition sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> forgetNodes(void) const = 0;

            /**
             *  Get the collection of all forget nodes and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the forget nodes shall be appended.
             */
            virtual void copyForgetNodesTo(std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the forget node at the specific position.
             *
             *  @param[in] index     The position of the forget node.
             *
             *  @return The ID of the forget node at the specific position.
             */
            virtual htd::vertex_t forgetNodeAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is a forget node in the decomposition.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex is a forget node in the decomposition, false otherwise.
             */
            virtual bool isForgetNode(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of introduce nodes of the decomposition.
             *
             *  @return The number of introduce nodes of the decomposition.
             */
            virtual std::size_t introduceNodeCount(void) const = 0;

            /**
             *  Access the collection of all introduce nodes in the decomposition.
             *
             *  @return The collection of all introduce nodes in the decomposition sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> introduceNodes(void) const = 0;

            /**
             *  Get the collection of all introduce nodes and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the introduce nodes shall be appended.
             */
            virtual void copyIntroduceNodesTo(std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the introduce node at the specific position.
             *
             *  @param[in] index     The position of the introduce node.
             *
             *  @return The ID of the introduce node at the specific position.
             */
            virtual htd::vertex_t introduceNodeAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is an introduce node in the decomposition.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex is an introduce node in the decomposition, false otherwise.
             */
            virtual bool isIntroduceNode(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of exchange nodes of the decomposition.
             *
             *  @return The number of exchange nodes of the decomposition.
             */
            virtual std::size_t exchangeNodeCount(void) const = 0;

            /**
             *  Access the collection of all exchange nodes in the decomposition.
             *
             *  @return The collection of all exchange nodes in the decomposition sorted by ID in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> exchangeNodes(void) const = 0;

            /**
             *  Get the collection of all exchange nodes and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[out] target  The target vector to which the exchange nodes shall be appended.
             */
            virtual void copyExchangeNodesTo(std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Access the exchange node at the specific position.
             *
             *  @param[in] index     The position of the exchange node.
             *
             *  @return The ID of the exchange node at the specific position.
             */
            virtual htd::vertex_t exchangeNodeAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a vertex is an exchange node in the decomposition.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex is an exchange node in the decomposition, false otherwise.
             */
            virtual bool isExchangeNode(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of vertices which are present in at least one child bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The number of vertices which are present in at least one child bag but not in the bag of the given vertex.
             */
            virtual std::size_t forgottenVertexCount(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of vertices which are present in the given child's bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The number of vertices which are present in the given child's bag but not in the bag of the given vertex.
             */
            virtual std::size_t forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Access the collection of all vertices which are present in at least one child bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The collection of all vertices which are present in at least one child bag but not in the bag of the given vertex. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all vertices which are present in the given child's bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The collection of all vertices which are present in the given child's bag but not in the bag of the given vertex. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Compute the collection of all vertices which are present in at least one child bag but not in the bag of the given vertex and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the forgotten vertices shall be appended.
             */
            virtual void copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Compute the collection of all vertices which are present in the given child's bag but not in the bag of the given vertex and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the forgotten vertices shall be appended.
             *  @param[in] child    The child.
             */
            virtual void copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const = 0;

            /**
             *  Access the forgotten vertex at the specific position. A forgotten vertex is a vertex which is present in at least one child bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex for which the forgotten vertex shall be returned.
             *  @param[in] index    The position of the forgotten vertex.
             *
             *  @return The forgotten vertex at the specific position.
             */
            virtual htd::vertex_t forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Access the forgotten vertex at the specific position. A forgotten vertex is a vertex which is present in the given child's bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex   The vertex for which the forgotten vertex shall be returned.
             *  @param[in] index    The position of the forgotten vertex.
             *  @param[in] child    The child.
             *
             *  @return The forgotten vertex at the specific position.
             */
            virtual htd::vertex_t forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            /**
             *  Check whether a vertex is present in at least one child bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] forgottenVertex  The potential forgotten vertex.
             *
             *  @return True if the given vertex is present in at least one child bag but not in the bag of the given vertex, false otherwise.
             */
            virtual bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const = 0;

            /**
             *  Check whether a vertex is present in the given child's bag but not in the bag of the given vertex.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] forgottenVertex  The potential forgotten vertex.
             *  @param[in] child            The child.
             *
             *  @return True if the given vertex is present in the given child's bag but not in the bag of the given vertex, false otherwise.
             */
            virtual bool isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const = 0;

            /**
             *  Getter for the number of vertices which are present in the bag of the given vertex but not in any child bag.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The number of vertices which are present in the bag of the given vertex but not in any child bag.
             */
            virtual std::size_t introducedVertexCount(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of vertices which are present in the bag of the given vertex but not in the given child's bag.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The number of vertices which are present in the bag of the given vertex but not in the given child's bag.
             */
            virtual std::size_t introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Access the collection of all vertices which are present in the bag of the given vertex but not in any child bag.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The collection of all vertices which are present in the bag of the given vertex but not in any child bag. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all vertices which are present in the bag of the given vertex but not in the given child's bag.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The collection of all vertices which are present in the bag of the given vertex but not in the given child's bag. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Compute the collection of all vertices which are present in the bag of the given vertex but not in any child bag and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the introduced vertices shall be appended.
             */
            virtual void copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Compute the collection of all vertices which are present in the bag of the given vertex but not in the given child's bag and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the introduced vertices shall be appended.
             *  @param[in] child    The child.
             */
            virtual void copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const = 0;

            /**
             *  Access the introduced vertex at the specific position. An introduced vertex is a vertex which is present in the bag of the given vertex but not in any child bag.
             *
             *  @param[in] vertex   The vertex for which the introduced vertex shall be returned.
             *  @param[in] index    The position of the introduced vertex.
             *
             *  @return The introduced vertex at the specific position.
             */
            virtual htd::vertex_t introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Access the introduced vertex at the specific position. An introduced vertex is a vertex which is present in the bag of the given vertex but not in the given child's bag.
             *
             *  @param[in] vertex   The vertex for which the introduced vertex shall be returned.
             *  @param[in] index    The position of the introduced vertex.
             *  @param[in] child    The child.
             *
             *  @return The introduced vertex at the specific position.
             */
            virtual htd::vertex_t introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            /**
             *  Check whether a vertex is present in the bag of the given vertex but not in any child bag.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] introducedVertex The potential introduced vertex.
             *
             *  @return True if the given vertex is present in the bag of the given vertex but not in any child bag, false otherwise.
             */
            virtual bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const = 0;

            /**
             *  Check whether a vertex is present in the bag of the given vertex but not in the given child's bag.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] introducedVertex The potential introduced vertex.
             *  @param[in] child            The child.
             *
             *  @return True if the given vertex is present in the bag of the given vertex but not in the given child's bag, false otherwise.
             */
            virtual bool isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const = 0;

            /**
             *  Getter for the number of vertices which are present in the bag of the given vertex and in at least one child bag.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The number of vertices which are present in the bag of the given vertex and in at least one child bag.
             */
            virtual std::size_t rememberedVertexCount(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the number of vertices which are present in the bag of the given vertex and in the given child's bag.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The number of vertices which are present in the bag of the given vertex and in the given child's bag.
             */
            virtual std::size_t rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Access the collection of all vertices which are present in the bag of the given vertex and in at least one child bag.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The collection of all vertices which are present in the bag of the given vertex and in at least one child bag. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex) const = 0;

            /**
             *  Access the collection of all vertices which are present in the bag of the given vertex and in the given child's bag.
             *
             *  @param[in] vertex   The vertex.
             *  @param[in] child    The child.
             *
             *  @return The collection of all vertices which are present in the bag of the given vertex and in the given child's bag. The result is sorted in ascending order.
             */
            virtual htd::ConstCollection<htd::vertex_t> rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const = 0;

            /**
             *  Compute the collection of all vertices which are present in the bag of the given vertex and in at least one child bag and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the remembered vertices shall be appended.
             */
            virtual void copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const = 0;

            /**
             *  Compute the collection of all vertices which are present in the bag of the given vertex and in the given child's bag and write it to the end of a given vector. The result is sorted in ascending order.
             *
             *  @param[in] vertex   The vertex.
             *  @param[out] target  The target vector to which the remembered vertices shall be appended.
             *  @param[in] child    The child.
             */
            virtual void copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const = 0;

            /**
             *  Access the remembered vertex at the specific position. A remembered vertex is a vertex which is present in the bag of the given vertex and in at least one child bag.
             *
             *  @param[in] vertex   The vertex for which the remembered vertex shall be returned.
             *  @param[in] index    The position of the remembered vertex.
             *
             *  @return The remembered vertex at the specific position.
             */
            virtual htd::vertex_t rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const = 0;

            /**
             *  Access the remembered vertex at the specific position. A remembered vertex is a vertex which is present in the bag of the given vertex and in the given child's bag.
             *
             *  @param[in] vertex   The vertex for which the remembered vertex shall be returned.
             *  @param[in] index    The position of the remembered vertex.
             *  @param[in] child    The child.
             *
             *  @return The remembered vertex at the specific position.
             */
            virtual htd::vertex_t rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const = 0;

            /**
             *  Check whether a vertex is present in the bag of the given vertex and in at least one child bag.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] rememberedVertex The potential remembered vertex.
             *
             *  @return True if the given vertex is present in the bag of the given vertex and in at least one child bag, false otherwise.
             */
            virtual bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const = 0;

            /**
             *  Check whether a vertex is present in the bag of the given vertex and in the given child's bag.
             *
             *  @param[in] vertex           The vertex which's bag shall be investigated.
             *  @param[in] rememberedVertex The potential remembered vertex.
             *  @param[in] child            The child.
             *
             *  @return True if the given vertex is present in the bag of the given vertex and in the given child's bag, false otherwise.
             */
            virtual bool isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current tree decomposition.
             *
             *  @return A new ITreeDecomposition object identical to the current tree decomposition.
             */
            virtual ITreeDecomposition * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current tree decomposition.
             *
             *  @return A new ITreeDecomposition object identical to the current tree decomposition.
             */
            virtual ITreeDecomposition * cloneTreeDecomposition(void) const = 0;
#endif
    };

    inline htd::ITreeDecomposition::~ITreeDecomposition() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITION_HPP */
