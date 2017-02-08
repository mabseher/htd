/* 
 * File:   IHypertreeDecomposition.hpp
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

#ifndef HTD_HTD_IHYPERTREEDECOMPOSITION_HPP
#define HTD_HTD_IHYPERTREEDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    /**
     * Interface for classes which represent hypertree decompositions.
     */
    class IHypertreeDecomposition : public virtual htd::ITreeDecomposition
    {
        public:
            /**
             *  Constant for the identifier of the edge label.
             */
            static constexpr const char * EDGE_LABEL_IDENTIFIER = "Edges";

            virtual ~IHypertreeDecomposition() = 0;

            /**
             *  Access the hyperedges covering the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the covering edges shall be returned.
             *
             *  @return A vector of hyperedges covering the bag content of the specific vertex.
             */
            virtual const std::vector<htd::Hyperedge> & coveringEdges(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the minimum amount of hyperedges required to cover a bag of the decomposition.
             *
             *  @return The minimum amount of hyperedges required to cover a bag of the decomposition.
             */
            virtual std::size_t minimumCoveringEdgeAmount(void) const = 0;

            /**
             *  Getter for the maximum amount of hyperedges required to cover a bag of the decomposition.
             *
             *  @return The maximum amount of hyperedges required to cover a bag of the decomposition.
             */
            virtual std::size_t maximumCoveringEdgeAmount(void) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current hypertree decomposition.
             *
             *  @return A new IHypertreeDecomposition object identical to the current hypertree decomposition.
             */
            virtual IHypertreeDecomposition * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current hypertree decomposition.
             *
             *  @return A new IHypertreeDecomposition object identical to the current hypertree decomposition.
             */
            virtual IHypertreeDecomposition * cloneHypertreeDecomposition(void) const = 0;
#endif
    };

    inline htd::IHypertreeDecomposition::~IHypertreeDecomposition() { }
}

#endif /* HTD_HTD_IHYPERTREEDECOMPOSITION_HPP */
