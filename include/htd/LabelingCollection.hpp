/*
 * File:   LabelingCollection.hpp
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

#ifndef HTD_HTD_LABELINGCOLLECTION_HPP
#define	HTD_HTD_LABELINGCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/Iterator.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace htd
{
    class LabelingCollection : public virtual htd::ILabelingCollection
    {
        public:
            LabelingCollection(void);

            LabelingCollection(const LabelingCollection & original);

            LabelingCollection(const htd::ILabelingCollection & original);
            
            ~LabelingCollection();

            std::size_t labelCount(void) const HTD_OVERRIDE;

            const htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE;

            bool isLabelingName(const std::string & labelName) const HTD_OVERRIDE;

            htd::IGraphLabeling & labeling(const std::string & labelName) HTD_OVERRIDE;

            const htd::IGraphLabeling & labeling(const std::string & labelName) const HTD_OVERRIDE;

            void setLabeling(const std::string & labelName, htd::IGraphLabeling * labeling) HTD_OVERRIDE;

            void removeLabeling(const std::string & labelName) HTD_OVERRIDE;

            void removeLabels(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeLabels(const htd::hyperedge_t & edge) HTD_OVERRIDE;

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            htd::ILabelCollection * exportLabelCollection(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ILabelCollection * exportLabelCollection(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            LabelingCollection * clone(void) const HTD_OVERRIDE;

            htd::IGraphLabeling & operator[](const std::string & labelName) HTD_OVERRIDE;

            const htd::IGraphLabeling & operator[](const std::string & labelName) const HTD_OVERRIDE;

            htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) HTD_OVERRIDE;

            const htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) const HTD_OVERRIDE;

            htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) HTD_OVERRIDE;

            const htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) const HTD_OVERRIDE;

        private:
            std::vector<std::string> labelNames_;

            std::unordered_map<std::string, htd::IGraphLabeling *> content_;
    };
}

#endif /* HTD_HTD_LABELINGCOLLECTION_HPP */
