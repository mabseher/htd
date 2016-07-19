/*
 * File:   JoinNodeNormalizationOperation.cpp
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

#ifndef HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP
#define	HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>

#include <algorithm>

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(void) : htd::LibraryObject(), identicalParent_(false)
{

}

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(bool identicalParent) : htd::LibraryObject(), identicalParent_(identicalParent)
{

}

htd::JoinNodeNormalizationOperation::~JoinNodeNormalizationOperation()
{

}

void htd::JoinNodeNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::JoinNodeNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::JoinNodeNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> joinNodes;

    decomposition.copyJoinNodesTo(joinNodes);

    for (htd::vertex_t node : joinNodes)
    {
        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        const htd::FilteredHyperedgeCollection & inducedHyperedges = decomposition.inducedHyperedges(node);

        DEBUGGING_CODE(
        std::cout << "JOIN NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bag, false);
        std::cout << std::endl << std::endl;
        )

        if (identicalParent_)
        {
            if (decomposition.bagContent(decomposition.parent(node)) != bag)
            {
                htd::vertex_t newParent = decomposition.addParent(node);

                decomposition.bagContent(newParent) = bag;

                decomposition.inducedHyperedges(newParent) = inducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newParent);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newParent, newLabel);
                }
            }
        }

        std::vector<htd::vertex_t> children;

        decomposition.copyChildrenTo(children, node);

        for (htd::vertex_t child : children)
        {
            if (decomposition.bagContent(child) != bag)
            {
                DEBUGGING_CODE(
                std::cout << "   ADDING INTERMEDIATE NODE BETWEEN NODES " << node << " AND " << child << " ..." << std::endl;
                std::cout << "      BAG CONTENT: ";
                htd::print(bag, false);
                std::cout << std::endl << std::endl;
                )

                htd::vertex_t intermediateVertex = decomposition.addParent(child, bag, inducedHyperedges);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(intermediateVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), intermediateVertex, newLabel);
                }
            }
        }
    }
}

void htd::JoinNodeNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    for (htd::vertex_t vertex : relevantVertices)
    {
        if (decomposition.isJoinNode(vertex))
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            const htd::FilteredHyperedgeCollection & inducedHyperedges = decomposition.inducedHyperedges(vertex);

            DEBUGGING_CODE(
            std::cout << "JOIN NODE: " << vertex << std::endl;
            std::cout << "   ";
            htd::print(bag, false);
            std::cout << std::endl << std::endl;
            )

            if (identicalParent_)
            {
                if (decomposition.bagContent(decomposition.parent(vertex)) != bag)
                {
                    htd::vertex_t newParent = decomposition.addParent(vertex);

                    decomposition.bagContent(newParent) = bag;

                    decomposition.inducedHyperedges(newParent) = inducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newParent);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newParent, newLabel);
                    }

                    createdVertices.push_back(newParent);
                }
            }

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(children, vertex);

            for (htd::vertex_t child : children)
            {
                if (decomposition.bagContent(child) != bag)
                {
                    DEBUGGING_CODE(
                    std::cout << "   ADDING INTERMEDIATE NODE BETWEEN NODES " << vertex << " AND " << child << " ..." << std::endl;
                    std::cout << "      BAG CONTENT: ";
                    htd::print(bag, false);
                    std::cout << std::endl << std::endl;
                    )

                    htd::vertex_t intermediateVertex = decomposition.addParent(child, bag, inducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(intermediateVertex);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), intermediateVertex, newLabel);
                    }

                    createdVertices.push_back(intermediateVertex);
                }
            }
        }
    }
}

bool htd::JoinNodeNormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::JoinNodeNormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::JoinNodeNormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::JoinNodeNormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::JoinNodeNormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::JoinNodeNormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::JoinNodeNormalizationOperation * htd::JoinNodeNormalizationOperation::clone(void) const
{
    htd::JoinNodeNormalizationOperation * ret = new htd::JoinNodeNormalizationOperation(identicalParent_);

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP */
