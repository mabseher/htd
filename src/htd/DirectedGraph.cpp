/* 
 * File:   DirectedGraph.cpp
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

#ifndef HTD_HTD_DIRECTEDGRAPH_CPP
#define HTD_HTD_DIRECTEDGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

htd::DirectedGraph::DirectedGraph(const htd::LibraryInstance * const manager) : base_(manager->hypergraphFactory().createInstance()), incomingNeighborhood_(), outgoingNeighborhood_()
{

}

htd::DirectedGraph::DirectedGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : base_(manager->hypergraphFactory().createInstance(initialSize)), incomingNeighborhood_(), outgoingNeighborhood_()
{
    incomingNeighborhood_.resize(initialSize, std::unordered_set<htd::vertex_t>());
    outgoingNeighborhood_.resize(initialSize, std::unordered_set<htd::vertex_t>());
}

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::DirectedGraph::DirectedGraph(const htd::DirectedGraph & original) : base_(original.base_->clone()), incomingNeighborhood_(original.incomingNeighborhood_), outgoingNeighborhood_(original.outgoingNeighborhood_)
{

}
#else
htd::DirectedGraph::DirectedGraph(const htd::DirectedGraph & original) : base_(original.base_->cloneMutableHypergraph()), incomingNeighborhood_(original.incomingNeighborhood_), outgoingNeighborhood_(original.outgoingNeighborhood_)
{

}
#endif

htd::DirectedGraph::DirectedGraph(const htd::IDirectedGraph & original) : base_(original.managementInstance()->hypergraphFactory().createInstance()), incomingNeighborhood_(), outgoingNeighborhood_()
{
    *this = original;
}

htd::DirectedGraph::~DirectedGraph()
{
    if (base_ != nullptr)
    {
        delete base_;

        base_ = nullptr;
    }
}

std::size_t htd::DirectedGraph::vertexCount(void) const
{
    return base_->vertexCount();
}

std::size_t htd::DirectedGraph::edgeCount(void) const
{
    return base_->edgeCount();
}

std::size_t htd::DirectedGraph::edgeCount(htd::vertex_t vertex) const
{
    return base_->edgeCount(vertex);
}

bool htd::DirectedGraph::isVertex(htd::vertex_t vertex) const
{
    return base_->isVertex(vertex);
}

bool htd::DirectedGraph::isEdge(htd::id_t edgeId) const
{
    return base_->isEdge(edgeId);
}

bool htd::DirectedGraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isEdge(vertex1, vertex2);
}

bool htd::DirectedGraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

bool htd::DirectedGraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::DirectedGraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::DirectedGraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

htd::ConstCollection<htd::id_t> htd::DirectedGraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

htd::vertex_t htd::DirectedGraph::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}

bool htd::DirectedGraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return base_->isNeighbor(vertex, neighbor);
}

bool htd::DirectedGraph::isIncomingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(neighbor))
    
    return std::binary_search(incomingNeighborhood_[vertex - htd::Vertex::FIRST].begin(), incomingNeighborhood_[vertex - htd::Vertex::FIRST].end(), neighbor);
}

bool htd::DirectedGraph::isOutgoingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(neighbor))

    return std::binary_search(outgoingNeighborhood_[vertex - htd::Vertex::FIRST].begin(), outgoingNeighborhood_[vertex - htd::Vertex::FIRST].end(), neighbor);
}

bool htd::DirectedGraph::isConnected(void) const
{
    return base_->isConnected();
}

bool htd::DirectedGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isConnected(vertex1, vertex2);
}

bool htd::DirectedGraph::isReachable(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    HTD_ASSERT(vertex1)
    HTD_ASSERT(vertex2)
    
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
                for (std::unordered_set<htd::vertex_t>::const_iterator it2 = outgoingNeighborhood_[*it - htd::Vertex::FIRST].begin(); !ret && it2 != outgoingNeighborhood_[*it - htd::Vertex::FIRST].end(); ++it2)
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

std::size_t htd::DirectedGraph::neighborCount(htd::vertex_t vertex) const
{
    return base_->neighborCount(vertex);
}

std::size_t htd::DirectedGraph::incomingNeighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return incomingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

std::size_t htd::DirectedGraph::outgoingNeighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return outgoingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return base_->neighbors(vertex);
}

void htd::DirectedGraph::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    base_->copyNeighborsTo(target, vertex);
}

htd::vertex_t htd::DirectedGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::incomingNeighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & currentNeighborhood = incomingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::outgoingNeighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & currentNeighborhood = outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::DirectedGraph::incomingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & neighborhood = incomingNeighborhood_[vertex - htd::Vertex::FIRST];

    HTD_ASSERT(index < neighborhood.size())

    auto position = neighborhood.begin();

    std::advance(position, index);

    return *position;
}

htd::vertex_t htd::DirectedGraph::outgoingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    auto & neighborhood = outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

    HTD_ASSERT(index < neighborhood.size())

    auto position = neighborhood.begin();

    std::advance(position, index);

    return *position;
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::vertices(void) const
{
    return base_->vertices();
}

std::size_t htd::DirectedGraph::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::DirectedGraph::isolatedVertexAtPosition(htd::index_t index) const
{
    return base_->isolatedVertexAtPosition(index);
}

bool htd::DirectedGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::Hyperedge> htd::DirectedGraph::hyperedges(void) const
{
    return base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::DirectedGraph::hyperedges(htd::vertex_t vertex) const
{
    return base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::DirectedGraph::hyperedge(htd::id_t edgeId) const
{
    return base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t index) const
{
    return base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->hyperedgeAtPosition(index, vertex);
}

htd::FilteredHyperedgeCollection htd::DirectedGraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return base_->hyperedgesAtPositions(indices);
}

htd::FilteredHyperedgeCollection htd::DirectedGraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return base_->hyperedgesAtPositions(std::move(indices));
}

htd::vertex_t htd::DirectedGraph::nextVertex(void) const
{
    return base_->nextVertex();
}

htd::id_t htd::DirectedGraph::nextEdgeId(void) const
{
    return base_->nextEdgeId();
}

htd::vertex_t htd::DirectedGraph::addVertex(void)
{
    htd::vertex_t ret = base_->addVertex();

    incomingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());
    outgoingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());

    return ret;
}

htd::vertex_t htd::DirectedGraph::addVertices(std::size_t count)
{
    incomingNeighborhood_.resize(incomingNeighborhood_.size() + count, std::unordered_set<htd::vertex_t>());
    outgoingNeighborhood_.resize(outgoingNeighborhood_.size() + count, std::unordered_set<htd::vertex_t>());

    return base_->addVertices(count);
}

void htd::DirectedGraph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        for (auto incomingNeighbor : incomingNeighborhood_[vertex - htd::Vertex::FIRST])
        {
            outgoingNeighborhood_[incomingNeighbor - htd::Vertex::FIRST].erase(vertex);
        }
        
        for (auto outgoingNeighbor : outgoingNeighborhood_[vertex - htd::Vertex::FIRST])
        {
            incomingNeighborhood_[outgoingNeighbor - htd::Vertex::FIRST].erase(vertex);
        }

        base_->removeVertex(vertex);
    }
}

htd::id_t htd::DirectedGraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    std::size_t edgeCountBefore = edgeCount();

    htd::id_t ret = base_->addEdge(vertex1, vertex2);

    if (edgeCount() != edgeCountBefore)
    {
        outgoingNeighborhood_[vertex1 - htd::Vertex::FIRST].insert(vertex2);
        incomingNeighborhood_[vertex2 - htd::Vertex::FIRST].insert(vertex1);
    }

    return ret;
}

void htd::DirectedGraph::removeEdge(htd::id_t edgeId)
{
    const htd::Hyperedge & selectedEdge = base_->hyperedge(edgeId);

    htd::vertex_t vertex1 = selectedEdge[0];
    htd::vertex_t vertex2 = selectedEdge[1];

    base_->removeEdge(edgeId);

    if (!base_->isEdge(vertex1, vertex2))
    {
        outgoingNeighborhood_[vertex1 - htd::Vertex::FIRST].erase(vertex2);
        incomingNeighborhood_[vertex2 - htd::Vertex::FIRST].erase(vertex1);
    }
}

void htd::DirectedGraph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(vertex1, vertex2);

    if (associatedIds.size() > 0)
    {
        removeEdge(associatedIds[0]);
    }
}

const htd::LibraryInstance * htd::DirectedGraph::managementInstance(void) const HTD_NOEXCEPT
{
    return base_->managementInstance();
}

void htd::DirectedGraph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    base_->setManagementInstance(manager);
}

htd::DirectedGraph * htd::DirectedGraph::clone(void) const
{
    return new htd::DirectedGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraph * htd::DirectedGraph::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::DirectedGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::DirectedGraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IDirectedGraph * htd::DirectedGraph::cloneDirectedGraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::DirectedGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IDirectedMultiGraph * htd::DirectedGraph::cloneDirectedMultiGraph(void) const
{
    return clone();
}

htd::IMutableDirectedGraph * htd::DirectedGraph::cloneMutableDirectedGraph(void) const
{
    return clone();
}
#endif

htd::DirectedGraph & htd::DirectedGraph::operator=(const htd::DirectedGraph & original)
{
    if (this != &original)
    {
        delete base_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        base_ = original.base_->clone();
#else
        base_ = original.base_->cloneMutableHypergraph();
#endif

        incomingNeighborhood_ = original.incomingNeighborhood_;
        outgoingNeighborhood_ = original.outgoingNeighborhood_;
    }

    return *this;
}

htd::DirectedGraph & htd::DirectedGraph::operator=(const htd::IDirectedGraph & original)
{
    if (this != &original)
    {
        htd::IMutableHypergraph * newBase = base_->managementInstance()->hypergraphFactory().createInstance(original);

        delete base_;

        base_ = newBase;

        incomingNeighborhood_.clear();
        outgoingNeighborhood_.clear();

        htd::vertex_t nextVertex = htd::Vertex::FIRST;

        for (htd::vertex_t vertex : original.vertices())
        {
            while (vertex > nextVertex)
            {
                incomingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());
                outgoingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());

                ++nextVertex;
            }

            const htd::ConstCollection<htd::vertex_t> & incomingNeighborCollection = original.incomingNeighbors(vertex);
            const htd::ConstCollection<htd::vertex_t> & outgoingNeighborCollection = original.incomingNeighbors(vertex);

            incomingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>(incomingNeighborCollection.begin(), incomingNeighborCollection.end()));
            outgoingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>(outgoingNeighborCollection.begin(), outgoingNeighborCollection.end()));
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::DirectedGraph::assign(const htd::IDirectedGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_DIRECTEDGRAPH_CPP */
