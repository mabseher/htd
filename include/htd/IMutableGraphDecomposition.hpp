/* 
 * File:   IMutableGraphDecomposition.hpp
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

#ifndef HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP
#define	HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledGraph.hpp>
#include <htd/IGraphDecomposition.hpp>
#include <htd/Label.hpp>

namespace htd
{
    class IMutableGraphDecomposition : public virtual htd::IMutableLabeledGraph, public virtual htd::IGraphDecomposition
    {
        public:
            using htd::IGraphDecomposition::bagContent;

            virtual ~IMutableGraphDecomposition() = 0;

            virtual std::vector<htd::vertex_t> & bagContent(htd::vertex_t vertex) = 0;

            virtual htd::FilteredHyperedgeCollection & inducedHyperedges(htd::vertex_t vertex) = 0;

            virtual IMutableGraphDecomposition * clone(void) const = 0;

            virtual IMutableGraphDecomposition & operator=(const htd::IGraph & original) = 0;

            virtual IMutableGraphDecomposition & operator=(const htd::ILabeledGraph & original) = 0;

            virtual IMutableGraphDecomposition & operator=(const htd::ILabeledMultiGraph & original) = 0;

            virtual IMutableGraphDecomposition & operator=(const htd::IGraphDecomposition & original) = 0;
    };

    inline htd::IMutableGraphDecomposition::~IMutableGraphDecomposition() { }
}

#endif /* HTD_HTD_IMUTABLEGRAPHDECOMPOSITION_HPP */
