/*
 * File:   LimitMaximumForgottenVertexCountOperation.cpp
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

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
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
            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(forgottenVertices, node);

            std::size_t remainder = forgottenVertexCount % implementation_->limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / implementation_->limit_;

            if (intermediatedVertexCount > 0)
            {
                intermediatedVertexCount--;
            }

            if (remainder == 0)
            {
                intermediatedVertexCount--;
            }

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(children, node);

            if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.end() - implementation_->limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.mutableBagContent(newNode) = newContent;

                newInducedHyperedges.restrictTo(newContent);

                decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - implementation_->limit_;
                    finish = finish - implementation_->limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.mutableBagContent(newNode) = newContent;

                        newInducedHyperedges.restrictTo(newContent);

                        decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + implementation_->limit_)
                        {
                            start = start - implementation_->limit_;
                            finish = finish - implementation_->limit_;
                        }
                    }
                }
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(graph, decomposition, labelingFunctions);
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
            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(forgottenVertices, node);

            std::size_t remainder = forgottenVertexCount % implementation_->limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / implementation_->limit_;

            if (intermediatedVertexCount > 0)
            {
                intermediatedVertexCount--;
            }

            if (remainder == 0)
            {
                intermediatedVertexCount--;
            }

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(children, node);

            if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.end() - implementation_->limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(child);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.mutableBagContent(newNode) = newContent;

                newInducedHyperedges.restrictTo(newContent);

                decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - implementation_->limit_;
                    finish = finish - implementation_->limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.mutableBagContent(newNode) = newContent;

                        newInducedHyperedges.restrictTo(newContent);

                        decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + implementation_->limit_)
                        {
                            start = start - implementation_->limit_;
                            finish = finish - implementation_->limit_;
                        }
                    }
                }
            }
            else
            {
                throw std::logic_error("void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition &) const");
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
                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(forgottenVertices, vertex);

                std::size_t remainder = forgottenVertexCount % implementation_->limit_;

                forgottenVertexCount -= remainder;

                std::size_t intermediatedVertexCount = forgottenVertexCount / implementation_->limit_;

                if (intermediatedVertexCount > 0)
                {
                    intermediatedVertexCount--;
                }

                if (remainder == 0)
                {
                    intermediatedVertexCount--;
                }

                std::vector<htd::vertex_t> children;

                decomposition.copyChildrenTo(children, vertex);

                if (children.size() == 1)
                {
                    htd::vertex_t child = children[0];

                    auto start = forgottenVertices.end() - implementation_->limit_;
                    auto finish = forgottenVertices.end();

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(child);

                    std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.mutableBagContent(newNode) = newContent;

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                    for (auto & labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                    }

                    createdVertices.push_back(newNode);

                    if (intermediatedVertexCount > 0)
                    {
                        start = start - implementation_->limit_;
                        finish = finish - implementation_->limit_;

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                            newNode = decomposition.addParent(newNode);

                            newContent.clear();

                            std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                            decomposition.mutableBagContent(newNode) = newContent;

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.mutableInducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            createdVertices.push_back(newNode);

                            if (index < forgottenVertexCount + implementation_->limit_)
                            {
                                start = start - implementation_->limit_;
                                finish = finish - implementation_->limit_;
                            }
                        }
                    }
                }
                else
                {
                    throw std::logic_error("void htd::LimitMaximumForgottenVertexCountOperation::apply(const htd::IMultiHypergraph &, htd::IMutableTreeDecomposition &, const std::vector<htd::vertex_t> &, const std::vector<htd::ILabelingFunction *> &, std::vector<htd::vertex_t> &, std::vector<htd::vertex_t> &) const");
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
