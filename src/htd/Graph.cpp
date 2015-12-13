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
#include <htd/Collection.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
#include <set>

htd::Graph::Graph(void) : htd::Graph::Graph(0)
{

}

htd::Graph::Graph(std::size_t size)
    : size_(size),
      next_vertex_(htd::Vertex::FIRST + size),
      vertices_(size),
      deletions_(),
      neighborhood_(size, std::vector<htd::vertex_t>())
{
    for (htd::vertex_t vertex = htd::Vertex::FIRST; vertex < size + htd::Vertex::FIRST; ++vertex)
    {
        vertices_[vertex - htd::Vertex::FIRST] = vertex;
    }
}

htd::Graph::~Graph()
{
    
}

std::size_t htd::Graph::vertexCount(void) const
{
    return size_ - deletions_.size();
}

std::size_t htd::Graph::edgeCount(void) const
{
    std::size_t ret = 0;
    
    for (auto& v : neighborhood_)
    {
        ret += v.size();
    }
    
    return ret / 2;
}

std::size_t htd::Graph::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = neighborhood_[vertex].size();
    }
    else
    {
        throw std::out_of_range("std::size_t htd::Graph::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::Graph::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && !std::binary_search(deletions_.begin(), deletions_.end(), vertex);
}

bool htd::Graph::isEdge(const htd::hyperedge_t & edge) const
{
    bool ret = false;

    if (edge.size() == 2 && edge[0] != edge[1])
    {
        ret = isNeighbor(edge[0], edge[1]);
    }

    return ret;
}

htd::vertex_t htd::Graph::vertex(htd::id_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (index < vertexCount())
    {
        htd::vertex_t vertex = 0;
        
        std::size_t currentIndex = 0;
        
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
            
bool htd::Graph::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return std::binary_search(neighborhood_[vertex1].begin(), neighborhood_[vertex1].end(), vertex2);
}

bool htd::Graph::isConnected(void) const
{
    bool ret = true;
    
    if (size_ > 0)
    {
        htd::vertex_t start = htd::Vertex::FIRST;
        
        htd::vertex_container newVertices;
        htd::vertex_container tmpVertices;

        std::vector<bool> reachableVertices(size_);

        for (auto deleted : deletions_)
        {
            reachableVertices[deleted - htd::Vertex::FIRST] = true;
            
            if (start == deleted)
            {
                start++;
            }
        }
        
        reachableVertices[start - htd::Vertex::FIRST] = true;

        newVertices.push_back(start);

        while (newVertices.size() > 0) 
        {
            std::swap(tmpVertices, newVertices);

            newVertices.resize(0);

            for (htd::vertex_container::const_iterator it = tmpVertices.begin(); it != tmpVertices.end(); it++)
            {
                for (htd::vertex_container::const_iterator it2 = neighborhood_[*it - htd::Vertex::FIRST].begin(); it2 != neighborhood_[*it - htd::Vertex::FIRST].end(); it2++)
                {
                    if (!reachableVertices[*it2 - htd::Vertex::FIRST])
                    {
                        reachableVertices[*it2 - htd::Vertex::FIRST] = true;

                        newVertices.push_back(*it2);
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

bool htd::Graph::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = false;

    if (isVertex(vertex1) && isVertex(vertex2))
    {
        if (vertex1 != vertex2)
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

                for (htd::vertex_container::const_iterator it = tmpVertices.begin(); !ret && it != tmpVertices.end(); it++)
                {
                    for (htd::vertex_container::const_iterator it2 = neighborhood_[*it - htd::Vertex::FIRST].begin(); !ret && it2 != neighborhood_[*it - htd::Vertex::FIRST].end(); it2++)
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
        else
        {
            ret = true;
        }
    }
    
    return ret;
}

std::size_t htd::Graph::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        ret = neighborhood_[vertex].size();
    }
    
    return ret;
}
            
void htd::Graph::getNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        std::copy(neighborhood_[vertex - htd::Vertex::FIRST].begin(), neighborhood_[vertex - htd::Vertex::FIRST].end(), std::back_inserter(output));
    }
}

htd::vertex_t htd::Graph::neighbor(htd::vertex_t vertex, htd::id_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto& currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];
        
        if (index < currentNeighborhood.size())
        {
            ret = currentNeighborhood[index];
        }
    }
    
    return ret;
}

const htd::Collection<htd::vertex_t> htd::Graph::vertices(void) const
{
    return Collection<htd::vertex_t>(vertices_);
}

std::size_t htd::Graph::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex = 0; vertex < size_; vertex++)
    {
        if (isVertex(vertex))
        {
            if (neighborhood_[vertex - htd::Vertex::FIRST].size() == 0)
            {
                ret++;
            }
        }
    }

    return ret;
}

