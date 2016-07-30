/*
 * File:   ConnectedComponentAlgorithmFactory.cpp
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

#ifndef HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_CPP
#define HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::ConnectedComponentAlgorithmFactory::ConnectedComponentAlgorithmFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::DepthFirstConnectedComponentAlgorithm(manager);
}

htd::ConnectedComponentAlgorithmFactory::ConnectedComponentAlgorithmFactory(const htd::ConnectedComponentAlgorithmFactory & original)
{
    constructionTemplate_ = original.constructionTemplate_->clone();
}

htd::ConnectedComponentAlgorithmFactory & htd::ConnectedComponentAlgorithmFactory::operator=(const htd::ConnectedComponentAlgorithmFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

        constructionTemplate_ = original.constructionTemplate_->clone();
    }

    return *this;
}

htd::ConnectedComponentAlgorithmFactory::~ConnectedComponentAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IConnectedComponentAlgorithm * htd::ConnectedComponentAlgorithmFactory::getConnectedComponentAlgorithm(void) const
{
    return constructionTemplate_->clone();
}

htd::IConnectedComponentAlgorithm * htd::ConnectedComponentAlgorithmFactory::getConnectedComponentAlgorithm(const htd::LibraryInstance * const manager) const
{
    htd::IConnectedComponentAlgorithm * ret = constructionTemplate_->clone();

    ret->setManagementInstance(manager);

    return ret;
}

void htd::ConnectedComponentAlgorithmFactory::setConstructionTemplate(htd::IConnectedComponentAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_CPP */
