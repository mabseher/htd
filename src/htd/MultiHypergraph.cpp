/* 
 * File:   MultiHypergraph.cpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPH_CPP
#define	HTD_HTD_MULTIHYPERGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiHypergraph.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <stack>
#include <unordered_set>
#include <vector>

htd::MultiHypergraph::MultiHypergraph(void)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      selfLoops_(),
      deletions_(),
      edges_(std::make_shared<htd::hyperedge_container>()),
      neighborhood_()
{

}

htd::MultiHypergraph::MultiHypergraph(std::size_t initialSize)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      selfLoops_(),
      deletions_(),
      edges_(std::make_shared<htd::hyperedge_container>()),
      neighborhood_()
{
    addVertices(initialSize);
}

htd::MultiHypergraph::MultiHypergraph(const htd::MultiHypergraph & original)
    : size_(original.size_),
      next_edge_(original.next_edge_),
      next_vertex_(original.next_vertex_),
      vertices_(original.vertices_),
      selfLoops_(original.selfLoops_),
      deletions_(original.deletions_),
      edges_(std::make_shared<htd::hyperedge_container>(*(original.edges_))),
      neighborhood_(original.neighborhood_)
{

}

htd::MultiHypergraph::MultiHypergraph(const htd::IMultiHypergraph & original)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      selfLoops_(),
      deletions_(),
      edges_(std::make_shared<htd::hyperedge_container>()),
      neighborhood_()
{
    *this = original;
}

htd::MultiHypergraph::~MultiHypergraph()
{

}

std::size_t htd::MultiHypergraph::vertexCount(void) const
{
    return size_;
}

std::size_t htd::MultiHypergraph::edgeCount(void) const
{
    return edges_->size();
}

std::size_t htd::MultiHypergraph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    HTD_ASSERT(isVertex(vertex))

    for (const htd::Hyperedge & edge : *edges_)
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
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && deletions_.count(vertex) == 0;
}

bool htd::MultiHypergraph::isEdge(htd::id_t edgeId) const
{
    bool ret = false;

    for (auto it = edges_->begin(); !ret && it != edges_->end(); ++it)
    {
        ret = (it->id() == edgeId);
    }

    return ret;
}

bool htd::MultiHypergraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isNeighbor(vertex1, vertex2) && isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(htd::vertex_container { vertex1, vertex2 }));
}

bool htd::MultiHypergraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::MultiHypergraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    for (auto it = edges_->begin(); !ret && it != edges_->end(); ++it)
    {
        ret = it->size() == elements.size() && std::equal(it->begin(), it->end(), elements.begin());
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
        if (edge.size() == elements.size() && std::equal(edge.begin(), edge.end(), elements.begin()))
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
        if (edge.size() == elements.size() && std::equal(edge.begin(), edge.end(), elements.begin()))
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::vertex_t htd::MultiHypergraph::vertexAtPosition(htd::index_t index) const
{
    if (index >= vertices_.size())
    {
        throw std::out_of_range("htd::vertex_t htd::MultiHypergraph::vertexAtPosition(htd::index_t) const");
    }

    return vertices_[index];
}

bool htd::MultiHypergraph::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    HTD_ASSERT(isVertex(vertex) && isVertex(neighbor))

    bool ret = false;

    if (vertex != neighbor)
    {
        const std::vector<htd::vertex_t> & currentNeighborhood = neighborhood_.at(vertex - htd::Vertex::FIRST);

        ret = std::binary_search(currentNeighborhood.begin(), currentNeighborhood.end(), neighbor);
    }
    else
    {
        for (auto it = edges_->begin(); !ret && it != edges_->end(); ++it)
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
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        ret = neighborhood_[vertex - htd::Vertex::FIRST].size();
    }
    
    return ret;
}

bool htd::MultiHypergraph::isConnected(void) const
{
    bool ret = true;
    
    if (size_ > 0)
    {
        std::stack<htd::vertex_t> originStack;

        std::unordered_set<htd::vertex_t> visitedVertices;

        htd::vertex_t currentVertex = vertices_.at(0);

        originStack.push(currentVertex);

        while (!originStack.empty())
        {
            currentVertex = originStack.top();

            if (visitedVertices.count(currentVertex) == 0)
            {
                visitedVertices.insert(currentVertex);

                originStack.pop();

                for (htd::vertex_t neighbor : neighborhood_.at(currentVertex - htd::Vertex::FIRST))
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

        ret = visitedVertices.size() == vertices_.size();
    }
    else
    {
        ret = true;
    }
    
    return ret;
}

bool htd::MultiHypergraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = false;
    
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        if (vertex1 == vertex2)
        {
            ret = true;
        }
        else
        {
            htd::vertex_container newVertices;
            htd::vertex_container tmpVertices;

            std::vector<bool> reachableVertices(size_);

            reachableVertices[vertex1 - htd::Vertex::FIRST] = true;

            newVertices.push_back(vertex1);

            while (!ret && newVertices.size() > 0)
            {
                std::swap(tmpVertices, newVertices);

                newVertices.resize(0);

                for (auto it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
                {
                    for (auto it2 = edges_->begin(); !ret && it2 != edges_->end(); it2++)
                    {
                        if (std::find((*it2).begin(), (*it2).end(), *it) != (*it2).end())
                        {
                            for (auto it3 = (*it2).begin(); !ret && it3 != (*it2).end(); it3++)
                            {
                                if (*it3 != *it && !reachableVertices[*it3 - htd::Vertex::FIRST])
                                {
                                    reachableVertices[*it3 - htd::Vertex::FIRST] = true;

                                    newVertices.push_back(*it3);

                                    if (*it3 == vertex2)
                                    {
                                        ret = true;
                                    }
                                }
                            }
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

    return htd::ConstCollection<htd::vertex_t>::getInstance(neighborhood_[vertex - htd::Vertex::FIRST]);
}

void htd::MultiHypergraph::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::copy(neighborhood_[vertex - htd::Vertex::FIRST].begin(), neighborhood_[vertex - htd::Vertex::FIRST].end(), std::back_inserter(target));
}

htd::vertex_t htd::MultiHypergraph::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        if (index < currentNeighborhood.size())
        {
            ret = currentNeighborhood[index];
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::MultiHypergraph::neighborAtPosition(htd::vertex_t, htd::index_t) const");
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(vertices_);
}

std::size_t htd::MultiHypergraph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    for (std::size_t vertex = htd::Vertex::FIRST; vertex < size_ + htd::Vertex::FIRST; vertex++)
    {
        if (isVertex(vertex) && neighborhood_[vertex - htd::Vertex::FIRST].empty())
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

    for (std::size_t vertex = htd::Vertex::FIRST; vertex < size_ + htd::Vertex::FIRST; vertex++)
    {
        if (isVertex(vertex))
        {
            bool isolated = true;
            
            for (auto it = edges_->begin(); isolated && it != edges_->end(); it++)
            {
                isolated = (*it).size() <= 1 || std::find((*it).begin(), (*it).end(), vertex) == (*it).end();
            }
            
            if (isolated)
            {
                result.push_back(vertex);
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::vertex_t htd::MultiHypergraph::isolatedVertexAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

    if (index >= isolatedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::MultiHypergraph::isolatedVertexAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = isolatedVertexCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::MultiHypergraph::isIsolatedVertex(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = true;

        for (auto it = edges_->begin(); ret && it != edges_->end(); it++)
        {
            ret = (*it).size() <= 1 || std::find((*it).begin(), (*it).end(), vertex) == (*it).end();
        }
    }

    return ret;
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>::getInstance(*edges_);
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    for (auto & edge : *edges_)
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

    auto position = edges_->begin();

    for (auto it = edges_->begin(); !found && it != edges_->end(); ++it)
    {
        if (it->id() == edgeId)
        {
            position = it;

            found = true;
        }
    }

    if (!found)
    {
        throw std::logic_error("const htd::Hyperedge & htd::MultiHypergraph::hyperedge(htd::id_t) const");
    }

    return *position;
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t index) const
{
    if (index >= edges_->size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t) const");
    }

    return edges_->at(index);
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    for (auto it = edges_->begin(); it != edges_->end(); ++it)
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
    return htd::FilteredHyperedgeCollection(edges_, indices);
}

htd::FilteredHyperedgeCollection htd::MultiHypergraph::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    return htd::FilteredHyperedgeCollection(edges_, std::move(indices));
}

htd::vertex_t htd::MultiHypergraph::addVertex(void)
{
    htd::vertex_t ret = next_vertex_;
    
    size_++;

    next_vertex_++;

    neighborhood_.push_back(htd::vertex_container());

    vertices_.push_back(ret);

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::addVertices(std::size_t count)
{
    htd::VectorAdapter<htd::vertex_t> ret;

    if (count > 0)
    {
        std::size_t previousSize = vertices_.size();

        std::vector<htd::vertex_t> & vertexContainer = ret.container();

        vertices_.resize(previousSize + count, 0);

        for (htd::index_t index = 0; index < count; ++index)
        {
            vertices_[previousSize + index + 1 - htd::Vertex::FIRST] = next_vertex_;

            vertexContainer.push_back(next_vertex_);

            ++next_vertex_;
        }

        neighborhood_.resize(neighborhood_.size() + count, htd::vertex_container());

        size_ += count;
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::MultiHypergraph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        htd::index_t currentIndex = 0;
        
        std::vector<htd::id_t> emptyEdges;
        
        for (auto & edge : *edges_)
        {
            edge.erase(vertex);
            
            if (edge.size() == 0)
            {
                emptyEdges.push_back(currentIndex);
            }
            
            ++currentIndex;
        }

        for (auto it = emptyEdges.rbegin(); it != emptyEdges.rend(); ++it)
        {
            edges_->erase(edges_->begin() + *it);
        }

        selfLoops_.erase(vertex);

        deletions_.insert(vertex);

        for (htd::vertex_t neighbor : neighborhood_[vertex - htd::Vertex::FIRST])
        {
            if (neighbor != vertex)
            {
                auto & currentNeighborhood = neighborhood_[neighbor - htd::Vertex::FIRST];

                /* Because 'neighbor' is a neighbor of 'vertex', std::lower_bound will always find 'vertex' in 'currentNeighborhood'. */
                // coverity[use_iterator]
                currentNeighborhood.erase(std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex));
            }
        }

        neighborhood_[vertex - htd::Vertex::FIRST].clear();

        vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), vertex));

        --size_;
    }
}

