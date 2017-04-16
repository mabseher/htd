/* 
 * File:   Graph.cpp
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

#ifndef HTD_HTD_GRAPH_CPP
#define HTD_HTD_GRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Graph.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

htd::Graph::Graph(const htd::LibraryInstance * const manager) : base_(manager->hypergraphFactory().createInstance())
{

}

htd::Graph::Graph(const htd::LibraryInstance * const manager, std::size_t initialSize) : base_(manager->hypergraphFactory().createInstance(initialSize))
{

}

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::Graph::Graph(const htd::Graph & original) : base_(original.base_->clone())
{

}
#else
htd::Graph::Graph(const htd::Graph & original) : base_(original.base_->cloneMutableHypergraph())
{

}
#endif

htd::Graph::Graph(const htd::IGraph & original) : base_(original.managementInstance()->hypergraphFactory().createInstance(original))
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

bool htd::Graph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

bool htd::Graph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::Graph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::Graph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

htd::ConstCollection<htd::id_t> htd::Graph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
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
    HTD_ASSERT(isVertex(vertex))

    return base_->neighbors(vertex);
}

void htd::Graph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    base_->copyNeighborsTo(vertex, target);
}

htd::vertex_t htd::Graph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::Graph::vertices(void) const
{
    return base_->vertices();
}

void htd::Graph::copyVerticesTo(std::vector<htd::vertex_t> &target) const
{
    base_->copyVerticesTo(target);
}

htd::vertex_t htd::Graph::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}

std::size_t htd::Graph::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::Graph::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::Graph::isolatedVertexAtPosition(htd::index_t index) const
{
    return base_->isolatedVertexAtPosition(index);
}

bool htd::Graph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return base_->isIsolatedVertex(vertex);
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
    return base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::Graph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->hyperedgeAtPosition(index, vertex);
}

htd::FilteredHyperedgeCollection htd::Graph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return base_->hyperedgesAtPositions(indices);
}

htd::FilteredHyperedgeCollection htd::Graph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return base_->hyperedgesAtPositions(std::move(indices));
}

htd::vertex_t htd::Graph::nextVertex(void) const
{
    return base_->nextVertex();
}

htd::id_t htd::Graph::nextEdgeId(void) const
{
    return base_->nextEdgeId();
}

htd::vertex_t htd::Graph::addVertex(void)
{
    return base_->addVertex();
}

htd::vertex_t htd::Graph::addVertices(std::size_t count)
{
    return base_->addVertices(count);
}

void htd::Graph::removeVertex(htd::vertex_t vertex)
{
    base_->removeVertex(vertex);

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

htd::id_t htd::Graph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    return base_->addEdge(vertex1, vertex2);
}

void htd::Graph::removeEdge(htd::id_t edgeId)
{
    base_->removeEdge(edgeId);
}

void htd::Graph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(vertex1, vertex2);

    if (associatedIds.size() > 0)
    {
        base_->removeEdge(associatedIds[0]);
    }
}

const htd::LibraryInstance * htd::Graph::managementInstance(void) const HTD_NOEXCEPT
{
    return base_->managementInstance();
}

void htd::Graph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    base_->setManagementInstance(manager);
}

htd::Graph * htd::Graph::clone(void) const
{
    return new htd::Graph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraph * htd::Graph::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::Graph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::Graph::cloneHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::Graph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::Graph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableGraph * htd::Graph::cloneMutableGraph(void) const
{
    return clone();
}
#endif

htd::Graph & htd::Graph::operator=(const htd::Graph & original)
{
    if (this != &original)
    {
        delete base_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        base_ = original.base_->clone();
#else
        base_ = original.base_->cloneMutableHypergraph();
#endif
    }

    return *this;
}

htd::Graph & htd::Graph::operator=(const htd::IGraph & original)
{
    if (this != &original)
    {
        htd::IMutableHypergraph * newBase = managementInstance()->hypergraphFactory().createInstance(original);

        delete base_;

        base_ = newBase;
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::Graph::assign(const htd::IGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_GRAPH_CPP */
