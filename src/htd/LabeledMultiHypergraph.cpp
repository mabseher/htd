/* 
 * File:   LabeledMultiHypergraph.cpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP
#define HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP

#include <htd/LabeledMultiHypergraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::MultiHypergraph>(manager)
{

}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::LabeledGraphType<htd::MultiHypergraph>(manager)
{
    addVertices(initialSize);
}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::LabeledMultiHypergraph & original) : htd::LabeledGraphType<htd::MultiHypergraph>(original)
{

}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::IMultiHypergraph & original) : htd::LabeledGraphType<htd::MultiHypergraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original) : htd::LabeledGraphType<htd::MultiHypergraph>(original.managementInstance())
{
    *this = original;
}

htd::LabeledMultiHypergraph::~LabeledMultiHypergraph()
{

}

void htd::LabeledMultiHypergraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::removeVertex(vertex);
}

void htd::LabeledMultiHypergraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::removeEdge(edgeId);
}

const htd::ILabelingCollection & htd::LabeledMultiHypergraph::labelings(void) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::labelings();
}

std::size_t htd::LabeledMultiHypergraph::labelCount(void) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledMultiHypergraph::labelNames(void) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::labelNames();
}

const std::string & htd::LabeledMultiHypergraph::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::labelNameAtPosition(index);
}

bool htd::LabeledMultiHypergraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledMultiHypergraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledMultiHypergraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledMultiHypergraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::edgeLabel(labelName, edgeId);
}

void htd::LabeledMultiHypergraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledMultiHypergraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledMultiHypergraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledMultiHypergraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledMultiHypergraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiHypergraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledMultiHypergraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledMultiHypergraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::MultiHypergraph>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledMultiHypergraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledMultiHypergraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::MultiHypergraph>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledMultiHypergraph * htd::LabeledMultiHypergraph::clone(void) const
{
    return new htd::LabeledMultiHypergraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiHypergraph * htd::LabeledMultiHypergraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledMultiHypergraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableMultiHypergraph * htd::LabeledMultiHypergraph::cloneMutableMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraph::cloneMutableLabeledMultiHypergraph(void) const
{
    return clone();
}
#endif

htd::LabeledMultiHypergraph & htd::LabeledMultiHypergraph::operator=(const htd::LabeledMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::MultiHypergraph>::operator=(original);
    }

    return *this;
}

htd::LabeledMultiHypergraph & htd::LabeledMultiHypergraph::operator=(const htd::IMultiHypergraph & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::MultiHypergraph::operator=(original);
    }

    return *this;
}

htd::LabeledMultiHypergraph & htd::LabeledMultiHypergraph::operator=(const htd::ILabeledMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::MultiHypergraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledMultiHypergraph::assign(const htd::IMultiHypergraph & original)
{
    *this = original;
}

void htd::LabeledMultiHypergraph::assign(const htd::ILabeledMultiHypergraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP */
