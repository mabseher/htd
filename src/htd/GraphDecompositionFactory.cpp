/*
 * File:   GraphDecompositionFactory.cpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITIONFACTORY_CPP
#define HTD_HTD_GRAPHDECOMPOSITIONFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/GraphDecomposition.hpp>

#include <stdexcept>

htd::GraphDecompositionFactory::GraphDecompositionFactory(void)
{
    constructionTemplate_ = new htd::GraphDecomposition();
}

htd::GraphDecompositionFactory::~GraphDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::GraphDecompositionFactory & htd::GraphDecompositionFactory::instance(void)
{
    static htd::GraphDecompositionFactory instance_;

    return instance_;
}

htd::IMutableGraphDecomposition * htd::GraphDecompositionFactory::getGraphDecomposition(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableGraphDecomposition * htd::GraphDecompositionFactory::getGraphDecomposition(const htd::IGraphDecomposition & original)
{
    htd::IMutableGraphDecomposition * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::GraphDecompositionFactory::setConstructionTemplate(htd::IMutableGraphDecomposition * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::GraphDecompositionFactory::setConstructionTemplate(htd::IMutableGraphDecomposition *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::GraphDecompositionFactory::setConstructionTemplate(htd::IMutableGraphDecomposition *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutableGraphDecomposition & htd::GraphDecompositionFactory::accessMutableGraphDecomposition(htd::IGraphDecomposition & original)
{
    return *(dynamic_cast<htd::IMutableGraphDecomposition *>(&original));
}

const htd::IMutableGraphDecomposition & htd::GraphDecompositionFactory::accessMutableGraphDecomposition(const htd::IGraphDecomposition & original)
{
    return *(dynamic_cast<const htd::IMutableGraphDecomposition *>(&original));
}

#endif /* HTD_HTD_GRAPHDECOMPOSITIONFACTORY_CPP */
