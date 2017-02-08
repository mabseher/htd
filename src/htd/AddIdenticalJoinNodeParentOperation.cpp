/*
 * File:   AddIdenticalJoinNodeParentOperation.cpp
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

#ifndef HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP
#define HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddIdenticalJoinNodeParentOperation.hpp>

/**
 *  Private implementation details of class htd::AddIdenticalJoinNodeParentOperation.
 */
struct htd::AddIdenticalJoinNodeParentOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     *
     *  @param[in] enforceAdditionalNode    Set this option to true to enforce a new parent node for join
     *  nodes also in those cases where the bag contents of the join node and its old parent did already
     *  match. If this option is set to false, no action will be triggered for join nodes for which the
     *  nodes' bag content already matches the parent's bag content.
     */
    Implementation(const htd::LibraryInstance * const manager, bool enforceAdditionalNode) : managementInstance_(manager), enforceAdditionalNode_(enforceAdditionalNode)
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
     *  If this flag is set to true, a new parent node for join nodes is enforced also in those cases where the bag contents of the join
     *  node and its old parent did already match. If this flag is set to false, no action will be triggered for join nodes for which
     *  the nodes' bag content already matches the parent's bag content.
     */
    bool enforceAdditionalNode_;
};

htd::AddIdenticalJoinNodeParentOperation::AddIdenticalJoinNodeParentOperation(const htd::LibraryInstance * const manager, bool enforceAdditionalNode) : implementation_(new Implementation(manager, enforceAdditionalNode))
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

        if (implementation_->enforceAdditionalNode_ || decomposition.isRoot(node) || decomposition.bagContent(decomposition.parent(node)) != bag)
        {
            htd::vertex_t newParent = decomposition.addParent(node);

            decomposition.mutableBagContent(newParent) = bag;

            decomposition.mutableInducedHyperedges(newParent) = decomposition.inducedHyperedges(node);

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

            if (implementation_->enforceAdditionalNode_ || decomposition.isRoot(vertex) || decomposition.bagContent(decomposition.parent(vertex)) != bag)
            {
                htd::vertex_t newParent = decomposition.addParent(vertex);

                decomposition.mutableBagContent(newParent) = bag;

                decomposition.mutableInducedHyperedges(newParent) = decomposition.inducedHyperedges(vertex);

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

const htd::LibraryInstance * htd::AddIdenticalJoinNodeParentOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::AddIdenticalJoinNodeParentOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::AddIdenticalJoinNodeParentOperation * htd::AddIdenticalJoinNodeParentOperation::clone(void) const
{
    return new htd::AddIdenticalJoinNodeParentOperation(implementation_->managementInstance_, implementation_->enforceAdditionalNode_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::AddIdenticalJoinNodeParentOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::AddIdenticalJoinNodeParentOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_ADDIDENTICALJOINNODEPARENTOPERATION_CPP */
