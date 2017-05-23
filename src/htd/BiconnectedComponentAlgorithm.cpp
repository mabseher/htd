/* 
 * File:   BiconnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_BICONNECTEDCOMPONENTALGORITHM_CPP
#define HTD_HTD_BICONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BiconnectedComponentAlgorithm.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>

/**
 *  Private implementation details of class htd::BiconnectedComponentAlgorithm.
 */
struct htd::BiconnectedComponentAlgorithm::Implementation
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

htd::BiconnectedComponentAlgorithm::BiconnectedComponentAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::BiconnectedComponentAlgorithm::~BiconnectedComponentAlgorithm()
{

}

void htd::BiconnectedComponentAlgorithm::determineComponents(const htd::IGraphStructure & graph, std::vector<std::vector<htd::vertex_t>> & target, std::vector<htd::vertex_t> & articulationPoints) const
{
    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    if (!vertexCollection.empty())
    {
        std::unordered_set<htd::vertex_t> unvisitedVertices(vertexCollection.begin(), vertexCollection.end());

        const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

        std::size_t time = 1;

        htd::vertex_t initialSize = graph.vertexAtPosition(graph.vertexCount() - 1) + 1;

        std::vector<std::size_t> low(initialSize);

        std::vector<std::size_t> discovery(initialSize);

        std::vector<htd::vertex_t> parent(initialSize, htd::Vertex::UNKNOWN - 1);

        std::deque<std::pair<htd::vertex_t, htd::vertex_t>> edges;

        std::stack<std::tuple<htd::vertex_t, htd::index_t, std::size_t>> stack;

        std::size_t oldArticulationPointCount = articulationPoints.size();

        while (!unvisitedVertices.empty() && !managementInstance.isTerminated())
        {
            htd::vertex_t vertex = *(unvisitedVertices.begin());

            if (discovery[vertex] == 0)
            {
                time = 1;

                stack.emplace(vertex, 0, 0);

                while (!stack.empty())
                {
                    htd::vertex_t current = std::get<0>(stack.top());

                    if (discovery[current] == 0)
                    {
                        low[current] = time;

                        discovery[current] = time;

                        unvisitedVertices.erase(current);

                        ++time;
                    }

                    htd::index_t index = std::get<1>(stack.top());

                    if (index < graph.neighborCount(current))
                    {
                        htd::vertex_t neighbor = graph.neighborAtPosition(current, index);

                        std::get<1>(stack.top())++;

                        if (discovery[neighbor] == 0)
                        {
                            std::get<2>(stack.top())++;

                            parent[neighbor] = current;

                            edges.emplace_back(current, neighbor);

                            stack.emplace(neighbor, 0, 0);
                        }
                        else if (neighbor != parent[current] && discovery[neighbor] < low[current])
                        {
                            low[current] = std::min(low[current], discovery[neighbor]);

                            edges.emplace_back(current, neighbor);
                        }
                    }
                    else
                    {
                        stack.pop();

                        if (!stack.empty())
                        {
                            current = std::get<0>(stack.top());

                            std::size_t children = std::get<2>(stack.top());

                            htd::vertex_t neighbor = graph.neighborAtPosition(current, std::get<1>(stack.top()) - 1);

                            low[current] = std::min(low[current], low[neighbor]);

                            if ((discovery[current] == 1 && children > 1) || (discovery[current] > 1 && low[neighbor] >= discovery[current]))
                            {
                                std::unordered_set<htd::vertex_t> component;

                                while (edges.back().first != current || edges.back().second != neighbor)
                                {
                                    component.insert(edges.back().first);
                                    component.insert(edges.back().second);

                                    edges.pop_back();
                                }

                                component.insert(edges.back().first);
                                component.insert(edges.back().second);

                                edges.pop_back();

                                target.emplace_back(component.begin(), component.end());

                                std::sort(target.back().begin(), target.back().end());

                                articulationPoints.push_back(current);
                            }
                        }
                    }
                }
            }

            std::unordered_set<htd::vertex_t> component;

            while (edges.size() > 0)
            {
                component.insert(edges.back().first);
                component.insert(edges.back().second);

                edges.pop_back();
            }

            if (!component.empty())
            {
                target.emplace_back(component.begin(), component.end());

                std::sort(target.back().begin(), target.back().end());
            }

            std::sort(articulationPoints.begin() + oldArticulationPointCount, articulationPoints.end());
        }
    }
}

void htd::BiconnectedComponentAlgorithm::determineComponent(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target, std::vector<htd::vertex_t> & articulationPoints) const
{
    HTD_ASSERT(graph.isVertex(startingVertex))

    std::vector<htd::vertex_t> tmp;

    std::vector<std::vector<htd::vertex_t>> components;

    htd::BiconnectedComponentAlgorithm::determineComponents(graph, components, tmp);

    bool found = false;

    for (auto it = components.begin(); !found && it != components.end(); ++it)
    {
        if (std::binary_search(it->begin(), it->end(), startingVertex))
        {
            target.insert(target.end(), it->begin(), it->end());

            std::set_intersection(it->begin(), it->end(), tmp.begin(), tmp.end(), std::back_inserter(articulationPoints));

            found = true;
        }
    }
}

const htd::LibraryInstance * htd::BiconnectedComponentAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::BiconnectedComponentAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::BiconnectedComponentAlgorithm * htd::BiconnectedComponentAlgorithm::clone(void) const
{
    return new htd::BiconnectedComponentAlgorithm(managementInstance());
}

#endif /* HTD_HTD_BICONNECTEDCOMPONENTALGORITHM_CPP */
