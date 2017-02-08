/*
 * File:   LabeledDirectedGraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/LabeledDirectedGraphFactory.hpp>
#include <htd/LabeledDirectedGraph.hpp>

htd::LabeledDirectedGraphFactory::LabeledDirectedGraphFactory(const htd::LibraryInstance * const manager) : htd::GraphTypeFactory<htd::ILabeledDirectedGraph, htd::IMutableLabeledDirectedGraph>(new htd::LabeledDirectedGraph(manager))
{

}

htd::LabeledDirectedGraphFactory::~LabeledDirectedGraphFactory()
{

}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::createInstance(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledDirectedGraph();
#endif
}

htd::IMutableLabeledDirectedGraph * htd::LabeledDirectedGraphFactory::createInstance(std::size_t initialSize) const
{
    htd::IMutableLabeledDirectedGraph * ret = createInstance();

    ret->addVertices(initialSize);

    return ret;
}

#endif /* HTD_HTD_LABELEDDIRECTEDGRAPHFACTORY_CPP */
