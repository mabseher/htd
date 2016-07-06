/*
 * File:   InducedSubgraphLabelingOperation.cpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/InducedSubgraphLabelingOperation.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <vector>

htd::InducedSubgraphLabelingOperation::InducedSubgraphLabelingOperation(const htd::IMultiHypergraph & graph) : graph_(graph)
{

}

htd::InducedSubgraphLabelingOperation::~InducedSubgraphLabelingOperation()
{

}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    htd::index_t index = 0;

    std::unordered_map<htd::id_t, htd::index_t> hyperedgeIndices;

    std::vector<htd::Hyperedge> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        hyperedgeIndices[hyperedge.id()] = index;

        hyperedges.push_back(hyperedge);

        ++index;
    }

    std::vector<htd::state_t> hyperedgeState(hyperedges.size(), 1);
    std::vector<htd::state_t> childHyperedgeState(hyperedges.size(), 1);

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        bool edgeIntroductionCheckNeeded = false;

        std::fill(childHyperedgeState.begin(), childHyperedgeState.end(), 1);

        if (decomposition.childCount(vertex) > 0)
        {
            for (htd::vertex_t child : decomposition.children(vertex))
            {
                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(forgottenVertices, vertex, child);

                for (const htd::Hyperedge & hyperedge : htd::accessLabel<htd::ConstCollection<htd::Hyperedge>>(decomposition.vertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))
                {
                    index = hyperedgeIndices[hyperedge.id()];

                    if (childHyperedgeState[index] == 1)
                    {
                        if (forgottenVertices.size() > 0 && htd::has_non_empty_set_intersection(hyperedges[index].sortedElements().begin(), hyperedges[index].sortedElements().end(), forgottenVertices.begin(), forgottenVertices.end()))
                        {
                            hyperedgeState[index] = 3;

                            childHyperedgeState[index] = 3;
                        }
                        else
                        {
                            childHyperedgeState[index] = 2;
                        }
                    }
                }

                edgeIntroductionCheckNeeded = edgeIntroductionCheckNeeded || decomposition.introducedVertexCount(vertex, child) > 0;
            }
        }
        else
        {
            edgeIntroductionCheckNeeded = true;
        }

        if (!decomposition.isRoot(vertex))
        {
            index = 0;

            for (const htd::Hyperedge & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    if (childHyperedgeState[index] == 2)
                    {
                        labelContent.push_back(hyperedge);
                    }
                    else if (edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.sortedElements().begin(), hyperedge.sortedElements().end()))
                    {
                        labelContent.push_back(hyperedge);

                        hyperedgeState[index] = 2;
                    }
                }
                else if (hyperedgeState[index] == 2)
                {
                    if (childHyperedgeState[index] == 2)
                    {
                        labelContent.push_back(hyperedge);
                    }
                    else if (edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.sortedElements().begin(), hyperedge.sortedElements().end()))
                    {
                        labelContent.push_back(hyperedge);
                    }
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const htd::Hyperedge & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] < 3)
                {
                    labelContent.push_back(hyperedge);
                }

                hyperedgeState[index] = 3;

                ++index;
            }
        }

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    htd::index_t index = 0;

    std::unordered_map<htd::id_t, htd::index_t> hyperedgeIndices;

    std::vector<htd::Hyperedge> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        hyperedgeIndices[hyperedge.id()] = index;

        hyperedges.push_back(hyperedge);

        ++index;
    }

    std::vector<htd::state_t> hyperedgeState(hyperedges.size(), 1);
    std::vector<htd::state_t> childHyperedgeState(hyperedges.size(), 1);

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        bool edgeIntroductionCheckNeeded = false;

        std::fill(childHyperedgeState.begin(), childHyperedgeState.end(), 1);

        if (decomposition.childCount(vertex) > 0)
        {
            for (htd::vertex_t child : decomposition.children(vertex))
            {
                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(forgottenVertices, vertex, child);

                for (const htd::Hyperedge & hyperedge : htd::accessLabel<htd::ConstCollection<htd::Hyperedge>>(decomposition.vertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))
                {
                    index = hyperedgeIndices[hyperedge.id()];

                    if (childHyperedgeState[index] == 1)
                    {
                        if (forgottenVertices.size() > 0 && htd::has_non_empty_set_intersection(hyperedges[index].sortedElements().begin(), hyperedges[index].sortedElements().end(), forgottenVertices.begin(), forgottenVertices.end()))
                        {
                            hyperedgeState[index] = 3;

                            childHyperedgeState[index] = 3;
                        }
                        else
                        {
                            childHyperedgeState[index] = 2;
                        }
                    }
                }

                edgeIntroductionCheckNeeded = edgeIntroductionCheckNeeded || decomposition.introducedVertexCount(vertex, child) > 0;
            }
        }
        else
        {
            edgeIntroductionCheckNeeded = true;
        }

        if (!decomposition.isRoot(vertex))
        {
            index = 0;

            for (const htd::Hyperedge & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    if (childHyperedgeState[index] == 2)
                    {
                        labelContent.push_back(hyperedge);
                    }
                    else if (edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.sortedElements().begin(), hyperedge.sortedElements().end()))
                    {
                        labelContent.push_back(hyperedge);

                        hyperedgeState[index] = 2;
                    }
                }
                else if (hyperedgeState[index] == 2)
                {
                    if (childHyperedgeState[index] == 2)
                    {
                        labelContent.push_back(hyperedge);
                    }
                    else if (edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.sortedElements().begin(), hyperedge.sortedElements().end()))
                    {
                        labelContent.push_back(hyperedge);
                    }
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const htd::Hyperedge & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] < 3)
                {
                    labelContent.push_back(hyperedge);
                }

                hyperedgeState[index] = 3;

                ++index;
            }
        }

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(decomposition, labelingFunctions);
}

bool htd::InducedSubgraphLabelingOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::InducedSubgraphLabelingOperation::createsTreeNodes(void) const
{
    return false;
}

bool htd::InducedSubgraphLabelingOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::InducedSubgraphLabelingOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::InducedSubgraphLabelingOperation::createsLocationDependendLabels(void) const
{
    //TODO Change?
    return true;
}

htd::InducedSubgraphLabelingOperation * htd::InducedSubgraphLabelingOperation::clone(void) const
{
    return new htd::InducedSubgraphLabelingOperation(graph_);
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP */
