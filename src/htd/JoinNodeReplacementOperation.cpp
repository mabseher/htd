/*
 * File:   JoinNodeReplacementOperation.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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
#define	HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/JoinNodeReplacementOperation.hpp>

#include <algorithm>
#include <stack>
#include <unordered_set>
#include <vector>

struct HistoryEntry
{
    std::size_t visits;
    htd::vertex_t vertex;

    std::vector<htd::vertex_t> requiredVertices;

    std::unordered_set<htd::vertex_t> availableChildren;

    HistoryEntry(htd::vertex_t currentVertex, std::size_t visits) : visits(visits), vertex(currentVertex), requiredVertices(), availableChildren()
    {

    }
};

htd::JoinNodeReplacementOperation::JoinNodeReplacementOperation(void)
{

}

htd::JoinNodeReplacementOperation::~JoinNodeReplacementOperation()
{

}

void htd::JoinNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::JoinNodeReplacementOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
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
                    if (availableChildren.size() == 0)
                    {
                        if (attachmentPoint == decomposition.parent(selectedChild))
                        {
                            htd::Collection<htd::vertex_t> introducedVertexCollection = decomposition.introducedVertices(currentNode, selectedChild);

                            std::cout << "   INTRODUCED VERTICES: ";
                            htd::print(introducedVertexCollection, false);
                            std::cout << std::endl;

                            htd::vertex_container newRequiredVertices2;

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
                        const htd::ConstCollection<htd::vertex_t> & bagContent = decomposition.bagContent(currentNode);

                        htd::vertex_container newBagContent;

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

                        decomposition.setBagContent(currentNode, newBagContent);

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(currentNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(htd::ConstCollection<htd::vertex_t>::getInstance(newBagContent), *labelCollection);

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
                        const htd::ConstCollection<htd::vertex_t> & childBagContent = decomposition.bagContent(child);

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

void htd::JoinNodeReplacementOperation::getChildrenVertexLabelSetUnion(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex, htd::vertex_container & output) const
{
    std::unordered_set<htd::vertex_t> result;

    for (htd::vertex_t child : decomposition.children(vertex))
    {
        const htd::ConstCollection<htd::vertex_t> & childLabel = decomposition.bagContent(child);

        result.insert(childLabel.begin(), childLabel.end());
    }

    output.reserve(result.size());

    std::copy(result.begin(), result.end(), std::back_inserter(output));

    std::sort(output.begin(), output.end());

    output.erase(std::unique(output.begin(), output.end()), output.end());
}

htd::JoinNodeReplacementOperation * htd::JoinNodeReplacementOperation::clone(void) const
{
    return new htd::JoinNodeReplacementOperation();
}

#endif /* HTD_HTD_JOINNODEREPLACEMENTOPERATION_CPP */
