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
     *  @param[in] minTreeWidth         The lower bound for the treewidth of the original input graph.
     */
    Implementation(std::vector<htd::vertex_t> && vertexNames,
                   std::vector<std::vector<htd::vertex_t>> && neighborhood,
                   std::vector<htd::vertex_t> && eliminationSequence,
                   std::vector<htd::vertex_t> && remainingVertices,
                   std::size_t minTreeWidth)
        : names(vertexNames), neighborhood(neighborhood), eliminationSequence(eliminationSequence), remainder(remainingVertices), minTreeWidth(minTreeWidth)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The actual identifiers of the vertices.
     */
    std::vector<htd::vertex_t> names;

    /**
     *  A vector containing the neighborhood of each of the vertices.
     */
    std::vector<std::vector<htd::vertex_t>> neighborhood;

    /**
     *  A partial vertex elimination ordering computed during the preprocessing phase.
     */
    std::vector<htd::vertex_t> eliminationSequence;

    /**
     *  The set of vertices which were not eliminated during the preprocessing phase.
     */
    std::vector<htd::vertex_t> remainder;

    /**
     *  The lower bound of the treewidth of the input graph.
     */
    std::size_t minTreeWidth;
};

htd::PreprocessedGraph::PreprocessedGraph(std::vector<htd::vertex_t> && vertexNames,
                                          std::vector<std::vector<htd::vertex_t>> && neighborhood,
                                          std::vector<htd::vertex_t> && eliminationSequence,
                                          std::vector<htd::vertex_t> && remainingVertices,
                                          std::size_t minTreeWidth)
    : implementation_(new Implementation(std::move(vertexNames),
                                         std::move(neighborhood),
                                         std::move(eliminationSequence),
                                         std::move(remainingVertices),
                                         minTreeWidth))
{

}

htd::PreprocessedGraph::~PreprocessedGraph()
{

}

std::size_t htd::PreprocessedGraph::vertexCount(void) const HTD_NOEXCEPT
{
    return implementation_->names.size();
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::vertexNames(void) const HTD_NOEXCEPT
{
    return implementation_->names;
}

htd::vertex_t htd::PreprocessedGraph::vertexName(htd::vertex_t vertex) const
{
    return implementation_->names[vertex];
}

const std::vector<std::vector<htd::vertex_t>> & htd::PreprocessedGraph::neighborhood(void) const HTD_NOEXCEPT
{
    return implementation_->neighborhood;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::neighborhood(htd::vertex_t vertex) const
{
    HTD_ASSERT(vertex < implementation_->names.size());

    return implementation_->neighborhood[vertex];
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::eliminationSequence(void) const HTD_NOEXCEPT
{
    return implementation_->eliminationSequence;
}

const std::vector<htd::vertex_t> & htd::PreprocessedGraph::remainingVertices(void) const HTD_NOEXCEPT
{
    return implementation_->remainder;
}

std::size_t htd::PreprocessedGraph::minTreeWidth(void) const HTD_NOEXCEPT
{
    return implementation_->minTreeWidth;
}

#endif /* HTD_HTD_PREPROCESSEDGRAPH_CPP */
