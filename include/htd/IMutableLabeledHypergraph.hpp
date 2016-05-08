/* 
 * File:   IMutableLabeledHypergraph.hpp
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

#ifndef HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP
#define	HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/ILabeledMultiHypergraph.hpp>

namespace htd
{
    class IMutableLabeledHypergraph : public virtual htd::ILabeledHypergraph, public virtual htd::IMutableHypergraph
    {
        public:
            virtual ~IMutableLabeledHypergraph() = 0;

            virtual void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) = 0;

            virtual void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            virtual void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

            virtual void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            virtual void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) = 0;

            virtual htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            virtual htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) = 0;

            /**
             *  Create a deep copy the current mutable labeled hypergraph.
             *
             *  @return A new IMutableLabeledHypergraph object identical to the current mutable labeled hypergraph.
             */
            virtual IMutableLabeledHypergraph * clone(void) const = 0;

            /**
             *  Copy assignment operator for a mutable labeled hypergraph.
             *
             *  @param[in] original  The original labeled hypergraph.
             */
            virtual IMutableLabeledHypergraph & operator=(const htd::ILabeledHypergraph & original) = 0;

            /**
             *  Copy assignment operator for a mutable labeled hypergraph.
             *
             *  @param[in] original  The original labeled multi-hypergraph.
             */
            virtual IMutableLabeledHypergraph & operator=(const htd::ILabeledMultiHypergraph & original) = 0;
    };

    inline htd::IMutableLabeledHypergraph::~IMutableLabeledHypergraph() { }
}

#endif /* HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP */
