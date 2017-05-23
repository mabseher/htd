/* 
 * File:   DinitzMaxFlowAlgorithm.cpp
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

#ifndef HTD_HTD_DINITZMAXFLOWALGORITHM_CPP
#define HTD_HTD_DINITZMAXFLOWALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DinitzMaxFlowAlgorithm.hpp>
#include <htd/IFlow.hpp>

#include <algorithm>
#include <deque>
#include <stack>
#include <stdexcept>
#include <unordered_map>

namespace htd
{
    /**
     *  Internal implementation of the htd::IFlow interface.
     */
    class Flow : public htd::IFlow
    {
        public:
            /**
             *  Constructor of a new flow data structure.
             *
             *  @param[in] vertexCount  The number of vertices of the flow data structure.
             *  @param[in] source       The source vertex.
             *  @param[in] target       The target vertex.
             */
            Flow(std::size_t vertexCount, htd::vertex_t source, htd::vertex_t target) : flow_(vertexCount, std::vector<long long>(vertexCount)), source_(source), target_(target)
            {

            }

            /**
             *  Copy constructor of a new flow data structure.
             *
             *  @param[in] original The original flow data structure.
             */
            Flow(const Flow & original) : flow_(original.flow_), source_(original.source_), target_(original.target_)
            {

            }

            std::size_t vertexCount(void) const HTD_OVERRIDE
            {
                return flow_.size();
            }

            htd::vertex_t source(void) const HTD_OVERRIDE
            {
                return source_;
            }

            htd::vertex_t target(void) const HTD_OVERRIDE
            {
                return target_;
            }

            std::size_t value(void) const HTD_OVERRIDE
            {
                std::size_t ret = 0;

                for (const std::vector<long long> & current : flow_)
                {
                    ret = ret + static_cast<std::size_t>(current[target_]);
                }

                return ret;
            }

            virtual long long flow(htd::vertex_t source, htd::vertex_t target) const HTD_OVERRIDE
            {
                HTD_ASSERT(source < vertexCount() && target < vertexCount())

                return flow_[source][target];
            }

            Flow * clone(void) const HTD_OVERRIDE
            {
                return new Flow(*this);
            }

            /**
             *  The flow.
             */
            std::vector<std::vector<long long>> flow_;

            /**
             *  The source vertex.
             */
            htd::vertex_t source_;

            /**
             *  The target vertex.
             */
            htd::vertex_t target_;
    };
}

/**
 *  Private implementation details of class htd::DinitzMaxFlowAlgorithm.
 */
struct htd::DinitzMaxFlowAlgorithm::Implementation
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
     *  Try to improve an existing flow.
     *
     *  @param[in] flowNetwork  The network for which the improved flow shall be computed.
     *  @param[in] flow         The (currently) best known flow within the given flow network.
     *
     *  @return A matrix containing the updated residual capacities or nullptr if the provided flow is already maximal.
     */
    std::vector<std::vector<std::size_t>> * improveFlow(const htd::IFlowNetworkStructure & flowNetwork, const htd::Flow & flow) const;

    /**
     *  Perform an improvement step for the flow between the source and the target vertex.
     *
     *  @param[in] flowNetwork  The flow network.
     *  @param[in] capacities   The residual capacities which will be updated.
     *  @param[in] distances    The distances from each vertex to the target vertex of the flow network.
     *  @param[in] source       The source vertex.
     *  @param[in] target       The target vertex.
     */
    void performImprovementStep(const htd::IFlowNetworkStructure & flowNetwork, std::vector<std::vector<std::size_t>> & capacities, const std::vector<std::size_t> & distances, htd::vertex_t source, htd::vertex_t target) const;

    /**
     *  Compute the minimum distances between the vertices of the given flow network to the selected target vertex.
     *
     *  @param[in] flowNetwork  The flow network.
     *  @param[in] capacities   The current residual capacities of the flow network.
     *  @param[in] target       The target vertex.
     *
     *  @return A vector containing the distances from each vertex to the target vertex.
     */
    std::vector<std::size_t> * computeMinimumDistances(const htd::IFlowNetworkStructure & flowNetwork, const std::vector<std::vector<std::size_t>> & capacities, htd::vertex_t target) const;

    /**
     *  Compute the minimum capacity within the given path starting from the given target vertex.
     *
     *  @param[in] path         A sequence of vertices which defines the path to investigate.
     *  @param[in] capacities   The current residual capacities of the flow network.
     *  @param[in] target       The target vertex.
     *
     *  @return The minimum capacity within the given path.
     */
    std::size_t computeMinimumCapacity(const std::vector<htd::vertex_t> & path, const std::vector<std::vector<std::size_t>> & capacities, htd::vertex_t target) const;
};

htd::DinitzMaxFlowAlgorithm::DinitzMaxFlowAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::DinitzMaxFlowAlgorithm::~DinitzMaxFlowAlgorithm()
{

}

htd::IFlow * htd::DinitzMaxFlowAlgorithm::determineMaximumFlow(const htd::IFlowNetworkStructure & flowNetwork, htd::vertex_t source, htd::vertex_t target) const
{
    std::size_t vertexCount = flowNetwork.vertexCount();

    htd::Flow * ret = new htd::Flow(vertexCount, source, target);

    std::vector<std::vector<std::size_t>> * capacities = implementation_->improveFlow(flowNetwork, *ret);

    while (capacities != nullptr)
    {
        for (htd::index_t i = 0; i < vertexCount; ++i)
        {
            for (htd::index_t j = 0; j < vertexCount; ++j)
            {
                ret->flow_[i][j] = flowNetwork.capacity(i, j) - (*capacities)[i][j];
            }
        }

        delete capacities;

        capacities = implementation_->improveFlow(flowNetwork, *ret);
    }

    return ret;
}

