/*
 * File:   JoinNodeReplacementOperation.cpp
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

#ifndef HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP
#define HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/JoinNodeReplacementOperation.hpp>

#include <algorithm>
#include <stack>
#include <unordered_set>
#include <vector>

/**
 *  Private implementation details of class htd::JoinNodeReplacementOperation.
 */
struct htd::JoinNodeReplacementOperation::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  Get the set union of all child bags of a given vertex.
     *
     *  @param[in] decomposition    The decomposition.
     *  @param[in] vertex           The vertex which child bags shall be merged.
     *  @param[out] output          The target vector to which the result shall be appended.
     */
    void getChildrenVertexLabelSetUnion(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex, std::vector<htd::vertex_t> & output) const;
};

/**
 *  Internal data structure for the pre-order traversal of the tree decomposition.
 */
struct HistoryEntry
{
    /**
     *  The decomposition node under focus.
     */
    htd::vertex_t vertex;

    /**
     *  The number of times how often the node was visited.
     */
    std::size_t visits;

    /**
     *  The collection of vertices which are still required by another child of a join node.
     */
    std::vector<htd::vertex_t> requiredVertices;

    /**
     *  The collection of children which are available to be assigned as new child of the resulting path node.
     */
    std::unordered_set<htd::vertex_t> availableChildren;

    /**
     *  Constructor of a history entry for the tree traversal.
     *
     *  @param[in] currentVertex    The decomposition node under focus.
     *  @param[in] visits           The number of times how often the node was visited.
     */
    HistoryEntry(htd::vertex_t currentVertex, std::size_t visits) : vertex(currentVertex), visits(visits), requiredVertices(), availableChildren()
    {

    }
};

