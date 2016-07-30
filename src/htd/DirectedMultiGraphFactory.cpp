/*
 * File:   DirectedMultiGraphFactory.cpp
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

#ifndef HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_CPP
#define HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DirectedMultiGraphFactory.hpp>
#include <htd/DirectedMultiGraph.hpp>

#include <stdexcept>

htd::DirectedMultiGraphFactory::DirectedMultiGraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::DirectedMultiGraph(manager);
}

htd::DirectedMultiGraphFactory::DirectedMultiGraphFactory(const htd::DirectedMultiGraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableDirectedMultiGraph();
#endif
}

htd::DirectedMultiGraphFactory & htd::DirectedMultiGraphFactory::operator=(const htd::DirectedMultiGraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableDirectedMultiGraph();
    #endif
    }

    return *this;
}

htd::DirectedMultiGraphFactory::~DirectedMultiGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableDirectedMultiGraph * htd::DirectedMultiGraphFactory::getDirectedMultiGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableDirectedMultiGraph();
#endif
}

htd::IMutableDirectedMultiGraph * htd::DirectedMultiGraphFactory::getDirectedMultiGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableDirectedMultiGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableDirectedMultiGraph * ret = constructionTemplate_->cloneMutableDirectedMultiGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableDirectedMultiGraph * htd::DirectedMultiGraphFactory::getDirectedMultiGraph(const htd::IDirectedMultiGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableDirectedMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableDirectedMultiGraph * ret = constructionTemplate_->cloneMutableDirectedMultiGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::DirectedMultiGraphFactory::setConstructionTemplate(htd::IMutableDirectedMultiGraph * original)
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

htd::IMutableDirectedMultiGraph & htd::DirectedMultiGraphFactory::accessMutableDirectedMultiGraph(htd::IDirectedMultiGraph & original) const
{
    return *(dynamic_cast<htd::IMutableDirectedMultiGraph *>(&original));
}

const htd::IMutableDirectedMultiGraph & htd::DirectedMultiGraphFactory::accessMutableDirectedMultiGraph(const htd::IDirectedMultiGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableDirectedMultiGraph *>(&original));
}

#endif /* HTD_HTD_DIRECTEDMULTIGRAPHFACTORY_CPP */
