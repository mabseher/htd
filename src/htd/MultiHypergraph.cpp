/* 
 * File:   MultiHypergraph.cpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPH_CPP
#define HTD_HTD_MULTIHYPERGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiHypergraph.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/HyperedgeDeque.hpp>

#include <htd/Algorithm.hpp>

#include <algorithm>
#include <array>
#include <deque>
#include <iterator>
#include <stack>
#include <unordered_set>
#include <vector>

/**
 *  Private implementation details of class htd::MultiHypergraph.
 */
struct htd::MultiHypergraph::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager)
        : managementInstance_(manager),
          size_(0),
          next_edge_(htd::Id::FIRST),
          next_vertex_(htd::Vertex::FIRST),
          vertices_(),
          selfLoops_(),
          deletions_(),
          edges_(std::make_shared<std::deque<htd::Hyperedge>>()),
          neighborhood_()
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original)
        : managementInstance_(original.managementInstance_),
          size_(original.size_),
          next_edge_(original.next_edge_),
          next_vertex_(original.next_vertex_),
          vertices_(original.vertices_),
          selfLoops_(original.selfLoops_),
          deletions_(original.deletions_),
          edges_(std::make_shared<std::deque<htd::Hyperedge>>(*(original.edges_))),
          neighborhood_(original.neighborhood_)
    {

    }

    /**
     *  Reset the multi-hypergraph to an empty one.
     */
    void reset(void)
    {
        size_ = 0;

        next_edge_ = htd::Id::FIRST;

        next_vertex_ = htd::Vertex::FIRST;

        vertices_.clear();

        selfLoops_.clear();

        deletions_.clear();

        edges_->clear();

        neighborhood_.clear();
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The number of vertices of the multi-hypergraph.
     */
    std::size_t size_;

    /**
     *  The ID the next edge added to the graph will get.
     */
    htd::id_t next_edge_;

    /**
     *  The ID the next vertex added to the graph will get.
     */
    htd::vertex_t next_vertex_;

    /**
     *  The vector of all vertices in the graph sorted in ascending order.
     */
    std::vector<htd::vertex_t> vertices_;

    /**
     *  The set of vertices which have self-loops.
     */
    std::unordered_set<htd::vertex_t> selfLoops_;

    /**
     *  The set of vertices which were removed from the graph.
     */
    std::unordered_set<htd::vertex_t> deletions_;

    /**
     *  The collection of hyperedges sorted by ID in ascending order.
     */
    std::shared_ptr<std::deque<htd::Hyperedge>> edges_;

    /**
     *  The vector of neighbors for each vertex in the hypergraph. The neighborhood of each vertex is sorted in ascending order.
     */
    std::vector<std::vector<htd::vertex_t>> neighborhood_;
};

htd::MultiHypergraph::MultiHypergraph(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::MultiHypergraph::MultiHypergraph(const htd::LibraryInstance * const manager, std::size_t initialSize) : implementation_(new Implementation(manager))
{
    addVertices(initialSize);
}

htd::MultiHypergraph::MultiHypergraph(const htd::MultiHypergraph & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::MultiHypergraph::MultiHypergraph(const htd::IMultiHypergraph & original) : implementation_(new Implementation(original.managementInstance()))
{
    *this = original;
}

htd::MultiHypergraph::~MultiHypergraph()
{

}

std::size_t htd::MultiHypergraph::vertexCount(void) const
{
    return implementation_->size_;
}

std::size_t htd::MultiHypergraph::edgeCount(void) const
{
    return implementation_->edges_->size();
}

std::size_t htd::MultiHypergraph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    HTD_ASSERT(isVertex(vertex))

    for (const htd::Hyperedge & edge : *(implementation_->edges_))
    {
        if (edge.contains(vertex))
        {
            ret++;
        }
    }

    return ret;
}

bool htd::MultiHypergraph::isVertex(htd::vertex_t vertex) const
{
    return vertex < implementation_->next_vertex_ && vertex != htd::Vertex::UNKNOWN && implementation_->deletions_.count(vertex) == 0;
}

bool htd::MultiHypergraph::isEdge(htd::id_t edgeId) const
{
    bool ret = false;

    for (auto it = implementation_->edges_->begin(); !ret && it != implementation_->edges_->end(); ++it)
    {
        ret = (it->id() == edgeId);
    }

    return ret;
}

bool htd::MultiHypergraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isNeighbor(vertex1, vertex2) && isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(std::vector<htd::vertex_t> { vertex1, vertex2 }));
}

