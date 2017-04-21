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
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/VertexOrdering.hpp>

#include <algorithm>
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

    /**
     *  Fill the pool of vertices having maximum weight.
     *
     *  @param[in] vertices The set of vertices which shall be considered.
     *  @param[in] weights  A vector containing the weights associated with each of the vertices.
     *  @param[out] pool    The vertex pool which shall be filled with all vertices of maximum weight.
     */
    void fillMaxCardinalityPool(const std::unordered_set<htd::vertex_t> & vertices, const std::vector<std::size_t> & weights, std::vector<htd::vertex_t> & pool) const HTD_NOEXCEPT
    {
        std::size_t max = 0;

        pool.clear();

        for (htd::vertex_t vertex : vertices)
        {
            std::size_t tmp = weights[vertex];

            if (tmp >= max)
            {
                if (tmp > max)
                {
                    max = tmp;

                    pool.clear();
                }

                pool.push_back(vertex);
            }
        }
    }
};

htd::MaximumCardinalitySearchOrderingAlgorithm::MaximumCardinalitySearchOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::MaximumCardinalitySearchOrderingAlgorithm::~MaximumCardinalitySearchOrderingAlgorithm()
{
    
}

htd::IVertexOrdering * htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::IVertexOrdering * ret = computeOrdering(graph, *preprocessedGraph);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::IVertexOrdering * htd::MaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    HTD_UNUSED(graph)

    std::size_t size = preprocessedGraph.remainingVertices().size();

    std::unordered_set<htd::vertex_t> vertices(size);

    htd::fillSet(preprocessedGraph.remainingVertices(), vertices);

    std::vector<std::vector<htd::vertex_t>> neighborhood(preprocessedGraph.neighborhood().begin(), preprocessedGraph.neighborhood().end());

    std::vector<htd::vertex_t> pool;

    std::vector<std::size_t> weights(preprocessedGraph.inputGraphVertexCount());

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(preprocessedGraph.vertexCount());

    ordering.insert(ordering.end(),
                    preprocessedGraph.eliminationSequence().begin(),
                    preprocessedGraph.eliminationSequence().end());

    while (size > 0 && !managementInstance.isTerminated())
    {
        implementation_->fillMaxCardinalityPool(vertices, weights, pool);

        htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

        std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood[selectedVertex];

        pool.clear();

        for (htd::vertex_t neighbor : selectedNeighborhood)
        {
            std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[neighbor];

            currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));

            weights[neighbor] += 1;
        }

        std::vector<htd::vertex_t>().swap(selectedNeighborhood);

        vertices.erase(selectedVertex);

        --size;

        ordering.push_back(preprocessedGraph.vertexName(selectedVertex));
    }

    std::reverse(ordering.begin() + preprocessedGraph.eliminationSequence().size(), ordering.end());

    return new htd::VertexOrdering(std::move(ordering), 1);
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
