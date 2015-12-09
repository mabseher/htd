/* 
 * File:   TreeDecompositionVerifier.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP
#define	HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/TreeDecompositionVerifier.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <map>
#include <algorithm>
#include <unordered_map>

htd::TreeDecompositionVerifier::TreeDecompositionVerifier(void)
{
    
}

htd::TreeDecompositionVerifier::~TreeDecompositionVerifier()
{
    
}

bool htd::TreeDecompositionVerifier::verify(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return verifyVertexExistence(graph, decomposition) && verifyHyperEdgeCoverage(graph, decomposition) && verifyConnectednessCriterion(graph, decomposition);
}

//Ensure that every vertex of the original graph is contained in at least one node of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::vertex_container result;
    
    getViolationsVertexExistence(graph, decomposition, result);
    
    return result.empty();
}

//Ensure that the vertices of an edge in the input graph occur jointly in at least on of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::hyperedge_container result;
    
    getViolationsHyperEdgeCoverage(graph, decomposition, result);
    
    return result.empty();
}

//Ensure for each vertex of the input graph that the bags containing the specific vertex are connected.
bool htd::TreeDecompositionVerifier::verifyConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::vertex_container result;
    
    getViolationsConnectednessCriterion(graph, decomposition, result);
    
    return result.empty();
}

void htd::TreeDecompositionVerifier::getViolationsVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_container & output) const
{
    bool ret = false;

    std::unordered_set<htd::vertex_t> missingVertices(graph.vertices().begin(), graph.vertices().end());
    
    for (auto it1 = decomposition.vertices().begin(); !ret && it1 != decomposition.vertices().end(); it1++)
    {
        htd::vertex_t node = *it1;

        auto label = decomposition.bagContent(node);

        for (auto it2 = label.begin(); !ret && it2 != label.end(); it2++)
        {
            missingVertices.erase(*it2);
            
            ret = missingVertices.empty();
        }
    }
    
    ret = missingVertices.empty();
    
    if (!ret)
    {
        std::copy(missingVertices.begin(), missingVertices.end(), std::back_inserter(output));
        
        std::sort(output.begin(), output.end());
    }
}
            
void htd::TreeDecompositionVerifier::getViolationsHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::hyperedge_container & output) const
{
    bool ret = false;

    std::size_t edgeCount = graph.edgeCount();

    htd::hyperedge_container edges;

    edges.reserve(edgeCount);

    for (const htd::hyperedge_t & edge : graph.hyperedges())
    {
        edges.push_back(edge);
    }

    std::unordered_set<htd::vertex_t> missingEdges(edgeCount);
    
    for (htd::index_t index = 0; index < edgeCount; index++)
    {
        missingEdges.insert(index);
    }
    
    std::vector<htd::index_t> coveredEdges;
        
    for (auto it1 = decomposition.vertices().begin(); !ret && it1 != decomposition.vertices().end(); it1++)
    {
        htd::vertex_t node = *it1;

        auto label = decomposition.bagContent(node);

        for (auto it2 = missingEdges.begin(); !ret && it2 != missingEdges.end(); it2++)
        {
            auto & edge = edges[*it2];
        
            if (std::includes(label.begin(), label.end(), edge.begin(), edge.end()))
            {
                coveredEdges.push_back(*it2);
            }
        }
        
        for (htd::index_t coveredEdge : coveredEdges)
        {
            missingEdges.erase(coveredEdge);
        }
        
        ret = missingEdges.empty();
        
        coveredEdges.clear();
    }
    
    if (!ret)
    {
        for (htd::index_t missingEdge : missingEdges)
        {
            output.push_back(edges[missingEdge]);
        }
        
        std::sort(output.begin(), output.end());
    }
}

void htd::TreeDecompositionVerifier::getViolationsConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_container & output) const
{
    bool ok = false;
    
    htd::edge_container edges;

    std::unordered_map<htd::vertex_t, std::vector<htd::vertex_t>> containers;

    decomposition.getEdges(edges);

    for (htd::vertex_t node : decomposition.vertices())
    {
        auto label = decomposition.bagContent(node);

        for (htd::vertex_t vertex : label)
        {
            containers[vertex].push_back(node);
        }
    }
    
    for (htd::vertex_t vertex : graph.vertices())
    {
        ok = false;
        
        auto & currentContainers = containers[vertex];
        
        if (currentContainers.size() > 1)
        {
            htd::vertex_container reachableVertices;
            getReachableVertices(currentContainers[0], decomposition, containers[vertex], reachableVertices);

            ok = reachableVertices.size() == currentContainers.size();
        }
        else
        {
            ok = true;
        }
        
        if (!ok)
        {
            output.push_back(vertex);
        }
    }
}

void htd::TreeDecompositionVerifier::getReachableVertices(htd::vertex_t start, const htd::ITreeDecomposition & decomposition, const htd::vertex_container & filter, htd::vertex_container & output) const
{
    std::size_t size = decomposition.vertexCount();
    
    if (size > 0)
    {
        htd::edge_container edges;
        
        std::map<htd::index_t, htd::vertex_container> neighbors;
        
        decomposition.getEdges(edges);
        
        for (auto & edge : edges)
        {
            if (std::binary_search(filter.begin(), filter.end(), edge.first) && std::binary_search(filter.begin(), filter.end(), edge.second))
            {
                auto & currentNeighborhood1 = neighbors[edge.first];
                auto & currentNeighborhood2 = neighbors[edge.second];
                
                if (!std::binary_search(currentNeighborhood1.begin(), currentNeighborhood1.end(), edge.second))
                {
                    currentNeighborhood1.push_back(edge.second);
                }
                
                if (!std::binary_search(currentNeighborhood2.begin(), currentNeighborhood2.end(), edge.first))
                {
                    currentNeighborhood2.push_back(edge.first);
                }
            }
        }
        
        edges.clear();
        
        std::vector<htd::vertex_t> newVertices;
        std::vector<htd::vertex_t> tmpVertices;

        std::set<htd::vertex_t> result;
        
        result.insert(start);

        newVertices.push_back(start);

        while (newVertices.size() > 0) 
        {
            std::swap(tmpVertices, newVertices);

            newVertices.clear();

            for (auto vertex : tmpVertices)
            {
                for (htd::vertex_t neighbor : neighbors[vertex])
                {
                    if (result.find(neighbor) == result.end())
                    {
                        result.insert(neighbor);

                        newVertices.push_back(neighbor);
                    }
                }
            }
        }
        
        std::copy(result.begin(), result.end(), std::back_inserter(output));
    }
}

#endif /* HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP */
