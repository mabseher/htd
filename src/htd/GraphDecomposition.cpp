/* 
 * File:   GraphDecomposition.cpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITION_CPP
#define	HTD_HTD_GRAPHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphDecomposition.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>

htd::GraphDecomposition::GraphDecomposition(void) : htd::LabeledGraph::LabeledGraph(), bagContent_(), inducedEdges_()
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::GraphDecomposition & original) : htd::LabeledGraph::LabeledGraph(original), bagContent_(original.bagContent_), inducedEdges_(original.inducedEdges_)
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::IGraph & original) : htd::LabeledGraph::LabeledGraph(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = std::vector<htd::vertex_t>();
        inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
    }
}

htd::GraphDecomposition::GraphDecomposition(const htd::ILabeledGraph & original) : htd::LabeledGraph::LabeledGraph(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = std::vector<htd::vertex_t>();
        inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
    }
}

htd::GraphDecomposition::GraphDecomposition(const htd::IGraphDecomposition & original) : htd::LabeledGraph::LabeledGraph(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = original.bagContent(vertex);
        inducedEdges_[vertex] = original.inducedHyperedges(vertex);
    }
}

htd::GraphDecomposition::~GraphDecomposition()
{

}

htd::vertex_t htd::GraphDecomposition::addVertex(void)
{
    htd::vertex_t ret = htd::Graph::addVertex();

    bagContent_[ret] = std::vector<htd::vertex_t>();

    inducedEdges_[ret] = htd::FilteredHyperedgeCollection();

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::GraphDecomposition::addVertices(std::size_t count)
{
    const htd::ConstCollection<htd::vertex_t> & ret = htd::Graph::addVertices(count);

    auto it = ret.begin();

    for (htd::index_t index = 0; index < count; ++index)
    {
        bagContent_[*it] = std::vector<htd::vertex_t>();

        inducedEdges_[*it] = htd::FilteredHyperedgeCollection();

        ++it;
    }

    return ret;
}

void htd::GraphDecomposition::removeVertex(htd::vertex_t vertex)
{
    htd::Graph::removeVertex(vertex);

    bagContent_.erase(vertex);

    inducedEdges_.erase(vertex);
}

std::size_t htd::GraphDecomposition::bagSize(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("std::size_t htd::GraphDecomposition::bagSize(htd::vertex_t) const");
    }

    return bagContent_.at(vertex).size();
}

const std::vector<htd::vertex_t> & htd::GraphDecomposition::bagContent(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex);
}

void htd::GraphDecomposition::setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content)
{
    HTD_ASSERT(isVertex(vertex))

    std::vector<htd::vertex_t> & bag = bagContent_[vertex];

    bag = content;

    std::sort(bag.begin(), bag.end());

    bag.erase(std::unique(bag.begin(), bag.end()), bag.end());
}

void htd::GraphDecomposition::setBagContent(htd::vertex_t vertex, std::vector<htd::vertex_t> && content)
{
    HTD_ASSERT(isVertex(vertex))

    std::vector<htd::vertex_t> & bag = bagContent_[vertex];

    bag = std::move(content);

    std::sort(bag.begin(), bag.end());

    bag.erase(std::unique(bag.begin(), bag.end()), bag.end());
}

void htd::GraphDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    HTD_ASSERT(isVertex(vertex))

    std::vector<htd::vertex_t> & bag = bagContent_[vertex];

    bag = std::vector<htd::vertex_t>(content.begin(), content.end());

    std::sort(bag.begin(), bag.end());

    bag.erase(std::unique(bag.begin(), bag.end()), bag.end());
}

const htd::FilteredHyperedgeCollection & htd::GraphDecomposition::inducedHyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return inducedEdges_.at(vertex);
}

void htd::GraphDecomposition::setInducedHyperedges(htd::vertex_t vertex, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    HTD_ASSERT(isVertex(vertex))

    inducedEdges_[vertex] = inducedEdges;
}

void htd::GraphDecomposition::setInducedHyperedges(htd::vertex_t vertex, htd::FilteredHyperedgeCollection && inducedEdges)
{
    HTD_ASSERT(isVertex(vertex))

    inducedEdges_[vertex] = std::move(inducedEdges);
}

std::size_t htd::GraphDecomposition::minimumBagSize(void) const
{
    bool start = true;

    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentBagSize = bagSize(vertex);

        if (start || currentBagSize < ret)
        {
            ret = currentBagSize;

            start = false;
        }
    }

    return ret;
}

std::size_t htd::GraphDecomposition::maximumBagSize(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentBagSize = bagSize(vertex);

        if (currentBagSize > ret)
        {
            ret = currentBagSize;
        }
    }

    return ret;
}

htd::GraphDecomposition * htd::GraphDecomposition::clone(void) const
{
    return new GraphDecomposition(*this);
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::GraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

        auto it = vertices.begin();

        std::size_t count = vertices.size();

        for (htd::index_t index = 0; index < count; ++index)
        {
            bagContent_[*it] = original.bagContent_.at(*it);

            inducedEdges_[*it] = original.inducedEdges_.at(*it);

            ++it;
        }
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

        auto it = vertices.begin();

        std::size_t count = vertices.size();

        for (htd::index_t index = 0; index < count; ++index)
        {
            bagContent_[*it] = std::vector<htd::vertex_t>();

            inducedEdges_[*it] = htd::FilteredHyperedgeCollection();

            ++it;
        }
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IMultiGraph & original)
{
    htd::LabeledGraph::operator=(original);

    bagContent_.clear();
    inducedEdges_.clear();

    const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

    auto it = vertices.begin();

    std::size_t count = vertices.size();

    for (htd::index_t index = 0; index < count; ++index)
    {
        bagContent_[*it] = std::vector<htd::vertex_t>();

        inducedEdges_[*it] = htd::FilteredHyperedgeCollection();

        ++it;
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::ILabeledGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

        auto it = vertices.begin();

        std::size_t count = vertices.size();

        for (htd::index_t index = 0; index < count; ++index)
        {
            bagContent_[*it] = std::vector<htd::vertex_t>();

            inducedEdges_[*it] = htd::FilteredHyperedgeCollection();

            ++it;
        }
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::ILabeledMultiGraph & original)
{
    htd::LabeledGraph::operator=(original);

    bagContent_.clear();
    inducedEdges_.clear();

    const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

    auto it = vertices.begin();

    std::size_t count = vertices.size();

    for (htd::index_t index = 0; index < count; ++index)
    {
        bagContent_[*it] = std::vector<htd::vertex_t>();

        inducedEdges_[*it] = htd::FilteredHyperedgeCollection();

        ++it;
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IGraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::Graph::vertices();

        auto it = vertices.begin();

        std::size_t count = vertices.size();

        for (htd::index_t index = 0; index < count; ++index)
        {
            bagContent_[*it] = original.bagContent(*it);

            inducedEdges_[*it] = original.inducedHyperedges(*it);

            ++it;
        }
    }

    return *this;
}

#endif /* HTD_HTD_GRAPHDECOMPOSITION_CPP */
