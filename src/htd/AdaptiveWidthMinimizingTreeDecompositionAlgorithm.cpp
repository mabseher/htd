/* 
 * File:   AdaptiveWidthMinimizingTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_ADAPTIVEWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP
#define HTD_HTD_ADAPTIVEWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/AdaptiveWidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>

#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <cstdarg>

/**
 *  Private implementation details of class htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm.
 */
struct htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager  The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager)
        : managementInstance_(manager), algorithms_(), filters_(), decisionRounds_(1), iterationCount_(1), nonImprovementLimit_(-1), computeInducedEdges_(true)
    {

    }

    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), algorithms_(), filters_(original.filters_), decisionRounds_(original.decisionRounds_), iterationCount_(original.iterationCount_), nonImprovementLimit_(original.nonImprovementLimit_), computeInducedEdges_(original.computeInducedEdges_)
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
     *  The filters for the decomposition algorithms together with the indices of the algorithms on which they apply.
     */
    std::vector<std::pair<std::function<bool(const htd::IMultiHypergraph &, const htd::IPreprocessedGraph &)>, htd::index_t>> filters_;

    /**
     *  The number of decision rounds which shall be performed.
     */
    std::size_t decisionRounds_;

    /**
     *  The number of iterations of the most promising algorithm which shall be performed.
     */
    std::size_t iterationCount_;

    /**
     *  The maximum number of iterations without improvement after which the most promising algorithm shall terminate.
     */
    std::size_t nonImprovementLimit_;

    /**
     *  A boolean flag indicating whether the hyperedges induced by a respective bag shall be computed.
     */
    bool computeInducedEdges_;

    /**
     *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
     *
     *  @param[in] algorithm                The algorithm which shall be used for computing the decomposition.
     *  @param[in] graph                    The input graph to decompose.
     *  @param[in] preprocessedGraph        The input graph in preprocessed format.
     *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
     *  @param[in] progressCallback         A callback function which is invoked for each new decomposition.
     *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
     *
     *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
     *
     *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
     *
     *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
     *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
     *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
     *
     *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
     */
    htd::ITreeDecomposition * computeImprovedDecomposition(const htd::ITreeDecompositionAlgorithm & algorithm,
                                                           const htd::IMultiHypergraph & graph,
                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const;

    /**
     *  Compute a decomposition of the given graph and apply the given manipulation operations to it.
     *
     *  @param[in] algorithm                The algorithm which shall be used for computing the decomposition.
     *  @param[in] graph                    The input graph to decompose.
     *  @param[in] preprocessedGraph        The input graph in preprocessed format.
     *  @param[in] manipulationOperations   The manipulation operations which shall be applied.
     *  @param[in] progressCallback         A callback function which is invoked for each new decomposition.
     *  @param[in] maxBagSize               The upper bound for the maximum bag size of the computed decomposition.
     *
     *  @note The maximum bag size of the computed decomposition must be less than or equal to the provided upper bound.
     *
     *  @note The manipulation operations provided to this function are applied right after the manipulation operations defined globally for the algorithm.
     *
     *  @note When calling this method the control over the memory regions of the manipulation operations is transferred to the
     *  decomposition algorithm. Deleting a manipulation operation provided to this method outside the decomposition algorithm
     *  or assigning the same manipulation operation multiple times will lead to undefined behavior.
     *
     *  @return A new ITreeDecomposition object representing the decomposition of the given graph.
     */
    htd::ITreeDecomposition * computeImprovedDecomposition(const htd::BucketEliminationTreeDecompositionAlgorithm & algorithm,
                                                           const htd::IMultiHypergraph & graph,
                                                           const htd::IPreprocessedGraph & preprocessedGraph,
                                                           const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                           const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const;
};

htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::AdaptiveWidthMinimizingTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::AdaptiveWidthMinimizingTreeDecompositionAlgorithm(const htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::~AdaptiveWidthMinimizingTreeDecompositionAlgorithm()
{

}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::addDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    algorithm->setComputeInducedEdgesEnabled(implementation_->computeInducedEdges_);

    implementation_->algorithms_.push_back(algorithm);
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::addDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm, const std::function<bool(const htd::IMultiHypergraph &, const htd::IPreprocessedGraph &)> & filter)
{
    HTD_ASSERT(algorithm != nullptr)

    algorithm->setComputeInducedEdgesEnabled(implementation_->computeInducedEdges_);

    implementation_->filters_.emplace_back(filter, implementation_->algorithms_.size());

    implementation_->algorithms_.push_back(algorithm);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
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

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, preprocessedGraph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, manipulationOperations, progressCallback, (std::size_t)-1);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
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

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations, std::size_t maxBagSize) const
{
    return computeImprovedDecomposition(graph, preprocessedGraph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){}, maxBagSize);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    std::size_t bestMaxBagSize = maxBagSize;

    if (bestMaxBagSize != (std::size_t)-1)
    {
        ++bestMaxBagSize;
    }

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    htd::ITreeDecomposition * ret = nullptr;

    std::vector<std::size_t> minimalWidths(implementation_->algorithms_.size(), (std::size_t)-1);
    std::vector<std::size_t> accumulatedWidths(implementation_->algorithms_.size());

    std::unordered_set<htd::index_t> disqualifiedAlgorithms;

    for (const std::pair<std::function<bool(const htd::IMultiHypergraph &, const htd::IPreprocessedGraph &)>, htd::index_t> & filter : implementation_->filters_)
    {
        if (!filter.first(graph, preprocessedGraph))
        {
            disqualifiedAlgorithms.insert(filter.second);
        }
    }

    for (htd::index_t round = 0; round < implementation_->decisionRounds_ && !managementInstance.isTerminated(); ++round)
    {
        htd::index_t algorithmIndex = 0;

        for (auto it = implementation_->algorithms_.begin(); it != implementation_->algorithms_.end() && !managementInstance.isTerminated(); ++it)
        {
            if (disqualifiedAlgorithms.count(algorithmIndex) == 0)
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

                htd::ITreeDecomposition * currentDecomposition = (*it)->computeDecomposition(graph, preprocessedGraph, clonedManipulationOperations);

                if (currentDecomposition != nullptr)
                {
                    if (!managementInstance.isTerminated() || (*it)->isSafelyInterruptible())
                    {
                        std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                        accumulatedWidths[algorithmIndex] += currentMaxBagSize;

                        if (currentMaxBagSize < minimalWidths[algorithmIndex])
                        {
                            minimalWidths[algorithmIndex] = currentMaxBagSize;
                        }

                        if (currentMaxBagSize < bestMaxBagSize)
                        {
                            progressCallback(graph, *currentDecomposition, htd::FitnessEvaluation(1, -(static_cast<double>(currentMaxBagSize))));

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

            ++algorithmIndex;
        }

        std::size_t optimum = (std::size_t)-1;

        for (std::size_t achievedWidth : minimalWidths)
        {
            if (achievedWidth < optimum)
            {
                optimum = achievedWidth;
            }
        }

        if (optimum == 0)
        {
            optimum = 1;
        }

        for (htd::index_t index = 0; index < accumulatedWidths.size(); ++index)
        {
            if (disqualifiedAlgorithms.count(index) == 0)
            {
                std::size_t achievedWidth = minimalWidths[index];

                if (static_cast<double>(achievedWidth) / static_cast<double>(optimum) > 1.5)
                {
                    disqualifiedAlgorithms.insert(index);
                }
            }
        }
    }

    std::size_t optimum = (std::size_t)-1;

    std::vector<htd::index_t> pool;

    for (htd::index_t index = 0; index < accumulatedWidths.size(); ++index)
    {
        if (disqualifiedAlgorithms.count(index) == 0)
        {
            std::size_t achievedTotalWidth = accumulatedWidths[index];

            if (achievedTotalWidth <= optimum)
            {
                if (achievedTotalWidth < optimum)
                {
                    optimum = achievedTotalWidth;

                    pool.clear();
                }

                pool.push_back(index);
            }
        }
    }

    htd::ITreeDecompositionAlgorithm * selectedAlgorithm = implementation_->algorithms_[htd::selectRandomElement<htd::index_t>(pool)];

    htd::BucketEliminationTreeDecompositionAlgorithm * bucketEliminationTreeDecompositionAlgorithm = dynamic_cast<htd::BucketEliminationTreeDecompositionAlgorithm *>(selectedAlgorithm);

    if (bucketEliminationTreeDecompositionAlgorithm != nullptr)
    {
        htd::ITreeDecomposition * currentDecomposition = implementation_->computeImprovedDecomposition(*bucketEliminationTreeDecompositionAlgorithm, graph, preprocessedGraph, manipulationOperations, progressCallback, bestMaxBagSize - 1);

        if (currentDecomposition != nullptr)
        {
            std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

            delete ret;

            ret = currentDecomposition;

            bestMaxBagSize = currentMaxBagSize;
        }
    }
    else
    {
        htd::ITreeDecomposition * currentDecomposition = implementation_->computeImprovedDecomposition(*selectedAlgorithm, graph, preprocessedGraph, manipulationOperations, progressCallback, bestMaxBagSize - 1);

        if (currentDecomposition != nullptr)
        {
            std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

            delete ret;

            ret = currentDecomposition;

            bestMaxBagSize = currentMaxBagSize;
        }
    }

    return ret;
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
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

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const
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

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, std::size_t maxBagSize, int manipulationOperationCount, ...) const
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

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::computeImprovedDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, std::size_t maxBagSize, int manipulationOperationCount, ...) const
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

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::ITreeDecompositionAlgorithm * algorithm : implementation_->algorithms_)
    {
        algorithm->setManipulationOperations(std::vector<htd::IDecompositionManipulationOperation *>());
    }

    addManipulationOperations(manipulationOperations);
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
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

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return true;
}

