/* 
 * File:   IterativeImprovementTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/IterativeImprovementTreeDecompositionAlgorithm.hpp>

#include <cstdarg>

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction)
    : iterationCount_(10), nonImprovementLimit_(-1), algorithm_(algorithm.clone()), fitnessFunction_(fitnessFunction.clone()), labelingFunctions_(), postProcessingOperations_()
{

}

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction)
    : iterationCount_(10), nonImprovementLimit_(-1), algorithm_(algorithm), fitnessFunction_(fitnessFunction.clone()), labelingFunctions_(), postProcessingOperations_()
{
    HTD_ASSERT(algorithm != nullptr)
}

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
    : iterationCount_(10), nonImprovementLimit_(-1), algorithm_(algorithm.clone()), fitnessFunction_(fitnessFunction.clone()), labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::IterativeImprovementTreeDecompositionAlgorithm::IterativeImprovementTreeDecompositionAlgorithm(htd::ITreeDecompositionAlgorithm * algorithm, const htd::ITreeDecompositionFitnessFunction & fitnessFunction, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
    : iterationCount_(10), nonImprovementLimit_(-1), algorithm_(algorithm), fitnessFunction_(fitnessFunction.clone()), labelingFunctions_(), postProcessingOperations_()
{
    setManipulationOperations(manipulationOperations);
}

htd::IterativeImprovementTreeDecompositionAlgorithm::~IterativeImprovementTreeDecompositionAlgorithm()
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

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>());
}

htd::ITreeDecomposition * htd::IterativeImprovementTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph, const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
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

    for (htd::index_t iteration = 0; (iteration == 0 || iteration < iterationCount_) && !isTerminated(); ++iteration)
    {
        htd::IMutableTreeDecomposition * currentDecomposition = dynamic_cast<htd::IMutableTreeDecomposition *>(algorithm_->computeDecomposition(graph));

        if (currentDecomposition != nullptr)
        {
            for (const auto & labelingFunction : labelingFunctions_)
            {
                for (htd::vertex_t vertex : currentDecomposition->vertices())
                {
                    htd::ILabelCollection * labelCollection = currentDecomposition->labelings().exportVertexLabelCollection(vertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(currentDecomposition->bagContent(vertex), *labelCollection);

                    delete labelCollection;

                    currentDecomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
                }
            }

            for (const auto & labelingFunction : labelingFunctions)
            {
                for (htd::vertex_t vertex : currentDecomposition->vertices())
                {
                    htd::ILabelCollection * labelCollection = currentDecomposition->labelings().exportVertexLabelCollection(vertex);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(currentDecomposition->bagContent(vertex), *labelCollection);

                    delete labelCollection;

                    currentDecomposition->setVertexLabel(labelingFunction->name(), vertex, newLabel);
                }
            }

            for (const auto & operation : postProcessingOperations_)
            {
                operation->apply(*currentDecomposition);
            }

            for (const auto & operation : postProcessingOperations)
            {
                operation->apply(*currentDecomposition);
            }

            if (!isTerminated())
            {
                htd::FitnessEvaluation * currentEvaluation = fitnessFunction_->fitness(*currentDecomposition);

                if (!isTerminated())
                {
                    if (iteration == 0 || *currentEvaluation > *bestEvaluation)
                    {
                        if (iteration > 0)
                        {
                            delete ret;

                            delete bestEvaluation;
                        }

                        ret = currentDecomposition;

                        bestEvaluation = currentEvaluation;
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

                    delete currentEvaluation;
                }
            }
            else
            {
                delete currentDecomposition;
            }
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


void htd::IterativeImprovementTreeDecompositionAlgorithm::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

void htd::IterativeImprovementTreeDecompositionAlgorithm::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
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

void htd::IterativeImprovementTreeDecompositionAlgorithm::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

bool htd::IterativeImprovementTreeDecompositionAlgorithm::isSafelyInterruptible(void) const
{
    return true;
}

std::size_t htd::IterativeImprovementTreeDecompositionAlgorithm::iterationCount(void) const
{
    return iterationCount_;
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setIterationCount(std::size_t iterationCount)
{
    iterationCount_ = iterationCount;
}

std::size_t htd::IterativeImprovementTreeDecompositionAlgorithm::nonImprovementLimit(void) const
{
    return nonImprovementLimit_;
}

void htd::IterativeImprovementTreeDecompositionAlgorithm::setNonImprovementLimit(std::size_t nonImprovementLimit)
{
    nonImprovementLimit_ = nonImprovementLimit;
}

htd::IterativeImprovementTreeDecompositionAlgorithm * htd::IterativeImprovementTreeDecompositionAlgorithm::clone(void) const
{
    htd::IterativeImprovementTreeDecompositionAlgorithm * ret = new htd::IterativeImprovementTreeDecompositionAlgorithm(*algorithm_, *fitnessFunction_);

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

#endif /* HTD_HTD_ITERATIVEIMPROVEMENTTREEDECOMPOSITIONALGORITHM_CPP */
