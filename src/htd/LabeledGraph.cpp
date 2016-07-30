/* 
 * File:   LabeledGraph.cpp
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

#ifndef HTD_HTD_LABELEDGRAPH_CPP
#define	HTD_HTD_LABELEDGRAPH_CPP

#include <htd/LabeledGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledGraph::LabeledGraph(const htd::LibraryInstance * const manager) : htd::Graph::Graph(manager), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledGraph::LabeledGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : htd::Graph::Graph(manager, initialSize), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledGraph::LabeledGraph(const htd::LabeledGraph & original) : htd::Graph::Graph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledGraph::LabeledGraph(const htd::IGraph & original) : htd::Graph::Graph(original), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledGraph::LabeledGraph(const htd::ILabeledGraph & original) : htd::Graph::Graph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledGraph::~LabeledGraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledGraph::removeVertex(htd::vertex_t vertex)
{
    htd::Graph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledGraph::removeEdge(htd::id_t edgeId)
{
    htd::Graph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledGraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledGraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledGraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledGraph::labelNameAtPosition(htd::index_t index) const
{
    return labelings_->labelNameAtPosition(index);
}

bool htd::LabeledGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferVertexLabel(vertex);
}

htd::ILabel * htd::LabeledGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    HTD_ASSERT(labelings_->isLabelName(labelName))

    return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
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
        htd::Graph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings_->clone();
    }

    return *this;
}

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::IGraph & original)
{
    if (this != &original)
    {
        htd::Graph::operator=(original);

        delete labelings_;

        labelings_ = new htd::LabelingCollection();
    }

    return *this;
}

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::IMultiGraph & original)
{
    htd::Graph::operator=(original);

    delete labelings_;

    labelings_ = new htd::LabelingCollection();

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

htd::LabeledGraph & htd::LabeledGraph::operator=(const htd::ILabeledMultiGraph & original)
{
    htd::Graph::operator=(original);

    delete labelings_;

    labelings_ = original.labelings().clone();

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::LabeledGraph::assign(const htd::IGraph & original)
{
    *this = original;
}

void htd::LabeledGraph::assign(const htd::IMultiGraph & original)
{
    *this = original;
}

void htd::LabeledGraph::assign(const htd::ILabeledGraph & original)
{
    *this = original;
}

void htd::LabeledGraph::assign(const htd::ILabeledMultiGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_LABELEDGRAPH_CPP */
