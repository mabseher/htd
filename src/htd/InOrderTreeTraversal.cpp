/*
 * File:   InOrderTreeTraversal.cpp
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

#ifndef HTD_HTD_INORDERTREETRAVERSAL_CPP
#define	HTD_HTD_INORDERTREETRAVERSAL_CPP

#include <htd/Globals.hpp>
#include <htd/InOrderTreeTraversal.hpp>
#include <htd/PreOrderTreeTraversal.hpp>

#include <stdexcept>
#include <unordered_map>
#include <utility>

htd::InOrderTreeTraversal::InOrderTreeTraversal(void)
{

}

htd::InOrderTreeTraversal::~InOrderTreeTraversal()
{

}

void htd::InOrderTreeTraversal::traverse(const htd::IPath & path, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> targetFunction) const
{
    if (path.vertexCount() > 0)
    {
        traverse(path, targetFunction, path.root());
    }
}

void htd::InOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> targetFunction) const
{
    if (tree.vertexCount() > 0)
    {
        traverse(tree, targetFunction, tree.root());
    }
}

void htd::InOrderTreeTraversal::traverse(const htd::IPath & path, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> targetFunction, htd::vertex_t startingVertex) const
{
    if (!path.isVertex(startingVertex))
    {
        throw std::logic_error("void htd::InOrderTreeTraversal::traverse(const htd::IPath &, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)>, htd::vertex_t) const");
    }

    htd::vertex_container vertices;

    htd::PreOrderTreeTraversal traversal;

    std::unordered_map<htd::vertex_t, std::pair<htd::vertex_t, std::size_t>> additionalInformation;

    traversal.traverse(path, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToStartingVertex)
    {
        vertices.push_back(vertex);

        additionalInformation[vertex] = std::make_pair(parent, distanceToStartingVertex);
    }, startingVertex);

    std::sort(vertices.begin(), vertices.end());

    for (htd::vertex_t vertex : vertices)
    {
        std::pair<htd::vertex_t, std::size_t> & information = additionalInformation[vertex];

        targetFunction(vertex, information.first, information.second);
    }
}

void htd::InOrderTreeTraversal::traverse(const htd::ITree & tree, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)> targetFunction, htd::vertex_t startingVertex) const
{
    if (!tree.isVertex(startingVertex))
    {
        throw std::logic_error("void htd::InOrderTreeTraversal::traverse(const htd::ITree &, std::function<void(htd::vertex_t, htd::vertex_t, std::size_t)>, htd::vertex_t) const");
    }

    htd::vertex_container vertices;

    htd::PreOrderTreeTraversal traversal;

    std::unordered_map<htd::vertex_t, std::pair<htd::vertex_t, std::size_t>> additionalInformation;

    traversal.traverse(tree, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToStartingVertex)
    {
        vertices.push_back(vertex);

        additionalInformation[vertex] = std::make_pair(parent, distanceToStartingVertex);
    }, startingVertex);

    std::sort(vertices.begin(), vertices.end());

    for (htd::vertex_t vertex : vertices)
    {
        std::pair<htd::vertex_t, std::size_t> & information = additionalInformation[vertex];

        targetFunction(vertex, information.first, information.second);
    }
}

#endif /* HTD_HTD_INORDERTREETRAVERSAL_CPP */