htd::id_t htd::MultiHypergraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    HTD_ASSERT(isVertex(vertex1) && isVertex(vertex2))

    edges_->push_back(htd::Hyperedge(next_edge_, vertex1, vertex2));

    if (vertex1 == vertex2)
    {
        auto & currentNeighborhood1 = neighborhood_[vertex1 - htd::Vertex::FIRST];

        auto position1 = std::lower_bound(currentNeighborhood1.begin(), currentNeighborhood1.end(), vertex1);

        if (position1 == currentNeighborhood1.end() || *position1 != vertex1)
        {
            currentNeighborhood1.insert(position1, vertex1);
        }

        selfLoops_.insert(vertex1);
    }
    else
    {
        auto & currentNeighborhood1 = neighborhood_[vertex1 - htd::Vertex::FIRST];
        auto & currentNeighborhood2 = neighborhood_[vertex2 - htd::Vertex::FIRST];

        auto position1 = std::lower_bound(currentNeighborhood1.begin(), currentNeighborhood1.end(), vertex2);

        if (position1 == currentNeighborhood1.end() || *position1 != vertex2)
        {
            currentNeighborhood1.insert(position1, vertex2);
        }

        auto position2 = std::lower_bound(currentNeighborhood2.begin(), currentNeighborhood2.end(), vertex1);

        if (position2 == currentNeighborhood2.end() || *position2 != vertex1)
        {
            currentNeighborhood2.insert(position2, vertex1);
        }
    }

    return next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(const std::vector<htd::vertex_t> & elements)
{
    return addEdge(std::vector<htd::vertex_t>(elements));
}

