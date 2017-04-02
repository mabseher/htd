/* 
 * File:   TarjanStronglyConnectedComponentAlgorithm.cpp
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

#ifndef HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP
#define HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/TarjanStronglyConnectedComponentAlgorithm.hpp>

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <unordered_map>

/**
 *  Internal data structure used to store relevant vertex information needed by Tarjan's algorithm.
 */
struct Node {
    /**
     *  The vertex to which the node corresponds.
     */
    htd::vertex_t vertex;

    /**
     *  The time when the vertex was discovered the first time in the depth-first search.
     */
    htd::index_t discovery;

    /**
     *  The smallest discovery time of any node which is known to be reachable from this node (including this node).
     */
    htd::index_t low;

    /**
     *  The node corresponding to the predecessor node before the recursive call is made in the recursive version of Tarjan's algorithm.
     */
    Node * predecessor;

    /**
     *  The index of the next neighbor which will be visited.
     */
    htd::index_t index;

    /**
     *  A vector of all outgoing neighbors from this node.
     */
    std::vector<Node *> * neighbors;

    /**
     *  Constructor of a new object of type Node.
     *
     *  @param[in] vertex   The vertex to which the node corresponds.
     */
    Node(htd::vertex_t vertex) : vertex(vertex), discovery(0), low(0), predecessor(nullptr), index(0), neighbors(new std::vector<Node *>())
    {

    }

    /**
     *  Destructor of an object of type Node.
     */
    virtual ~Node()
    {
        delete neighbors;
    }
};

/**
 *  Private implementation details of class htd::TarjanStronglyConnectedComponentAlgorithm.
 */
struct htd::TarjanStronglyConnectedComponentAlgorithm::Implementation
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
     *  Determine the strongly connected components of a given graph.
     *
     *  @param[in] node         The node from which the algorithm shall start.
     *  @param[in] stack        The stack needed for simulating the recursion of depth-first search.
     *  @param[in] stackMembers A set containing all vertices which are currently members of the stack.
     *  @param[in] time         A number for keeping track of the time when a vertex was first discovered and which is incremented after discovering a new vertex.
     *  @param[out] target      The target vector to which the determined components shall be appended.
     */
    void determineComponents(Node * node, std::stack<Node *> & stack, std::unordered_set<htd::vertex_t> & stackMembers, htd::index_t & time, std::vector<std::vector<htd::vertex_t>> & target) const
    {
        node->discovery = time;
        node->low = time;

        time++;

        stack.push(node);

        stackMembers.insert(node->vertex);

        Node * last = node;

        bool finished = false;

        while (!finished)
        {
           if (last->index < last->neighbors->size())
           {
               Node * w = (*(last->neighbors))[last->index];

               last->index++;

               if(w->discovery == 0)
               {
                   w->predecessor = last;
                   w->index = 0;
                   w->discovery = time;
                   w->low = time;

                   ++time;

                   stack.push(w);

                   stackMembers.insert(w->vertex);

                   last = w;
               }
               else if (stackMembers.count(w->vertex) == 1)
               {
                   last->low = std::min(last->low, w->discovery);
               }
           }
           else
           {
               if(last->low == last->discovery)
               {
                   std::vector<htd::vertex_t> component;

                   Node * top = stack.top();

                   component.emplace_back(top->vertex);

                   stack.pop();

                   stackMembers.erase(top->vertex);

                   int size = 1;

                   while(top->vertex != last->vertex)
                   {
                       top = stack.top();

                       component.emplace_back(top->vertex);

                       stack.pop();

                       stackMembers.erase(top->vertex);

                       size++;
                   }

                   std::sort(component.begin(), component.end());

                   target.emplace_back(std::move(component));
               }

               Node * newLast = last->predecessor;

               if(newLast != nullptr)
               {
                   newLast->low = std::min(newLast->low, last->low);

                   last = newLast;
               }
               else
               {
                   finished = true;
               }
           }
       }
    }
};

