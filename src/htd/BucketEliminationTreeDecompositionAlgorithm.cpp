/* 
 * File:   BucketEliminationTreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/Converters.hpp>
#include <htd/VertexContainerLabel.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabelingFunction.hpp>

#include <algorithm>
#include <cstdarg>
#include <stdexcept>
#include <unordered_set>
#include <stack>
#include <utility>
#include <vector>
#include <tuple>

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm) : orderingAlgorithm_(orderingAlgorithm)
{

}

htd::BucketEliminationTreeDecompositionAlgorithm::BucketEliminationTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm, const std::vector<htd::ILabelingFunction *> & labelingFunctions) : orderingAlgorithm_(orderingAlgorithm)
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::BucketEliminationTreeDecompositionAlgorithm::~BucketEliminationTreeDecompositionAlgorithm()
{
    
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    htd::IMutableTreeDecomposition * ret = computeMutableDecomposition(graph);

    if (ret != nullptr)
    {
        compressDecomposition(*ret);
    }

    return ret;
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::IMutableTreeDecomposition * ret = computeMutableDecomposition(graph);

    if (ret != nullptr)
    {
        compressDecomposition(*ret);

        for (auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                auto label = (dynamic_cast<const htd::VertexContainerLabel *>(&(ret->label(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex))))->container();

                htd::ILabelCollection * labelCollection = ret->labelings().exportLabelCollection(vertex);

                //TODO Optimize (Use htd::Collection<T> as first parameter)
                htd::ILabel * newLabel = labelingFunction->computeLabel(label, *labelCollection);

                delete labelCollection;

                ret->setLabel(labelingFunction->name(), vertex, newLabel);
            }
        }
    }

    if (ret != nullptr)
    {
        compressDecomposition(*ret);
    }

    return ret;
}

htd::ITreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const
{
    va_list arguments;

    va_start(arguments, labelingFunctionCount);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    for (int labelingFunctionIndex = 0; labelingFunctionIndex < labelingFunctionCount; labelingFunctionIndex++)
    {
        labelingFunctions.push_back(va_arg(arguments, htd::ILabelingFunction *));
    }

    return computeDecomposition(graph, labelingFunctions);
}

htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::computeMutableDecomposition(const htd::IHypergraph & graph) const
{
    htd::IMutableTreeDecomposition * ret = nullptr;

    std::size_t size = graph.vertexCount();

    if (size > 0)
    {
        std::size_t index = 0;

        std::vector<htd::vertex_t> ordering;

        orderingAlgorithm_.computeOrdering(graph, ordering);

        if (ordering.size() == size)
        {
            std::vector<htd::index_t> indices(size);

            //std::vector<htd::vertex_t> vertexLabels(size, htd::Vertex::UNKNOWN);

            std::vector<htd::vertex_container> buckets(size);

            std::vector<htd::id_t> relevantBuckets;

            std::unordered_set<htd::vertex_t> isolatedVertices(ordering.begin(), ordering.end());

            DEBUGGING_CODE(std::cout << "Ordering:" << std::endl;

            for (htd::vertex_t vertex : ordering)
            {
                std::cout << vertex << std::endl;
            })

            for (htd::vertex_t vertex : ordering)
            {
                indices[vertex - htd::Vertex::FIRST] = index++;
            }

            for (std::size_t index = 0; index < size; index++)
            {
                buckets[index].push_back(index + htd::Vertex::FIRST);
            }

            for (htd::hyperedge_t edge : graph.hyperedges())
            {
                htd::vertex_t minimumVertex = getMinimumVertex(edge, indices);

                auto& selectedBucket = buckets[minimumVertex - htd::Vertex::FIRST];

                std::vector<htd::vertex_t> newBucketContent;
                newBucketContent.reserve(selectedBucket.size());

                /*
                if (vertexLabels[minimumVertex - htd::Vertex::FIRST] == htd::unknown_id)
                {
                    relevantBuckets.push_back(minimumVertex);
                }
                */

                if (edge.size() > 1)
                {
                    for (htd::vertex_t vertex : edge)
                    {
                        isolatedVertices.erase(vertex);
                    }
                }

                //vertexLabels[minimumVertex - htd::Vertex::FIRST] = minimumVertex;

                std::set_union(selectedBucket.begin(), selectedBucket.end(), edge.begin(), edge.end(), std::back_inserter(newBucketContent));

                std::swap(selectedBucket, newBucketContent);
            }

            if (isolatedVertices.size() > 0)
            {
                for (htd::vertex_t vertex : isolatedVertices)
                {
                    relevantBuckets.push_back(vertex);
                }
            }

            //TODO
            relevantBuckets.clear();
            std::copy(ordering.begin(), ordering.end(), std::back_inserter(relevantBuckets));

            std::sort(relevantBuckets.begin(), relevantBuckets.end());

            DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
            for (std::size_t index = 0; index < size; index++)
            {
                std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
                htd::print(buckets[index], false);
                std::cout << std::endl;
            })

            DEBUGGING_CODE(std::cout << std::endl << "Relevant Buckets:" << std::endl;
            for (htd::id_t bucket : relevantBuckets)
            {
                std::cout << "   Bucket " << bucket << ": ";
                htd::print(buckets[bucket - htd::Vertex::FIRST], false);
                std::cout << std::endl;
            })

            DEBUGGING_CODE(std::cout << std::endl << "Connections:" << std::endl;)

            std::size_t edgeCount = 0;

            std::vector<htd::vertex_t> tmp;
            std::vector<std::vector<htd::vertex_t>> neighbors(size);

            for (std::size_t index = 0; index < size; index++)
            {
                tmp.clear();

                htd::vertex_t selection = ordering[index];

                DEBUGGING_CODE(std::cout << std::endl << "   Processing bucket " << selection << " ..." << std::endl;)

                for (htd::vertex_t vertex : buckets[selection - htd::Vertex::FIRST])
                {
                    if (vertex != selection)
                    {
                        tmp.push_back(vertex);
                    }
                }

                if (tmp.size() > 0)
                {
                    DEBUGGING_CODE(
                        std::cout << "      Bucket " << selection << ": ";
                        htd::print(tmp, false);
                        std::cout << std::endl;
                    )

                    htd::vertex_t minimumVertex = getMinimumVertex(tmp, indices);

                    DEBUGGING_CODE(
                        std::cout << "      Minimum Vertex: " << minimumVertex << std::endl;

                        if (minimumVertex < selection)
                        {
                            std::cout << "      Connection: " << minimumVertex << " - " << selection << std::endl;
                        }
                        else
                        {
                            std::cout << "      Connection: " << selection << " - " << minimumVertex << std::endl;
                        }
                    )

                    auto& selectedBucket = buckets[minimumVertex - htd::Vertex::FIRST];

                    std::vector<htd::vertex_t> newBucketContent;
                    newBucketContent.reserve(selectedBucket.size());

                    std::set_union(selectedBucket.begin(), selectedBucket.end(), tmp.begin(), tmp.end(), std::back_inserter(newBucketContent));

                    std::swap(selectedBucket, newBucketContent);

                    //TODO
                    /*
                    htd::id_t selectionLabel = labels[selection];
                    htd::id_t minimumVertexLabel = labels[minimumVertex];

                    if (minimumVertexLabel != htd::unknown_id && selectionLabel != htd::unknown_id)
                    {
                        ++edgeCount;

                        neighbors[selectionLabel].push_back(minimumVertexLabel);
                        neighbors[minimumVertexLabel].push_back(selectionLabel);
                    }
                    */

                    neighbors[selection - htd::Vertex::FIRST].push_back(minimumVertex);
                    neighbors[minimumVertex - htd::Vertex::FIRST].push_back(selection);
                }
            }

            DEBUGGING_CODE(std::cout << std::endl << "Buckets:" << std::endl;
            for (std::size_t index = 0; index < size; index++)
            {
                std::cout << "   Bucket " << index + htd::Vertex::FIRST << ": ";
                htd::print(buckets[index], false);
                std::cout << std::endl;
            })

            DEBUGGING_CODE(std::cout << std::endl << "Relevant Buckets:" << std::endl;
            for (htd::id_t bucket : relevantBuckets)
            {
                std::cout << "   Bucket " << bucket << ": ";
                htd::print(buckets[bucket - htd::Vertex::FIRST], false);
                std::cout << std::endl;
            })

            //TODO Selection of root
            htd::vertex_t root = relevantBuckets[0];

            if (edgeCount < relevantBuckets.size() - 1)
            {
                std::vector<htd::index_t> bucketIndices(size);

                std::vector<htd::vertex_t> unreachableVertices;

                htd::index_t currentIndex = 0;

                for (htd::vertex_t bucket : relevantBuckets)
                {
                    bucketIndices[bucket - htd::Vertex::FIRST] = currentIndex;

                    ++currentIndex;
                }

                getUnreachableVertices(root, relevantBuckets, bucketIndices, neighbors, unreachableVertices);

                while (unreachableVertices.size() > 0)
                {
                    std::size_t bestOverlap = 0;
                    htd::vertex_t bestBucket = htd::Vertex::UNKNOWN;
                    htd::vertex_t currentBucket = unreachableVertices[0];

                    auto& currentBucketContent = buckets[currentBucket - htd::Vertex::FIRST];

                    std::vector<htd::vertex_t> reachableVertices;

                    getReachableVertices(currentBucket, relevantBuckets, bucketIndices, neighbors, reachableVertices);

                    auto it = reachableVertices.begin();
                    auto last = reachableVertices.end();

                    for (htd::vertex_t bucket : relevantBuckets)
                    {
                        while (it != last && bucket > *it)
                        {
                            it++;
                        }

                        if (it == last || bucket < *it)
                        {
                            auto& bucketContent = buckets[bucket - htd::Vertex::FIRST];

                            std::size_t currentOverlap = htd::compute_set_intersection_size(currentBucketContent.begin(), currentBucketContent.end(), bucketContent.begin(), bucketContent.end());

                            //TODO Keep options of same quality and select (randomly) from this pool?
                            if (currentOverlap > bestOverlap)
                            {
                                bestBucket = bucket;
                                bestOverlap = currentOverlap;
                            }
                        }
                    }

                    if (bestBucket == htd::Vertex::UNKNOWN)
                    {
                        bestBucket = root;
                    }

                    DEBUGGING_CODE(std::cout << std::endl << "Unreachable Vertices: " << unreachableVertices.size() << std::endl;)

                    if (unreachableVertices.size() > 1)
                    {
                        std::vector<htd::vertex_t> newUnreachableVertices;

                        std::set_difference(unreachableVertices.begin(), unreachableVertices.end(), reachableVertices.begin(), reachableVertices.end(), std::back_inserter(newUnreachableVertices));

                        unreachableVertices.clear();

                        std::swap(unreachableVertices, newUnreachableVertices);
                    }
                    else
                    {
                        unreachableVertices.clear();
                    }

                    neighbors[bestBucket - htd::Vertex::FIRST].push_back(currentBucket);
                    neighbors[currentBucket - htd::Vertex::FIRST].push_back(bestBucket);
                }
            }

            ret = createRootedTreeDecomposition(relevantBuckets[root - htd::Vertex::FIRST], neighbors, buckets);
        }
    }
    else
    {
        ret = htd::getDefaultTreeDecomposition();

        ret->insertRoot();
    }

    return ret;
}

