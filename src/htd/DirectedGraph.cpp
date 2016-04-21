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
#define	HTD_HTD_DIRECTEDGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

htd::DirectedGraph::DirectedGraph(void) : base_(htd::HypergraphFactory::instance().getHypergraph()), incomingNeighborhood_(), outgoingNeighborhood_()
{

}

htd::DirectedGraph::DirectedGraph(std::size_t initialSize) : base_(htd::HypergraphFactory::instance().getHypergraph(initialSize)), incomingNeighborhood_(), outgoingNeighborhood_()
{

}

htd::DirectedGraph::DirectedGraph(const htd::DirectedGraph & original) : base_(original.base_->clone()), incomingNeighborhood_(original.incomingNeighborhood_), outgoingNeighborhood_(original.outgoingNeighborhood_)
{

}

htd::DirectedGraph::DirectedGraph(const htd::IDirectedGraph & original) : base_(htd::HypergraphFactory::instance().getHypergraph()), incomingNeighborhood_(), outgoingNeighborhood_()
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

htd::ConstCollection<htd::id_t> htd::DirectedGraph::associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const
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
    if (!isVertex(vertex) || !isVertex(neighbor))
    {
        throw std::out_of_range("bool htd::DirectedGraph::isIncomingNeighbor(htd::vertex_t, htd::vertex_t) const");
    }
    
    return std::binary_search(incomingNeighborhood_[vertex - htd::Vertex::FIRST].begin(), incomingNeighborhood_[vertex - htd::Vertex::FIRST].end(), neighbor);
}

bool htd::DirectedGraph::isOutgoingNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    if (!isVertex(vertex) || !isVertex(neighbor))
    {
        throw std::out_of_range("bool htd::DirectedGraph::isOutgoingNeighbor(htd::vertex_t, htd::vertex_t) const");
    }

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
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::out_of_range("bool htd::DirectedGraph::isReachable(htd::vertex_t, htd::vertex_t) const");
    }
    
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
    if (!isVertex(vertex))
    {
        throw std::logic_error("std::size_t htd::DirectedGraph::incomingNeighborCount(htd::vertex_t) const");
    }

    return incomingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

std::size_t htd::DirectedGraph::outgoingNeighborCount(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("std::size_t htd::DirectedGraph::outgoingNeighborCount(htd::vertex_t) const");
    }

    return outgoingNeighborhood_[vertex - htd::Vertex::FIRST].size();
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::neighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::neighbors(htd::vertex_t) const");
    }

    return base_->neighbors(vertex);
}

void htd::DirectedGraph::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::DirectedGraph::copyNeighborsTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }

    base_->copyNeighborsTo(target, vertex);
}

htd::vertex_t htd::DirectedGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::incomingNeighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::incomingNeighbors(htd::vertex_t) const");
    }

    auto & currentNeighborhood = incomingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::outgoingNeighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::outgoingNeighbors(htd::vertex_t) const");
    }

    auto & currentNeighborhood = outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

    htd::VectorAdapter<htd::vertex_t> ret(htd::ConstCollection<htd::vertex_t>(currentNeighborhood.begin(), currentNeighborhood.end()));

    auto & result = ret.container();

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::DirectedGraph::incomingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        auto & neighborhood = incomingNeighborhood_[vertex - htd::Vertex::FIRST];

        if (index < neighborhood.size())
        {
            auto position = neighborhood.begin();

            std::advance(position, index);

            ret = *position;
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::DirectedGraph::incomingNeighborAtPosition(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::DirectedGraph::incomingNeighborAtPosition(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

htd::vertex_t htd::DirectedGraph::outgoingNeighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{

    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        auto & neighborhood = outgoingNeighborhood_[vertex - htd::Vertex::FIRST];

        if (index < neighborhood.size())
        {
            auto position = neighborhood.begin();

            std::advance(position, index);

            ret = *position;
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::DirectedGraph::outgoingNeighborAtPosition(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::DirectedGraph::outgoingNeighborAtPosition(htd::vertex_t, htd::index_t) const");
    }

    return ret;
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
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges(vertex);

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::FilteredHyperedgeCollection htd::DirectedGraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return base_->hyperedgesAtPositions(indices);
}

htd::vertex_t htd::DirectedGraph::addVertex(void)
{
    htd::vertex_t ret = base_->addVertex();

    incomingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());
    outgoingNeighborhood_.push_back(std::unordered_set<htd::vertex_t>());

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::DirectedGraph::addVertices(std::size_t count)
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
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::logic_error("htd::id_t htd::DirectedGraph::addEdge(htd::vertex_t, htd::vertex_t)");
    }

    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(vertex1, vertex2);

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    outgoingNeighborhood_[vertex1 - htd::Vertex::FIRST].insert(vertex2);
    incomingNeighborhood_[vertex2 - htd::Vertex::FIRST].insert(vertex1);

    return base_->addEdge(vertex1, vertex2);
}

void htd::DirectedGraph::removeEdge(htd::id_t edgeId)
{
    const htd::Hyperedge & selectedEdge = base_->hyperedge(edgeId);

    htd::vertex_t vertex1 = selectedEdge[0];
    htd::vertex_t vertex2 = selectedEdge[1];

    base_->removeEdge(edgeId);

    if (!base_->isEdge(vertex1, vertex2))
    {
        outgoingNeighborhood_[vertex1].erase(vertex2);
        incomingNeighborhood_[vertex2].erase(vertex1);
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

htd::DirectedGraph * htd::DirectedGraph::clone(void) const
{
    return new DirectedGraph(*this);
}

htd::DirectedGraph & htd::DirectedGraph::operator=(const htd::DirectedGraph & original)
{
    if (this != &original)
    {
        delete base_;

        base_ = original.base_->clone();

        incomingNeighborhood_ = original.incomingNeighborhood_;
        outgoingNeighborhood_ = original.outgoingNeighborhood_;
    }

    return *this;
}

htd::DirectedGraph & htd::DirectedGraph::operator=(const htd::IDirectedGraph & original)
{
    if (this != &original)
    {
        delete base_;

        base_ = htd::HypergraphFactory::instance().getHypergraph(original);

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

htd::DirectedGraph & htd::DirectedGraph::operator=(const htd::IDirectedMultiGraph & original)
{
    delete base_;

    base_ = htd::HypergraphFactory::instance().getHypergraph(original);

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

    return *this;
}

#endif /* HTD_HTD_DIRECTEDGRAPH_CPP */
