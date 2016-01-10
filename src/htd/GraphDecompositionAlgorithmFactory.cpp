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
#include <htd/GraphDecompositionAlgorithmFactory.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::GraphDecompositionAlgorithmFactory::GraphDecompositionAlgorithmFactory(void)
{
    constructionTemplate_ = new htd::BucketEliminationGraphDecompositionAlgorithm();
}

htd::GraphDecompositionAlgorithmFactory::~GraphDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::GraphDecompositionAlgorithmFactory & htd::GraphDecompositionAlgorithmFactory::instance(void)
{
    static htd::GraphDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::IGraphDecompositionAlgorithm * htd::GraphDecompositionAlgorithmFactory::getGraphDecompositionAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::GraphDecompositionAlgorithmFactory::setConstructionTemplate(htd::IGraphDecompositionAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::GraphDecompositionAlgorithmFactory::setConstructionTemplate(htd::IGraphDecompositionAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

void htd::GraphDecompositionAlgorithmFactory::setManipulationOperations(const std::vector<htd::IDecompositionManipulationOperation *> & manipulationOperations)
{
    constructionTemplate_->setManipulationOperations(manipulationOperations);
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONALGORITHMFACTORY_CPP */
