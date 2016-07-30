/*
 * File:   HypertreeDecompositionFactory.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP
#define HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/Vertex.hpp>

#include <stdexcept>

htd::HypertreeDecompositionFactory::HypertreeDecompositionFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::HypertreeDecomposition(manager);
}

htd::HypertreeDecompositionFactory::HypertreeDecompositionFactory(const htd::HypertreeDecompositionFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableHypertreeDecomposition();
#endif
}

htd::HypertreeDecompositionFactory & htd::HypertreeDecompositionFactory::operator=(const htd::HypertreeDecompositionFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableHypertreeDecomposition();
    #endif
    }

    return *this;
}

htd::HypertreeDecompositionFactory::~HypertreeDecompositionFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::getHypertreeDecomposition(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableHypertreeDecomposition();
#endif
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::getHypertreeDecomposition(const htd::ITreeDecomposition & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableHypertreeDecomposition * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableHypertreeDecomposition * ret = constructionTemplate_->cloneMutableHypertreeDecomposition();

    ret->assign(original);
#endif

    return ret;
}

void htd::HypertreeDecompositionFactory::setConstructionTemplate(htd::IMutableHypertreeDecomposition * original)
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

htd::IMutableHypertreeDecomposition & htd::HypertreeDecompositionFactory::accessMutableHypertreeDecomposition(htd::IHypertreeDecomposition & original) const
{
    return *(dynamic_cast<htd::IMutableHypertreeDecomposition *>(&original));
}

const htd::IMutableHypertreeDecomposition & htd::HypertreeDecompositionFactory::accessMutableHypertreeDecomposition(const htd::IHypertreeDecomposition & original) const
{
    return *(dynamic_cast<const htd::IMutableHypertreeDecomposition *>(&original));
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP */
