/*
 * File:   BidirectionalGraphLabeling.cpp
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

#ifndef HTD_HTD_BIDIRECTIONALGRAPHLABELING_CPP
#define	HTD_HTD_BIDIRECTIONALGRAPHLABELING_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BidirectionalGraphLabeling.hpp>

#include <stdexcept>

htd::BidirectionalGraphLabeling::BidirectionalGraphLabeling(void) : vertexLabels_(), edgeLabels_(), vertexLabelsReverseMap_(), edgeLabelsReverseMap_()
{

}

htd::BidirectionalGraphLabeling::~BidirectionalGraphLabeling()
{
    clear();
}

std::size_t htd::BidirectionalGraphLabeling::vertexLabelCount(void) const
{
    return vertexLabels_.size();
}

std::size_t htd::BidirectionalGraphLabeling::edgeLabelCount(void) const
{
    return edgeLabels_.size();
}

bool htd::BidirectionalGraphLabeling::isLabeledVertex(htd::vertex_t vertex) const
{
    return vertexLabels_.find(vertex) != vertexLabels_.end();
}

bool htd::BidirectionalGraphLabeling::isLabeledEdge(htd::id_t edgeId) const
{
    return edgeLabels_.find(edgeId) != edgeLabels_.end();
}

const htd::ILabel & htd::BidirectionalGraphLabeling::vertexLabel(htd::vertex_t vertex) const
{
    return *(vertexLabels_.at(vertex));
}

const htd::ILabel & htd::BidirectionalGraphLabeling::edgeLabel(htd::id_t edgeId) const
{
    return *(edgeLabels_.at(edgeId));
}

void htd::BidirectionalGraphLabeling::setVertexLabel(htd::vertex_t vertex, htd::ILabel * label)
{
    if (vertexLabelsReverseMap_.find(label) == vertexLabelsReverseMap_.end())
    {
        auto position = vertexLabels_.find(vertex);

        if (position != vertexLabels_.end())
        {
            if (!(*(position->second) == *label))
            {
                auto position2 = vertexLabelsReverseMap_.find(position->second);

                if (position2 != vertexLabelsReverseMap_.end())
                {
                    vertexLabelsReverseMap_.erase(position2);
                }

                delete position->second;
            }
        }

        vertexLabels_[vertex] = label;
        vertexLabelsReverseMap_[label] = vertex;
    }
    else
    {
        throw std::logic_error("void htd::BidirectionalGraphLabeling::setVertexLabel(htd::vertex_t, htd::ILabel *)");
    }
}

void htd::BidirectionalGraphLabeling::setEdgeLabel(htd::id_t edgeId, htd::ILabel * label)
{
    if (edgeLabelsReverseMap_.find(label) == edgeLabelsReverseMap_.end())
    {
        auto position = edgeLabels_.find(edgeId);

        if (position != edgeLabels_.end())
        {
            if (!(*(position->second) == *label))
            {
                auto position2 = edgeLabelsReverseMap_.find(position->second);

                if (position2 != edgeLabelsReverseMap_.end())
                {
                    edgeLabelsReverseMap_.erase(position2);
                }

                delete position->second;
            }
        }

        edgeLabels_[edgeId] = label;
        edgeLabelsReverseMap_[label] = edgeId;
    }
    else
    {
        throw std::logic_error("void htd::BidirectionalGraphLabeling::setEdgeLabel(htd::id_t, htd::ILabel *)");
    }
}

void htd::BidirectionalGraphLabeling::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    auto position1 = vertexLabels_.find(vertex1);
    auto position2 = vertexLabels_.find(vertex2);

    if (position1 != vertexLabels_.end() && position2 != vertexLabels_.end())
    {
        auto label1 = position1->second;

        position1->second = position2->second;

        position2->second = label1;

        vertexLabelsReverseMap_[vertexLabels_[vertex1]] = vertex1;
        vertexLabelsReverseMap_[vertexLabels_[vertex2]] = vertex2;
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::swapVertexLabels(htd::vertex_t, htd::vertex_t)");
    }
}

void htd::BidirectionalGraphLabeling::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    auto position1 = edgeLabels_.find(edgeId1);
    auto position2 = edgeLabels_.find(edgeId2);

    if (position1 != edgeLabels_.end() && position2 != edgeLabels_.end())
    {
        auto label1 = position1->second;

        position1->second = position2->second;

        position2->second = label1;

        edgeLabelsReverseMap_[edgeLabels_[edgeId1]] = edgeId1;
        edgeLabelsReverseMap_[edgeLabels_[edgeId2]] = edgeId2;
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::swapEdgeLabels(htd::id_t, htd::id_t)");
    }
}

std::pair<htd::id_t, bool> htd::BidirectionalGraphLabeling::insertVertex(htd::ILabel * label, std::function<htd::vertex_t(void)> vertexCreationFunction)
{
    std::pair<htd::id_t, bool> ret(0, false);

    auto result = vertexLabelsReverseMap_.insert(std::make_pair(label, 0));

    if (result.second)
    {
        htd::vertex_t newVertex = vertexCreationFunction();

        ret.first = newVertex;

        ret.second = true;

        result.first->second = newVertex;

        vertexLabels_[newVertex] = label;
    }
    else
    {
        ret.first = result.first->second;
    }

    return ret;
}

htd::ILabel * htd::BidirectionalGraphLabeling::transferVertexLabel(htd::vertex_t vertex)
{
    auto position = vertexLabels_.find(vertex);

    if (position == vertexLabels_.end())
    {
        throw std::logic_error("htd::ILabel * htd::BidirectionalGraphLabeling::transferVertexLabel(htd::vertex_t)");
    }

    htd::ILabel * ret = position->second;

    vertexLabels_.erase(vertex);

    vertexLabelsReverseMap_.erase(ret);

    return ret;
}

htd::ILabel * htd::BidirectionalGraphLabeling::transferEdgeLabel(htd::id_t edgeId)
{
    auto position = edgeLabels_.find(edgeId);

    if (position == edgeLabels_.end())
    {
        throw std::logic_error("htd::ILabel * htd::BidirectionalGraphLabeling::transferEdgeLabel(htd::id_t)");
    }

    htd::ILabel * ret = position->second;

    edgeLabels_.erase(edgeId);

    edgeLabelsReverseMap_.erase(ret);

    return ret;
}

void htd::BidirectionalGraphLabeling::removeVertexLabel(htd::vertex_t vertex)
{
    auto position = vertexLabels_.find(vertex);

    if (position != vertexLabels_.end())
    {
        auto position2 = vertexLabelsReverseMap_.find(position->second);

        if (position2 != vertexLabelsReverseMap_.end())
        {
            vertexLabelsReverseMap_.erase(position2);
        }

        delete position->second;

        vertexLabels_.erase(position);
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::removeVertexLabel(htd::vertex_t)");
    }
}

void htd::BidirectionalGraphLabeling::removeEdgeLabel(htd::id_t edgeId)
{
    auto position = edgeLabels_.find(edgeId);

    if (position != edgeLabels_.end())
    {
        auto position2 = edgeLabelsReverseMap_.find(position->second);

        if (position2 != edgeLabelsReverseMap_.end())
        {
            edgeLabelsReverseMap_.erase(position2);
        }

        delete position->second;

        edgeLabels_.erase(position);
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::removeEdgeLabel(htd::id_t edgeId)");
    }
}

void htd::BidirectionalGraphLabeling::clear(void)
{
    for (auto & label : vertexLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;

            label.second = nullptr;
        }
    }

    for (auto & label : edgeLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;

            label.second = nullptr;
        }
    }

    vertexLabels_.clear();

    edgeLabels_.clear();

    vertexLabelsReverseMap_.clear();

    edgeLabelsReverseMap_.clear();
}

bool htd::BidirectionalGraphLabeling::isVertexLabel(const htd::ILabel & label) const
{
    return vertexLabelsReverseMap_.find(&label) != vertexLabelsReverseMap_.end();
}

bool htd::BidirectionalGraphLabeling::isEdgeLabel(const htd::ILabel & label) const
{
    return edgeLabelsReverseMap_.find(&label) != edgeLabelsReverseMap_.end();
}

htd::vertex_t htd::BidirectionalGraphLabeling::lookupVertex(const htd::ILabel & label) const
{
    return vertexLabelsReverseMap_.at(&label);
}

htd::id_t htd::BidirectionalGraphLabeling::lookupEdge(const htd::ILabel & label) const
{
    return edgeLabelsReverseMap_.at(&label);
}

htd::BidirectionalGraphLabeling * htd::BidirectionalGraphLabeling::clone(void) const
{
    BidirectionalGraphLabeling * ret = new BidirectionalGraphLabeling();

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

#endif /* HTD_HTD_BIDIRECTIONALGRAPHLABELING_CPP */
