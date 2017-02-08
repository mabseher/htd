/*
 * File:   PostOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_POSTORDERTREETRAVERSAL_CPP
#define HTD_HTD_POSTORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <stack>
#include <stdexcept>
#include <utility>

htd::PostOrderTreeTraversal::PostOrderTreeTraversal(void)
{

}

htd::PostOrderTreeTraversal::~PostOrderTreeTraversal()
{

}

void htd::PostOrderTreeTraversal::traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    if (path.vertexCount() > 0)
    {
        traverse(path, targetFunction, path.root());
    }
}

void htd::PostOrderTreeTraversal::traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const
{
    HTD_ASSERT(path.isVertex(startingVertex))

    htd::vertex_t currentNode = startingVertex;

    htd::vertex_t parentNode = htd::Vertex::UNKNOWN;

    std::size_t currentDepth = 0;

    std::stack<htd::vertex_t> parentStack;

    while (currentNode != htd::Vertex::UNKNOWN)
    {
        parentStack.push(currentNode);

        if (path.childCount(currentNode) > 0)
        {
            currentNode = path.child(currentNode);

            ++currentDepth;
        }
        else
        {
            currentNode = htd::Vertex::UNKNOWN;
        }
    }

    while (!parentStack.empty())
    {
        currentNode = parentStack.top();

        parentStack.pop();

        if (parentStack.empty())
        {
            parentNode = htd::Vertex::UNKNOWN;
        }
        else
        {
            parentNode = parentStack.top();
        }

        targetFunction(currentNode, parentNode, currentDepth);

        --currentDepth;
    }
}

void htd::PostOrderTreeTraversal::traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    if (tree.vertexCount() > 0)
    {
        traverse(tree, targetFunction, tree.root());
    }
}

void htd::PostOrderTreeTraversal::traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const
{
    HTD_ASSERT(tree.isVertex(startingVertex))

    htd::vertex_t lastNode = htd::Vertex::UNKNOWN;

    htd::vertex_t peekNode = htd::Vertex::UNKNOWN;

    htd::vertex_t currentNode = startingVertex;

    htd::index_t lastIndex = 0;

    htd::index_t peekIndex = 0;

    htd::index_t currentIndex = tree.childCount(currentNode) - 1;

    std::size_t currentDepth = 0;

    std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

    while (!parentStack.empty() || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex < tree.childCount(currentNode))
            {
                parentStack.emplace(currentNode, currentIndex);

                currentNode = tree.childAtPosition(currentNode, currentIndex);

                currentIndex = tree.childCount(currentNode) - 1;

                ++currentDepth;
            }
            else
            {
                if (!parentStack.empty() && parentStack.top().first != htd::Vertex::UNKNOWN)
                {
                    targetFunction(currentNode, std::get<0>(parentStack.top()), currentDepth);

                    parentStack.top().second--;

                    --currentDepth;
                }
                else
                {
                    targetFunction(startingVertex, htd::Vertex::UNKNOWN, 0);
                }

                currentNode = htd::Vertex::UNKNOWN;
            }
        }
        else
        {
            peekNode = parentStack.top().first;
            peekIndex = parentStack.top().second;

            if (peekIndex < tree.childCount(peekNode) && !(lastNode == peekNode && lastIndex == peekIndex))
            {
                currentNode = tree.childAtPosition(peekNode, peekIndex);

                currentIndex = tree.childCount(currentNode) - 1;

                ++currentDepth;
            }
            else
            {
                lastNode = peekNode;
                lastIndex = peekIndex;

                currentNode = htd::Vertex::UNKNOWN;

                parentStack.pop();

                if (!parentStack.empty() && parentStack.top().first != htd::Vertex::UNKNOWN)
                {
                    targetFunction(peekNode, std::get<0>(parentStack.top()), currentDepth);

                    parentStack.top().second--;

                    --currentDepth;
                }
                else
                {
                    targetFunction(startingVertex, htd::Vertex::UNKNOWN, 0);
                }
            }
        }
    }
}

#endif /* HTD_HTD_POSTORDERTREETRAVERSAL_CPP */
