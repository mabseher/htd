/* 
 * File:   TarjanStronglyConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP
#define	HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TarjanStronglyConnectedComponentAlgorithm.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>

htd::TarjanStronglyConnectedComponentAlgorithm::TarjanStronglyConnectedComponentAlgorithm(void)
{

}

htd::TarjanStronglyConnectedComponentAlgorithm::~TarjanStronglyConnectedComponentAlgorithm()
{

}

htd::ConstCollection<htd::ConstCollection<htd::vertex_t>> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IHypergraph & graph) const
{
    htd::VectorAdapter<htd::ConstCollection<htd::vertex_t>> ret;

    std::vector<htd::ConstCollection<htd::vertex_t>> & components = ret.container();

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (vertexCollection.size() > 0)
    {
        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        while (unvisitedVertices.size() > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & component = determineComponent(graph, *(unvisitedVertices.begin()));

            for (htd::vertex_t visitedVertex : component)
            {
                unvisitedVertices.erase(visitedVertex);
            }

            components.push_back(component);
        }
    }

    return htd::ConstCollection<htd::ConstCollection<htd::vertex_t>>::getInstance(ret);
}

htd::ConstCollection<htd::ConstCollection<htd::vertex_t>> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IDirectedGraph & graph) const
{
    htd::VectorAdapter<htd::ConstCollection<htd::vertex_t>> ret;

    std::vector<htd::ConstCollection<htd::vertex_t>> & components = ret.container();

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (vertexCollection.size() > 0)
    {
        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        while (unvisitedVertices.size() > 0)
        {
            const htd::ConstCollection<htd::vertex_t> & component = determineComponent(graph, *(unvisitedVertices.begin()));

            for (htd::vertex_t visitedVertex : component)
            {
                unvisitedVertices.erase(visitedVertex);
            }

            components.push_back(component);
        }
    }

    return htd::ConstCollection<htd::ConstCollection<htd::vertex_t>>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IHypergraph & graph, htd::vertex_t startingVertex) const
{
    if (!graph.isVertex(startingVertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IHypergraph &, htd::vertex_t) const");
    }

    std::stack<htd::vertex_t> originStack;

    htd::VectorAdapter<htd::vertex_t> ret;

    std::unordered_set<htd::vertex_t> visitedVertices;

    std::vector<htd::vertex_t> & component = ret.container();

    htd::vertex_t currentVertex = startingVertex;

    originStack.push(currentVertex);

    while (!originStack.empty())
    {
        currentVertex = originStack.top();

        component.push_back(currentVertex);
        visitedVertices.insert(currentVertex);

        originStack.pop();

        for (htd::vertex_t neighbor : graph.neighbors(currentVertex))
        {
            if (visitedVertices.count(neighbor) == 0)
            {
                originStack.push(neighbor);
            }
        }
    }

    std::sort(component.begin(), component.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedGraph & graph, htd::vertex_t startingVertex) const
{
    if (!graph.isVertex(startingVertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedGraph &, htd::vertex_t) const");
    }

    std::stack<htd::vertex_t> originStack;

    htd::VectorAdapter<htd::vertex_t> ret;

    std::unordered_set<htd::vertex_t> visitedVertices;

    std::vector<htd::vertex_t> & component = ret.container();

    htd::vertex_t currentVertex = startingVertex;

    originStack.push(currentVertex);

    while (!originStack.empty())
    {
        currentVertex = originStack.top();

        component.push_back(currentVertex);
        visitedVertices.insert(currentVertex);

        originStack.pop();

        for (htd::vertex_t neighbor : graph.neighbors(currentVertex))
        {
            if (visitedVertices.count(neighbor) == 0)
            {
                originStack.push(neighbor);
            }
        }
    }

    std::sort(component.begin(), component.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::TarjanStronglyConnectedComponentAlgorithm * htd::TarjanStronglyConnectedComponentAlgorithm::clone(void) const
{
    return new TarjanStronglyConnectedComponentAlgorithm();
}

#endif /* HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP */
