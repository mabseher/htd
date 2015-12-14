/*
 * File:   SetCoverAlgorithmFactory.cpp
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

#ifndef HTD_SETCOVERALGORITHMFACTORY_CPP
#define HTD_SETCOVERALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/HeuristicSetCoverAlgorithm.hpp>

#include <stdexcept>

htd::SetCoverAlgorithmFactory::SetCoverAlgorithmFactory(void)
{
    constructionTemplate_ = new htd::HeuristicSetCoverAlgorithm();
}

htd::SetCoverAlgorithmFactory::~SetCoverAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::SetCoverAlgorithmFactory & htd::SetCoverAlgorithmFactory::instance(void)
{
    static htd::SetCoverAlgorithmFactory instance_;

    return instance_;
}

htd::ISetCoverAlgorithm * htd::SetCoverAlgorithmFactory::getSetCoverAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::SetCoverAlgorithmFactory::setConstructionTemplate(htd::ISetCoverAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::SetCoverAlgorithmFactory::setConstructionTemplate(htd::ISetCoverAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_SETCOVERALGORITHMFACTORY_CPP */
