/*
 * File:   InducedSubgraphLabelingFunction.hpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_HPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/Label.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/IHypergraph.hpp>

#include <string>

namespace htd
{
    class InducedSubgraphLabelingFunction : public virtual htd::ILabelingFunction
    {
        public:
            /**
             *  Constant for the identifier of the induced subgraph label.
             */
            static constexpr const char * INDUCED_SUBGRAPH_LABEL_IDENTIFIER = "Induced Subgraph";

            InducedSubgraphLabelingFunction(const htd::IHypergraph & graph);

            ~InducedSubgraphLabelingFunction();
	    
            std::string name() const HTD_OVERRIDE;
	        
            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices) const;

            htd::Label<htd::ConstCollection<htd::Hyperedge>> * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE;

        private:
            const htd::IHypergraph & graph_;

            htd::hyperedge_container hyperedges_;
    };
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_HPP */
