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

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

    htd::index_t index = 0;

    htd::vertex_t nextParent = htd::Vertex::UNKNOWN;

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        htd::vertex_container elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));

        ++index;
    }

    std::vector<char> hyperedgeState(hyperedges.size(), 0);

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        if (!decomposition.isRoot(vertex))
        {
            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(parent, vertex);

            index = 0;

            bool edgeIntroductionCheckNeeded = decomposition.isJoinNode(vertex) || decomposition.isIntroduceNode(vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 0)
                {
                    if (edgeIntroductionCheckNeeded)
                    {
                        if (std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                        {
                            labelContent.push_back(hyperedge.second);

                            hyperedgeState[index] |= 1;

                            if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                            {
                                hyperedgeState[index] |= 2;
                            }
                        }
                    }
                }
                else if (hyperedgeState[index] == 1)
                {
                    if (edgeIntroductionCheckNeeded)
                    {
                        if (std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                        {
                            labelContent.push_back(hyperedge.second);
                        }
                    }

                    if (vertex == nextParent)
                    {
                        if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                        {
                            hyperedgeState[index] |= 2;
                        }
                    }
                }
                else if (hyperedgeState[index] == 3)
                {
                    hyperedgeState[index] = 2;
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] < 2)
                {
                    labelContent.push_back(hyperedge.second);
                }

                hyperedgeState[index] = 2;

                ++index;
            }
        }

        /*
        std::cout << "VERTEX: " << vertex << std::endl;
        for (htd::index_t index = 0; index < hyperedges.size(); ++index)
        {
            std::cout << (int)hyperedgeState[index] << " ";
        }
        std::cout << std::endl << std::endl;

        if (vertex == nextParent)
        {
            std::cout << "PARENT: " << vertex << std::endl;
            for (htd::index_t index = 0; index < hyperedges.size(); ++index)
            {
                std::cout << (int)hyperedgeState[index] << " ";
            }
            std::cout << std::endl << std::endl;
        }
        */

        nextParent = parent;

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::InducedSubgraphLabelingOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

    htd::index_t index = 0;

    htd::vertex_t nextParent = htd::Vertex::UNKNOWN;

    std::vector<std::pair<htd::Hyperedge, htd::Hyperedge>> hyperedges;

    for (const htd::Hyperedge & hyperedge : graph_.hyperedges())
    {
        htd::vertex_container elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges.push_back(std::make_pair(htd::Hyperedge(hyperedge.id(), elements), hyperedge));

        ++index;
    }

    std::vector<char> hyperedgeState(hyperedges.size(), 0);

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        htd::VectorAdapter<htd::Hyperedge> label;

        std::vector<htd::Hyperedge> & labelContent = label.container();

        const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

        if (!decomposition.isRoot(vertex))
        {
            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(parent, vertex);

            index = 0;

            bool edgeIntroductionCheckNeeded = decomposition.isJoinNode(vertex) || decomposition.isIntroduceNode(vertex);

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] == 0)
                {
                    if (edgeIntroductionCheckNeeded)
                    {
                        if (std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                        {
                            labelContent.push_back(hyperedge.second);

                            hyperedgeState[index] |= 1;

                            if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                            {
                                hyperedgeState[index] |= 2;
                            }
                        }
                    }
                }
                else if (hyperedgeState[index] == 1)
                {
                    if (edgeIntroductionCheckNeeded)
                    {
                        if (std::includes(bag.begin(), bag.end(), hyperedge.first.begin(), hyperedge.first.end()))
                        {
                            labelContent.push_back(hyperedge.second);
                        }
                    }

                    if (vertex == nextParent)
                    {
                        if (htd::has_non_empty_set_intersection(hyperedge.first.begin(), hyperedge.first.end(), forgottenVertexCollection.begin(), forgottenVertexCollection.end()))
                        {
                            hyperedgeState[index] |= 2;
                        }
                    }
                }
                else if (hyperedgeState[index] == 3)
                {
                    hyperedgeState[index] = 2;
                }

                ++index;
            }
        }
        else
        {
            index = 0;

            for (const std::pair<htd::Hyperedge, htd::Hyperedge> & hyperedge : hyperedges)
            {
                if (hyperedgeState[index] < 2)
                {
                    labelContent.push_back(hyperedge.second);
                }

                hyperedgeState[index] = 2;

                ++index;
            }
        }

        /*
        std::cout << "VERTEX: " << vertex << std::endl;
        for (htd::index_t index = 0; index < hyperedges.size(); ++index)
        {
            std::cout << (int)hyperedgeState[index] << " ";
        }
        std::cout << std::endl << std::endl;

        if (vertex == nextParent)
        {
            std::cout << "PARENT: " << vertex << std::endl;
            for (htd::index_t index = 0; index < hyperedges.size(); ++index)
            {
                std::cout << (int)hyperedgeState[index] << " ";
            }
            std::cout << std::endl << std::endl;
        }
        */

        nextParent = parent;

        decomposition.setVertexLabel(htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label)));
    });
}

htd::InducedSubgraphLabelingOperation * htd::InducedSubgraphLabelingOperation::clone(void) const
{
    return new htd::InducedSubgraphLabelingOperation(graph_);
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGOPERATION_CPP */
