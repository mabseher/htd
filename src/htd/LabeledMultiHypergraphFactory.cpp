/*
 * File:   LabeledMultiHypergraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledMultiHypergraphFactory.hpp>
#include <htd/LabeledMultiHypergraph.hpp>

#include <stdexcept>

htd::LabeledMultiHypergraphFactory::LabeledMultiHypergraphFactory(void)
{
    constructionTemplate_ = new htd::LabeledMultiHypergraph();
}

htd::LabeledMultiHypergraphFactory::~LabeledMultiHypergraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledMultiHypergraphFactory & htd::LabeledMultiHypergraphFactory::instance(void)
{
    static htd::LabeledMultiHypergraphFactory instance_;

    return instance_;
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::getLabeledMultiHypergraph(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::getLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original)
{
    htd::IMutableLabeledMultiHypergraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::LabeledMultiHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledMultiHypergraph * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::LabeledMultiHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledMultiHypergraph *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::LabeledMultiHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledMultiHypergraph *)");
    }

    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }

    constructionTemplate_ = original;
}

htd::IMutableLabeledMultiHypergraph & htd::LabeledMultiHypergraphFactory::accessMutableLabeledMultiHypergraph(htd::ILabeledMultiHypergraph & original)
{
    return *(dynamic_cast<htd::IMutableLabeledMultiHypergraph *>(&original));
}

const htd::IMutableLabeledMultiHypergraph & htd::LabeledMultiHypergraphFactory::accessMutableLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledMultiHypergraph *>(&original));
}

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP */
