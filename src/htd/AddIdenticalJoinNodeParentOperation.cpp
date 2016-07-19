/*
 * File:   AddIdenticalJoinNodeParentOperation.cpp
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

#ifndef HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP
#define	HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddIdenticalJoinNodeParentOperation.hpp>

htd::AddIdenticalJoinNodeParentOperation::AddIdenticalJoinNodeParentOperation(bool enforceAdditionalNode) : htd::LibraryObject(), enforceAdditionalNode_(enforceAdditionalNode)
{

}

htd::AddIdenticalJoinNodeParentOperation::~AddIdenticalJoinNodeParentOperation()
{

}

void htd::AddIdenticalJoinNodeParentOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddIdenticalJoinNodeParentOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddIdenticalJoinNodeParentOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    const htd::ConstCollection<htd::vertex_t> & joinNodeCollection = decomposition.joinNodes();

    for (htd::vertex_t node : joinNodeCollection)
    {
        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        DEBUGGING_CODE(
        std::cout << "JOIN NODE: " << node << std::endl;
        std::cout << "   ";
        htd::print(bag, false);
        std::cout << std::endl << std::endl;
        )

        if (enforceAdditionalNode_ || decomposition.bagContent(decomposition.parent(node)) != bag)
        {
            htd::vertex_t newParent = decomposition.addParent(node);

            decomposition.bagContent(newParent) = bag;

            decomposition.inducedHyperedges(newParent) = decomposition.inducedHyperedges(node);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newParent);

                htd::ILabel * newLabel = labelingFunction->computeLabel(bag, *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newParent, newLabel);
            }
        }
    }
}

void htd::AddIdenticalJoinNodeParentOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    for (htd::vertex_t vertex : relevantVertices)
    {
        if (decomposition.isJoinNode(vertex))
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            DEBUGGING_CODE(
            std::cout << "JOIN NODE: " << vertex << std::endl;
            std::cout << "   ";
            htd::print(bag, false);
            std::cout << std::endl << std::endl;
            )

            if (enforceAdditionalNode_ || decomposition.bagContent(decomposition.parent(vertex)) != bag)
            {
                htd::vertex_t newParent = decomposition.addParent(vertex);

                decomposition.bagContent(newParent) = bag;

                decomposition.inducedHyperedges(newParent) = decomposition.inducedHyperedges(vertex);

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
    }
}

bool htd::AddIdenticalJoinNodeParentOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::AddIdenticalJoinNodeParentOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::AddIdenticalJoinNodeParentOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::AddIdenticalJoinNodeParentOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::AddIdenticalJoinNodeParentOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::AddIdenticalJoinNodeParentOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::AddIdenticalJoinNodeParentOperation * htd::AddIdenticalJoinNodeParentOperation::clone(void) const
{
    htd::AddIdenticalJoinNodeParentOperation * ret = new htd::AddIdenticalJoinNodeParentOperation();

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP */
