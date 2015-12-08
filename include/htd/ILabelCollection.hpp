/*
 * File:   ILabelCollection.hpp
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

#ifndef HTD_HTD_ILABELCOLLECTION_HPP
#define	HTD_HTD_ILABELCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/ILabel.hpp>

namespace htd
{
    class ILabelCollection
    {
        public:
            virtual ~ILabelCollection() = 0;

            virtual std::size_t labelCount(void) const = 0;

            virtual htd::Collection<std::string> labelNames(void) const = 0;

            virtual const std::string & labelName(htd::index_t index) const = 0;

            virtual htd::ILabel & label(const std::string & labelName) = 0;

            virtual const htd::ILabel & label(const std::string & labelName) const = 0;

            virtual void setLabel(const std::string & labelName, htd::ILabel * label) = 0;

            virtual void removeLabel(const std::string & labelName) = 0;

            virtual ILabelCollection * clone(void) const = 0;
    };

    inline htd::ILabelCollection::~ILabelCollection() { }
}

#endif /* HTD_HTD_ILABELCOLLECTION_HPP */