void htd::Graph::getIsolatedVertices(htd::vertex_container & output) const
{
    for (htd::vertex_t vertex = 0; vertex < size_; vertex++)
    {
        if (isVertex(vertex))
        {
            if (neighborhood_[vertex - htd::Vertex::FIRST].size() == 0)
            {
                output.push_back(vertex);
            }
        }
    }
}

htd::vertex_t htd::Graph::isolatedVertex(htd::index_t index) const
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
        throw std::out_of_range("htd::vertex_t htd::Graph::isolatedVertex(htd::index_t) const");
    }

    return ret;
}

bool htd::Graph::isIsolatedVertex(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = neighborhood_[vertex - htd::Vertex::FIRST].size() == 0;
    }

    return ret;
}

void htd::Graph::getEdges(htd::edge_container & output) const
{
    for (size_t vertex1 = 0; vertex1 < size_; vertex1++)
    {
        for (auto& vertex2 : neighborhood_[vertex1 - htd::Vertex::FIRST])
        {
            output.push_back(edge_t(vertex1, vertex2));
        }
    }
}

void htd::Graph::getEdges(htd::edge_container & output, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        for (auto& vertex2 : neighborhood_[vertex - htd::Vertex::FIRST])
        {
            output.push_back(edge_t(vertex, vertex2));
        }
    }
}

const htd::edge_t & htd::Graph::edge(htd::index_t index) const
{
    HTD_UNUSED(index);

    //TODO Implement
    throw std::logic_error("NOT IMPLEMENTED");
}

const htd::edge_t & htd::Graph::edge(htd::index_t index, htd::vertex_t vertex) const
{
    HTD_UNUSED(index);
    HTD_UNUSED(vertex);

    //TODO Implement
    throw std::logic_error("NOT IMPLEMENTED");
}

const htd::Collection<htd::hyperedge_t> htd::Graph::hyperedges(void) const
{
    htd::VectorAdapter<htd::hyperedge_t> ret;

    auto & result = ret.container();

    for (size_t vertex1 = 0; vertex1 < size_; vertex1++)
    {
        for (auto& vertex2 : neighborhood_[vertex1 - htd::Vertex::FIRST])
        {
            hyperedge_t hyperedge;

            if (vertex1 < vertex2)
            {
                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);
            }
            else
            {
                hyperedge.push_back(vertex2);
                hyperedge.push_back(vertex1);
            }

            result.push_back(hyperedge);
        }
    }

    return ret;
}

const htd::Collection<htd::hyperedge_t> htd::Graph::hyperedges(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::hyperedge_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        for (auto& vertex2 : neighborhood_[vertex - htd::Vertex::FIRST])
        {
            hyperedge_t hyperedge;

            if (vertex < vertex2)
            {
                hyperedge.push_back(vertex);
                hyperedge.push_back(vertex2);
            }
            else
            {
                hyperedge.push_back(vertex2);
                hyperedge.push_back(vertex);
            }

            result.push_back(hyperedge);
        }
    }
    else
    {
        throw std::logic_error("const htd::Collection<htd::hyperedge_t> htd::Graph::hyperedges(htd::vertex_t) const");
    }

    return ret;
}

const htd::hyperedge_t & htd::Graph::hyperedge(htd::index_t index) const
{
    HTD_UNUSED(index);

    //TODO Implement
    throw std::logic_error("NOT IMPLEMENTED");
}

const htd::hyperedge_t & htd::Graph::hyperedge(htd::index_t index, htd::vertex_t vertex) const
{
    HTD_UNUSED(index);
    HTD_UNUSED(vertex);

    //TODO Implement
    throw std::logic_error("NOT IMPLEMENTED");
}

htd::vertex_t htd::Graph::addVertex(void)
{
    htd::vertex_t ret = next_vertex_;

    size_++;

    next_vertex_++;

    vertices_.push_back(ret);

    neighborhood_.push_back(htd::vertex_container());

    return ret;
}

