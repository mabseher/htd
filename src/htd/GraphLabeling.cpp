/*
 * File:   GraphLabeling.cpp
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

#ifndef HTD_HTD_GRAPHLABELING_CPP
#define	HTD_HTD_GRAPHLABELING_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabel.hpp>

#include <stdexcept>

htd::GraphLabeling::GraphLabeling(void) : vertexLabels_(), hyperedgeLabels_()
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

std::size_t htd::GraphLabeling::hyperedgeLabelCount(void) const
{
    return hyperedgeLabels_.size();
}

bool htd::GraphLabeling::hasLabel(htd::vertex_t vertex) const
{
    return vertexLabels_.find(vertex) != vertexLabels_.end();
}

bool htd::GraphLabeling::hasLabel(const htd::hyperedge_t & edge) const
{
    return hyperedgeLabels_.find(edge) != hyperedgeLabels_.end();
}

const htd::ILabel & htd::GraphLabeling::label(htd::vertex_t vertex) const
{
    return *(vertexLabels_.at(vertex));
}

const htd::ILabel & htd::GraphLabeling::label(const htd::hyperedge_t & edge) const
{
    return *(hyperedgeLabels_.at(edge));
}

void htd::GraphLabeling::setLabel(htd::vertex_t vertex, htd::ILabel * label)
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

void htd::GraphLabeling::setLabel(const htd::hyperedge_t & edge, htd::ILabel * label)
{
    auto position = hyperedgeLabels_.find(edge);

    if (position != hyperedgeLabels_.end())
    {
        if (!(*(position->second) == *label))
        {
            delete position->second;
        }
    }

    hyperedgeLabels_[edge] = label;
}

void htd::GraphLabeling::swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    auto position1 = vertexLabels_.find(vertex1);
    auto position2 = vertexLabels_.find(vertex2);

    if (position1 != vertexLabels_.end() && position2 != vertexLabels_.end())
    {
        auto label1 = position1->second;

        position1->second = position2->second;

        position2->second = label1;
    }
    else
    {
        throw std::out_of_range("htd::GraphLabeling::swapLabels(htd::vertex_t, htd::vertex_t)");
    }
}

void htd::GraphLabeling::swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    auto position1 = hyperedgeLabels_.find(edge1);
    auto position2 = hyperedgeLabels_.find(edge2);

    if (position1 != hyperedgeLabels_.end() && position2 != hyperedgeLabels_.end())
    {
        auto label1 = position1->second;

        position1->second = position2->second;

        position2->second = label1;
    }
    else
    {
        throw std::out_of_range("htd::GraphLabeling::swapLabels(const htd::hyperedge_t &, const htd::hyperedge_t &)");
    }
}

void htd::GraphLabeling::removeLabel(htd::vertex_t vertex)
{
    auto position = vertexLabels_.find(vertex);

    if (position != vertexLabels_.end())
    {
        delete position->second;

        vertexLabels_.erase(position);
    }
    else
    {
        throw std::out_of_range("htd::GraphLabeling::removeLabel(htd::vertex_t)");
    }
}

void htd::GraphLabeling::removeLabel(const htd::hyperedge_t & edge)
{
    auto position = hyperedgeLabels_.find(edge);

    if (position != hyperedgeLabels_.end())
    {
        delete position->second;

        hyperedgeLabels_.erase(position);
    }
    else
    {
        throw std::out_of_range("htd::GraphLabeling::removeLabel(const htd::hyperedge_t &)");
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

    for (auto & label : hyperedgeLabels_)
    {
        if (label.second != nullptr)
        {
            delete label.second;
        }
    }

    vertexLabels_.clear();

    hyperedgeLabels_.clear();
}

htd::GraphLabeling * htd::GraphLabeling::clone(void) const
{
    GraphLabeling * ret = new GraphLabeling();

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

#endif /* HTD_HTD_GRAPHLABELING_CPP */
