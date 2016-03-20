/* 
 * File:   TreeDecomposition.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITION_CPP
#define	HTD_HTD_TREEDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/Label.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <algorithm>
#include <stdexcept>

htd::TreeDecomposition::TreeDecomposition(void) : htd::LabeledTree::LabeledTree(), bagContent_(), inducedEdges_()
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::TreeDecomposition & original) : htd::LabeledTree::LabeledTree(original), bagContent_(original.bagContent_), inducedEdges_(original.inducedEdges_)
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::ITree & original) : htd::LabeledTree::LabeledTree(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = std::vector<htd::vertex_t>();

        inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
    }
}

htd::TreeDecomposition::TreeDecomposition(const htd::ILabeledTree & original) : htd::LabeledTree::LabeledTree(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = std::vector<htd::vertex_t>();

        inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
    }
}

htd::TreeDecomposition::TreeDecomposition(const htd::ITreeDecomposition & original) : htd::LabeledTree::LabeledTree(original), bagContent_(), inducedEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        bagContent_[vertex] = original.bagContent(vertex);

        inducedEdges_[vertex] = original.inducedHyperedges(vertex);
    }
}

htd::TreeDecomposition::~TreeDecomposition()
{

}

void htd::TreeDecomposition::removeVertex(htd::vertex_t vertex)
{
    htd::Tree::removeVertex(vertex);

    bagContent_.erase(vertex);

    inducedEdges_.erase(vertex);
}

void htd::TreeDecomposition::removeSubtree(htd::vertex_t subtreeRoot)
{
    if (!isVertex(subtreeRoot))
    {
        throw std::logic_error("void htd::TreeDecomposition::removeSubtree(htd::vertex_t)");
    }

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        bagContent_.erase(vertex);

        inducedEdges_.erase(vertex);
    }, subtreeRoot);

    htd::Tree::removeSubtree(subtreeRoot);
}

htd::vertex_t htd::TreeDecomposition::insertRoot(void)
{
    bool inserted = vertexCount() == 0;

    htd::vertex_t ret = htd::Tree::insertRoot();

    if (inserted)
    {
        bagContent_[ret] = std::vector<htd::vertex_t>();

        inducedEdges_[ret] = htd::FilteredHyperedgeCollection();
    }

    return ret;
}

void htd::TreeDecomposition::removeRoot(void)
{
    htd::Tree::removeRoot();

    bagContent_.clear();

    inducedEdges_.clear();
}

htd::vertex_t htd::TreeDecomposition::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Tree::addChild(vertex);

    bagContent_[ret] = std::vector<htd::vertex_t>();

    inducedEdges_[ret] = htd::FilteredHyperedgeCollection();

    return ret;
}

htd::vertex_t htd::TreeDecomposition::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Tree::addParent(vertex);

    bagContent_[ret] = std::vector<htd::vertex_t>();

    inducedEdges_[ret] = htd::FilteredHyperedgeCollection();

    return ret;
}

void htd::TreeDecomposition::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    htd::Tree::removeChild(vertex, child);

    bagContent_.erase(child);

    inducedEdges_.erase(child);
}

std::size_t htd::TreeDecomposition::joinNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 1)
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::joinNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 1)
        {
            result.push_back(node);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::joinNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & joinNodeCollection = joinNodes();

    if (index >= joinNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::joinNodeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = joinNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isJoinNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = childCount(vertex) > 1;
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isJoinNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgetNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertices())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end()))
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgetNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t node : vertices())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end()))
        {
            result.push_back(node);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::forgetNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = forgetNodes();

    if (index >= forgetNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgetNodeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgetNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isForgetNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::has_non_empty_set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end());
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isForgetNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::introduceNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertices())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end()))
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introduceNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t node : vertices())
    {
        const std::vector<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end()))
        {
            result.push_back(node);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::introduceNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = introduceNodes();

    if (index >= introduceNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introduceNodeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introduceNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isIntroduceNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end());
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isIntroduceNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::bagSize(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::bagSize(htd::vertex_t) const");
    }

    return bagContent_.at(vertex).size();
}

const std::vector<htd::vertex_t> & htd::TreeDecomposition::bagContent(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("const std::vector<htd::vertex_t> & htd::TreeDecomposition::bagContent(htd::vertex_t) const");
    }

    return bagContent_.at(vertex);
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, const std::vector<htd::vertex_t> &)");
    }

    bagContent_[vertex] = content;
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, std::vector<htd::vertex_t> && content)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, std::vector<htd::vertex_t> &&)");
    }

    bagContent_[vertex] = std::move(content);
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, const htd::ConstCollection<htd::vertex_t> &)");
    }

    bagContent_[vertex] = std::vector<htd::vertex_t>(content.begin(), content.end());
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, htd::ConstCollection<htd::vertex_t> && content)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, htd::IConstCollection<htd::vertex_t> &&)");
    }

    bagContent_[vertex] = std::vector<htd::vertex_t>(content.begin(), content.end());
}

const htd::FilteredHyperedgeCollection & htd::TreeDecomposition::inducedHyperedges(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("const htd::FilteredHyperedgeCollection & htd::TreeDecomposition::inducedHyperedges(htd::vertex_t) const");
    }

    return inducedEdges_.at(vertex);
}

void htd::TreeDecomposition::setInducedHyperedges(htd::vertex_t vertex, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setInducedHyperedges(htd::vertex_t, const htd::FilteredHyperedgeCollection &)");
    }

    inducedEdges_[vertex] = inducedEdges;
}

void htd::TreeDecomposition::setInducedHyperedges(htd::vertex_t vertex, htd::FilteredHyperedgeCollection && inducedEdges)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::TreeDecomposition::setInducedHyperedges(htd::vertex_t, htd::FilteredHyperedgeCollection &&)");
    }

    inducedEdges_[vertex] = std::move(inducedEdges);
}

std::size_t htd::TreeDecomposition::minimumBagSize(void) const
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

std::size_t htd::TreeDecomposition::maximumBagSize(void) const
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

std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::set_difference_size(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::TreeDecomposition::copyForgottenVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyForgottenVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }
}

void htd::TreeDecomposition::copyForgottenVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const
{
    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyForgottenVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t, htd::vertex_t) const");
    }
}

htd::vertex_t htd::TreeDecomposition::forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertexAtPosition(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::forgottenVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertexAtPosition(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    return std::binary_search(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), forgottenVertex);
}

bool htd::TreeDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    return std::binary_search(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), forgottenVertex);
}

std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::set_difference_size(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::TreeDecomposition::copyIntroducedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyIntroducedVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }
}

void htd::TreeDecomposition::copyIntroducedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const
{
    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyIntroducedVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t, htd::vertex_t) const");
    }
}

htd::vertex_t htd::TreeDecomposition::introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertexAtPosition(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::introducedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertexAtPosition(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    return std::binary_search(introducedVertexCollection.begin(), introducedVertexCollection.end(), introducedVertex);
}

bool htd::TreeDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    return std::binary_search(introducedVertexCollection.begin(), introducedVertexCollection.end(), introducedVertex);
}

std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::set_intersection_size(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_intersection(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::TreeDecomposition::copyRememberedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        std::set_intersection(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyRememberedVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }
}

void htd::TreeDecomposition::copyRememberedVerticesTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex, htd::vertex_t child) const
{
    if (isVertex(vertex) && isChild(vertex, child))
    {
        const std::vector<htd::vertex_t> & bag = bagContent(vertex);
        const std::vector<htd::vertex_t> & childBag = bagContent(child);

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(target));
    }
    else
    {
        throw std::logic_error("std::vector<htd::vertex_t> htd::TreeDecomposition::copyRememberedVerticesTo(std::vector<htd::vertex_t> &, htd::vertex_t, htd::vertex_t) const");
    }
}

htd::vertex_t htd::TreeDecomposition::rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex);

    if (index >= rememberedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertexAtPosition(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = rememberedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::rememberedVertexAtPosition(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex, child);

    if (index >= rememberedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertexAtPosition(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = rememberedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::TreeDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex);

    return std::binary_search(rememberedVertexCollection.begin(), rememberedVertexCollection.end(), rememberedVertex);
}

bool htd::TreeDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = rememberedVertices(vertex, child);

    return std::binary_search(rememberedVertexCollection.begin(), rememberedVertexCollection.end(), rememberedVertex);
}

void htd::TreeDecomposition::getChildrenVertexLabelSetUnion(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        switch (nodes_.at(vertex)->children.size())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                const std::vector<htd::vertex_t> & childBag = bagContent(child(vertex, 0));

                std::copy(childBag.begin(), childBag.end(), std::back_inserter(output));

                break;
            }
            default:
            {
                for (auto child : children(vertex))
                {
                    const std::vector<htd::vertex_t> & childBag = bagContent(child);

                    std::copy(childBag.begin(), childBag.end(), std::back_inserter(output));
                }

                std::sort(output.begin(), output.end());

                output.erase(std::unique(output.begin(), output.end()), output.end());

                break;
            }
        }
    }
    else
    {
        throw std::logic_error("void htd::TreeDecomposition::getChildrenVertexLabelSetUnion(htd::vertex_t, htd::vertex_container &) const");
    }
}

htd::TreeDecomposition * htd::TreeDecomposition::clone(void) const
{
    return new htd::TreeDecomposition(*this);
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::TreeDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            bagContent_[vertex] = original.bagContent(vertex);

            inducedEdges_[vertex] = original.inducedHyperedges(vertex);
        }
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            bagContent_[vertex] = std::vector<htd::vertex_t>();

            inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
        }
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ILabeledTree & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            bagContent_[vertex] = std::vector<htd::vertex_t>();

            inducedEdges_[vertex] = htd::FilteredHyperedgeCollection();
        }
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ITreeDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            bagContent_[vertex] = original.bagContent(vertex);

            inducedEdges_[vertex] = original.inducedHyperedges(vertex);
        }
    }

    return *this;
}

#endif /* HTD_HTD_TREEDECOMPOSITION_CPP */
