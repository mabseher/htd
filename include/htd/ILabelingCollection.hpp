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
#include <htd/Collection.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/Iterator.hpp>

namespace htd
{
    class ILabelingCollection
    {
        public:
            virtual ~ILabelingCollection() = 0;

            virtual std::size_t labelCount(void) const = 0;

            virtual const htd::Collection<std::string> labelNames(void) const = 0;

            virtual const std::string & labelName(htd::index_t index) const = 0;

            virtual bool isLabelingName(const std::string & labelName) const = 0;

            virtual htd::IGraphLabeling & labeling(const std::string & labelName) = 0;

            virtual const htd::IGraphLabeling & labeling(const std::string & labelName) const = 0;

            virtual void setLabeling(const std::string & labelName, htd::IGraphLabeling * labeling) = 0;

            virtual void removeLabeling(const std::string & labelName) = 0;

            virtual void removeLabels(htd::vertex_t vertex) = 0;

            virtual void removeLabels(const htd::hyperedge_t & edge) = 0;

            virtual void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) = 0;

            virtual htd::ILabelCollection * exportLabelCollection(htd::vertex_t vertex) const = 0;

            virtual htd::ILabelCollection * exportLabelCollection(const htd::hyperedge_t & edge) const = 0;

            virtual ILabelingCollection * clone(void) const = 0;

            virtual htd::IGraphLabeling & operator[](const std::string & labelName) = 0;

            virtual const htd::IGraphLabeling & operator[](const std::string & labelName) const = 0;

            virtual htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) = 0;

            virtual const htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) const = 0;

            virtual htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) = 0;

            virtual const htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) const = 0;
    };

    inline htd::ILabelingCollection::~ILabelingCollection() { }
}

#endif /* HTD_HTD_ILABELINGCOLLECTION_HPP */
