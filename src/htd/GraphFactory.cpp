/*
 * File:   GraphFactory.cpp
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

#ifndef HTD_HTD_GRAPHFACTORY_CPP
#define HTD_HTD_GRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphFactory.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/Graph.hpp>

#include <stdexcept>

htd::GraphFactory::GraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::Graph(manager);
}

htd::GraphFactory::GraphFactory(const htd::GraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableGraph();
#endif
}

htd::GraphFactory & htd::GraphFactory::operator=(const htd::GraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableGraph();
    #endif
    }

    return *this;
}

htd::GraphFactory::~GraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableGraph * htd::GraphFactory::getGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableGraph();
#endif
}

htd::IMutableGraph * htd::GraphFactory::getGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableGraph * ret = constructionTemplate_->cloneMutableGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableGraph * htd::GraphFactory::getGraph(const htd::IGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableGraph * ret = constructionTemplate_->cloneMutableGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::GraphFactory::setConstructionTemplate(htd::IMutableGraph * original)
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

htd::IMutableGraph & htd::GraphFactory::accessMutableGraph(htd::IGraph & original) const
{
    return *(dynamic_cast<htd::IMutableGraph *>(&original));
}

const htd::IMutableGraph & htd::GraphFactory::accessMutableGraph(const htd::IGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableGraph *>(&original));
}

#endif /* HTD_HTD_GRAPHFACTORY_CPP */
