/* 
 * File:   IMutableLabeledPath.hpp
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

#ifndef HTD_HTD_IMUTABLELABELEDPATH_HPP
#define HTD_HTD_IMUTABLELABELEDPATH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutablePath.hpp>
#include <htd/ILabeledPath.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable labeled paths.
     */
    class IMutableLabeledPath : public virtual htd::ILabeledPath, public virtual htd::IMutablePath
    {
        public:
#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            using htd::IMutablePath::assign;
#endif

            /**
             *  Destructor for an IMutableLabeledPath object.
             */
            virtual ~IMutableLabeledPath() = 0;

            /**
             *  Set the label associated with the given vertex.
             *
             *  If the vertex is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  path. Deleting the label outside the path or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] vertex       The vertex to be labeled.
             *  @param[in] label        The new label.
             */
            virtual void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            /**
             *  Set the label associated with the given edge.
             *
             *  If the edge is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  path. Deleting the label outside the path or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] edgeId       The ID of the edge to be labeled.
             *  @param[in] label        The new label.
             */
            virtual void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) = 0;

            /**
             *  Remove the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] vertex       The vertex.
             */
            virtual void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            /**
             *  Remove the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] edgeId       The ID of the edge.
             */
            virtual void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

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
             *  Swap the labels of two vertices.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] vertex1      The first vertex.
             *  @param[in] vertex2      The second vertex.
             */
            virtual void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] edgeId1      The ID of the first edge.
             *  @param[in] edgeId2      The ID of the second edge.
             */
            virtual void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            /**
             *  Transfer the control over a vertex label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] vertex       The vertex which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the vertex is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the vertex label.
             */
            virtual htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            /**
             *  Transfer the control over an edge label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] edgeId       The ID of the edge which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the edge is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the edge label.
             */
            virtual htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current mutable labeled path.
             *
             *  @return A new IMutableLabeledPath object identical to the current mutable labeled path.
             */
            virtual IMutableLabeledPath * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current mutable labeled path.
             *
             *  @return A new IMutableLabeledPath object identical to the current mutable labeled path.
             */
            virtual IMutableLabeledPath * cloneMutableLabeledPath(void) const = 0;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a mutable labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            virtual IMutableLabeledPath & operator=(const htd::ILabeledPath & original) = 0;
#else
            /**
             *  Copy assignment operator for a mutable labeled path.
             *
             *  @param[in] original  The original labeled path.
             */
            virtual void assign(const htd::ILabeledPath & original) = 0;
#endif
    };

    inline htd::IMutableLabeledPath::~IMutableLabeledPath() { }
}

#endif /* HTD_HTD_IMUTABLELABELEDPATH_HPP */
