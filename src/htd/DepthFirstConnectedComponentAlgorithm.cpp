/* 
 * File:   DepthFirstConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP
#define	HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/DepthFirstGraphTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>

htd::DepthFirstConnectedComponentAlgorithm::DepthFirstConnectedComponentAlgorithm(void) : htd::LibraryObject()
{

}

htd::DepthFirstConnectedComponentAlgorithm::~DepthFirstConnectedComponentAlgorithm()
{

}

void htd::DepthFirstConnectedComponentAlgorithm::determineComponents(const htd::IMultiHypergraph & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    htd::VectorAdapter<htd::ConstCollection<htd::vertex_t>> ret;

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (vertexCollection.size() > 0)
    {
        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        while (unvisitedVertices.size() > 0)
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

void htd::DepthFirstConnectedComponentAlgorithm::determineComponent(const htd::IMultiHypergraph & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(graph.isVertex(startingVertex))

    htd::DepthFirstGraphTraversal traversal;

    traversal.traverse(graph, startingVertex, [&](htd::vertex_t vertex, htd::vertex_t predecessor, std::size_t distanceFromStartingVertex)
    {
        HTD_UNUSED(predecessor)
        HTD_UNUSED(distanceFromStartingVertex)

        target.push_back(vertex);
    });

    std::sort(target.begin(), target.end());
}

htd::DepthFirstConnectedComponentAlgorithm * htd::DepthFirstConnectedComponentAlgorithm::clone(void) const
{
    htd::DepthFirstConnectedComponentAlgorithm * ret = new htd::DepthFirstConnectedComponentAlgorithm();

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_DEPTHFIRSTCONNECTEDCOMPONENTALGORITHM_CPP */
