/*
 * File:   HypergraphFactory.cpp
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

#ifndef HTD_HYPERGRAPHFACTORY_CPP
#define HTD_HYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/IMutableHypergraph.hpp>
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
    return constructionTemplate_->clone();
}

void htd::HypergraphFactory::setConstructionTemplate(htd::IMutableHypergraph * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::HypergraphFactory::setConstructionTemplate(htd::IMutableHypergraph *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::HypergraphFactory::setConstructionTemplate(htd::IMutableHypergraph *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

#endif /* HTD_HYPERGRAPHFACTORY_CPP */