bool htd::MultiHypergraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::MultiHypergraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    for (auto it = implementation_->edges_->begin(); !ret && it != implementation_->edges_->end(); ++it)
    {
        ret = it->size() == elements.size() && htd::equal(it->begin(), it->end(), elements.begin(), elements.end());
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (isNeighbor(vertex1, vertex2))
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (edge.size() == 2 && edge[0] == vertex1 && edge[1] == vertex2)
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge.size() == elements.size() && htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge.size() == elements.size() && htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

bool htd::MultiHypergraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

    bool ret = false;

    if (vertex != neighbor)
    {
        const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

        ret = std::binary_search(currentNeighborhood.begin(), currentNeighborhood.end(), neighbor);
    }
    else
    {
        for (auto it = implementation_->edges_->begin(); !ret && it != implementation_->edges_->end(); ++it)
        {
            const htd::Hyperedge & edge = *it;

            if (std::count_if(edge.begin(), edge.end(), [&](htd::vertex_t element) { return element == vertex; }) >= 2)
            {
                ret = true;
            }
        }
    }
    
    return ret;
}

std::size_t htd::MultiHypergraph::neighborCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->neighborhood_[vertex - htd::Vertex::FIRST].size();
}

bool htd::MultiHypergraph::isConnected(void) const
{
    bool ret = true;
    
    if (implementation_->size_ > 0)
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = implementation_->vertices_[0];

        originStack.push(currentVertex);

        while (!originStack.empty())
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : implementation_->neighborhood_[currentVertex - htd::Vertex::FIRST])
                {
                    if (visitedVertices.count(neighbor) == 0)
                    {
                        originStack.push(neighbor);
                    }
                }
            }
            else
            {
                originStack.pop();
            }
        }

        ret = visitedVertices.size() == implementation_->vertices_.size();
    }
    else
    {
        ret = true;
    }
    
    return ret;
}

bool htd::MultiHypergraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

    bool ret = false;

    if (vertex1 == vertex2)
    {
        ret = true;
    }
    else
    {
        std::vector<htd::vertex_t> newVertices;
        std::vector<htd::vertex_t> tmpVertices;

        std::vector<bool> reachableVertices(implementation_->size_);

        reachableVertices[vertex1 - htd::Vertex::FIRST] = true;

        newVertices.push_back(vertex1);

        while (!ret && !newVertices.empty())
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (auto it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
            {
                htd::vertex_t vertex = *it;

                const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

                for (auto it2 = currentNeighborhood.begin(); !ret && it2 != currentNeighborhood.end(); ++it2)
                {
                    htd::vertex_t neighbor = *it2;

                    if (neighbor != vertex && !reachableVertices[neighbor - htd::Vertex::FIRST])
                    {
                        reachableVertices[neighbor - htd::Vertex::FIRST] = true;

                        newVertices.push_back(neighbor);

                        if (neighbor == vertex2)
                        {
                            ret = true;
                        }
                    }
                }
            }
        }
    }
    
    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->neighborhood_[vertex - htd::Vertex::FIRST]);
}

void htd::MultiHypergraph::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

    target.insert(target.end(), currentNeighborhood.begin(), currentNeighborhood.end());
}

htd::vertex_t htd::MultiHypergraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

    HTD_ASSERT(index < currentNeighborhood.size())

    return currentNeighborhood[index];
}

htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->vertices_);
}

void htd::MultiHypergraph::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    target.insert(target.end(),
                  implementation_->vertices_.begin(),
                  implementation_->vertices_.end());
}

