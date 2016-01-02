/*
 * File:   PostOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_POSTORDERTREETRAVERSAL_CPP
#define	HTD_HTD_POSTORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <stack>
#include <stdexcept>

htd::PostOrderTreeTraversal::PostOrderTreeTraversal(void)
{

}

htd::PostOrderTreeTraversal::~PostOrderTreeTraversal()
{

}

void htd::PostOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction) const
{
    if (tree.vertexCount() > 0)
    {
        traverse(tree, targetFunction, tree.root());
    }
}

void htd::PostOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction, htd::vertex_t startingNode) const
{
    if (!tree.isVertex(startingNode))
    {
        throw std::logic_error("void htd::PostOrderTreeTraversal::traverse(const htd::ITree &, std::function<void(htd::vertex_t)>, htd::vertex_t) const");
    }

    htd::vertex_t lastNode = htd::Vertex::UNKNOWN;

    htd::vertex_t peekNode = htd::Vertex::UNKNOWN;

    htd::vertex_t currentNode = startingNode;

    htd::index_t lastIndex = 0;

    htd::index_t peekIndex = 0;

    htd::index_t currentIndex = tree.childCount(currentNode) - 1;

    std::stack<std::pair<htd::vertex_t, htd::index_t>> parentStack;

    while (parentStack.size() > 0 || currentNode != htd::Vertex::UNKNOWN)
    {
        if (currentNode != htd::Vertex::UNKNOWN)
        {
            if (currentIndex < tree.childCount(currentNode))
            {
                parentStack.push(std::make_pair(currentNode, currentIndex));

                currentNode = tree.child(currentNode, currentIndex);

                currentIndex = tree.childCount(currentNode) - 1;
            }
            else
            {
                if (parentStack.size() > 0 && parentStack.top().first != htd::Vertex::UNKNOWN)
                {
                    targetFunction(currentNode);

                    parentStack.top().second--;
                }
                else
                {
                    targetFunction(startingNode);
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
                currentNode = tree.child(peekNode, peekIndex);

                currentIndex = tree.childCount(currentNode) - 1;
            }
            else
            {
                lastNode = peekNode;
                lastIndex = peekIndex;

                currentNode = htd::Vertex::UNKNOWN;

                parentStack.pop();

                if (parentStack.size() > 0 && parentStack.top().first != htd::Vertex::UNKNOWN)
                {
                    targetFunction(peekNode);

                    parentStack.top().second--;
                }
                else
                {
                    targetFunction(startingNode);
                }
            }
        }
    }
}

#endif /* HTD_HTD_POSTORDERTREETRAVERSAL_CPP */
