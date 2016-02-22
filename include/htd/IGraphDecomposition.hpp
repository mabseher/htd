/* 
 * File:   IGraphDecomposition.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITION_HPP
#define	HTD_HTD_IGRAPHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabeledGraph.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/FilteredHyperedgeCollection.hpp>

#include <vector>

namespace htd
{
    class IGraphDecomposition : public virtual htd::ILabeledGraph
    {
        public:
            /**
             *  Constant for the identifier of the bag label.
             */
            static constexpr const char * BAG_LABEL_IDENTIFIER = "Bag";

            /**
             *  Constant for the identifier of the label for induced edges.
             */
            static constexpr const char * INDUCED_EDGES_LABEL_IDENTIFIER = "Induced Edges";

            virtual ~IGraphDecomposition() = 0;

            virtual std::size_t bagSize(htd::vertex_t vertex) const = 0;

            virtual const std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) const = 0;

            virtual const htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) const = 0;

            virtual std::size_t minimumBagSize(void) const = 0;

            virtual std::size_t maximumBagSize(void) const = 0;

            virtual IGraphDecomposition * clone(void) const = 0;
    };

    inline htd::IGraphDecomposition::~IGraphDecomposition() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITION_HPP */
