/*
 * File:   LabeledGraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledGraphFactory.hpp>
#include <htd/LabeledGraph.hpp>

#include <stdexcept>

htd::LabeledGraphFactory::LabeledGraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::LabeledGraph(manager);
}

htd::LabeledGraphFactory::LabeledGraphFactory(const htd::LabeledGraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledGraph();
#endif
}

htd::LabeledGraphFactory & htd::LabeledGraphFactory::operator=(const htd::LabeledGraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledGraph();
    #endif
    }

    return *this;
}

htd::LabeledGraphFactory::~LabeledGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableLabeledGraph * htd::LabeledGraphFactory::getLabeledGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledGraph();
#endif
}

htd::IMutableLabeledGraph * htd::LabeledGraphFactory::getLabeledGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledGraph * ret = constructionTemplate_->cloneMutableLabeledGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledGraph * htd::LabeledGraphFactory::getLabeledGraph(const htd::ILabeledGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledGraph * ret = constructionTemplate_->cloneMutableLabeledGraph();

    ret->assign(original);
#endif

    return ret;
}

htd::IMutableLabeledGraph * htd::LabeledGraphFactory::getLabeledGraph(const htd::ILabeledMultiGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledGraph * ret = constructionTemplate_->cloneMutableLabeledGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::LabeledGraphFactory::setConstructionTemplate(htd::IMutableLabeledGraph * original)
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

htd::IMutableLabeledGraph & htd::LabeledGraphFactory::accessMutableLabeledGraph(htd::ILabeledGraph & original) const
{
    return *(dynamic_cast<htd::IMutableLabeledGraph *>(&original));
}

const htd::IMutableLabeledGraph & htd::LabeledGraphFactory::accessMutableLabeledGraph(const htd::ILabeledGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableLabeledGraph *>(&original));
}

#endif /* HTD_HTD_LABELEDGRAPHFACTORY_CPP */
