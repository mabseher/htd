/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.hpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP

#include <htd/Globals.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IOrderingAlgorithm.hpp>

#include <vector>
#include <unordered_set>

namespace htd
{
    class BucketEliminationTreeDecompositionAlgorithm : public virtual htd::ITreeDecompositionAlgorithm
    {
        public:
            BucketEliminationTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm);

            BucketEliminationTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm, const std::vector<htd::ILabelingFunction *> & labelingFunctions);

            ~BucketEliminationTreeDecompositionAlgorithm();
            
            htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph) const HTD_OVERRIDE;

            htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const HTD_OVERRIDE;

            htd::ITreeDecomposition * computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const; //TODO HTD_OVERRIDE;

        protected:
            BucketEliminationTreeDecompositionAlgorithm & operator=(const BucketEliminationTreeDecompositionAlgorithm &) { return *this; }

        private:
            const htd::IOrderingAlgorithm & orderingAlgorithm_;

            htd::IMutableTreeDecomposition * computeMutableDecomposition(const htd::IHypergraph & graph) const;

            htd::vertex_t getMinimumVertex(const htd::hyperedge_t & edge, const std::vector<htd::index_t> & vertexIndices) const;

            void getReachableVertices(htd::vertex_t start, const htd::vertex_container & vertices, const std::vector<htd::index_t> & vertexIndices, const std::vector<htd::vertex_container> & neighbors, htd::vertex_container & output) const;
            
            void getUnreachableVertices(htd::vertex_t start, const htd::vertex_container & vertices, const std::vector<htd::index_t> & vertexIndices, const std::vector<htd::vertex_container> & neighbors, htd::vertex_container & output) const;

            htd::IMutableTreeDecomposition * createRootedTreeDecomposition(htd::vertex_t vertex, const std::vector<htd::vertex_container> & neighbors, const std::vector<htd::vertex_container> & buckets) const;

            void compressDecomposition(htd::IMutableTreeDecomposition & decomposition) const;
    };
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_HPP */
