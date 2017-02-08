/*
 * File:   NormalizationOperation.cpp
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

#ifndef HTD_HTD_NORMALIZATIONOPERATION_CPP
#define HTD_HTD_NORMALIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/NormalizationOperation.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>

/**
 *  Private implementation details of class htd::NormalizationOperation.
 */
struct htd::NormalizationOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] treatLeafNodesAsIntroduceNodes   A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
     */
    Implementation(bool treatLeafNodesAsIntroduceNodes) : treatLeafNodesAsIntroduceNodes_(treatLeafNodesAsIntroduceNodes)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  A boolean flag whether leaf nodes shall be treated as introduce nodes in the context of this operation.
     */
    bool treatLeafNodesAsIntroduceNodes_;
};

htd::NormalizationOperation::NormalizationOperation(const htd::LibraryInstance * const manager)
    : htd::SemiNormalizationOperation(manager), implementation_(new Implementation(false))
{

}

htd::NormalizationOperation::NormalizationOperation(const htd::LibraryInstance * const manager, bool emptyRoot, bool emptyLeaves, bool identicalJoinNodeParent, bool treatLeafNodesAsIntroduceNodes)
    : htd::SemiNormalizationOperation(manager, emptyRoot, emptyLeaves, identicalJoinNodeParent), implementation_(new Implementation(treatLeafNodesAsIntroduceNodes))
{

}

htd::NormalizationOperation::~NormalizationOperation()
{

}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::SemiNormalizationOperation::apply(graph, decomposition, labelingFunctions);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation(managementInstance());

    exchangeNodeReplacementOperation.apply(graph, decomposition, labelingFunctions);

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(managementInstance(), 1);

    limitMaximumForgottenVertexCountOperation.apply(graph, decomposition, labelingFunctions);

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(managementInstance(), 1);

    limitMaximumIntroducedVertexCountOperation.apply(graph, decomposition, labelingFunctions);
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    htd::SemiNormalizationOperation::apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation(managementInstance());

    exchangeNodeReplacementOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(managementInstance(),1);

    limitMaximumForgottenVertexCountOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(managementInstance(), 1, implementation_->treatLeafNodesAsIntroduceNodes_);

    limitMaximumIntroducedVertexCountOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::SemiNormalizationOperation::apply(graph, decomposition, labelingFunctions);

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation(managementInstance());

    exchangeNodeReplacementOperation.apply(graph, decomposition, labelingFunctions);

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(managementInstance(), 1);

    limitMaximumForgottenVertexCountOperation.apply(graph, decomposition, labelingFunctions);

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(managementInstance(), 1, implementation_->treatLeafNodesAsIntroduceNodes_);

    limitMaximumIntroducedVertexCountOperation.apply(graph, decomposition, labelingFunctions);
}

void htd::NormalizationOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    std::size_t newVertexCount = 0;

    std::size_t oldCreatedVerticesCount = createdVertices.size();

    std::vector<htd::vertex_t> newRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    htd::SemiNormalizationOperation::apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::ExchangeNodeReplacementOperation exchangeNodeReplacementOperation(managementInstance());

    exchangeNodeReplacementOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumForgottenVertexCountOperation limitMaximumForgottenVertexCountOperation(managementInstance(),1);

    limitMaximumForgottenVertexCountOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);

    newVertexCount = createdVertices.size() - oldCreatedVerticesCount;

    if (newVertexCount > 0)
    {
        newRelevantVertices.insert(newRelevantVertices.end(), createdVertices.begin() + oldCreatedVerticesCount, createdVertices.end());

        oldCreatedVerticesCount = createdVertices.size();
    }

    htd::LimitMaximumIntroducedVertexCountOperation limitMaximumIntroducedVertexCountOperation(managementInstance(), 1, implementation_->treatLeafNodesAsIntroduceNodes_);

    limitMaximumIntroducedVertexCountOperation.apply(graph, decomposition, newRelevantVertices, labelingFunctions, createdVertices, removedVertices);
}

bool htd::NormalizationOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::NormalizationOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::NormalizationOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::NormalizationOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::NormalizationOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::NormalizationOperation::createsLocationDependendLabels(void) const
{
    return false;
}

bool htd::NormalizationOperation::leafNodesTreatedAsIntroduceNodes(void) const
{
    return implementation_->treatLeafNodesAsIntroduceNodes_;
}

htd::NormalizationOperation * htd::NormalizationOperation::clone(void) const
{
    return new htd::NormalizationOperation(managementInstance(), emptyRootRequired(), emptyLeavesRequired(), identicalJoinNodeParentRequired(), implementation_->treatLeafNodesAsIntroduceNodes_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::NormalizationOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::NormalizationOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::NormalizationOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_NORMALIZATIONOPERATION_CPP */
