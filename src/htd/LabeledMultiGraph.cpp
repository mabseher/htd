/* 
 * File:   LabeledMultiGraph.cpp
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

#ifndef HTD_HTD_LABELEDMULTIGRAPH_CPP
#define	HTD_HTD_LABELEDMULTIGRAPH_CPP

#include <htd/LabeledMultiGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledMultiGraph::LabeledMultiGraph(void) : htd::MultiGraph::MultiGraph(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(std::size_t initialSize) : htd::MultiGraph::MultiGraph(initialSize), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::LabeledMultiGraph & original) : htd::MultiGraph::MultiGraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::IMultiGraph & original) : htd::MultiGraph::MultiGraph(original), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledMultiGraph::LabeledMultiGraph(const htd::ILabeledMultiGraph & original) : htd::MultiGraph::MultiGraph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledMultiGraph::~LabeledMultiGraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledMultiGraph::removeVertex(htd::vertex_t vertex)
{
    htd::MultiGraph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledMultiGraph::removeEdge(htd::id_t edgeId)
{
    htd::MultiGraph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledMultiGraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledMultiGraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledMultiGraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledMultiGraph::labelNameAtPosition(htd::index_t index) const
{
    return labelings_->labelNameAtPosition(index);
}

bool htd::LabeledMultiGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledMultiGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledMultiGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledMultiGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledMultiGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledMultiGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledMultiGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledMultiGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledMultiGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledMultiGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledMultiGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledMultiGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferVertexLabel(vertex);
}

htd::ILabel * htd::LabeledMultiGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
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
        htd::MultiGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings_->clone();
    }

    return *this;
}

htd::LabeledMultiGraph & htd::LabeledMultiGraph::operator=(const htd::IMultiGraph & original)
{
    if (this != &original)
    {
        htd::MultiGraph::operator=(original);

        delete labelings_;

        labelings_ = new htd::LabelingCollection();
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

#endif /* HTD_HTD_LABELEDMULTIGRAPH_CPP */
