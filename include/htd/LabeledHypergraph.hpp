/* 
 * File:   LabeledHypergraph.hpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_HPP
#define	HTD_HTD_LABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>
#include <htd/Hypergraph.hpp>

#include <htd/Collection.hpp>

namespace htd
{
    class LabeledHypergraph : public htd::Hypergraph, public virtual htd::IMutableLabeledHypergraph
    {
        public:
            LabeledHypergraph(void);
            
            LabeledHypergraph(std::size_t size);

            LabeledHypergraph(const LabeledHypergraph & original);
            
            virtual ~LabeledHypergraph();

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge) HTD_OVERRIDE;

            void removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void removeEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end) HTD_OVERRIDE;

            void removeEdge(const htd::edge_t & edge) HTD_OVERRIDE;

            void removeEdge(const htd::hyperedge_t & edge) HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE;

            const htd::ILabel & label(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & label(const std::string & labelName, const htd::hyperedge_t & edge) const HTD_OVERRIDE;

            void setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label) HTD_OVERRIDE;

            void removeLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            void removeLabel(const std::string & labelName, const htd::hyperedge_t & edge) HTD_OVERRIDE;

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            void swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE;

            LabeledHypergraph * clone(void) const HTD_OVERRIDE;

        private:
            htd::ILabelingCollection * labelings_;
    };
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_HPP */
