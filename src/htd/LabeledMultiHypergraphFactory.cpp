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
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledMultiHypergraph();
#endif
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::getLabeledMultiHypergraph(std::size_t initialSize)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledMultiHypergraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledMultiHypergraph * ret = constructionTemplate_->cloneMutableLabeledMultiHypergraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledMultiHypergraph * htd::LabeledMultiHypergraphFactory::getLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledMultiHypergraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledMultiHypergraph * ret = constructionTemplate_->cloneMutableLabeledMultiHypergraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::LabeledMultiHypergraphFactory::setConstructionTemplate(htd::IMutableLabeledMultiHypergraph * original)
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

htd::IMutableLabeledMultiHypergraph & htd::LabeledMultiHypergraphFactory::accessMutableLabeledMultiHypergraph(htd::ILabeledMultiHypergraph & original)
{
    return *(dynamic_cast<htd::IMutableLabeledMultiHypergraph *>(&original));
}

const htd::IMutableLabeledMultiHypergraph & htd::LabeledMultiHypergraphFactory::accessMutableLabeledMultiHypergraph(const htd::ILabeledMultiHypergraph & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledMultiHypergraph *>(&original));
}

#endif /* HTD_HTD_LABELEDMULTIHYPERGRAPHFACTORY_CPP */