void htd::Graph::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        for (auto neighbor : neighborhood_[vertex - htd::Vertex::FIRST])
        {
            auto& currentNeighborhood = neighborhood_[neighbor - htd::Vertex::FIRST];
            
            auto position = std::find(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);
            
            if (position != currentNeighborhood.end())
            {
                currentNeighborhood.erase(position);
            }
        }
        
        neighborhood_[vertex - htd::Vertex::FIRST].clear();

        deletions_.insert(vertex);

        vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), vertex));
    }
}

void htd::Graph::removeVertex(htd::vertex_t vertex, bool addNeighborClique)
{
    if (isVertex(vertex))
    {
        auto& currentNeighborhood = neighborhood_[vertex - htd::Vertex::FIRST];
        
        if (addNeighborClique)
        {
            auto position = std::find(currentNeighborhood.begin(), currentNeighborhood.end(), vertex);

            if (position != currentNeighborhood.end())
            {
                currentNeighborhood.erase(position);
            }
        }
        
        for (std::size_t index = 0; index < currentNeighborhood.size(); index++)
        {
            auto neighbor = currentNeighborhood[index];
            
            if (neighbor != vertex)
            {
                auto& localNeighborhood = neighborhood_[neighbor - htd::Vertex::FIRST];

                if (addNeighborClique)
                {
                    htd::vertex_container newNeighborhood;

                    htd::vertex_container filter(2);

                    if (vertex < neighbor)
                    {
                        filter[0] = vertex;
                        filter[1] = neighbor;
                    }
                    else
                    {
                        filter[0] = neighbor;
                        filter[1] = vertex;
                    }

                    htd::filtered_set_union(localNeighborhood.begin(), localNeighborhood.end(), currentNeighborhood.begin(), currentNeighborhood.end(), filter.begin(), filter.end(), std::back_inserter(newNeighborhood));

                    std::swap(newNeighborhood, localNeighborhood);
                }
                else
                {
                    auto position = std::find(localNeighborhood.begin(), localNeighborhood.end(), vertex);

                    if (position != localNeighborhood.end())
                    {
                        localNeighborhood.erase(position);
                    }
                }
            }
        }
        
        neighborhood_[vertex - htd::Vertex::FIRST].clear();

        deletions_.insert(vertex);

        vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), vertex));
    }
}

void htd::Graph::addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        auto& currentNeighborhood1 = neighborhood_[vertex1 - htd::Vertex::FIRST];
        auto& currentNeighborhood2 = neighborhood_[vertex2 - htd::Vertex::FIRST];
        
        std::vector<htd::id_t> newVertex1 { vertex1 };
        std::vector<htd::id_t> newVertex2 { vertex2 };
        
        std::vector<htd::id_t> newNeighborhood1;
        std::vector<htd::id_t> newNeighborhood2;

        std::set_union(currentNeighborhood1.begin(), currentNeighborhood1.end(), newVertex2.begin(), newVertex2.end(), std::back_inserter(newNeighborhood1));
        std::set_union(currentNeighborhood2.begin(), currentNeighborhood2.end(), newVertex1.begin(), newVertex1.end(), std::back_inserter(newNeighborhood2));

        std::swap(newNeighborhood1, currentNeighborhood1);
        std::swap(newNeighborhood2, currentNeighborhood2);
    }
}

void htd::Graph::addEdge(const htd::edge_t & edge)
{
    addEdge(edge.first, edge.second);
}

void htd::Graph::removeEdge(id_t vertex1, id_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        auto& neighborhood1 = neighborhood_[vertex1 - htd::Vertex::FIRST];
        auto& neighborhood2 = neighborhood_[vertex2 - htd::Vertex::FIRST];
        
        auto position1 = std::find(neighborhood1.begin(), neighborhood1.end(), vertex2);

        if (position1 != neighborhood2.end())
        {
            neighborhood1.erase(position1);
        }
        
        auto position2 = std::find(neighborhood2.begin(), neighborhood2.end(), vertex1);

        if (position2 != neighborhood2.end())
        {
            neighborhood2.erase(position2);
        }
    }
}

void htd::Graph::removeEdge(const htd::edge_t & edge)
{
    removeEdge(edge.first, edge.second);
}

htd::Graph * htd::Graph::clone(void) const
{
    return new Graph(*this);
}

#endif /* HTD_HTD_GRAPH_CPP */
