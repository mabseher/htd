/* 
 * File:   GraphDecomposition.hpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITION_HPP
#define	HTD_HTD_GRAPHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutableGraphDecomposition.hpp>
#include <htd/LabeledGraph.hpp>

namespace htd
{
    class GraphDecomposition : public htd::LabeledGraph, public virtual htd::IMutableGraphDecomposition
    {
        public:
            GraphDecomposition(void);

            GraphDecomposition(const GraphDecomposition & original);

            GraphDecomposition(const htd::IGraph & original);

            GraphDecomposition(const htd::ILabeledGraph & original);

            GraphDecomposition(const htd::IGraphDecomposition & original);
            
            ~GraphDecomposition();

            std::size_t bagSize(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> bagContent(htd::vertex_t vertex) const HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content) HTD_OVERRIDE;

            void setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content) HTD_OVERRIDE;

            std::size_t minimumBagSize(void) const HTD_OVERRIDE;

            std::size_t maximumBagSize(void) const HTD_OVERRIDE;

            GraphDecomposition * clone(void) const HTD_OVERRIDE;

            GraphDecomposition & operator=(const GraphDecomposition & original);

            GraphDecomposition & operator=(const htd::IGraph & original) HTD_OVERRIDE;

            GraphDecomposition & operator=(const htd::ILabeledGraph & original) HTD_OVERRIDE;

            GraphDecomposition & operator=(const htd::IGraphDecomposition & original) HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_GRAPHDECOMPOSITION_HPP */
