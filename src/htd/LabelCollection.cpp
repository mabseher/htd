/*
 * File:   LabelCollection.cpp
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

#ifndef HTD_HTD_LABELCOLLECTION_CPP
#define	HTD_HTD_LABELCOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/LabelCollection.hpp>
#include <htd/ILabel.hpp>

#include <algorithm>
#include <stdexcept>

htd::LabelCollection::LabelCollection(void) : labelNames_(), content_()
{
 
}

htd::LabelCollection::~LabelCollection()
{
 
}

std::size_t htd::LabelCollection::labelCount(void) const
{
    return labelNames_.size();
}

htd::Collection<std::string> htd::LabelCollection::labelNames(void) const
{
    return htd::Collection<std::string>(labelNames_);
}

const std::string & htd::LabelCollection::labelName(htd::index_t index) const
{
    if (index >= labelNames_.size())
    {
        throw std::out_of_range("const std::string & htd::LabelCollection::labelName(htd::index_t) const");
    }

    return labelNames_.at(index);
}

htd::ILabel & htd::LabelCollection::label(const std::string & labelName)
{
    if (content_.find(labelName) == content_.end())
    {
        throw std::out_of_range("htd::ILabel & htd::LabelCollection::label(const std::string &)");
    }

    return *(content_.at(labelName));
}

const htd::ILabel & htd::LabelCollection::label(const std::string & labelName) const
{
    if (content_.find(labelName) == content_.end())
    {
        throw std::out_of_range("const htd::ILabel & htd::LabelCollection::label(const std::string &) const");
    }

    return *(content_.at(labelName));
}

void htd::LabelCollection::setLabel(const std::string & labelName, htd::ILabel * label)
{
    if (content_.find(labelName) != content_.end())
    {
        throw std::out_of_range("void htd::LabelCollection::setLabel(const std::string &, htd::ILabel *)");
    }

    auto position = std::lower_bound(labelNames_.begin(), labelNames_.end(), labelName);

    labelNames_.insert(position, labelName);

    content_[labelName] = label;
}

void htd::LabelCollection::removeLabel(const std::string & labelName)
{
    auto position = content_.find(labelName);

    if (position != content_.end())
    {
        delete position->second;

        content_.erase(position);

        auto position2 = std::find(labelNames_.begin(), labelNames_.end(), labelName);

        labelNames_.erase(position2);
    }
}

htd::LabelCollection * htd::LabelCollection::clone(void) const
{
    htd::LabelCollection * ret = new htd::LabelCollection();

    for (const std::string & labelName : labelNames_)
    {
        ret->setLabel(labelName, content_.at(labelName)->clone());
    }

    return ret;
}

#endif /* HTD_HTD_LABELCOLLECTION_CPP */
