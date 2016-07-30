/*
 * File:   StronglyConnectedComponentAlgorithmFactory.cpp
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

#ifndef HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_CPP
#define HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/StronglyConnectedComponentAlgorithmFactory.hpp>
#include <htd/IStronglyConnectedComponentAlgorithm.hpp>
#include <htd/TarjanStronglyConnectedComponentAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::StronglyConnectedComponentAlgorithmFactory::StronglyConnectedComponentAlgorithmFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::TarjanStronglyConnectedComponentAlgorithm(manager);
}

htd::StronglyConnectedComponentAlgorithmFactory::StronglyConnectedComponentAlgorithmFactory(const htd::StronglyConnectedComponentAlgorithmFactory & original)
{
    constructionTemplate_ = original.constructionTemplate_->clone();
}

htd::StronglyConnectedComponentAlgorithmFactory & htd::StronglyConnectedComponentAlgorithmFactory::operator=(const htd::StronglyConnectedComponentAlgorithmFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

        constructionTemplate_ = original.constructionTemplate_->clone();
    }

    return *this;
}

htd::StronglyConnectedComponentAlgorithmFactory::~StronglyConnectedComponentAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IStronglyConnectedComponentAlgorithm * htd::StronglyConnectedComponentAlgorithmFactory::getStronglyConnectedComponentAlgorithm(void) const
{
    return constructionTemplate_->clone();
}

htd::IStronglyConnectedComponentAlgorithm * htd::StronglyConnectedComponentAlgorithmFactory::getStronglyConnectedComponentAlgorithm(const htd::LibraryInstance * const manager) const
{
    htd::IStronglyConnectedComponentAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(manager);

    return ret;
}

void htd::StronglyConnectedComponentAlgorithmFactory::setConstructionTemplate(htd::IStronglyConnectedComponentAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HTD_STRONGLYCONNECTEDCOMPONENTALGORITHMFACTORY_CPP */
