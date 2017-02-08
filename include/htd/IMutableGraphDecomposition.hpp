/* 
 * File:   IMutableGraphDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP
#define HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledMultiHypergraph.hpp>
#include <htd/IGraphDecomposition.hpp>

namespace htd
{
    /**
     * Interface for classes which represent mutable graph decompositions.
     */
    class IMutableGraphDecomposition : public virtual htd::IMutableLabeledMultiHypergraph, public virtual htd::IGraphDecomposition
    {
        public:
            using htd::IMutableLabeledMultiHypergraph::addVertex;

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            using htd::IMutableLabeledMultiHypergraph::assign;
#endif

            /**
             *  Destructor for an IMutableGraphDecomposition object.
             */
            virtual ~IMutableGraphDecomposition() = 0;

            /**
             *  Add a new vertex to the graph decomposition.
             *
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new vertex.
             */
            virtual htd::vertex_t addVertex(const std::vector<htd::vertex_t> & bagContent, const htd::FilteredHyperedgeCollection & inducedEdges) = 0;

            /**
             *  Add a new vertex to the graph decomposition.
             *
             *  @param[in] bagContent   The bag content associated with the new vertex.
             *  @param[in] inducedEdges The collection of induced edges associated with the new vertex.
             *
             *  @return The ID of the new vertex.
             */
            virtual htd::vertex_t addVertex(std::vector<htd::vertex_t> && bagContent, htd::FilteredHyperedgeCollection && inducedEdges) = 0;

            /**
             *  Access the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the bag content shall be returned.
             *
             *  @return The bag content of the specific vertex.
             */
            virtual std::vector<htd::vertex_t> & mutableBagContent(htd::vertex_t vertex) = 0;

            /**
             *  Access the hyperedges induced by the bag content of a specific vertex.
             *
             *  @param[in] vertex   The vertex for which the induced hyperedges shall be returned.
             *
             *  @return The collection of hyperedges induced by the bag content of the specific vertex.
             */
            virtual htd::FilteredHyperedgeCollection & mutableInducedHyperedges(htd::vertex_t vertex) = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current mutable graph decomposition.
             *
             *  @return A new IMutableGraphDecomposition object identical to the current mutable graph decomposition.
             */
            virtual IMutableGraphDecomposition * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current mutable graph decomposition.
             *
             *  @return A new IMutableGraphDecomposition object identical to the current mutable graph decomposition.
             */
            virtual IMutableGraphDecomposition * cloneMutableGraphDecomposition(void) const = 0;
#endif

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a mutable graph decomposition.
             *
             *  @param[in] original  The original multi-hypergraph.
             */
            virtual IMutableGraphDecomposition & operator=(const htd::IMultiHypergraph & original) HTD_OVERRIDE = 0;

            /**
             *  Copy assignment operator for a mutable graph decomposition.
             *
             *  @param[in] original  The original labeled multi-hypergraph.
             */
            virtual IMutableGraphDecomposition & operator=(const htd::ILabeledMultiHypergraph & original) HTD_OVERRIDE = 0;

            /**
             *  Copy assignment operator for a mutable graph decomposition.
             *
             *  @param[in] original  The original graph decomposition.
             */
            virtual IMutableGraphDecomposition & operator=(const htd::IGraphDecomposition & original) = 0;
#else
            /**
             *  Copy assignment operator for a mutable graph decomposition.
             *
             *  @param[in] original  The original graph decomposition.
             */
            virtual void assign(const htd::IGraphDecomposition & original) = 0;
#endif
    };

    inline htd::IMutableGraphDecomposition::~IMutableGraphDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP */
