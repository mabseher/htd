/*
 * File:   ILabelingCollection.hpp
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

#ifndef HTD_HTD_ILABELINGCOLLECTION_HPP
#define	HTD_HTD_ILABELINGCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>

namespace htd
{
    class ILabelingCollection
    {
        public:
            virtual ~ILabelingCollection() = 0;

            virtual std::size_t labelCount(void) const = 0;

            virtual void getLabelNames(std::vector<std::string> & output) const = 0;

            virtual std::string labelName(htd::index_t index) const = 0;

            virtual const htd::ILabel * label(std::string labelName, htd::vertex_t vertex) const = 0;

            virtual void setLabel(std::string labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void removeLabel(std::string labelName, htd::vertex_t vertex) = 0;

            virtual void setLabeling(std::string labelName, htd::IGraphLabeling * labeling) = 0;

            virtual void removeLabeling(std::string labelName) = 0;

            virtual htd::ILabelCollection * exportLabelCollection(htd::vertex_t vertex) const = 0;

            virtual ILabelingCollection * clone(void) const = 0;
    };

    inline htd::ILabelingCollection::~ILabelingCollection() { }
}

#endif /* HTD_HTD_ILABELINGCOLLECTION_HPP */
