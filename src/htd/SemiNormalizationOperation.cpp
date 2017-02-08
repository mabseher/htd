/*
 * File:   SemiNormalizationOperation.cpp
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

#ifndef HTD_HTD_SEMINORMALIZATIONOPERATION_CPP
#define HTD_HTD_SEMINORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/LimitChildCountOperation.hpp>

/**
 *  Private implementation details of class htd::SemiNormalizationOperation.
 */
struct htd::SemiNormalizationOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     */
    Implementation()
    {

    }

    virtual ~Implementation()
    {

    }
};

htd::SemiNormalizationOperation::SemiNormalizationOperation(const htd::LibraryInstance * const manager)
    : htd::WeakNormalizationOperation(manager)
{

}

htd::SemiNormalizationOperation::SemiNormalizationOperation(const htd::LibraryInstance * const manager, bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent)
    : htd::WeakNormalizationOperation(manager, emptyRoot, emptyLeaves, identicalJoinNodeParent)
{

}

htd::SemiNormalizationOperation::~SemiNormalizationOperation()
{

}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::WeakNormalizationOperation::apply(graph, decomposition, labelingFunctions);
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    htd::WeakNormalizationOperation::apply(graph, decomposition, relevantVertices, labelingFunctions, createdVertices, removedVertices);
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::WeakNormalizationOperation::apply(graph, decomposition, labelingFunctions);

    htd::LimitChildCountOperation limitChildCountOperation(managementInstance(), 2);

    limitChildCountOperation.apply(graph, decomposition, labelingFunctions);
}

void htd::SemiNormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    htd::WeakNormalizationOperation::apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitChildCountOperation limitChildCountOperation(managementInstance(), 2);

    limitChildCountOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

bool htd::SemiNormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::SemiNormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::SemiNormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::SemiNormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::SemiNormalizationOperation * htd::SemiNormalizationOperation::clone(void) const
{
    return new htd::SemiNormalizationOperation(managementInstance(), emptyRootRequired(), emptyLeavesRequired(), identicalJoinNodeParentRequired());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::SemiNormalizationOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::SemiNormalizationOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::SemiNormalizationOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_SEMINORMALIZATIONOPERATION_CPP */
