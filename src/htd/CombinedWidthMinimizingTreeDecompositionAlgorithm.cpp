/* 
 * File:   CombinedWidthMinimizingTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP
#define HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/CombinedWidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/IWidthMinimizingTreeDecompositionAlgorithm.hpp>

#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <cstdarg>

/**
 *  Private implementation details of class htd::CombinedWidthMinimizingTreeDecompositionAlgorithm.
 */
struct htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager  The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager)
        : managementInstance_(manager), algorithms_(), computeInducedEdges_(true)
    {

    }

    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), algorithms_(), computeInducedEdges_(original.computeInducedEdges_)
    {
        for (const htd::ITreeDecompositionAlgorithm * algorithm : original.algorithms_)
        {
            algorithms_.push_back(algorithm->clone());
        }
    }

    virtual ~Implementation()
    {
        for (htd::ITreeDecompositionAlgorithm * algorithm : algorithms_)
        {
            delete algorithm;
        }
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The decomposition algorithms which will be called.
     */
    std::vector<htd::ITreeDecompositionAlgorithm *> algorithms_;

    /**
     *  A boolean flag indicating whether the hyperedges induced by a respective bag shall be computed.
     */
    bool computeInducedEdges_;
};

htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::CombinedWidthMinimizingTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::CombinedWidthMinimizingTreeDecompositionAlgorithm(const htd::CombinedWidthMinimizingTreeDecompositionAlgorithm & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::~CombinedWidthMinimizingTreeDecompositionAlgorithm()
{

}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::addDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    algorithm->setComputeInducedEdgesEnabled(implementation_->computeInducedEdges_);

    implementation_->algorithms_.push_back(algorithm);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::ITreeDecomposition * ret = computeDecomposition(graph, *preprocessedGraph, manipulationOperations, progressCallback);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, preprocessedGraph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, manipulationOperations, progressCallback, (std::size_t)-1);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    htd::IGraphPreprocessor * preprocessor = implementation_->managementInstance_->graphPreprocessorFactory().createInstance();

    htd::IPreprocessedGraph * preprocessedGraph = preprocessor->prepare(graph);

    htd::ITreeDecomposition * ret = computeImprovedDecomposition(graph, *preprocessedGraph, manipulationOperations, progressCallback, maxBagSize);

    delete preprocessedGraph;
    delete preprocessor;

    return ret;
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    std::size_t bestMaxBagSize = maxBagSize;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    htd::ITreeDecomposition * ret = nullptr;

    for (auto it = implementation_->algorithms_.begin(); it != implementation_->algorithms_.end() && !managementInstance.isTerminated(); ++it)
    {
        std::vector<htd::IDecompositionManipulationOperation *> clonedManipulationOperations;

        for (const htd::IDecompositionManipulationOperation * operation : manipulationOperations)
        {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            clonedManipulationOperations.push_back(operation->clone());
#else
            clonedManipulationOperations.push_back(operation->cloneDecompositionManipulationOperation());
#endif
        }

        htd::IWidthMinimizingTreeDecompositionAlgorithm * widthMinimizingTreeDecompositionAlgorithm = dynamic_cast<htd::IWidthMinimizingTreeDecompositionAlgorithm *>(*it);

        if (widthMinimizingTreeDecompositionAlgorithm != nullptr)
        {
            htd::ITreeDecomposition * currentDecomposition =
                widthMinimizingTreeDecompositionAlgorithm->computeImprovedDecomposition(graph, preprocessedGraph, clonedManipulationOperations, [&](const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, const htd::FitnessEvaluation & fitness)
                {
                    progressCallback(graph, decomposition, fitness);
                }, bestMaxBagSize - 1);

            if (currentDecomposition != nullptr)
            {
                std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                if (currentMaxBagSize < bestMaxBagSize)
                {
                    delete ret;

                    ret = currentDecomposition;

                    bestMaxBagSize = currentMaxBagSize;
                }
                else
                {
                    delete currentDecomposition;
                }
            }
        }
        else
        {
            htd::ITreeDecomposition * currentDecomposition = (*it)->computeDecomposition(graph, preprocessedGraph, clonedManipulationOperations);

            if (currentDecomposition != nullptr)
            {
                if (!managementInstance.isTerminated() || (*it)->isSafelyInterruptible())
                {
                    std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                    progressCallback(graph, *currentDecomposition, htd::FitnessEvaluation(1, -(static_cast<double>(currentMaxBagSize))));

                    if (currentMaxBagSize < bestMaxBagSize)
                    {
                        delete ret;

                        ret = currentDecomposition;

                        bestMaxBagSize = currentMaxBagSize;
                    }
                    else
                    {
                        delete currentDecomposition;
                    }
                }
                else
                {
                    delete currentDecomposition;
                }
            }
        }
    }

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        delete operation;
    }

    return ret;
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
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

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeDecomposition(graph, preprocessedGraph, manipulationOperations);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeImprovedDecomposition(graph, manipulationOperations, maxBagSize);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, int manipulationOperationCount, ...) const
{
    va_list arguments;

    va_start(arguments, manipulationOperationCount);

    std::vector<htd::IDecompositionManipulationOperation *> manipulationOperations;

    for (int manipulationOperationIndex = 0; manipulationOperationIndex < manipulationOperationCount; manipulationOperationIndex++)
    {
        manipulationOperations.push_back(va_arg(arguments, htd::IDecompositionManipulationOperation *));
    }

    va_end(arguments);

    return computeImprovedDecomposition(graph, preprocessedGraph, manipulationOperations, maxBagSize);
}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::ITreeDecompositionAlgorithm * algorithm : implementation_->algorithms_)
    {
        algorithm->setManipulationOperations(std::vector<htd::IDecompositionManipulationOperation *>());
    }

    addManipulationOperations(manipulationOperations);
}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    for (htd::ITreeDecompositionAlgorithm * algorithm : implementation_->algorithms_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        algorithm->addManipulationOperation(manipulationOperation->clone());
#else
        algorithm->addManipulationOperation(manipulationOperation->cloneDecompositionManipulationOperation());
#endif
    }

    delete manipulationOperation;
}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return true;
}

bool htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::isComputeInducedEdgesEnabled(void) const
{
    return implementation_->computeInducedEdges_;
}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled)
{
    implementation_->computeInducedEdges_ = computeInducedEdgesEnabled;

    for (htd::ITreeDecompositionAlgorithm * algorithm : implementation_->algorithms_)
    {
        algorithm->setComputeInducedEdgesEnabled(computeInducedEdgesEnabled);
    }
}

const htd::LibraryInstance * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::CombinedWidthMinimizingTreeDecompositionAlgorithm * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::clone(void) const
{
    return new htd::CombinedWidthMinimizingTreeDecompositionAlgorithm(*this);
}

#endif /* HTD_HTD_COMBINEDWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP */
