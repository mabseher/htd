/*
 * File:   WidthReductionOperation.cpp
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

#ifndef HTD_HTD_WIDTHREDUCTIONOPERATION_CPP
#define HTD_HTD_WIDTHREDUCTIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/WidthReductionOperation.hpp>
#include <htd/MultiGraphFactory.hpp>
#include <htd/MinimumSeparatorAlgorithm.hpp>
#include <htd/GraphSeparatorAlgorithmFactory.hpp>
#include <htd/ConnectedComponentAlgorithmFactory.hpp>

#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 *  Private implementation details of class htd::WidthReductionOperation.
 */
struct htd::WidthReductionOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager),
                                                                 separatorAlgorithm_(managementInstance_->graphSeparatorAlgorithmFactory().createInstance()),
                                                                 connectedComponentAlgorithm_(managementInstance_->connectedComponentAlgorithmFactory().createInstance()), restrictedToLargestBags_(true)
    {

    }

    /**
     *  Copy constructor for the implementation details structure.
     *
     *  @param[in] original The original implementation details structure.
     */
    Implementation(const Implementation & original) : managementInstance_(original.managementInstance_), separatorAlgorithm_(original.separatorAlgorithm_->clone()), connectedComponentAlgorithm_(original.connectedComponentAlgorithm_->clone()), restrictedToLargestBags_(original.restrictedToLargestBags_)
    {

    }

    virtual ~Implementation()
    {
        delete separatorAlgorithm_;
        delete connectedComponentAlgorithm_;
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The algorithm for computing separating vertex sets.
     */
    htd::IGraphSeparatorAlgorithm * separatorAlgorithm_;

    /**
     *  The algorithm for computing connected components.
     */
    htd::IConnectedComponentAlgorithm * connectedComponentAlgorithm_;

    /**
     *  A boolean flag indicating whether only the largest bags of the decomposition shall be considered or all of them.
     */
    bool restrictedToLargestBags_;

    /**
     * Internal data structure for storing induced graphs.
     */
    class InducedGraph
    {
        public:
            /**
             *  Constructor for a new induced graph.
             *
             *  @param[in] graph            The graph for which the induced graph shall be constructed.
             *  @param[in] relevantVertices The vertices of the induced graph.
             */
            InducedGraph(const htd::IMultiHypergraph & graph, const std::vector<htd::vertex_t> & relevantVertices) : baseGraphToInducedGraphMapping_(), inducedGraphToBaseGraphMapping_(relevantVertices), graph_(graph.managementInstance()->multiGraphFactory().createInstance(relevantVertices.size()))
            {
                #ifndef NDEBUG
                for (htd::vertex_t vertex : relevantVertices)
                {
                    HTD_ASSERT(graph.isVertex(vertex))
                }
                #endif

                htd::index_t index = 0;

                for (htd::vertex_t vertex : relevantVertices)
                {
                    baseGraphToInducedGraphMapping_.emplace(vertex, index);

                    ++index;
                }

                for (auto it = relevantVertices.begin(); it != relevantVertices.end();)
                {
                    htd::vertex_t vertex = *it;

                    htd::vertex_t mappedVertex = baseGraphToInducedGraphMapping_.at(vertex) + 1;

                    const htd::ConstCollection<htd::vertex_t> & currentNeighborhood = graph.neighbors(vertex);

                    std::vector<htd::vertex_t> relevantNeighbors;

                    ++it;

                    std::set_intersection(currentNeighborhood.begin(), currentNeighborhood.end(), it, relevantVertices.end(), std::back_inserter(relevantNeighbors));

                    for (htd::vertex_t relevantNeighbor : relevantNeighbors)
                    {
                        graph_->addEdge(mappedVertex, baseGraphToInducedGraphMapping_.at(relevantNeighbor) + 1);
                    }
                }
            }

            /**
             *  Destructor for an induced graph.
             */
            ~InducedGraph()
            {
               delete graph_;
            }

            /**
             *  Getter for the number of vertices in the induced graph.
             *
             *  @return The number of vertices in the induced graph.
             */
            std::size_t vertexCount(void) const
            {
                return graph_->vertexCount();
            }

            /**
             *  Access the underlying IMultiGraph object.
             *
             *  @return The underlying IMultiGraph object.
             */
            const htd::IMultiGraph & internalGraph(void) const
            {
                return *graph_;
            }

            /**
             *  Create a clique in the induced graph.
             *
             *  @param[in] vertices The vertices of the induced graph which shall form a clique.
             */
            void createClique(const std::vector<htd::vertex_t> & vertices)
            {
                #ifndef NDEBUG
                for (htd::vertex_t vertex : vertices)
                {
                    HTD_ASSERT(graph_->isVertex(vertex))
                }
                #endif

                for (auto it = vertices.begin(); it != vertices.end();)
                {
                    htd::vertex_t vertex = *it;

                    ++it;

                    for (auto it2 = it; it2 != vertices.end(); ++it2)
                    {
                        if (!graph_->isNeighbor(vertex, *it2))
                        {
                            graph_->addEdge(vertex, *it2);
                        }
                    }
                }
            }

            /**
             *  Remove a vertex from the induced graph.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            void removeVertex(htd::vertex_t vertex)
            {
                HTD_ASSERT(graph_->isVertex(vertex))

                graph_->removeVertex(vertex);
            }

            /**
             *  Get the vertex of the base graph which corresponds to the given vertex of the induced graph.
             *
             *  @param[in] inducedGraphVertex   The vertex of the induced graph.
             *
             *  @return The vertex of the base graph which corresponds to the given vertex of the induced graph.
             */
            htd::vertex_t baseGraphVertex(htd::vertex_t inducedGraphVertex) const
            {
                return inducedGraphToBaseGraphMapping_[inducedGraphVertex - 1];
            }

            /**
             *  Get the vertex of the induced graph which corresponds to the given vertex of the base graph.
             *
             *  @param[in] baseGraphVertex  The vertex of the base graph.
             *
             *  @return The vertex of the induced graph which corresponds to the given vertex of the base graph.
             */
            htd::vertex_t inducedGraphVertex(htd::vertex_t baseGraphVertex) const
            {
                return baseGraphToInducedGraphMapping_.at(baseGraphVertex) + 1;
            }

        private:
            /**
             * A mapping from the base graph vertices to the vertices of the induced graph.
             */
            std::unordered_map<htd::vertex_t, htd::vertex_t> baseGraphToInducedGraphMapping_;

            /**
             * A mapping from the vertices of the induced graph to the base graph vertices.
             */
            std::vector<htd::vertex_t> inducedGraphToBaseGraphMapping_;

            /**
             * The induced graph.
             */
            htd::IMutableMultiGraph * graph_;
    };

    /**
     *  Check whether the given graph is complete.
     *
     *  @param[in] graph    The graph.
     *
     *  @return True if the given graph is complete, false otherwise.
     */
    bool isComplete(const htd::IGraphStructure & graph) const;

    /**
     *  Check whether a vertex is contained in a subtree of the given decomposition.
     *
     *  @param[in] decomposition    The decomposition.
     *  @param[in] root             The root of the subtree.
     *  @param[in] vertex           The vertex for which to check whether it is contained in the subtree.
     *
     *  @return True if the given vertex is contained in the subtree, false otherwise.
     */
    bool isInSubtree(const htd::ITreeDecomposition & decomposition, htd::vertex_t root, htd::vertex_t vertex) const;

    /**
     *  Remove unneccessary vertices from bags.
     *
     *  @param[in] graph            The graph from which the decomposition was computed.
     *  @param[in] decomposition    The decomposition which shall be updated.
     */
    void performCleanup(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const;

    /**
     *  Try to improve the bag size of the selected decomposition node.
     *
     *  @param[in] graph            The graph from which the decomposition was computed.
     *  @param[in] decomposition    The decomposition which shall be updated.
     *  @param[in] vertex           The selected node.
     *  @param[out] createdVertices A vector of vertices which were created by the manipulation operation.
     *  @param[out] removedVertices A vector of vertices which were removed by the manipulation operation.
     *
     *  @return True if the bag size of the selected decomposition node could be reduced, false otherwise.
     */
    bool processDecompositionNode(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, htd::vertex_t vertex, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const;

    /**
     *  Create the graph which corresponds to the bag of the selected decomposition node.
     *
     *  @param[in] graph            The graph from which the decomposition was computed.
     *  @param[in] decomposition    The decomposition.
     *  @param[in] vertex           The selected node.
     *
     *  @return The graph which corresponds to the bag of the selected decomposition node.
     */
    InducedGraph * createCorrespondingGraph(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex) const;
};

htd::WidthReductionOperation::WidthReductionOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::WidthReductionOperation::~WidthReductionOperation()
{

}

void htd::WidthReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::WidthReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::WidthReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    std::vector<htd::vertex_t> vertices;
    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    decomposition.copyVerticesTo(vertices);

    return apply(graph, decomposition, vertices, labelingFunctions, createdVertices, removedVertices);
}

void htd::WidthReductionOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    bool ok = true;

    std::unordered_set<htd::vertex_t> updatedRelevantVertices(relevantVertices.begin(), relevantVertices.end());

    while (ok)
    {
        ok = false;

        std::vector<htd::vertex_t> pool;

        if (implementation_->restrictedToLargestBags_)
        {
            std::size_t maxBagSize = 0;

            for (htd::vertex_t vertex : updatedRelevantVertices)
            {
                std::size_t currentBagSize = decomposition.bagSize(vertex);

                if (currentBagSize >= maxBagSize)
                {
                    if (currentBagSize > maxBagSize)
                    {
                        maxBagSize = currentBagSize;

                        pool.clear();
                    }

                    pool.push_back(vertex);
                }
            }
        }
        else
        {
            const htd::ConstCollection<htd::vertex_t> & vertexCollection = decomposition.vertices();

            std::set_intersection(vertexCollection.begin(), vertexCollection.end(), updatedRelevantVertices.begin(), updatedRelevantVertices.end(), std::back_inserter(pool));
        }

        for (htd::vertex_t vertex : pool)
        {
            if (implementation_->processDecompositionNode(graph, decomposition, vertex, createdVertices, removedVertices))
            {
                for (htd::vertex_t createdVertex : createdVertices)
                {
                    for (const htd::ILabelingFunction * labelingFunction : labelingFunctions)
                    {
                        htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(vertex);

                        htd::ILabel * newLabel = labelingFunction->computeLabel(decomposition.bagContent(vertex), *labelCollection);

                        delete labelCollection;

                        decomposition.setVertexLabel(labelingFunction->name(), createdVertex, newLabel);
                    }
                }

                for (htd::vertex_t removedVertex : removedVertices)
                {
                    updatedRelevantVertices.erase(removedVertex);
                }

                for (htd::vertex_t createdVertex : createdVertices)
                {
                    updatedRelevantVertices.insert(createdVertex);
                }

                createdVertices.clear();
                removedVertices.clear();

                ok = true;
            }
        }
    }
}

