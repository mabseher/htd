/*
 * File:   LabeledGraph.hpp
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

#ifndef HTD_HTD_LABELEDGRAPH_HPP
#define HTD_HTD_LABELEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Graph.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/IMutableLabeledGraph.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledGraph interface.
     */
    class LabeledGraph : public htd::LabeledGraphType<htd::Graph>, public virtual htd::IMutableLabeledGraph
    {
        public:
            /**
             *  Constructor for a labeled graph.
             *
             *  @param[in] manager   The management instance to which the new labeled graph belongs.
             */
            HTD_API LabeledGraph(const htd::LibraryInstance * const manager);

            /**
             *  Constructor for a labeled graph.
             *
             *  @param[in] manager       The management instance to which the new labeled graph belongs.
             *  @param[in] initialSize  The initial size of the created graph.
             */
            HTD_API LabeledGraph(const htd::LibraryInstance * const manager, std::size_t initialSize);

            /**
             *  Copy constructor for a labeled graph.
             *
             *  @param[in] original  The original labeled graph.
             */
            HTD_API LabeledGraph(const LabeledGraph & original);

            /**
             *  Copy constructor for a labeled graph.
             *
             *  @param[in] original  The original graph.
             */
            HTD_API LabeledGraph(const htd::IGraph & original);

            /**
             *  Copy constructor for a labeled graph.
             *
             *  @param[in] original  The original labeled graph.
             */
            HTD_API LabeledGraph(const htd::ILabeledGraph & original);

            HTD_API virtual ~LabeledGraph();

            HTD_API void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeEdge(htd::id_t edgeId) HTD_OVERRIDE;

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
            HTD_API LabeledGraph * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable labeled graph.
             *
             *  @return A new LabeledGraph object identical to the current mutable labeled graph.
             */
            HTD_API LabeledGraph * clone(void) const;

            HTD_API htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE;

            HTD_API htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableGraph * cloneMutableGraph(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledGraph * cloneMutableLabeledGraph(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable labeled graph.
             *
             *  @param[in] original  The original labeled graph.
             */
            HTD_API LabeledGraph & operator=(const LabeledGraph & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledGraph & operator=(const htd::IGraph & original) HTD_OVERRIDE;

            HTD_API LabeledGraph & operator=(const htd::ILabeledGraph & original) HTD_OVERRIDE;
#else
            HTD_API LabeledGraph & operator=(const htd::IGraph & original);

            HTD_API LabeledGraph & operator=(const htd::ILabeledGraph & original);

            HTD_API void assign(const htd::IGraph & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledGraph & original) HTD_OVERRIDE;
#endif
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_LABELEDGRAPH_HPP */
