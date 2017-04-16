/*
 * File:   MinimumSeparatorAlgorithm.cpp
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

#ifndef HTD_HTD_MINIMUMSEPARATORALGORITHM_CPP
#define HTD_HTD_MINIMUMSEPARATORALGORITHM_CPP

#include <htd/MinimumSeparatorAlgorithm.hpp>

#include <htd/FlowNetworkStructure.hpp>
#include <htd/DinitzMaxFlowAlgorithm.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::MinimumSeparatorAlgorithm.
 */
struct htd::MinimumSeparatorAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;
};

htd::MinimumSeparatorAlgorithm::MinimumSeparatorAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::MinimumSeparatorAlgorithm::~MinimumSeparatorAlgorithm(void)
{

}

std::vector<htd::vertex_t> * htd::MinimumSeparatorAlgorithm::computeSeparator(const htd::IGraphStructure & graph) const
{
    std::vector<htd::vertex_t> * ret = new std::vector<htd::vertex_t>();

    std::size_t n = graph.vertexCount();

    htd::index_t index = 0;

    std::unordered_map<htd::vertex_t, htd::index_t> indices;

    for (htd::vertex_t vertex : graph.vertices())
    {
        indices.emplace(vertex, index);

        ++index;
    }

    htd::FlowNetworkStructure flowNetwork(n * 2);

    for (htd::vertex_t vertex : graph.vertices())
    {
        htd::index_t vertexIndex = indices.at(vertex);

        flowNetwork.updateCapacity(vertexIndex, vertexIndex + n, 1);

        for (htd::vertex_t neighbor : graph.neighbors(vertex))
        {
            htd::index_t neighborIndex = indices.at(neighbor);

            flowNetwork.updateCapacity(vertexIndex + n, neighborIndex, (std::size_t)-1);
            flowNetwork.updateCapacity(neighborIndex + n, vertexIndex, (std::size_t)-1);
        }
    }

    graph.copyVerticesTo(*ret);

    for (htd::index_t i = 0; i < n; ++i)
    {
        htd::vertex_t vertex1 = graph.vertexAtPosition(i);

        for (htd::index_t j = i + 1; j < n; ++j)
        {
            htd::vertex_t vertex2 = graph.vertexAtPosition(j);

            if (!graph.isNeighbor(vertex1, vertex2))
            {
                htd::DinitzMaxFlowAlgorithm maxFlowAlgorithm(implementation_->managementInstance_);

                htd::IFlow * flow = maxFlowAlgorithm.determineMaximumFlow(flowNetwork, i + n, j);

                std::unordered_set<htd::vertex_t> candidate;

                for(htd::index_t k = 0; k < n; ++k)
                {
                    if (k != i && k != j)
                    {
                        std::size_t capacity = flowNetwork.capacity(k, k + n);

                        if (static_cast<std::size_t>(flow->flow(k, k + n)) == capacity && capacity > 0 && capacity < (std::size_t)-1)
                        {
                            candidate.insert(graph.vertexAtPosition(k));
                        }
                    }
                }

                if (candidate.size() < ret->size())
                {
                    ret->clear();

                    ret->insert(ret->end(), candidate.begin(), candidate.end());

                    std::sort(ret->begin(), ret->end());
                }

                delete flow;
            }
        }
    }

    return ret;
}

const htd::LibraryInstance * htd::MinimumSeparatorAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MinimumSeparatorAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MinimumSeparatorAlgorithm * htd::MinimumSeparatorAlgorithm::clone(void) const
{
    return new htd::MinimumSeparatorAlgorithm(managementInstance());
}

#endif /* HTD_HTD_MINIMUMSEPARATORALGORITHM_CPP */
