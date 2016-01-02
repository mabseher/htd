/*
 * File:   CompressionOperation.cpp
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

#ifndef HTD_HTD_COMPRESSIONOPERATION_CPP
#define	HTD_HTD_COMPRESSIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/IMutableTreeDecomposition.hpp>

#include <stack>

htd::CompressionOperation::CompressionOperation(void)
{

}

htd::CompressionOperation::~CompressionOperation()
{

}

void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

//TODO Exploit the fact that nodes in a path have at most one child!
void htd::CompressionOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

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

                    const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(currentNode);

                    parentStack.push(std::make_pair(currentNode, currentIndex + 1));

                    currentNode = decomposition.child(currentNode);

                    currentIndex = 0;

                    const htd::ConstCollection<htd::vertex_t> & childBag = decomposition.bagContent(currentNode);

                    if (childBag.size() < bag.size())
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), currentNode) == unneededVertices.end() && std::includes(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
                        {
                            unneededVertices.push_back(currentNode);
                        }
                    }
                    else
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), oldNode) == unneededVertices.end() && std::includes(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
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

                const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(vertex);

                const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(vertex);

                std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

                for (htd::vertex_t child : children)
                {
                    const htd::ConstCollection<htd::vertex_t> & childBag = decomposition.bagContent(child);

                    if (std::includes(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
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

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::CompressionOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(labelingFunctions);

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

                    const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(currentNode);

                    parentStack.push(std::make_pair(currentNode, currentIndex + 1));

                    currentNode = decomposition.child(currentNode, currentIndex);

                    currentIndex = 0;

                    const htd::ConstCollection<htd::vertex_t> & childBag = decomposition.bagContent(currentNode);

                    if (childBag.size() < bag.size())
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), currentNode) == unneededVertices.end() && std::includes(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
                        {
                            unneededVertices.push_back(currentNode);
                        }
                    }
                    else
                    {
                        if (std::find(unneededVertices.begin(), unneededVertices.end(), oldNode) == unneededVertices.end() && std::includes(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
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

                const htd::ConstCollection<htd::vertex_t> & bag = decomposition.bagContent(currentNode);

                const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(vertex);

                std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

                for (htd::vertex_t child : children)
                {
                    const htd::ConstCollection<htd::vertex_t> & childBag = decomposition.bagContent(currentNode);

                    if (std::includes(bag.begin(), bag.end(), childBag.begin(), childBag.end()))
                    {
                        decomposition.removeVertex(child);
                    }
                    else
                    {
                        /*
                        if (std::includes(childBag.begin(), childBag.end(), bag.begin(), bag.end()))
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

htd::CompressionOperation * htd::CompressionOperation::clone(void) const
{
    return new htd::CompressionOperation();
}

#endif /* HTD_HTD_COMPRESSIONOPERATION_CPP */
