/* 
 * File:   LabeledDirectedMultiGraph.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP
#define	HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP

#include <htd/LabeledDirectedMultiGraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(void) : htd::DirectedMultiGraph::DirectedMultiGraph(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(std::size_t initialSize) : htd::DirectedMultiGraph::DirectedMultiGraph(initialSize), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::LabeledDirectedMultiGraph & original) : htd::DirectedMultiGraph::DirectedMultiGraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::IDirectedMultiGraph & original) : htd::DirectedMultiGraph::DirectedMultiGraph(original), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledDirectedMultiGraph::LabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) : htd::DirectedMultiGraph::DirectedMultiGraph(original), labelings_(original.labelings().clone())
{

}

htd::LabeledDirectedMultiGraph::~LabeledDirectedMultiGraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledDirectedMultiGraph::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledDirectedMultiGraph::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

void htd::LabeledDirectedMultiGraph::removeEdge(htd::id_t edgeId)
{
    htd::LabeledDirectedMultiGraph::removeEdge(edgeId);

    labelings_->removeEdgeLabels(edgeId);
}

const htd::ILabelingCollection & htd::LabeledDirectedMultiGraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledDirectedMultiGraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledDirectedMultiGraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledDirectedMultiGraph::labelName(htd::index_t index) const
{
    return labelings_->labelName(index);
}

bool htd::LabeledDirectedMultiGraph::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledDirectedMultiGraph::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledDirectedMultiGraph::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledDirectedMultiGraph::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledDirectedMultiGraph::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledDirectedMultiGraph::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledDirectedMultiGraph::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledDirectedMultiGraph::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledDirectedMultiGraph::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedMultiGraph::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledDirectedMultiGraph::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledDirectedMultiGraph::swapVertexLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledDirectedMultiGraph::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledDirectedMultiGraph::swapEdgeLabel(const std::string &, htd::id_t, htd::id_t)");
    }

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::ILabel * htd::LabeledDirectedMultiGraph::transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("htd::ILabel * htd::LabeledDirectedMultiGraph::transferVertexLabel(const std::string &, htd::vertex_t)");
    }

    return labelings_->labeling(labelName).transferVertexLabel(vertex);
}

htd::ILabel * htd::LabeledDirectedMultiGraph::transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("htd::ILabel * htd::LabeledDirectedMultiGraph::transferEdgeLabel(const std::string &, htd::id_t)");
    }

    return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
}

htd::LabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraph::clone(void) const
{
    return new htd::LabeledDirectedMultiGraph(*this);
}

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::LabeledDirectedMultiGraph & original)
{
    if (this != &original)
    {
        htd::DirectedMultiGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings_->clone();
    }

    return *this;
}

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::IDirectedMultiGraph & original)
{
    if (this != &original)
    {
        htd::DirectedMultiGraph::operator=(original);

        delete labelings_;

        labelings_ = new htd::LabelingCollection();
    }

    return *this;
}

htd::LabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraph::operator=(const htd::ILabeledDirectedMultiGraph & original)
{
    if (this != &original)
    {
        htd::DirectedMultiGraph::operator=(original);

        delete labelings_;

        labelings_ = original.labelings().clone();
    }

    return *this;
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPH_CPP */
