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
#define	HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>

#include <algorithm>
#include <stdexcept>

htd::LimitMaximumForgottenVertexCountOperation::LimitMaximumForgottenVertexCountOperation(std::size_t limit) : limit_(limit)
{
  
}
  
htd::LimitMaximumForgottenVertexCountOperation::~LimitMaximumForgottenVertexCountOperation()
{
  
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> forgetNodes;

    decomposition.copyForgetNodesTo(forgetNodes);

    for (htd::vertex_t node : forgetNodes)
    {
        std::vector<htd::vertex_t> bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > limit_)
        {
            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(forgottenVertices, node);

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / limit_;

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

                auto start = forgottenVertices.end() - limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.bagContent(newNode) = newContent;

                newInducedHyperedges.restrictTo(newContent);

                decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - limit_;
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.bagContent(newNode) = newContent;

                        newInducedHyperedges.restrictTo(newContent);

                        decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + limit_)
                        {
                            start = start - limit_;
                            finish = finish - limit_;
                        }
                    }
                }
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> forgetNodes;

    decomposition.copyForgetNodesTo(forgetNodes);

    for (htd::vertex_t node : forgetNodes)
    {
        std::vector<htd::vertex_t> bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > limit_)
        {
            std::vector<htd::vertex_t> forgottenVertices;

            decomposition.copyForgottenVerticesTo(forgottenVertices, node);

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / limit_;

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

                auto start = forgottenVertices.end() - limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(child);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.bagContent(newNode) = newContent;

                newInducedHyperedges.restrictTo(newContent);

                decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - limit_;
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.bagContent(newNode) = newContent;

                        newInducedHyperedges.restrictTo(newContent);

                        decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + limit_)
                        {
                            start = start - limit_;
                            finish = finish - limit_;
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

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(removedVertices)

    for (htd::vertex_t vertex : relevantVertices)
    {
        if (decomposition.isForgetNode(vertex))
        {
            std::vector<htd::vertex_t> bagContent;

            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

            std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(vertex);

            if (forgottenVertexCount > limit_)
            {
                std::vector<htd::vertex_t> forgottenVertices;

                decomposition.copyForgottenVerticesTo(forgottenVertices, vertex);

                std::size_t remainder = forgottenVertexCount % limit_;

                forgottenVertexCount -= remainder;

                std::size_t intermediatedVertexCount = forgottenVertexCount / limit_;

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

                    auto start = forgottenVertices.end() - limit_;
                    auto finish = forgottenVertices.end();

                    htd::vertex_t newNode = decomposition.addParent(child);

                    std::vector<htd::vertex_t> newContent;

                    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(child);

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(child);

                    std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                    decomposition.bagContent(newNode) = newContent;

                    newInducedHyperedges.restrictTo(newContent);

                    decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

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
                        start = start - limit_;
                        finish = finish - limit_;

                        for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                        {
                            const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContent(newNode);

                            newNode = decomposition.addParent(newNode);

                            newContent.clear();

                            std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                            decomposition.bagContent(newNode) = newContent;

                            newInducedHyperedges.restrictTo(newContent);

                            decomposition.inducedHyperedges(newNode) = newInducedHyperedges;

                            for (auto & labelingFunction : labelingFunctions)
                            {
                                htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                                htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                                delete labelCollection;

                                decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                            }

                            createdVertices.push_back(newNode);

                            if (index < forgottenVertexCount + limit_)
                            {
                                start = start - limit_;
                                finish = finish - limit_;
                            }
                        }
                    }
                }
                else
                {
                    throw std::logic_error("void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition &, const std::vector<htd::vertex_t> &, const std::vector<htd::ILabelingFunction *> &, std::vector<htd::vertex_t> &, std::vector<htd::vertex_t> &) const");
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

htd::LimitMaximumForgottenVertexCountOperation * htd::LimitMaximumForgottenVertexCountOperation::clone(void) const
{
    return new htd::LimitMaximumForgottenVertexCountOperation(limit_);
}

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP */
