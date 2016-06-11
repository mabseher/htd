/*
 * File:   IntroducedSubgraphLabelingOperation.cpp
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

#ifndef HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP
#define	HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IntroducedSubgraphLabelingOperation.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <unordered_map>
#include <vector>

htd::IntroducedSubgraphLabelingOperation::IntroducedSubgraphLabelingOperation(const htd::IMultiHypergraph & graph) : graph_(graph)
{

}

htd::IntroducedSubgraphLabelingOperation::~IntroducedSubgraphLabelingOperation()
{

}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    htd::index_t index = 0;

    std::unordered_map<htd::id_t, htd::index_t> hyperedgeIndices;

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        std::vector<htd::vertex_t> elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));

        hyperedgeIndices[hyperedge.id()] = index;

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

                for (const htd::Hyperedge & hyperedge : htd::accessLabel<htd::ConstCollection<htd::Hyperedge>>(decomposition.vertexLabel(htd::IntroducedSubgraphLabelingOperation::INTRODUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))
                {
                    index = hyperedgeIndices[hyperedge.id()];

                    if (childHyperedgeState[index] == 1)
                    {
                        if (forgottenVertices.size() > 0 && htd::has_non_empty_set_intersection(hyperedges[index].first.begin(), hyperedges[index].first.end(), forgottenVertices.begin(), forgottenVertices.end()))
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

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    if (childHyperedgeState[index] == 1 && edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                    {
                        labelContent.push_back(hyperedge.second);

                        hyperedgeState[index] = 2;
                    }
                }
                else if (hyperedgeState[index] == 2)
                {
                    if (childHyperedgeState[index] == 1 && edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                    {
                        labelContent.push_back(hyperedge.second);
                    }
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    labelContent.push_back(hyperedge.second);
                }

                hyperedgeState[index] = 3;

                ++index;
            }
        }

        decomposition.setVertexLabel(htd::IntroducedSubgraphLabelingOperation::INTRODUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions)

    htd::index_t index = 0;

    std::unordered_map<htd::id_t, htd::index_t> hyperedgeIndices;

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        std::vector<htd::vertex_t> elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));

        hyperedgeIndices[hyperedge.id()] = index;

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

                for (const htd::Hyperedge & hyperedge : htd::accessLabel<htd::ConstCollection<htd::Hyperedge>>(decomposition.vertexLabel(htd::IntroducedSubgraphLabelingOperation::INTRODUCED_SUBGRAPH_LABEL_IDENTIFIER, child)))
                {
                    index = hyperedgeIndices[hyperedge.id()];

                    if (childHyperedgeState[index] == 1)
                    {
                        if (forgottenVertices.size() > 0 && htd::has_non_empty_set_intersection(hyperedges[index].first.begin(), hyperedges[index].first.end(), forgottenVertices.begin(), forgottenVertices.end()))
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

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    if (childHyperedgeState[index] == 1 && edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                    {
                        labelContent.push_back(hyperedge.second);

                        hyperedgeState[index] = 2;
                    }
                }
                else if (hyperedgeState[index] == 2)
                {
                    if (childHyperedgeState[index] == 1 && edgeIntroductionCheckNeeded && std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                    {
                        labelContent.push_back(hyperedge.second);
                    }
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 1)
                {
                    labelContent.push_back(hyperedge.second);
                }

                hyperedgeState[index] = 3;

                ++index;
            }
        }

        decomposition.setVertexLabel(htd::IntroducedSubgraphLabelingOperation::INTRODUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::IntroducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

htd::IntroducedSubgraphLabelingOperation * htd::IntroducedSubgraphLabelingOperation::clone(void) const
{
    return new htd::IntroducedSubgraphLabelingOperation(graph_);
}

#endif /* HTD_HTD_INTRODUCEDSUBGRAPHLABELINGOPERATION_CPP */
