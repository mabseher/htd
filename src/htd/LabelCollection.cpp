/*
 * File:   LabelCollection.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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
#define HTD_HTD_LABELCOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabelCollection.hpp>

#include <algorithm>
#include <stdexcept>

htd::LabelCollection::LabelCollection(void) : labelNames_(), content_()
{
 
}

htd::LabelCollection::LabelCollection(const htd::LabelCollection & original) : labelNames_(), content_()
{
    for (const std::string & labelName : original.labelNames())
    {
        labelNames_.push_back(labelName);

        content_[labelName] = original.label(labelName).clone();
    }
}

htd::LabelCollection::LabelCollection(const htd::ILabelCollection & original) : labelNames_(), content_()
{
    for (const std::string & labelName : original.labelNames())
    {
        labelNames_.push_back(labelName);

        content_[labelName] = original.label(labelName).clone();
    }
}

htd::LabelCollection::~LabelCollection()
{
    for (auto & storedLabel : content_)
    {
        if (storedLabel.second != nullptr)
        {
            delete storedLabel.second;
        }
    }

    content_.clear();
}

std::size_t htd::LabelCollection::labelCount(void) const
{
    return labelNames_.size();
}

htd::ConstCollection<std::string> htd::LabelCollection::labelNames(void) const
{
    return htd::ConstCollection<std::string>::getInstance(labelNames_);
}

const std::string & htd::LabelCollection::labelNameAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < labelNames_.size())

    return labelNames_.at(index);
}

htd::ILabel & htd::LabelCollection::label(const std::string & labelName)
{
    auto position = content_.find(labelName);

    HTD_ASSERT(position != content_.end())

    return *(position->second);
}

const htd::ILabel & htd::LabelCollection::label(const std::string & labelName) const
{
    auto position = content_.find(labelName);

    HTD_ASSERT(position != content_.end())

    return *(position->second);
}

void htd::LabelCollection::setLabel(const std::string & labelName, htd::ILabel * label)
{
    auto oldPosition = content_.find(labelName);

    if (oldPosition != content_.end())
    {
        delete oldPosition->second;

        content_.erase(oldPosition);
    }

    auto position = std::lower_bound(labelNames_.begin(), labelNames_.end(), labelName);

    if (position == labelNames_.end() || *position != labelName)
    {
        labelNames_.insert(position, labelName);
    }

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