htd::id_t htd::MultiHypergraph::addEdge(std::vector<htd::vertex_t> && elements)
{
    HTD_ASSERT(elements.size() > 0)

    switch (elements.size())
    {
        case 1:
        {
            HTD_ASSERT(isVertex(elements[0]))

            edges_->push_back(htd::Hyperedge(next_edge_, std::move(elements)));

            return next_edge_++;
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

    std::sort(sortedElements.begin(), sortedElements.end());

    auto position = std::unique(sortedElements.begin(), sortedElements.end());

    for (auto it = position; it != sortedElements.end(); it++)
    {
        selfLoops_.insert(*it);
    }

    sortedElements.erase(position, sortedElements.end());

    edges_->push_back(htd::Hyperedge(next_edge_, std::move(elements)));

    htd::vertex_container newNeighborhood;

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        if (selfLoops_.count(vertex) > 0)
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

    return next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(const htd::ConstCollection<htd::vertex_t> & elements)
{
    return addEdge(std::vector<htd::vertex_t>(elements.begin(), elements.end()));
}

htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge & hyperedge)
{
    switch (hyperedge.size())
    {
        case 0:
        {
            throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge &)");
        }
        case 1:
        {
            if (!isVertex(hyperedge[0]))
            {
                throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge &)");
            }

            edges_->push_back(htd::Hyperedge(next_edge_, hyperedge.elements()));

            return next_edge_++;
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

    bool ok = true;

    for (auto it = hyperedge.begin(); ok && it != hyperedge.end(); it++)
    {
        isVertex(*it);
    }

    if (!ok)
    {
        throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge &)");
    }

    edges_->push_back(htd::Hyperedge(next_edge_, hyperedge.elements()));

    std::vector<htd::vertex_t> sortedElements(hyperedge.begin(), hyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    auto position = std::unique(sortedElements.begin(), sortedElements.end());

    for (auto it = position; it != sortedElements.end(); it++)
    {
        selfLoops_.insert(*it);
    }

    sortedElements.erase(position, sortedElements.end());

    htd::vertex_container newNeighborhood;

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        if (selfLoops_.count(vertex) > 0)
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

    return next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge && hyperedge)
{
    switch (hyperedge.size())
    {
        case 0:
        {
            throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge &&)");
        }
        case 1:
        {
            if (!isVertex(hyperedge[0]))
            {
                throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge &&)");
            }

            htd::Hyperedge newHyperedge(std::move(hyperedge));

            newHyperedge.setId(next_edge_);

            edges_->push_back(newHyperedge);

            return next_edge_++;
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

    for (htd::vertex_t vertex : hyperedge)
    {
        if (!isVertex(vertex))
        {
            throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge &&)");
        }
    }

    htd::Hyperedge newHyperedge(std::move(hyperedge));

    newHyperedge.setId(next_edge_);

    edges_->push_back(newHyperedge);

    std::vector<htd::vertex_t> sortedElements(newHyperedge.begin(), newHyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    auto position = std::unique(sortedElements.begin(), sortedElements.end());

    for (auto it = position; it != sortedElements.end(); it++)
    {
        selfLoops_.insert(*it);
    }

    sortedElements.erase(position, sortedElements.end());

    htd::vertex_container newNeighborhood;

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        if (selfLoops_.count(vertex) > 0)
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

    return next_edge_++;
}

void htd::MultiHypergraph::removeEdge(htd::id_t edgeId)
{
    bool found = false;

    auto position = edges_->begin();

    for (auto it = edges_->begin(); !found && it != edges_->end(); ++it)
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

            for (auto it = edges_->begin(); !missing.empty() && it != edges_->end(); it++)
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
                htd::vertex_container & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

                for (auto it = missing.begin(); it != missing.end(); it++)
                {
                    auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), *it);

                    if (position2 != currentNeighborhood.end())
                    {
                        currentNeighborhood.erase(position2);
                    }
                }
            }

            if (selfLoops_.count(vertex) > 0 && !selfLoopExists)
            {
                htd::vertex_container & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

                auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

                if (position2 != currentNeighborhood.end())
                {
                    // coverity[use_iterator]
                    position2 = currentNeighborhood.erase(position2);
                }

                selfLoops_.erase(vertex);
            }
        }

        edges_->erase(position);
    }
}