htd::TarjanStronglyConnectedComponentAlgorithm::TarjanStronglyConnectedComponentAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::TarjanStronglyConnectedComponentAlgorithm::~TarjanStronglyConnectedComponentAlgorithm()
{

}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IGraphStructure & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    /**
     *  Hypergraphs are assumed to be undirected, therefore the strongly connected components are identical to the connected components.
     *
     *  For this reason we can use the more efficient algorithm based on simple depth-first search.
     */
    DepthFirstConnectedComponentAlgorithm algorithm(implementation_->managementInstance_);

    algorithm.determineComponents(graph, target);
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponents(const htd::IDirectedMultiGraph & graph, std::vector<std::vector<htd::vertex_t>> & target) const
{
    std::size_t vertexCount = graph.vertexCount();

    std::unordered_map<htd::vertex_t, Node *> nodes(vertexCount);

    std::stack<Node *> stack;

    std::unordered_set<htd::vertex_t> stackMembers;

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    auto it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        htd::vertex_t vertex = *it;

        nodes.emplace(vertex, new Node(vertex));

        ++it;
    }

    it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        htd::vertex_t vertex = *it;

        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.outgoingNeighbors(vertex);

        auto it2 = neighborCollection.begin();

        for (htd::index_t index2 = 0; index2 < neighborCollection.size(); ++index2)
        {
            htd::vertex_t neighbor = *it2;

            if (neighbor != vertex)
            {
                nodes[vertex]->neighbors->emplace_back(nodes.at(neighbor));
            }

            ++it2;
        }

        ++it;
    }

    it = vertexCollection.begin();

    htd::index_t time = 1;

    for (htd::index_t index = 0; index < vertexCount; ++index)
    {
        htd::vertex_t vertex = *it;

        if (nodes[vertex]->discovery == 0)
        {
            implementation_->determineComponents(nodes.at(vertex), stack, stackMembers, time, target);
        }

        ++it;
    }

    it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        delete nodes[*it];

        ++it;
    }
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IGraphStructure & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    /**
     *  Hypergraphs are assumed to be undirected, therefore the strongly connected components are identical to the connected components.
     *
     *  For this reason we can use the more efficient algorithm based on simple depth-first search.
     */
    DepthFirstConnectedComponentAlgorithm algorithm(managementInstance());

    algorithm.determineComponent(graph, startingVertex, target);
}

void htd::TarjanStronglyConnectedComponentAlgorithm::determineComponent(const htd::IDirectedMultiGraph & graph, htd::vertex_t startingVertex, std::vector<htd::vertex_t> & target) const
{
    std::size_t vertexCount = graph.vertexCount();

    std::unordered_map<htd::vertex_t, Node *> nodes(vertexCount);

    std::stack<Node *> stack;

    std::unordered_set<htd::vertex_t> stackMembers;

    const htd::ConstCollection<htd::vertex_t> & vertexCollection = graph.vertices();

    auto it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        htd::vertex_t vertex = *it;

        nodes.emplace(vertex, new Node(vertex));

        ++it;
    }

    it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        htd::vertex_t vertex = *it;

        const htd::ConstCollection<htd::vertex_t> & neighborCollection = graph.outgoingNeighbors(vertex);

        auto it2 = neighborCollection.begin();

        for (htd::index_t index2 = 0; index2 < neighborCollection.size(); ++index2)
        {
            htd::vertex_t neighbor = *it2;

            if (neighbor != vertex)
            {
                nodes[vertex]->neighbors->emplace_back(nodes.at(neighbor));
            }

            ++it2;
        }

        ++it;
    }

    htd::index_t time = 1;

    std::vector<std::vector<htd::vertex_t>> components;

    implementation_->determineComponents(nodes.at(startingVertex), stack, stackMembers, time, components);

    bool found = false;

    for (auto it2 = components.begin(); it2 != components.end() && !found; ++it2)
    {
        const std::vector<htd::vertex_t> & component = *it2;

        if (std::binary_search(component.begin(), component.end(), startingVertex))
        {
            std::copy(component.begin(), component.end(), std::back_inserter(target));

            found = true;
        }
    }

    it = vertexCollection.begin();

    for (htd::index_t index = 0; index < vertexCount; index++)
    {
        delete nodes[*it];

        ++it;
    }
}

const htd::LibraryInstance * htd::TarjanStronglyConnectedComponentAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::TarjanStronglyConnectedComponentAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::TarjanStronglyConnectedComponentAlgorithm * htd::TarjanStronglyConnectedComponentAlgorithm::clone(void) const
{
    return new htd::TarjanStronglyConnectedComponentAlgorithm((managementInstance()));
}

#endif /* HTD_HTD_TARJANSTRONGLYCONNECTEDCOMPONENTALGORITHM_CPP */
