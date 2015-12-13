/*
 * File:   BidirectionalGraphLabeling.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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
#include <htd/ILabel.hpp>

#include <stdexcept>

htd::BidirectionalGraphLabeling::BidirectionalGraphLabeling(void) : vertexLabels_(), hyperedgeLabels_(), vertexLabelsReverseMap_(), hyperedgeLabelsReverseMap_()
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

std::size_t htd::BidirectionalGraphLabeling::hyperedgeLabelCount(void) const
{
    return hyperedgeLabels_.size();
}

bool htd::BidirectionalGraphLabeling::hasLabel(htd::vertex_t vertex) const
{
    return vertexLabels_.find(vertex) != vertexLabels_.end();
}

bool htd::BidirectionalGraphLabeling::hasLabel(const htd::hyperedge_t & edge) const
{
    return hyperedgeLabels_.find(edge) != hyperedgeLabels_.end();
}

const htd::ILabel & htd::BidirectionalGraphLabeling::label(htd::vertex_t vertex) const
{
    return *(vertexLabels_.at(vertex));
}

const htd::ILabel & htd::BidirectionalGraphLabeling::label(const htd::hyperedge_t & edge) const
{
    return *(hyperedgeLabels_.at(edge));
}

void htd::BidirectionalGraphLabeling::setLabel(htd::vertex_t vertex, htd::ILabel * label)
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
        throw std::logic_error("void htd::BidirectionalGraphLabeling::setLabel(htd::vertex_t, htd::ILabel *)");
    }
}

void htd::BidirectionalGraphLabeling::setLabel(const htd::hyperedge_t & edge, htd::ILabel * label)
{
    if (hyperedgeLabelsReverseMap_.find(label) == hyperedgeLabelsReverseMap_.end())
    {
        auto position = hyperedgeLabels_.find(edge);

        if (position != hyperedgeLabels_.end())
        {
            if (!(*(position->second) == *label))
            {
                auto position2 = hyperedgeLabelsReverseMap_.find(position->second);

                if (position2 != hyperedgeLabelsReverseMap_.end())
                {
                    hyperedgeLabelsReverseMap_.erase(position2);
                }

                delete position->second;
            }
        }

        hyperedgeLabels_[edge] = label;
        hyperedgeLabelsReverseMap_[label] = edge;
    }
    else
    {
        throw std::logic_error("void htd::BidirectionalGraphLabeling::setLabel(const htd::hyperedge_t &, htd::ILabel *)");
    }
}

void htd::BidirectionalGraphLabeling::swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
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
        throw std::out_of_range("htd::BidirectionalGraphLabeling::swapLabels(htd::vertex_t, htd::vertex_t)");
    }
}

void htd::BidirectionalGraphLabeling::swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    auto position1 = hyperedgeLabels_.find(edge1);
    auto position2 = hyperedgeLabels_.find(edge2);

    if (position1 != hyperedgeLabels_.end() && position2 != hyperedgeLabels_.end())
    {
        auto label1 = position1->second;

        position1->second = position2->second;

        position2->second = label1;

        hyperedgeLabelsReverseMap_[hyperedgeLabels_[edge1]] = edge1;
        hyperedgeLabelsReverseMap_[hyperedgeLabels_[edge2]] = edge2;
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::swapLabels(const htd::hyperedge_t &, const htd::hyperedge_t &)");
    }
}

void htd::BidirectionalGraphLabeling::removeLabel(htd::vertex_t vertex)
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
        throw std::out_of_range("htd::BidirectionalGraphLabeling::removeLabel(htd::vertex_t)");
    }
}

void htd::BidirectionalGraphLabeling::removeLabel(const htd::hyperedge_t & edge)
{
    auto position = hyperedgeLabels_.find(edge);

    if (position != hyperedgeLabels_.end())
    {
        auto position2 = hyperedgeLabelsReverseMap_.find(position->second);

        if (position2 != hyperedgeLabelsReverseMap_.end())
        {
            hyperedgeLabelsReverseMap_.erase(position2);
        }

        delete position->second;

        hyperedgeLabels_.erase(position);
    }
    else
    {
        throw std::out_of_range("htd::BidirectionalGraphLabeling::removeLabel(const htd::hyperedge_t &)");
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

    for (auto & label : hyperedgeLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;

            label.second = nullptr;
        }
    }

    vertexLabels_.clear();

    hyperedgeLabels_.clear();

    vertexLabelsReverseMap_.clear();

    hyperedgeLabelsReverseMap_.clear();
}

bool htd::BidirectionalGraphLabeling::isVertexLabel(const htd::ILabel & label) const
{
    return vertexLabelsReverseMap_.find(&label) != vertexLabelsReverseMap_.end();
}

bool htd::BidirectionalGraphLabeling::isHyperedgeLabel(const htd::ILabel & label) const
{
    return hyperedgeLabelsReverseMap_.find(&label) != hyperedgeLabelsReverseMap_.end();
}

htd::vertex_t htd::BidirectionalGraphLabeling::lookupVertex(const htd::ILabel & label) const
{
    return vertexLabelsReverseMap_.at(&label);
}

const htd::hyperedge_t & htd::BidirectionalGraphLabeling::lookupHyperedge(const htd::ILabel & label) const
{
    return hyperedgeLabelsReverseMap_.at(&label);
}

htd::BidirectionalGraphLabeling * htd::BidirectionalGraphLabeling::clone(void) const
{
    BidirectionalGraphLabeling * ret = new BidirectionalGraphLabeling();

    for (auto label : vertexLabels_)
    {
        ret->setLabel(label.first, label.second->clone());
    }

    for (auto label : hyperedgeLabels_)
    {
        ret->setLabel(label.first, label.second->clone());
    }

    return ret;
}

#endif /* HTD_HTD_BIDIRECTIONALGRAPHLABELING_CPP */
