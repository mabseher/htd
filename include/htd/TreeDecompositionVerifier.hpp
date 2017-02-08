/* 
 * File:   TreeDecompositionVerifier.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP
#define HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionVerifier.hpp>

namespace htd
{
    /**
     *  Default implementation of the ITreeDecompositionVerifier interface.
     */
    class TreeDecompositionVerifier : public virtual htd::ITreeDecompositionVerifier
    {
        public:
            /**
             *  Constructor for a tree decomposition verifier.
             */
            HTD_API TreeDecompositionVerifier(void);
                        
            HTD_API virtual ~TreeDecompositionVerifier();
                        
            HTD_API bool verify(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API bool verifyVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API bool verifyHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API bool verifyConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API htd::ConstCollection<htd::vertex_t> violationsVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API htd::ConstCollection<htd::Hyperedge> violationsHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            HTD_API htd::ConstCollection<htd::vertex_t> violationsConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;

        protected:
            /**
             *  Copy assignment operator for a tree decomposition verifier.
             *
             *  @note This operator is protected to prevent assignments to an already initialized tree decomposition verifier.
             */
            TreeDecompositionVerifier & operator=(const TreeDecompositionVerifier &) { return *this; }
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP */
