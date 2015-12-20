/*
 * File:   JoinNodeReplacementOperation.cpp
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

#ifndef HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP
#define	HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/JoinNodeReplacementOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <algorithm>
#include <unordered_set>

//TODO Remove
#include <iostream>
#include <htd/Helpers.hpp>

htd::JoinNodeReplacementOperation::JoinNodeReplacementOperation(const htd::IHypergraph & graph): graph_(graph), hyperedges_()
{
    htd::Collection<htd::Hyperedge> hyperedgeCollection = graph.hyperedges();

    hyperedges_.reserve(hyperedgeCollection.size());

    for (htd::Hyperedge originalHyperedge : hyperedgeCollection)
    {
        htd::Hyperedge newHyperedge(originalHyperedge.id());

        htd::Collection<htd::vertex_t> elementCollection = originalHyperedge.elements();

        htd::vertex_container elements;

        elements.reserve(elementCollection.size());

        std::copy(elementCollection.begin(), elementCollection.end(), std::back_inserter(elements));

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges_.push_back(newHyperedge);
    }

    std::sort(hyperedges_.begin(), hyperedges_.end());

    hyperedges_.erase(std::unique(hyperedges_.begin(), hyperedges_.end()), hyperedges_.end());

    //TODO Remove hyperedges which are subset of another!
}

htd::JoinNodeReplacementOperation::~JoinNodeReplacementOperation()
{

}

void htd::JoinNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    if (decomposition.vertexCount() > 0)
    {
        htd::vertex_t node = decomposition.root();

        std::size_t childCount = decomposition.childCount(node);

        while (childCount > 0)
        {
            htd::vertex_container children;

            const htd::Collection<htd::vertex_t> childContainer = decomposition.children(node);

            std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

            if (childCount >= 2)
            {
                DEBUGGING_CODE(std::cout << "JOIN NODE: " << node << std::endl;)

                htd::vertex_container bagContent;

                htd::Collection<htd::vertex_t> bag = decomposition.bagContent(node);

                std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

                DEBUGGING_CODE(
                std::cout << "   ";
                htd::print(children, false);
                std::cout << std::endl << std::endl;
                )

                htd::vertex_container newBagContent;

                getChildrenVertexLabelSetUnion(decomposition, node, newBagContent);

                decomposition.setBagContent(children[0], htd::Collection<htd::vertex_t>(newBagContent));

                for (htd::vertex_t child : children)
                {
                    if (child != children[0])
                    {
                        htd::vertex_container grandChildren;

                        const htd::Collection<htd::vertex_t> grandChildContainer = decomposition.children(child);

                        std::copy(grandChildContainer.begin(), grandChildContainer.end(), std::back_inserter(grandChildren));

                        for (htd::vertex_t grandChild : grandChildren)
                        {
                            decomposition.setParent(grandChild, children[0]);

                            std::cout << "MOVING GRANDCHILD " << grandChild << " TO " << children[0] << " ..." << std::endl;
                        }

                        std::cout << "REMOVING NODE " << child << " ..." << std::endl;

                        decomposition.removeChild(node, child);
                    }
                }
            }

            node = children[0];

            childCount = decomposition.childCount(node);
        }
    }
}

void htd::JoinNodeReplacementOperation::getChildrenVertexLabelSetUnion(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex, htd::vertex_container & output) const
{
    std::unordered_set<htd::vertex_t> result;

    for (htd::vertex_t child : decomposition.children(vertex))
    {
        auto childLabel = decomposition.bagContent(child);

        result.insert(childLabel.begin(), childLabel.end());
    }

    output.reserve(result.size());

    std::copy(result.begin(), result.end(), std::back_inserter(output));

    std::sort(output.begin(), output.end());

    output.erase(std::unique(output.begin(), output.end()), output.end());
}

#endif /* HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP */
