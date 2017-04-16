/* 
 * File:   DirectedMultiGraph.cpp
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

#ifndef HTD_HTD_DIRECTEDMULTIGRAPH_CPP
#define HTD_HTD_DIRECTEDMULTIGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DirectedMultiGraph.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

/**
 *  Private implementation details of class htd::DirectedMultiGraph.
 */
struct htd::DirectedMultiGraph::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     *  @param[in] base     The multi-hypergraph instance which will act as base class for the directed multi-graph.
     */
    Implementation(const htd::LibraryInstance * const manager, htd::IMutableMultiHypergraph * base) : managementInstance_(manager), base_(base), incomingNeighborhood_(), outgoingNeighborhood_()
    {

    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), incomingNeighborhood_(original.incomingNeighborhood_), outgoingNeighborhood_(original.outgoingNeighborhood_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        base_ = original.base_->clone();
#else
        base_ = original.base_->cloneMutableMultiHypergraph();
#endif
    }

    virtual ~Implementation()
    {
        delete base_;
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The multi-hypergraph instance which will act as base class for the directed multi-graph.
     */
    htd::IMutableMultiHypergraph * base_;

    /**
     *  The information about incoming neighbors for each vertex.
     */
    std::vector<std::unordered_set<htd::vertex_t>> incomingNeighborhood_;

    /**
     *  The information about outgoing neighbors for each vertex.
     */
    std::vector<std::unordered_set<htd::vertex_t>> outgoingNeighborhood_;
};

htd::DirectedMultiGraph::DirectedMultiGraph(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager, manager->multiHypergraphFactory().createInstance()))
{

}

htd::DirectedMultiGraph::DirectedMultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : implementation_(new Implementation(manager, manager->multiHypergraphFactory().createInstance(initialSize)))
{

}

htd::DirectedMultiGraph::DirectedMultiGraph(const htd::DirectedMultiGraph & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::DirectedMultiGraph::DirectedMultiGraph(const htd::IDirectedMultiGraph & original) : implementation_(new Implementation(original.managementInstance(), original.managementInstance()->multiHypergraphFactory().createInstance()))
{
    *this = original;
}

htd::DirectedMultiGraph::~DirectedMultiGraph()
{

}

std::size_t htd::DirectedMultiGraph::vertexCount(void) const
{
    return implementation_->base_->vertexCount();
}

std::size_t htd::DirectedMultiGraph::edgeCount(void) const
{
    return implementation_->base_->edgeCount();
}

std::size_t htd::DirectedMultiGraph::edgeCount(htd::vertex_t vertex) const
{
    return implementation_->base_->edgeCount(vertex);
}

bool htd::DirectedMultiGraph::isVertex(htd::vertex_t vertex) const
{
    return implementation_->base_->isVertex(vertex);
}

bool htd::DirectedMultiGraph::isEdge(htd::id_t edgeId) const
{
    return implementation_->base_->isEdge(edgeId);
}

bool htd::DirectedMultiGraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->isEdge(vertex1, vertex2);
}

bool htd::DirectedMultiGraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return implementation_->base_->isEdge(elements);
}

bool htd::DirectedMultiGraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return implementation_->base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::DirectedMultiGraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::DirectedMultiGraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return implementation_->base_->associatedEdgeIds(elements);
}

htd::ConstCollection<htd::id_t> htd::DirectedMultiGraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return implementation_->base_->associatedEdgeIds(elements);
}

bool htd::DirectedMultiGraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return implementation_->base_->isNeighbor(vertex, neighbor);
}

bool htd::DirectedMultiGraph::isIncomingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(neighbor))
    
    return std::binary_search(implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST].begin(), implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST].end(), neighbor);
}

bool htd::DirectedMultiGraph::isOutgoingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(neighbor))

    return std::binary_search(implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST].begin(), implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST].end(), neighbor);
}

bool htd::DirectedMultiGraph::isConnected(void) const
{
    return implementation_->base_->isConnected();
}

bool htd::DirectedMultiGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->isConnected(vertex1, vertex2);
}

