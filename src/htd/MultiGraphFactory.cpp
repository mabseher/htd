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
    return constructionTemplate_->clone();
}

htd::IMutableMultiGraph * htd::MultiGraphFactory::getMultiGraph(std::size_t initialSize)
{
    htd::IMutableMultiGraph * ret = constructionTemplate_->clone();

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableMultiGraph * htd::MultiGraphFactory::getMultiGraph(const htd::IMultiGraph & original)
{
    htd::IMutableMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::MultiGraphFactory::setConstructionTemplate(htd::IMutableMultiGraph * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::MultiGraphFactory::setConstructionTemplate(htd::IMutableMultiGraph *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::MultiGraphFactory::setConstructionTemplate(htd::IMutableMultiGraph *)");
    }

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
