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
//TODO
//#include <htd/LabeledPath.hpp>

#include <stdexcept>

htd::LabeledPathFactory::LabeledPathFactory(void)
{
    constructionTemplate_ = nullptr; //new htd::LabeledPath();
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
    return constructionTemplate_->clone();
}

//TODO Use construction template!
htd::IMutableLabeledPath * htd::LabeledPathFactory::getLabeledPath(const htd::ILabeledPath & original)
{
    htd::IMutableLabeledPath * ret = nullptr; //new htd::LabeledPath(original); //TODO constructionTemplate_->clone();

    //TODO Copy decomposition content!
    HTD_UNUSED(original)

    return ret;
}

void htd::LabeledPathFactory::setConstructionTemplate(htd::IMutableLabeledPath * original)
{
    if (original == nullptr)
    {
        throw std::logic_error("void htd::LabeledPathFactory::setConstructionTemplate(htd::IMutableLabeledPath *)");
    }

    if (original->vertexCount() > 0)
    {
        throw std::logic_error("void htd::LabeledPathFactory::setConstructionTemplate(htd::IMutableLabeledPath *)");
    }

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
