/* 
 * File:   TreeDecompositionVerifier.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP
#define	HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionVerifier.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <map>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

htd::TreeDecompositionVerifier::TreeDecompositionVerifier(void)
{
    
}

htd::TreeDecompositionVerifier::~TreeDecompositionVerifier()
{
    
}

bool htd::TreeDecompositionVerifier::verify(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return verifyVertexExistence(graph, decomposition) && verifyHyperEdgeCoverage(graph, decomposition) && verifyConnectednessCriterion(graph, decomposition);
}

//Ensure that every vertex of the original graph is contained in at least one node of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return violationsVertexExistence(graph, decomposition).empty();
}

//Ensure that the vertices of an edge in the input graph occur jointly in at least on of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyHyperEdgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return violationsHyperEdgeCoverage(graph, decomposition).empty();
}

//Ensure for each vertex of the input graph that the bags containing the specific vertex are connected.
bool htd::TreeDecompositionVerifier::verifyConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return violationsConnectednessCriterion(graph, decomposition).empty();
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecompositionVerifier::violationsVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    bool ok = false;

    std::unordered_set<htd::vertex_t> missingVertices(graph.vertices().begin(), graph.vertices().end());
    
    for (auto it1 = decomposition.vertices().begin(); !ok && it1 != decomposition.vertices().end(); it1++)
    {
        htd::vertex_t node = *it1;

        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(node);

        for (auto it2 = bag.begin(); !ok && it2 != bag.end(); it2++)
        {
            missingVertices.erase(*it2);
            
            ok = missingVertices.empty();
        }
    }

    std::copy(missingVertices.begin(), missingVertices.end(), std::back_inserter(result));
        
    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}
            
htd::ConstCollection<htd::Hyperedge> htd::TreeDecompositionVerifier::violationsHyperEdgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    bool ok = false;

    std::size_t edgeCount = graph.edgeCount();

    std::unordered_set<htd::vertex_t> missingEdges(edgeCount);

    htd::hyperedge_container edges;

    edges.reserve(edgeCount);

    for (const htd::Hyperedge & edge : graph.hyperedges())
    {
        const htd::ConstCollection<htd::vertex_t> & elementCollection = edge.elements();

        htd::vertex_container elements(elementCollection.begin(), elementCollection.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        edges.push_back(htd::Hyperedge(edge.id(), htd::ConstCollection<htd::vertex_t>::getInstance(elements)));
    }

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        if (!ok)
        {
            const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            for (auto it = edges.begin(); !ok && it != edges.end(); ++it)
            {
                const htd::Hyperedge & edge = *it;

                if (missingEdges.count(edge.id()) > 0 && std::includes(bag.begin(), bag.end(), edge.begin(), edge.end()))
                {
                    missingEdges.erase(edge.id());
                }

                ok = missingEdges.empty();
            }
        }
    });

    if (!ok)
    {
        for (htd::index_t missingEdge : missingEdges)
        {
            result.push_back(edges[missingEdge]);
        }

        std::sort(result.begin(), result.end());
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

htd::ConstCollection<htd::vertex_t> htd::TreeDecompositionVerifier::violationsConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    std::unordered_set<htd::vertex_t> forgottenVertices(graph.vertexCount());

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(distanceToSubtreeRoot)

        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        if (parent != htd::Vertex::UNKNOWN)
        {
            const htd::ConstCollection<htd::vertex_t> & forgottenBagContent = decomposition.forgottenVertices(parent, vertex);

            for (htd::vertex_t bagElement : bag)
            {
                if (forgottenVertices.count(bagElement) > 0)
                {
                    result.push_back(bagElement);
                }
            }

            for (htd::vertex_t forgottenVertex : forgottenBagContent)
            {
                forgottenVertices.insert(forgottenVertex);
            }
        }
        else
        {
            for (htd::vertex_t bagElement : bag)
            {
                if (forgottenVertices.count(bagElement) > 0)
                {
                    result.push_back(bagElement);
                }
            }
        }
    });

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

#endif /* HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP */
