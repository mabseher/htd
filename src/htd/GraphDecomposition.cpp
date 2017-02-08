/* 
 * File:   GraphDecomposition.cpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITION_CPP
#define HTD_HTD_GRAPHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphDecomposition.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>

htd::GraphDecomposition::GraphDecomposition(const htd::LibraryInstance * const manager) : htd::LabeledMultiHypergraph::LabeledMultiHypergraph(manager), bagContent_(), inducedEdges_()
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::GraphDecomposition & original) : htd::LabeledMultiHypergraph::LabeledMultiHypergraph(original), bagContent_(original.bagContent_), inducedEdges_(original.inducedEdges_)
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::IMultiHypergraph & original) : htd::LabeledMultiHypergraph::LabeledMultiHypergraph(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_.emplace(vertex, std::vector<htd::vertex_t>());

        inducedEdges_.emplace(vertex, htd::FilteredHyperedgeCollection());
    }
}

htd::GraphDecomposition::GraphDecomposition(const htd::ILabeledMultiHypergraph & original) : htd::LabeledMultiHypergraph::LabeledMultiHypergraph(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_.emplace(vertex, std::vector<htd::vertex_t>());

        inducedEdges_.emplace(vertex, htd::FilteredHyperedgeCollection());
    }
}

htd::GraphDecomposition::GraphDecomposition(const htd::IGraphDecomposition & original) : htd::LabeledMultiHypergraph::LabeledMultiHypergraph(original), bagContent_(), inducedEdges_()
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
    htd::vertex_t ret = htd::LabeledMultiHypergraph::addVertex();

    bagContent_.emplace(ret, std::vector<htd::vertex_t>());

    inducedEdges_.emplace(ret, htd::FilteredHyperedgeCollection());

    return ret;
}

htd::vertex_t htd::GraphDecomposition::addVertex(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::LabeledMultiHypergraph::addVertex();

    bagContent_[ret] = bagContent;

    inducedEdges_[ret] = inducedEdges;

    return ret;
}

htd::vertex_t htd::GraphDecomposition::addVertex(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::LabeledMultiHypergraph::addVertex();

    bagContent_.emplace(ret, std::move(bagContent));

    inducedEdges_.emplace(ret, std::move(inducedEdges));

    return ret;
}

htd::vertex_t htd::GraphDecomposition::addVertices(std::size_t count)
{
    htd::vertex_t ret = htd::LabeledMultiHypergraph::addVertices(count);

    for (htd::index_t index = 0; index < count; ++index)
    {
        bagContent_.emplace(static_cast<htd::vertex_t>(ret + index), std::vector<htd::vertex_t>());

        inducedEdges_.emplace(static_cast<htd::vertex_t>(ret + index), htd::FilteredHyperedgeCollection());
    }

    return ret;
}

void htd::GraphDecomposition::removeVertex(htd::vertex_t vertex)
{
    htd::LabeledMultiHypergraph::removeVertex(vertex);

    bagContent_.erase(vertex);

    inducedEdges_.erase(vertex);
}

std::size_t htd::GraphDecomposition::bagSize(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex).size();
}

std::vector<htd::vertex_t> & htd::GraphDecomposition::mutableBagContent(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex);
}

const std::vector<htd::vertex_t> & htd::GraphDecomposition::bagContent(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex);
}

htd::FilteredHyperedgeCollection & htd::GraphDecomposition::mutableInducedHyperedges(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    return inducedEdges_.at(vertex);
}

const htd::FilteredHyperedgeCollection & htd::GraphDecomposition::inducedHyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return inducedEdges_.at(vertex);
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
    return new htd::GraphDecomposition(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiHypergraph * htd::GraphDecomposition::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::GraphDecomposition::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IGraphDecomposition * htd::GraphDecomposition::cloneGraphDecomposition(void) const
{
    return clone();
}

htd::IMutableMultiHypergraph * htd::GraphDecomposition::cloneMutableMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableLabeledMultiHypergraph * htd::GraphDecomposition::cloneMutableLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableGraphDecomposition * htd::GraphDecomposition::cloneMutableGraphDecomposition(void) const
{
    return clone();
}
#endif

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::GraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledMultiHypergraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::LabeledMultiHypergraph::vertices();

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

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::LabeledMultiHypergraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::LabeledMultiHypergraph::vertices();

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

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::ILabeledMultiHypergraph & original)
{
    if (this != &original)
    {
        htd::LabeledMultiHypergraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::LabeledMultiHypergraph::vertices();

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

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IGraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledMultiHypergraph::operator=(original);

        bagContent_.clear();
        inducedEdges_.clear();

        const htd::ConstCollection<htd::vertex_t> & vertices = htd::LabeledMultiHypergraph::vertices();

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

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::GraphDecomposition::assign(const htd::IMultiHypergraph & original)
{
    *this = original;
}

void htd::GraphDecomposition::assign(const htd::ILabeledMultiHypergraph & original)
{
    *this = original;
}

void htd::GraphDecomposition::assign(const htd::IGraphDecomposition & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_GRAPHDECOMPOSITION_CPP */
