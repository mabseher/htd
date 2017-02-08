/* 
 * File:   ITreeDecompositionVerifier.hpp
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

#ifndef HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP
#define HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP

#include <htd/Globals.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/ITreeDecomposition.hpp>

namespace htd
{
    /**
     * Interface for algorithms which verify the correctness of a given tree decomposition.
     */
    class ITreeDecompositionVerifier
    {
        public:
            virtual ~ITreeDecompositionVerifier() = 0;
            
            /**
             *  Verify if the given tree decomposition is indeed a valid tree decomposition of the given graph.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return True if the given tree decomposition is indeed a valid tree decomposition of the given graph, false otherwise.
             */
            virtual bool verify(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Verify whether for each vertex of the input graph there is at least one bag of the given tree decomposition which contains the vertex.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return True if for each vertex of the input graph there is at least one bag of the given tree decomposition which contains the vertex, false otherwise.
             */
            virtual bool verifyVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Verify whether for each edge of the input graph there is at least one bag of the given tree decomposition which contains the edge.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return True if for each edge of the input graph there is at least one bag of the given tree decomposition which contains the edge, false otherwise.
             */
            virtual bool verifyHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Verify whether for each vertex of the input graph the decomposition nodes containing the vertex in their bags form a connected subgraph.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return True if for each vertex of the input graph the decomposition nodes containing the vertex in their bags form a connected subgraph, false otherwise.
             */
            virtual bool verifyConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
            
            /**
             *  Get the collection of all vertices of the input graph which do not occur in any bag of the decomposition.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return The collection of all vertices of the input graph which do not occur in any bag of the decomposition.
             */
            virtual htd::ConstCollection<htd::vertex_t> violationsVertexExistence(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Get the collection of all edges of the input graph which are not contained in any bag of the decomposition.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return The collection of all edges of the input graph which are not contained in any bag of the decomposition.
             */
            virtual htd::ConstCollection<htd::Hyperedge> violationsHyperedgeCoverage(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;

            /**
             *  Get the collection of all vertices of the input graph for which the decomposition nodes containing the vertex in their bags do not form a connected subgraph.
             *
             *  @param[in] graph            The input graph.
             *  @param[in] decomposition    The tree decomposition which shall be verified.
             *
             *  @return The collection of all vertices of the input graph for which the decomposition nodes containing the vertex in their bags do not form a connected subgraph.
             */
            virtual htd::ConstCollection<htd::vertex_t> violationsConnectednessCriterion(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition) const = 0;
    };

    inline htd::ITreeDecompositionVerifier::~ITreeDecompositionVerifier() { }
}

#endif /* HTD_HTD_ITREEDECOMPOSITIONVERIFIER_HPP */
