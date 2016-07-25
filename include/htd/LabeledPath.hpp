/*
 * File:   LabeledPath.hpp
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

#ifndef HTD_HTD_LABELEDPATH_HPP
#define	HTD_HTD_LABELEDPATH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/Path.hpp>

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledPath interface.
     */
    class LabeledPath : public htd::Path, public virtual htd::IMutableLabeledPath
    {
        public:
            /**
             *  Constructor for a labeled path.
             */
            LabeledPath(void);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            LabeledPath(const LabeledPath & original);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original path.
             */
            LabeledPath(const htd::IPath & original);

            /**
             *  Copy constructor for a labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            LabeledPath(const htd::ILabeledPath & original);
            
            virtual ~LabeledPath();

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelNameAtPosition(htd::index_t index) const HTD_OVERRIDE;

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

            htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            LabeledPath * clone(void) const HTD_OVERRIDE;
#else
            LabeledPath * clone(void) const;

            htd::IPath * clonePath(void) const HTD_OVERRIDE;

            htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            htd::ILabeledPath * cloneLabeledPath(void) const HTD_OVERRIDE;

            htd::ILabeledTree * cloneLabeledTree(void) const HTD_OVERRIDE;

            htd::ILabeledGraph * cloneLabeledGraph(void) const HTD_OVERRIDE;

            htd::ILabeledMultiGraph * cloneLabeledMultiGraph(void) const HTD_OVERRIDE;

            htd::ILabeledHypergraph * cloneLabeledHypergraph(void) const HTD_OVERRIDE;

            htd::ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const HTD_OVERRIDE;

            htd::IMutablePath * cloneMutablePath(void) const HTD_OVERRIDE;

            htd::IMutableLabeledPath * cloneMutableLabeledPath(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            LabeledPath & operator=(const LabeledPath & original);

            LabeledPath & operator=(const htd::IPath & original) HTD_OVERRIDE;

            LabeledPath & operator=(const htd::ILabeledPath & original) HTD_OVERRIDE;

        private:
            htd::ILabelingCollection * labelings_;
    };
}

#endif /* HTD_HTD_LABELEDPATH_HPP */
