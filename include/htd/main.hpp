/*
 * File:   main.hpp
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

#ifndef HTD_HTD_MAIN_HPP
#define	HTD_HTD_MAIN_HPP

#include <htd/AddEmptyLeavesOperation.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/BidirectionalGraphLabeling.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/Collection.hpp>
#include <htd/CompilerDetection.hpp>
#include <htd/Converters.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/Globals.hpp>
#include <htd/Graph.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/Helpers.hpp>
#include <htd/HeuristicSetCoverAlgorithm.hpp>
#include <htd/HyperedgeContainerLabel.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>
#include <htd/IBidirectionalGraphLabeling.hpp>
#include <htd/Id.hpp>
#include <htd/IDirectedGraph.hpp>
#include <htd/IGraph.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IHypertreeDecomposition.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>
#include <htd/ILabel.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/ILabeledDirectedGraph.hpp>
#include <htd/ILabeledGraph.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/ILabeledPath.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/IMutableLabeledDirectedGraph.hpp>
#include <htd/IMutableLabeledGraph.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/IMutablePath.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IMutableTree.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IPath.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/ITree.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionVerifier.hpp>
#include <htd/InducedSubgraphLabelingFunction.hpp>
#include <htd/Iterator.hpp>
#include <htd/IteratorBase.hpp>
#include <htd/IteratorWrapper.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/Label.hpp>
#include <htd/LabelCollection.hpp>
#include <htd/LabeledHypergraph.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/LimitMaximumForgottenVerticesCountOperation.hpp>
#include <htd/LimitMaximumIntroducedVerticesCountOperation.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/NaturalOrderingAlgorithm.hpp>
#include <htd/NormalizationOperation.hpp>
#include <htd/SetCoverAlgorithm.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/TreeDecompositionVerifier.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/Vertex.hpp>
#include <htd/VertexContainerLabel.hpp>

#endif /* HTD_HTD_MAIN_HPP */
