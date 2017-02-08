/* 
 * File:   LabeledMultiGraph.cpp
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

#ifndef HTD_HTD_LABELEDMULTIGRAPH_CPP
#define HTD_HTD_LABELEDMULTIGRAPH_CPP

#include <htd/LabeledMultiGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::MultiGraph>(manager)
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::MultiGraph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::LabeledMultiGraph & original) : htd::LabeledGraphType<htd::MultiGraph>(original)
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::IMultiGraph & original) : htd::LabeledGraphType<htd::MultiGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::ILabeledMultiGraph & original) : htd::LabeledGraphType<htd::MultiGraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledMultiGraph::~LabeledMultiGraph()
{

}

void htd::LabeledMultiGraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::MultiGraph>::removeVertex(vertex);
}

void htd::LabeledMultiGraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::MultiGraph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledMultiGraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::labelings();
}

std::size_t htd::LabeledMultiGraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledMultiGraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::labelNames();
}

const std::string & htd::LabeledMultiGraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::labelNameAtPosition(index);
}

bool htd::LabeledMultiGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledMultiGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledMultiGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledMultiGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::MultiGraph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledMultiGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::MultiGraph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledMultiGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::MultiGraph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledMultiGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::MultiGraph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledMultiGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::MultiGraph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledMultiGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::MultiGraph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::MultiGraph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledMultiGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::MultiGraph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledMultiGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::MultiGraph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledMultiGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::MultiGraph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledMultiGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::MultiGraph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledMultiGraph * htd::LabeledMultiGraph::clone(void) const
{
    return new htd::LabeledMultiGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiGraph * htd::LabeledMultiGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledMultiGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledMultiGraph::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledMultiGraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableMultiGraph * htd::LabeledMultiGraph::cloneMutableMultiGraph(void) const
{
    return clone();
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraph::cloneMutableLabeledMultiGraph(void) const
{
    return clone();
}
#endif

htd::LabeledMultiGraph & htd::LabeledMultiGraph::operator=(const htd::LabeledMultiGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::MultiGraph>::operator=(original);
    }

    return *this;
}

htd::LabeledMultiGraph & htd::LabeledMultiGraph::operator=(const htd::IMultiGraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::MultiGraph::operator=(original);
    }

    return *this;
}

htd::LabeledMultiGraph & htd::LabeledMultiGraph::operator=(const htd::ILabeledMultiGraph & original)
{
    if (this != &original)
    {
        htd::MultiGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledMultiGraph::assign(const htd::IMultiGraph & original)
{
    *this = original;
}

void htd::LabeledMultiGraph::assign(const htd::ILabeledMultiGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDMULTIGRAPH_CPP */
