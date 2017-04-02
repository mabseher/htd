/* 
 * File:   LabeledTree.cpp
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

#ifndef HTD_HTD_LABELEDTREE_CPP
#define HTD_HTD_LABELEDTREE_CPP

#include <htd/LabeledTree.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledTree::LabeledTree(const htd::LibraryInstance * const manager) : htd::LabeledGraphType<htd::Tree>(manager)
{

}

htd::LabeledTree::LabeledTree(const htd::LabeledTree & original) : htd::LabeledGraphType<htd::Tree>(original)
{

}

htd::LabeledTree::LabeledTree(const htd::ITree & original) : htd::LabeledGraphType<htd::Tree>(original.managementInstance())
{
    *this = original;
}

htd::LabeledTree::LabeledTree(const htd::ILabeledTree & original) : htd::LabeledGraphType<htd::Tree>(original.managementInstance())
{
    *this = original;
}

htd::LabeledTree::~LabeledTree()
{

}

void htd::LabeledTree::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Tree>::removeVertex(vertex);
}

const htd::ILabelingCollection & htd::LabeledTree::labelings(void) const
{
    return htd::LabeledGraphType<htd::Tree>::labelings();
}

std::size_t htd::LabeledTree::labelCount(void) const
{
    return htd::LabeledGraphType<htd::Tree>::labelCount();
}

htd::ConstCollection<std::string> htd::LabeledTree::labelNames(void) const
{
    return htd::LabeledGraphType<htd::Tree>::labelNames();
}

const std::string & htd::LabeledTree::labelNameAtPosition(htd::index_t index) const
{
    return htd::LabeledGraphType<htd::Tree>::labelNameAtPosition(index);
}

bool htd::LabeledTree::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Tree>::isLabeledVertex(labelName, vertex);
}

bool htd::LabeledTree::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Tree>::isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::LabeledTree::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return htd::LabeledGraphType<htd::Tree>::vertexLabel(labelName, vertex);
}

const htd::ILabel & htd::LabeledTree::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return htd::LabeledGraphType<htd::Tree>::edgeLabel(labelName, edgeId);
}

void htd::LabeledTree::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Tree>::setVertexLabel(labelName, vertex, label);
}

void htd::LabeledTree::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    htd::LabeledGraphType<htd::Tree>::setEdgeLabel(labelName, edgeId, label);
}

void htd::LabeledTree::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    htd::LabeledGraphType<htd::Tree>::removeVertexLabel(labelName, vertex);
}

void htd::LabeledTree::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    htd::LabeledGraphType<htd::Tree>::removeEdgeLabel(labelName, edgeId);
}

void htd::LabeledTree::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Tree>::swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledTree::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Tree>::swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledTree::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::LabeledGraphType<htd::Tree>::swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::LabeledTree::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    htd::LabeledGraphType<htd::Tree>::swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledTree::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    return htd::LabeledGraphType<htd::Tree>::transferVertexLabel(labelName, vertex);
}

htd::ILabel * htd::LabeledTree::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    return htd::LabeledGraphType<htd::Tree>::transferEdgeLabel(labelName, edgeId);
}

htd::LabeledTree * htd::LabeledTree::clone(void) const
{
    return new htd::LabeledTree(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::ITree * htd::LabeledTree::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::LabeledTree::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::LabeledTree::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::LabeledTree::cloneHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::LabeledTree::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledTree::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledTree * htd::LabeledTree::cloneLabeledTree(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::LabeledTree::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledTree::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledTree::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledTree::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableTree * htd::LabeledTree::cloneMutableTree(void) const
{
    return clone();
}

htd::IMutableLabeledTree * htd::LabeledTree::cloneMutableLabeledTree(void) const
{
    return clone();
}
#endif

htd::LabeledTree & htd::LabeledTree::operator=(const htd::LabeledTree & original)
{
    if (this != &original)
    {
        htd::LabeledGraphType<htd::Tree>::operator=(original);
    }

    return *this;
}

htd::LabeledTree & htd::LabeledTree::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        labelings_->clear();

        htd::Tree::operator=(original);
    }

    return *this;
}

htd::LabeledTree & htd::LabeledTree::operator=(const htd::ILabeledTree & original)
{
    if (this != &original)
    {
        htd::Tree::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledTree::assign(const htd::ITree & original)
{
    *this = original;
}

void htd::LabeledTree::assign(const htd::ILabeledTree & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDTREE_CPP */
