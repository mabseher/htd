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
#include <htd/Helpers.hpp>
#include <htd/PathDecompositionFactory.hpp>
#include <htd/PathDecomposition.hpp>

#include <stdexcept>

htd::PathDecompositionFactory::PathDecompositionFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::PathDecomposition(manager);
}

htd::PathDecompositionFactory::PathDecompositionFactory(const htd::PathDecompositionFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutablePathDecomposition();
#endif
}

htd::PathDecompositionFactory & htd::PathDecompositionFactory::operator=(const htd::PathDecompositionFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutablePathDecomposition();
    #endif
    }

    return *this;
}

htd::PathDecompositionFactory::~PathDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutablePathDecomposition * htd::PathDecompositionFactory::getPathDecomposition(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutablePathDecomposition();
#endif
}

htd::IMutablePathDecomposition * htd::PathDecompositionFactory::getPathDecomposition(const htd::IPathDecomposition & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutablePathDecomposition * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutablePathDecomposition * ret = constructionTemplate_->cloneMutablePathDecomposition();

    ret->assign(original);
#endif

    return ret;
}

void htd::PathDecompositionFactory::setConstructionTemplate(htd::IMutablePathDecomposition * original)
{
    HTD_ASSERT(original != nullptr)
    HTD_ASSERT(original->vertexCount() == 0)

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutablePathDecomposition & htd::PathDecompositionFactory::accessMutablePathDecomposition(htd::IPathDecomposition & original) const
{
    return *(dynamic_cast<htd::IMutablePathDecomposition *>(&original));
}

const htd::IMutablePathDecomposition & htd::PathDecompositionFactory::accessMutablePathDecomposition(const htd::IPathDecomposition & original) const
{
    return *(dynamic_cast<const htd::IMutablePathDecomposition *>(&original));
}

#endif /* HTD_HTD_PATHDECOMPOSITIONFACTORY_CPP */
