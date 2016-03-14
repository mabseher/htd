/* 
 * File:   MultiGraph.cpp
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

#ifndef HTD_HTD_MULTIGRAPH_CPP
#define	HTD_HTD_MULTIGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiGraph.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

htd::MultiGraph::MultiGraph(void) : base_(htd::MultiHypergraphFactory::instance().getMultiHypergraph())
{

}

htd::MultiGraph::MultiGraph(std::size_t initialSize) : base_(htd::MultiHypergraphFactory::instance().getMultiHypergraph(initialSize))
{

}

htd::MultiGraph::MultiGraph(const htd::MultiGraph & original) : base_(original.base_->clone())
{

}

htd::MultiGraph::MultiGraph(const htd::IMultiGraph & original) : base_(htd::MultiHypergraphFactory::instance().getMultiHypergraph(original))
{

}

htd::MultiGraph::~MultiGraph()
{
    if (base_ != nullptr)
    {
        delete base_;

        base_ = nullptr;
    }
}

std::size_t htd::MultiGraph::vertexCount(void) const
{
    return base_->vertexCount();
}

std::size_t htd::MultiGraph::edgeCount(void) const
{
    return base_->edgeCount();
}

std::size_t htd::MultiGraph::edgeCount(htd::vertex_t vertex) const
{
    return base_->edgeCount(vertex);
}

bool htd::MultiGraph::isVertex(htd::vertex_t vertex) const
{
    return base_->isVertex(vertex);
}

bool htd::MultiGraph::isEdge(htd::id_t edgeId) const
{
    return base_->isEdge(edgeId);
}

bool htd::MultiGraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isEdge(vertex1, vertex2);
}

bool htd::MultiGraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::MultiGraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    if (elements.size() == 2)
    {
        ret = base_->isEdge(elements);
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge[0] == vertex1 && edge[1] == vertex2)
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return associatedEdgeIds(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (std::equal(edge.begin(), edge.end(), elements.begin()))
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (std::equal(edge.begin(), edge.end(), elements.begin()))
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::vertex_t htd::MultiGraph::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}
            
bool htd::MultiGraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return base_->isNeighbor(vertex, neighbor);
}

bool htd::MultiGraph::isConnected(void) const
{
    return base_->isConnected();
}

bool htd::MultiGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isConnected(vertex1, vertex2);
}

std::size_t htd::MultiGraph::neighborCount(htd::vertex_t vertex) const
{
    return base_->neighborCount(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::neighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::MultiGraph::neighbors(htd::vertex_t) const");
    }

    return base_->neighbors(vertex);
}

void htd::MultiGraph::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::MultiGraph::copyNeighborsTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }

    base_->copyNeighborsTo(target, vertex);
}

htd::vertex_t htd::MultiGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::vertices(void) const
{
    return base_->vertices();
}

std::size_t htd::MultiGraph::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::MultiGraph::isolatedVertexAtPosition(htd::index_t index) const
{
    return base_->isolatedVertexAtPosition(index);
}

bool htd::MultiGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::edge_t> htd::MultiGraph::edges(void) const
{
    htd::VectorAdapter<htd::edge_t> ret;

    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = base_->hyperedges();

    auto & result = ret.container();

    htd::vertex_t vertex1 = htd::Vertex::UNKNOWN;
    htd::vertex_t vertex2 = htd::Vertex::UNKNOWN;

    for (const htd::Hyperedge & hyperedge : hyperedgeCollection)
    {
        htd::edge_t edge;

        vertex1 = hyperedge[0];
        vertex2 = hyperedge[1];

        if (vertex1 < vertex2)
        {
            edge.first = vertex1;
            edge.second = vertex2;
        }
        else
        {
            edge.first = vertex2;
            edge.second = vertex1;
        }

        result.push_back(edge);
    }

    return htd::ConstCollection<htd::edge_t>::getInstance(ret);
}

htd::ConstCollection<htd::edge_t> htd::MultiGraph::edges(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::edge_t> ret;

    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = base_->hyperedges(vertex);

    auto & result = ret.container();

    htd::vertex_t vertex1 = htd::Vertex::UNKNOWN;
    htd::vertex_t vertex2 = htd::Vertex::UNKNOWN;

    for (const htd::Hyperedge & hyperedge : hyperedgeCollection)
    {
        htd::edge_t edge;

        vertex1 = hyperedge[0];
        vertex2 = hyperedge[1];

        if (vertex1 < vertex2)
        {
            edge.first = vertex1;
            edge.second = vertex2;
        }
        else
        {
            edge.first = vertex2;
            edge.second = vertex1;
        }

        result.push_back(edge);
    }

    return htd::ConstCollection<htd::edge_t>::getInstance(ret);
}

const htd::edge_t & htd::MultiGraph::edgeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges();

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::MultiGraph::edgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::edge_t & htd::MultiGraph::edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges(vertex);

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::MultiGraph::edgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::ConstCollection<htd::Hyperedge> htd::MultiGraph::hyperedges(void) const
{
    return base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::MultiGraph::hyperedges(htd::vertex_t vertex) const
{
    return base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::MultiGraph::hyperedge(htd::id_t edgeId) const
{
    return base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::MultiGraph::hyperedgeAtPosition(htd::index_t index) const
{
    return base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::MultiGraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->hyperedgeAtPosition(index, vertex);
}

htd::FilteredHyperedgeCollection htd::MultiGraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return base_->hyperedgesAtPositions(indices);
}

htd::vertex_t htd::MultiGraph::addVertex(void)
{
    return base_->addVertex();
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::addVertices(std::size_t count)
{
    return base_->addVertices(count);
}

void htd::MultiGraph::removeVertex(htd::vertex_t vertex)
{
    base_->removeVertex(vertex);
}

htd::id_t htd::MultiGraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    return base_->addEdge(vertex1, vertex2);
}

htd::id_t htd::MultiGraph::addEdge(const htd::edge_t & edge)
{
    return base_->addEdge(edge.first, edge.second);
}

void htd::MultiGraph::removeEdge(htd::id_t edgeId)
{
    base_->removeEdge(edgeId);
}

htd::MultiGraph * htd::MultiGraph::clone(void) const
{
    return new MultiGraph(*this);
}

htd::MultiGraph & htd::MultiGraph::operator=(const htd::MultiGraph & original)
{
    if (this != &original)
    {
        delete base_;

        base_ = original.base_->clone();
    }

    return *this;
}

htd::MultiGraph & htd::MultiGraph::operator=(const htd::IMultiGraph & original)
{
    if (this != &original)
    {
        delete base_;

        base_ = htd::MultiHypergraphFactory::instance().getMultiHypergraph(original);
    }

    return *this;
}

#endif /* HTD_HTD_MULTIGRAPH_CPP */
