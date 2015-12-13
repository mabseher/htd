/* 
 * File:   HypertreeDecomposition.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_HPP
#define	HTD_HTD_HYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/IGraphLabeling.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    class HypertreeDecomposition : public TreeDecomposition, public virtual htd::IMutableHypertreeDecomposition
    {
        public:
            HypertreeDecomposition(void);
            
            HypertreeDecomposition(const htd::ILabeledTree & original);

            HypertreeDecomposition(const htd::HypertreeDecomposition & original);

            ~HypertreeDecomposition();

            void getEdgeLabel(htd::vertex_t vertex, htd::hyperedge_container & output) const HTD_OVERRIDE;

            void setEdgeLabel(htd::vertex_t vertex, const htd::hyperedge_container & content) HTD_OVERRIDE;

            void setEdgeLabel(htd::vertex_t vertex, const htd::Collection<htd::hyperedge_t> & content) HTD_OVERRIDE;

            HypertreeDecomposition * clone(void) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_HPP */
