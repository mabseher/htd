/*
 * File:   PreprocessedGraph.cpp
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

#ifndef HTD_HTD_PREPROCESSEDGRAPH_CPP
#define HTD_HTD_PREPROCESSEDGRAPH_CPP

#include <htd/Helpers.hpp>

#include <htd/PreprocessedGraph.hpp>

#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stack>
#include <unordered_set>
#include <vector>

/**
 *  Private implementation details of class htd::PreprocessedGraph.
 */
struct htd::PreprocessedGraph::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] vertexNames          The actual identifiers of the vertices.
     *  @param[in] neighborhood         A vector containing the neighborhood of each of the vertices.
     *  @param[in] eliminationSequence  A partial vertex elimination ordering computed during the preprocessing phase.
     *  @param[in] remainingVertices    The set of vertices which were not eliminated during the preprocessing phase.
     *  @param[in] inputGraphEdgeCount  The number of edges in the input graph.
     *  @param[in] minTreeWidth         The lower bound for the treewidth of the original input graph.
     */
    Implementation(std::vector<htd::vertex_t> && vertexNames,
                   std::vector<std::vector<htd::vertex_t>> && neighborhood,
                   std::vector<htd::vertex_t> && eliminationSequence,
                   std::vector<htd::vertex_t> && remainingVertices,
                   std::size_t inputGraphEdgeCount,
                   std::size_t minTreeWidth)
        : names_(std::move(vertexNames)), neighborhood_(std::move(neighborhood)), eliminationSequence_(std::move(eliminationSequence)), remainingVertices_(std::move(remainingVertices)), minTreeWidth_(minTreeWidth), edgeCount_(0), inputGraphEdgeCount_(inputGraphEdgeCount)
    {
        updateEdgeCount();
    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original)
        : names_(original.names_), neighborhood_(original.neighborhood_), eliminationSequence_(original.eliminationSequence_), remainingVertices_(original.remainingVertices_), minTreeWidth_(original.minTreeWidth_), edgeCount_(original.edgeCount_), inputGraphEdgeCount_(original.inputGraphEdgeCount_)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The actual identifiers of the vertices.
     */
    std::vector<htd::vertex_t> names_;

    /**
     *  A vector containing the neighborhood of each of the vertices.
     */
    std::vector<std::vector<htd::vertex_t>> neighborhood_;

    /**
     *  A partial vertex elimination ordering computed during the preprocessing phase.
     */
    std::vector<htd::vertex_t> eliminationSequence_;

    /**
     *  The set of vertices which were not eliminated during the preprocessing phase.
     */
    std::vector<htd::vertex_t> remainingVertices_;

    /**
     *  The lower bound of the treewidth of the input graph.
     */
    std::size_t minTreeWidth_;

    /**
     *  The number of edges in the preprocessed graph.
     */
    std::size_t edgeCount_;

    /**
     *  The number of edges in the input graph.
     */
    std::size_t inputGraphEdgeCount_;

    /**
     *  Recompute the number of edges in the graph to update the result of the function edgeCount().
     */
    void updateEdgeCount(void)
    {
        edgeCount_ = 0;

        for (htd::vertex_t vertex : remainingVertices_)
        {
            edgeCount_ += neighborhood_[vertex].size();
        }

        edgeCount_ = edgeCount_ >> 1;
    }
};

htd::PreprocessedGraph::PreprocessedGraph(std::vector<htd::vertex_t> && vertexNames,
                                          std::vector<std::vector<htd::vertex_t>> && neighborhood,
                                          std::vector<htd::vertex_t> && eliminationSequence,
                                          std::vector<htd::vertex_t> && remainingVertices,
                                          std::size_t inputGraphEdgeCount,
                                          std::size_t minTreeWidth)
    : implementation_(new Implementation(std::move(vertexNames),
                                         std::move(neighborhood),
                                         std::move(eliminationSequence),
                                         std::move(remainingVertices),
                                         inputGraphEdgeCount,
                                         minTreeWidth))
{

}