htd::JoinNodeReplacementOperation::JoinNodeReplacementOperation(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::JoinNodeReplacementOperation::~JoinNodeReplacementOperation()
{

}

void htd::JoinNodeReplacementOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition) const
{
    apply(graph, decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::JoinNodeReplacementOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    apply(graph, decomposition, relevantVertices, std::vector<htd::ILabelingFunction *>(), createdVertices, removedVertices);
}

void htd::JoinNodeReplacementOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(graph)

    if (decomposition.vertexCount() > 0)
    {
        std::size_t currentVisits = 0;

        htd::vertex_t currentNode = decomposition.root();

        htd::vertex_t attachmentPoint = htd::Vertex::UNKNOWN;

        std::stack<HistoryEntry> parentStack;

        std::vector<htd::vertex_t> requiredVertices;

        const htd::ConstCollection<htd::vertex_t> & childCollection = decomposition.children(currentNode);

        std::unordered_set<htd::vertex_t> availableChildren(childCollection.begin(), childCollection.end());

        while (parentStack.size() > 0 || currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentNode != htd::Vertex::UNKNOWN)
            {
                DEBUGGING_CODE(std::cout << std::endl << std::endl << "NODE: " << currentNode << std::endl;)

                if (currentVisits == 0)
                {
                    if (attachmentPoint != htd::Vertex::UNKNOWN && decomposition.parent(currentNode) != attachmentPoint)
                    {
                        DEBUGGING_CODE(std::cout << "   ATTACH " << currentNode << " TO " << attachmentPoint << std::endl;)

                        decomposition.setParent(currentNode, attachmentPoint);
                    }

                    attachmentPoint = currentNode;
                }

                if (!availableChildren.empty())
                {
                    htd::vertex_t selectedChild = *(availableChildren.begin());

                    std::unordered_set<htd::vertex_t> newAvailableChildren(availableChildren);

                    newAvailableChildren.erase(selectedChild);

                    availableChildren.erase(selectedChild);

                    DEBUGGING_CODE(
                    std::cout << "   SELECTED CHILD: " << selectedChild << std::endl;
                    std::cout << "   REMAINING CHILDREN: ";
                    htd::print(availableChildren, true);
                    std::cout << std::endl;

                    std::cout << "OLD REQUIRED VERTICES " << currentNode << ": ";
                    htd::print(requiredVertices, false);
                    std::cout << std::endl << std::endl;
                    )

                    std::vector<htd::vertex_t> newRequiredVertices;

                    const htd::ConstCollection<htd::vertex_t> & rememberedVertexCollection = decomposition.rememberedVertices(currentNode);

                    std::set_union(requiredVertices.begin(), requiredVertices.end(), rememberedVertexCollection.begin(), rememberedVertexCollection.end(), std::back_inserter(newRequiredVertices));

                    DEBUGGING_CODE(
                    std::cout << "NEW REQUIRED VERTICES " << currentNode << ": ";
                    htd::print(newRequiredVertices, false);
                    std::cout << std::endl << std::endl;
                    )

                    std::swap(requiredVertices, newRequiredVertices);

                    //TODO Fix!
                    /*
                    if (availableChildren.empty())
                    {
                        if (attachmentPoint == decomposition.parent(selectedChild))
                        {
                            htd::Collection<htd::vertex_t> introducedVertexCollection = decomposition.introducedVertices(currentNode, selectedChild);

                            std::cout << "   INTRODUCED VERTICES: ";
                            htd::print(introducedVertexCollection, false);
                            std::cout << std::endl;

                            std::vector<htd::vertex_t> newRequiredVertices2;

                            std::set_difference(requiredVertices.begin(), requiredVertices.end(), introducedVertexCollection.begin(), introducedVertexCollection.end(), std::back_inserter(newRequiredVertices));

                            std::swap(requiredVertices, newRequiredVertices2);
                        }
                    }
                    */

                    parentStack.push(HistoryEntry(currentNode, currentVisits + 1));

                    parentStack.top().availableChildren = newAvailableChildren;

                    parentStack.top().requiredVertices = requiredVertices;

                    currentNode = selectedChild;

                    availableChildren.clear();

                    const htd::ConstCollection<htd::vertex_t> & newChildCollection = decomposition.children(currentNode);

                    availableChildren.insert(newChildCollection.begin(), newChildCollection.end());

                    if (requiredVertices.size() > 0)
                    {
                        const std::vector<htd::vertex_t> & bagContent = decomposition.bagContent(currentNode);

                        std::vector<htd::vertex_t> newBagContent;

                        DEBUGGING_CODE(
                        std::cout << "OLD BAG CONTENT " << currentNode << ": ";
                        htd::print(bagContent, false);
                        std::cout << std::endl << std::endl;
                        )

                        std::set_union(bagContent.begin(), bagContent.end(), requiredVertices.begin(), requiredVertices.end(), std::back_inserter(newBagContent));

                        DEBUGGING_CODE(
                        std::cout << "NEW BAG CONTENT " << currentNode << ": ";
                        htd::print(newBagContent, false);
                        std::cout << std::endl << std::endl;
                        )

                        decomposition.mutableBagContent(currentNode) = newBagContent;

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(currentNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newBagContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), currentNode, newLabel);
                        }
                    }

                    currentVisits = 0;
                }
                else
                {
                    currentNode = htd::Vertex::UNKNOWN;
                }
            }
            else
            {
                DEBUGGING_CODE(
                std::cout << "   BACKTRACKING TO " << parentStack.top().vertex << std::endl;

                std::cout << "   REQUIRED VERTICES 1: ";
                htd::print(requiredVertices, false);
                std::cout << std::endl;
                )

                currentNode = parentStack.top().vertex;

                currentVisits = parentStack.top().visits;

                requiredVertices = parentStack.top().requiredVertices;

                availableChildren = parentStack.top().availableChildren;

                parentStack.pop();

                DEBUGGING_CODE(
                std::cout << "   REQUIRED VERTICES 2: ";
                htd::print(requiredVertices, false);
                std::cout << std::endl;
                )

                if (currentNode != decomposition.root())
                {
                    std::vector<htd::vertex_t> potentiallyUnneededVertices;

                    std::set_difference(requiredVertices.begin(), requiredVertices.end(), parentStack.top().requiredVertices.begin(), parentStack.top().requiredVertices.end(), std::back_inserter(potentiallyUnneededVertices));

                    DEBUGGING_CODE(
                    std::cout << "POTENTIALLY UNNEEDED VERTICES: ";
                    htd::print(potentiallyUnneededVertices, false);
                    std::cout << std::endl;
                    )

                    std::unordered_set<htd::vertex_t> unneededVertices(potentiallyUnneededVertices.begin(), potentiallyUnneededVertices.end());

                    for (htd::vertex_t child : availableChildren)
                    {
                        const std::vector<htd::vertex_t> & childBagContent = decomposition.bagContent(child);

                        DEBUGGING_CODE(
                        std::cout << "   SIBLING: " << child << std::endl;
                        std::cout << "      CONTENT: ";
                        htd::print(childBagContent);
                        std::cout << std::endl;
                        )

                        for (htd::vertex_t requiredVertex : childBagContent)
                        {
                            unneededVertices.erase(requiredVertex);
                        }
                    }

                    std::vector<htd::vertex_t> unneededVertices2(unneededVertices.begin(), unneededVertices.end());

                    std::sort(unneededVertices2.begin(), unneededVertices2.end());

                    DEBUGGING_CODE(
                    std::cout << "   REQUIRED VERTICES: ";
                    htd::print(requiredVertices, false);
                    std::cout << std::endl;

                    std::cout << "   UNNEEDED VERTICES: ";
                    htd::print(unneededVertices2, false);
                    std::cout << std::endl;
                    )

                    std::vector<htd::vertex_t> newRequiredVertices;

                    std::set_difference(requiredVertices.begin(), requiredVertices.end(), unneededVertices2.begin(), unneededVertices2.end(), std::back_inserter(newRequiredVertices));

                    DEBUGGING_CODE(
                    std::cout << "   NEW REQUIRED VERTICES: ";
                    htd::print(newRequiredVertices, false);
                    std::cout << std::endl;
                    )

                    requiredVertices = newRequiredVertices;
                }
            }
        }
    }
}

