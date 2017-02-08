/*
 * File:   ILabelingCollection.hpp
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

#ifndef HTD_HTD_ILABELINGCOLLECTION_HPP
#define HTD_HTD_ILABELINGCOLLECTION_HPP

#include <htd/Globals.hpp>
#include <htd/Collection.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/Iterator.hpp>

namespace htd
{
    /**
     * Interface for classes which represent collections of label mappings.
     */
    class ILabelingCollection
    {
        public:
            virtual ~ILabelingCollection() = 0;

            /**
             *  Getter for the number of different label names.
             *
             *  @return The number of different label names.
             */
            virtual std::size_t labelCount(void) const = 0;

            /**
             *  Access the collection of all label names.
             *
             *  @return The collection of all label names sorted in ascending order.
             */
            virtual htd::ConstCollection<std::string> labelNames(void) const = 0;

            /**
             *  Access the label name at the specific position.
             *
             *  @param[in] index    The position of the label name.
             *
             *  @return The label name at the specific position.
             */
            virtual const std::string & labelNameAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a given string is the name of a labeling.
             *
             *  @param[in] labelName    The name of the labeling.
             *
             *  @return True if the given string is the name of a labeling, false otherwise.
             */
            virtual bool isLabelName(const std::string & labelName) const = 0;

            /**
             *  Access the labeling with the given name.
             *
             *  @param[in] labelName    The name of the labeling.
             *
             *  @return The labeling with the given name.
             */
            virtual htd::IGraphLabeling & labeling(const std::string & labelName) = 0;

            /**
             *  Access the labeling with the given name.
             *
             *  @param[in] labelName    The name of the labeling.
             *
             *  @return The labeling with the given name.
             */
            virtual const htd::IGraphLabeling & labeling(const std::string & labelName) const = 0;

            /**
             *  Set the labeling with the given name.
             *
             *  If a graph labeling with the same name already exists in the labeling collection,
             *  the existing labeling will be replaced and the memory of the previous labeling
             *  is freed.
             *
             *  @note When calling this method the control over the memory region of the new labeling is transferred to the
             *  labeling collection. Deleting the labeling outside the labeling collection or inserting the same labeling
             *  object with multiple names will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new labeling.
             *  @param[in] labeling     The new labeling.
             */
            virtual void setLabeling(const std::string & labelName, htd::IGraphLabeling * labeling) = 0;

            /**
             *  Remove the labeling with the given name.
             *
             *  @param[in] labelName    The name of the labeling which shall be removed.
             */
            virtual void removeLabeling(const std::string & labelName) = 0;

            /**
             *  Remove all labels associated with a given vertex.
             *
             *  @param[in] vertex   The vertex which's labels shall be removed.
             */
            virtual void removeVertexLabels(htd::vertex_t vertex) = 0;

            /**
             *  Remove all labels associated with a given edge.
             *
             *  @param[in] edgeId   The ID of the edge which's labels shall be removed.
             */
            virtual void removeEdgeLabels(htd::id_t edgeId) = 0;

            /**
             *  Swap the labels of two vertices.
             *
             *  @param[in] vertex1  The first vertex.
             *  @param[in] vertex2  The second vertex.
             */
            virtual void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] edgeId1  The ID of the first edge.
             *  @param[in] edgeId2  The ID of the second edge.
             */
            virtual void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            /**
             *  Create a new ILabelCollection object containing all labels for a given vertex.
             *
             *  @param[in] vertex   The vertex which's labels shall be returned.
             *
             *  @return A new ILabelCollection object containing all labels for the given vertex.
             */
            virtual htd::ILabelCollection * exportVertexLabelCollection(htd::vertex_t vertex) const = 0;

            /**
             *  Create a new ILabelCollection object containing all labels for a given edge.
             *
             *  @param[in] edgeId   The ID of the edge which's labels shall be returned.
             *
             *  @return A new ILabelCollection object containing all labels for the given edge.
             */
            virtual htd::ILabelCollection * exportEdgeLabelCollection(htd::id_t edgeId) const = 0;

            /**
             *  Clear the labeling collection at hand.
             */
            virtual void clear(void) = 0;

            /**
             *  Create a deep copy of the current labeling collection.
             *
             *  @return A new ILabelingCollection object identical to the current labeling collection.
             */
            virtual ILabelingCollection * clone(void) const = 0;

            /**
             *  Access the labeling with the given name.
             *
             *  @param[in] labelName    The name of the labeling.
             *
             *  @return The labeling with the given name.
             */
            virtual htd::IGraphLabeling & operator[](const std::string & labelName) = 0;

            /**
             *  Access the labeling with the given name.
             *
             *  @param[in] labelName    The name of the labeling.
             *
             *  @return The labeling with the given name.
             */
            virtual const htd::IGraphLabeling & operator[](const std::string & labelName) const = 0;

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            virtual htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) = 0;

            /**
             *  Getter for the iterator to the first element in the collection.
             *
             *  @return An iterator to the first element in the collection.
             */
            virtual const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> begin(void) const = 0;

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            virtual htd::Iterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) = 0;

            /**
             *  Getter for the iterator to the end of the collection.
             *
             *  @return An iterator to the end of the collection.
             */
            virtual const htd::ConstIterator<std::pair<const std::string, htd::IGraphLabeling *>> end(void) const = 0;
    };

    inline htd::ILabelingCollection::~ILabelingCollection() { }
}

#endif /* HTD_HTD_ILABELINGCOLLECTION_HPP */
