/* 
 * File:   LabeledHypergraph.cpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_CPP
#define HTD_HTD_LABELEDHYPERGRAPH_CPP

#include <htd/LabeledHypergraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledHypergraph::LabeledHypergraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::Hypergraph>(manager)
{

}

htd::LabeledHypergraph::LabeledHypergraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::Hypergraph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledHypergraph::LabeledHypergraph(const htd::LabeledHypergraph & original) : htd::LabeledGraphType<htd::Hypergraph>(original)
{

}

htd::LabeledHypergraph::LabeledHypergraph(const htd::IHypergraph & original) : htd::LabeledGraphType<htd::Hypergraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledHypergraph::LabeledHypergraph(const htd::ILabeledHypergraph & original) : htd::LabeledGraphType<htd::Hypergraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledHypergraph::~LabeledHypergraph()
{

}

void htd::LabeledHypergraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Hypergraph>::removeVertex(vertex);
}

void htd::LabeledHypergraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Hypergraph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledHypergraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::labelings();
}

std::size_t htd::LabeledHypergraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledHypergraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::labelNames();
}

const std::string & htd::LabeledHypergraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::labelNameAtPosition(index);
}

bool htd::LabeledHypergraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledHypergraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledHypergraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledHypergraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Hypergraph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledHypergraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Hypergraph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledHypergraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Hypergraph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledHypergraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Hypergraph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledHypergraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Hypergraph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledHypergraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Hypergraph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledHypergraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Hypergraph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledHypergraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Hypergraph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledHypergraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Hypergraph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledHypergraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::Hypergraph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledHypergraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::Hypergraph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledHypergraph * htd::LabeledHypergraph::clone(void) const
{
    return new htd::LabeledHypergraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IHypergraph * htd::LabeledHypergraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledHypergraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledHypergraph::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledHypergraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableHypergraph * htd::LabeledHypergraph::cloneMutableHypergraph(void) const
{
    return clone();
}

htd::IMutableLabeledHypergraph * htd::LabeledHypergraph::cloneMutableLabeledHypergraph(void) const
{
    return clone();
}
#endif

htd::LabeledHypergraph & htd::LabeledHypergraph::operator=(const htd::LabeledHypergraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::Hypergraph>::operator=(original);
    }

    return *this;
}

htd::LabeledHypergraph & htd::LabeledHypergraph::operator=(const htd::IHypergraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::Hypergraph::operator=(original);
    }

    return *this;
}

htd::LabeledHypergraph & htd::LabeledHypergraph::operator=(const htd::ILabeledHypergraph & original)
{
    if (this != &original)
    {
        htd::Hypergraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledHypergraph::assign(const htd::IHypergraph & original)
{
    *this = original;
}

void htd::LabeledHypergraph::assign(const htd::ILabeledHypergraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDHYPERGRAPH_CPP */
