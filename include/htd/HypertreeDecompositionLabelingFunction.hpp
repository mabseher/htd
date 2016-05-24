/*
 * File:   HypertreeDecompositionLabelingFunction.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/Label.hpp>

namespace htd
{
    /**
     *  Implementation of the ILabelingFunction interface which returns labels containing the hyperedges needed to cover the given bag.
     */
    class HypertreeDecompositionLabelingFunction : public virtual htd::ILabelingFunction
    {
        public:
            /**
             *  Constructor for a new labeling function of type HypertreeDecompositionLabelingFunction.
             *
             *  @param[in] graph    The graph from which the edges required to cover each bag shall be computed.
             */
            HypertreeDecompositionLabelingFunction(const htd::IMultiHypergraph & graph);

            ~HypertreeDecompositionLabelingFunction();
	    
            std::string name() const HTD_OVERRIDE;

            /**
             *  Compute a new label based on a set of vertices (e.g., the bag of a graph decomposition).
             *
             *  @param[in] vertices The set of input vertices sorted in ascending order.
             *
             *  @return A new label based on the given set of vertices.
             */
            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const std::vector<htd::vertex_t> & vertices) const;

            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE;

            /**
             *  Compute a new label based on a set of vertices (e.g., the bag of a graph decomposition).
             *
             *  @param[in] vertices The set of input vertices sorted in ascending order.
             *
             *  @return A new label based on the given set of vertices.
             */
            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices) const;

            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE;

            HypertreeDecompositionLabelingFunction * clone(void) const HTD_OVERRIDE;

        private:
            const htd::IMultiHypergraph & graph_;

            htd::hyperedge_container hyperedges_;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP */
