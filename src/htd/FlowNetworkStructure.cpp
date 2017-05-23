/* 
 * File:   MultiGraph.cpp
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

#ifndef HTD_HTD_MULTIGRAPH_CPP
#define HTD_HTD_MULTIGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/FlowNetworkStructure.hpp>

#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <numeric>
#include <utility>
#include <stack>
#include <unordered_set>

/**
 *  Private implementation details of class htd::FlowNetworkStructure.
 */
struct htd::FlowNetworkStructure::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] vertexCount  The number of vertices of the flow network structure.
     */
    Implementation(std::size_t vertexCount) : vertices_(vertexCount), neighborhood_(vertexCount), capacities_(vertexCount, std::vector<std::size_t>(vertexCount))
    {
        std::iota(vertices_.begin(), vertices_.end(), 0);
    }

    virtual ~Implementation()
    {

    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original) : vertices_(original.vertices_), neighborhood_(original.neighborhood_), capacities_(original.capacities_)
    {

    }

    /**
     *  The vertices of the flow network.
     */
    std::vector<htd::vertex_t> vertices_;

    /**
     *  The directed neighborhood for each of the vertices.
     */
    std::vector<std::vector<htd::vertex_t>> neighborhood_;

    /**
     *  The residual capacities of the flow network.
     */
    std::vector<std::vector<std::size_t>> capacities_;
};

htd::FlowNetworkStructure::FlowNetworkStructure(std::size_t vertexCount) : implementation_(new Implementation(vertexCount))
{

}

htd::FlowNetworkStructure::FlowNetworkStructure(const htd::FlowNetworkStructure & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::FlowNetworkStructure::~FlowNetworkStructure()
{

}

std::size_t htd::FlowNetworkStructure::vertexCount(void) const
{
    return implementation_->neighborhood_.size();
}

std::size_t htd::FlowNetworkStructure::edgeCount(void) const
{
    std::size_t ret = 0;

    for (const std::vector<htd::vertex_t> & currentNeighborhood : implementation_->neighborhood_)
    {
        ret += currentNeighborhood.size();
    }

    return ret;
}

std::size_t htd::FlowNetworkStructure::edgeCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->neighborhood_[vertex].size();
}

bool htd::FlowNetworkStructure::isVertex(htd::vertex_t vertex) const
{
    return vertex < implementation_->neighborhood_.size();
}

bool htd::FlowNetworkStructure::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    return std::binary_search(currentNeighborhood.begin(), currentNeighborhood.end(), neighbor);
}

bool htd::FlowNetworkStructure::isConnected(void) const
{
    bool ret = true;

    if (!(implementation_->neighborhood_.empty()))
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = 0;

        originStack.push(currentVertex);

        while (!originStack.empty())
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : implementation_->neighborhood_[currentVertex])
                {
                    if (visitedVertices.count(neighbor) == 0)
                    {
                        originStack.push(neighbor);
                    }
                }
            }
            else
            {
                originStack.pop();
            }
        }

        ret = visitedVertices.size() == implementation_->neighborhood_.size();
    }
    else
    {
        ret = true;
    }

    return ret;
}

bool htd::FlowNetworkStructure::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

    bool ret = false;

    if (vertex1 == vertex2)
    {
        ret = true;
    }
    else
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = vertex1;

        originStack.push(currentVertex);

        while (!originStack.empty() && visitedVertices.count(vertex2) == 0)
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : implementation_->neighborhood_[currentVertex])
                {
                    if (visitedVertices.count(neighbor) == 0)
                    {
                        originStack.push(neighbor);
                    }
                }
            }
            else
            {
                originStack.pop();
            }
        }

        ret = visitedVertices.count(vertex2) == 1;
    }

    return ret;
}

std::size_t htd::FlowNetworkStructure::neighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->neighborhood_[vertex].size();
}

htd::ConstCollection<htd::vertex_t> htd::FlowNetworkStructure::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->neighborhood_[vertex]);
}

void htd::FlowNetworkStructure::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    target.insert(target.end(), currentNeighborhood.begin(), currentNeighborhood.end());
}

htd::vertex_t htd::FlowNetworkStructure::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex];

    HTD_ASSERT(index < currentNeighborhood.size())

    return currentNeighborhood[index];
}

htd::ConstCollection<htd::vertex_t> htd::FlowNetworkStructure::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->vertices_);
}

void htd::FlowNetworkStructure::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    target.insert(target.end(), implementation_->vertices_.begin(), implementation_->vertices_.end());
}

htd::vertex_t htd::FlowNetworkStructure::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->vertices_.size())

    return implementation_->vertices_[index];
}

std::size_t htd::FlowNetworkStructure::isolatedVertexCount(void) const
{
    return isolatedVertices().size();
}

htd::ConstCollection<htd::vertex_t> htd::FlowNetworkStructure::isolatedVertices(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t vertex : implementation_->vertices_)
    {
        if (implementation_->neighborhood_[vertex].empty())
        {
            bool isolated = true;

            for (auto it = implementation_->neighborhood_.begin(); isolated && it != implementation_->neighborhood_.end(); ++it)
            {
                isolated = !(std::binary_search(it->begin(), it->end(), vertex));
            }

            if (isolated)
            {
                result.push_back(vertex);
            }
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::FlowNetworkStructure::isolatedVertexAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

    HTD_ASSERT(index < isolatedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = isolatedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::FlowNetworkStructure::isIsolatedVertex(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    bool ret = false;

    if (implementation_->neighborhood_[vertex].empty())
    {
        ret = true;

        for (auto it = implementation_->neighborhood_.begin(); ret && it != implementation_->neighborhood_.end(); ++it)
        {
            ret = !(std::binary_search(it->begin(), it->end(), vertex));
        }
    }

    return ret;
}

std::size_t htd::FlowNetworkStructure::capacity(htd::vertex_t source, htd::vertex_t target) const
{
    HTD_ASSERT(isVertex(source) && isVertex(target))

    return implementation_->capacities_[source][target];
}

void htd::FlowNetworkStructure::updateCapacity(htd::vertex_t source, htd::vertex_t target, std::size_t capacity)
{
    HTD_ASSERT(isVertex(source) && isVertex(target))

    std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[source];

    auto position = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), target);

    if (position == currentNeighborhood.end() || *position != target)
    {
        currentNeighborhood.insert(position, target);
    }

    implementation_->capacities_[source][target] = capacity;
}

htd::FlowNetworkStructure * htd::FlowNetworkStructure::clone(void) const
{
    return new htd::FlowNetworkStructure(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraphStructure * htd::FlowNetworkStructure::cloneGraphStructure(void) const
{
    return clone();
}

htd::IFlowNetworkStructure * htd::FlowNetworkStructure::cloneFlowNetworkStructure(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_MULTIGRAPH_CPP */