bool htd::WidthReductionOperation::isLocalOperation(void) const
{
    return false;
}

bool htd::WidthReductionOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::WidthReductionOperation::removesTreeNodes(void) const
{
    return true;
}

bool htd::WidthReductionOperation::modifiesBagContents(void) const
{
    return true;
}

bool htd::WidthReductionOperation::createsSubsetMaximalBags(void) const
{
    return true;
}

bool htd::WidthReductionOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::WidthReductionOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::WidthReductionOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

bool htd::WidthReductionOperation::isRestrictedToLargestBags(void) const
{
    return implementation_->restrictedToLargestBags_;
}

void htd::WidthReductionOperation::setRestrictedToLargestBags(bool restrictedToLargestBags)
{
    implementation_->restrictedToLargestBags_ = restrictedToLargestBags;
}

htd::WidthReductionOperation * htd::WidthReductionOperation::clone(void) const
{
    return new htd::WidthReductionOperation(implementation_->managementInstance_);
}

void htd::WidthReductionOperation::setGraphSeparatorAlgorithm(htd::IGraphSeparatorAlgorithm * algorithm)
{
    HTD_ASSERT(algorithm != nullptr)

    delete implementation_->separatorAlgorithm_;

    implementation_->separatorAlgorithm_ = algorithm;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::WidthReductionOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::WidthReductionOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

bool htd::WidthReductionOperation::Implementation::processDecompositionNode(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, htd::vertex_t vertex, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_ASSERT(decomposition.isVertex(vertex))

    bool ret = false;

    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(vertex);

    htd::WidthReductionOperation::Implementation::InducedGraph * inducedGraph = createCorrespondingGraph(graph, decomposition, vertex);

    if (!isComplete(inducedGraph->internalGraph()))
    {
        std::vector<htd::vertex_t> neighbors;
        decomposition.copyNeighborsTo(vertex, neighbors);

        std::vector<htd::vertex_t> * separator = separatorAlgorithm_->computeSeparator(inducedGraph->internalGraph());

        for (htd::vertex_t & separatingVertex : *separator)
        {
            inducedGraph->removeVertex(separatingVertex);

            separatingVertex = inducedGraph->baseGraphVertex(separatingVertex);
        }

        std::vector<std::vector<htd::vertex_t>> components;

        connectedComponentAlgorithm_->determineComponents(inducedGraph->internalGraph(), components);

        std::vector<htd::id_t> componentIdentifiers(components.size());

        htd::index_t index = 0;

        const htd::FilteredHyperedgeCollection & inducedEdges = decomposition.inducedHyperedges(vertex);

        std::vector<htd::vertex_t> relevantCreatedVertices;

        for (std::vector<htd::vertex_t> & component : components)
        {
            std::vector<htd::vertex_t> newBag;

            std::for_each(component.begin(), component.end(), [&](htd::vertex_t & componentVertex)
            {
                componentVertex = inducedGraph->baseGraphVertex(componentVertex);
            });

            std::set_union(component.begin(), component.end(), separator->begin(), separator->end(), std::back_inserter(newBag));

            auto position =
                std::find_if(neighbors.begin(), neighbors.end(), [&](htd::vertex_t neighbor)
                             {
                                const std::vector<htd::vertex_t> & neighborBagContent = decomposition.bagContent(neighbor);

                                return std::includes(neighborBagContent.begin(), neighborBagContent.end(), newBag.begin(), newBag.end());
                             });

            if (position != neighbors.end())
            {
                componentIdentifiers[index] = *position;
            }
            else
            {
                htd::FilteredHyperedgeCollection * relevantInducedEdges = inducedEdges.clone(newBag);

                htd::vertex_t newVertex = decomposition.addChild(vertex, std::move(newBag), *relevantInducedEdges);

                componentIdentifiers[index] = newVertex;

                relevantCreatedVertices.push_back(newVertex);

                delete relevantInducedEdges;
            }

            ++index;
        }

        decomposition.mutableInducedHyperedges(vertex).restrictTo(*separator);

        decomposition.mutableBagContent(vertex) = std::move(*separator);

        for (htd::vertex_t neighbor : neighbors)
        {
            const std::vector<htd::vertex_t> & neighborBagContent = decomposition.bagContent(neighbor);

            auto position =
                std::find_if(components.begin(), components.end(), [&](const std::vector<htd::vertex_t> & component)
                             {
                                return htd::has_non_empty_set_intersection(neighborBagContent.begin(), neighborBagContent.end(), component.begin(), component.end());
                             });

            if (position != components.end())
            {
                htd::vertex_t newParent = componentIdentifiers[std::distance(components.begin(), position)];

                if (neighbor != newParent)
                {
                    if (isInSubtree(decomposition, neighbor, newParent))
                    {
                        decomposition.swapWithParent(newParent);
                    }
                    else
                    {
                        decomposition.setParent(neighbor, newParent);
                    }
                }
            }
        }

        neighbors.clear();

        decomposition.copyNeighborsTo(vertex, neighbors);

        auto position =
            std::find_if(neighbors.begin(), neighbors.end(), [&](htd::vertex_t neighbor)
                         {
                            const std::vector<htd::vertex_t> & neighborBagContent = decomposition.bagContent(neighbor);

                            return std::includes(neighborBagContent.begin(), neighborBagContent.end(), bagContent.begin(), bagContent.end());
                         });

        if (position != neighbors.end())
        {
            std::vector<htd::vertex_t> children;
            decomposition.copyChildrenTo(vertex, children);

            for (htd::vertex_t child : children)
            {
                if (child != *position)
                {
                    decomposition.setParent(child, *position);
                }
            }

            for (htd::vertex_t createdVertex : relevantCreatedVertices)
            {
                if (createdVertex != *position)
                {
                    if (isInSubtree(decomposition, vertex, createdVertex))
                    {
                        decomposition.setParent(createdVertex, *position);
                    }
                }
            }

            decomposition.removeVertex(vertex);

            auto position2 = std::lower_bound(relevantCreatedVertices.begin(), relevantCreatedVertices.end(), vertex);

            if (position2 == relevantCreatedVertices.end() || *position2 != vertex)
            {
                removedVertices.push_back(vertex);
            }
            else
            {
                relevantCreatedVertices.erase(position2);
            }
        }

        createdVertices.insert(createdVertices.end(), relevantCreatedVertices.begin(), relevantCreatedVertices.end());

        ret = true;

        delete separator;
    }

    delete inducedGraph;

    return ret;
}

bool htd::WidthReductionOperation::Implementation::isComplete(const htd::IGraphStructure & graph) const
{
    bool ret = true;

    std::vector<htd::vertex_t> vertices;
    graph.copyVerticesTo(vertices);

    for (auto it = vertices.begin(); ret && it != vertices.end(); ++it)
    {
        const htd::ConstCollection<htd::vertex_t> & currentNeighborhood = graph.neighbors(*it);

        ret = htd::set_intersection_size(currentNeighborhood.begin(), currentNeighborhood.end(), vertices.begin(), vertices.end()) >= vertices.size() - 1;
    }

    return ret;
}

bool htd::WidthReductionOperation::Implementation::isInSubtree(const htd::ITreeDecomposition & decomposition, htd::vertex_t root, htd::vertex_t vertex) const
{
    HTD_ASSERT(decomposition.isVertex(root) && decomposition.isVertex(vertex))

    bool ret = false;

    htd::vertex_t current = vertex;

    htd::vertex_t decompositionRoot = decomposition.root();

    while (!ret && current != decompositionRoot)
    {
        ret = current == root;

        current = decomposition.parent(current);
    }

    return ret || current == root;
}

htd::WidthReductionOperation::Implementation::InducedGraph * htd::WidthReductionOperation::Implementation::createCorrespondingGraph(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex) const
{
    HTD_ASSERT(decomposition.isVertex(vertex))

    const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(vertex);

    htd::WidthReductionOperation::Implementation::InducedGraph * ret = new htd::WidthReductionOperation::Implementation::InducedGraph(graph, bagContent);

    std::vector<htd::vertex_t> neighbors;
    decomposition.copyNeighborsTo(vertex, neighbors);

    for (htd::vertex_t neighbor : neighbors)
    {
        const std::vector<htd::vertex_t> & neighborBagContent = decomposition.bagContent(neighbor);

        std::vector<htd::vertex_t> relevantBagContent;

        std::set_intersection(neighborBagContent.begin(), neighborBagContent.end(), bagContent.begin(), bagContent.end(), std::back_inserter(relevantBagContent));

        std::for_each(relevantBagContent.begin(), relevantBagContent.end(), [&](htd::vertex_t & bagElement)
        {
            bagElement = ret->inducedGraphVertex(bagElement);
        });

        ret->createClique(relevantBagContent);
    }

    return ret;
}

#endif /* HTD_HTD_WIDTHREDUCTIONOPERATION_CPP */
