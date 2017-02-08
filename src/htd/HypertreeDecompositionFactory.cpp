/*
 * File:   HypertreeDecompositionFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2017, Michael Abseher
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
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/HypertreeDecomposition.hpp>

htd::HypertreeDecompositionFactory::HypertreeDecompositionFactory(const htd::LibraryInstance * const manager) : htd::GraphTypeFactory<htd::IHypertreeDecomposition, htd::IMutableHypertreeDecomposition>(new htd::HypertreeDecomposition(manager))
{

}

htd::HypertreeDecompositionFactory::~HypertreeDecompositionFactory()
{

}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::createInstance(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableHypertreeDecomposition();
#endif
}

htd::IMutableHypertreeDecomposition * htd::HypertreeDecompositionFactory::createInstance(const htd::ITreeDecomposition & original) const
{
    htd::IMutableHypertreeDecomposition * ret = createInstance();

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    *ret = original;
#else
    ret->assign(original);
#endif

    return ret;
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONFACTORY_CPP */
