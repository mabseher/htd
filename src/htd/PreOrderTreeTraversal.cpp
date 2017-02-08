/*
 * File:   PreOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_PREORDERTREETRAVERSAL_CPP
#define HTD_HTD_PREORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/PreOrderTreeTraversal.hpp>

#include <stack>
#include <stdexcept>
#include <utility>

htd::PreOrderTreeTraversal::PreOrderTreeTraversal(void)
{

}

htd::PreOrderTreeTraversal::~PreOrderTreeTraversal()
{

}

void htd::PreOrderTreeTraversal::traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    if (path.vertexCount() > 0)
    {
        traverse(path, targetFunction, path.root());
    }
}

void htd::PreOrderTreeTraversal::traverse(const htd::IPath & path, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const
{
    HTD_ASSERT(path.isVertex(startingVertex))

    htd::vertex_t currentNode = startingVertex;

    htd::vertex_t parentNode = htd::Vertex::UNKNOWN;

    std::size_t currentDepth = 0;

    while (currentNode != htd::Vertex::UNKNOWN)
    {
        targetFunction(currentNode, parentNode, currentDepth);

        if (path.childCount(currentNode) > 0)
        {
            parentNode = currentNode;

            currentNode = path.child(currentNode);

            ++currentDepth;
        }
        else
        {
            currentNode = htd::Vertex::UNKNOWN;
        }
    }
}

void htd::PreOrderTreeTraversal::traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction) const
{
    if (tree.vertexCount() > 0)
    {
        traverse(tree, targetFunction, tree.root());
    }
}

void htd::PreOrderTreeTraversal::traverse(const htd::ITree & tree, const std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> & targetFunction, htd::vertex_t startingVertex) const
{
    HTD_ASSERT(tree.isVertex(startingVertex))

    htd::vertex_t currentNode = startingVertex;

    std::size_t currentDepth = 0;

    htd::index_t currentIndex = 0;

    std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

    while (!parentStack.empty() || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex == 0)
            {
                if (!parentStack.empty())
                {
                    targetFunction(currentNode, std::get<0>(parentStack.top()), currentDepth);
                }
                else
                {
                    targetFunction(currentNode, htd::Vertex::UNKNOWN, 0);
                }
            }

            if (currentIndex < tree.childCount(currentNode))
            {
                parentStack.emplace(currentNode, currentIndex + 1);

                currentNode = tree.childAtPosition(currentNode, currentIndex);

                currentIndex = 0;

                ++currentDepth;
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

            --currentDepth;

            parentStack.pop();
        }
    }
}

#endif /* HTD_HTD_PREORDERTREETRAVERSAL_CPP */
