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
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>

#include <memory>
#include <stdexcept>

htd::ConnectedComponentAlgorithmFactory::ConnectedComponentAlgorithmFactory(void)
{
    constructionTemplate_ = new htd::DepthFirstConnectedComponentAlgorithm();
}

htd::ConnectedComponentAlgorithmFactory::~ConnectedComponentAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::ConnectedComponentAlgorithmFactory & htd::ConnectedComponentAlgorithmFactory::instance(void)
{
    static htd::ConnectedComponentAlgorithmFactory instance_;

    return instance_;
}

htd::IConnectedComponentAlgorithm * htd::ConnectedComponentAlgorithmFactory::getConnectedComponentAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::ConnectedComponentAlgorithmFactory::setConstructionTemplate(htd::IConnectedComponentAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::ConnectedComponentAlgorithmFactory::setConstructionTemplate(htd::IConnectedComponentAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HTD_CONNECTEDCOMPONENTALGORITHMFACTORY_CPP */
