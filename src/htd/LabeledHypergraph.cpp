/* 
 * File:   LabeledHypergraph.cpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_CPP
#define	HTD_HTD_LABELEDHYPERGRAPH_CPP

#include <htd/LabeledHypergraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

htd::LabeledHypergraph::LabeledHypergraph(void) : htd::Hypergraph::Hypergraph(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledHypergraph::LabeledHypergraph(const htd::LabeledHypergraph & original) : htd::Hypergraph::Hypergraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledHypergraph::LabeledHypergraph(const htd::ILabeledHypergraph & original) : htd::Hypergraph::Hypergraph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledHypergraph::~LabeledHypergraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledHypergraph::removeVertex(htd::vertex_t vertex)
{
    htd::Hypergraph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledHypergraph::removeEdge(htd::id_t edgeId)
{
    htd::Hypergraph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledHypergraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledHypergraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledHypergraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledHypergraph::labelName(htd::index_t index) const
{
    return labelings_->labelName(index);
}

bool htd::LabeledHypergraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledHypergraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledHypergraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledHypergraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledHypergraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledHypergraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledHypergraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledHypergraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledHypergraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledHypergraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledHypergraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledHypergraph::swapVertexLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledHypergraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledHypergraph::swapEdgeLabel(const std::string &, htd::id_t, htd::id_t)");
    }

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::LabeledHypergraph * htd::LabeledHypergraph::clone(void) const
{
    return new htd::LabeledHypergraph(*this);
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_CPP */
