/*
 * File:   HypergraphFactory.cpp
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

#ifndef HTD_HTD_DIRECTEDGRAPHFACTORY_CPP
#define HTD_HTD_DIRECTEDGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/DirectedGraphFactory.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/DirectedGraph.hpp>

#include <stdexcept>

htd::DirectedGraphFactory::DirectedGraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::DirectedGraph(manager);
}

htd::DirectedGraphFactory::DirectedGraphFactory(const htd::DirectedGraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableDirectedGraph();
#endif
}

htd::DirectedGraphFactory & htd::DirectedGraphFactory::operator=(const htd::DirectedGraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableDirectedGraph();
    #endif
    }

    return *this;
}

htd::DirectedGraphFactory::~DirectedGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableDirectedGraph * htd::DirectedGraphFactory::getDirectedGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableDirectedGraph();
#endif
}

htd::IMutableDirectedGraph * htd::DirectedGraphFactory::getDirectedGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableDirectedGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableDirectedGraph * ret = constructionTemplate_->cloneMutableDirectedGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableDirectedGraph * htd::DirectedGraphFactory::getDirectedGraph(const htd::IDirectedGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableDirectedGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableDirectedGraph * ret = constructionTemplate_->cloneMutableDirectedGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::DirectedGraphFactory::setConstructionTemplate(htd::IMutableDirectedGraph * original)
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

htd::IMutableDirectedGraph & htd::DirectedGraphFactory::accessMutableDirectedGraph(htd::IDirectedGraph & original) const
{
    return *(dynamic_cast<htd::IMutableDirectedGraph *>(&original));
}

const htd::IMutableDirectedGraph & htd::DirectedGraphFactory::accessMutableDirectedGraph(const htd::IDirectedGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableDirectedGraph *>(&original));
}

#endif /* HTD_HTD_DIRECTEDGRAPHFACTORY_CPP */
