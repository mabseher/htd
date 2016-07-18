/*
 * File:   ExchangeNodeReplacementOperation.cpp
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

#ifndef HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP
#define	HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>

#include <algorithm>

htd::ExchangeNodeReplacementOperation::ExchangeNodeReplacementOperation(void) : htd::LibraryObject()
{
  
}
  
htd::ExchangeNodeReplacementOperation::~ExchangeNodeReplacementOperation()
{
  
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> exchangeNodes;

    decomposition.copyExchangeNodesTo(exchangeNodes);

    std::vector<htd::vertex_t> rememberedVertices;

    for (auto it = exchangeNodes.begin(); it != exchangeNodes.end() && !isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::vector<htd::vertex_t> children;

        decomposition.copyChildrenTo(children, node);

        for (htd::vertex_t child : children)
        {
            decomposition.copyRememberedVerticesTo(rememberedVertices, node, child);

            if (bag.size() != rememberedVertices.size() || !std::equal(bag.begin(), bag.end(), rememberedVertices.begin()))
            {
                htd::vertex_t newVertex = decomposition.addParent(child);

                decomposition.bagContent(newVertex) = rememberedVertices;

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                newInducedHyperedges.restrictTo(rememberedVertices);

                decomposition.inducedHyperedges(newVertex) = std::move(newInducedHyperedges);

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

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> exchangeNodes;

    decomposition.copyExchangeNodesTo(exchangeNodes);

    std::vector<htd::vertex_t> rememberedVertices;

    for (auto it = exchangeNodes.begin(); it != exchangeNodes.end() && !isTerminated(); ++it)
    {
        htd::vertex_t node = *it;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContent(node);

        std::vector<htd::vertex_t> children;

        decomposition.copyChildrenTo(children, node);

        for (htd::vertex_t child : children)
        {
            decomposition.copyRememberedVerticesTo(rememberedVertices, node, child);

            if (bag.size() != rememberedVertices.size() || !std::equal(bag.begin(), bag.end(), rememberedVertices.begin()))
            {
                htd::vertex_t newVertex = decomposition.addParent(child);

                decomposition.bagContent(newVertex) = rememberedVertices;

                htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(node);

                newInducedHyperedges.restrictTo(rememberedVertices);

                decomposition.inducedHyperedges(newVertex) = std::move(newInducedHyperedges);

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

void htd::ExchangeNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(removedVertices)

    std::vector<htd::vertex_t> rememberedVertices;

    for (auto it = relevantVertices.begin(); it != relevantVertices.end() && !isTerminated(); ++it)
    {
        htd::vertex_t vertex = *it;

        if (decomposition.isExchangeNode(vertex))
        {
            const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

            std::vector<htd::vertex_t> children;

            decomposition.copyChildrenTo(children, vertex);

            for (htd::vertex_t child : children)
            {
                decomposition.copyRememberedVerticesTo(rememberedVertices, vertex, child);

                if (bag.size() != rememberedVertices.size() || !std::equal(bag.begin(), bag.end(), rememberedVertices.begin()))
                {
                    htd::vertex_t newVertex = decomposition.addParent(child);

                    decomposition.bagContent(newVertex) = rememberedVertices;

                    htd::FilteredHyperedgeCollection newInducedHyperedges = decomposition.inducedHyperedges(vertex);

                    newInducedHyperedges.restrictTo(rememberedVertices);

                    decomposition.inducedHyperedges(newVertex) = std::move(newInducedHyperedges);

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

bool htd::ExchangeNodeReplacementOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::ExchangeNodeReplacementOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::ExchangeNodeReplacementOperation::removesTreeNodes(void) const
{
    return false;
}

bool htd::ExchangeNodeReplacementOperation::modifiesBagContents(void) const
{
    return false;
}

bool htd::ExchangeNodeReplacementOperation::createsSubsetMaximalBags(void) const
{
    return false;
}

bool htd::ExchangeNodeReplacementOperation::createsLocationDependendLabels(void) const
{
    return false;
}

htd::ExchangeNodeReplacementOperation * htd::ExchangeNodeReplacementOperation::clone(void) const
{
    htd::ExchangeNodeReplacementOperation * ret = new htd::ExchangeNodeReplacementOperation();

    ret->setManagementInstance(managementInstance());

    return ret;
}

#endif /* HTD_HTD_EXCHANGENODEREPLACEMENTOPERATION_CPP */
