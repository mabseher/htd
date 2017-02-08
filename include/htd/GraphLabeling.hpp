/*
 * File:   GraphLabeling.hpp
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

#ifndef HTD_HTD_GRAPHLABELING_HPP
#define HTD_HTD_GRAPHLABELING_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabel.hpp>

#include <unordered_map>

namespace htd
{
    /**
     *  Default implementation of the IGraphLabeling interface.
     */
    class GraphLabeling : public htd::IGraphLabeling
    {
        public:
            HTD_API GraphLabeling(void);

            HTD_API virtual ~GraphLabeling();

            HTD_API std::size_t vertexLabelCount(void) const HTD_OVERRIDE;

            HTD_API std::size_t edgeLabelCount(void) const HTD_OVERRIDE;

            HTD_API bool isLabeledVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API bool isLabeledEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API const htd::ILabel & vertexLabel(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API const htd::ILabel & edgeLabel(htd::id_t edgeId) const HTD_OVERRIDE;

            HTD_API void setVertexLabel(htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            HTD_API void setEdgeLabel(htd::id_t edgeId, htd::ILabel * label) HTD_OVERRIDE;

            HTD_API void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            HTD_API void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            HTD_API htd::ILabel * transferVertexLabel(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API htd::ILabel * transferEdgeLabel(htd::id_t edgeId) HTD_OVERRIDE;

            HTD_API void removeVertexLabel(htd::vertex_t vertex) HTD_OVERRIDE;

            HTD_API void removeEdgeLabel(htd::id_t edgeId) HTD_OVERRIDE;

            HTD_API GraphLabeling * clone(void) const HTD_OVERRIDE;

            HTD_API void clear(void) HTD_OVERRIDE;

        private:
            std::unordered_map<htd::id_t, htd::ILabel *> vertexLabels_;

            std::unordered_map<htd::id_t, htd::ILabel *> edgeLabels_;
    };
}

#endif /* HTD_HTD_GRAPHLABELING_HPP */
