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
#include <vector>

htd::MultiHypergraph::MultiHypergraph(void)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      deletions_(),
      edges_(),
      neighborhood_()
{

}

htd::MultiHypergraph::MultiHypergraph(std::size_t initialSize)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      deletions_(),
      edges_(),
      neighborhood_()
{
    addVertices(initialSize);
}

htd::MultiHypergraph::MultiHypergraph(const htd::MultiHypergraph & original)
    : size_(original.size_),
      next_edge_(original.next_edge_),
      next_vertex_(original.next_vertex_),
      vertices_(original.vertices_),
      deletions_(original.deletions_),
      edges_(original.edges_),
      neighborhood_(original.neighborhood_)
{

}

htd::MultiHypergraph::MultiHypergraph(const htd::IMultiHypergraph & original)
    : size_(0),
      next_edge_(htd::Id::FIRST),
      next_vertex_(htd::Vertex::FIRST),
      vertices_(),
      deletions_(),
      edges_(),
      neighborhood_()
{
    *this = original;
}

htd::MultiHypergraph::~MultiHypergraph()
{

}

std::size_t htd::MultiHypergraph::vertexCount(void) const
{
    return size_ - deletions_.size();
}

std::size_t htd::MultiHypergraph::edgeCount(void) const
{
    return edges_.size();
}

std::size_t htd::MultiHypergraph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        for (auto & edge : edges_)
        {
            const htd::ConstCollection<htd::vertex_t> & elements = edge.elements();

            if (std::find(elements.begin(), elements.end(), vertex) != elements.end())
            {
                ret++;
            }
        }
    }
    else
    {
        throw std::out_of_range("std::size_t htd::MultiHypergraph::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::MultiHypergraph::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && deletions_.find(vertex) == deletions_.end();
}

bool htd::MultiHypergraph::isEdge(htd::id_t edgeId) const
{
    bool ret = false;

    for (auto it = edges_.begin(); !ret && it != edges_.end(); ++it)
    {
        ret = (it->id() == edgeId);
    }

    return ret;
}

bool htd::MultiHypergraph::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(htd::vertex_container { vertex1, vertex2 }));
}

