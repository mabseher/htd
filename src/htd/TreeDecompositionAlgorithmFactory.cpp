/*
 * File:   TreeDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::TreeDecompositionAlgorithmFactory::TreeDecompositionAlgorithmFactory(void) : constructionTemplate_(new htd::BucketEliminationTreeDecompositionAlgorithm()), labelingFunctions_(), postProcessingOperations_()
{

}

htd::TreeDecompositionAlgorithmFactory::~TreeDecompositionAlgorithmFactory()
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

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        delete postProcessingOperation;
    }

    postProcessingOperations_.clear();
}

htd::TreeDecompositionAlgorithmFactory & htd::TreeDecompositionAlgorithmFactory::instance(void)
{
    static htd::TreeDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::ITreeDecompositionAlgorithm * htd::TreeDecompositionAlgorithmFactory::getTreeDecompositionAlgorithm(void) const
{
    htd::ITreeDecompositionAlgorithm * ret = constructionTemplate_->clone();

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        ret->addManipulationOperation(labelingFunction->clone());
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        ret->addManipulationOperation(postProcessingOperation->clone());
    }

    return ret;
}

htd::ITreeDecompositionAlgorithm * htd::TreeDecompositionAlgorithmFactory::getTreeDecompositionAlgorithm(const std::shared_ptr<htd::LibraryInstance> & instance) const
{
    htd::ITreeDecompositionAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(instance);

    for (htd::ILabelingFunction * labelingFunction : labelingFunctions_)
    {
        htd::ILabelingFunction * clone = labelingFunction->clone();

        clone->setManagementInstance(instance);

        ret->addManipulationOperation(clone);
    }

    for (htd::ITreeDecompositionManipulationOperation * postProcessingOperation : postProcessingOperations_)
    {
        htd::ITreeDecompositionManipulationOperation * clone = postProcessingOperation->clone();

        clone->setManagementInstance(instance);

        ret->addManipulationOperation(clone);
    }

    return ret;
}

void htd::TreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::ITreeDecompositionAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::TreeDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::TreeDecompositionAlgorithmFactory::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
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

void htd::TreeDecompositionAlgorithmFactory::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

#endif /* HTD_HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP */
