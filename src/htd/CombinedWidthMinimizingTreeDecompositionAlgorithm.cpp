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
#include <htd/WidthMinimizingTreeDecompositionAlgorithm.hpp>

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
        : managementInstance_(manager), algorithms_()
    {

    }

    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), algorithms_()
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

    implementation_->algorithms_.push_back(algorithm);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, std::size_t){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, std::size_t)> & progressCallback) const
{
    return computeDecomposition(graph, std::vector<htd::IDecompositionManipulationOperation *>(), progressCallback);
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations) const
{
    return computeDecomposition(graph, manipulationOperations, [](const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, std::size_t){});
}

htd::ITreeDecomposition * htd::CombinedWidthMinimizingTreeDecompositionAlgorithm::computeDecomposition(const htd::IMultiHypergraph & graph,
                                                                                                       const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations,
                                                                                                       const std::function<void(const htd::IMultiHypergraph &, const htd::ITreeDecomposition &, std::size_t)> & progressCallback) const
{
    std::size_t bestMaxBagSize = (std::size_t)-1;

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

        htd::WidthMinimizingTreeDecompositionAlgorithm * widthMinimizingTreeDecompositionAlgorithm = dynamic_cast<htd::WidthMinimizingTreeDecompositionAlgorithm *>(*it);

        if (widthMinimizingTreeDecompositionAlgorithm != nullptr)
        {
            htd::ITreeDecomposition * currentDecomposition =
                widthMinimizingTreeDecompositionAlgorithm->computeDecomposition(graph, clonedManipulationOperations, [&](const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, std::size_t maximumBagSize)
                {
                    progressCallback(graph, decomposition, maximumBagSize);
                });

            if (currentDecomposition != nullptr)
            {
                std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                progressCallback(graph, *currentDecomposition, currentMaxBagSize);

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
            htd::ITreeDecomposition * currentDecomposition = (*it)->computeDecomposition(graph, clonedManipulationOperations);

            if (currentDecomposition != nullptr)
            {
                if (!managementInstance.isTerminated() || (*it)->isSafelyInterruptible())
                {
                    std::size_t currentMaxBagSize = currentDecomposition->maximumBagSize();

                    progressCallback(graph, *currentDecomposition, currentMaxBagSize);

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