bool htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::isComputeInducedEdgesEnabled(void) const
{
    return implementation_->computeInducedEdges_;
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled)
{
    implementation_->computeInducedEdges_ = computeInducedEdgesEnabled;

    for (htd::ITreeDecompositionAlgorithm * algorithm : implementation_->algorithms_)
    {
        algorithm->setComputeInducedEdgesEnabled(computeInducedEdgesEnabled);
    }
}

const htd::LibraryInstance * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

std::size_t htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::iterationCount(void) const
{
    return implementation_->iterationCount_;
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setIterationCount(std::size_t iterationCount)
{
    implementation_->iterationCount_ = iterationCount;
}

std::size_t htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::nonImprovementLimit(void) const
{
    return implementation_->nonImprovementLimit_;
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setNonImprovementLimit(std::size_t nonImprovementLimit)
{
    implementation_->nonImprovementLimit_ = nonImprovementLimit;
}

std::size_t htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::decisionRounds(void) const
{
    return implementation_->decisionRounds_;
}

void htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::setDecisionRounds(std::size_t rounds)
{
    implementation_->decisionRounds_ = rounds;
}

htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::clone(void) const
{
    return new htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm(*this);
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::Implementation::computeImprovedDecomposition(const htd::ITreeDecompositionAlgorithm & algorithm,
                                                                                                                               const htd::IMultiHypergraph & graph,
                                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    std::size_t bestMaxBagSize = maxBagSize + 1;

    htd::ITreeDecomposition * ret = nullptr;

    std::size_t remainingIterations = iterationCount_;

    std::size_t nonImprovementCount = 0;

    while (remainingIterations > 0 && !managementInstance_->isTerminated())
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

        htd::ITreeDecomposition * currentDecomposition = algorithm.computeDecomposition(graph, preprocessedGraph, clonedManipulationOperations);

        if (currentDecomposition != nullptr)
        {
            if (!managementInstance_->isTerminated() || algorithm.isSafelyInterruptible())
            {
                std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                if (!managementInstance_->isTerminated() || algorithm.isSafelyInterruptible())
                {
                    if (currentMaxBagSize < bestMaxBagSize)
                    {
                        progressCallback(graph, *currentDecomposition, htd::FitnessEvaluation(1, -(static_cast<double>(currentMaxBagSize))));

                        if (ret != nullptr)
                        {
                            delete ret;
                        }

                        ret = currentDecomposition;

                        bestMaxBagSize = currentMaxBagSize;

                        nonImprovementCount = 0;
                    }
                    else
                    {
                        delete currentDecomposition;

                        ++nonImprovementCount;
                    }
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
        else
        {
            ++nonImprovementCount;
        }

        if (nonImprovementCount > nonImprovementLimit_)
        {
            remainingIterations = 0;
        }
        else
        {
            --remainingIterations;
        }
    }

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        delete operation;
    }

    return ret;
}

htd::ITreeDecomposition * htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm::Implementation::computeImprovedDecomposition(const htd::BucketEliminationTreeDecompositionAlgorithm & algorithm,
                                                                                                                               const htd::IMultiHypergraph & graph,
                                                                                                                               const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                                               const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                                               const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback, std::size_t maxBagSize) const
{
    std::size_t bestMaxBagSize = maxBagSize + 1;

    htd::ITreeDecomposition * ret = nullptr;

    std::size_t remainingIterations = iterationCount_;

    while (remainingIterations > 0 && !managementInstance_->isTerminated())
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

        std::pair<htd::ITreeDecomposition *, std::size_t> decompositionResult = algorithm.computeDecomposition(graph, preprocessedGraph, clonedManipulationOperations, bestMaxBagSize - 1, std::min(remainingIterations, nonImprovementLimit_));

        htd::ITreeDecomposition * currentDecomposition = decompositionResult.first;

        if (decompositionResult.second < nonImprovementLimit_)
        {
            remainingIterations -= decompositionResult.second;
        }
        else
        {
            remainingIterations = 0;
        }

        if (currentDecomposition != nullptr)
        {
            if (!managementInstance_->isTerminated() || algorithm.isSafelyInterruptible())
            {
                std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                if (!managementInstance_->isTerminated() || algorithm.isSafelyInterruptible())
                {
                    if (currentMaxBagSize < bestMaxBagSize)
                    {
                        progressCallback(graph, *currentDecomposition, htd::FitnessEvaluation(1, -(static_cast<double>(currentMaxBagSize))));

                        if (ret != nullptr)
                        {
                            delete ret;
                        }

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
            else
            {
                delete currentDecomposition;
            }
        }
    }

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        delete operation;
    }

    return ret;
}

#endif /* HTD_HTD_ADAPTIVEWIDTHMINIMIZINGTREEDECOMPOSITIONALGORITHM_CPP */
