/* 
 * File:   ILabeledMultiHypergraph.hpp
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

#ifndef HTD_HTD_ILABELEDMULTIHYPERGRAPH_HPP
#define HTD_HTD_ILABELEDMULTIHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/ILabel.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/ILabelingCollection.hpp>

#include <string>

namespace htd
{
    /**
     * Interface for classes which represent labeled hypergraphs with potentially duplicated edges.
     */
    class ILabeledMultiHypergraph : public virtual htd::IMultiHypergraph
    {
        public:
            virtual ~ILabeledMultiHypergraph() = 0;

            /**
             *  Access the collection of all labelings used in the graph.
             *
             *  @return The collection of all labelings used in the graph.
             */
            virtual const htd::ILabelingCollection & labelings(void) const = 0;

            /**
             *  Getter for the number of different label names in the graph.
             *
             *  @return The number of different label names in the graph.
             */
            virtual std::size_t labelCount(void) const = 0;

            /**
             *  Access the collection of all label names used in the graph.
             *
             *  @return The collection of all label names used in the graph sorted in ascending order.
             */
            virtual htd::ConstCollection<std::string> labelNames(void) const = 0;

            /**
             *  Access the label name at the specific position.
             *
             *  @param[in] index    The position of the label name.
             *
             *  @return The label name at the specific position.
             */
            virtual const std::string & labelNameAtPosition(htd::index_t index) const = 0;

            /**
             *  Check whether a given vertex has a label with the specific name.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] vertex       The vertex.
             *
             *  @return True if the given vertex has a label with the specific name, false otherwise.
             */
            virtual bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const = 0;

            /**
             *  Check whether a given edge has a label with the specific name.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeId       The ID of the edge.
             *
             *  @return True if the given edge has a label with the specific name, false otherwise.
             */
            virtual bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const = 0;

            /**
             *  Access the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] vertex       The vertex.
             *
             *  @return The label associated with the given vertex.
             */
            virtual const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const = 0;

            /**
             *  Access the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeId       The ID of the edge.
             *
             *  @return The label associated with the given edge.
             */
            virtual const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const = 0;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current labeled multi-hypergraph.
             *
             *  @return A new ILabeledMultiHypergraph object identical to the current labeled multi-hypergraph.
             */
            virtual ILabeledMultiHypergraph * clone(void) const HTD_OVERRIDE = 0;
#else
            /**
             *  Create a deep copy of the current labeled multi-hypergraph.
             *
             *  @return A new ILabeledMultiHypergraph object identical to the current labeled multi-hypergraph.
             */
            virtual ILabeledMultiHypergraph * cloneLabeledMultiHypergraph(void) const = 0;
#endif
    };

    inline htd::ILabeledMultiHypergraph::~ILabeledMultiHypergraph() { }
}

#endif /* HTD_HTD_ILABELEDMULTIHYPERGRAPH_HPP */