bool htd::DirectedMultiGraph::isReachable(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    HTD_ASSERT(isVertex(vertex1))
    HTD_ASSERT(isVertex(vertex2))

    bool ret = true;

    if (vertex1 != vertex2)
    {
        ret = false;

        std::vector<id_t> newVertices;
        std::vector<id_t> tmpVertices;

        std::vector<bool> reachableVertices(vertexCount());

        reachableVertices[vertex1] = true;

        newVertices.push_back(vertex1);

        while (newVertices.size() > 0)
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (std::vector<htd::vertex_t>::const_iterator it = tmpVertices.begin(); !ret && it != tmpVertices.end(); ++it)
            {
                for (std::unordered_set<htd::vertex_t>::const_iterator it2 = implementation_->outgoingNeighborhood_[*it - htd::Vertex::FIRST].begin(); !ret && it2 != implementation_->outgoingNeighborhood_[*it - htd::Vertex::FIRST].end(); ++it2)
                {
                    if (!reachableVertices[*it2 - htd::Vertex::FIRST])
                    {
                        reachableVertices[*it2 - htd::Vertex::FIRST] = true;

                        newVertices.push_back(*it2);

                        ret = *it2 == vertex2;
                    }
                }
            }
        }
    }
    
    return ret;
}

std::size_t htd::DirectedMultiGraph::neighborCount(htd::vertex_t vertex) const
{
    return implementation_->base_->neighborCount(vertex);
}

std::size_t htd::DirectedMultiGraph::incomingNeighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

std::size_t htd::DirectedMultiGraph::outgoingNeighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

htd::ConstCollection<htd::vertex_t> htd::DirectedMultiGraph::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->base_->neighbors(vertex);
}

void htd::DirectedMultiGraph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    implementation_->base_->copyNeighborsTo(vertex, target);
}

htd::vertex_t htd::DirectedMultiGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return implementation_->base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedMultiGraph::incomingNeighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & currentNeighborhood = implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedMultiGraph::outgoingNeighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & currentNeighborhood = implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::DirectedMultiGraph::incomingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & neighborhood = implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST];

    HTD_ASSERT(index < neighborhood.size())

    auto position = neighborhood.begin();

    std::advance(position, index);

    return *position;
}

htd::vertex_t htd::DirectedMultiGraph::outgoingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & neighborhood = implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

    HTD_ASSERT(index < neighborhood.size())

    auto position = neighborhood.begin();

    std::advance(position, index);

    return *position;
}

htd::ConstCollection<htd::vertex_t> htd::DirectedMultiGraph::vertices(void) const
{
    return implementation_->base_->vertices();
}

void htd::DirectedMultiGraph::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    implementation_->base_->copyVerticesTo(target);
}

htd::vertex_t htd::DirectedMultiGraph::vertexAtPosition(htd::index_t index) const
{
    return implementation_->base_->vertexAtPosition(index);
}

std::size_t htd::DirectedMultiGraph::isolatedVertexCount(void) const
{
    return implementation_->base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::DirectedMultiGraph::isolatedVertices(void) const
{
    return implementation_->base_->isolatedVertices();
}

htd::vertex_t htd::DirectedMultiGraph::isolatedVertexAtPosition(htd::index_t index) const
{
    return implementation_->base_->isolatedVertexAtPosition(index);
}

bool htd::DirectedMultiGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return implementation_->base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::Hyperedge> htd::DirectedMultiGraph::hyperedges(void) const
{
    return implementation_->base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::DirectedMultiGraph::hyperedges(htd::vertex_t vertex) const
{
    return implementation_->base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::DirectedMultiGraph::hyperedge(htd::id_t edgeId) const
{
    return implementation_->base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::DirectedMultiGraph::hyperedgeAtPosition(htd::index_t index) const
{
    return implementation_->base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::DirectedMultiGraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return implementation_->base_->hyperedgeAtPosition(index, vertex);
}

htd::FilteredHyperedgeCollection htd::DirectedMultiGraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return implementation_->base_->hyperedgesAtPositions(indices);
}

htd::FilteredHyperedgeCollection htd::DirectedMultiGraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return implementation_->base_->hyperedgesAtPositions(std::move(indices));
}

htd::vertex_t htd::DirectedMultiGraph::nextVertex(void) const
{
    return implementation_->base_->nextVertex();
}

htd::id_t htd::DirectedMultiGraph::nextEdgeId(void) const
{
    return implementation_->base_->nextEdgeId();
}

htd::vertex_t htd::DirectedMultiGraph::addVertex(void)
{
    htd::vertex_t ret = implementation_->base_->addVertex();

    implementation_->incomingNeighborhood_.emplace_back(std::unordered_set<htd::vertex_t>());
    implementation_->outgoingNeighborhood_.emplace_back(std::unordered_set<htd::vertex_t>());

    return ret;
}

htd::vertex_t htd::DirectedMultiGraph::addVertices(std::size_t count)
{
    htd::vertex_t ret = implementation_->base_->addVertices(count);

    implementation_->incomingNeighborhood_.resize(implementation_->incomingNeighborhood_.size() + count);
    implementation_->outgoingNeighborhood_.resize(implementation_->incomingNeighborhood_.size() + count);

    return ret;
}

void htd::DirectedMultiGraph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        for (auto incomingNeighbor : implementation_->incomingNeighborhood_[vertex - htd::Vertex::FIRST])
        {
            implementation_->outgoingNeighborhood_[incomingNeighbor - htd::Vertex::FIRST].erase(vertex);
        }
        
        for (auto outgoingNeighbor : implementation_->outgoingNeighborhood_[vertex - htd::Vertex::FIRST])
        {
            implementation_->incomingNeighborhood_[outgoingNeighbor - htd::Vertex::FIRST].erase(vertex);
        }

        implementation_->base_->removeVertex(vertex);

        std::vector<htd::id_t> erasableEdges;

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (edge.size() != 2)
            {
                erasableEdges.push_back(edge.id());
            }
        }

        for (htd::id_t id : erasableEdges)
        {
            removeEdge(id);
        }
    }
}

htd::id_t htd::DirectedMultiGraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(isVertex(vertex1))
    HTD_ASSERT(isVertex(vertex2))

    implementation_->outgoingNeighborhood_[vertex1 - htd::Vertex::FIRST].insert(vertex2);
    implementation_->incomingNeighborhood_[vertex2 - htd::Vertex::FIRST].insert(vertex1);

    return implementation_->base_->addEdge(vertex1, vertex2);
}

void htd::DirectedMultiGraph::removeEdge(htd::id_t edgeId)
{
    const htd::Hyperedge & selectedEdge = implementation_->base_->hyperedge(edgeId);

    htd::vertex_t vertex1 = selectedEdge[0];
    htd::vertex_t vertex2 = selectedEdge[1];

    implementation_->base_->removeEdge(edgeId);

    if (!implementation_->base_->isEdge(vertex1, vertex2))
    {
        implementation_->outgoingNeighborhood_[vertex1 - htd::Vertex::FIRST].erase(vertex2);
        implementation_->incomingNeighborhood_[vertex2 - htd::Vertex::FIRST].erase(vertex1);
    }
}

const htd::LibraryInstance * htd::DirectedMultiGraph::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->base_->managementInstance();
}

void htd::DirectedMultiGraph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    implementation_->base_->setManagementInstance(manager);
}

htd::DirectedMultiGraph * htd::DirectedMultiGraph::clone(void) const
{
    return new htd::DirectedMultiGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiGraph * htd::DirectedMultiGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::DirectedMultiGraph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::DirectedMultiGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IDirectedMultiGraph * htd::DirectedMultiGraph::cloneDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableDirectedMultiGraph * htd::DirectedMultiGraph::cloneMutableDirectedMultiGraph(void) const
{
    return clone();
}
#endif

htd::DirectedMultiGraph & htd::DirectedMultiGraph::operator=(const htd::DirectedMultiGraph & original)
{
    if (this != &original)
    {
        delete implementation_->base_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        implementation_->base_ = original.implementation_->base_->clone();
#else
        implementation_->base_ = original.implementation_->base_->cloneMutableMultiHypergraph();
#endif

        implementation_->incomingNeighborhood_ = original.implementation_->incomingNeighborhood_;
        implementation_->outgoingNeighborhood_ = original.implementation_->outgoingNeighborhood_;
    }

    return *this;
}

htd::DirectedMultiGraph & htd::DirectedMultiGraph::operator=(const htd::IDirectedMultiGraph & original)
{
    if (this != &original)
    {
        delete implementation_->base_;

        implementation_->base_ = implementation_->managementInstance_->multiHypergraphFactory().createInstance(original);

        implementation_->incomingNeighborhood_.clear();
        implementation_->outgoingNeighborhood_.clear();

        htd::vertex_t nextVertex = htd::Vertex::FIRST;

        for (htd::vertex_t vertex : original.vertices())
        {
            while (vertex > nextVertex)
            {
                implementation_->incomingNeighborhood_.emplace_back(std::unordered_set<htd::vertex_t>());
                implementation_->outgoingNeighborhood_.emplace_back(std::unordered_set<htd::vertex_t>());

                ++nextVertex;
            }

            const htd::ConstCollection<htd::vertex_t> & incomingNeighborCollection = original.incomingNeighbors(vertex);
            const htd::ConstCollection<htd::vertex_t> & outgoingNeighborCollection = original.incomingNeighbors(vertex);

            implementation_->incomingNeighborhood_.emplace_back(incomingNeighborCollection.begin(), incomingNeighborCollection.end());
            implementation_->outgoingNeighborhood_.emplace_back(outgoingNeighborCollection.begin(), outgoingNeighborCollection.end());
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::DirectedMultiGraph::assign(const htd::IDirectedMultiGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_DIRECTEDMULTIGRAPH_CPP */
