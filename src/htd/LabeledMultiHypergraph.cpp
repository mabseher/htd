/* 
 * File:   LabeledMultiHypergraph.cpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP
#define	HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP

#include <htd/LabeledMultiHypergraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(void) : htd::MultiHypergraph::MultiHypergraph(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::LabeledMultiHypergraph & original) : htd::MultiHypergraph::MultiHypergraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::IMultiHypergraph & original) : htd::MultiHypergraph::MultiHypergraph(original), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledMultiHypergraph::LabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original) : htd::MultiHypergraph::MultiHypergraph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledMultiHypergraph::~LabeledMultiHypergraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledMultiHypergraph::removeVertex(htd::vertex_t vertex)
{
    htd::MultiHypergraph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledMultiHypergraph::removeEdge(htd::id_t edgeId)
{
    htd::MultiHypergraph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledMultiHypergraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledMultiHypergraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledMultiHypergraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledMultiHypergraph::labelNameAtPosition(htd::index_t index) const
{
    return labelings_->labelNameAtPosition(index);
}

bool htd::LabeledMultiHypergraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledMultiHypergraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledMultiHypergraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledMultiHypergraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledMultiHypergraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledMultiHypergraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledMultiHypergraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledMultiHypergraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledMultiHypergraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiHypergraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledMultiHypergraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (!labelings_->isLabelName(labelName))
    {
        throw std::logic_error("void htd::LabeledMultiHypergraph::swapVertexLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiHypergraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    if (!labelings_->isLabelName(labelName))
    {
        throw std::logic_error("void htd::LabeledMultiHypergraph::swapEdgeLabel(const std::string &, htd::id_t, htd::id_t)");
    }

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledMultiHypergraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (!labelings_->isLabelName(labelName))
    {
        throw std::logic_error("htd::ILabel * htd::LabeledMultiHypergraph::transferVertexLabel(const std::string &, htd::vertex_t)");
    }

    return labelings_->labeling(labelName).transferVertexLabel(vertex);
}

htd::ILabel * htd::LabeledMultiHypergraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (!labelings_->isLabelName(labelName))
    {
        throw std::logic_error("htd::ILabel * htd::LabeledMultiHypergraph::transferEdgeLabel(const std::string &, htd::id_t)");
    }

    return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
}

htd::LabeledMultiHypergraph * htd::LabeledMultiHypergraph::clone(void) const
{
    return new htd::LabeledMultiHypergraph(*this);
}

htd::LabeledMultiHypergraph & htd::LabeledMultiHypergraph::operator=(const htd::LabeledMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::MultiHypergraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings_->clone();
    }

    return *this;
}

htd::LabeledMultiHypergraph & htd::LabeledMultiHypergraph::operator=(const htd::IMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::MultiHypergraph::operator=(original);

        delete labelings_;

        labelings_ = new htd::LabelingCollection();
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

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPH_CPP */
