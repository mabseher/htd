/*
 * File:   IBidirectionalGraphLabeling.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP
#define	HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP

#include <htd/Globals.hpp>

#include <htd/IGraphLabeling.hpp>

#include <utility>

namespace htd
{
    class IBidirectionalGraphLabeling : public htd::IGraphLabeling
    {
        public:
            virtual ~IBidirectionalGraphLabeling() = 0;

            virtual std::pair<htd::id_t, bool> insertVertex(htd::ILabel * label, const std::function<htd::vertex_t(void)> & vertexCreationFunction) = 0;

            /**
             *  Check whether a given label is indeed the label of a known vertex.
             *
             *  @param[in] label    The label to test.
             *
             *  @return True if the given label is indeed the label of a known vertex, false otherwise.
             */
            virtual bool isVertexLabel(const htd::ILabel & label) const = 0;

            /**
             *  Check whether a given label is indeed the label of a known edge.
             *
             *  @param[in] label    The label to test.
             *
             *  @return True if the given label is indeed the label of a known edge, false otherwise.
             */
            virtual bool isEdgeLabel(const htd::ILabel & label) const = 0;

            /**
             *  Access the vertex with the given label.
             *
             *  @param[in] label    The label of the vertex which shall be returned.
             *
             *  @return The vertex with the given label.
             */
            virtual htd::vertex_t lookupVertex(const htd::ILabel & label) const = 0;

            /**
             *  Access the ID of the edge with the given label.
             *
             *  @param[in] label    The label of the edge which shall be returned.
             *
             *  @return The ID of the edge with the given label.
             */
            virtual htd::id_t lookupEdge(const htd::ILabel & label) const = 0;

            /**
             *  Create a deep copy the current bi-directional graph labeling.
             *
             *  @return A new IBidirectionalGraphLabeling object identical to the current bi-directional graph labeling.
             */
            virtual IBidirectionalGraphLabeling * clone(void) const = 0;
    };
    
    inline htd::IBidirectionalGraphLabeling::~IBidirectionalGraphLabeling() { }
}

#endif /* HTD_HTD_IBIDIRECTIONALGRAPHLABELING_HPP */
