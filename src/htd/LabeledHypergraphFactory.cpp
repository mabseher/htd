/*
 * File:   LabeledHypergraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDHYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledHypergraphFactory.hpp>
#include <htd/LabeledHypergraph.hpp>

#include <stdexcept>

htd::LabeledHypergraphFactory::LabeledHypergraphFactory(void)
{
    constructionTemplate_ = new htd::LabeledHypergraph();
}

htd::LabeledHypergraphFactory::~LabeledHypergraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledHypergraphFactory & htd::LabeledHypergraphFactory::instance(void)
{
    static htd::LabeledHypergraphFactory instance_;

    return instance_;
}

htd::IMutableLabeledHypergraph * htd::LabeledHypergraphFactory::getLabeledHypergraph(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableLabeledHypergraph * htd::LabeledHypergraphFactory::getLabeledHypergraph(std::size_t initialSize)
{
    htd::IMutableLabeledHypergraph * ret = constructionTemplate_->clone();

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledHypergraph * htd::LabeledHypergraphFactory::getLabeledHypergraph(const htd::ILabeledHypergraph & original)
{
    htd::IMutableLabeledHypergraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

htd::IMutableLabeledHypergraph * htd::LabeledHypergraphFactory::getLabeledHypergraph(const htd::ILabeledMultiHypergraph & original)
{
    htd::IMutableLabeledHypergraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::LabeledHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledHypergraph * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::LabeledHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledHypergraph *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::LabeledHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledHypergraph *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutableLabeledHypergraph & htd::LabeledHypergraphFactory::accessMutableLabeledHypergraph(htd::ILabeledHypergraph & original)
{
    return *(dynamic_cast<htd::IMutableLabeledHypergraph *>(&original));
}

const htd::IMutableLabeledHypergraph & htd::LabeledHypergraphFactory::accessMutableLabeledHypergraph(const htd::ILabeledHypergraph & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledHypergraph *>(&original));
}

#endif /* HTD_HTD_LABELEDHYPERGRAPHFACTORY_CPP */