const htd::LibraryInstance * htd::DinitzMaxFlowAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::DinitzMaxFlowAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::DinitzMaxFlowAlgorithm * htd::DinitzMaxFlowAlgorithm::clone(void) const
{
    return new htd::DinitzMaxFlowAlgorithm(managementInstance());
}

std::vector<std::vector<std::size_t>> * htd::DinitzMaxFlowAlgorithm::Implementation::improveFlow(const htd::IFlowNetworkStructure & flowNetwork, const htd::Flow & flow) const
{
    std::size_t vertexCount = flowNetwork.vertexCount();

    std::vector<std::vector<std::size_t>> * ret = new std::vector<std::vector<std::size_t>>(vertexCount, std::vector<std::size_t>(vertexCount));

    std::vector<std::vector<std::size_t>> & capacities = *ret;

    for (htd::index_t i = 0; i < vertexCount; i++)
    {
        for (htd::index_t j = 0; j < vertexCount; j++)
        {
            capacities[i][j] = flowNetwork.capacity(i, j) - static_cast<std::size_t>(flow.flow_[i][j]);
        }
    }

    std::vector<std::size_t> * distances = computeMinimumDistances(flowNetwork, capacities, flow.target_);

    if ((*distances)[flow.source_] == (std::size_t)-1)
    {
        delete ret;

        ret = nullptr;
    }
    else
    {
        performImprovementStep(flowNetwork, capacities, *distances, flow.source_, flow.target_);
    }

    delete distances;

    return ret;
}

void htd::DinitzMaxFlowAlgorithm::Implementation::performImprovementStep(const htd::IFlowNetworkStructure & flowNetwork, std::vector<std::vector<std::size_t>> & capacities, const std::vector<std::size_t> & distances, htd::vertex_t source, htd::vertex_t target) const
{
    std::deque<htd::vertex_t> originDeque;

    std::unordered_set<htd::vertex_t> visitedVertices;

    htd::vertex_t currentVertex = source;

    originDeque.emplace_back(currentVertex);

    std::vector<htd::vertex_t> predecessors(flowNetwork.vertexCount(), (htd::vertex_t)-1);

    while (!originDeque.empty() && !managementInstance_->isTerminated())
    {
        currentVertex = originDeque.front();

        if (visitedVertices.count(currentVertex) == 0)
        {
            visitedVertices.insert(currentVertex);

            if (currentVertex == target)
            {
                std::size_t delta = computeMinimumCapacity(predecessors, capacities, target);

                htd::vertex_t current = currentVertex;

                htd::vertex_t predecessor = predecessors[currentVertex];

                while (predecessor != (htd::vertex_t)-1)
                {
                    capacities[predecessor][current] = capacities[predecessor][current] - delta;
                    capacities[current][predecessor] = capacities[current][predecessor] + delta;

                    if (capacities[predecessor][current] == 0)
                    {
                        currentVertex = predecessor;
                    }

                    current = predecessor;

                    predecessor = predecessors[predecessor];
                }
            }

            originDeque.pop_front();

            for (htd::vertex_t otherVertex = 0; otherVertex < flowNetwork.vertexCount(); ++otherVertex)
            {
                if (visitedVertices.count(otherVertex) == 0 && flowNetwork.capacity(currentVertex, otherVertex) > 0 && capacities[currentVertex][otherVertex] > 0 && distances[currentVertex] == distances[otherVertex] + 1)
                {
                    predecessors[otherVertex] = currentVertex;

                    originDeque.emplace_back(otherVertex);
                }
            }
        }
        else
        {
            originDeque.pop_front();
        }
    }
}

std::vector<std::size_t> * htd::DinitzMaxFlowAlgorithm::Implementation::computeMinimumDistances(const htd::IFlowNetworkStructure & flowNetwork, const std::vector<std::vector<std::size_t>> & capacities, htd::vertex_t target) const
{
    std::size_t vertexCount = flowNetwork.vertexCount();

    std::vector<std::size_t> * ret = new std::vector<std::size_t>(vertexCount, (std::size_t)-1);

    std::vector<std::size_t> & distances = *ret;

    distances[target]=0;

    std::stack<htd::vertex_t> stack;

    stack.push(target);

    while(!stack.empty())
    {
        htd::vertex_t vertex = stack.top();

        stack.pop();

        for (htd::index_t index = 0; index < vertexCount; ++index)
        {
            if (flowNetwork.capacity(index, vertex) > 0 && capacities[index][vertex] > 0)
            {
                std::size_t distance = distances[vertex] + 1;

                if (distance < distances[index])
                {
                    distances[index] = distance;

                    stack.push(index);
                }
            }
        }
    }

    return ret;
}

std::size_t htd::DinitzMaxFlowAlgorithm::Implementation::computeMinimumCapacity(const std::vector<htd::vertex_t> & path, const std::vector<std::vector<std::size_t>> & capacities, htd::vertex_t target) const
{
    std::size_t ret = (std::size_t)-1;

    htd::vertex_t current = target;

    htd::vertex_t predecessor = path[current];

    while (predecessor != (htd::vertex_t)-1)
    {
        std::size_t capacity = capacities[predecessor][current];

        if (ret > capacity)
        {
            ret = capacity;
        }

        current = predecessor;

        predecessor = path[predecessor];
    }

    return ret;
}

#endif /* HTD_HTD_DINITZMAXFLOWALGORITHM_CPP */
