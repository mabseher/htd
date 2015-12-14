/*
 * File:   GraphFactory.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_GRAPHFACTORY_CPP
#define HTD_GRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/GraphFactory.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/Graph.hpp>

#include <stdexcept>

htd::GraphFactory::GraphFactory(void)
{
    constructionTemplate_ = new htd::Graph();
}

htd::GraphFactory::~GraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::GraphFactory & htd::GraphFactory::instance(void)
{
    static htd::GraphFactory instance_;

    return instance_;
}

htd::IMutableGraph * htd::GraphFactory::getGraph(void)
{
    return constructionTemplate_->clone();
}

void htd::GraphFactory::setConstructionTemplate(htd::IMutableGraph * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::GraphFactory::setConstructionTemplate(htd::IMutableGraph *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::GraphFactory::setConstructionTemplate(htd::IMutableGraph *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_GRAPHFACTORY_CPP */
