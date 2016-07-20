/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/BreadthFirstGraphTraversal.hpp>

#include <algorithm>
#include <cstdarg>
#include <memory>
#include <stack>
#include <stdexcept>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(void) : htd::LibraryObject(), labelingFunctions_(), postProcessingOperations_()
{

}

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationTreeDecompositionAlgorithm::~BucketEliminationTreeDecompositionAlgorithm()
{
    for (auto & labelingFunction : labelingFunctions_)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    htd::IMutableTreeDecomposition * ret = computeMutableDecomposition(graph);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations;

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions.push_back(labelingFunction);
        }

        htd::ITreeDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations.push_back(manipulationOperation);
        }
    }

    if (ret != nullptr)
    {
        for (const auto & labelingFunction : labelingFunctions_)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & operation : postProcessingOperations_)
        {
            operation->apply(graph, *ret);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(graph, *ret);
        }
    }

    for (auto & labelingFunction : labelingFunctions)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : postProcessingOperations)
    {
        delete postProcessingOperation;
    }

    return ret;
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeDecomposition(graph, manipulationOperations);
}

void htd::BucketEliminationTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (auto & labelingFunction : labelingFunctions_)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::ITreeDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

bool htd::BucketEliminationTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return false;
}

htd::BucketEliminationTreeDecompositionAlgorithm * htd::BucketEliminationTreeDecompositionAlgorithm::clone(void) const
{
    htd::BucketEliminationTreeDecompositionAlgorithm * ret = new htd::BucketEliminationTreeDecompositionAlgorithm();

    for (const auto & labelingFunction : labelingFunctions_)
    {
        ret->addManipulationOperation(labelingFunction->clone());
    }

    for (const auto & postProcessingOperation : postProcessingOperations_)
    {
        ret->addManipulationOperation(postProcessingOperation->clone());
    }

    ret->setManagementInstance(managementInstance());

    return ret;
}

htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeMutableDecomposition(const htd::IMultiHypergraph & graph) const
{
    htd::IMutableTreeDecomposition * ret = htd::TreeDecompositionFactory::instance().getTreeDecomposition();

    if (graph.vertexCount() > 0)
    {
        htd::BucketEliminationGraphDecompositionAlgorithm graphDecompositionAlgorithm;

        graphDecompositionAlgorithm.setManagementInstance(managementInstance());

        htd::IGraphDecomposition * graphDecomposition = graphDecompositionAlgorithm.computeDecomposition(graph);

        HTD_ASSERT(graphDecomposition != nullptr)

        htd::IMutableGraphDecomposition & mutableGraphDecomposition = htd::GraphDecompositionFactory::instance().accessMutableGraphDecomposition(*graphDecomposition);

        if (!isTerminated())
        {
            if (mutableGraphDecomposition.edgeCount() + 1 != mutableGraphDecomposition.vertexCount() || mutableGraphDecomposition.isolatedVertexCount() > 0)
            {
                htd::IConnectedComponentAlgorithm * connectedComponentAlgorithm = htd::ConnectedComponentAlgorithmFactory::instance().getConnectedComponentAlgorithm(managementInstance());

                HTD_ASSERT(connectedComponentAlgorithm != nullptr)

                std::vector<std::vector<htd::vertex_t>> components;

                connectedComponentAlgorithm->determineComponents(*graphDecomposition, components);

                delete connectedComponentAlgorithm;

                std::size_t componentCount = components.size();

                if (componentCount > 1)
                {
                    for (htd::index_t index = 0; index < componentCount - 1; ++index)
                    {
                        const std::vector<htd::vertex_t> & component1 = components[index];
                        const std::vector<htd::vertex_t> & component2 = components[index + 1];

                        /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
                        // coverity[dont_call]
                        htd::vertex_t vertex1 = component1[std::rand() % component1.size()];

                        /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
                        // coverity[dont_call]
                        htd::vertex_t vertex2 = component2[std::rand() % component2.size()];

                        mutableGraphDecomposition.addEdge(vertex1, vertex2);
                    }
                }
            }

            htd::vertex_t node = htd::Vertex::UNKNOWN;

            std::unordered_map<htd::vertex_t, htd::vertex_t> vertexMapping;

            htd::BreadthFirstGraphTraversal graphTraversal;

            /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
            // coverity[dont_call]
            graphTraversal.traverse(*graphDecomposition, graphDecomposition->vertexAtPosition(std::rand() % graphDecomposition->vertexCount()), [&](htd::vertex_t vertex, htd::vertex_t predecessor, std::size_t distanceFromStartingVertex)
            {
                HTD_UNUSED(distanceFromStartingVertex)

                if (predecessor == htd::Vertex::UNKNOWN)
                {
                    node = ret->insertRoot(std::move(mutableGraphDecomposition.bagContent(vertex)),
                                           std::move(mutableGraphDecomposition.inducedHyperedges(vertex)));
                }
                else
                {
                    node = ret->addChild(vertexMapping.at(predecessor),
                                         std::move(mutableGraphDecomposition.bagContent(vertex)),
                                         std::move(mutableGraphDecomposition.inducedHyperedges(vertex)));
                }

                vertexMapping[vertex] = node;;
            });
        }
        else
        {
            ret->insertRoot();
        }

        delete graphDecomposition;
    }
    else
    {
        ret->insertRoot();
    }

    return ret;
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP */
