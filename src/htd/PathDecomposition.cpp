/* 
 * File:   PathDecomposition.cpp
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

#ifndef HTD_HTD_PATHDECOMPOSITION_CPP
#define	HTD_HTD_PATHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/PathDecomposition.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/Label.hpp>

#include <algorithm>
#include <stdexcept>

htd::PathDecomposition::PathDecomposition(void) : htd::LabeledPath::LabeledPath()
{

}

htd::PathDecomposition::PathDecomposition(const htd::PathDecomposition & original) : htd::LabeledPath::LabeledPath(original)
{

}

htd::PathDecomposition::PathDecomposition(const htd::IPath & original) : htd::LabeledPath::LabeledPath(original)
{

}

htd::PathDecomposition::PathDecomposition(const htd::ILabeledPath & original) : htd::LabeledPath::LabeledPath(original)
{

}

htd::PathDecomposition::PathDecomposition(const htd::IPathDecomposition & original) : htd::LabeledPath::LabeledPath(original)
{

}

htd::PathDecomposition::~PathDecomposition()
{

}

std::size_t htd::PathDecomposition::joinNodeCount(void) const
{
    return 0;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::joinNodes(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>());
}

htd::vertex_t htd::PathDecomposition::joinNode(htd::index_t index) const
{
    HTD_UNUSED(index)

    throw std::out_of_range("htd::vertex_t htd::PathDecomposition::joinNode(htd::index_t) const");
}

bool htd::PathDecomposition::isJoinNode(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::out_of_range("bool htd::PathDecomposition::isJoinNode(htd::vertex_t) const");
    }

    return false;
}

std::size_t htd::PathDecomposition::forgetNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(node));

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

    auto & result = ret.container();

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
            {
                result.push_back(node);
            }
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PathDecomposition::forgetNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = forgetNodes();

    if (index >= forgetNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::forgetNode(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgetNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isForgetNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        if (childCount(vertex) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

            ret = htd::has_non_empty_set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end());
        }
    }
    else
    {
        throw std::out_of_range("bool htd::PathDecomposition::isForgetNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::PathDecomposition::introduceNodeCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
            {
                ret++;
            }
        }
    }

    return ret;;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introduceNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t node : vertices())
    {
        if (childCount(node) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(node);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(node));

            if (htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
            {
                result.push_back(node);
            }
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PathDecomposition::introduceNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introduceNodeCollection = introduceNodes();

    if (index >= introduceNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::introduceNode(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introduceNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PathDecomposition::isIntroduceNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        if (childCount(vertex) > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
            const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

            ret = htd::has_non_empty_set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end());
        }
    }
    else
    {
        throw std::out_of_range("bool htd::PathDecomposition::isIntroduceNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::PathDecomposition::bagSize(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = bagContent(vertex).size();
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::bagSize(htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::bagContent(htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        if (isLabeledVertex(htd::IPathDecomposition::BAG_LABEL_IDENTIFIER, vertex))
        {
            auto & bagLabel = dynamic_cast<const htd::Label<htd::ConstCollection<htd::vertex_t>> *>(&(vertexLabel(htd::IPathDecomposition::BAG_LABEL_IDENTIFIER, vertex)))->value();

            return htd::ConstCollection<htd::vertex_t>(bagLabel);
        }
        else
        {
            return htd::ConstCollection<htd::vertex_t>();
        }
    }
    else
    {
        throw std::logic_error("const htd::Collection<htd::vertex_t> htd::PathDecomposition::bagContent(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>();
}

void htd::PathDecomposition::setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IPathDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::PathDecomposition::setBagContent(htd::vertex_t, const std::vector<htd::vertex_t> &)");
    }
}

void htd::PathDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IPathDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::PathDecomposition::setBagContent(htd::vertex_t, const htd::IConstCollection<htd::vertex_t> &)");
    }
}

std::size_t htd::PathDecomposition::minimumBagSize(void) const
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

std::size_t htd::PathDecomposition::maximumBagSize(void) const
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

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::compute_set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_difference_size(childBag.begin(), childBag.end(), bag.begin(), bag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(childBag.begin(), childBag.end(), bag.begin(), bag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = forgottenVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = forgottenVertices(vertex, child);

    if (index >= forgottenVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

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
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::compute_set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_difference_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_difference(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

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
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        ret = htd::compute_set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        ret = htd::compute_set_intersection_size(bag.begin(), bag.end(), childBag.begin(), childBag.end());
    }
    else
    {
        throw std::logic_error("std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child(vertex));

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex) && isChild(vertex, child))
    {
        const htd::ConstCollection<htd::vertex_t> & bag = bagContent(vertex);
        const htd::ConstCollection<htd::vertex_t> & childBag = bagContent(child);

        std::set_intersection(bag.begin(), bag.end(), childBag.begin(), childBag.end(), std::back_inserter(result));
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t, htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t, htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    const htd::ConstCollection<htd::vertex_t> & introducedVertexCollection = introducedVertices(vertex, child);

    if (index >= introducedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = introducedVertexCollection.begin();

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
    return new PathDecomposition(*this);
}

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

#endif /* HTD_HTD_PATHDECOMPOSITION_CPP */
