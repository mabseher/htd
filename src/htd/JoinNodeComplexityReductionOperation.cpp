/*
 * File:   JoinNodeComplexityReductionOperation.cpp
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

#ifndef HTD_HTD_JOINNODECOMPLEXITYREDUCTIONOPERATION_CPP
#define HTD_HTD_JOINNODECOMPLEXITYREDUCTIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/JoinNodeComplexityReductionOperation.hpp>

#include <htd/Algorithm.hpp>

#include <algorithm>

/**
 *  Private implementation details of class htd::JoinNodeComplexityReductionOperation.
 */
struct htd::JoinNodeComplexityReductionOperation::Implementation
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

htd::JoinNodeComplexityReductionOperation::JoinNodeComplexityReductionOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{
  
}

htd::JoinNodeComplexityReductionOperation::~JoinNodeComplexityReductionOperation()
{
  
}

void htd::JoinNodeComplexityReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::JoinNodeComplexityReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::JoinNodeComplexityReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> joinNodes;

    decomposition.copyJoinNodesTo(joinNodes);

    std::vector<htd::vertex_t> rememberedVertices;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = joinNodes.begin(); it != joinNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::vector<htd::vertex_t> children;

        decomposition.copyChildrenTo(node, children);

        for (htd::vertex_t child : children)
        {
            const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(child);

            decomposition.copyRememberedVerticesTo(node, rememberedVertices, child);

            if (childBag.size() > bag.size() || bag.size() != rememberedVertices.size() || !htd::equal(bag.begin(), bag.end(), rememberedVertices.begin(), rememberedVertices.end()))
            {
                htd::vertex_t newVertex = decomposition.addParent(child);

                decomposition.mutableBagContent(newVertex) = rememberedVertices;

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                newInducedHyperedges.restrictTo(rememberedVertices);

                decomposition.mutableInducedHyperedges(newVertex) = std::move(newInducedHyperedges);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newVertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(rememberedVertices, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newVertex, newLabel);
                }
            }

            rememberedVertices.clear();
        }
    }
}

void htd::JoinNodeComplexityReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    std::vector<htd::vertex_t> rememberedVertices;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isJoinNode(vertex))
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(vertex, children);

            for (htd::vertex_t child : children)
            {
                const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(child);

                decomposition.copyRememberedVerticesTo(vertex, rememberedVertices, child);

                if (childBag.size() > bag.size() || bag.size() != rememberedVertices.size() || !htd::equal(bag.begin(), bag.end(), rememberedVertices.begin(), rememberedVertices.end()))
                {
                    htd::vertex_t newVertex = decomposition.addParent(child);

                    decomposition.mutableBagContent(newVertex) = rememberedVertices;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                    newInducedHyperedges.restrictTo(rememberedVertices);

                    decomposition.mutableInducedHyperedges(newVertex) = std::move(newInducedHyperedges);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newVertex);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(rememberedVertices, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newVertex, newLabel);
                    }

                    createdVertices.push_back(newVertex);
                }

                rememberedVertices.clear();
            }
        }
    }
}

bool htd::JoinNodeComplexityReductionOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::JoinNodeComplexityReductionOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::JoinNodeComplexityReductionOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::JoinNodeComplexityReductionOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::JoinNodeComplexityReductionOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::JoinNodeComplexityReductionOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::JoinNodeComplexityReductionOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::JoinNodeComplexityReductionOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::JoinNodeComplexityReductionOperation * htd::JoinNodeComplexityReductionOperation::clone(void) const
{
    return new htd::JoinNodeComplexityReductionOperation(managementInstance());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::JoinNodeComplexityReductionOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::JoinNodeComplexityReductionOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_JOINNODECOMPLEXITYREDUCTIONOPERATION_CPP */
