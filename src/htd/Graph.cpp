/* 
 * File:   Graph.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_GRAPH_CPP
#define	HTD_HTD_GRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Graph.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/Collection.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

htd::Graph::Graph(void) : base_(htd::HypergraphFactory::instance().getHypergraph())
{

}

htd::Graph::Graph(const htd::Graph & original) : base_(original.base_->clone())
{

}

htd::Graph::~Graph()
{
    if (base_ != nullptr)
    {
        delete base_;

        base_ = nullptr;
    }
}

std::size_t htd::Graph::vertexCount(void) const
{
    return base_->vertexCount();
}

std::size_t htd::Graph::edgeCount(void) const
{
    return base_->edgeCount();
}

std::size_t htd::Graph::edgeCount(htd::vertex_t vertex) const
{
    return base_->edgeCount(vertex);
}

bool htd::Graph::isVertex(htd::vertex_t vertex) const
{
    return base_->isVertex(vertex);
}

bool htd::Graph::isEdge(htd::id_t edgeId) const
{
    return base_->isEdge(edgeId);
}

bool htd::Graph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isEdge(vertex1, vertex2);
}

bool htd::Graph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    if (elements.size() == 2)
    {
        ret = base_->isEdge(elements);
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::Graph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
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

    return ret;
}

htd::ConstCollection<htd::id_t> htd::Graph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
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

    return ret;
}

htd::vertex_t htd::Graph::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}
            
bool htd::Graph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return base_->isNeighbor(vertex, neighbor);
}

bool htd::Graph::isConnected(void) const
{
    return base_->isConnected();
}

bool htd::Graph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isConnected(vertex1, vertex2);
}

std::size_t htd::Graph::neighborCount(htd::vertex_t vertex) const
{
    return base_->neighborCount(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::Graph::neighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Graph::neighbors(htd::vertex_t) const");
    }

    return base_->neighbors(vertex);
}

htd::vertex_t htd::Graph::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighbor(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::Graph::vertices(void) const
{
    return base_->vertices();
}

std::size_t htd::Graph::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::Graph::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::Graph::isolatedVertex(htd::index_t index) const
{
    return base_->isolatedVertex(index);
}

bool htd::Graph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::edge_t> htd::Graph::edges(void) const
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

    return ret;
}

htd::ConstCollection<htd::edge_t> htd::Graph::edges(htd::vertex_t vertex) const
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

    return ret;
}

const htd::edge_t & htd::Graph::edgeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges();

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::Graph::edgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::edge_t & htd::Graph::edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges(vertex);

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::Graph::edgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::ConstCollection<htd::Hyperedge> htd::Graph::hyperedges(void) const
{
    return base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::Graph::hyperedges(htd::vertex_t vertex) const
{
    return base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::Graph::hyperedge(htd::id_t edgeId) const
{
    return base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::Graph::hyperedgeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Graph::hyperedgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::Hyperedge & htd::Graph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges(vertex);

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Graph::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::Graph::addVertex(void)
{
    return base_->addVertex();
}

void htd::Graph::removeVertex(htd::vertex_t vertex)
{
    base_->removeVertex(vertex);
}

htd::id_t htd::Graph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    return base_->addEdge(vertex1, vertex2);
}

htd::id_t htd::Graph::addEdge(const htd::edge_t & edge)
{
    return base_->addEdge(edge.first, edge.second);
}

void htd::Graph::removeEdge(htd::id_t edgeId)
{
    base_->removeEdge(edgeId);
}

htd::Graph * htd::Graph::clone(void) const
{
    return new Graph(*this);
}

#endif /* HTD_HTD_GRAPH_CPP */
