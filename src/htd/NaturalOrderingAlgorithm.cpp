/* 
 * File:   NaturalOrderingAlgorithm.cpp
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

#ifndef HTD_HTD_NATURALORDERINGALGORITHM_CPP
#define HTD_HTD_NATURALORDERINGALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/NaturalOrderingAlgorithm.hpp>
#include <htd/VertexOrdering.hpp>

#include <algorithm>

/**
 *  Private implementation details of class htd::NaturalOrderingAlgorithm.
 */
struct htd::NaturalOrderingAlgorithm::Implementation
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

htd::NaturalOrderingAlgorithm::NaturalOrderingAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
    
}
            
htd::NaturalOrderingAlgorithm::~NaturalOrderingAlgorithm()
{
    
}

htd::IVertexOrdering * htd::NaturalOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph) const HTD_NOEXCEPT
{
    return new htd::VertexOrdering(std::vector<htd::vertex_t>(graph.vertices().begin(), graph.vertices().end()), 1);
}

htd::IVertexOrdering * htd::NaturalOrderingAlgorithm::computeOrdering(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const HTD_NOEXCEPT
{
    HTD_UNUSED(preprocessedGraph)

    return new htd::VertexOrdering(std::vector<htd::vertex_t>(graph.vertices().begin(), graph.vertices().end()), 1);
}

const htd::LibraryInstance * htd::NaturalOrderingAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::NaturalOrderingAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::NaturalOrderingAlgorithm * htd::NaturalOrderingAlgorithm::clone(void) const
{
    return new htd::NaturalOrderingAlgorithm(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IOrderingAlgorithm * htd::NaturalOrderingAlgorithm::cloneOrderingAlgorithm(void) const
{
    return new htd::NaturalOrderingAlgorithm(implementation_->managementInstance_);
}
#endif

#endif /* HTD_HTD_NATURALORDERINGALGORITHM_CPP */