htd::PreprocessedGraph::PreprocessedGraph(const htd::PreprocessedGraph & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::PreprocessedGraph::~PreprocessedGraph()
{

}

std::size_t htd::PreprocessedGraph::vertexCount(void) const HTD_NOEXCEPT
{
    return implementation_->remainingVertices_.size();
}

std::size_t htd::PreprocessedGraph::inputGraphVertexCount(void) const HTD_NOEXCEPT
{
    return implementation_->names_.size();
}

std::size_t htd::PreprocessedGraph::edgeCount(void) const HTD_NOEXCEPT
{
    return implementation_->edgeCount_;
}

std::size_t htd::PreprocessedGraph::edgeCount(htd::vertex_t vertex) const
{
    return neighborCount(vertex);
}

std::size_t htd::PreprocessedGraph::inputGraphEdgeCount(void) const HTD_NOEXCEPT
{
    return implementation_->inputGraphEdgeCount_;
}

htd::ConstCollection<htd::vertex_t> htd::PreprocessedGraph::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->remainingVertices_);
}

void htd::PreprocessedGraph::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    target.insert(target.end(),
                  implementation_->remainingVertices_.begin(),
                  implementation_->remainingVertices_.end());
}

htd::vertex_t htd::PreprocessedGraph::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->remainingVertices_.size())

    return implementation_->remainingVertices_[index];
}

bool htd::PreprocessedGraph::isVertex(htd::vertex_t vertex) const
{
    return std::binary_search(implementation_->remainingVertices_.begin(),
                              implementation_->remainingVertices_.end(),
                              vertex);
}

std::size_t htd::PreprocessedGraph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : implementation_->remainingVertices_)
    {
        if (implementation_->neighborhood_[vertex].empty())
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::PreprocessedGraph::isolatedVertices(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t vertex : implementation_->remainingVertices_)
    {
        if (implementation_->neighborhood_[vertex].empty())
        {
            result.push_back(vertex);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::PreprocessedGraph::isolatedVertexAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

    HTD_ASSERT(index < isolatedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = isolatedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::PreprocessedGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->neighborhood_[vertex].empty();
}

std::size_t htd::PreprocessedGraph::neighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->neighborhood_[vertex].size();
}

htd::ConstCollection<htd::vertex_t> htd::PreprocessedGraph::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->neighborhood_[vertex]);
}

void htd::PreprocessedGraph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    target.insert(target.end(), currentNeighborhood.begin(), currentNeighborhood.end());
}

htd::vertex_t htd::PreprocessedGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    HTD_ASSERT(index < currentNeighborhood.size())

    return currentNeighborhood[index];
}

bool htd::PreprocessedGraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    return std::binary_search(currentNeighborhood.begin(), currentNeighborhood.end(), neighbor);
}

bool htd::PreprocessedGraph::isConnected(void) const
{
    bool ret = true;

    if (!(implementation_->remainingVertices_.empty()))
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = implementation_->remainingVertices_[0];

        originStack.push(currentVertex);

        while (!originStack.empty())
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : implementation_->neighborhood_[currentVertex])
                {
                    if (visitedVertices.count(neighbor) == 0)
                    {
                        originStack.push(neighbor);
                    }
                }
            }
            else
            {
                originStack.pop();
            }
        }

        ret = visitedVertices.size() == implementation_->remainingVertices_.size();
    }
    else
    {
        ret = true;
    }

    return ret;
}

