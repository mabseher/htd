/* 
 * File:   IGraphDecomposition.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITION_HPP
#define HTD_HTD_IGRAPHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabeledMultiHypergraph.hpp>
#include <htd/FilteredHyperedgeCollection.hpp>

#include <vector>

namespace htd
{
    /**
     * Interface for classes which represent graph decompositions.
     */
    class IGraphDecomposition : public virtual htd::ILabeledMultiHypergraph
    {
        public:
            virtual ~IGraphDecomposition() = 0;

            /**
             *  Getter for the bag size of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the bag size shall be returned.
             *
             *  @return The bag size of the specific vertex.
             */
            virtual std::size_t bagSize(htd::vertex_t vertex) const = 0;

            /**
             *  Access the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the bag content shall be returned.
             *
             *  @return The bag content of the specific vertex.
             */
            virtual const std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) const = 0;

            /**
             *  Access the hyperedges induced by the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the induced hyperedges shall be returned.
             *
             *  @return The collection of hyperedges induced by the bag content of the specific vertex.
             */
            virtual const htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) const = 0;

            /**
             *  Getter for the minimum bag size of the decomposition.
             *
             *  @return The minimum bag size of the decomposition.
             */
            virtual std::size_t minimumBagSize(void) const = 0;

            /**
             *  Getter for the maximum bag size of the decomposition.
             *
             *  @return The minimum bag size of the decomposition.
             */
            virtual std::size_t maximumBagSize(void) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current graph decomposition.
             *
             *  @return A new IGraphDecomposition object identical to the current graph decomposition.
             */
            virtual IGraphDecomposition * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current graph decomposition.
             *
             *  @return A new IGraphDecomposition object identical to the current graph decomposition.
             */
            virtual IGraphDecomposition * cloneGraphDecomposition(void) const = 0;
#endif
    };

    inline htd::IGraphDecomposition::~IGraphDecomposition() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITION_HPP */
