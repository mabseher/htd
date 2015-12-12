/*
 * File:   GraphLabeling.hpp
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

#ifndef HTD_HTD_GRAPHLABELING_HPP
#define	HTD_HTD_GRAPHLABELING_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabel.hpp>

#include <unordered_map>

namespace htd
{
    class GraphLabeling : public virtual htd::IGraphLabeling
    {
        public:
            GraphLabeling(void);

            ~GraphLabeling();

            std::size_t vertexLabelCount(void) const HTD_OVERRIDE;

            std::size_t hyperedgeLabelCount(void) const HTD_OVERRIDE;

            bool hasLabel(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool hasLabel(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            const htd::ILabel & label(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & label(const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            void setLabel(htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setLabel(const htd::hyperedge_t & edge, htd::ILabel * label) HTD_OVERRIDE;

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            void removeLabel(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeLabel(const htd::hyperedge_t & edge) HTD_OVERRIDE;

            void clear(void) HTD_OVERRIDE;

            GraphLabeling * clone(void) const HTD_OVERRIDE;

        private:
            std::unordered_map<htd::vertex_t, htd::ILabel *> vertexLabels_;

            std::unordered_map<htd::hyperedge_t, htd::ILabel *> hyperedgeLabels_;
    };
}

#endif /* HTD_HTD_GRAPHLABELING_HPP */
