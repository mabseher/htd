/* 
 * File:   LabeledHypergraph.hpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_HPP
#define	HTD_HTD_LABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>
#include <htd/Hypergraph.hpp>

namespace htd
{
    /**
     *  Default implementation of the IMutableLabeledHypergraph interface.
     */
    class LabeledHypergraph : public htd::Hypergraph, public virtual htd::IMutableLabeledHypergraph
    {
        public:
            /**
             *  Constructor for a labeled hypergraph.
             */
            LabeledHypergraph(void);

            /**
             *  Constructor for a labeled hypergraph.
             *
             *  @param[in] initialSize  The initial size of the created graph.
             */
            LabeledHypergraph(std::size_t initialSize);

            /**
             *  Copy constructor for a labeled hypergraph.
             *
             *  @param[in] original  The original labeled hypergraph.
             */
            LabeledHypergraph(const LabeledHypergraph & original);

            /**
             *  Copy constructor for a labeled hypergraph.
             *
             *  @param[in] original  The original hypergraph.
             */
            LabeledHypergraph(const htd::IHypergraph & original);

            /**
             *  Copy constructor for a labeled hypergraph.
             *
             *  @param[in] original  The original labeled hypergraph.
             */
            LabeledHypergraph(const htd::ILabeledHypergraph & original);
            
            virtual ~LabeledHypergraph();

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeEdge(htd::id_t edgeId) HTD_OVERRIDE;

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE;

            std::size_t labelCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<std::string> labelNames(void) const HTD_OVERRIDE;

            const std::string & labelNameAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const HTD_OVERRIDE;

            void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label) HTD_OVERRIDE;

            void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label) HTD_OVERRIDE;

            void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

            void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE;

            void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2) HTD_OVERRIDE;

            htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex) HTD_OVERRIDE;

            htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId) HTD_OVERRIDE;

            LabeledHypergraph * clone(void) const HTD_OVERRIDE;

            /**
             *  Copy assignment operator for a mutable labeled hypergraph.
             *
             *  @param[in] original  The original labeled hypergraph.
             */
            LabeledHypergraph & operator=(const LabeledHypergraph & original);

            LabeledHypergraph & operator=(const htd::IHypergraph & original) HTD_OVERRIDE;

            LabeledHypergraph & operator=(const htd::IMultiHypergraph & original) HTD_OVERRIDE;

            LabeledHypergraph & operator=(const htd::ILabeledHypergraph & original) HTD_OVERRIDE;

            LabeledHypergraph & operator=(const htd::ILabeledMultiHypergraph & original) HTD_OVERRIDE;

        private:
            htd::ILabelingCollection * labelings_;
    };
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_HPP */