htd::MultiHypergraph * htd::MultiHypergraph::clone(void) const
{
    return new htd::MultiHypergraph(*this);
}

htd::MultiHypergraph & htd::MultiHypergraph::operator=(const htd::MultiHypergraph & original)
{
    if (this != &original)
    {
        size_ = original.size_;

        next_edge_ = original.next_edge_;

        next_vertex_ = original.next_vertex_;

        vertices_ = original.vertices_;

        selfLoops_ = original.selfLoops_;

        deletions_ = original.deletions_;

        edges_ = original.edges_;

        neighborhood_ = original.neighborhood_;
    }

    return *this;
}

htd::MultiHypergraph & htd::MultiHypergraph::operator=(const htd::IMultiHypergraph & original)
{
    if (this != &original)
    {
        size_ = 0;

        next_edge_ = htd::Id::FIRST;

        next_vertex_ = htd::Vertex::FIRST;

        vertices_.clear();

        selfLoops_.clear();

        deletions_.clear();

        edges_->clear();

        neighborhood_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            while (vertex > next_vertex_)
            {
                deletions_.insert(next_vertex_);

                neighborhood_.push_back(htd::vertex_container());

                ++next_vertex_;
            }

            size_++;

            next_vertex_++;

            neighborhood_.push_back(htd::vertex_container());

            vertices_.push_back(vertex);
        }

        for (const htd::Hyperedge & hyperedge : original.hyperedges())
        {
            next_edge_ = hyperedge.id();

            addEdge(hyperedge);
        }
    }

    return *this;
}

#endif /* HTD_HTD_MULTIHYPERGRAPH_CPP */
