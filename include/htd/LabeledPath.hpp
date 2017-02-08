/*
 * File:   LabeledPath.hpp
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

#ifndef HTD_HTD_LABELEDPATH_HPP
#define HTD_HTD_LABELEDPATH_HPP

#include <htd/Globals.hpp>
#include <htd/Path.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/IMutableLabeledPath.hpp>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledPath interface.
     */
    class LabeledPath : public htd::LabeledGraphType<htd::Path>, public virtual htd::IMutableLabeledPath
    {
        public:
            /**
             *  Constructor for a labeled path.
             *
             *  @param[in] manager   The management instance to which the new labeled path belongs.
             */
            HTD_API LabeledPath(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            HTD_API LabeledPath(const LabeledPath & original);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original path.
             */
            HTD_API LabeledPath(const htd::IPath & original);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            HTD_API LabeledPath(const htd::ILabeledPath & original);
            
            HTD_API virtual ~LabeledPath();

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
            HTD_API LabeledPath * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable labeled path.
             *
             *  @return A new LabeledPath object identical to the current mutable labeled path.
             */
            HTD_API LabeledPath * clone(void) const;

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

            HTD_API htd::IMutablePath * cloneMutablePath(void) const HTD_OVERRIDE;

            HTD_API htd::IMutableLabeledPath * cloneMutableLabeledPath(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            HTD_API LabeledPath & operator=(const LabeledPath & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API LabeledPath & operator=(const htd::IPath & original) HTD_OVERRIDE;

            HTD_API LabeledPath & operator=(const htd::ILabeledPath & original) HTD_OVERRIDE;
#else
            HTD_API LabeledPath & operator=(const htd::IPath & original);

            HTD_API LabeledPath & operator=(const htd::ILabeledPath & original);

            HTD_API void assign(const htd::IPath & original) HTD_OVERRIDE;

            HTD_API void assign(const htd::ILabeledPath & original) HTD_OVERRIDE;
#endif
    };
}

MSVC_PRAGMA_WARNING_POP

#endif /* HTD_HTD_LABELEDPATH_HPP */
