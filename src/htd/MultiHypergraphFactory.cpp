/*
 * File:   MultiHypergraphFactory.cpp
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

#ifndef HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP
#define HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/MultiHypergraph.hpp>

#include <stdexcept>

htd::MultiHypergraphFactory::MultiHypergraphFactory(void)
{
    constructionTemplate_ = new htd::MultiHypergraph();
}

htd::MultiHypergraphFactory::~MultiHypergraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::MultiHypergraphFactory & htd::MultiHypergraphFactory::instance(void)
{
    static htd::MultiHypergraphFactory instance_;

    return instance_;
}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(std::size_t initialSize)
{
    htd::IMutableMultiHypergraph * ret = constructionTemplate_->clone();

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableMultiHypergraph * htd::MultiHypergraphFactory::getMultiHypergraph(const htd::IMultiHypergraph & original)
{
    htd::IMutableMultiHypergraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::MultiHypergraphFactory::setConstructionTemplate(htd::IMutableMultiHypergraph * original)
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

htd::IMutableMultiHypergraph & htd::MultiHypergraphFactory::accessMutableMultiHypergraph(htd::IMultiHypergraph & original)
{
    return *(dynamic_cast<htd::IMutableMultiHypergraph *>(&original));
}

const htd::IMutableMultiHypergraph & htd::MultiHypergraphFactory::accessMutableMultiHypergraph(const htd::IMultiHypergraph & original)
{
    return *(dynamic_cast<const htd::IMutableMultiHypergraph *>(&original));
}

#endif /* HTD_HTD_MULTIHYPERGRAPHFACTORY_CPP */
