/*
 * File:   GraphDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphDecompositionAlgorithmFactory.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::GraphDecompositionAlgorithmFactory::GraphDecompositionAlgorithmFactory(const htd::LibraryInstance * const manager) : constructionTemplate_(new htd::BucketEliminationGraphDecompositionAlgorithm(manager)), labelingFunctions_(), postProcessingOperations_()
{

}

htd::GraphDecompositionAlgorithmFactory::GraphDecompositionAlgorithmFactory(const htd::GraphDecompositionAlgorithmFactory & original)
{
    constructionTemplate_ = original.constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : original.labelingFunctions_)
    {
    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        labelingFunctions_.emplace_back(labelingFunction->clone());
    #else
        labelingFunctions_.emplace_back(labelingFunction->cloneLabelingFunction());
    #endif
    }

    for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : original.postProcessingOperations_)
    {
    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        postProcessingOperations_.emplace_back(postProcessingOperation->clone());
    #else
        postProcessingOperations_.emplace_back(postProcessingOperation->cloneGraphDecompositionManipulationOperation());
    #endif
    }
}

htd::GraphDecompositionAlgorithmFactory & htd::GraphDecompositionAlgorithmFactory::operator=(const htd::GraphDecompositionAlgorithmFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

        constructionTemplate_ = original.constructionTemplate_->clone();

        for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
        {
            delete labelingFunction;
        }

        labelingFunctions_.clear();

        for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
        {
            delete postProcessingOperation;
        }

        postProcessingOperations_.clear();

        for (htd::ILabelingFunction * labelingFunction : original.labelingFunctions_)
        {
        #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            labelingFunctions_.emplace_back(labelingFunction->clone());
        #else
            labelingFunctions_.emplace_back(labelingFunction->cloneLabelingFunction());
        #endif
        }

        for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : original.postProcessingOperations_)
        {
        #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            postProcessingOperations_.emplace_back(postProcessingOperation->clone());
        #else
            postProcessingOperations_.emplace_back(postProcessingOperation->cloneGraphDecompositionManipulationOperation());
        #endif
        }
    }

    return *this;
}

htd::GraphDecompositionAlgorithmFactory::~GraphDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        delete labelingFunction;
    }

    labelingFunctions_.clear();

    for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    postProcessingOperations_.clear();
}

htd::IGraphDecompositionAlgorithm * htd::GraphDecompositionAlgorithmFactory::getGraphDecompositionAlgorithm(void) const
{
    htd::IGraphDecompositionAlgorithm * ret = constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(labelingFunction->clone());
#else
        ret->addManipulationOperation(labelingFunction->cloneLabelingFunction());
#endif
    }

    for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        ret->addManipulationOperation(postProcessingOperation->clone());
#else
        ret->addManipulationOperation(postProcessingOperation->cloneGraphDecompositionManipulationOperation());
#endif
    }

    return ret;
}

htd::IGraphDecompositionAlgorithm * htd::GraphDecompositionAlgorithmFactory::getGraphDecompositionAlgorithm(const htd::LibraryInstance * const manager) const
{
    htd::IGraphDecompositionAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(manager);

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::ILabelingFunction * clone = labelingFunction->clone();
#else
        htd::ILabelingFunction * clone = labelingFunction->cloneLabelingFunction();
#endif

        clone->setManagementInstance(manager);

        ret->addManipulationOperation(clone);
    }

    for (htd::IGraphDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        htd::IGraphDecompositionManipulationOperation * clone = postProcessingOperation->clone();
#else
        htd::IGraphDecompositionManipulationOperation * clone = postProcessingOperation->cloneGraphDecompositionManipulationOperation();
#endif

        clone->setManagementInstance(manager);

        ret->addManipulationOperation(clone);
    }

    return ret;
}

void htd::GraphDecompositionAlgorithmFactory::setConstructionTemplate(htd::IGraphDecompositionAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::GraphDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::GraphDecompositionAlgorithmFactory::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::IGraphDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::GraphDecompositionAlgorithmFactory::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::IGraphDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IGraphDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_CPP */
