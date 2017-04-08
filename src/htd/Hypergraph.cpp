/* 
 * File:   Hypergraph.cpp
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

#ifndef HTD_HTD_HYPERGRAPH_CPP
#define HTD_HTD_HYPERGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/MultiHypergraphFactory.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

htd::Hypergraph::Hypergraph(const htd::LibraryInstance * const manager) : base_(manager->multiHypergraphFactory().createInstance())
{

}

htd::Hypergraph::Hypergraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : base_(manager->multiHypergraphFactory().createInstance(initialSize))
{

}

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::Hypergraph::Hypergraph(const htd::Hypergraph & original) : base_(original.base_->clone())
{

}
#else
htd::Hypergraph::Hypergraph(const htd::Hypergraph & original) : base_(original.base_->cloneMutableMultiHypergraph())
{

}
#endif

htd::Hypergraph::Hypergraph(const htd::IHypergraph & original) : base_(original.managementInstance()->multiHypergraphFactory().createInstance(original))
{
    *this = original;
}

htd::Hypergraph::~Hypergraph()
{
    if (base_ != nullptr)
    {
        delete base_;

        base_ = nullptr;
    }
}

std::size_t htd::Hypergraph::vertexCount(void) const
{
    return base_->vertexCount();
}

std::size_t htd::Hypergraph::edgeCount(void) const
{
    return base_->edgeCount();
}

std::size_t htd::Hypergraph::edgeCount(htd::vertex_t vertex) const
{
    return base_->edgeCount(vertex);
}

bool htd::Hypergraph::isVertex(htd::vertex_t vertex) const
{
    return base_->isVertex(vertex);
}

bool htd::Hypergraph::isEdge(htd::id_t edgeId) const
{
    return base_->isEdge(edgeId);
}

bool htd::Hypergraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isEdge(vertex1, vertex2);
}

bool htd::Hypergraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

bool htd::Hypergraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::Hypergraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::Hypergraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

htd::ConstCollection<htd::id_t> htd::Hypergraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

bool htd::Hypergraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    return base_->isNeighbor(vertex, neighbor);
}

std::size_t htd::Hypergraph::neighborCount(htd::vertex_t vertex) const
{
    return base_->neighborCount(vertex);
}

bool htd::Hypergraph::isConnected(void) const
{
    return base_->isConnected();
}

bool htd::Hypergraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isConnected(vertex1, vertex2);
}

htd::ConstCollection<htd::vertex_t> htd::Hypergraph::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return base_->neighbors(vertex);
}

void htd::Hypergraph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    base_->copyNeighborsTo(vertex, target);
}

htd::vertex_t htd::Hypergraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighborAtPosition(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::Hypergraph::vertices(void) const
{
    return base_->vertices();
}

void htd::Hypergraph::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    base_->copyVerticesTo(target);
}

htd::vertex_t htd::Hypergraph::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}

std::size_t htd::Hypergraph::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::Hypergraph::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::Hypergraph::isolatedVertexAtPosition(htd::index_t index) const
{
    return base_->isolatedVertexAtPosition(index);
}

bool htd::Hypergraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    return base_->isIsolatedVertex(vertex);
}

htd::ConstCollection<htd::Hyperedge> htd::Hypergraph::hyperedges(void) const
{
    return base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::Hypergraph::hyperedges(htd::vertex_t vertex) const
{
    return base_->hyperedges(vertex);
}

htd::FilteredHyperedgeCollection htd::Hypergraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return base_->hyperedgesAtPositions(indices);
}

htd::FilteredHyperedgeCollection htd::Hypergraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return base_->hyperedgesAtPositions(std::move(indices));
}

const htd::Hyperedge & htd::Hypergraph::hyperedge(htd::id_t edgeId) const
{
    return base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::Hypergraph::hyperedgeAtPosition(htd::index_t index) const
{
    return base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::Hypergraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->hyperedgeAtPosition(index, vertex);
}

htd::vertex_t htd::Hypergraph::nextVertex(void) const
{
    return base_->nextVertex();
}

htd::id_t htd::Hypergraph::nextEdgeId(void) const
{
    return base_->nextEdgeId();
}

htd::vertex_t htd::Hypergraph::addVertex(void)
{
    return base_->addVertex();
}

htd::vertex_t htd::Hypergraph::addVertices(std::size_t count)
{
    return base_->addVertices(count);
}

void htd::Hypergraph::removeVertex(htd::vertex_t vertex)
{
    base_->removeVertex(vertex);
}

htd::id_t htd::Hypergraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isNeighbor(vertex1, vertex2))
    {
        const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(vertex1, vertex2);

        if (associatedIds.size() > 0)
        {
            return associatedIds[0];
        }
    }

    return base_->addEdge(vertex1, vertex2);
}

htd::id_t htd::Hypergraph::addEdge(const std::vector<htd::vertex_t> & elements)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(elements);

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    return base_->addEdge(elements);
}

htd::id_t htd::Hypergraph::addEdge(std::vector<htd::vertex_t> && elements)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(elements);

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    return base_->addEdge(std::move(elements));
}

htd::id_t htd::Hypergraph::addEdge(const htd::ConstCollection<htd::vertex_t> & elements)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(elements);

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    return base_->addEdge(elements);
}

htd::id_t htd::Hypergraph::addEdge(const htd::Hyperedge & hyperedge)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(hyperedge.elements());

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    return base_->addEdge(hyperedge);
}

htd::id_t htd::Hypergraph::addEdge(htd::Hyperedge && hyperedge)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(hyperedge.elements());

    if (associatedIds.size() > 0)
    {
        return associatedIds[0];
    }

    return base_->addEdge(std::move(hyperedge));
}

void htd::Hypergraph::removeEdge(htd::id_t edgeId)
{
    base_->removeEdge(edgeId);
}

void htd::Hypergraph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(vertex1, vertex2);

    if (associatedIds.size() > 0)
    {
        base_->removeEdge(associatedIds[0]);
    }
}

void htd::Hypergraph::removeEdge(const std::vector<htd::vertex_t> & elements)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(elements);

    if (associatedIds.size() > 0)
    {
        base_->removeEdge(associatedIds[0]);
    }
}

void htd::Hypergraph::removeEdge(const htd::ConstCollection<htd::vertex_t> & elements)
{
    const htd::ConstCollection<htd::id_t> & associatedIds = associatedEdgeIds(elements);

    if (associatedIds.size() > 0)
    {
        base_->removeEdge(associatedIds[0]);
    }
}

const htd::LibraryInstance * htd::Hypergraph::managementInstance(void) const HTD_NOEXCEPT
{
    return base_->managementInstance();
}

void htd::Hypergraph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    base_->setManagementInstance(manager);
}

htd::Hypergraph * htd::Hypergraph::clone(void) const
{
    return new htd::Hypergraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IHypergraph * htd::Hypergraph::cloneHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::Hypergraph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::Hypergraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableHypergraph * htd::Hypergraph::cloneMutableHypergraph(void) const
{
    return clone();
}
#endif

htd::Hypergraph & htd::Hypergraph::operator=(const htd::Hypergraph & original)
{
    if (this != &original)
    {
        delete base_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        base_ = original.base_->clone();
#else
        base_ = original.base_->cloneMutableMultiHypergraph();
#endif
    }

    return *this;
}

htd::Hypergraph & htd::Hypergraph::operator=(const htd::IHypergraph & original)
{
    if (this != &original)
    {
        htd::IMutableMultiHypergraph * newBase = managementInstance()->multiHypergraphFactory().createInstance(original);

        delete base_;

        base_ = newBase;
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::Hypergraph::assign(const htd::IHypergraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_HYPERGRAPH_CPP */
