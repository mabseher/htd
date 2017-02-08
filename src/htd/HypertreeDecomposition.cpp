/* 
 * File:   HypertreeDecomposition.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_CPP
#define HTD_HTD_HYPERTREEDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <algorithm>
#include <stdexcept>

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::LibraryInstance * const manager) : htd::TreeDecomposition(manager), coveringEdges_()
{
    
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::HypertreeDecomposition & original) : htd::TreeDecomposition(original), coveringEdges_(original.coveringEdges_)
{

}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::ITree & original) : htd::TreeDecomposition(original), coveringEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
    }
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::ILabeledTree & original) : htd::TreeDecomposition(original), coveringEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
    }
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::ITreeDecomposition & original) : htd::TreeDecomposition(original), coveringEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
    }
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::IHypertreeDecomposition & original) : htd::TreeDecomposition(original), coveringEdges_()
{
    for (htd::vertex_t vertex : original.vertices())
    {
        coveringEdges_[vertex] = original.coveringEdges(vertex);
    }
}

htd::HypertreeDecomposition::~HypertreeDecomposition()
{

}

void htd::HypertreeDecomposition::removeVertex(htd::vertex_t vertex)
{
    htd::TreeDecomposition::removeVertex(vertex);

    coveringEdges_.erase(vertex);
}

void htd::HypertreeDecomposition::removeSubtree(htd::vertex_t subtreeRoot)
{
    HTD_ASSERT(isVertex(subtreeRoot))

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        coveringEdges_.erase(vertex);
    }, subtreeRoot);

    htd::TreeDecomposition::removeSubtree(subtreeRoot);
}

htd::vertex_t htd::HypertreeDecomposition::insertRoot(void)
{
    htd::vertex_t ret = htd::TreeDecomposition::insertRoot();

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::insertRoot(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::insertRoot(bagContent, inducedEdges);

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::insertRoot(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::insertRoot(std::move(bagContent), std::move(inducedEdges));

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::TreeDecomposition::addChild(vertex);

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addChild(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::addChild(vertex, bagContent, inducedEdges);

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addChild(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::addChild(vertex, std::move(bagContent), std::move(inducedEdges));

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::TreeDecomposition::addParent(vertex);

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addParent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::addParent(vertex, bagContent, inducedEdges);

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

htd::vertex_t htd::HypertreeDecomposition::addParent(htd::vertex_t vertex, std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges)
{
    htd::vertex_t ret = htd::TreeDecomposition::addParent(vertex, std::move(bagContent), std::move(inducedEdges));

    coveringEdges_[ret] = std::vector<htd::Hyperedge>();

    return ret;
}

void htd::HypertreeDecomposition::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    htd::TreeDecomposition::removeChild(vertex, child);

    coveringEdges_.erase(child);
}

const std::vector<htd::Hyperedge> & htd::HypertreeDecomposition::coveringEdges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return coveringEdges_.at(vertex);
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const std::vector<htd::Hyperedge> & content)
{
    HTD_ASSERT(isVertex(vertex))

    coveringEdges_[vertex] = content;
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content)
{
    HTD_ASSERT(isVertex(vertex))

    std::vector<htd::Hyperedge> & coveringEdges = coveringEdges_[vertex];

    coveringEdges.clear();

    coveringEdges.insert(coveringEdges.end(), content.begin(), content.end());
}

std::size_t htd::HypertreeDecomposition::minimumCoveringEdgeAmount(void) const
{
    bool start = true;

    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentCoveringEdgeAmount = coveringEdges(vertex).size();

        if (start || currentCoveringEdgeAmount < ret)
        {
            ret = currentCoveringEdgeAmount;

            start = false;
        }
    }

    return ret;
}

std::size_t htd::HypertreeDecomposition::maximumCoveringEdgeAmount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentCoveringEdgeAmount = coveringEdges(vertex).size();

        if (currentCoveringEdgeAmount > ret)
        {
            ret = currentCoveringEdgeAmount;
        }
    }

    return ret;
}

htd::HypertreeDecomposition * htd::HypertreeDecomposition::clone(void) const
{
    return new htd::HypertreeDecomposition(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::ITree * htd::HypertreeDecomposition::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::HypertreeDecomposition::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::HypertreeDecomposition::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::HypertreeDecomposition::cloneHypergraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::HypertreeDecomposition::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::ILabeledTree * htd::HypertreeDecomposition::cloneLabeledTree(void) const
{
    return clone();
}

htd::ILabeledGraph * htd::HypertreeDecomposition::cloneLabeledGraph(void) const
{
    return clone();
}

htd::ILabeledMultiGraph * htd::HypertreeDecomposition::cloneLabeledMultiGraph(void) const
{
    return clone();
}

htd::ILabeledHypergraph * htd::HypertreeDecomposition::cloneLabeledHypergraph(void) const
{
    return clone();
}

htd::ILabeledMultiHypergraph * htd::HypertreeDecomposition::cloneLabeledMultiHypergraph(void) const
{
    return clone();
}

htd::ITreeDecomposition * htd::HypertreeDecomposition::cloneTreeDecomposition(void) const
{
    return clone();
}

htd::IGraphDecomposition * htd::HypertreeDecomposition::cloneGraphDecomposition(void) const
{
    return clone();
}

htd::IHypertreeDecomposition * htd::HypertreeDecomposition::cloneHypertreeDecomposition(void) const
{
    return clone();
}

htd::IMutableTree * htd::HypertreeDecomposition::cloneMutableTree(void) const
{
    return clone();
}

htd::IMutableLabeledTree * htd::HypertreeDecomposition::cloneMutableLabeledTree(void) const
{
    return clone();
}

htd::IMutableTreeDecomposition * htd::HypertreeDecomposition::cloneMutableTreeDecomposition(void) const
{
    return clone();
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecomposition::cloneMutableHypertreeDecomposition(void) const
{
    return clone();
}
#endif

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        coveringEdges_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ILabeledTree & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        coveringEdges_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITreeDecomposition & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        coveringEdges_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::IHypertreeDecomposition & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        coveringEdges_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = original.coveringEdges(vertex);
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::HypertreeDecomposition::assign(const htd::ITree & original)
{
    *this = original;
}

void htd::HypertreeDecomposition::assign(const htd::ILabeledTree & original)
{
    *this = original;
}

void htd::HypertreeDecomposition::assign(const htd::ITreeDecomposition & original)
{
    *this = original;
}

void htd::HypertreeDecomposition::assign(const htd::IHypertreeDecomposition & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_CPP */
