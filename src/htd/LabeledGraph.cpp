/* 
 * File:   LabeledGraph.cpp
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

#ifndef HTD_HTD_LABELEDGRAPH_CPP
#define HTD_HTD_LABELEDGRAPH_CPP

#include <htd/LabeledGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledGraph::LabeledGraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::Graph>(manager)
{

}

htd::LabeledGraph::LabeledGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::Graph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledGraph::LabeledGraph(const htd::LabeledGraph & original) : htd::LabeledGraphType<htd::Graph>(original)
{

}

htd::LabeledGraph::LabeledGraph(const htd::IGraph & original) : htd::LabeledGraphType<htd::Graph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledGraph::LabeledGraph(const htd::ILabeledGraph & original) : htd::LabeledGraphType<htd::Graph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledGraph::~LabeledGraph()
{

}

void htd::LabeledGraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Graph>::removeVertex(vertex);
}

void htd::LabeledGraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Graph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledGraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::Graph>::labelings();
}

std::size_t htd::LabeledGraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::Graph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledGraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::Graph>::labelNames();
}

const std::string & htd::LabeledGraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::Graph>::labelNameAtPosition(index);
}

bool htd::LabeledGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Graph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Graph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Graph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Graph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Graph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Graph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Graph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Graph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Graph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Graph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Graph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Graph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::Graph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::Graph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledGraph * htd::LabeledGraph::clone(void) const
{
    return new htd::LabeledGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraph * htd::LabeledGraph::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::LabeledGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::LabeledGraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::LabeledGraph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::LabeledGraph::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledGraph::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledGraph::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledGraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableGraph * htd::LabeledGraph::cloneMutableGraph(void) const
{
    return clone();
}

htd::IMutableLabeledGraph * htd::LabeledGraph::cloneMutableLabeledGraph(void) const
{
    return clone();
}
#endif

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::LabeledGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::Graph>::operator=(original);
    }

    return *this;
}

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::IGraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::Graph::operator=(original);
    }

    return *this;
}

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::ILabeledGraph & original)
{
    if (this != &original)
    {
        htd::Graph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledGraph::assign(const htd::IGraph & original)
{
    *this = original;
}

void htd::LabeledGraph::assign(const htd::ILabeledGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDGRAPH_CPP */
