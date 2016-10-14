/* 
 * File:   MaximumCardinalitySearchOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP
#define	HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::MaximumCardinalitySearchOrderingAlgorithm.
 */
struct htd::MaximumCardinalitySearchOrderingAlgorithm::Implementation
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

htd::MaximumCardinalitySearchOrderingAlgorithm::MaximumCardinalitySearchOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::MaximumCardinalitySearchOrderingAlgorithm::~MaximumCardinalitySearchOrderingAlgorithm()
{
    
}

htd::VertexOrdering * htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    std::size_t size = graph.vertexCount();

    std::size_t minDegree = (std::size_t)-1;

    std::unordered_set<htd::vertex_t> pool;

    std::unordered_set<htd::vertex_t> vertices(size);

    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> neighborhood(size);

    std::unordered_map<htd::vertex_t, std::size_t> weights(size);

    htd::fillSet(graph.vertices(), vertices);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(size);

    for (auto it = vertices.begin(); it != vertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        auto & currentNeighborhood = neighborhood[vertex];

        graph.copyNeighborsTo(currentNeighborhood, vertex);

        weights[vertex] = 0;

        std::size_t tmp = currentNeighborhood.size();

        if (tmp <= minDegree)
        {
            if (tmp < minDegree)
            {
                minDegree = tmp;

                pool.clear();
            }

            pool.insert(vertex);
        }
    }

    while (size > 0 && !managementInstance.isTerminated())
    {
        if (pool.empty())
        {
            std::size_t maxCardinality = 0;

            for (htd::vertex_t vertex : vertices)
            {
                std::size_t tmp = weights.at(vertex);

                if (tmp >= maxCardinality)
                {
                    if (tmp > maxCardinality)
                    {
                        maxCardinality = tmp;

                        pool.clear();
                    }

                    pool.insert(vertex);
                }
            }
        }

        htd::vertex_t selectedVertex = selectRandomElement<htd::vertex_t>(pool);

        auto & selectedNeighborhood = neighborhood.at(selectedVertex);

        pool.erase(selectedVertex);

        if (selectedNeighborhood.size() > 1)
        {
            for (auto neighbor : selectedNeighborhood)
            {
                if (neighbor != selectedVertex)
                {
                    if (vertices.count(neighbor) == 1)
                    {
                        weights[neighbor] += 1;

                        pool.erase(neighbor);
                    }
                }
            }
        }

        selectedNeighborhood.clear();

        vertices.erase(selectedVertex);

        size--;

        ordering.push_back(selectedVertex);
    }

    return new htd::VertexOrdering(std::move(ordering));
}

const htd::LibraryInstance * htd::MaximumCardinalitySearchOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MaximumCardinalitySearchOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MaximumCardinalitySearchOrderingAlgorithm * htd::MaximumCardinalitySearchOrderingAlgorithm::clone(void) const
{
    return new htd::MaximumCardinalitySearchOrderingAlgorithm(managementInstance());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::MaximumCardinalitySearchOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::MaximumCardinalitySearchOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP */
