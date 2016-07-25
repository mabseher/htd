/* 
 * File:   LabeledDirectedGraph.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPH_CPP
#define	HTD_HTD_LABELEDDIRECTEDGRAPH_CPP

#include <htd/LabeledDirectedGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledDirectedGraph::LabeledDirectedGraph(void) : htd::DirectedGraph::DirectedGraph(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(std::size_t initialSize) : htd::DirectedGraph::DirectedGraph(initialSize), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::LabeledDirectedGraph & original) : htd::DirectedGraph::DirectedGraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::IDirectedGraph & original) : htd::DirectedGraph::DirectedGraph(original), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedGraph::LabeledDirectedGraph(const htd::ILabeledDirectedGraph & original) : htd::DirectedGraph::DirectedGraph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledDirectedGraph::~LabeledDirectedGraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledDirectedGraph::removeVertex(htd::vertex_t vertex)
{
    htd::DirectedGraph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledDirectedGraph::removeEdge(htd::id_t edgeId)
{
    htd::DirectedGraph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledDirectedGraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledDirectedGraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledDirectedGraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledDirectedGraph::labelNameAtPosition(htd::index_t index) const
{
    return labelings_->labelNameAtPosition(index);
}

bool htd::LabeledDirectedGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledDirectedGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledDirectedGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledDirectedGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledDirectedGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledDirectedGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledDirectedGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledDirectedGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledDirectedGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledDirectedGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledDirectedGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferVertexLabel(vertex);
}

htd::ILabel * htd::LabeledDirectedGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
}

htd::LabeledDirectedGraph * htd::LabeledDirectedGraph::clone(void) const
{
    return new htd::LabeledDirectedGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraph * htd::LabeledDirectedGraph::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::LabeledDirectedGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::LabeledDirectedGraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IDirectedGraph * htd::LabeledDirectedGraph::cloneDirectedGraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::LabeledDirectedGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IDirectedMultiGraph * htd::LabeledDirectedGraph::cloneDirectedMultiGraph(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::LabeledDirectedGraph::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::LabeledDirectedGraph::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::LabeledDirectedGraph::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledDirectedGraph * htd::LabeledDirectedGraph::cloneLabeledDirectedGraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::LabeledDirectedGraph::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledDirectedMultiGraph * htd::LabeledDirectedGraph::cloneLabeledDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableDirectedGraph * htd::LabeledDirectedGraph::cloneMutableDirectedGraph(void) const
{
    return clone();
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraph::cloneMutableLabeledDirectedGraph(void) const
{
    return clone();
}
#endif

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::LabeledDirectedGraph & original)
{
    if (this != &original)
    {
        htd::DirectedGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings_->clone();
    }

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::IDirectedGraph & original)
{
    if (this != &original)
    {
        htd::DirectedGraph::operator=(original);

        delete labelings_;

        labelings_ = new htd::LabelingCollection();
    }

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::IDirectedMultiGraph & original)
{
    htd::DirectedGraph::operator=(original);

    delete labelings_;

    labelings_ = new htd::LabelingCollection();

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::ILabeledDirectedGraph & original)
{
    if (this != &original)
    {
        htd::DirectedGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

htd::LabeledDirectedGraph & htd::LabeledDirectedGraph::operator=(const htd::ILabeledDirectedMultiGraph & original)
{
    htd::DirectedGraph::operator=(original);

    delete labelings_;

    labelings_ = original.labelings().clone();

    return *this;
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPH_CPP */
