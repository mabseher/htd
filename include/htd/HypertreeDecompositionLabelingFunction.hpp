/*
 * File:   HypertreeDecompositionLabelingFunction.hpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/ISetCoverAlgorithm.hpp>

#include <string>

namespace htd
{
    class HypertreeDecompositionLabelingFunction : public htd::ILabelingFunction
    {
        public:
            HypertreeDecompositionLabelingFunction(const htd::IHypergraph & graph, const htd::ISetCoverAlgorithm & setCoverAlgorithm);

            ~HypertreeDecompositionLabelingFunction();
	    
            std::string name() const HTD_OVERRIDE;
	        
            htd::ILabel * computeLabel(const htd::vertex_container & vertices) const HTD_OVERRIDE;

        private:
            const htd::IHypergraph & graph_;

            const htd::ISetCoverAlgorithm & setCoverAlgorithm_;

            htd::hyperedge_container hyperedges_;
    };
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_HPP */
