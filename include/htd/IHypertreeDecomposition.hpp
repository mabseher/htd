/* 
 * File:   IHypertreeDecomposition.hpp
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

#ifndef HTD_HTD_IHYPERTREEDECOMPOSITION_HPP
#define	HTD_HTD_IHYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    class IHypertreeDecomposition : public virtual htd::ITreeDecomposition
    {
        public:
            /**
             *  Constant for the identifier of the edge label.
             */
            static constexpr const char * EDGE_LABEL_IDENTIFIER = "Edges";

            virtual ~IHypertreeDecomposition() = 0;

            virtual const htd::Collection<htd::hyperedge_t> edgeLabel(htd::vertex_t vertex) const = 0;

            virtual void setEdgeLabel(htd::vertex_t vertex, const htd::hyperedge_container & content) = 0;

            virtual void setEdgeLabel(htd::vertex_t vertex, const htd::Collection<htd::hyperedge_t> & content) = 0;

            virtual IHypertreeDecomposition * clone(void) const = 0;
    };

    inline htd::IHypertreeDecomposition::~IHypertreeDecomposition() { }
}

#endif /* HTD_HTD_IHYPERTREEDECOMPOSITION_HPP */
