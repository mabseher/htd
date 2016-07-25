/*
 * File:   LabeledTreeFactory.cpp
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

#ifndef HTD_HTD_LABELEDTREEFACTORY_CPP
#define HTD_HTD_LABELEDTREEFACTORY_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledTreeFactory.hpp>
#include <htd/LabeledTree.hpp>

#include <stdexcept>

htd::LabeledTreeFactory::LabeledTreeFactory(void)
{
    constructionTemplate_ = new htd::LabeledTree();
}

htd::LabeledTreeFactory::~LabeledTreeFactory()
{
    if (constructionTemplate_ != nullptr)
    {
        delete constructionTemplate_;

        constructionTemplate_ = nullptr;
    }
}

htd::LabeledTreeFactory & htd::LabeledTreeFactory::instance(void)
{
    static htd::LabeledTreeFactory instance_;

    return instance_;
}

htd::IMutableLabeledTree * htd::LabeledTreeFactory::getLabeledTree(void)
{
#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return constructionTemplate_->clone();
#else
    return constructionTemplate_->cloneMutableLabeledTree();
#endif
}

htd::IMutableLabeledTree * htd::LabeledTreeFactory::getLabeledTree(const htd::ILabeledTree & original)
{
    htd::IMutableLabeledTree * ret = htd::LabeledTreeFactory::getLabeledTree();

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    *ret = original;
#else
    ret->assign(original);
#endif

    return ret;
}

void htd::LabeledTreeFactory::setConstructionTemplate(htd::IMutableLabeledTree * original)
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

htd::IMutableLabeledTree & htd::LabeledTreeFactory::accessMutableLabeledTree(htd::ILabeledTree & original)
{
    return *(dynamic_cast<htd::IMutableLabeledTree *>(&original));
}

const htd::IMutableLabeledTree & htd::LabeledTreeFactory::accessMutableLabeledTree(const htd::ILabeledTree & original)
{
    return *(dynamic_cast<const htd::IMutableLabeledTree *>(&original));
}

#endif /* HTD_HTD_LABELEDTREEFACTORY_CPP */
