/* 
 * File:   HypertreeDecomposition.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_HPP
#define	HTD_HTD_HYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>

namespace htd
{
    /**
     *  Default implementation of the IMutableHypertreeDecomposition interface.
     */
    class HypertreeDecomposition : public htd::TreeDecomposition, public virtual htd::IMutableHypertreeDecomposition
    {
        public:
            /**
             *  Constructor for a hypertree decomposition.
             */
            HypertreeDecomposition(void);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original tree decomposition.
             */
            HypertreeDecomposition(const htd::ITreeDecomposition & original);

            /**
             *  Copy constructor for a hypertree decomposition.
             *
             *  @param[in] original  The original hypertree decomposition.
             */
            HypertreeDecomposition(const htd::IHypertreeDecomposition & original);

            ~HypertreeDecomposition();

            htd::ConstCollection<htd::Hyperedge> coveringEdges(htd::vertex_t vertex) const HTD_OVERRIDE;

            void setCoveringEdges(htd::vertex_t vertex, const htd::hyperedge_container & content) HTD_OVERRIDE;

            void setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content) HTD_OVERRIDE;

            HypertreeDecomposition * clone(void) const HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::ITree & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::ILabeledTree & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::ITreeDecomposition & original) HTD_OVERRIDE;

            HypertreeDecomposition & operator=(const htd::IHypertreeDecomposition & original) HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_HPP */
