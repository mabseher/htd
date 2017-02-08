/*
 * File:   WeakNormalizationOperation.cpp
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

#ifndef HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP
#define HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/AddEmptyLeavesOperation.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>

/**
 *  Private implementation details of class htd::WeakNormalizationOperation.
 */
struct htd::WeakNormalizationOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager                   The management instance to which the current object instance belongs.
     *  @param[in] emptyRoot                A boolean flag whether the decomposition shall have a root node with empty bag.
     *  @param[in] emptyLeaves              A boolean flag whether the decomposition's leave nodes shall have an empty bag.
     *  @param[in] identicalJoinNodeParent  A boolean flag whether each join node shall have a parent with equal bag content.
     */
    Implementation(const htd::LibraryInstance * const manager, bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent) : managementInstance_(manager), emptyRoot_(emptyRoot), emptyLeaves_(emptyLeaves), identicalJoinNodeParent_(identicalJoinNodeParent)
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
     *  A boolean flag whether the decomposition shall have a root node with empty bag.
     */
    bool emptyRoot_;

    /**
     *  A boolean flag whether the decomposition's leave nodes shall have an empty bag.
     */
    bool emptyLeaves_;

    /**
     *  A boolean flag whether each join node shall have a parent with equal bag content.
     */
    bool identicalJoinNodeParent_;
};

htd::WeakNormalizationOperation::WeakNormalizationOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager, false, false, false))
{

}

htd::WeakNormalizationOperation::WeakNormalizationOperation(const htd::LibraryInstance * const manager, bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent) : implementation_(new Implementation(manager, emptyRoot, emptyLeaves, identicalJoinNodeParent))
{

}

htd::WeakNormalizationOperation::~WeakNormalizationOperation()
{

}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (implementation_->emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation(implementation_->managementInstance_);

        addEmptyRootOperation.apply(graph, decomposition, labelingFunctions);
    }

    if (implementation_->emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation(implementation_->managementInstance_);

        addEmptyLeavesOperation.apply(graph, decomposition, labelingFunctions);
    }
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    if (implementation_->emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation(implementation_->managementInstance_);

        addEmptyRootOperation.apply(graph, decomposition, relevantVertices, labelingFunctions, createdVertices, removedVertices);
    }

    if (implementation_->emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation(implementation_->managementInstance_);

        addEmptyLeavesOperation.apply(graph, decomposition, relevantVertices, labelingFunctions, createdVertices, removedVertices);
    }
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (implementation_->emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation(implementation_->managementInstance_);

        addEmptyRootOperation.apply(graph, decomposition, labelingFunctions);
    }

    if (implementation_->emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation(implementation_->managementInstance_);

        addEmptyLeavesOperation.apply(graph, decomposition, labelingFunctions);
    }

    htd::JoinNodeNormalizationOperation joinNodeNormalizationOperation(implementation_->managementInstance_, implementation_->identicalJoinNodeParent_);

    joinNodeNormalizationOperation.apply(graph, decomposition, labelingFunctions);
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    if (implementation_->emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation(implementation_->managementInstance_);

        addEmptyRootOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

        newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

        if (newVertexCount > 0)
        {
            newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

            oldCreatedVerticesCount = createdVertices.size();
        }
    }

    if (implementation_->emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation(implementation_->managementInstance_);

        addEmptyLeavesOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

        newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

        if (newVertexCount > 0)
        {
            newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

            oldCreatedVerticesCount = createdVertices.size();
        }
    }

    htd::JoinNodeNormalizationOperation joinNodeNormalizationOperation(implementation_->managementInstance_, implementation_->identicalJoinNodeParent_);

    joinNodeNormalizationOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

bool htd::WeakNormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::WeakNormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::WeakNormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::WeakNormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::WeakNormalizationOperation::emptyRootRequired(void) const
{
    return implementation_->emptyRoot_;
}

bool htd::WeakNormalizationOperation::emptyLeavesRequired(void) const
{
    return implementation_->emptyLeaves_;
}

bool htd::WeakNormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::WeakNormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

bool htd::WeakNormalizationOperation::identicalJoinNodeParentRequired(void) const
{
    return implementation_->identicalJoinNodeParent_;
}

const htd::LibraryInstance * htd::WeakNormalizationOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::WeakNormalizationOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::WeakNormalizationOperation * htd::WeakNormalizationOperation::clone(void) const
{
    return new htd::WeakNormalizationOperation(implementation_->managementInstance_, implementation_->emptyRoot_, implementation_->emptyLeaves_, implementation_->identicalJoinNodeParent_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::WeakNormalizationOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::WeakNormalizationOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::WeakNormalizationOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP */
