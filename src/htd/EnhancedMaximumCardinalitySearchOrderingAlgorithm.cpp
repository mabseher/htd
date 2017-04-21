/* 
 * File:   EnhancedMaximumCardinalitySearchOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_ENHANCEDMAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP
#define HTD_HTD_ENHANCEDMAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/EnhancedMaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/VertexOrdering.hpp>

#include <algorithm>
#include <deque>
#include <unordered_set>

/**
 *  Private implementation details of class htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm.
 */
struct htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::Implementation
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

    /**
     *  Check whether there exists a path between two vertices consisting of only
     *  unnumbered vertices in the graph whose weight is strictly less than the
     *  weight of the source vertex.
     *
     *  @param[in] graph    The graph.
     *  @param[in] weights  A vector containing the weights associated with each of the vertices.
     *  @param[in] vertices The set of vertices which shall be considered.
     *  @param[in] source   The source vertex.
     *  @param[in] target   The target vertex.
     *
     *  @return True if a valid path between the two vertices exists, false otherwise.
     */
    bool hasValidPath(const htd::IPreprocessedGraph & graph, const std::vector<std::size_t> & weights, const std::unordered_set<htd::vertex_t> & vertices, htd::vertex_t source, htd::vertex_t target)
    {
        bool ret = false;

        std::size_t currentWeight = weights[source];

        std::deque<htd::vertex_t> originDeque;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = source;

        originDeque.push_back(currentVertex);

        while (!ret && !originDeque.empty() && !managementInstance_->isTerminated())
        {
            currentVertex = originDeque.front();

            visitedVertices.insert(currentVertex);

            ret = currentVertex == target;

            if (!ret)
            {
                const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.neighbors(currentVertex);

                auto it = neighborCollection.begin();

                for (std::size_t remainder = neighborCollection.size(); remainder > 0; --remainder)
                {
                    htd::vertex_t neighbor = *it;

                    if (visitedVertices.count(neighbor) == 0 && ((vertices.count(neighbor) == 1 && weights[neighbor] < currentWeight) || neighbor == target))
                    {
                        originDeque.push_back(neighbor);
                    }

                    ++it;
                }
            }

            originDeque.pop_front();
        }

        return ret;
    }
};

htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::EnhancedMaximumCardinalitySearchOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::~EnhancedMaximumCardinalitySearchOrderingAlgorithm()
{
    
}

htd::IVertexOrdering * htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::IVertexOrdering * ret = computeOrdering(graph, *preprocessedGraph);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::IVertexOrdering * htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    HTD_UNUSED(graph)

    std::size_t size = preprocessedGraph.remainingVertices().size();

    std::unordered_set<htd::vertex_t> vertices(size);

    htd::fillSet(preprocessedGraph.remainingVertices(), vertices);

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

        vertices.erase(selectedVertex);

        for (htd::vertex_t vertex : vertices)
        {
            if (implementation_->hasValidPath(preprocessedGraph, weights, vertices, vertex, selectedVertex))
            {
                weights[vertex]++;
            }
        }

        pool.clear();

        --size;

        ordering.push_back(preprocessedGraph.vertexName(selectedVertex));
    }

    std::reverse(ordering.begin() + preprocessedGraph.eliminationSequence().size(), ordering.end());

    return new htd::VertexOrdering(std::move(ordering), 1);
}

const htd::LibraryInstance * htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm * htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::clone(void) const
{
    return new htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm(managementInstance());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_ENHANCEDMAXIMUMCARDINALITYSEARCHORDERINGALGORITHM_CPP */