htd::vertex_t htd::MultiHypergraph::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->vertices_.size())

    return implementation_->vertices_[index];
}

const std::vector<htd::vertex_t> & htd::MultiHypergraph::vertexVector(void) const
{
    return implementation_->vertices_;
}

std::size_t htd::MultiHypergraph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : implementation_->vertices_)
    {
        if (implementation_->neighborhood_[vertex - htd::Vertex::FIRST].empty())
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::isolatedVertices(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (htd::vertex_t vertex : implementation_->vertices_)
    {
        bool isolated = true;

        for (auto it = implementation_->edges_->begin(); isolated && it != implementation_->edges_->end(); it++)
        {
            isolated = (*it).size() <= 1 || std::find((*it).begin(), (*it).end(), vertex) == (*it).end();
        }

        if (isolated)
        {
            result.push_back(vertex);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::MultiHypergraph::isolatedVertexAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

    HTD_ASSERT(index < isolatedVertexCollection.size())

    htd::ConstIterator<htd::vertex_t> it = isolatedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::MultiHypergraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    bool ret = true;

    for (auto it = implementation_->edges_->begin(); ret && it != implementation_->edges_->end(); it++)
    {
        ret = (*it).size() <= 1 || std::find((*it).begin(), (*it).end(), vertex) == (*it).end();
    }

    return ret;
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>::getInstance(*(implementation_->edges_));
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    for (auto & edge : *(implementation_->edges_))
    {
        if (edge.contains(vertex))
        {
            result.push_back(edge);
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedge(htd::id_t edgeId) const
{
    bool found = false;

    auto position = implementation_->edges_->begin();

    for (auto it = implementation_->edges_->begin(); !found && it != implementation_->edges_->end(); ++it)
    {
        if (it->id() == edgeId)
        {
            position = it;

            found = true;
        }
    }

    HTD_ASSERT(found)

    return *position;
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->edges_->size())

    return implementation_->edges_->at(index);
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    for (auto it = implementation_->edges_->begin(); it != implementation_->edges_->end(); ++it)
    {
        const htd::Hyperedge & hyperedge = *it;

        if (hyperedge.contains(vertex))
        {
            if (index == 0)
            {
                return hyperedge;
            }

            --index;
        }
    }

    throw std::out_of_range("const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
}

htd::FilteredHyperedgeCollection htd::MultiHypergraph::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    return htd::FilteredHyperedgeCollection(new htd::HyperedgeDeque(implementation_->edges_), indices);
}

htd::FilteredHyperedgeCollection htd::MultiHypergraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return htd::FilteredHyperedgeCollection(new htd::HyperedgeDeque(implementation_->edges_), std::move(indices));
}

htd::vertex_t htd::MultiHypergraph::nextVertex(void) const
{
    return implementation_->next_vertex_;
}

htd::id_t htd::MultiHypergraph::nextEdgeId(void) const
{
    return implementation_->next_edge_;
}

htd::vertex_t htd::MultiHypergraph::addVertex(void)
{
    htd::vertex_t ret = implementation_->next_vertex_;
    
    implementation_->size_++;

    implementation_->next_vertex_++;

    implementation_->neighborhood_.emplace_back(std::vector<htd::vertex_t>());

    implementation_->vertices_.push_back(ret);

    return ret;
}

htd::vertex_t htd::MultiHypergraph::addVertices(std::size_t count)
{
    htd::vertex_t ret = implementation_->next_vertex_;

    if (count > 0)
    {
        std::size_t previousSize = implementation_->vertices_.size();

        implementation_->vertices_.resize(previousSize + count, 0);

        for (htd::index_t index = 0; index < count; ++index)
        {
            implementation_->vertices_[previousSize + index + 1 - htd::Vertex::FIRST] = implementation_->next_vertex_;

            ++(implementation_->next_vertex_);
        }

        implementation_->neighborhood_.resize(implementation_->neighborhood_.size() + count, std::vector<htd::vertex_t>());

        implementation_->size_ += count;
    }
    else
    {
        --ret;
    }

    return ret;
}

void htd::MultiHypergraph::removeVertex(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::index_t currentIndex = 0;

    std::vector<htd::index_t> emptyEdges;

    for (auto & edge : *(implementation_->edges_))
    {
        edge.erase(vertex);

        if (edge.empty())
        {
            emptyEdges.push_back(currentIndex);
        }

        ++currentIndex;
    }

    for (auto it = emptyEdges.rbegin(); it != emptyEdges.rend(); ++it)
    {
        implementation_->edges_->erase(implementation_->edges_->begin() + *it);
    }

    implementation_->selfLoops_.erase(vertex);

    implementation_->deletions_.insert(vertex);

    for (htd::vertex_t neighbor : implementation_->neighborhood_[vertex - htd::Vertex::FIRST])
    {
        if (neighbor != vertex)
        {
            auto & currentNeighborhood = implementation_->neighborhood_[neighbor - htd::Vertex::FIRST];

            /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'currentNeighborhood'. */
            // coverity[use_iterator]
            currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex));
        }
    }

    implementation_->neighborhood_[vertex - htd::Vertex::FIRST].clear();

    implementation_->vertices_.erase(std::lower_bound(implementation_->vertices_.begin(), implementation_->vertices_.end(), vertex));

    --(implementation_->size_);
}

htd::id_t htd::MultiHypergraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

    implementation_->edges_->emplace_back(implementation_->next_edge_, vertex1, vertex2);

    if (vertex1 != vertex2)
    {
        std::vector<htd::vertex_t> & currentNeighborhood1 = implementation_->neighborhood_[vertex1 - htd::Vertex::FIRST];

        auto position = std::lower_bound(currentNeighborhood1.begin(), currentNeighborhood1.end(), vertex2);

        if (position == currentNeighborhood1.end() || *position != vertex2)
        {
            currentNeighborhood1.insert(position, vertex2);

            std::vector<htd::vertex_t> & currentNeighborhood2 = implementation_->neighborhood_[vertex2 - htd::Vertex::FIRST];

            currentNeighborhood2.insert(std::lower_bound(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex1), vertex1);
        }
    }
    else
    {
        std::vector<htd::vertex_t> & currentNeighborhood1 = implementation_->neighborhood_[vertex1 - htd::Vertex::FIRST];

        auto position = std::lower_bound(currentNeighborhood1.begin(), currentNeighborhood1.end(), vertex1);

        if (position == currentNeighborhood1.end() || *position != vertex1)
        {
            currentNeighborhood1.insert(position, vertex1);
        }

        implementation_->selfLoops_.insert(vertex1);
    }

    return implementation_->next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(const std::vector<htd::vertex_t> & elements)
{
    return addEdge(std::vector<htd::vertex_t>(elements));
}

htd::id_t htd::MultiHypergraph::addEdge(std::vector<htd::vertex_t> && elements)
{
    HTD_ASSERT(!elements.empty())

    switch (elements.size())
    {
        case 1:
        {
            HTD_ASSERT(isVertex(elements[0]))

            implementation_->edges_->emplace_back(implementation_->next_edge_, elements[0]);

            return implementation_->next_edge_++;
        }
        case 2:
        {
            return addEdge(elements[0], elements[1]);
        }
        default:
        {
            break;
        }
    }

    #ifndef NDEBUG
    for (htd::vertex_t vertex : elements)
    {
        HTD_ASSERT(isVertex(vertex))
    }
    #endif

    std::vector<htd::vertex_t> sortedElements(elements);

    auto elementsBegin = sortedElements.begin();
    auto elementsEnd = sortedElements.end();

    std::sort(elementsBegin, elementsEnd);

    auto position = std::unique(elementsBegin, elementsEnd);

    implementation_->selfLoops_.insert(position, elementsEnd);

    elementsEnd = sortedElements.erase(position, elementsEnd);

    for (htd::vertex_t vertex : sortedElements)
    {
        std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

        std::vector<htd::vertex_t> tmp;
        tmp.reserve(sortedElements.size());

        std::set_difference(elementsBegin, elementsEnd,
                            currentNeighborhood.begin(), currentNeighborhood.end(), std::back_inserter(tmp));

        if (!tmp.empty())
        {
            if (implementation_->selfLoops_.count(vertex) == 0)
            {
                /* Because 'vertex' does not have any self-loops, the set difference between the
                 * endpoints of the hyperedge and the neighborhood of 'vertex' always contains
                 * 'vertex'. */
                // coverity[use_iterator]
                tmp.erase(std::lower_bound(tmp.begin(), tmp.end(), vertex));
            }

            if (!tmp.empty())
            {
                htd::inplace_merge(currentNeighborhood, tmp);
            }
        }
    }

    implementation_->edges_->emplace_back(implementation_->next_edge_, std::move(elements), std::move(sortedElements));

    return implementation_->next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(const htd::ConstCollection<htd::vertex_t> & elements)
{
    return addEdge(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
}

htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge & hyperedge)
{
    HTD_ASSERT(!hyperedge.empty())

    switch (hyperedge.size())
    {
        case 1:
        {
            HTD_ASSERT(isVertex(hyperedge[0]))

            implementation_->edges_->emplace_back(implementation_->next_edge_, hyperedge.elements());

            return implementation_->next_edge_++;
        }
        case 2:
        {
            return addEdge(hyperedge[0], hyperedge[1]);
        }
        default:
        {
            break;
        }
    }

    for (htd::vertex_t vertex : hyperedge.elements())
    {
        HTD_UNUSED(vertex)

        HTD_ASSERT(isVertex(vertex));
    }

    implementation_->edges_->emplace_back(implementation_->next_edge_, hyperedge.elements());

    std::vector<htd::vertex_t> sortedElements(hyperedge.begin(), hyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    auto position = std::unique(sortedElements.begin(), sortedElements.end());

    for (auto it = position; it != sortedElements.end(); it++)
    {
        implementation_->selfLoops_.insert(*it);
    }

    sortedElements.erase(position, sortedElements.end());

    std::vector<htd::vertex_t> newNeighborhood;

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

        if (implementation_->selfLoops_.count(vertex) > 0)
        {
            htd::set_union(currentNeighborhood, sortedElements, newNeighborhood);
        }
        else
        {
            htd::set_union(currentNeighborhood, sortedElements, vertex, newNeighborhood);
        }

        currentNeighborhood.swap(newNeighborhood);

        newNeighborhood.clear();
    }

    return implementation_->next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge && hyperedge)
{
    HTD_ASSERT(!hyperedge.empty())

    switch (hyperedge.size())
    {
        case 1:
        {
            HTD_ASSERT(isVertex(hyperedge[0]))

            hyperedge.setId(implementation_->next_edge_);

            implementation_->edges_->emplace_back(std::move(hyperedge));

            return implementation_->next_edge_++;
        }
        case 2:
        {
            return addEdge(hyperedge[0], hyperedge[1]);
        }
        default:
        {
            break;
        }
    }

    for (htd::vertex_t vertex : hyperedge.elements())
    {
        HTD_UNUSED(vertex)

        HTD_ASSERT(isVertex(vertex));
    }

    htd::Hyperedge newHyperedge(std::move(hyperedge));

    newHyperedge.setId(implementation_->next_edge_);

    implementation_->edges_->emplace_back(newHyperedge);

    std::vector<htd::vertex_t> sortedElements(newHyperedge.begin(), newHyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    auto position = std::unique(sortedElements.begin(), sortedElements.end());

    for (auto it = position; it != sortedElements.end(); it++)
    {
        implementation_->selfLoops_.insert(*it);
    }

    sortedElements.erase(position, sortedElements.end());

    std::vector<htd::vertex_t> newNeighborhood;

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

        if (implementation_->selfLoops_.count(vertex) > 0)
        {
            htd::set_union(currentNeighborhood, sortedElements, newNeighborhood);
        }
        else
        {
            htd::set_union(currentNeighborhood, sortedElements, vertex, newNeighborhood);
        }

        currentNeighborhood.swap(newNeighborhood);

        newNeighborhood.clear();
    }

    return implementation_->next_edge_++;
}

void htd::MultiHypergraph::removeEdge(htd::id_t edgeId)
{
    bool found = false;

    auto position = implementation_->edges_->begin();

    for (auto it = implementation_->edges_->begin(); !found && it != implementation_->edges_->end(); ++it)
    {
        if (it->id() == edgeId)
        {
            position = it;

            found = true;
        }
    }

    if (found)
    {
        const htd::Hyperedge & hyperedge = *position;

        for (htd::vertex_t vertex : hyperedge)
        {
            std::unordered_set<htd::vertex_t> missing(hyperedge.begin(), hyperedge.end());

            bool selfLoopExists = false;

            for (auto it = implementation_->edges_->begin(); !missing.empty() && it != implementation_->edges_->end(); it++)
            {
                htd::Hyperedge & currentEdge = *it;

                if (it != position && currentEdge.contains(vertex))
                {
                    std::size_t occurrences = 0;

                    for (htd::vertex_t vertex2 : currentEdge)
                    {
                        missing.erase(vertex2);

                        if (vertex2 == vertex)
                        {
                            ++occurrences;
                        }
                    }

                    selfLoopExists = occurrences > 1;
                }
            }

            if (!missing.empty())
            {
                std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

                for (auto it = missing.begin(); it != missing.end(); it++)
                {
                    auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), *it);

                    if (position2 != currentNeighborhood.end())
                    {
                        /* Iterator 'position2' is no longer used after erasing the underlying element. Therefore, invalidating the iterator does no harm. */
                        // coverity[use_iterator]
                        currentNeighborhood.erase(position2);
                    }
                }
            }

            if (implementation_->selfLoops_.count(vertex) > 0 && !selfLoopExists)
            {
                std::vector<htd::vertex_t> & currentNeighborhood = implementation_->neighborhood_[vertex - htd::Vertex::FIRST];

                auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

                if (position2 != currentNeighborhood.end())
                {
                    /* Iterator 'position2' is no longer used after erasing the underlying element. Therefore, invalidating the iterator does no harm. */
                    // coverity[use_iterator]
                    currentNeighborhood.erase(position2);
                }

                implementation_->selfLoops_.erase(vertex);
            }
        }

        implementation_->edges_->erase(position);
    }
}

const htd::LibraryInstance * htd::MultiHypergraph::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::MultiHypergraph::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::MultiHypergraph * htd::MultiHypergraph::clone(void) const
{
    return new htd::MultiHypergraph(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IGraphStructure * htd::MultiHypergraph::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::MultiHypergraph::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableMultiHypergraph * htd::MultiHypergraph::cloneMutableMultiHypergraph(void) const
{
    return clone();
}
#endif

htd::MultiHypergraph & htd::MultiHypergraph::operator=(const htd::MultiHypergraph & original)
{
    if (this != &original)
    {
        *implementation_ = *(original.implementation_);
    }

    return *this;
}

htd::MultiHypergraph & htd::MultiHypergraph::operator=(const htd::IMultiHypergraph & original)
{
    if (this != &original)
    {
        implementation_->reset();

        for (htd::vertex_t vertex : original.vertices())
        {
            while (vertex > implementation_->next_vertex_)
            {
                implementation_->deletions_.insert(implementation_->next_vertex_);

                implementation_->neighborhood_.emplace_back(std::vector<htd::vertex_t>());

                ++(implementation_->next_vertex_);
            }

            implementation_->size_++;

            implementation_->next_vertex_++;

            implementation_->neighborhood_.emplace_back(std::vector<htd::vertex_t>());

            implementation_->vertices_.push_back(vertex);
        }

        for (const htd::Hyperedge & hyperedge : original.hyperedges())
        {
            implementation_->next_edge_ = hyperedge.id();

            addEdge(hyperedge);
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::MultiHypergraph::assign(const htd::IMultiHypergraph & original)
{
    *this = original;
}
#endif

#endif /* HTD_HTD_MULTIHYPERGRAPH_CPP */
