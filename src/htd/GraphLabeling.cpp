/*
 * File:   GraphLabeling.cpp
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

#ifndef HTD_HTD_GRAPHLABELING_CPP
#define HTD_HTD_GRAPHLABELING_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

htd::GraphLabeling::GraphLabeling(void) : vertexLabels_(), edgeLabels_()
{

}

htd::GraphLabeling::~GraphLabeling()
{
    clear();
}

std::size_t htd::GraphLabeling::vertexLabelCount(void) const
{
    return vertexLabels_.size();
}

std::size_t htd::GraphLabeling::edgeLabelCount(void) const
{
    return edgeLabels_.size();
}

bool htd::GraphLabeling::isLabeledVertex(htd::vertex_t vertex) const
{
    return vertexLabels_.find(vertex) != vertexLabels_.end();
}

bool htd::GraphLabeling::isLabeledEdge(htd::id_t edgeId) const
{
    return edgeLabels_.find(edgeId) != edgeLabels_.end();
}

const htd::ILabel & htd::GraphLabeling::vertexLabel(htd::vertex_t vertex) const
{
    auto label = vertexLabels_.find(vertex);

    HTD_ASSERT(label != vertexLabels_.end())

    return *(label->second);
}

const htd::ILabel & htd::GraphLabeling::edgeLabel(htd::id_t edgeId) const
{
    auto label = edgeLabels_.find(edgeId);

    HTD_ASSERT(label != edgeLabels_.end())

    return *(label->second);
}

void htd::GraphLabeling::setVertexLabel(htd::vertex_t vertex, htd::ILabel * label)
{
    auto position = vertexLabels_.find(vertex);

    if (position != vertexLabels_.end())
    {
        if (!(*(position->second) == *label))
        {
            delete position->second;
        }
    }

    vertexLabels_[vertex] = label;
}

void htd::GraphLabeling::setEdgeLabel(htd::id_t edgeId, htd::ILabel * label)
{
    auto position = edgeLabels_.find(edgeId);

    if (position != edgeLabels_.end())
    {
        if (!(*(position->second) == *label))
        {
            delete position->second;
        }
    }

    edgeLabels_[edgeId] = label;
}

void htd::GraphLabeling::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    auto position1 = vertexLabels_.find(vertex1);
    auto position2 = vertexLabels_.find(vertex2);

    HTD_ASSERT(position1 != vertexLabels_.end())
    HTD_ASSERT(position2 != vertexLabels_.end())

    htd::ILabel * label1 = position1->second;

    position1->second = position2->second;

    position2->second = label1;
}

void htd::GraphLabeling::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    auto position1 = edgeLabels_.find(edgeId1);
    auto position2 = edgeLabels_.find(edgeId2);

    HTD_ASSERT(position1 != edgeLabels_.end())
    HTD_ASSERT(position2 != edgeLabels_.end())

    htd::ILabel * label1 = position1->second;

    position1->second = position2->second;

    position2->second = label1;
}

htd::ILabel * htd::GraphLabeling::transferVertexLabel(htd::vertex_t vertex)
{
    auto position = vertexLabels_.find(vertex);

    HTD_ASSERT(position != vertexLabels_.end())

    htd::ILabel * ret = position->second;

    vertexLabels_.erase(vertex);

    return ret;
}

htd::ILabel * htd::GraphLabeling::transferEdgeLabel(htd::id_t edgeId)
{
    auto position = edgeLabels_.find(edgeId);

    HTD_ASSERT(position != edgeLabels_.end())

    htd::ILabel * ret = position->second;

    edgeLabels_.erase(edgeId);

    return ret;
}

void htd::GraphLabeling::removeVertexLabel(htd::vertex_t vertex)
{
    auto position = vertexLabels_.find(vertex);

    if (position != vertexLabels_.end())
    {
        delete position->second;

        vertexLabels_.erase(position);
    }
}

void htd::GraphLabeling::removeEdgeLabel(htd::id_t edgeId)
{
    auto position = edgeLabels_.find(edgeId);

    if (position != edgeLabels_.end())
    {
        delete position->second;

        edgeLabels_.erase(position);
    }
}

void htd::GraphLabeling::clear(void)
{
    for (auto & label : vertexLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;
        }
    }

    for (auto & label : edgeLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;
        }
    }

    vertexLabels_.clear();

    edgeLabels_.clear();
}

htd::GraphLabeling * htd::GraphLabeling::clone(void) const
{
    GraphLabeling * ret = new GraphLabeling();

    for (auto label : vertexLabels_)
    {
        ret->setVertexLabel(label.first, label.second->clone());
    }

    for (auto label : edgeLabels_)
    {
        ret->setEdgeLabel(label.first, label.second->clone());
    }

    return ret;
}

#endif /* HTD_HTD_GRAPHLABELING_CPP */
