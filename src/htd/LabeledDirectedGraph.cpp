/* 
 * File:   LabeledDirectedGraph.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPH_CPP
#define HTD_HTD_LABELEDDIRECTEDGRAPH_CPP

#include <htd/LabeledDirectedGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::DirectedGraph>(manager)
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::DirectedGraph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::LabeledDirectedGraph & original) : htd::LabeledGraphType<htd::DirectedGraph>(original)
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::IDirectedGraph & original) : htd::LabeledGraphType<htd::DirectedGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::ILabeledDirectedGraph & original) : htd::LabeledGraphType<htd::DirectedGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledDirectedGraph::~LabeledDirectedGraph()
{

}

void htd::LabeledDirectedGraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::DirectedGraph>::removeVertex(vertex);
}

void htd::LabeledDirectedGraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::DirectedGraph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledDirectedGraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::labelings();
}

std::size_t htd::LabeledDirectedGraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledDirectedGraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::labelNames();
}

const std::string & htd::LabeledDirectedGraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::labelNameAtPosition(index);
}

bool htd::LabeledDirectedGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledDirectedGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledDirectedGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledDirectedGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::DirectedGraph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledDirectedGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::DirectedGraph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledDirectedGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::DirectedGraph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledDirectedGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::DirectedGraph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledDirectedGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::DirectedGraph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledDirectedGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::DirectedGraph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::DirectedGraph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledDirectedGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::DirectedGraph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledDirectedGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::DirectedGraph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledDirectedGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::DirectedGraph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledDirectedGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::DirectedGraph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledDirectedGraph * htd::LabeledDirectedGraph::clone(void) const
{
    return new htd::LabeledDirectedGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraph * htd::LabeledDirectedGraph::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::LabeledDirectedGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::LabeledDirectedGraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IDirectedGraph * htd::LabeledDirectedGraph::cloneDirectedGraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledDirectedGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IDirectedMultiGraph * htd::LabeledDirectedGraph::cloneDirectedMultiGraph(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::LabeledDirectedGraph::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledDirectedGraph::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledDirectedGraph::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledDirectedGraph * htd::LabeledDirectedGraph::cloneLabeledDirectedGraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledDirectedGraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledDirectedMultiGraph * htd::LabeledDirectedGraph::cloneLabeledDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableDirectedGraph * htd::LabeledDirectedGraph::cloneMutableDirectedGraph(void) const
{
    return clone();
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraph::cloneMutableLabeledDirectedGraph(void) const
{
    return clone();
}
#endif

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::LabeledDirectedGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::DirectedGraph>::operator=(original);
    }

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::IDirectedGraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::DirectedGraph::operator=(original);
    }

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::ILabeledDirectedGraph & original)
{
    if (this != &original)
    {
        htd::DirectedGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledDirectedGraph::assign(const htd::IDirectedGraph & original)
{
    *this = original;
}

void htd::LabeledDirectedGraph::assign(const htd::ILabeledDirectedGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPH_CPP */
