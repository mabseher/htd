/*
 * File:   LabeledMultiGraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDMULTIGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDMULTIGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledMultiGraphFactory.hpp>
#include <htd/LabeledMultiGraph.hpp>

#include <stdexcept>

htd::LabeledMultiGraphFactory::LabeledMultiGraphFactory(void)
{
    constructionTemplate_ = new htd::LabeledMultiGraph();
}

htd::LabeledMultiGraphFactory::~LabeledMultiGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledMultiGraphFactory & htd::LabeledMultiGraphFactory::instance(void)
{
    static htd::LabeledMultiGraphFactory instance_;

    return instance_;
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(void)
{
    return constructionTemplate_->clone();
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(std::size_t initialSize)
{
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->clone();

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(const htd::ILabeledMultiGraph & original)
{
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;

    return ret;
}

void htd::LabeledMultiGraphFactory::setConstructionTemplate(htd::IMutableLabeledMultiGraph * original)
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

htd::IMutableLabeledMultiGraph & htd::LabeledMultiGraphFactory::accessMutableLabeledMultiGraph(htd::ILabeledMultiGraph & original)
{
    return *(dynamic_cast<htd::IMutableLabeledMultiGraph *>(&original));
}

const htd::IMutableLabeledMultiGraph & htd::LabeledMultiGraphFactory::accessMutableLabeledMultiGraph(const htd::ILabeledMultiGraph & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledMultiGraph *>(&original));
}

#endif /* HTD_HTD_LABELEDMULTIGRAPHFACTORY_CPP */
