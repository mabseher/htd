/*
 * File:   LabeledDirectedGraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledDirectedGraphFactory.hpp>
#include <htd/LabeledDirectedGraph.hpp>

#include <stdexcept>

htd::LabeledDirectedGraphFactory::LabeledDirectedGraphFactory(void)
{
    constructionTemplate_ = new htd::LabeledDirectedGraph();
}

htd::LabeledDirectedGraphFactory::~LabeledDirectedGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledDirectedGraphFactory & htd::LabeledDirectedGraphFactory::instance(void)
{
    static htd::LabeledDirectedGraphFactory instance_;

    return instance_;
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::getLabeledDirectedGraph(void)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledDirectedGraph();
#endif
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::getLabeledDirectedGraph(std::size_t initialSize)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->cloneMutableLabeledDirectedGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::getLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->cloneMutableLabeledDirectedGraph();

    ret->assign(original);
#endif

    return ret;
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::getLabeledDirectedGraph(const htd::ILabeledDirectedMultiGraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledDirectedGraph * ret = constructionTemplate_->cloneMutableLabeledDirectedGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::LabeledDirectedGraphFactory::setConstructionTemplate(htd::IMutableLabeledDirectedGraph * original)
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

htd::IMutableLabeledDirectedGraph & htd::LabeledDirectedGraphFactory::accessMutableLabeledDirectedGraph(htd::ILabeledDirectedGraph & original)
{
    return *(dynamic_cast<htd::IMutableLabeledDirectedGraph *>(&original));
}

const htd::IMutableLabeledDirectedGraph & htd::LabeledDirectedGraphFactory::accessMutableLabeledDirectedGraph(const htd::ILabeledDirectedGraph & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledDirectedGraph *>(&original));
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP */
