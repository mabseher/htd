/*
 * File:   TreeDecompositionAlgorithmFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>

#include <memory>
#include <stdexcept>

htd::TreeDecompositionAlgorithmFactory::TreeDecompositionAlgorithmFactory(void)
{
    htd::IOrderingAlgorithm * orderingAlgorithm = htd::OrderingAlgorithmFactory::instance().getOrderingAlgorithm();

    constructionTemplate_ = new htd::BucketEliminationTreeDecompositionAlgorithm(*(std::shared_ptr<htd::IOrderingAlgorithm>(orderingAlgorithm)));
}

htd::TreeDecompositionAlgorithmFactory::~TreeDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::TreeDecompositionAlgorithmFactory & htd::TreeDecompositionAlgorithmFactory::instance(void)
{
    static htd::TreeDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::ITreeDecompositionAlgorithm * htd::TreeDecompositionAlgorithmFactory::getTreeDecompositionAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::TreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::ITreeDecompositionAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::TreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::ITreeDecompositionAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_TREEDECOMPOSITIONALGORITHMFACTORY_CPP */
