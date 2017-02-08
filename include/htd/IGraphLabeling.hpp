/*
 * File:   IGraphLabeling.hpp
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

#ifndef HTD_HTD_IGRAPHLABELING_HPP
#define HTD_HTD_IGRAPHLABELING_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>

namespace htd
{
    /**
     * Interface for graph labelings providing uni-directional mappings between vertices (and/or edges) and labels.
     */
    class IGraphLabeling
    {
        public:
            virtual ~IGraphLabeling() = 0;

            /**
             *  Getter for the number of different vertex labels stored in the graph labeling.
             *
             *  @return The number of different vertex labels stored in the graph labeling.
             */
            virtual std::size_t vertexLabelCount() const = 0;

            /**
             *  Getter for the number of different edge labels stored in the graph labeling.
             *
             *  @return The number of different edge labels stored in the graph labeling.
             */
            virtual std::size_t edgeLabelCount() const = 0;

            /**
             *  Check whether a given vertex has a label.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex has a label, false otherwise.
             */
            virtual bool isLabeledVertex(htd::vertex_t vertex) const = 0;

            /**
             *  Check whether a given edge has a label.
             *
             *  @param[in] edgeId   The ID of the edge.
             *
             *  @return True if the given edge has a label, false otherwise.
             */
            virtual bool isLabeledEdge(htd::id_t edgeId) const = 0;

            /**
             *  Access the label associated with the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The label associated with the given vertex.
             */
            virtual const htd::ILabel & vertexLabel(htd::vertex_t vertex) const = 0;

            /**
             *  Access the label associated with the given edge.
             *
             *  @param[in] edgeId   The ID of the edge.
             *
             *  @return The label associated with the given edge.
             */
            virtual const htd::ILabel & edgeLabel(htd::id_t edgeId) const = 0;

            /**
             *  Set the label associated with the given vertex.
             *
             *  If the vertex is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred
             *  to the graph labeling. Deleting the label outside the graph labeling or assigning the same label
             *  object to multiple vertices or edges will lead to undefined behavior.
             *
             *  @param[in] vertex   The vertex to be labeled.
             *  @param[in] label    The new label.
             */
            virtual void setVertexLabel(htd::vertex_t vertex, htd::ILabel * label) = 0;

            /**
             *  Set the label associated with the given edge.
             *
             *  If the edge is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred
             *  to the graph labeling. Deleting the label outside the graph labeling or assigning the same label
             *  object to multiple vertices or edges will lead to undefined behavior.
             *
             *  @param[in] edgeId   The ID of the edge to be labeled.
             *  @param[in] label    The new label.
             */
            virtual void setEdgeLabel(htd::id_t edgeId, htd::ILabel * label) = 0;

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
             *  Transfer the control over a vertex label to a new owner.
             *
             *  @param[in] vertex   The vertex which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the vertex is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the vertex label.
             */
            virtual htd::ILabel * transferVertexLabel(htd::vertex_t vertex) = 0;

            /**
             *  Transfer the control over an edge label to a new owner.
             *
             *  @param[in] edgeId   The ID of the edge which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the edge is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the edge label.
             */
            virtual htd::ILabel * transferEdgeLabel(htd::id_t edgeId) = 0;

            /**
             *  Remove the label associated with the given vertex.
             *
             *  @param[in] vertex   The vertex.
             */
            virtual void removeVertexLabel(htd::vertex_t vertex) = 0;

            /**
             *  Remove the label associated with the given edge.
             *
             *  @param[in] edgeId   The ID of the edge.
             */
            virtual void removeEdgeLabel(htd::id_t edgeId) = 0;

            /**
             *  Create a deep copy of the current graph labeling.
             *
             *  @return A new IGraphLabeling object identical to the current graph labeling.
             */
            virtual IGraphLabeling * clone(void) const = 0;

            /**
             *  Remove all labels from the current labeling.
             */
            virtual void clear(void) = 0;
    };
    
    inline htd::IGraphLabeling::~IGraphLabeling() { }
}

#endif /* HTD_HTD_IGRAPHLABELING_HPP */
