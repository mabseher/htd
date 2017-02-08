/*
 * File:   LabelingCollection.hpp
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

#ifndef HTD_HTD_LABELINGCOLLECTION_HPP
#define HTD_HTD_LABELINGCOLLECTION_HPP

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
    /**
     *  Default implementation of the ILabelingCollection interface.
     */
    class LabelingCollection : public virtual htd::ILabelingCollection
    {
        public:
            /**
             *  Constructor for a labeling collection.
             */
            HTD_API LabelingCollection(void);

            /**
             *  Copy constructor for a labeling collection.
             *
             *  @param[in] original The original labeling collection.
             */
            HTD_API LabelingCollection(const LabelingCollection & original);

            /**
             *  Copy constructor for a labeling collection.
             *
             *  @param[in] original The original labeling collection.
             */
            HTD_API LabelingCollection(const htd::ILabelingCollection & original);
            
            HTD_API virtual ~LabelingCollection();

            HTD_API std::size_t labelCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<std::string> labelNames(void) const HTD_OVERRIDE;

            HTD_API const std::string & labelNameAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isLabelName(const std::string & labelName) const HTD_OVERRIDE;

            HTD_API htd::IGraphLabeling & labeling(const std::string & labelName) HTD_OVERRIDE;

            HTD_API const htd::IGraphLabeling & labeling(const std::string & labelName) const HTD_OVERRIDE;

            HTD_API void setLabeling(const std::string & labelName, htd::IGraphLabeling * labeling) HTD_OVERRIDE;

            HTD_API void removeLabeling(const std::string & labelName) HTD_OVERRIDE;

            HTD_API void removeVertexLabels(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeEdgeLabels(htd::id_t edgeId) HTD_OVERRIDE;

            HTD_API void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            HTD_API void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            HTD_API htd::ILabelCollection * exportVertexLabelCollection(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ILabelCollection * exportEdgeLabelCollection(htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API void clear(void) HTD_OVERRIDE;

            HTD_API LabelingCollection * clone(void) const HTD_OVERRIDE;

            HTD_API htd::IGraphLabeling & operator[](const std::string & labelName) HTD_OVERRIDE;

            HTD_API const htd::IGraphLabeling & operator[](const std::string & labelName) const HTD_OVERRIDE;

            HTD_API htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) HTD_OVERRIDE;

            HTD_API const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) const HTD_OVERRIDE;

            HTD_API htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) HTD_OVERRIDE;

            HTD_API const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) const HTD_OVERRIDE;

        private:
            std::vector<std::string> labelNames_;

            std::unordered_map<std::string, htd::IGraphLabeling *> content_;
    };
}

#endif /* HTD_HTD_LABELINGCOLLECTION_HPP */
