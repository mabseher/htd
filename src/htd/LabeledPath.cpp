/* 
 * File:   LabeledPath.cpp
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

#ifndef HTD_HTD_LABELEDPATH_CPP
#define HTD_HTD_LABELEDPATH_CPP

#include <htd/LabeledPath.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledPath::LabeledPath(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::Path>(manager)
{

}

htd::LabeledPath::LabeledPath(const htd::LabeledPath & original) : htd::LabeledGraphType<htd::Path>(original)
{

}

htd::LabeledPath::LabeledPath(const htd::IPath & original) : htd::LabeledGraphType<htd::Path>(original.managementInstance())
{
    *this = original;
}

htd::LabeledPath::LabeledPath(const htd::ILabeledPath & original) : htd::LabeledGraphType<htd::Path>(original.managementInstance())
{
    *this = original;
}

htd::LabeledPath::~LabeledPath()
{

}

void htd::LabeledPath::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Path>::removeVertex(vertex);
}

const htd::ILabelingCollection & htd::LabeledPath::labelings(void) const
{
    return htd::LabeledGraphType<htd::Path>::labelings();
}

std::size_t htd::LabeledPath::labelCount(void) const
{
    return htd::LabeledGraphType<htd::Path>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledPath::labelNames(void) const
{
    return htd::LabeledGraphType<htd::Path>::labelNames();
}

const std::string & htd::LabeledPath::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::Path>::labelNameAtPosition(index);
}

bool htd::LabeledPath::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Path>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledPath::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Path>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledPath::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Path>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledPath::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Path>::edgeLabel(labelName, edgeId);
}

void htd::LabeledPath::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Path>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledPath::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Path>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledPath::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Path>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledPath::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Path>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledPath::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Path>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledPath::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Path>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledPath::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Path>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledPath::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Path>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledPath::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::Path>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledPath::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::Path>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledPath * htd::LabeledPath::clone(void) const
{
    return new htd::LabeledPath(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IPath * htd::LabeledPath::clonePath(void) const
{
    return clone();
}

htd::ITree * htd::LabeledPath::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::LabeledPath::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::LabeledPath::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::LabeledPath::cloneHypergraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledPath::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledPath * htd::LabeledPath::cloneLabeledPath(void) const
{
    return clone();
}

htd::ILabeledTree * htd::LabeledPath::cloneLabeledTree(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::LabeledPath::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledPath::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledPath::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledPath::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutablePath * htd::LabeledPath::cloneMutablePath(void) const
{
    return clone();
}

htd::IMutableLabeledPath * htd::LabeledPath::cloneMutableLabeledPath(void) const
{
    return clone();
}
#endif

htd::LabeledPath & htd::LabeledPath::operator=(const htd::LabeledPath & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::Path>::operator=(original);
    }

    return *this;
}

htd::LabeledPath & htd::LabeledPath::operator=(const htd::IPath & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::Path::operator=(original);
    }

    return *this;
}

htd::LabeledPath & htd::LabeledPath::operator=(const htd::ILabeledPath & original)
{
    if (this != &original)
    {
        htd::Path::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledPath::assign(const htd::IPath & original)
{
    *this = original;
}

void htd::LabeledPath::assign(const htd::ILabeledPath & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDPATH_CPP */
