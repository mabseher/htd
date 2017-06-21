/* 
 * File:   IterativeImprovementTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP
#define HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/IterativeImprovementTreeDecompositionAlgorithm.hpp>

#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <cstdarg>

/**
 *  Private implementation details of class htd::IterativeImprovementTreeDecompositionAlgorithm.
 */
struct htd::IterativeImprovementTreeDecompositionAlgorithm::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager          The management instance to which the current object instance belongs.
     *  @param[in] algorithm        The decomposition algorithm which will be called repeatedly.
     *  @param[in] fitnessFunction  The fitness function which will be used to evaluate the constructed tree decompositions.
     */
    Implementation(const htd::LibraryInstance * const manager, htd::ITreeDecompositionAlgorithm * algorithm, htd::ITreeDecompositionFitnessFunction * fitnessFunction)
        : managementInstance_(manager), iterationCount_(1), nonImprovementLimit_(-1), algorithm_(algorithm), fitnessFunction_(fitnessFunction), labelingFunctions_(), postProcessingOperations_()
    {

    }

    virtual ~Implementation()
    {
        delete algorithm_;

        delete fitnessFunction_;

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
     *  The number of iterations which shall be performed.
     */
    std::size_t iterationCount_;

    /**
     *  The maximum number of iterations without improvement after which the algorithm shall terminate.
     */
    std::size_t nonImprovementLimit_;

    /**
     *  The decomposition algorithm which will be called repeatedly.
     */
    htd::ITreeDecompositionAlgorithm * algorithm_;

    /**
     *  The fitness function which will be used to evaluate the constructed tree decompositions.
     */
    htd::ITreeDecompositionFitnessFunction * fitnessFunction_;

    /**
     *  The labeling functions which are applied after a new decomposition was computed.
     */
    std::vector<htd::ILabelingFunction *> labelingFunctions_;

    /**
     *  The manipuation operations which are applied after a new decomposition was computed.
     */
    std::vector<htd::ITreeDecompositionManipulationOperation *> postProcessingOperations_;

    /**
     *  Compute a new mutable tree decompostion of the given graph.
     *
     *  @param[in] graph    The graph which shall be decomposed.
     *
     *  @return A mutable tree decompostion of the given graph.
     */
    htd::IMutableTreeDecomposition * computeMutableDecomposition(const htd::IMultiHypergraph & graph) const;
};

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, htd::ITreeDecompositionAlgorithm * algorithm, htd::ITreeDecompositionFitnessFunction * fitnessFunction) : implementation_(new Implementation(manager, algorithm, fitnessFunction))
{
    HTD_ASSERT(algorithm != nullptr)
}

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(const htd::LibraryInstance * const manager, htd::ITreeDecompositionAlgorithm * algorithm, htd::ITreeDecompositionFitnessFunction * fitnessFunction, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) : implementation_(new Implementation(manager, algorithm, fitnessFunction))
{
    HTD_ASSERT(algorithm != nullptr)

    setManipulationOperations(manipulationOperations);
}

