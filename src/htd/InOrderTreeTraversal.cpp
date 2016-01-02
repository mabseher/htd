/*
 * File:   InOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_INORDERTREETRAVERSAL_CPP
#define	HTD_HTD_INORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/InOrderTreeTraversal.hpp>
#include <htd/PreOrderTreeTraversal.hpp>

#include <stdexcept>

htd::InOrderTreeTraversal::InOrderTreeTraversal(void)
{

}

htd::InOrderTreeTraversal::~InOrderTreeTraversal()
{

}

void htd::InOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction) const
{
    const htd::ConstCollection<htd::vertex_t> & vertexCollection = tree.vertices();

    htd::vertex_container vertices(vertexCollection.begin(), vertexCollection.end());

    std::sort(vertices.begin(), vertices.end());

    for (htd::vertex_t vertex : vertices)
    {
        targetFunction(vertex);
    }
}

void htd::InOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t)> targetFunction, htd::vertex_t startingNode) const
{
    if (!tree.isVertex(startingNode))
    {
        throw std::logic_error("void htd::InOrderTreeTraversal::traverse(const htd::ITree &, std::function<void(htd::vertex_t)>, htd::vertex_t) const");
    }

    htd::vertex_container vertices;

    htd::PreOrderTreeTraversal traversal;

    traversal.traverse(tree, [&](htd::vertex_t vertex) { vertices.push_back(vertex); }, startingNode);

    std::sort(vertices.begin(), vertices.end());

    for (htd::vertex_t vertex : vertices)
    {
        targetFunction(vertex);
    }
}

#endif /* HTD_HTD_INORDERTREETRAVERSAL_CPP */
