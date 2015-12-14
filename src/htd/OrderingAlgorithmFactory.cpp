/*
 * File:   OrderingAlgorithmFactory.cpp
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

#ifndef HTD_ORDERINGALGORITHMFACTORY_CPP
#define HTD_ORDERINGALGORITHMFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>

#include <stdexcept>

htd::OrderingAlgorithmFactory::OrderingAlgorithmFactory(void)
{
    constructionTemplate_ = new htd::MinFillOrderingAlgorithm();
}

htd::OrderingAlgorithmFactory::~OrderingAlgorithmFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::OrderingAlgorithmFactory & htd::OrderingAlgorithmFactory::instance(void)
{
    static htd::OrderingAlgorithmFactory instance_;

    return instance_;
}

htd::IOrderingAlgorithm * htd::OrderingAlgorithmFactory::getOrderingAlgorithm(void)
{
    return constructionTemplate_->clone();
}

void htd::OrderingAlgorithmFactory::setConstructionTemplate(htd::IOrderingAlgorithm * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::OrderingAlgorithmFactory::setConstructionTemplate(htd::IOrderingAlgorithm *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_ORDERINGALGORITHMFACTORY_CPP */
