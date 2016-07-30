/*
 * File:   LabeledDirectedMultiGraphFactory.cpp
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

#ifndef HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP
#define HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledDirectedMultiGraphFactory.hpp>
#include <htd/LabeledDirectedMultiGraph.hpp>

#include <stdexcept>

htd::LabeledDirectedMultiGraphFactory::LabeledDirectedMultiGraphFactory(const htd::LibraryInstance * const manager)
{
    constructionTemplate_ = new htd::LabeledDirectedMultiGraph(manager);
}

htd::LabeledDirectedMultiGraphFactory::LabeledDirectedMultiGraphFactory(const htd::LabeledDirectedMultiGraphFactory & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    constructionTemplate_ = original.constructionTemplate_->clone();
#else
    constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();
#endif
}

htd::LabeledDirectedMultiGraphFactory & htd::LabeledDirectedMultiGraphFactory::operator=(const htd::LabeledDirectedMultiGraphFactory & original)
{
    if (this != &original)
    {
        delete constructionTemplate_;

    #ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        constructionTemplate_ = original.constructionTemplate_->clone();
    #else
        constructionTemplate_ = original.constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();
    #endif
    }

    return *this;
}

htd::LabeledDirectedMultiGraphFactory::~LabeledDirectedMultiGraphFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraphFactory::getLabeledDirectedMultiGraph(void) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();
#endif
}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraphFactory::getLabeledDirectedMultiGraph(std::size_t initialSize) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledDirectedMultiGraph * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledDirectedMultiGraph * ret = constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();
#endif

    ret->addVertices(initialSize);

    return ret;
}

htd::IMutableLabeledDirectedMultiGraph * htd::LabeledDirectedMultiGraphFactory::getLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) const
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledDirectedMultiGraph * ret = constructionTemplate_->clone();

    *ret = original;
#else
    htd::IMutableLabeledDirectedMultiGraph * ret = constructionTemplate_->cloneMutableLabeledDirectedMultiGraph();

    ret->assign(original);
#endif

    return ret;
}

void htd::LabeledDirectedMultiGraphFactory::setConstructionTemplate(htd::IMutableLabeledDirectedMultiGraph * original)
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

htd::IMutableLabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraphFactory::accessMutableLabeledDirectedMultiGraph(htd::ILabeledDirectedMultiGraph & original) const
{
    return *(dynamic_cast<htd::IMutableLabeledDirectedMultiGraph *>(&original));
}

const htd::IMutableLabeledDirectedMultiGraph & htd::LabeledDirectedMultiGraphFactory::accessMutableLabeledDirectedMultiGraph(const htd::ILabeledDirectedMultiGraph & original) const
{
    return *(dynamic_cast<const htd::IMutableLabeledDirectedMultiGraph *>(&original));
}

#endif /* HTD_HTD_LABELEDDIRECTEDMULTIGRAPHFACTORY_CPP */
