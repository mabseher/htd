/*
 * File:   MultiGraphFactory.cpp
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

#ifndef HTD_HTD_MULTIGRAPHFACTORY_CPP
#define HTD_HTD_MULTIGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiGraphFactory.hpp>
#include <htd/MultiGraph.hpp>

#include <stdexcept>

htd::MultiGraphFactory::MultiGraphFactory(void)
{
    constructionTemplate_ = new htd::MultiGraph();
}

htd::MultiGraphFactory::~MultiGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::MultiGraphFactory & htd::MultiGraphFactory::instance(void)
{
    static htd::MultiGraphFactory instance_;

    return instance_;
}

htd::IMutableMultiGraph * htd::MultiGraphFactory::getMultiGraph(void)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableMultiGraph();
#endif
}

htd::IMutableMultiGraph * htd::MultiGraphFactory::getMultiGraph(std::size_t initialSize)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableMultiGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableMultiGraph * ret = constructionTemplate_->cloneMutableMultiGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableMultiGraph * htd::MultiGraphFactory::getMultiGraph(const htd::IMultiGraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableMultiGraph * ret = constructionTemplate_->cloneMutableMultiGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::MultiGraphFactory::setConstructionTemplate(htd::IMutableMultiGraph * original)
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

htd::IMutableMultiGraph & htd::MultiGraphFactory::accessMutableMultiGraph(htd::IMultiGraph & original)
{
    return *(dynamic_cast<htd::IMutableMultiGraph *>(&original));
}

const htd::IMutableMultiGraph & htd::MultiGraphFactory::accessMutableMultiGraph(const htd::IMultiGraph & original)
{
    return *(dynamic_cast<const htd::IMutableMultiGraph *>(&original));
}

#endif /* HTD_HTD_MULTIGRAPHFACTORY_CPP */