bool htd::MultiHypergraph::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::MultiHypergraph::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    for (auto it = edges_.begin(); !ret && it != edges_.end(); ++it)
    {
        ret = it->size() == elements.size() && std::equal(it->begin(), it->end(), elements.begin());
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge.size() == 2 && edge[0] == vertex1 && edge[1] == vertex2)
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return associatedEdgeIds(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

htd::ConstCollection<htd::id_t> htd::MultiHypergraph::associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const
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
    bool ret = 0;
    
    if (isVertex(vertex) && isVertex(neighbor))
    {
        for (auto it = edges_.begin(); it != edges_.end();)
        {
            const htd::Hyperedge & edge = *it;
            
            if (std::binary_search(edge.begin(), edge.end(), vertex))
            {
                if (std::binary_search(edge.begin(), edge.end(), neighbor))
                {
                    ret = true;
                    
                    it = edges_.end();
                }
                else
                {
                    it++;
                }
            }
            else
            {
                it++;
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
        htd::vertex_t start = 0;
        
        htd::vertex_container newVertices;
        htd::vertex_container tmpVertices;

        std::vector<bool> reachableVertices(size_);

        for (auto deleted : deletions_)
        {
            reachableVertices[deleted] = true;
            
            if (start == deleted)
            {
                start++;
            }
        }
        
        reachableVertices[start] = true;

        newVertices.push_back(start);

        while (newVertices.size() > 0) 
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (htd::vertex_container::const_iterator it = tmpVertices.begin(); it != tmpVertices.end(); it++)
            {
                for (auto & edge : edges_)
                {
                    if (std::find(edge.begin(), edge.end(), *it) != edge.end())
                    {
                        for (htd::vertex_t neighbor : edge)
                        {
                            if (neighbor != *it && !reachableVertices[neighbor])
                            {
                                reachableVertices[neighbor] = true;

                                newVertices.push_back(neighbor);
                            }
                        }
                    }
                }
            }
        }
        
        ret = std::find(reachableVertices.begin(), reachableVertices.end(), false) == reachableVertices.end();
    }
    else
    {
        ret = false;
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
                    for (auto it2 = edges_.begin(); !ret && it2 != edges_.end(); it2++)
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
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::MultiHypergraph::neighbors(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(neighborhood_[vertex - htd::Vertex::FIRST]);
}

htd::vertex_t htd::MultiHypergraph::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        auto & currentNeighborhood = neighborhood_[vertex];

        if (index < currentNeighborhood.size())
        {
            ret = currentNeighborhood[index];
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::MultiHypergraph::neighbor(htd::vertex_t, htd::index_t) const");
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
            
            for (auto it = edges_.begin(); isolated && it != edges_.end(); it++)
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

htd::vertex_t htd::MultiHypergraph::isolatedVertex(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & isolatedVertexCollection = isolatedVertices();

    if (index >= isolatedVertexCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::MultiHypergraph::isolatedVertex(htd::index_t) const");
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

        for (auto it = edges_.begin(); ret && it != edges_.end(); it++)
        {
            ret = (*it).size() <= 1 || std::find((*it).begin(), (*it).end(), vertex) == (*it).end();
        }
    }

    return ret;
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>::getInstance(edges_);
}

htd::ConstCollection<htd::Hyperedge> htd::MultiHypergraph::hyperedges(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        for (auto & edge : edges_)
        {
            if (std::find(edge.begin(), edge.end(), vertex) != edge.end())
            {
                result.push_back(edge);
            }
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedge(htd::id_t edgeId) const
{
    bool found = false;

    auto position = edges_.begin();

    for (auto it = edges_.begin(); !found && it != edges_.end(); ++it)
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
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::DirectedGraph::hyperedgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::Hyperedge & htd::MultiHypergraph::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
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
        std::vector<htd::vertex_t> & vertexContainer = ret.container();

        vertices_.resize(vertices_.size() + count, 0);

        for (htd::index_t index = 0; index < count; ++index)
        {
            vertices_[size_ + index + 1 - htd::Vertex::FIRST] = next_vertex_;

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
        
        for (auto & edge : edges_)
        {
            edge.erase(vertex);
            
            if (edge.size() == 0)
            {
                emptyEdges.push_back(currentIndex);
            }
            
            ++currentIndex;
        }

        std::size_t count = emptyEdges.size();
        
        for (currentIndex = 0; currentIndex < count; currentIndex++)
        {
            emptyEdges.erase(emptyEdges.begin() + count - currentIndex - 1);
        }
        
        deletions_.insert(vertex);

        vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), vertex));
    }
}

htd::id_t htd::MultiHypergraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (!isVertex(vertex1) || !isVertex(vertex2))
    {
        throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(htd::vertex_t, htd::vertex_t)");
    }

    edges_.push_back(htd::Hyperedge(next_edge_, htd::ConstCollection<htd::vertex_t>::getInstance(htd::vertex_container { vertex1, vertex2 })));

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

    return next_edge_++;
}

htd::id_t htd::MultiHypergraph::addEdge(const std::vector<htd::vertex_t> & elements)
{
    return addEdge(htd::Hyperedge(htd::Id::UNKNOWN, elements));
}

htd::id_t htd::MultiHypergraph::addEdge(std::vector<htd::vertex_t> && elements)
{
    return addEdge(htd::Hyperedge(htd::Id::UNKNOWN, std::move(elements)));
}

htd::id_t htd::MultiHypergraph::addEdge(const htd::ConstCollection<htd::vertex_t> & elements)
{
    return addEdge(htd::Hyperedge(htd::Id::UNKNOWN, elements));
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

            htd::Hyperedge newHyperedge(hyperedge);

            newHyperedge.setId(next_edge_);

            edges_.push_back(newHyperedge);

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
        ok = isVertex(*it);
    }

    if (!ok)
    {
        throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(const htd::Hyperedge &)");
    }

    htd::Hyperedge newHyperedge(hyperedge);

    newHyperedge.setId(next_edge_);

    edges_.push_back(newHyperedge);

    std::vector<htd::vertex_t> sortedElements(newHyperedge.begin(), newHyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    sortedElements.erase(std::unique(sortedElements.begin(), sortedElements.end()), sortedElements.end());

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        htd::vertex_container newNeighborhood;

        htd::filtered_set_union(currentNeighborhood.begin(), currentNeighborhood.end(), sortedElements.begin(), sortedElements.end(), vertex, std::back_inserter(newNeighborhood));

        currentNeighborhood.swap(newNeighborhood);
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

            edges_.push_back(newHyperedge);

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
        ok = isVertex(*it);
    }

    if (!ok)
    {
        throw std::logic_error("htd::id_t htd::MultiHypergraph::addEdge(htd::Hyperedge &&)");
    }

    htd::Hyperedge newHyperedge(std::move(hyperedge));

    newHyperedge.setId(next_edge_);

    edges_.push_back(newHyperedge);

    std::vector<htd::vertex_t> sortedElements(newHyperedge.begin(), newHyperedge.end());

    std::sort(sortedElements.begin(), sortedElements.end());

    sortedElements.erase(std::unique(sortedElements.begin(), sortedElements.end()), sortedElements.end());

    for (htd::vertex_t vertex : sortedElements)
    {
        auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        htd::vertex_container newNeighborhood;

        htd::filtered_set_union(currentNeighborhood.begin(), currentNeighborhood.end(), sortedElements.begin(), sortedElements.end(), vertex, std::back_inserter(newNeighborhood));

        currentNeighborhood.swap(newNeighborhood);
    }

    return next_edge_++;
}

void htd::MultiHypergraph::removeEdge(htd::id_t edgeId)
{
    bool found = false;

    auto position = edges_.begin();

    for (auto it = edges_.begin(); !found && it != edges_.end(); ++it)
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

        edges_.erase(position);

        for (htd::vertex_t vertex : hyperedge)
        {
            std::unordered_set<htd::vertex_t> missing(hyperedge.begin(), hyperedge.end());

            for (auto it = edges_.begin(); !missing.empty() && it != edges_.end(); it++)
            {
                htd::Hyperedge & currentEdge = *it;

                if (std::find(currentEdge.begin(), currentEdge.end(), vertex) != currentEdge.end())
                {
                    for (htd::vertex_t vertex2 : currentEdge)
                    {
                        missing.erase(vertex2);
                    }
                }
            }

            if (!missing.empty())
            {
                htd::vertex_container & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

                for (auto it = missing.begin(); it != missing.end(); it++)
                {
                    auto position2 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), *it);

                    currentNeighborhood.erase(position2);
                }
            }
        }
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

        deletions_.clear();

        edges_.clear();

        neighborhood_.clear();

        for (htd::vertex_t vertex : original.vertices())
        {
            while (vertex > next_vertex_)
            {
                deletions_.insert(next_vertex_);

                neighborhood_.push_back(htd::vertex_container());
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
