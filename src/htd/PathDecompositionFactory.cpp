/*
 * File:   PathDecompositionFactory.cpp
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

#ifndef HTD_HTD_PATHDECOMPOSITIONFACTORY_CPP
#define HTD_HTD_PATHDECOMPOSITIONFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/PathDecompositionFactory.hpp>
#include <htd/PathDecomposition.hpp>

#include <stdexcept>

htd::PathDecompositionFactory::PathDecompositionFactory(void)
{
    constructionTemplate_ = new htd::PathDecomposition();
}

htd::PathDecompositionFactory::~PathDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::PathDecompositionFactory & htd::PathDecompositionFactory::instance(void)
{
    static htd::PathDecompositionFactory instance_;

    return instance_;
}

htd::IMutablePathDecomposition * htd::PathDecompositionFactory::getPathDecomposition(void)
{
    return constructionTemplate_->clone();
}

//TODO Use construction template!
htd::IMutablePathDecomposition * htd::PathDecompositionFactory::getPathDecomposition(const htd::IPathDecomposition & original)
{
    htd::IMutablePathDecomposition * ret = new htd::PathDecomposition(original); //TODO constructionTemplate_->clone();

    //TODO Copy decomposition content!

    return ret;
}

void htd::PathDecompositionFactory::setConstructionTemplate(htd::IMutablePathDecomposition * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::PathDecompositionFactory::setConstructionTemplate(htd::IMutablePathDecomposition *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::PathDecompositionFactory::setConstructionTemplate(htd::IMutablePathDecomposition *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutablePathDecomposition & htd::PathDecompositionFactory::accessMutablePathDecomposition(htd::IPathDecomposition & original)
{
    return *(dynamic_cast<htd::IMutablePathDecomposition *>(&original));
}

const htd::IMutablePathDecomposition & htd::PathDecompositionFactory::accessMutablePathDecomposition(const htd::IPathDecomposition & original)
{
    return *(dynamic_cast<const htd::IMutablePathDecomposition *>(&original));
}

#endif /* HTD_HTD_PATHDECOMPOSITIONFACTORY_CPP */
