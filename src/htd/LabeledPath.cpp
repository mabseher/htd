/* 
 * File:   LabeledPath.cpp
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

#ifndef HTD_HTD_LABELEDPATH_CPP
#define	HTD_HTD_LABELEDPATH_CPP

#include <htd/LabeledPath.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

htd::LabeledPath::LabeledPath(void) : htd::Path::Path(), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledPath::LabeledPath(const htd::LabeledPath & original) : htd::Path::Path(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledPath::LabeledPath(const htd::ILabeledPath & original) : htd::Path::Path(original), labelings_(original.labelings().clone())
{

}

htd::LabeledPath::~LabeledPath()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledPath::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledPath::removeVertex(vertex);

    labelings_->removeVertexLabels(vertex);
}

const htd::ILabelingCollection & htd::LabeledPath::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledPath::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::ConstCollection<std::string> htd::LabeledPath::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledPath::labelName(htd::index_t index) const
{
    return labelings_->labelName(index);
}

bool htd::LabeledPath::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
}

bool htd::LabeledPath::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->isLabelingName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
}

const htd::ILabel & htd::LabeledPath::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).vertexLabel(vertex);
}

const htd::ILabel & htd::LabeledPath::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return labelings_->labeling(labelName).edgeLabel(edgeId);
}

void htd::LabeledPath::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setVertexLabel(vertex, label);
}

void htd::LabeledPath::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
}

void htd::LabeledPath::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeVertexLabel(vertex);
    }
}

void htd::LabeledPath::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeEdgeLabel(edgeId);
    }
}

void htd::LabeledPath::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledPath::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    labelings_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::LabeledPath::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledPath::swapVertexLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }

    labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
}

void htd::LabeledPath::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("void htd::LabeledPath::swapEdgeLabel(const std::string &, htd::id_t, htd::id_t)");
    }

    labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
}

htd::LabeledPath * htd::LabeledPath::clone(void) const
{
    return new htd::LabeledPath(*this);
}

#endif /* HTD_HTD_LABELEDPATH_CPP */
