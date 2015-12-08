/* 
 * File:   IGraphDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ILabeledGraph.hpp>
#include <htd/ILabelingFunction.hpp>

#include <vector>

namespace htd
{
    class IGraphDecompositionAlgorithm
    {
        public:
            virtual ~IGraphDecompositionAlgorithm() = 0;
            
            virtual htd::ILabeledGraph * computeDecomposition(const htd::IHypergraph & graph) const = 0;

            virtual htd::ILabeledGraph * computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const = 0;

            //virtual htd::ILabeledGraph * computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const = 0; //TODO HTD_OVERRIDE
    };

    inline htd::IGraphDecompositionAlgorithm::~IGraphDecompositionAlgorithm() { }
}

#endif /* HTD_HTD_IGRAPHDECOMPOSITIONALGORITHM_HPP */
