/* 
 * File:   RandomOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_RANDOMORDERINGALGORITHM_CPP
#define HTD_HTD_RANDOMORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/RandomOrderingAlgorithm.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/VertexOrdering.hpp>

#include <algorithm>
#include <random>

/**
 *  Private implementation details of class htd::NaturalOrderingAlgorithm.
 */
struct htd::RandomOrderingAlgorithm::Implementation
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

htd::RandomOrderingAlgorithm::RandomOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::RandomOrderingAlgorithm::~RandomOrderingAlgorithm()
{
    
}

htd::IVertexOrdering * htd::RandomOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::IVertexOrdering * ret = computeOrdering(graph, *preprocessedGraph);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::IVertexOrdering * htd::RandomOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> ordering;
    ordering.reserve(preprocessedGraph.vertexCount());

    ordering.insert(ordering.end(),
                    preprocessedGraph.eliminationSequence().begin(),
                    preprocessedGraph.eliminationSequence().end());

    ordering.insert(ordering.end(),
                    preprocessedGraph.remainingVertices().begin(),
                    preprocessedGraph.remainingVertices().end());

    auto middle = ordering.begin() + preprocessedGraph.eliminationSequence().size();

    std::for_each(middle, ordering.end(), [&](htd::vertex_t & vertex)
    {
        vertex = preprocessedGraph.vertexName(vertex);
    });

    /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
    // coverity[dont_call]
    std::mt19937 g(static_cast<std::mt19937::result_type>(std::rand()));

    std::shuffle(middle, ordering.end(), g);

    return new htd::VertexOrdering(std::move(ordering), 1);
}

const htd::LibraryInstance * htd::RandomOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::RandomOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::RandomOrderingAlgorithm * htd::RandomOrderingAlgorithm::clone(void) const
{
    return new htd::RandomOrderingAlgorithm(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::RandomOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::RandomOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_RANDOMORDERINGALGORITHM_CPP */