htd::vertex_t htd::BucketEliminationTreeDecompositionAlgorithm::getMinimumVertex(const htd::hyperedge_t & edge, const std::vector<htd::index_t> & vertexIndices) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (edge.size() > 0)
    {
        std::size_t minimum = (std::size_t)-1;

        std::size_t currentIndex = (std::size_t)-1;

        for (htd::vertex_t vertex : edge)
        {
            currentIndex = vertexIndices[vertex - htd::Vertex::FIRST];

            if (currentIndex < minimum)
            {
                ret = vertex;

                minimum = currentIndex;
            }
        }
    }
    else
    {
        throw std::out_of_range("htd::BucketEliminationTreeDecompositionAlgorithm::getMinimumVertex(const htd::hyperedge_t&, const std::vector<htd::index_t>&) const");
    }

    return ret;
}

//TODO Optimize (Use stack approach - Tarjan's Algorithm)
//TODO Export as global helper function
void htd::BucketEliminationTreeDecompositionAlgorithm::getReachableVertices(htd::vertex_t start, const htd::vertex_container & vertices, const std::vector<htd::index_t> & vertexIndices, const std::vector<htd::vertex_container> & neighbors, htd::vertex_container & output) const
{
    std::size_t size = vertices.size();

    if (size > 0)
    {
        htd::vertex_t vertex = htd::Vertex::UNKNOWN;

        htd::vertex_container newVertices;
        htd::vertex_container tmpVertices;

        std::vector<bool> reachableVertices(size, false);

        reachableVertices[vertexIndices[start - htd::Vertex::FIRST]] = true;

        newVertices.push_back(start);

        output.push_back(start);

        while (newVertices.size() > 0)
        {
            std::swap(tmpVertices, newVertices);

            newVertices.clear();

            for (auto index : tmpVertices)
            {
                vertex = vertices[vertexIndices[index - htd::Vertex::FIRST]];

                for (htd::vertex_t neighbor : neighbors[vertex - htd::Vertex::FIRST])
                {
                    htd::index_t vertexIndex = vertexIndices[neighbor - htd::Vertex::FIRST];

                    if (!reachableVertices[vertexIndex])
                    {
                        reachableVertices[vertexIndex] = true;

                        output.push_back(neighbor);

                        newVertices.push_back(neighbor);
                    }
                }
            }
        }

        std::sort(output.begin(), output.end());
    }
}

