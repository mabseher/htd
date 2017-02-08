/* 
 * File:   TreeDecompositionVerifier.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP
#define HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP

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
    return verifyVertexExistence(graph, decomposition) && verifyHyperedgeCoverage(graph, decomposition) && verifyConnectednessCriterion(graph, decomposition);
}

//Ensure that every vertex of the original graph is contained in at least one node of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return violationsVertexExistence(graph, decomposition).empty();
}

//Ensure that the vertices of an edge in the input graph occur jointly in at least on of the tree decomposition.
bool htd::TreeDecompositionVerifier::verifyHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    return violationsHyperedgeCoverage(graph, decomposition).empty();
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
        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(*it1);

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
            
htd::ConstCollection<htd::Hyperedge> htd::TreeDecompositionVerifier::violationsHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    bool ok = false;

    std::size_t edgeCount = graph.edgeCount();

    std::unordered_set<htd::id_t> missingEdges(edgeCount);

    std::vector<htd::id_t> identifiers(edgeCount);

    std::vector<std::vector<htd::vertex_t>> sortedEdges(edgeCount);

    htd::index_t index = 0;

    const htd::ConstCollection<htd::Hyperedge> & hyperedges = graph.hyperedges();

    for (const htd::Hyperedge & hyperedge : hyperedges)
    {
        std::vector<htd::vertex_t> & elements = sortedEdges[index];

        std::copy(hyperedge.sortedElements().begin(), hyperedge.sortedElements().end(), std::back_inserter(elements));

        identifiers[index] = hyperedge.id();

        missingEdges.insert(hyperedge.id());

        index++;
    }

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        if (!ok)
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            index = 0;

            while (!ok && index < edgeCount)
            {
                htd::id_t id = identifiers[index];

                const std::vector<htd::vertex_t> & edge = sortedEdges[index];

                if (missingEdges.count(id) > 0 && std::includes(bag.begin(), bag.end(), edge.begin(), edge.end()))
                {
                    missingEdges.erase(id);
                }

                ok = missingEdges.empty();

                ++index;
            }
        }
    });

    if (!ok)
    {
        index = 0;

        for (const htd::Hyperedge & hyperedge : hyperedges)
        {
            if (missingEdges.count(static_cast<htd::id_t>(index)) > 0)
            {
                result.push_back(hyperedge);
            }

            ++index;
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

    std::vector<htd::vertex_t> forgottenBagContent;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(distanceToSubtreeRoot)

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        if (parent != htd::Vertex::UNKNOWN)
        {
            decomposition.copyForgottenVerticesTo(parent, forgottenBagContent, vertex);

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

            forgottenBagContent.clear();
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

    std::sort(result.begin(), result.end());

    result.erase(std::unique(result.begin(), result.end()), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

#endif /* HTD_HTD_TREEDECOMPOSITIONVERIFIER_CPP */
