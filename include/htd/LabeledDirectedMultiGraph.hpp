/*
 * File:   LabeledDirectedMultiGraph.hpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP
#define	HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledDirectedMultiGraph.hpp>
#include <htd/DirectedMultiGraph.hpp>

namespace htd
{
    class LabeledDirectedMultiGraph : public htd::DirectedMultiGraph, public virtual htd::IMutableLabeledDirectedMultiGraph
    {
        public:
            LabeledDirectedMultiGraph(void);

            LabeledDirectedMultiGraph(std::size_t initialSize);

            LabeledDirectedMultiGraph(const LabeledDirectedMultiGraph & original);

            LabeledDirectedMultiGraph(const htd::IDirectedMultiGraph & original);

            LabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original);
            
            virtual ~LabeledDirectedMultiGraph();

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeEdge(htd::id_t edgeId) HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<std::string> labelNames(void) const HTD_OVERRIDE;

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

            htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

            LabeledDirectedMultiGraph * clone(void) const HTD_OVERRIDE;

            LabeledDirectedMultiGraph & operator=(const LabeledDirectedMultiGraph & original);

            LabeledDirectedMultiGraph & operator=(const htd::IDirectedMultiGraph & original) HTD_OVERRIDE;

            LabeledDirectedMultiGraph & operator=(const htd::ILabeledDirectedMultiGraph & original) HTD_OVERRIDE;

        private:
            htd::ILabelingCollection * labelings_;
    };
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_HPP */