bool htd::PreprocessedGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

    bool ret = false;

    if (vertex1 == vertex2)
    {
        ret = true;
    }
    else
    {
        std::vector<htd::vertex_t> newVertices;
        std::vector<htd::vertex_t> tmpVertices;

        std::vector<bool> reachableVertices(implementation_->remainingVertices_.size());

        reachableVertices[vertex1] = true;

        newVertices.push_back(vertex1);

        while (!ret && !newVertices.empty())
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (auto it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
            {
                const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[*it];

                for (auto it2 = currentNeighborhood.begin(); !ret && it2 != currentNeighborhood.end(); ++it2)
                {
                    htd::vertex_t neighbor = *it2;

                    if (!reachableVertices[neighbor])
                    {
                        reachableVertices[neighbor] = true;

                        newVertices.push_back(neighbor);

                        if (neighbor == vertex2)
                        {
                            ret = true;
                        }
                    }
                }
            }
        }
    }

    return ret;
}

void htd::PreprocessedGraph::removeVertex(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex));

    std::vector<htd::vertex_t> & selectedNeighborhood = implementation_->neighborhood_[vertex];

    implementation_->edgeCount_ -= selectedNeighborhood.size();

    for (htd::vertex_t neighbor : selectedNeighborhood)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[neighbor];

        /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'currentNeighborhood'. */
        // coverity[use_iterator]
        currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex));
    }

    implementation_->remainingVertices_.erase(std::lower_bound(implementation_->remainingVertices_.begin(),
                                                               implementation_->remainingVertices_.end(),
                                                               vertex));

    std::vector<htd::vertex_t>().swap(selectedNeighborhood);
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::vertexNames(void) const HTD_NOEXCEPT
{
    return implementation_->names_;
}

htd::vertex_t htd::PreprocessedGraph::vertexName(htd::vertex_t vertex) const
{
    HTD_ASSERT(vertex < implementation_->names_.size());

    return implementation_->names_[vertex];
}

std::vector<std::vector<htd::vertex_t>> & htd::PreprocessedGraph::neighborhood(void) HTD_NOEXCEPT
{
    return implementation_->neighborhood_;
}

const std::vector<std::vector<htd::vertex_t>> & htd::PreprocessedGraph::neighborhood(void) const HTD_NOEXCEPT
{
    return implementation_->neighborhood_;
}

std::vector<htd::vertex_t> & htd::PreprocessedGraph::neighborhood(htd::vertex_t vertex)
{
    HTD_ASSERT(vertex < implementation_->names_.size());

    return implementation_->neighborhood_[vertex];
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::neighborhood(htd::vertex_t vertex) const
{
    HTD_ASSERT(vertex < implementation_->names_.size());

    return implementation_->neighborhood_[vertex];
}

void htd::PreprocessedGraph::updateEdgeCount(void)
{
    implementation_->updateEdgeCount();
}

std::vector<htd::vertex_t> & htd::PreprocessedGraph::eliminationSequence(void) HTD_NOEXCEPT
{
    return implementation_->eliminationSequence_;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::eliminationSequence(void) const HTD_NOEXCEPT
{
    return implementation_->eliminationSequence_;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::remainingVertices(void) const HTD_NOEXCEPT
{
    return implementation_->remainingVertices_;
}

void htd::PreprocessedGraph::setRemainingVertices(const std::vector<htd::vertex_t> & remainingVertices)
{
    implementation_->remainingVertices_ = remainingVertices;

    implementation_->updateEdgeCount();
}

void htd::PreprocessedGraph::setRemainingVertices(std::vector<htd::vertex_t> && remainingVertices)
{
    implementation_->remainingVertices_ = std::move(remainingVertices);

    implementation_->updateEdgeCount();
}

std::size_t & htd::PreprocessedGraph::minTreeWidth(void) HTD_NOEXCEPT
{
    return implementation_->minTreeWidth_;
}

std::size_t htd::PreprocessedGraph::minTreeWidth(void) const HTD_NOEXCEPT
{
    return implementation_->minTreeWidth_;
}

htd::PreprocessedGraph * htd::PreprocessedGraph::clone(void) const
{
    return new htd::PreprocessedGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraphStructure * htd::PreprocessedGraph::cloneGraphStructure(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_PREPROCESSEDGRAPH_CPP */