htd::IterativeImprovementTreeDecompositionAlgorithm::~IterativeImprovementTreeDecompositionAlgorithm()
{

}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                    const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                    const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
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

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                    const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                    const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
{
    return computeDecomposition(graph, preprocessedGraph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                    const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                    const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, preprocessedGraph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &){});
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                    const htd::IPreprocessedGraph & preprocessedGraph,
                                                                                                    const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                    const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, const htd::FitnessEvaluation &)> & progressCallback) const
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

    htd::ITreeDecomposition * ret = nullptr;

    htd::FitnessEvaluation * bestEvaluation = nullptr;

    std::size_t nonImprovementCount = 0;

    const htd::LibraryInstance & managementInstance = *(implementation_->managementInstance_);

    for (htd::index_t iteration = 0; (iteration == 0 || implementation_->iterationCount_ == 0 || iteration < implementation_->iterationCount_) && nonImprovementCount <= implementation_->nonImprovementLimit_ && !managementInstance.isTerminated(); ++iteration)
    {
        htd::IMutableTreeDecomposition * currentDecomposition = dynamic_cast<htd::IMutableTreeDecomposition *>(implementation_->algorithm_->computeDecomposition(graph, preprocessedGraph));

        if (currentDecomposition != nullptr)
        {
            for (const htd::ITreeDecompositionManipulationOperation * operation : implementation_->postProcessingOperations_)
            {
                operation->apply(graph, *currentDecomposition);
            }

            for (htd::ITreeDecompositionManipulationOperation * operation : postProcessingOperations)
            {
                operation->apply(graph, *currentDecomposition);
            }

            for (const htd::ILabelingFunction * labelingFunction : implementation_->labelingFunctions_)
            {
                for (htd::vertex_t vertex : currentDecomposition->vertices())
                {
                    htd::ILabelCollection * labelCollection = currentDecomposition->labelings().exportVertexLabelCollection(vertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(currentDecomposition->bagContent(vertex), *labelCollection);

                    delete labelCollection;

                    currentDecomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
                }
            }

            for (htd::ILabelingFunction * labelingFunction : labelingFunctions)
            {
                for (htd::vertex_t vertex : currentDecomposition->vertices())
                {
                    htd::ILabelCollection * labelCollection = currentDecomposition->labelings().exportVertexLabelCollection(vertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(currentDecomposition->bagContent(vertex), *labelCollection);

                    delete labelCollection;

                    currentDecomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
                }
            }

            if (!managementInstance.isTerminated())
            {
                htd::FitnessEvaluation * currentEvaluation = implementation_->fitnessFunction_->fitness(graph, *currentDecomposition);

                if (!managementInstance.isTerminated())
                {
                    progressCallback(graph, *currentDecomposition, *currentEvaluation);

                    if (iteration == 0 || *currentEvaluation > *bestEvaluation)
                    {
                        if (iteration > 0)
                        {
                            delete ret;

                            delete bestEvaluation;
                        }

                        ret = currentDecomposition;

                        bestEvaluation = currentEvaluation;

                        nonImprovementCount = 0;
                    }
                    else
                    {
                        delete currentDecomposition;

                        delete currentEvaluation;

                        ++nonImprovementCount;
                    }
                }
                else
                {
                    delete currentDecomposition;

                    delete currentEvaluation;
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
    }

    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        delete operation;
    }

    if (bestEvaluation != nullptr)
    {
        delete bestEvaluation;
    }

    return ret;
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, int manipulationOperationCount, ...) const
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

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph, int manipulationOperationCount, ...) const
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

void htd::IterativeImprovementTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

void htd::IterativeImprovementTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        implementation_->labelingFunctions_.emplace_back(labelingFunction);
    }

    htd::ITreeDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::ITreeDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        implementation_->postProcessingOperations_.emplace_back(newManipulationOperation);
    }
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        addManipulationOperation(operation);
    }
}

bool htd::IterativeImprovementTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return true;
}

bool htd::IterativeImprovementTreeDecompositionAlgorithm::isComputeInducedEdgesEnabled(void) const
{
    return implementation_->algorithm_->isComputeInducedEdgesEnabled();
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setComputeInducedEdgesEnabled(bool computeInducedEdgesEnabled)
{
    implementation_->algorithm_->setComputeInducedEdgesEnabled(computeInducedEdgesEnabled);
}

std::size_t htd::IterativeImprovementTreeDecompositionAlgorithm::iterationCount(void) const
{
    return implementation_->iterationCount_;
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setIterationCount(std::size_t iterationCount)
{
    implementation_->iterationCount_ = iterationCount;
}

std::size_t htd::IterativeImprovementTreeDecompositionAlgorithm::nonImprovementLimit(void) const
{
    return implementation_->nonImprovementLimit_;
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setNonImprovementLimit(std::size_t nonImprovementLimit)
{
    implementation_->nonImprovementLimit_ = nonImprovementLimit;
}

const htd::LibraryInstance * htd::IterativeImprovementTreeDecompositionAlgorithm::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::IterativeImprovementTreeDecompositionAlgorithm * htd::IterativeImprovementTreeDecompositionAlgorithm::clone(void) const
{
    htd::IterativeImprovementTreeDecompositionAlgorithm * ret = new htd::IterativeImprovementTreeDecompositionAlgorithm(managementInstance(), implementation_->algorithm_->clone(), implementation_->fitnessFunction_->clone());

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

    ret->setIterationCount(implementation_->iterationCount_);
    ret->setNonImprovementLimit(implementation_->nonImprovementLimit_);

    return ret;
}

#endif /* HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP */
