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
#include <htd/MultiGraph.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

/**
 *  Private implementation details of class htd::MultiGraph.
 */
struct htd::MultiGraph::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     *  @param[in] base     The multi-hypergraph instance which will act as base class for the multi-graph.
     */
    Implementation(const htd::LibraryInstance * const manager, htd::IMutableMultiHypergraph * base) : managementInstance_(manager), base_(base)
    {

    }

    virtual ~Implementation()
    {
        delete base_;
    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_)
    {
    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        base_ = original.base_->clone();
    #else
        base_ = original.base_->cloneMutableMultiHypergraph();
    #endif
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The multi-hypergraph instance which will act as base class for the multi-graph.
     */
    htd::IMutableMultiHypergraph * base_;
};

htd::MultiGraph::MultiGraph(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager, manager->multiHypergraphFactory().createInstance()))
{

}

htd::MultiGraph::MultiGraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : implementation_(new Implementation(manager, manager->multiHypergraphFactory().createInstance(initialSize)))
{

}

htd::MultiGraph::MultiGraph(const htd::MultiGraph & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::MultiGraph::MultiGraph(const htd::IMultiGraph & original) : implementation_(new Implementation(original.managementInstance(), original.managementInstance()->multiHypergraphFactory().createInstance(original)))
{

}

htd::MultiGraph::~MultiGraph()
{

}

std::size_t htd::MultiGraph::vertexCount(void) const
{
    return implementation_->base_->vertexCount();
}

std::size_t htd::MultiGraph::edgeCount(void) const
{
    return implementation_->base_->edgeCount();
}

std::size_t htd::MultiGraph::edgeCount(htd::vertex_t vertex) const
{
    return implementation_->base_->edgeCount(vertex);
}

bool htd::MultiGraph::isVertex(htd::vertex_t vertex) const
{
    return implementation_->base_->isVertex(vertex);
}

bool htd::MultiGraph::isEdge(htd::id_t edgeId) const
{
    return implementation_->base_->isEdge(edgeId);
}

bool htd::MultiGraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->isEdge(vertex1, vertex2);
}

bool htd::MultiGraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return implementation_->base_->isEdge(elements);
}

bool htd::MultiGraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return implementation_->base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return implementation_->base_->associatedEdgeIds(elements);
}

htd::ConstCollection<htd::id_t> htd::MultiGraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return implementation_->base_->associatedEdgeIds(elements);
}

bool htd::MultiGraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return implementation_->base_->isNeighbor(vertex, neighbor);
}

bool htd::MultiGraph::isConnected(void) const
{
    return implementation_->base_->isConnected();
}

bool htd::MultiGraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return implementation_->base_->isConnected(vertex1, vertex2);
}

std::size_t htd::MultiGraph::neighborCount(htd::vertex_t vertex) const
{
    return implementation_->base_->neighborCount(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::neighbors(htd::vertex_t vertex) const
{
    return implementation_->base_->neighbors(vertex);
}

void htd::MultiGraph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    implementation_->base_->copyNeighborsTo(vertex, target);
}

htd::vertex_t htd::MultiGraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return implementation_->base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::vertices(void) const
{
    return implementation_->base_->vertices();
}

void htd::MultiGraph::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    implementation_->base_->copyVerticesTo(target);
}

htd::vertex_t htd::MultiGraph::vertexAtPosition(htd::index_t index) const
{
    return implementation_->base_->vertexAtPosition(index);
}

std::size_t htd::MultiGraph::isolatedVertexCount(void) const
{
    return implementation_->base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::MultiGraph::isolatedVertices(void) const
{
    return implementation_->base_->isolatedVertices();
}

htd::vertex_t htd::MultiGraph::isolatedVertexAtPosition(htd::index_t index) const
{
    return implementation_->base_->isolatedVertexAtPosition(index);
}

bool htd::MultiGraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return implementation_->base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::Hyperedge> htd::MultiGraph::hyperedges(void) const
{
    return implementation_->base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::MultiGraph::hyperedges(htd::vertex_t vertex) const
{
    return implementation_->base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::MultiGraph::hyperedge(htd::id_t edgeId) const
{
    return implementation_->base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::MultiGraph::hyperedgeAtPosition(htd::index_t index) const
{
    return implementation_->base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::MultiGraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return implementation_->base_->hyperedgeAtPosition(index, vertex);
}

htd::FilteredHyperedgeCollection htd::MultiGraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return implementation_->base_->hyperedgesAtPositions(indices);
}

htd::FilteredHyperedgeCollection htd::MultiGraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return implementation_->base_->hyperedgesAtPositions(std::move(indices));
}

htd::vertex_t htd::MultiGraph::nextVertex(void) const
{
    return implementation_->base_->nextVertex();
}

htd::id_t htd::MultiGraph::nextEdgeId(void) const
{
    return implementation_->base_->nextEdgeId();
}

htd::vertex_t htd::MultiGraph::addVertex(void)
{
    return implementation_->base_->addVertex();
}

htd::vertex_t htd::MultiGraph::addVertices(std::size_t count)
{
    return implementation_->base_->addVertices(count);
}

void htd::MultiGraph::removeVertex(htd::vertex_t vertex)
{
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

htd::id_t htd::MultiGraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    return implementation_->base_->addEdge(vertex1, vertex2);
}

void htd::MultiGraph::removeEdge(htd::id_t edgeId)
{
    implementation_->base_->removeEdge(edgeId);
}

const htd::LibraryInstance * htd::MultiGraph::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->base_->managementInstance();
}

void htd::MultiGraph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    implementation_->base_->setManagementInstance(manager);
}

htd::MultiGraph * htd::MultiGraph::clone(void) const
{
    return new htd::MultiGraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IMultiGraph * htd::MultiGraph::cloneMultiGraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::MultiGraph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::MultiGraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableMultiGraph * htd::MultiGraph::cloneMutableMultiGraph(void) const
{
    return clone();
}
#endif

htd::MultiGraph & htd::MultiGraph::operator=(const htd::MultiGraph & original)
{
    if (this != &original)
    {
        delete implementation_->base_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        implementation_->base_ = original.implementation_->base_->clone();
#else
        implementation_->base_ = original.implementation_->base_->cloneMutableMultiHypergraph();
#endif
    }

    return *this;
}

htd::MultiGraph & htd::MultiGraph::operator=(const htd::IMultiGraph & original)
{
    if (this != &original)
    {
        delete implementation_->base_;

        implementation_->base_ = implementation_->managementInstance_->multiHypergraphFactory().createInstance(original);
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::MultiGraph::assign(const htd::IMultiGraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_MULTIGRAPH_CPP */