void htd::BucketEliminationTreeDecompositionAlgorithm::getUnreachableVertices(htd::vertex_t start, const htd::vertex_container & vertices, const std::vector<htd::index_t> & vertexIndices, const std::vector<htd::vertex_container> & neighbors, htd::vertex_container & output) const
{
    std::size_t size = vertices.size();

    if (size > 0)
    {
        htd::vertex_container reachableVertices;

        getReachableVertices(start, vertices, vertexIndices, neighbors, reachableVertices);

        std::set_difference(vertices.begin(), vertices.end(), reachableVertices.begin(), reachableVertices.end(), std::back_inserter(output));
    }
}

htd::IMutableTreeDecomposition * htd::BucketEliminationTreeDecompositionAlgorithm::createRootedTreeDecomposition(htd::vertex_t root, const std::vector<htd::vertex_container> & neighbors, const std::vector<std::vector<htd::id_t>> & buckets) const
{
    htd::IMutableTreeDecomposition * ret = htd::getDefaultTreeDecomposition();

    if (root != htd::Vertex::UNKNOWN)
    {
        htd::index_t currentIndex = 0;

        htd::vertex_t currentNode = root;

        htd::vertex_t decompositionNode = ret->insertRoot();

        std::unordered_set<htd::vertex_t> visited(neighbors.size());

        std::stack<std::tuple<htd::vertex_t, htd::index_t, htd::vertex_t>> parentStack;

        while (parentStack.size() > 0 || currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentNode != htd::Vertex::UNKNOWN)
            {
                const std::vector<htd::vertex_t>& currentNeighborhood = neighbors[currentNode - htd::Vertex::FIRST];

                if (visited.find(currentNode) == visited.end())
                {
                    ret->setLabel(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, decompositionNode,
                                  new htd::VertexContainerLabel(htd::vertex_container(buckets[currentNode - htd::Vertex::FIRST].begin(),
                                                                                      buckets[currentNode - htd::Vertex::FIRST].end())));

                    visited.insert(currentNode);
                }

                if (currentIndex < currentNeighborhood.size())
                {
                    parentStack.push(std::make_tuple(currentNode, currentIndex + 1, decompositionNode));

                    if (visited.find(currentNeighborhood[currentIndex]) == visited.end())
                    {
                        currentNode = currentNeighborhood[currentIndex];

                        currentIndex = 0;
                        
                        decompositionNode = ret->addChild(decompositionNode);
                    }
                    else
                    {
                        currentNode = htd::Vertex::UNKNOWN;
                    }
                }
                else
                {
                    currentNode = htd::Vertex::UNKNOWN;
                }
            }
            else
            {
                currentNode = std::get<0>(parentStack.top());

                currentIndex = std::get<1>(parentStack.top());
                
                decompositionNode = std::get<2>(parentStack.top());
                        
                parentStack.pop();
            }
        }
    }
    
    return ret;
}

