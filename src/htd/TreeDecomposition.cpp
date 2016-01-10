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

#include <algorithm>
#include <stdexcept>

htd::TreeDecomposition::TreeDecomposition(void) : htd::LabeledTree::LabeledTree()
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::TreeDecomposition & original) : htd::LabeledTree::LabeledTree(original)
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::ITree & original) : htd::LabeledTree::LabeledTree(original)
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::ILabeledTree & original) : htd::LabeledTree::LabeledTree(original)
{

}

htd::TreeDecomposition::TreeDecomposition(const htd::ITreeDecomposition & original) : htd::LabeledTree::LabeledTree(original)
{

}

htd::TreeDecomposition::~TreeDecomposition()
{

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

htd::vertex_t htd::TreeDecomposition::joinNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & joinNodeCollection = joinNodes();

    if (index >= joinNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::joinNode(htd::index_t) const");
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);

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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end()))
        {
            result.push_back(node);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::forgetNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = forgetNodes();

    if (index >= forgetNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgetNode(htd::index_t) const");
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);

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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(node, childBagContent);

        if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end()))
        {
            result.push_back(node);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::introduceNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = introduceNodes();

    if (index >= introduceNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introduceNode(htd::index_t) const");
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

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
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = bagContent(vertex).size();
    }
    else
    {
        throw std::logic_error("std::size_t htd::TreeDecomposition::bagSize(htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::bagContent(htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        if (isLabeledVertex(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex))
        {
            auto & bagLabel = dynamic_cast<const htd::Label<htd::ConstCollection<htd::vertex_t>> *>(&(vertexLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex)))->value();

            return htd::ConstCollection<htd::vertex_t>(bagLabel);
        }
        else
        {
            return htd::ConstCollection<htd::vertex_t>();
        }
    }
    else
    {
        throw std::logic_error("const htd::Collection<htd::vertex_t> htd::TreeDecomposition::bagContent(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>();
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, const htd::vertex_container & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, const htd::vertex_container &)");
    }
}

void htd::TreeDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::TreeDecomposition::setBagContent(htd::vertex_t, const htd::IConstCollection<htd::vertex_t> &)");
    }
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::compute_set_difference_size(childBagContent.begin(), childBagContent.end(), bag.begin(), bag.end());
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

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

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::forgottenVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::compute_set_difference_size(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end());
    }

    return ret;
}

std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

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

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::introducedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
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
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        htd::vertex_container childBagContent;

        getChildrenVertexLabelSetUnion(vertex, childBagContent);

        ret = htd::compute_set_intersection_size(bag.begin(), bag.end(), childBagContent.begin(), childBagContent.end());
    }

    return ret;
}

std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

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

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);

        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TreeDecomposition::rememberedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

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
        for (auto child : children(vertex))
        {
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

            std::copy(childBag.begin(), childBag.end(), std::back_inserter(output));
        }

        std::sort(output.begin(), output.end());

        output.erase(std::unique(output.begin(), output.end()), output.end());
    }
}

htd::TreeDecomposition * htd::TreeDecomposition::clone(void) const
{
    return new TreeDecomposition(*this);
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::TreeDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ILabeledTree & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);
    }

    return *this;
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::ITreeDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledTree::operator=(original);
    }

    return *this;
}

#endif /* HTD_HTD_TREEDECOMPOSITION_CPP */
