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
#include <htd/PathDecompositionAlgorithmFactory.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>
#include <htd/PostProcessingPathDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::PathDecompositionAlgorithmFactory::PathDecompositionAlgorithmFactory(void)
{
    constructionTemplate_ = new htd::PostProcessingPathDecompositionAlgorithm();
}

htd::PathDecompositionAlgorithmFactory::~PathDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::PathDecompositionAlgorithmFactory & htd::PathDecompositionAlgorithmFactory::instance(void)
{
    static htd::PathDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::IPathDecompositionAlgorithm * htd::PathDecompositionAlgorithmFactory::getPathDecompositionAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::PathDecompositionAlgorithmFactory::setConstructionTemplate(htd::IPathDecompositionAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::PathDecompositionAlgorithmFactory::setConstructionTemplate(htd::IPathDecompositionAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::PathDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    constructionTemplate_->setManipulationOperations(manipulationOperations);
}

#endif /* HTD_HTD_PATHDECOMPOSITIONALGORITHMFACTORY_CPP */
