/*
 * File:   CompressionOperation.cpp
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

#ifndef HTD_HTD_COMPRESSIONOPERATION_CPP
#define	HTD_HTD_COMPRESSIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>

#include <stack>

htd::CompressionOperation::CompressionOperation(void)
{

}

htd::CompressionOperation::~CompressionOperation()
{

}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
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
    }
}

#endif /* HTD_HTD_COMPRESSIONOPERATION_CPP */
