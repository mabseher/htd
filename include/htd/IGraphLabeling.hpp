/*
 * File:   IGraphLabeling.hpp
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

#ifndef HTD_HTD_IGRAPHLABELING_HPP
#define	HTD_HTD_IGRAPHLABELING_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>

namespace htd
{
    class IGraphLabeling
    {
        public:
            virtual ~IGraphLabeling() = 0;

            virtual std::size_t vertexLabelCount() const = 0;

            virtual std::size_t edgeLabelCount() const = 0;

            virtual bool isLabeledVertex(htd::vertex_t vertex) const = 0;

            virtual bool isLabeledEdge(htd::id_t edgeId) const = 0;

            virtual const htd::ILabel & vertexLabel(htd::vertex_t vertex) const = 0;

            virtual const htd::ILabel & edgeLabel(htd::id_t id) const = 0;

            virtual void setVertexLabel(htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void setEdgeLabel(htd::id_t edgeId, htd::ILabel * label) = 0;

            virtual void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            virtual htd::ILabel * transferVertexLabel(htd::vertex_t vertex) = 0;

            virtual htd::ILabel * transferEdgeLabel(htd::id_t edgeId) = 0;

            virtual void removeVertexLabel(htd::vertex_t vertex) = 0;

            virtual void removeEdgeLabel(htd::id_t edgeId) = 0;

            virtual IGraphLabeling * clone(void) const = 0;

            virtual void clear(void) = 0;
    };
    
    inline htd::IGraphLabeling::~IGraphLabeling() { }
}

#endif /* HTD_HTD_IGRAPHLABELING_HPP */
