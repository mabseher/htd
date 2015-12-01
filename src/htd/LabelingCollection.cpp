/*
 * File:   LabelingCollection.cpp
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

#ifndef HTD_HTD_LABELINGCOLLECTION_CPP
#define	HTD_HTD_LABELINGCOLLECTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/ILabel.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/LabelCollection.hpp>

#include <algorithm>
#include <stdexcept>

htd::LabelingCollection::LabelingCollection(void) : labelNames_(), content_()
{

}
            
htd::LabelingCollection::~LabelingCollection()
{

}

std::size_t htd::LabelingCollection::labelCount(void) const
{
    return content_.size();
}

void htd::LabelingCollection::getLabelNames(std::vector<std::string> & output) const
{
    std::copy(labelNames_.begin(), labelNames_.end(), std::back_inserter(output));
}

std::string htd::LabelingCollection::labelName(htd::index_t index) const
{
    if (index >= labelNames_.size())
    {
        throw std::out_of_range("std::string htd::LabelingCollection::labelName(htd::index_t) const");
    }

    return labelNames_.at(index);
}

const htd::ILabel * htd::LabelingCollection::label(std::string labelName, htd::vertex_t vertex) const
{
    if (content_.find(labelName) == content_.end())
    {
        throw std::out_of_range("const htd::ILabel * const htd::LabelingCollection::label(std::string) const");
    }

    return content_.at(labelName)->label(vertex);
}

void htd::LabelingCollection::setLabel(std::string labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    auto position = content_.find(labelName);

    if (position == content_.end())
    {
        content_[labelName] = new GraphLabeling();
    }

    auto labeling = dynamic_cast<htd::IGraphLabeling *>(content_[labelName]);

    labeling->setLabel(vertex, label);
}

void htd::LabelingCollection::removeLabel(std::string labelName, htd::vertex_t vertex)
{
    auto position = content_.find(labelName);

    if (position != content_.end())
    {
        position->second->removeLabel(vertex);
    }
}

void htd::LabelingCollection::setLabeling(std::string labelName, htd::IGraphLabeling * labeling)
{
    auto position = content_.find(labelName);

    if (position == content_.end())
    {
        content_[labelName] = labeling;
    }
}

void htd::LabelingCollection::removeLabeling(std::string labelName)
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

htd::ILabelCollection * htd::LabelingCollection::exportLabelCollection(htd::vertex_t vertex) const
{
    htd::ILabelCollection * ret = new LabelCollection();

    for (std::string labelName : labelNames_)
    {
        IGraphLabeling * labeling = content_.at(labelName);

        if (labeling != nullptr && labeling->hasLabel(vertex))
        {
            ret->setLabel(labelName, labeling->label(vertex)->clone());
        }
    }

    return ret;
}

htd::LabelingCollection * htd::LabelingCollection::clone(void) const
{
    htd::LabelingCollection * ret = new htd::LabelingCollection();

    for (std::string labelName : labelNames_)
    {
        ret->setLabeling(labelName, content_.at(labelName)->clone());
    }

    return ret;
}

#endif /* HTD_HTD_LABELINGCOLLECTION_CPP */
