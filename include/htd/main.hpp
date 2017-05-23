/*
 * File:   main.hpp
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

#ifndef HTD_HTD_MAIN_HPP
#define HTD_HTD_MAIN_HPP

#include <htd/AdaptiveWidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/AddEmptyLeavesOperation.hpp>
#include <htd/AddEmptyRootOperation.hpp>
#include <htd/AddIdenticalJoinNodeParentOperation.hpp>
#include <htd/Algorithm.hpp>
#include <htd/AssemblyInfo.hpp>
#include <htd/BiconnectedComponentAlgorithm.hpp>
#include <htd/BidirectionalGraphNaming.hpp>
#include <htd/BreadthFirstGraphTraversal.hpp>
#include <htd/BucketEliminationGraphDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
#include <htd/CliqueMinimalSeparatorAlgorithm.hpp>
#include <htd/Collection.hpp>
#include <htd/CombinedWidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/ConstIteratorBase.hpp>
#include <htd/ConstIterator.hpp>
#include <htd/ConstIteratorWrapper.hpp>
#include <htd/ConstPointerIteratorWrapper.hpp>
#include <htd/DepthFirstConnectedComponentAlgorithm.hpp>
#include <htd/DepthFirstGraphTraversal.hpp>
#include <htd/DinitzMaxFlowAlgorithm.hpp>
#include <htd/DirectedGraphFactory.hpp>
#include <htd/DirectedGraph.hpp>
#include <htd/DirectedMultiGraphFactory.hpp>
#include <htd/DirectedMultiGraph.hpp>
#include <htd/EnhancedMaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/ExchangeNodeReplacementOperation.hpp>
#include <htd/ExhaustiveVertexSelectionStrategy.hpp>
#include <htd/FilteredHyperedgeCollection.hpp>
#include <htd/FitnessEvaluation.hpp>
#include <htd/FlowNetworkStructure.hpp>
#include <htd/Globals.hpp>
#include <htd/GraphDecompositionAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/GraphDecomposition.hpp>
#include <htd/GraphFactory.hpp>
#include <htd/Graph.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/GraphPreprocessor.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/GraphSeparatorAlgorithmFactory.hpp>
#include <htd/GreedySetCoverAlgorithm.hpp>
#include <htd/Helpers.hpp>
#include <htd/HyperedgeDeque.hpp>
#include <htd/Hyperedge.hpp>
#include <htd/HyperedgePointerDeque.hpp>
#include <htd/HyperedgePointerVector.hpp>
#include <htd/HyperedgeVector.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/HypertreeDecompositionAlgorithmFactory.hpp>
#include <htd/HypertreeDecompositionAlgorithm.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/IBiconnectedComponentAlgorithm.hpp>
#include <htd/IConnectedComponentAlgorithm.hpp>
#include <htd/ICustomizedTreeDecompositionAlgorithm.hpp>
#include <htd/IDecompositionManipulationOperation.hpp>
#include <htd/Id.hpp>
#include <htd/IDirectedGraph.hpp>
#include <htd/IDirectedMultiGraph.hpp>
#include <htd/IFlow.hpp>
#include <htd/IFlowNetworkStructure.hpp>
#include <htd/IGraphDecompositionAlgorithm.hpp>
#include <htd/IGraphDecomposition.hpp>
#include <htd/IGraphDecompositionManipulationOperation.hpp>
#include <htd/IGraph.hpp>
#include <htd/IGraphLabeling.hpp>
#include <htd/IGraphPreprocessor.hpp>
#include <htd/IGraphSeparatorAlgorithm.hpp>
#include <htd/IGraphStructure.hpp>
#include <htd/IGraphTraversal.hpp>
#include <htd/IHyperedgeCollection.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>
#include <htd/IHypertreeDecomposition.hpp>
#include <htd/ILabelCollection.hpp>
#include <htd/ILabeledDirectedGraph.hpp>
#include <htd/ILabeledDirectedMultiGraph.hpp>
#include <htd/ILabeledGraph.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/ILabeledMultiGraph.hpp>
#include <htd/ILabeledMultiHypergraph.hpp>
#include <htd/ILabeledPath.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/ILabel.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/ILabelingFunction.hpp>
#include <htd/IMaxFlowAlgorithm.hpp>
#include <htd/IMultiGraph.hpp>
#include <htd/IMultiHypergraph.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/IMutableDirectedMultiGraph.hpp>
#include <htd/IMutableGraphDecomposition.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/IMutableLabeledDirectedGraph.hpp>
#include <htd/IMutableLabeledDirectedMultiGraph.hpp>
#include <htd/IMutableLabeledGraph.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>
#include <htd/IMutableLabeledMultiGraph.hpp>
#include <htd/IMutableLabeledMultiHypergraph.hpp>
#include <htd/IMutableLabeledPath.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/IMutableMultiGraph.hpp>
#include <htd/IMutableMultiHypergraph.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/IMutablePath.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IMutableTree.hpp>
#include <htd/InducedSubgraphLabelingOperation.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/IPathDecompositionAlgorithm.hpp>
#include <htd/IPathDecomposition.hpp>
#include <htd/IPathDecompositionManipulationOperation.hpp>
#include <htd/IPath.hpp>
#include <htd/IPreprocessedGraph.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/IStronglyConnectedComponentAlgorithm.hpp>
#include <htd/IterativeImprovementTreeDecompositionAlgorithm.hpp>
#include <htd/IteratorBase.hpp>
#include <htd/Iterator.hpp>
#include <htd/IteratorWrapper.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/ITreeDecompositionFitnessFunction.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/ITreeDecompositionManipulationOperation.hpp>
#include <htd/ITreeDecompositionVerifier.hpp>
#include <htd/ITree.hpp>
#include <htd/ITreeTraversal.hpp>
#include <htd/IVertexOrdering.hpp>
#include <htd/IVertexSelectionStrategy.hpp>
#include <htd/IWidthLimitableOrderingAlgorithm.hpp>
#include <htd/IWidthLimitedVertexOrdering.hpp>
#include <htd/IWidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/JoinNodeComplexityReductionOperation.hpp>
#include <htd/JoinNodeNormalizationOperation.hpp>
#include <htd/JoinNodeReplacementOperation.hpp>
#include <htd/LabelCollection.hpp>
#include <htd/LabeledDirectedGraphFactory.hpp>
#include <htd/LabeledDirectedGraph.hpp>
#include <htd/LabeledDirectedMultiGraphFactory.hpp>
#include <htd/LabeledDirectedMultiGraph.hpp>
#include <htd/LabeledGraphFactory.hpp>
#include <htd/LabeledGraph.hpp>
#include <htd/LabeledGraphType.hpp>
#include <htd/LabeledHypergraphFactory.hpp>
#include <htd/LabeledHypergraph.hpp>
#include <htd/LabeledMultiGraphFactory.hpp>
#include <htd/LabeledMultiGraph.hpp>
#include <htd/LabeledMultiHypergraphFactory.hpp>
#include <htd/LabeledMultiHypergraph.hpp>
#include <htd/LabeledPathFactory.hpp>
#include <htd/LabeledPath.hpp>
#include <htd/LabeledTreeFactory.hpp>
#include <htd/LabeledTree.hpp>
#include <htd/Label.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/LibraryInstance.hpp>
#include <htd/LimitChildCountOperation.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>
#include <htd/LimitMaximumIntroducedVertexCountOperation.hpp>
#include <htd/MaximumCardinalitySearchOrderingAlgorithm.hpp>
#include <htd/MinDegreeOrderingAlgorithm.hpp>
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/MinimumSeparatorAlgorithm.hpp>
#include <htd/MultiGraphFactory.hpp>
#include <htd/MultiGraph.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/MultiHypergraph.hpp>
#include <htd/NamedDirectedGraph.hpp>
#include <htd/NamedDirectedMultiGraph.hpp>
#include <htd/NamedGraph.hpp>
#include <htd/NamedHypergraph.hpp>
#include <htd/NamedMultiGraph.hpp>
#include <htd/NamedMultiHypergraph.hpp>
#include <htd/NamedPath.hpp>
#include <htd/NamedTree.hpp>
#include <htd/NamedVertexHyperedge.hpp>
#include <htd/NaturalOrderingAlgorithm.hpp>
#include <htd/NormalizationOperation.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/PathDecompositionAlgorithmFactory.hpp>
#include <htd/PathDecompositionFactory.hpp>
#include <htd/PathDecomposition.hpp>
#include <htd/Path.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/PostProcessingPathDecompositionAlgorithm.hpp>
#include <htd/PreOrderTreeTraversal.hpp>
#include <htd/PreprocessedGraph.hpp>
#include <htd/PreprocessorDefinitions.hpp>
#include <htd/PriorityQueue.hpp>
#include <htd/RandomOrderingAlgorithm.hpp>
#include <htd/RandomVertexSelectionStrategy.hpp>
#include <htd/SemiNormalizationOperation.hpp>
#include <htd/SeparatorBasedTreeDecompositionAlgorithm.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/SetCoverAlgorithm.hpp>
#include <htd/SingleNeighborVertexSelectionStrategy.hpp>
#include <htd/State.hpp>
#include <htd/StronglyConnectedComponentAlgorithmFactory.hpp>
#include <htd/TarjanStronglyConnectedComponentAlgorithm.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/TreeDecompositionOptimizationOperation.hpp>
#include <htd/TreeDecompositionVerifier.hpp>
#include <htd/Tree.hpp>
#include <htd/TriangulationMinimizationOrderingAlgorithm.hpp>
#include <htd/TrivialTreeDecompositionAlgorithm.hpp>
#include <htd/VectorAdapterConstIteratorWrapper.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/VectorAdapterIteratorWrapper.hpp>
#include <htd/Vertex.hpp>
#include <htd/VertexOrdering.hpp>
#include <htd/WeakNormalizationOperation.hpp>
#include <htd/WidthMinimizingTreeDecompositionAlgorithm.hpp>
#include <htd/WidthReductionOperation.hpp>

#endif /* HTD_HTD_MAIN_HPP */
