/*
 * File:   WeakNormalizationOperation.cpp
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

#ifndef HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP
#define	HTD_HTD_WEAKNORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/AddEmptyLeavesOperation.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>

htd::WeakNormalizationOperation::WeakNormalizationOperation(void) : htd::LibraryObject(), emptyRoot_(false), emptyLeaves_(false), identicalJoinNodeParent_(false)
{

}

htd::WeakNormalizationOperation::WeakNormalizationOperation(bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent) : htd::LibraryObject(), emptyRoot_(emptyRoot), emptyLeaves_(emptyLeaves), identicalJoinNodeParent_(identicalJoinNodeParent)
{

}

htd::WeakNormalizationOperation::~WeakNormalizationOperation()
{

}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>());
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.setManagementInstance(managementInstance());

        addEmptyRootOperation.apply(graph, decomposition, labelingFunctions);
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.setManagementInstance(managementInstance());

        addEmptyLeavesOperation.apply(graph, decomposition, labelingFunctions);
    }
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.setManagementInstance(managementInstance());

        addEmptyRootOperation.apply(graph, decomposition, relevantVertices, labelingFunctions);
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.setManagementInstance(managementInstance());

        addEmptyLeavesOperation.apply(graph, decomposition, relevantVertices, labelingFunctions);
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
    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.setManagementInstance(managementInstance());

        addEmptyRootOperation.apply(graph, decomposition, labelingFunctions);
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.setManagementInstance(managementInstance());

        addEmptyLeavesOperation.apply(graph, decomposition, labelingFunctions);
    }

    htd::JoinNodeNormalizationOperation joinNodeNormalizationOperation(identicalJoinNodeParent_);

    joinNodeNormalizationOperation.setManagementInstance(managementInstance());

    joinNodeNormalizationOperation.apply(graph, decomposition, labelingFunctions);
}

void htd::WeakNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    if (emptyRoot_)
    {
        htd::AddEmptyRootOperation addEmptyRootOperation;

        addEmptyRootOperation.setManagementInstance(managementInstance());

        addEmptyRootOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

        newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

        if (newVertexCount > 0)
        {
            std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

            oldCreatedVerticesCount = createdVertices.size();
        }
    }

    if (emptyLeaves_)
    {
        htd::AddEmptyLeavesOperation addEmptyLeavesOperation;

        addEmptyLeavesOperation.setManagementInstance(managementInstance());

        addEmptyLeavesOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

        newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

        if (newVertexCount > 0)
        {
            std::copy(createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end(), std::back_inserter(newRelevantVertices));

            oldCreatedVerticesCount = createdVertices.size();
        }
    }

    htd::JoinNodeNormalizationOperation joinNodeNormalizationOperation(identicalJoinNodeParent_);

    joinNodeNormalizationOperation.setManagementInstance(managementInstance());

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
    return emptyRoot_;
}

bool htd::WeakNormalizationOperation::emptyLeavesRequired(void) const
{
    return emptyLeaves_;
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
    return identicalJoinNodeParent_;
}

htd::WeakNormalizationOperation * htd::WeakNormalizationOperation::clone(void) const
{
    htd::WeakNormalizationOperation * ret = new htd::WeakNormalizationOperation(emptyRoot_, emptyLeaves_, identicalJoinNodeParent_);

    ret->setManagementInstance(managementInstance());

    return ret;
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
