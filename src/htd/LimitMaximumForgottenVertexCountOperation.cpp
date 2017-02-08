/*
 * File:   LimitMaximumForgottenVertexCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP
#define HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>

#include <algorithm>
#include <stdexcept>

/**
 *  Private implementation details of class htd::LimitMaximumForgottenVertexCountOperation.
 */
struct htd::LimitMaximumForgottenVertexCountOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     *  @param[in] limit    The maximum number of forgotten vertices for a decomposition node.
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
     *  The maximum number of forgotten vertices for a decomposition node.
     */
    std::size_t limit_;
};

htd::LimitMaximumForgottenVertexCountOperation::LimitMaximumForgottenVertexCountOperation(const htd::LibraryInstance * const manager, std::size_t limit) : implementation_(new Implementation(manager, limit))
{
  
}

htd::LimitMaximumForgottenVertexCountOperation::~LimitMaximumForgottenVertexCountOperation()
{
  
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> forgetNodes;

    decomposition.copyForgetNodesTo(forgetNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = forgetNodes.begin(); it != forgetNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        std::vector<htd::vertex_t> bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > implementation_->limit_)
        {
            HTD_ASSERT(decomposition.childCount(node) == 1)

            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(node, forgottenVertices);

            htd::index_t index = implementation_->limit_;

            htd::vertex_t attachmentPoint = decomposition.childAtPosition(node, 0);

            while (index < forgottenVertexCount)
            {
                std::vector<htd::vertex_t> newBagContent;

                const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(attachmentPoint);

                std::set_difference(childBag.begin(), childBag.end(), forgottenVertices.begin(), forgottenVertices.begin() + index, std::back_inserter(newBagContent));

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                newInducedHyperedges.restrictTo(newBagContent);

                attachmentPoint = decomposition.addParent(attachmentPoint, std::move(newBagContent), std::move(newInducedHyperedges));

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(attachmentPoint);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(attachmentPoint), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), attachmentPoint, newLabel);
                }

                index += implementation_->limit_;

                if (index > forgottenVertexCount)
                {
                    index = forgottenVertexCount;
                }
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isForgetNode(vertex))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(vertex);

            if (forgottenVertexCount > implementation_->limit_)
            {
                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(vertex, forgottenVertices);

                htd::index_t index = implementation_->limit_;

                htd::vertex_t attachmentPoint = decomposition.childAtPosition(vertex, 0);

                while (index < forgottenVertexCount)
                {
                    std::vector<htd::vertex_t> newBagContent;

                    const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(attachmentPoint);

                    std::set_difference(childBag.begin(), childBag.end(), forgottenVertices.begin(), forgottenVertices.begin() + index, std::back_inserter(newBagContent));

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                    newInducedHyperedges.restrictTo(newBagContent);

                    attachmentPoint = decomposition.addParent(attachmentPoint, std::move(newBagContent), std::move(newInducedHyperedges));

                    createdVertices.push_back(attachmentPoint);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(attachmentPoint);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(attachmentPoint), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), attachmentPoint, newLabel);
                    }

                    index += implementation_->limit_;

                    if (index > forgottenVertexCount)
                    {
                        index = forgottenVertexCount;
                    }
                }
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    std::vector<htd::vertex_t> forgetNodes;

    decomposition.copyForgetNodesTo(forgetNodes);

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = forgetNodes.begin(); it != forgetNodes.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        std::vector<htd::vertex_t> bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > implementation_->limit_)
        {
            HTD_ASSERT(decomposition.childCount(node) == 1)

            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(node, forgottenVertices);

            htd::index_t index = implementation_->limit_;

            htd::vertex_t attachmentPoint = decomposition.childAtPosition(node, 0);

            while (index < forgottenVertexCount)
            {
                std::vector<htd::vertex_t> newBagContent;

                const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(attachmentPoint);

                std::set_difference(childBag.begin(), childBag.end(), forgottenVertices.begin(), forgottenVertices.begin() + index, std::back_inserter(newBagContent));

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                newInducedHyperedges.restrictTo(newBagContent);

                attachmentPoint = decomposition.addParent(attachmentPoint, std::move(newBagContent), std::move(newInducedHyperedges));

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(attachmentPoint);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(attachmentPoint), *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), attachmentPoint, newLabel);
                }

                index += implementation_->limit_;

                if (index > forgottenVertexCount)
                {
                    index = forgottenVertexCount;
                }
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(graph)
    HTD_UNUSED(removedVertices)

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !managementInstance.isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isForgetNode(vertex))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(vertex);

            if (forgottenVertexCount > implementation_->limit_)
            {
                HTD_ASSERT(decomposition.childCount(vertex) == 1)

                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(vertex, forgottenVertices);

                htd::index_t index = implementation_->limit_;

                htd::vertex_t attachmentPoint = decomposition.childAtPosition(vertex, 0);

                while (index < forgottenVertexCount)
                {
                    std::vector<htd::vertex_t> newBagContent;

                    const std::vector<htd::vertex_t> & childBag = decomposition.bagContent(attachmentPoint);

                    std::set_difference(childBag.begin(), childBag.end(), forgottenVertices.begin(), forgottenVertices.begin() + index, std::back_inserter(newBagContent));

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                    newInducedHyperedges.restrictTo(newBagContent);

                    attachmentPoint = decomposition.addParent(attachmentPoint, std::move(newBagContent), std::move(newInducedHyperedges));

                    createdVertices.push_back(attachmentPoint);

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(attachmentPoint);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(attachmentPoint), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), attachmentPoint, newLabel);
                    }

                    index += implementation_->limit_;

                    if (index > forgottenVertexCount)
                    {
                        index = forgottenVertexCount;
                    }
                }
            }
        }
    }
}

bool htd::LimitMaximumForgottenVertexCountOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::LimitMaximumForgottenVertexCountOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::LimitMaximumForgottenVertexCountOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::LimitMaximumForgottenVertexCountOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::LimitMaximumForgottenVertexCountOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::LimitMaximumForgottenVertexCountOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::LimitMaximumForgottenVertexCountOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::LimitMaximumForgottenVertexCountOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::LimitMaximumForgottenVertexCountOperation * htd::LimitMaximumForgottenVertexCountOperation::clone(void) const
{
    return new htd::LimitMaximumForgottenVertexCountOperation(implementation_->managementInstance_, implementation_->limit_);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::LimitMaximumForgottenVertexCountOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::IPathDecompositionManipulationOperation * htd::LimitMaximumForgottenVertexCountOperation::clonePathDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::LimitMaximumForgottenVertexCountOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP */
