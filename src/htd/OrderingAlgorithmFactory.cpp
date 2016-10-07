/*
 * File:   OrderingAlgorithmFactory.cpp
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

#ifndef HTD_HTD_ORDERINGALGORITHMFACTORY_CPP
#define HTD_HTD_ORDERINGALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>

#include <stdexcept>

htd::OrderingAlgorithmFactory::OrderingAlgorithmFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::MinFillOrderingAlgorithm(manager);
}

htd::OrderingAlgorithmFactory::OrderingAlgorithmFactory(const htd::OrderingAlgorithmFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneOrderingAlgorithm();
#endif
}

htd::OrderingAlgorithmFactory & htd::OrderingAlgorithmFactory::operator=(const htd::OrderingAlgorithmFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
#else
        constructionTemplate_ = original.constructionTemplate_->cloneOrderingAlgorithm();
#endif
    }

    return *this;
}

htd::OrderingAlgorithmFactory::~OrderingAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IOrderingAlgorithm * htd::OrderingAlgorithmFactory::getOrderingAlgorithm(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneOrderingAlgorithm();
#endif
}

htd::IOrderingAlgorithm * htd::OrderingAlgorithmFactory::getOrderingAlgorithm(const htd::LibraryInstance * const manager) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IOrderingAlgorithm * ret = constructionTemplate_->clone();
#else
    htd::IOrderingAlgorithm * ret = constructionTemplate_->cloneOrderingAlgorithm();
#endif

    ret->setManagementInstance(manager);

    return ret;
}

void htd::OrderingAlgorithmFactory::setConstructionTemplate(htd::IOrderingAlgorithm * original)
{
    HTD_ASSERT(original != nullptr)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HTD_ORDERINGALGORITHMFACTORY_CPP */
