/*
 * File:   PathDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HTD_PATHDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HTD_PATHDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/PathDecompositionAlgorithmFactory.hpp>
#include <htd/PostProcessingPathDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::PathDecompositionAlgorithmFactory::PathDecompositionAlgorithmFactory(void) : constructionTemplate_(new htd::PostProcessingPathDecompositionAlgorithm()), labelingFunctions_(), postProcessingOperations_()
{

}

htd::PathDecompositionAlgorithmFactory::~PathDecompositionAlgorithmFactory()
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

    for (htd::IPathDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    postProcessingOperations_.clear();
}

htd::PathDecompositionAlgorithmFactory & htd::PathDecompositionAlgorithmFactory::instance(void)
{
    static htd::PathDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::IPathDecompositionAlgorithm * htd::PathDecompositionAlgorithmFactory::getPathDecompositionAlgorithm(void) const
{
    htd::IPathDecompositionAlgorithm * ret = constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        ret->addManipulationOperation(labelingFunction->clone());
    }

    for (htd::IPathDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        ret->addManipulationOperation(postProcessingOperation->clone());
    }

    return ret;
}

htd::IPathDecompositionAlgorithm * htd::PathDecompositionAlgorithmFactory::getPathDecompositionAlgorithm(const std::shared_ptr<htd::LibraryInstance> & instance) const
{
    htd::IPathDecompositionAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(instance);

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        htd::ILabelingFunction * clone = labelingFunction->clone();

        clone->setManagementInstance(instance);

        ret->addManipulationOperation(clone);
    }

    for (htd::IPathDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        htd::IPathDecompositionManipulationOperation * clone = postProcessingOperation->clone();

        clone->setManagementInstance(instance);

        ret->addManipulationOperation(clone);
    }

    return ret;
}

void htd::PathDecompositionAlgorithmFactory::setConstructionTemplate(htd::IPathDecompositionAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::PathDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::PathDecompositionAlgorithmFactory::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
{
    htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(manipulationOperation);

    if (labelingFunction != nullptr)
    {
        labelingFunctions_.push_back(labelingFunction);
    }

    htd::IPathDecompositionManipulationOperation * newManipulationOperation = dynamic_cast<htd::IPathDecompositionManipulationOperation *>(manipulationOperation);

    if (newManipulationOperation != nullptr)
    {
        postProcessingOperations_.push_back(newManipulationOperation);
    }
}

void htd::PathDecompositionAlgorithmFactory::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    for (htd::IDecompositionManipulationOperation * operation : manipulationOperations)
    {
        htd::ILabelingFunction * labelingFunction = dynamic_cast<htd::ILabelingFunction *>(operation);

        if (labelingFunction != nullptr)
        {
            labelingFunctions_.push_back(labelingFunction);
        }

        htd::IPathDecompositionManipulationOperation * manipulationOperation = dynamic_cast<htd::IPathDecompositionManipulationOperation *>(operation);

        if (manipulationOperation != nullptr)
        {
            postProcessingOperations_.push_back(manipulationOperation);
        }
    }
}

#endif /* HTD_HTD_PATHDECOMPOSITIONALGORITHMFACTORY_CPP */
