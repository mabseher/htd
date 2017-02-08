/* 
 * File:   LabeledDirectedMultiGraph.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP
#define HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP

#include <htd/LabeledDirectedMultiGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::DirectedMultiGraph>(manager)
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::DirectedMultiGraph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::LabeledDirectedMultiGraph & original) : htd::LabeledGraphType<htd::DirectedMultiGraph>(original)
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::IDirectedMultiGraph & original) : htd::LabeledGraphType<htd::DirectedMultiGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) : htd::LabeledGraphType<htd::DirectedMultiGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledDirectedMultiGraph::~LabeledDirectedMultiGraph()
{

}

void htd::LabeledDirectedMultiGraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::removeVertex(vertex);
}

void htd::LabeledDirectedMultiGraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledDirectedMultiGraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::labelings();
}

std::size_t htd::LabeledDirectedMultiGraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledDirectedMultiGraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::labelNames();
}

const std::string & htd::LabeledDirectedMultiGraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::labelNameAtPosition(index);
}

bool htd::LabeledDirectedMultiGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledDirectedMultiGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledDirectedMultiGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledDirectedMultiGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledDirectedMultiGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledDirectedMultiGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledDirectedMultiGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledDirectedMultiGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledDirectedMultiGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedMultiGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledDirectedMultiGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledDirectedMultiGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::DirectedMultiGraph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledDirectedMultiGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledDirectedMultiGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::DirectedMultiGraph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraph::clone(void) const
{
    return new htd::LabeledDirectedMultiGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiGraph * htd::LabeledDirectedMultiGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledDirectedMultiGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IDirectedMultiGraph * htd::LabeledDirectedMultiGraph::cloneDirectedMultiGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledDirectedMultiGraph::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledDirectedMultiGraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraph::cloneLabeledDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableDirectedMultiGraph * htd::LabeledDirectedMultiGraph::cloneMutableDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraph::cloneMutableLabeledDirectedMultiGraph(void) const
{
    return clone();
}
#endif

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::LabeledDirectedMultiGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::DirectedMultiGraph>::operator=(original);
    }

    return *this;
}

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::IDirectedMultiGraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::DirectedMultiGraph::operator=(original);
    }

    return *this;
}

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::ILabeledDirectedMultiGraph & original)
{
    if (this != &original)
    {
        htd::DirectedMultiGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledDirectedMultiGraph::assign(const htd::IDirectedMultiGraph & original)
{
    *this = original;
}

void htd::LabeledDirectedMultiGraph::assign(const htd::ILabeledDirectedMultiGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP */
