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

htd::LabeledMultiGraphFactory::LabeledMultiGraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::LabeledMultiGraph(manager);
}

htd::LabeledMultiGraphFactory::LabeledMultiGraphFactory(const htd::LabeledMultiGraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledMultiGraph();
#endif
}

htd::LabeledMultiGraphFactory & htd::LabeledMultiGraphFactory::operator=(const htd::LabeledMultiGraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledMultiGraph();
    #endif
    }

    return *this;
}

htd::LabeledMultiGraphFactory::~LabeledMultiGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledMultiGraph();
#endif
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->cloneMutableLabeledMultiGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledMultiGraph * htd::LabeledMultiGraphFactory::getLabeledMultiGraph(const htd::ILabeledMultiGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledMultiGraph * ret = constructionTemplate_->cloneMutableLabeledMultiGraph();

    ret->assign(original);
#endif

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

htd::IMutableLabeledMultiGraph & htd::LabeledMultiGraphFactory::accessMutableLabeledMultiGraph(htd::ILabeledMultiGraph & original) const
{
    return *(dynamic_cast<htd::IMutableLabeledMultiGraph *>(&original));
}

const htd::IMutableLabeledMultiGraph & htd::LabeledMultiGraphFactory::accessMutableLabeledMultiGraph(const htd::ILabeledMultiGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableLabeledMultiGraph *>(&original));
}

#endif /* HTD_HTD_LABELEDMULTIGRAPHFACTORY_CPP */