void htd::BucketEliminationTreeDecompositionAlgorithm::compressDecomposition(htd::IMutableTreeDecomposition & decomposition) const
{
    if (decomposition.vertexCount() > 1)
    {
        std::size_t childCount = 0;

        htd::index_t currentIndex = 0;

        htd::vertex_t oldNode = htd::Vertex::UNKNOWN;

        htd::vertex_t currentNode = decomposition.root();

        std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

        htd::vertex_container unneededVertices;

        while (parentStack.size() > 0 || currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentNode != htd::Vertex::UNKNOWN)
            {
                childCount = decomposition.childCount(currentNode);

                if (currentIndex < childCount)
                {
                    oldNode = currentNode;

                    Collection<htd::vertex_t> label = decomposition.bagContent(currentNode);

                    parentStack.push(std::make_pair(currentNode, currentIndex + 1));

                    currentNode = decomposition.child(currentNode, currentIndex);

                    currentIndex = 0;

                    Collection<htd::vertex_t> childLabel = decomposition.bagContent(currentNode);

                    if (childLabel.size() < label.size())
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), currentNode) == unneededVertices.end() && std::includes(label.begin(), label.end(), childLabel.begin(), childLabel.end()))
                        {
                            unneededVertices.push_back(currentNode);
                        }
                    }
                    else
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), oldNode) == unneededVertices.end() && std::includes(childLabel.begin(), childLabel.end(), label.begin(), label.end()))
                        {
                            unneededVertices.push_back(oldNode);
                        }
                    }
                }
                else
                {
                    currentNode = htd::Vertex::UNKNOWN;
                }
            }
            else
            {
                currentNode = parentStack.top().first;

                currentIndex = parentStack.top().second;

                parentStack.pop();
            }
        }

        for (htd::vertex_t vertex : unneededVertices)
        {
            /*
            std::cout << "ELIMINATING VERTEX " << vertex << " (CHILDREN: " << decomposition.childCount(vertex) << ")" << std::endl;
            std::vector<htd::vertex_t> childrenTMP;
            decomposition.getChildren(vertex, childrenTMP);
            for (auto child : childrenTMP)
            {
                htd::vertex_container label;
                decomposition.getVertexLabel(child, label);
                
                std::cout << "   CHILD: VERTEX " << child << "   ";
                htd::print(label, false);
                std::cout << std::endl;
            }
            */
            
            if (decomposition.childCount(vertex) <= 1)
            {
                decomposition.removeVertex(vertex);
            }
            else
            {
                std::vector<htd::vertex_t> children;

                const htd::Collection<htd::vertex_t> label = decomposition.bagContent(vertex);

                const htd::Collection<htd::vertex_t> childContainer = decomposition.children(vertex);

                std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

                for (htd::vertex_t child : children)
                {
                    Collection<htd::vertex_t> childLabel = decomposition.bagContent(child);

                    if (std::includes(label.begin(), label.end(), childLabel.begin(), childLabel.end()))
                    {
                        decomposition.removeVertex(child);
                    }
                    else
                    {
                        /*
                        if (std::includes(childLabel.begin(), childLabel.end(), label.begin(), label.end()))
                        {
                            std::cout << "SWAP NODES " << child << " AND " << vertex << " (ERASE NODE " << vertex << ")" << std::endl;
                            
                            //TODO Optimize
                            decomposition.swapLabels(vertex, child);
                            
                            decomposition.removeVertex(child);
                        }
                        */
                    }
                }
            }
        }
            
        DEBUGGING_CODE(std::cout << std::endl;)
    }
}

#endif /* HTD_HTD_BUCKETELIMINATIONTREEDECOMPOSITIONALGORITHM_CPP */
