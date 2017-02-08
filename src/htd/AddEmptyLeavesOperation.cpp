/*
 * File:   AddEmptyLeavesOperation.cpp
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

#ifndef HTD_HTD_ADDEMPTYLEAVESOPERATION_CPP
#define HTD_HTD_ADDEMPTYLEAVESOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/AddEmptyLeavesOperation.hpp>

#include <algorithm>
#include <vector>

/**
 *  Private implementation details of class htd::AddEmptyLeavesOperation.
 */
struct htd::AddEmptyLeavesOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;
};

htd::AddEmptyLeavesOperation::AddEmptyLeavesOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::AddEmptyLeavesOperation::~AddEmptyLeavesOperation()
{

}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> leafNodes;

    decomposition.copyLeavesTo(leafNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = leafNodes.begin(); it != leafNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t leaf = *it;

        if (decomposition.bagSize(leaf) > 0)
        {
            htd::vertex_t newLeaf = decomposition.addChild(leaf);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newLeaf);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newLeaf), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newLeaf, newLabel);
            }
        }
    }
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isLeaf(vertex) && decomposition.bagSize(vertex) > 0)
        {
            htd::vertex_t newLeaf = decomposition.addChild(vertex);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newLeaf);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newLeaf), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newLeaf, newLabel);
            }

            createdVertices.push_back(newLeaf);
        }
    }
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> leafNodes;

    decomposition.copyLeavesTo(leafNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = leafNodes.begin(); it != leafNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t leaf = *it;

        if (decomposition.bagSize(leaf) > 0)
        {
            htd::vertex_t newLeaf = decomposition.addChild(leaf);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newLeaf);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newLeaf), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newLeaf, newLabel);
            }
        }
    }
}

void htd::AddEmptyLeavesOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isLeaf(vertex) && decomposition.bagSize(vertex) > 0)
        {
            htd::vertex_t newLeaf = decomposition.addChild(vertex);

            for (auto & labelingFunction : labelingFunctions)
            {
                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newLeaf);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(newLeaf), *labelCollection);

                delete labelCollection;

                decomposition.setVertexLabel(labelingFunction->name(), newLeaf, newLabel);
            }

            createdVertices.push_back(newLeaf);
        }
    }
}

bool htd::AddEmptyLeavesOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::AddEmptyLeavesOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::AddEmptyLeavesOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::AddEmptyLeavesOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::AddEmptyLeavesOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::AddEmptyLeavesOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::AddEmptyLeavesOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::AddEmptyLeavesOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::AddEmptyLeavesOperation * htd::AddEmptyLeavesOperation::clone(void) const
{
    return new htd::AddEmptyLeavesOperation(implementation_->managementInstance_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::AddEmptyLeavesOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::AddEmptyLeavesOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::AddEmptyLeavesOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_ADDEMPTYLEAVESOPERATION_CPP */
