/* 
 * File:   MaximumCardinalitySearchOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP
#define HTD_HTD_MAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/GraphPreprocessor.hpp>

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
    htd::GraphPreprocessor preprocessor(implementation_->managementInstance_);

    htd::PreprocessedGraph * preprocessedGraph = preprocessor.prepare(graph, false);

    htd::VertexOrdering * ret = computeOrdering(graph, *preprocessedGraph);

    delete preprocessedGraph;

    return ret;
}

htd::VertexOrdering * htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::PreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    HTD_UNUSED(graph)

    std::size_t size = preprocessedGraph.remainingVertices().size();

    std::unordered_set<htd::vertex_t> vertices(size);

    htd::fillSet(preprocessedGraph.remainingVertices(), vertices);

    std::vector<std::vector<htd::vertex_t>> neighborhood(preprocessedGraph.neighborhood().begin(), preprocessedGraph.neighborhood().end());

    std::vector<htd::vertex_t> pool;

    std::vector<std::size_t> weights(preprocessedGraph.vertexCount());

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(preprocessedGraph.vertexCount());

    ordering.insert(ordering.end(),
                    preprocessedGraph.eliminationSequence().begin(),
                    preprocessedGraph.eliminationSequence().end());

    while (size > 0 && !managementInstance.isTerminated())
    {
        std::size_t maxCardinality = 0;

        for (htd::vertex_t vertex : vertices)
        {
            std::size_t tmp = weights[vertex];

            if (tmp >= maxCardinality)
            {
                if (tmp > maxCardinality)
                {
                    maxCardinality = tmp;

                    pool.clear();
                }

                pool.push_back(vertex);
            }
        }

        htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

        std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood.at(selectedVertex);

        pool.clear();

        for (htd::vertex_t neighbor : selectedNeighborhood)
        {
            if (vertices.count(neighbor) == 1)
            {
                weights[neighbor] += 1;
            }
        }

        selectedNeighborhood.clear();

        vertices.erase(selectedVertex);

        --size;

        ordering.push_back(preprocessedGraph.vertexName(selectedVertex));
    }

    std::reverse(ordering.begin(), ordering.end());

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
