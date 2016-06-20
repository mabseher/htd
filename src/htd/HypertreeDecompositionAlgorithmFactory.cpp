/*
 * File:   HypertreeDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecompositionAlgorithmFactory.hpp>
#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>

#include <memory>
#include <stdexcept>

htd::HypertreeDecompositionAlgorithmFactory::HypertreeDecompositionAlgorithmFactory(void) : constructionTemplate_(new htd::HypertreeDecompositionAlgorithm()), labelingFunctions_(), postProcessingOperations_()
{

}

htd::HypertreeDecompositionAlgorithmFactory::~HypertreeDecompositionAlgorithmFactory()
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

htd::HypertreeDecompositionAlgorithmFactory & htd::HypertreeDecompositionAlgorithmFactory::instance(void)
{
    static htd::HypertreeDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::IHypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithmFactory::getHypertreeDecompositionAlgorithm(void)
{
    htd::IHypertreeDecompositionAlgorithm * ret = constructionTemplate_->clone();

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

void htd::HypertreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::IHypertreeDecompositionAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::HypertreeDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    labelingFunctions_.clear();

    postProcessingOperations_.clear();

    addManipulationOperations(manipulationOperations);
}

void htd::HypertreeDecompositionAlgorithmFactory::addManipulationOperation(htd::IDecompositionManipulationOperation * manipulationOperation)
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

void htd::HypertreeDecompositionAlgorithmFactory::addManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
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

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP */
