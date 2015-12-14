/*
 * File:   HypertreeDecompositionAlgorithmFactory.cpp
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

#ifndef HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP
#define HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/HypertreeDecompositionAlgorithmFactory.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>
#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>

#include <memory>
#include <stdexcept>

htd::HypertreeDecompositionAlgorithmFactory::HypertreeDecompositionAlgorithmFactory(void)
{
    htd::ITreeDecompositionAlgorithm * treeDecompositionAlgorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();
    htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm();

    constructionTemplate_ = new htd::HypertreeDecompositionAlgorithm(*(std::shared_ptr<htd::ITreeDecompositionAlgorithm>(treeDecompositionAlgorithm)), *(std::shared_ptr<htd::ISetCoverAlgorithm>(setCoverAlgorithm)));
}

htd::HypertreeDecompositionAlgorithmFactory::~HypertreeDecompositionAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::HypertreeDecompositionAlgorithmFactory & htd::HypertreeDecompositionAlgorithmFactory::instance(void)
{
    static htd::HypertreeDecompositionAlgorithmFactory instance_;

    return instance_;
}

htd::IHypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithmFactory::getHypertreeDecompositionAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::HypertreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::IHypertreeDecompositionAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::HypertreeDecompositionAlgorithmFactory::setConstructionTemplate(htd::IHypertreeDecompositionAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HYPERTREEDECOMPOSITIONALGORITHMFACTORY_CPP */
