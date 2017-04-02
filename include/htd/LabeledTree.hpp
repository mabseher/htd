/*
 * File:   LabeledTree.hpp
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

#ifndef HTD_HTD_LABELEDTREE_HPP
#define HTD_HTD_LABELEDTREE_HPP

#include <htd/Globals.hpp>
#include <htd/Tree.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/IMutableLabeledTree.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledTree interface.
     */
    class LabeledTree : public htd::LabeledGraphType<htd::Tree>, public virtual htd::IMutableLabeledTree
    {
        public:
            /**
             *  Constructor for a labeled tree.
             *
             *  @param[in] manager   The management instance to which the new labeled tree belongs.
             */
            HTD_API LabeledTree(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a labeled tree.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API LabeledTree(const LabeledTree & original);

            /**
             *  Copy constructor for a labeled tree.
             *
             *  @param[in] original  The original tree.
             */
            HTD_API LabeledTree(const htd::ITree & original);

            /**
             *  Copy constructor for a labeled tree.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API LabeledTree(const htd::ILabeledTree & original);
            
            HTD_API virtual ~LabeledTree();

            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            HTD_API std::size_t labelCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<std::string> labelNames(void) const HTD_OVERRIDE;

            HTD_API const std::string & labelNameAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            HTD_API void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) HTD_OVERRIDE;

            HTD_API void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

            HTD_API void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            HTD_API void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            HTD_API void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            HTD_API void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            HTD_API htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledTree * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable labeled tree.
             *
             *  @return A new LabeledTree object identical to the current mutable labeled tree.
             */
            HTD_API LabeledTree * clone(void) const;

            HTD_API htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            HTD_API htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableTree * cloneMutableTree(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledTree * cloneMutableLabeledTree(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable labeled tree.
             *
             *  @param[in] original  The original labeled tree.
             */
            HTD_API LabeledTree & operator=(const LabeledTree & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledTree & operator=(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API LabeledTree & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;
#else
            HTD_API LabeledTree & operator=(const htd::ITree & original);

            HTD_API LabeledTree & operator=(const htd::ILabeledTree & original);

            HTD_API void assign(const htd::ITree & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledTree & original) HTD_OVERRIDE;
#endif
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_LABELEDTREE_HPP */
