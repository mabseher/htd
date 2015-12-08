/* 
 * File:   ITreeDecompositionVerifier.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP
#define	HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    class ITreeDecompositionVerifier
    {
        public:
            virtual ~ITreeDecompositionVerifier() = 0;
            
            virtual bool verify(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
            
            virtual bool verifyVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
            
            virtual bool verifyHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
            
            virtual bool verifyConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
            
            virtual void getViolationsVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_container & output) const = 0;
            
            virtual void getViolationsHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::hyperedge_container & output) const = 0;
            
            virtual void getViolationsConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_container & output) const = 0;
    };

    inline htd::ITreeDecompositionVerifier::~ITreeDecompositionVerifier() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP */
