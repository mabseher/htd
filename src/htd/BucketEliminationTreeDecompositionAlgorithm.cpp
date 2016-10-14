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
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/BreadthFirstGraphTraversal.hpp>

#include <algorithm>
#include <cstdarg>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 *  Private implementation details of class htd::BucketEliminationTreeDecompositionAlgorithm.
 */
struct htd::BucketEliminationTreeDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), labelingFunctions_(), postProcessingOperations_()
    {

    }

    virtual ~Implementation()
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

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The labeling functions which are applied after the decomposition was computed.
     */
    std::vector<htd::ILabelingFunction *> labelingFunctions_;

    /**
     *  The manipuation operations which are applied after the decomposition was computed.
     */
    std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

    /**
     *  Compute a new mutable tree decompostion of the given graph.
     *
     *  @param[in] graph    The graph which shall be decomposed.
     *  @param[in] maxBagSize           The upper bound for the maximum bag size of the decomposition.
     *  @param[in] maxIterationCount    The maximum number of iterations resulting in a higher maximum bag size than maxBagSize after which a null-pointer is returned.
     *
     *  @return A pair consisting of a mutable tree decompostion of the given graph or a null-pointer in case that no decomposition with a appropriate maximum bag size could be found after maxIterationCount iterations and the number of iterations actually needed to find the decomposition at hand.
     */
    std::pair<htd::IMutableTreeDecomposition *, std::size_t> computeMutableDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const;
};

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)  : implementation_(new Implementation(manager))
{
    setManipulationOperations(manipulationOperations);
}

htd::BucketEliminationTreeDecompositionAlgorithm::~BucketEliminationTreeDecompositionAlgorithm()
{

}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, (std::size_t)-1, 1).first;
}

std::pair<htd::ITreeDecomposition *, std::size_t> htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), maxBagSize, maxIterationCount);
}

std::pair<htd::ITreeDecomposition *, std::size_t> htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    std::pair<htd::IMutableTreeDecomposition *, std::size_t> ret = implementation_->computeMutableDecomposition(graph, maxBagSize, maxIterationCount);

    htd::IMutableTreeDecomposition * decomposition = ret.first;

    if (decomposition != nullptr)
    {
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

        for (const auto & labelingFunction : implementation_->labelingFunctions_)
        {
            for (htd::vertex_t vertex : decomposition->vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition->bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : decomposition->vertices())
            {
                htd::ILabelCollection * labelCollection = decomposition->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition->bagContent(vertex), *labelCollection);

                delete labelCollection;

                decomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        for (const auto & operation : implementation_->postProcessingOperations_)
        {
            operation->apply(graph, *decomposition);
        }

        for (const auto & operation : postProcessingOperations)
        {
            operation->apply(graph, *decomposition);
        }

        for (auto & labelingFunction : labelingFunctions)
        {
            delete labelingFunction;
        }

        for (auto & postProcessingOperation : postProcessingOperations)
        {
            delete postProcessingOperation;
        }
    }
    else
    {
        for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
        {
            delete operation;
        }
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
    for (auto & labelingFunction : implementation_->labelingFunctions_)
    {
        delete labelingFunction;
    }

    for (auto & postProcessingOperation : implementation_->postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    implementation_->labelingFunctions_.clear();

    implementation_->postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    bool assigned = false;

    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        implementation_->labelingFunctions_.emplace_back(labelingFunction);

        assigned = true;
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        implementation_->postProcessingOperations_.emplace_back(newManipulationOperation);

        assigned = true;
    }

    if (!assigned)
    {
        delete manipulationOperation;
    }
}

void htd::BucketEliminationTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::BucketEliminationTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return false;
}

const htd::LibraryInstance * htd::BucketEliminationTreeDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::BucketEliminationTreeDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::BucketEliminationTreeDecompositionAlgorithm * htd::BucketEliminationTreeDecompositionAlgorithm::clone(void) const
{
    htd::BucketEliminationTreeDecompositionAlgorithm * ret = new htd::BucketEliminationTreeDecompositionAlgorithm(managementInstance());

    for (htd::ILabelingFunction * labelingFunction : implementation_->labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(labelingFunction->clone());
#else
        ret->addManipulationOperation(labelingFunction->cloneLabelingFunction());
#endif
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : implementation_->postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(postProcessingOperation->clone());
#else
        ret->addManipulationOperation(postProcessingOperation->cloneTreeDecompositionManipulationOperation());
#endif
    }

    ret->setManagementInstance(managementInstance());

    return ret;
}

std::pair<htd::IMutableTreeDecomposition *, std::size_t> htd::BucketEliminationTreeDecompositionAlgorithm::Implementation::computeMutableDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, std::size_t maxIterationCount) const
{
    htd::IMutableTreeDecomposition * ret = managementInstance_->treeDecompositionFactory().getTreeDecomposition();

    std::size_t iterations = 1;

    if (graph.vertexCount() > 0)
    {
        htd::BucketEliminationGraphDecompositionAlgorithm graphDecompositionAlgorithm(managementInstance_);

        std::pair<htd::IGraphDecomposition *, std::size_t> graphDecomposition = graphDecompositionAlgorithm.computeDecomposition(graph, maxBagSize, maxIterationCount);

        if (graphDecomposition.first != nullptr)
        {
            htd::IMutableGraphDecomposition & mutableGraphDecomposition = managementInstance_->graphDecompositionFactory().accessMutableGraphDecomposition(*(graphDecomposition.first));

            if (!managementInstance_->isTerminated())
            {
                if (mutableGraphDecomposition.edgeCount() + 1 != mutableGraphDecomposition.vertexCount() || mutableGraphDecomposition.isolatedVertexCount() > 0)
                {
                    htd::IConnectedComponentAlgorithm * connectedComponentAlgorithm = managementInstance_->connectedComponentAlgorithmFactory().getConnectedComponentAlgorithm(managementInstance_);

                    HTD_ASSERT(connectedComponentAlgorithm != nullptr)

                    std::vector<std::vector<htd::vertex_t>> components;

                    connectedComponentAlgorithm->determineComponents(*(graphDecomposition.first), components);

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

                htd::BreadthFirstGraphTraversal graphTraversal(managementInstance_);

                /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
                // coverity[dont_call]
                graphTraversal.traverse(*(graphDecomposition.first), graphDecomposition.first->vertexAtPosition(std::rand() % graphDecomposition.first->vertexCount()), [&](htd::vertex_t vertex, htd::vertex_t predecessor, std::size_t distanceFromStartingVertex)
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

                    vertexMapping.emplace(vertex, node);
                });
            }
            else
            {
                delete ret;

                ret = nullptr;
            }

            delete graphDecomposition.first;
        }
        else
        {
            delete ret;

            ret = nullptr;
        }

        iterations = graphDecomposition.second;
    }
    else
    {
        ret->insertRoot();
    }

    return std::make_pair(ret, iterations);
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP */
