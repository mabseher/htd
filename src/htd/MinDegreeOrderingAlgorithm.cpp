/* 
 * File:   MinDegreeOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP
#define HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/GraphPreprocessor.hpp>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/**
 *  Private implementation details of class htd::MinDegreeOrderingAlgorithm.
 */
struct htd::MinDegreeOrderingAlgorithm::Implementation
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
     *  Compute the vertex ordering of a given graph and write it to the end of a given vector.
     *
     *  @param[in] preprocessedGraph    The input graph in preprocessed format.
     *  @param[out] target              The target vector to which the computed ordering shall be appended.
     *  @param[in] maxBagSize           The upper bound for the maximum bag size of a decomposition based on the resulting ordering.
     *
     *  @return The maximum bag size of the decomposition which is obtained via bucket elimination using the input graph and the resulting ordering.
     */
    std::size_t writeOrderingTo(const htd::PreprocessedGraph & preprocessedGraph, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT;

    /**
     *  Get a random vertex having minimum degree.
     *
     *  @param[in] vertices     The set of vertices which shall be considered.
     *  @param[in] neighborhood A vector containing the neighborhood of each of the vertices.
     *  @param[out] pool        The vertex pool which shall be filled with all vertices of minimum degree.
     */
    void fillMinDegreePool(const std::unordered_set<htd::vertex_t> & vertices, const std::vector<std::vector<htd::vertex_t>> & neighborhood, std::vector<htd::vertex_t> & pool) const HTD_NOEXCEPT
    {
        std::size_t min = (std::size_t)-1;

        pool.clear();

        for (htd::vertex_t vertex : vertices)
        {
            std::size_t degree = neighborhood[vertex].size();

            if (degree <= min)
            {
                if (degree < min)
                {
                    min = degree;

                    pool.clear();
                }

                pool.push_back(vertex);
            }
        }
    }
};

htd::MinDegreeOrderingAlgorithm::MinDegreeOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::MinDegreeOrderingAlgorithm::~MinDegreeOrderingAlgorithm()
{
    
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    return computeOrdering(graph, (std::size_t)-1, 1);
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT
{
    htd::GraphPreprocessor preprocessor(implementation_->managementInstance_);

    htd::PreprocessedGraph * preprocessedGraph = preprocessor.prepare(graph, false);

    htd::VertexOrdering * ret = computeOrdering(graph, *preprocessedGraph, maxBagSize, maxIterationCount);

    delete preprocessedGraph;

    return ret;
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::PreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    return computeOrdering(graph, preprocessedGraph, (std::size_t)-1, 1);
}

htd::VertexOrdering * htd::MinDegreeOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::PreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, std::size_t maxIterationCount) const HTD_NOEXCEPT
{
    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(graph.vertexCount());

    std::size_t iterations = 0;

    std::size_t currentMaxBagSize = (std::size_t)-1;

    do
    {
        ordering.clear();

        currentMaxBagSize = implementation_->writeOrderingTo(preprocessedGraph, ordering, maxBagSize);

        ++iterations;
    }
    while (currentMaxBagSize > maxBagSize && iterations < maxIterationCount && !managementInstance.isTerminated());

    if (maxIterationCount == 0 && currentMaxBagSize > maxBagSize)
    {
        ordering.clear();
    }

    return new htd::VertexOrdering(std::move(ordering), iterations);
}

std::size_t htd::MinDegreeOrderingAlgorithm::Implementation::writeOrderingTo(const htd::PreprocessedGraph & preprocessedGraph, std::vector<htd::vertex_t> & target, std::size_t maxBagSize) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    std::size_t size = preprocessedGraph.remainingVertices().size();

    std::unordered_set<htd::vertex_t> vertices(size);

    htd::fillSet(preprocessedGraph.remainingVertices(), vertices);

    std::vector<std::vector<htd::vertex_t>> neighborhood(preprocessedGraph.neighborhood().begin(), preprocessedGraph.neighborhood().end());

    std::vector<htd::vertex_t> difference;

    std::vector<htd::vertex_t> pool;

    target.insert(target.end(),
                  preprocessedGraph.eliminationSequence().begin(),
                  preprocessedGraph.eliminationSequence().end());

    ret = preprocessedGraph.minTreeWidth() + 1;

    for (htd::vertex_t vertex : vertices)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[vertex];

        currentNeighborhood.insert(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex), vertex);
    }

    while (size > 0 && ret <= maxBagSize && !managementInstance_->isTerminated())
    {
        fillMinDegreePool(vertices, neighborhood, pool);

        htd::vertex_t selectedVertex = htd::selectRandomElement<htd::vertex_t>(pool);

        std::vector<htd::vertex_t> & selectedNeighborhood = neighborhood[selectedVertex];

        if (selectedNeighborhood.size() > ret)
        {
            ret = selectedNeighborhood.size();
        }

        vertices.erase(selectedVertex);

        if (selectedNeighborhood.size() > 1)
        {
            selectedNeighborhood.erase(std::lower_bound(selectedNeighborhood.begin(), selectedNeighborhood.end(), selectedVertex));

            for (auto neighbor : selectedNeighborhood)
            {
                std::vector<htd::vertex_t> & currentNeighborhood = neighborhood[neighbor];

                currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), selectedVertex));

                htd::set_difference(selectedNeighborhood, currentNeighborhood, difference);

                if (!difference.empty())
                {
                    if (difference.size() <= 8)
                    {
                        auto it = currentNeighborhood.begin();

                        for (htd::vertex_t newNeighbor : difference)
                        {
                            it = currentNeighborhood.insert(std::lower_bound(it, currentNeighborhood.end(), newNeighbor), newNeighbor) + 1;
                        }
                    }
                    else
                    {
                        std::size_t middle = currentNeighborhood.size();

                        currentNeighborhood.insert(currentNeighborhood.end(), difference.begin(), difference.end());

                        std::inplace_merge(currentNeighborhood.begin(),
                                           currentNeighborhood.begin() + middle,
                                           currentNeighborhood.end());
                    }

                    difference.clear();
                }
            }
        }

        selectedNeighborhood.clear();

        size--;

        target.push_back(preprocessedGraph.vertexName(selectedVertex));
    }

    return ret;
}

const htd::LibraryInstance * htd::MinDegreeOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MinDegreeOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MinDegreeOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::clone(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}

htd::IWidthLimitableOrderingAlgorithm * htd::MinDegreeOrderingAlgorithm::cloneWidthLimitableOrderingAlgorithm(void) const
{
    return new htd::MinDegreeOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_MINDEGREEORDERINGALGORITHM_CPP */
