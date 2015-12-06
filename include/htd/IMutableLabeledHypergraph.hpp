/* 
 * File:   IMutableLabeledHypergraph.hpp
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

#ifndef HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP
#define	HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/ILabeledHypergraph.hpp>

namespace htd
{
    class IMutableLabeledHypergraph : public virtual htd::ILabeledHypergraph, public virtual htd::IMutableHypergraph
    {
        public:
            virtual ~IMutableLabeledHypergraph() = 0;

            virtual void setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) = 0;

            virtual void setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label) = 0;

            virtual void removeLabel(const std::string & labelName, htd::vertex_t vertex) = 0;

            virtual void removeLabel(const std::string & labelName, const htd::hyperedge_t & edge) = 0;

            virtual void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) = 0;

            virtual void swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) = 0;

            virtual void swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) = 0;

            virtual IMutableLabeledHypergraph * clone(void) const = 0;
    };

    inline htd::IMutableLabeledHypergraph::~IMutableLabeledHypergraph() { }
}

#endif /* HTD_HTD_IMUTABLELABELEDHYPERGRAPH_HPP */
