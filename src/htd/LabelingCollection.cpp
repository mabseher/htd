/*
 * File:   LabelingCollection.cpp
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

#ifndef HTD_HTD_LABELINGCOLLECTION_CPP
#define HTD_HTD_LABELINGCOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/ILabel.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/LabelCollection.hpp>
#include <htd/ConstCollection.hpp>

#include <algorithm>
#include <stdexcept>

htd::LabelingCollection::LabelingCollection(void) : labelNames_(), content_()
{

}

htd::LabelingCollection::LabelingCollection(const LabelingCollection & original)
{
    for (const std::string & labelName : original.labelNames_)
    {
        setLabeling(labelName, original.content_.at(labelName)->clone());
    }
}

htd::LabelingCollection::LabelingCollection(const htd::ILabelingCollection & original)
{
    for (const std::string & labelName : original.labelNames())
    {
        setLabeling(labelName, original.labeling(labelName).clone());
    }
}

htd::LabelingCollection::~LabelingCollection()
{
    clear();
}

std::size_t htd::LabelingCollection::labelCount(void) const
{
    return content_.size();
}

htd::ConstCollection<std::string> htd::LabelingCollection::labelNames(void) const
{
    return htd::ConstCollection<std::string>::getInstance(labelNames_);
}

const std::string & htd::LabelingCollection::labelNameAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < labelNames_.size())

    return labelNames_[index];
}

htd::IGraphLabeling & htd::LabelingCollection::labeling(const std::string & labelName)
{
    auto position = content_.find(labelName);

    HTD_ASSERT(position != content_.end())

    return *(position->second);
}

const htd::IGraphLabeling & htd::LabelingCollection::labeling(const std::string & labelName) const
{
    auto position = content_.find(labelName);

    HTD_ASSERT(position != content_.end())

    return *(position->second);
}

bool htd::LabelingCollection::isLabelName(const std::string & labelName) const
{
    return content_.find(labelName) != content_.end();
}

void htd::LabelingCollection::setLabeling(const std::string & labelName, htd::IGraphLabeling * labeling)
{
    auto position = content_.find(labelName);

    if (position == content_.end())
    {
        content_[labelName] = labeling;

        labelNames_.push_back(labelName);

        std::sort(labelNames_.begin(), labelNames_.end());
    }
    else
    {
        delete position->second;

        content_[labelName] = labeling;
    }
}

void htd::LabelingCollection::removeLabeling(const std::string & labelName)
{
    auto position = content_.find(labelName);

    if (position != content_.end())
    {
        delete position->second;

        content_.erase(position);

        auto position2 = std::find(labelNames_.begin(), labelNames_.end(), labelName);

        labelNames_.erase(position2);
    }
}

void htd::LabelingCollection::removeVertexLabels(htd::vertex_t vertex)
{
    for (const std::string & labelName : labelNames_)
    {
        auto labeling = content_.at(labelName);

        if (labeling->isLabeledVertex(vertex))
        {
            labeling->removeVertexLabel(vertex);
        }
    }
}

void htd::LabelingCollection::removeEdgeLabels(htd::id_t edgeId)
{
    for (const std::string & labelName : labelNames_)
    {
        auto labeling = content_.at(labelName);

        if (labeling->isLabeledEdge(edgeId))
        {
            labeling->removeEdgeLabel(edgeId);
        }
    }
}

void htd::LabelingCollection::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    for (const std::string & labelName : labelNames_)
    {
        content_.at(labelName)->swapVertexLabels(vertex1, vertex2);
    }
}

void htd::LabelingCollection::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    for (const std::string & labelName : labelNames_)
    {
        content_.at(labelName)->swapEdgeLabels(edgeId1, edgeId2);
    }
}

htd::ILabelCollection * htd::LabelingCollection::exportVertexLabelCollection(htd::vertex_t vertex) const
{
    htd::ILabelCollection * ret = new LabelCollection();

    for (const std::string & labelName : labelNames_)
    {
        const htd::IGraphLabeling * labeling = content_.at(labelName);

        if (labeling != nullptr && labeling->isLabeledVertex(vertex))
        {
            ret->setLabel(labelName, labeling->vertexLabel(vertex).clone());
        }
    }

    return ret;
}

htd::ILabelCollection * htd::LabelingCollection::exportEdgeLabelCollection(htd::id_t edgeId) const
{
    htd::ILabelCollection * ret = new LabelCollection();

    for (const std::string & labelName : labelNames_)
    {
        const htd::IGraphLabeling * labeling = content_.at(labelName);

        if (labeling != nullptr && labeling->isLabeledEdge(edgeId))
        {
            ret->setLabel(labelName, labeling->edgeLabel(edgeId).clone());
        }
    }

    return ret;
}

void htd::LabelingCollection::clear(void)
{
    for (auto & labeling : content_)
    {
        if (labeling.second != nullptr)
        {
            delete labeling.second;
        }
    }

    content_.clear();
}

htd::LabelingCollection * htd::LabelingCollection::clone(void) const
{
    htd::LabelingCollection * ret = new htd::LabelingCollection();

    for (const std::string & labelName : labelNames_)
    {
        ret->setLabeling(labelName, content_.at(labelName)->clone());
    }

    return ret;
}

htd::IGraphLabeling & htd::LabelingCollection::operator[](const std::string & labelName)
{
    return labeling(labelName);
}

const htd::IGraphLabeling & htd::LabelingCollection::operator[](const std::string & labelName) const
{
    return labeling(labelName);
}

htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> htd::LabelingCollection::begin(void)
{
    return htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>>(content_.begin());
}

const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> htd::LabelingCollection::begin(void) const
{
    return htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>>(content_.begin());
}

htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> htd::LabelingCollection::end(void)
{
    return htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>>(content_.end());
}

const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> htd::LabelingCollection::end(void) const
{
    return htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>>(content_.end());
}

#endif /* HTD_HTD_LABELINGCOLLECTION_CPP */
