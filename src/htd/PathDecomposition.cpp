/* 
 * File:   PathDecomposition.cpp
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

#ifndef HTD_HTD_PATHDECOMPOSITION_CPP
#define HTD_HTD_PATHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/PathDecomposition.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/Label.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <algorithm>
#include <stdexcept>

htd::PathDecomposition::PathDecomposition(const htd::LibraryInstance * const manager) : htd::LabeledPath::LabeledPath(manager), bagContent_(), inducedEdges_()
{

}

htd::PathDecomposition::PathDecomposition(const htd::PathDecomposition & original) : htd::LabeledPath::LabeledPath(original), bagContent_(original.bagContent_), inducedEdges_(original.inducedEdges_)
{

}

htd::PathDecomposition::PathDecomposition(const htd::IPath & original) : htd::LabeledPath::LabeledPath(original), bagContent_(), inducedEdges_()
{

}

htd::PathDecomposition::PathDecomposition(const htd::ILabeledPath & original) : htd::LabeledPath::LabeledPath(original), bagContent_(), inducedEdges_()
{

}

htd::PathDecomposition::PathDecomposition(const htd::IPathDecomposition & original) : htd::LabeledPath::LabeledPath(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = original.bagContent(vertex);
        inducedEdges_[vertex] = original.inducedHyperedges(vertex);
    }
}

htd::PathDecomposition::~PathDecomposition()
{

}

void htd::PathDecomposition::removeVertex(htd::vertex_t vertex)
{
    htd::Path::removeVertex(vertex);

    bagContent_.erase(vertex);

    inducedEdges_.erase(vertex);
}

void htd::PathDecomposition::removeSubpath(htd::vertex_t subpathRoot)
{
    HTD_ASSERT(isVertex(subpathRoot))

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        bagContent_.erase(vertex);

        inducedEdges_.erase(vertex);
    }, subpathRoot);

    htd::Path::removeSubpath(subpathRoot);
}

htd::vertex_t htd::PathDecomposition::insertRoot(void)
{
    bool inserted = vertexCount() == 0;

    htd::vertex_t ret = htd::Path::insertRoot();

    if (inserted)
    {
        bagContent_[ret] = std::vector<htd::vertex_t>();

        inducedEdges_[ret] = htd::FilteredHyperedgeCollection();
    }

    return ret;
}

htd::vertex_t htd::PathDecomposition::insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    bool inserted = vertexCount() == 0;

    htd::vertex_t ret = htd::Path::insertRoot();

    if (inserted)
    {
        bagContent_[ret] = bagContent;

        inducedEdges_[ret] = inducedEdges;
    }

    return ret;
}

htd::vertex_t htd::PathDecomposition::insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    bool inserted = vertexCount() == 0;

    htd::vertex_t ret = htd::Path::insertRoot();

    if (inserted)
    {
        bagContent_.emplace(ret, std::move(bagContent));

        inducedEdges_.emplace(ret, std::move(inducedEdges));
    }

    return ret;
}

htd::vertex_t htd::PathDecomposition::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Path::addChild(vertex);

    bagContent_[ret] = std::vector<htd::vertex_t>();

    inducedEdges_[ret] = htd::FilteredHyperedgeCollection();

    return ret;
}

htd::vertex_t htd::PathDecomposition::addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::Path::addChild(vertex);

    bagContent_[ret] = bagContent;

    inducedEdges_[ret] = inducedEdges;

    return ret;
}

htd::vertex_t htd::PathDecomposition::addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::Path::addChild(vertex);

    bagContent_[ret] = std::move(bagContent);

    inducedEdges_[ret] = std::move(inducedEdges);

    return ret;
}

htd::vertex_t htd::PathDecomposition::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Path::addParent(vertex);

    bagContent_[ret] = std::vector<htd::vertex_t>();

    inducedEdges_[ret] = htd::FilteredHyperedgeCollection();

    return ret;
}

htd::vertex_t htd::PathDecomposition::addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::Path::addParent(vertex);

    bagContent_[ret] = bagContent;

    inducedEdges_[ret] = inducedEdges;

    return ret;
}

htd::vertex_t htd::PathDecomposition::addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::Path::addParent(vertex);

    bagContent_[ret] = std::move(bagContent);

    inducedEdges_[ret] = std::move(inducedEdges);

    return ret;
}

void htd::PathDecomposition::removeChild(htd::vertex_t vertex)
{
    if (childCount(vertex) > 0)
    {
        htd::vertex_t childVertex = child(vertex);

        htd::Path::removeChild(vertex, childVertex);

        bagContent_.erase(childVertex);

        inducedEdges_.erase(childVertex);
    }
}

void htd::PathDecomposition::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    htd::Path::removeChild(vertex, child);

    bagContent_.erase(child);

    inducedEdges_.erase(child);
}

std::size_t htd::PathDecomposition::joinNodeCount(void) const
{
    return 0;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::joinNodes(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>());
}

void htd::PathDecomposition::copyJoinNodesTo(std::vector<htd::vertex_t> & target) const
{
    HTD_UNUSED(target)
}

htd::vertex_t htd::PathDecomposition::joinNodeAtPosition(htd::index_t index) const
{
    HTD_UNUSED(index)

    throw std::out_of_range("htd::vertex_t htd::PathDecomposition::joinNodeAtPosition(htd::index_t) const");
}

bool htd::PathDecomposition::isJoinNode(htd::vertex_t vertex) const
{
    HTD_UNUSED(vertex)

    HTD_ASSERT(isVertex(vertex))

    return false;
}

std::size_t htd::PathDecomposition::forgetNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertexVector())
    {
        if (childCount(node) > 0)
        {
            const std::vector<htd::vertex_t> & bag = bagContent(node);
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
            {
                ret++;
            }
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgetNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    copyForgetNodesTo(ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyForgetNodesTo(std::vector<htd::vertex_t> & target) const
{
    for (htd::vertex_t node : vertexVector())
    {
        if (childCount(node) > 0)
        {
            const std::vector<htd::vertex_t> & bag = bagContent(node);
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
            {
                target.push_back(node);
            }
        }
    }
}

htd::vertex_t htd::PathDecomposition::forgetNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = forgetNodes();

    HTD_ASSERT(index < forgetNodeCollection.size())

    htd::ConstIterator<htd::vertex_t> it = forgetNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isForgetNode(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    bool ret = false;

    if (childCount(vertex) > 0)
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::has_non_empty_set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }

    return ret;
}

std::size_t htd::PathDecomposition::introduceNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertexVector())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        if (!isLeaf(node))
        {
            const std::vector<htd::vertex_t> & bag = bagContent(node);
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
            {
                ++ret;
            }
        }
        else
        {
            if (!bag.empty())
            {
                ++ret;
            }
        }
    }

    return ret;;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introduceNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    copyIntroduceNodesTo(ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyIntroduceNodesTo(std::vector<htd::vertex_t> & target) const
{
    for (htd::vertex_t node : vertexVector())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        if (!isLeaf(node))
        {
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
            {
                target.push_back(node);
            }
        }
        else
        {
            if (!bag.empty())
            {
                target.push_back(node);
            }
        }
    }
}

htd::vertex_t htd::PathDecomposition::introduceNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = introduceNodes();

    HTD_ASSERT(index < introduceNodeCollection.size())

    htd::ConstIterator<htd::vertex_t> it = introduceNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isIntroduceNode(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    bool ret = false;

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        ret = !bag.empty();
    }

    return ret;
}

std::size_t htd::PathDecomposition::exchangeNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertexVector())
    {
        if (!isLeaf(node))
        {
            const std::vector<htd::vertex_t> & bag = bagContent(node);
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            std::pair<std::size_t, std::size_t> symmetricDifference = htd::symmetric_difference_sizes(bag, childBag);

            if (symmetricDifference.first > 0 && symmetricDifference.second > 0)
            {
                ret++;
            }
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::exchangeNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    copyExchangeNodesTo(ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyExchangeNodesTo(std::vector<htd::vertex_t> & target) const
{
    for (htd::vertex_t node : vertexVector())
    {
        if (!isLeaf(node))
        {
            const std::vector<htd::vertex_t> & bag = bagContent(node);
            const std::vector<htd::vertex_t> & childBag = bagContent(child(node));

            std::pair<std::size_t, std::size_t> symmetricDifference = htd::symmetric_difference_sizes(bag, childBag);

            if (symmetricDifference.first > 0 && symmetricDifference.second > 0)
            {
                target.push_back(node);
            }
        }
    }
}

htd::vertex_t htd::PathDecomposition::exchangeNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & exchangeNodeCollection = exchangeNodes();

    HTD_ASSERT(index < exchangeNodeCollection.size())

    htd::ConstIterator<htd::vertex_t> it = exchangeNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isExchangeNode(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    bool ret = false;

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::pair<std::size_t, std::size_t> symmetricDifference = htd::symmetric_difference_sizes(bag, childBag);

        ret = symmetricDifference.first > 0 && symmetricDifference.second > 0;
    }

    return ret;
}

std::size_t htd::PathDecomposition::bagSize(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex).size();
}

std::vector<htd::vertex_t> & htd::PathDecomposition::mutableBagContent(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex);
}

const std::vector<htd::vertex_t> & htd::PathDecomposition::bagContent(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return bagContent_.at(vertex);
}

htd::FilteredHyperedgeCollection & htd::PathDecomposition::mutableInducedHyperedges(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    return inducedEdges_.at(vertex);
}

const htd::FilteredHyperedgeCollection & htd::PathDecomposition::inducedHyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return inducedEdges_.at(vertex);
}

std::size_t htd::PathDecomposition::minimumBagSize(void) const
{
    bool start = true;

    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertexVector())
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

std::size_t htd::PathDecomposition::maximumBagSize(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertexVector())
    {
        std::size_t currentBagSize = bagSize(vertex);

        if (currentBagSize > ret)
        {
            ret = currentBagSize;
        }
    }

    return ret;
}

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t ret = 0;

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }

    return ret;
}

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    return htd::set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    if (!isLeaf(vertex))
    {
        auto & result = ret.container();

        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(target));
    }
}

void htd::PathDecomposition::copyForgottenVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(target));
}

htd::vertex_t htd::PathDecomposition::forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    HTD_ASSERT(index < forgottenVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    HTD_ASSERT(index < forgottenVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    return std::binary_search(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), forgottenVertex);
}

bool htd::PathDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    return std::binary_search(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), forgottenVertex);
}

std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t ret = 0;

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        ret += bag.size();
    }

    return ret;
}

std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    return htd::set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        result.insert(result.end(), bag.begin(), bag.end());
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);

    if (!isLeaf(vertex))
    {
        const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
    }
    else
    {
        std::copy(bag.begin(), bag.end(), std::back_inserter(target));
    }
}

void htd::PathDecomposition::copyIntroducedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
}

htd::vertex_t htd::PathDecomposition::introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    HTD_ASSERT(index < introducedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    HTD_ASSERT(index < introducedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    return std::binary_search(introducedVertexCollection.begin(), introducedVertexCollection.end(), introducedVertex);
}

bool htd::PathDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    return std::binary_search(introducedVertexCollection.begin(), introducedVertexCollection.end(), introducedVertex);
}

std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

    return htd::set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
}

std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    return htd::set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

    std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::PathDecomposition::copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex));

    std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
}

void htd::PathDecomposition::copyRememberedVerticesTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isChild(vertex, child))

    const std::vector<htd::vertex_t> & bag = bagContent(vertex);
    const std::vector<htd::vertex_t> & childBag = bagContent(child);

    std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
}

htd::vertex_t htd::PathDecomposition::rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex);

    HTD_ASSERT(index < rememberedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = rememberedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex, child);

    HTD_ASSERT(index < rememberedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = rememberedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex);

    return std::binary_search(rememberedVertexCollection.begin(), rememberedVertexCollection.end(), rememberedVertex);
}

bool htd::PathDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex, child);

    return std::binary_search(rememberedVertexCollection.begin(), rememberedVertexCollection.end(), rememberedVertex);
}

htd::PathDecomposition * htd::PathDecomposition::clone(void) const
{
    return new htd::PathDecomposition(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IPath * htd::PathDecomposition::clonePath(void) const
{
    return clone();
}

htd::ITree * htd::PathDecomposition::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::PathDecomposition::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::PathDecomposition::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::PathDecomposition::cloneHypergraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::PathDecomposition::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledPath * htd::PathDecomposition::cloneLabeledPath(void) const
{
    return clone();
}

htd::ILabeledTree * htd::PathDecomposition::cloneLabeledTree(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::PathDecomposition::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::PathDecomposition::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::PathDecomposition::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::PathDecomposition::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::IPathDecomposition * htd::PathDecomposition::clonePathDecomposition(void) const
{
    return clone();
}

htd::ITreeDecomposition * htd::PathDecomposition::cloneTreeDecomposition(void) const
{
    return clone();
}

htd::IGraphDecomposition * htd::PathDecomposition::cloneGraphDecomposition(void) const
{
    return clone();
}

htd::IMutablePath * htd::PathDecomposition::cloneMutablePath(void) const
{
    return clone();
}

htd::IMutableLabeledPath * htd::PathDecomposition::cloneMutableLabeledPath(void) const
{
    return clone();
}

htd::IMutablePathDecomposition * htd::PathDecomposition::cloneMutablePathDecomposition(void) const
{
    return clone();
}
#endif

htd::PathDecomposition & htd::PathDecomposition::operator=(const htd::PathDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledPath::operator=(original);
    }

    return *this;
}

htd::PathDecomposition & htd::PathDecomposition::operator=(const htd::IPath & original)
{
    if (this != &original)
    {
        htd::LabeledPath::operator=(original);
    }

    return *this;
}

htd::PathDecomposition & htd::PathDecomposition::operator=(const htd::ILabeledPath & original)
{
    if (this != &original)
    {
        htd::LabeledPath::operator=(original);
    }

    return *this;
}

htd::PathDecomposition & htd::PathDecomposition::operator=(const htd::IPathDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledPath::operator=(original);
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::PathDecomposition::assign(const htd::IPath & original)
{
    *this = original;
}

void htd::PathDecomposition::assign(const htd::ILabeledPath & original)
{
    *this = original;
}

void htd::PathDecomposition::assign(const htd::IPathDecomposition & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_PATHDECOMPOSITION_CPP */
