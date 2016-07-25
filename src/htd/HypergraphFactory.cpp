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

#ifndef HTD_HTD_HYPERGRAPHFACTORY_CPP
#define HTD_HTD_HYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/Hypergraph.hpp>

#include <stdexcept>

htd::HypergraphFactory::HypergraphFactory(void)
{
    constructionTemplate_ = new htd::Hypergraph();
}

htd::HypergraphFactory::~HypergraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::HypergraphFactory & htd::HypergraphFactory::instance(void)
{
    static htd::HypergraphFactory instance_;

    return instance_;
}

htd::IMutableHypergraph * htd::HypergraphFactory::getHypergraph(void)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableHypergraph();
#endif
}

htd::IMutableHypergraph * htd::HypergraphFactory::getHypergraph(std::size_t initialSize)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableHypergraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableHypergraph * ret = constructionTemplate_->cloneMutableHypergraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableHypergraph * htd::HypergraphFactory::getHypergraph(const htd::IHypergraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableHypergraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableHypergraph * ret = constructionTemplate_->cloneMutableHypergraph();
#endif

    *ret = original;

    return ret;
}

htd::IMutableHypergraph * htd::HypergraphFactory::getHypergraph(const htd::IMultiHypergraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableHypergraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableHypergraph * ret = constructionTemplate_->cloneMutableHypergraph();
#endif

    *ret = original;

    return ret;
}

void htd::HypergraphFactory::setConstructionTemplate(htd::IMutableHypergraph * original)
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

htd::IMutableHypergraph & htd::HypergraphFactory::accessMutableHypergraph(htd::IHypergraph & original)
{
    return *(dynamic_cast<htd::IMutableHypergraph *>(&original));
}

const htd::IMutableHypergraph & htd::HypergraphFactory::accessMutableHypergraph(const htd::IHypergraph & original)
{
    return *(dynamic_cast<const htd::IMutableHypergraph *>(&original));
}

#endif /* HTD_HTD_HYPERGRAPHFACTORY_CPP */
