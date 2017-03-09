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
        for (htd::vertex_t vertex : remainingVertices_)
        {
            edgeCount_ += neighborhood_[vertex].size();
        }

        edgeCount_ = edgeCount_ >> 1;
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

std::size_t htd::PreprocessedGraph::inputGraphEdgeCount(void) const HTD_NOEXCEPT
{
    return implementation_->inputGraphEdgeCount_;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::vertexNames(void) const HTD_NOEXCEPT
{
    return implementation_->names_;
}

htd::vertex_t htd::PreprocessedGraph::vertexName(htd::vertex_t vertex) const
{
    return implementation_->names_[vertex];
}

const std::vector<std::vector<htd::vertex_t>> & htd::PreprocessedGraph::neighborhood(void) const HTD_NOEXCEPT
{
    return implementation_->neighborhood_;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::neighborhood(htd::vertex_t vertex) const
{
    HTD_ASSERT(vertex < implementation_->names_.size());

    return implementation_->neighborhood_[vertex];
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::eliminationSequence(void) const HTD_NOEXCEPT
{
    return implementation_->eliminationSequence_;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::remainingVertices(void) const HTD_NOEXCEPT
{
    return implementation_->remainingVertices_;
}

std::size_t htd::PreprocessedGraph::minTreeWidth(void) const HTD_NOEXCEPT
{
    return implementation_->minTreeWidth_;
}

#endif /* HTD_HTD_PREPROCESSEDGRAPH_CPP */
