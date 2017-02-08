/*
 * File:   LimitChildCountOperation.cpp
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

#ifndef HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP
#define HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LimitChildCountOperation.hpp>

#include <algorithm>
#include <stdexcept>
#include <iterator>

/**
 *  Private implementation details of class htd::LimitChildCountOperation.
 */
struct htd::LimitChildCountOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     *  @param[in] limit    The maximum number of children for a decomposition node.
     */
    Implementation(const htd::LibraryInstance * const manager, std::size_t limit) : managementInstance_(manager), limit_(limit)
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
     *  The maximum number of children for a decomposition node.
     */
    std::size_t limit_;
};

htd::LimitChildCountOperation::LimitChildCountOperation(const htd::LibraryInstance * const manager, std::size_t limit) : implementation_(new Implementation(manager, limit))
{
    HTD_ASSERT(limit > 0)
}

htd::LimitChildCountOperation::~LimitChildCountOperation()
{

}

void htd::LimitChildCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitChildCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitChildCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> joinNodes;

    decomposition.copyJoinNodesTo(joinNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = joinNodes.begin(); it != joinNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        std::size_t childCount = decomposition.childCount(node);

        if (childCount > implementation_->limit_)
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

            const htd::FilteredHyperedgeCollection & inducedHyperedges = decomposition.inducedHyperedges(node);

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(node, children);

            htd::index_t index = implementation_->limit_ - 1;

            htd::vertex_t attachmentPoint = node;

            while (childCount - index > implementation_->limit_)
            {
                htd::vertex_t newNode = decomposition.addChild(attachmentPoint);

                decomposition.mutableBagContent(newNode) = bag;

                decomposition.mutableInducedHyperedges(newNode) = inducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                attachmentPoint = newNode;

                for (htd::index_t childPosition = index; childPosition < index + implementation_->limit_ - 1; ++childPosition)
                {
                    decomposition.setParent(children[childPosition], attachmentPoint);
                }

                index += implementation_->limit_ - 1;
            }

            if (index < childCount)
            {
                htd::vertex_t newNode = decomposition.addChild(attachmentPoint);

                decomposition.mutableBagContent(newNode) = bag;

                decomposition.mutableInducedHyperedges(newNode) = inducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                attachmentPoint = newNode;

                for (htd::index_t childPosition = index; childPosition < childCount; ++childPosition)
                {
                    decomposition.setParent(children[childPosition], attachmentPoint);
                }
            }
        }
    }
}

void htd::LimitChildCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        std::size_t childCount = decomposition.childCount(vertex);

        if (childCount > implementation_->limit_)
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            const htd::FilteredHyperedgeCollection & inducedHyperedges = decomposition.inducedHyperedges(vertex);

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(vertex, children);

            htd::index_t index = implementation_->limit_ - 1;

            htd::vertex_t attachmentPoint = vertex;

            while (childCount - index > implementation_->limit_)
            {
                htd::vertex_t newNode = decomposition.addChild(attachmentPoint);

                decomposition.mutableBagContent(newNode) = bag;

                decomposition.mutableInducedHyperedges(newNode) = inducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                attachmentPoint = newNode;

                for (htd::index_t childPosition = index; childPosition < index + implementation_->limit_ - 1; ++childPosition)
                {
                    decomposition.setParent(children[childPosition], attachmentPoint);
                }

                createdVertices.push_back(newNode);

                index += implementation_->limit_ - 1;
            }

            if (index < childCount)
            {
                htd::vertex_t newNode = decomposition.addChild(attachmentPoint);

                decomposition.mutableBagContent(newNode) = bag;

                decomposition.mutableInducedHyperedges(newNode) = inducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newNode), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                attachmentPoint = newNode;

                for (htd::index_t childPosition = index; childPosition < childCount; ++childPosition)
                {
                    decomposition.setParent(children[childPosition], attachmentPoint);
                }

                createdVertices.push_back(newNode);
            }
        }
    }
}

bool htd::LimitChildCountOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::LimitChildCountOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::LimitChildCountOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::LimitChildCountOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::LimitChildCountOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::LimitChildCountOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::LimitChildCountOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::LimitChildCountOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::LimitChildCountOperation * htd::LimitChildCountOperation::clone(void) const
{
    return new htd::LimitChildCountOperation(managementInstance(), implementation_->limit_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::LimitChildCountOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::LimitChildCountOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_LIMITCHILDCOUNTOPERATION_CPP */
