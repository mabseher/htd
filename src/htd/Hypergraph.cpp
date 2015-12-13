/* 
 * File:   Hypergraph.cpp
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

#ifndef HTD_HTD_HYPERGRAPH_CPP
#define	HTD_HTD_HYPERGRAPH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Hypergraph.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

htd::Hypergraph::Hypergraph(void) : htd::Hypergraph::Hypergraph(0)
{

}

htd::Hypergraph::Hypergraph(std::size_t size)
    : size_(size),
      next_vertex_(htd::Vertex::FIRST + size),
      vertices_(size),
      deletions_(),
      edges_(),
      neighborhood_(size, htd::vertex_container())
{
    for (htd::vertex_t vertex = htd::Vertex::FIRST; vertex < size + htd::Vertex::FIRST; ++vertex)
    {
        vertices_[vertex - htd::Vertex::FIRST] = vertex;
    }
}

htd::Hypergraph::~Hypergraph()
{

}

std::size_t htd::Hypergraph::vertexCount(void) const
{
    return size_ - deletions_.size();
}

std::size_t htd::Hypergraph::edgeCount(void) const
{
    return edges_.size();
}

std::size_t htd::Hypergraph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        for (auto& edge : edges_)
        {
            if (std::binary_search(edge.begin(), edge.end(), vertex))
            {
                ret++;
            }
        }
    }
    else
    {
        throw std::out_of_range("std::size_t htd::Hypergraph::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::Hypergraph::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && !std::binary_search(deletions_.begin(), deletions_.end(), vertex);
}

bool htd::Hypergraph::isEdge(const htd::hyperedge_t & edge) const
{
    htd::hyperedge_t hyperedge(edge);

    std::sort(hyperedge.begin(), hyperedge.end());

    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

    return std::find(edges_.begin(), edges_.end(), hyperedge) != edges_.end();
}

htd::vertex_t htd::Hypergraph::vertex(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (index < vertexCount())
    {
        htd::vertex_t vertex = 0;
        
        htd::index_t currentIndex = 0;
        
        while (currentIndex < index)
        {
            if (!std::binary_search(deletions_.begin(), deletions_.end(), vertex))
            {
                ++currentIndex;
            }
            
            ++vertex;
        }
        
        ret = vertex;
    }
    
    return ret;
}

bool htd::Hypergraph::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = 0;
    
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        for (auto it = edges_.begin(); it != edges_.end();)
        {
            const htd::hyperedge_t & edge = *it;
            
            if (std::binary_search(edge.begin(), edge.end(), vertex1))
            {
                if (std::binary_search(edge.begin(), edge.end(), vertex2))
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

std::size_t htd::Hypergraph::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        ret = neighborhood_[vertex - htd::Vertex::FIRST].size();
    }
    
    return ret;
}

bool htd::Hypergraph::isConnected(void) const
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
                for (auto& edge : edges_)
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

bool htd::Hypergraph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
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

void htd::Hypergraph::getNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        std::copy(neighborhood_[vertex - htd::Vertex::FIRST].begin(), neighborhood_[vertex - htd::Vertex::FIRST].end(), std::back_inserter(output));
    }
}

htd::vertex_t htd::Hypergraph::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        auto& currentNeighborhood = neighborhood_[vertex];

        if (index < currentNeighborhood.size())
        {
            ret = currentNeighborhood[index];
        }
        else
        {
            throw std::out_of_range("htd::vertex_t htd::Hypergraph::neighbor(htd::vertex_t, htd::index_t) const");
        }
    }

    return ret;
}

const htd::Collection<htd::vertex_t> htd::Hypergraph::vertices(void) const
{
    return Collection<htd::vertex_t>(vertices_);
}

std::size_t htd::Hypergraph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

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
                ret++;
            }
        }
    }

    return ret;
}

void htd::Hypergraph::getIsolatedVertices(htd::vertex_container & output) const
{
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
                output.push_back(vertex);
            }
        }
    }
}

htd::vertex_t htd::Hypergraph::isolatedVertex(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container result;

    getIsolatedVertices(result);

    if (index < result.size())
    {
        ret = result[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::Hypergraph::isolatedVertex(htd::index_t) const");
    }

    return ret;
}

bool htd::Hypergraph::isIsolatedVertex(htd::vertex_t vertex) const
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

const htd::Collection<htd::hyperedge_t> htd::Hypergraph::hyperedges(void) const
{
    return Collection<htd::hyperedge_t>(edges_);
}

void htd::Hypergraph::getHyperedges(htd::hyperedge_container & output, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        for (auto& edge : edges_)
        {
            if (std::find(edge.begin(), edge.end(), vertex) != edge.end())
            {
                output.push_back(edge);
            }
        }
    }
}

const htd::hyperedge_t & htd::Hypergraph::hyperedge(htd::index_t index) const
{
    HTD_UNUSED(index);

    //TODO Implement
    throw std::logic_error("const htd::hyperedge_t & htd::Hypergraph::hyperedge(htd::index_t) const: NOT YET IMPLEMENTED");
}

const htd::hyperedge_t & htd::Hypergraph::hyperedge(htd::index_t index, htd::vertex_t vertex) const
{
    HTD_UNUSED(index);
    HTD_UNUSED(vertex);

    //TODO Implement
    throw std::logic_error("const htd::hyperedge_t & htd::Hypergraph::hyperedge(htd::index_t, htd::vertex_t) const: NOT YET IMPLEMENTED");
}

htd::vertex_t htd::Hypergraph::addVertex(void)
{
    htd::vertex_t ret = next_vertex_;
    
    size_++;

    next_vertex_++;

    neighborhood_.push_back(htd::vertex_container());

    vertices_.push_back(ret);

    return ret;
}

void htd::Hypergraph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        htd::index_t currentIndex = 0;
        
        std::vector<htd::id_t> emptyEdges;
        
        for (auto& edge : edges_)
        {
            edge.erase(std::remove(edge.begin(), edge.end(), vertex), edge.end());
            
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

void htd::Hypergraph::removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge)
{
    if (isVertex(vertex))
    {
        htd::index_t currentIndex = 0;

        std::vector<htd::id_t> emptyEdges;

        auto& currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

        if (addNeighborHyperedge)
        {
            htd::hyperedge_t newEdge;

            auto position1 = std::lower_bound(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

            if (position1 != currentNeighborhood.end())
            {
                currentNeighborhood.erase(position1);
            }

            std::copy(currentNeighborhood.begin(), currentNeighborhood.end(), std::back_inserter(newEdge));

            edges_.push_back(newEdge);
        }

        currentNeighborhood.clear();

        for (auto& edge : edges_)
        {
            edge.erase(std::remove(edge.begin(), edge.end(), vertex), edge.end());

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

void htd::Hypergraph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    addEdge(htd::edge_t(vertex1, vertex2));
}

void htd::Hypergraph::addEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end)
{
    addEdge(htd::hyperedge_t(begin, end));
}

void htd::Hypergraph::addEdge(const htd::edge_t & edge)
{
    htd::hyperedge_t hyperedge;

    if (edge.first < edge.second)
    {
        hyperedge.push_back(edge.first);
        hyperedge.push_back(edge.second);
    }
    else
    {
        if (edge.first != edge.second)
        {
            hyperedge.push_back(edge.second);
        }

        hyperedge.push_back(edge.first);
    }

    addEdge(hyperedge);
}

void htd::Hypergraph::addEdge(const htd::hyperedge_t & edge)
{
    if (edge.size() > 0)
    {
        bool ok = true;

        for (auto it = edge.begin(); ok && it != edge.end(); it++)
        {
            ok = isVertex(*it);
        }

        if (ok)
        {
            htd::hyperedge_t hyperedge(edge);

            std::sort(hyperedge.begin(), hyperedge.end());

            hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

            edges_.push_back(hyperedge);

            std::array<htd::vertex_t, 1> currentVertex;

            for (htd::vertex_t vertex : hyperedge)
            {
                currentVertex[0] = vertex;

                auto & currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];

                htd::vertex_container newNeighborhood;

                htd::filtered_set_union(currentNeighborhood.begin(), currentNeighborhood.end(),
                                        hyperedge.begin(), hyperedge.end(),
                                        currentVertex.begin(), currentVertex.end(),
                                        std::back_inserter(newNeighborhood));

                currentNeighborhood.swap(newNeighborhood);
            }
        }
        else
        {
            throw std::logic_error("void htd::Hypergraph::addEdge(const htd::hyperedge_t &)");
        }
    }
}

void htd::Hypergraph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    removeEdge(htd::edge_t(vertex1, vertex2));
}

void htd::Hypergraph::removeEdge(vertex_container::const_iterator begin, vertex_container::const_iterator end)
{
    removeEdge(htd::hyperedge_t(begin, end));
}

void htd::Hypergraph::removeEdge(const htd::edge_t & edge)
{
    htd::hyperedge_t hyperedge;

    if (edge.first < edge.second)
    {
        hyperedge.push_back(edge.first);
        hyperedge.push_back(edge.second);
    }
    else
    {
        if (edge.first != edge.second)
        {
            hyperedge.push_back(edge.second);
        }    
        
        hyperedge.push_back(edge.first);
    }
    
    removeEdge(hyperedge);
}

void htd::Hypergraph::removeEdge(const htd::hyperedge_t & edge)
{
    if (edge.size() > 0)
    {
        bool ok = true;

        for (auto it = edge.begin(); ok && it != edge.end(); it++)
        {
            ok = isVertex(*it);
        }

        if (ok)
        {
            auto position = std::find(edges_.begin(), edges_.end(), edge);
            
            if (position != edges_.end() && *position == edge)
            {
                edges_.erase(position);

                for (htd::vertex_t vertex : edge)
                {
                    for (auto it = edges_.begin(); it != edges_.end(); it++)
                    {
                        htd::hyperedge_t & currentEdge = *it;

                        if (std::lower_bound(currentEdge.begin(), currentEdge.end(), vertex) != currentEdge.end())
                        {
                            it = edges_.end();
                        }
                    }
                }
            }
        }
        else
        {
            throw std::logic_error("void htd::Hypergraph::removeEdge(const htd::hyperedge_t &)");
        }
    }
}

htd::Hypergraph * htd::Hypergraph::clone(void) const
{
    return new Hypergraph(*this);
}

#endif /* HTD_HTD_HYPERGRAPH_CPP */