void htd::JoinNodeReplacementOperation::apply(const htd::IMultiHypergraph & graph, htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions, std::vector<htd::vertex_t> & createdVertices, std::vector<htd::vertex_t> & removedVertices) const
{
    HTD_UNUSED(relevantVertices)
    HTD_UNUSED(createdVertices)
    HTD_UNUSED(removedVertices)

    apply(graph, decomposition, labelingFunctions);
}

bool htd::JoinNodeReplacementOperation::isLocalOperation(void) const
{
    return true;
}

bool htd::JoinNodeReplacementOperation::createsTreeNodes(void) const
{
    return true;
}

bool htd::JoinNodeReplacementOperation::removesTreeNodes(void) const
{
    return true;
}

bool htd::JoinNodeReplacementOperation::modifiesBagContents(void) const
{
    return true;
}

bool htd::JoinNodeReplacementOperation::createsSubsetMaximalBags(void) const
{
    return true;
}

bool htd::JoinNodeReplacementOperation::createsLocationDependendLabels(void) const
{
    return false;
}

const htd::LibraryInstance * htd::JoinNodeReplacementOperation::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::JoinNodeReplacementOperation::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::JoinNodeReplacementOperation * htd::JoinNodeReplacementOperation::clone(void) const
{
    return new htd::JoinNodeReplacementOperation(managementInstance());
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IDecompositionManipulationOperation * htd::JoinNodeReplacementOperation::cloneDecompositionManipulationOperation(void) const
{
    return clone();
}

htd::ITreeDecompositionManipulationOperation * htd::JoinNodeReplacementOperation::cloneTreeDecompositionManipulationOperation(void) const
{
    return clone();
}
#endif

void htd::JoinNodeReplacementOperation::Implementation::getChildrenVertexLabelSetUnion(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex, std::vector<htd::vertex_t> & output) const
{
    std::unordered_set<htd::vertex_t> result;

    for (htd::vertex_t child : decomposition.children(vertex))
    {
        const std::vector<htd::vertex_t> & childLabel = decomposition.bagContent(child);

        result.insert(childLabel.begin(), childLabel.end());
    }

    output.reserve(result.size());

    output.insert(output.end(), result.begin(), result.end());

    std::sort(output.begin(), output.end());

    output.erase(std::unique(output.begin(), output.end()), output.end());
}

#endif /* HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP */
