/* 
 * File:   TreeDecompositionVerifier.hpp
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

#ifndef HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP
#define	HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP

#include <htd/Globals.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/ITreeDecompositionVerifier.hpp>

namespace htd
{
    class TreeDecompositionVerifier : public virtual htd::ITreeDecompositionVerifier
    {
        public:
            TreeDecompositionVerifier(void);
                        
            ~TreeDecompositionVerifier();
                        
            bool verify(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            bool verifyVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            bool verifyHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            bool verifyConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            const htd::Collection<htd::vertex_t> violationsVertexExistence(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            const htd::Collection<htd::hyperedge_t> violationsHyperEdgeCoverage(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;
            
            const htd::Collection<htd::vertex_t> violationsConnectednessCriterion(const htd::IHypergraph & graph, const htd::ITreeDecomposition & decomposition) const HTD_OVERRIDE;

        protected:
            TreeDecompositionVerifier & operator=(const TreeDecompositionVerifier &) { return *this; }

        private:
            void getReachableVertices(htd::vertex_t start, const htd::ITreeDecomposition & decomposition, const htd::vertex_container & filter, htd::vertex_container & output) const;
    };
}

#endif /* HTD_HTD_TREEDECOMPOSITIONVERIFIER_HPP */
