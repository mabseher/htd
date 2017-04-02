/* 
 * File:   DepthFirstConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP
#define HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/DepthFirstGraphTraversal.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>

/**
 *  Private implementation details of class htd::DepthFirstConnectedComponentAlgorithm.
 */
struct htd::DepthFirstConnectedComponentAlgorithm::Implementation
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

htd::DepthFirstConnectedComponentAlgorithm::DepthFirstConnectedComponentAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::DepthFirstConnectedComponentAlgorithm::~DepthFirstConnectedComponentAlgorithm()
{

}

void htd::DepthFirstConnectedComponentAlgorithm::determineComponents(const htd::IGraphStructure & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (!vertexCollection.empty())
    {
        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

        while (!unvisitedVertices.empty() && !managementInstance.isTerminated())
        {
            std::vector<htd::vertex_t> component;

            determineComponent(graph, *(unvisitedVertices.begin()), component);

            for (htd::vertex_t visitedVertex : component)
            {
                unvisitedVertices.erase(visitedVertex);
            }

            target.push_back(std::move(component));
        }
    }
}

void htd::DepthFirstConnectedComponentAlgorithm::determineComponent(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(graph.isVertex(startingVertex))

    htd::DepthFirstGraphTraversal traversal(managementInstance());

    traversal.traverse(graph, startingVertex, [&](htd::vertex_t vertex, htd::vertex_t predecessor, std::size_t distanceFromStartingVertex)
    {
        HTD_UNUSED(predecessor)
        HTD_UNUSED(distanceFromStartingVertex)

        target.push_back(vertex);
    });

    std::sort(target.begin(), target.end());
}

const htd::LibraryInstance * htd::DepthFirstConnectedComponentAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::DepthFirstConnectedComponentAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::DepthFirstConnectedComponentAlgorithm * htd::DepthFirstConnectedComponentAlgorithm::clone(void) const
{
    return new htd::DepthFirstConnectedComponentAlgorithm(managementInstance());
}

#endif /* HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP */
