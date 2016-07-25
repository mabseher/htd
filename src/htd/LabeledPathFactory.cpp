/*
 * File:   LabeledPathFactory.cpp
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

#ifndef HTD_HTD_LABELEDPATHFACTORY_CPP
#define HTD_HTD_LABELEDPATHFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledPathFactory.hpp>
#include <htd/LabeledPath.hpp>

#include <stdexcept>

htd::LabeledPathFactory::LabeledPathFactory(void)
{
    constructionTemplate_ = new htd::LabeledPath();
}

htd::LabeledPathFactory::~LabeledPathFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledPathFactory & htd::LabeledPathFactory::instance(void)
{
    static htd::LabeledPathFactory instance_;

    return instance_;
}

htd::IMutableLabeledPath * htd::LabeledPathFactory::getLabeledPath(void)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledPath();
#endif
}

htd::IMutableLabeledPath * htd::LabeledPathFactory::getLabeledPath(const htd::ILabeledPath & original)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableLabeledPath * ret = constructionTemplate_->clone();
#else
    htd::IMutableLabeledPath * ret = constructionTemplate_->cloneMutableLabeledPath();
#endif

    *ret = original;

    return ret;
}

void htd::LabeledPathFactory::setConstructionTemplate(htd::IMutableLabeledPath * original)
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

htd::IMutableLabeledPath & htd::LabeledPathFactory::accessMutableLabeledPath(htd::ILabeledPath & original)
{
    return *(dynamic_cast<htd::IMutableLabeledPath *>(&original));
}

const htd::IMutableLabeledPath & htd::LabeledPathFactory::accessMutableLabeledPath(const htd::ILabeledPath & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledPath *>(&original));
}

#endif /* HTD_HTD_LABELEDPATHFACTORY_CPP */
