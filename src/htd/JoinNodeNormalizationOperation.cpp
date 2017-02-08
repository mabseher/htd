/*
 * File:   JoinNodeNormalizationOperation.cpp
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

#ifndef HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP
#define HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Collection.hpp>

#include <algorithm>

/**
 *  Private implementation details of class htd::JoinNodeNormalizationOperation.
 */
struct htd::JoinNodeNormalizationOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager           The management instance to which the current object instance belongs.
     *  @param[in] identicalParent  A boolean flag whether each join node shall have a parent with equal bag content.
     */
    Implementation(const htd::LibraryInstance * const manager, bool identicalParent) : managementInstance_(manager), identicalParent_(identicalParent)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  A boolean flag whether each join node shall have a parent with equal bag content.
     */
    bool identicalParent_;
};

htd::JoinNodeNormalizationOperation::JoinNodeNormalizationOperation(const htd::LibraryInstance * const manager, bool identicalParent) : implementation_(new Implementation(manager, identicalParent))
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

        if (implementation_->identicalParent_)
        {
            if (decomposition.isRoot(node) || decomposition.bagContent(decomposition.parent(node)) != bag)
            {
                htd::vertex_t newParent = decomposition.addParent(node);

                decomposition.mutableBagContent(newParent) = bag;

                decomposition.mutableInducedHyperedges(newParent) = inducedHyperedges;

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

        decomposition.copyChildrenTo(node, children);

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

            if (implementation_->identicalParent_)
            {
                if (decomposition.isRoot(vertex) || decomposition.bagContent(decomposition.parent(vertex)) != bag)
                {
                    htd::vertex_t newParent = decomposition.addParent(vertex);

                    decomposition.mutableBagContent(newParent) = bag;

                    decomposition.mutableInducedHyperedges(newParent) = inducedHyperedges;

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

            decomposition.copyChildrenTo(vertex, children);

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

const htd::LibraryInstance * htd::JoinNodeNormalizationOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::JoinNodeNormalizationOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::JoinNodeNormalizationOperation * htd::JoinNodeNormalizationOperation::clone(void) const
{
    return new htd::JoinNodeNormalizationOperation(managementInstance(), implementation_->identicalParent_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::JoinNodeNormalizationOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::JoinNodeNormalizationOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_JOINNODENORMALIZATIONOPERATION_CPP */
