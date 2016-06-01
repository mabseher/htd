/*
 * File:   HumanReadableExporter.cpp
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

#ifndef HTD_HTD_HUMANREADABLEEXPORTER_CPP
#define	HTD_HTD_HUMANREADABLEEXPORTER_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HumanReadableExporter.hpp>

#include <htd/PreOrderTreeTraversal.hpp>

#include <iostream>
#include <unordered_map>

htd::HumanReadableExporter::HumanReadableExporter(void)
{

}

htd::HumanReadableExporter::~HumanReadableExporter()
{

}

void printBagContent(const std::vector<htd::vertex_t> & bag, std::ostream & outputStream)
{
    outputStream << "[ ";

    if (bag.empty())
    {
        outputStream << "]";
    }
    else
    {
        for (htd::index_t index = 0; index < bag.size(); ++index)
        {
            outputStream << bag.at(index);

            if (index < bag.size() - 1)
            {
                outputStream << ", ";
            }
        }

        outputStream << " ]";
    }
}

void printBagContent(const std::vector<htd::vertex_t> & bag, std::ostream & outputStream, const htd::NamedMultiHypergraph<std::string, std::string> & graph)
{
    outputStream << "[ ";

    if (bag.empty())
    {
        outputStream << "]";
    }
    else
    {
        for (htd::index_t index = 0; index < bag.size(); ++index)
        {
            outputStream << graph.vertexName(bag.at(index));

            if (index < bag.size() - 1)
            {
                outputStream << ", ";
            }
        }

        outputStream << " ]";
    }
}

void htd::HumanReadableExporter::write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    htd::PreOrderTreeTraversal traversal;

    HTD_UNUSED(graph)

    traversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToRoot)
    {
        HTD_UNUSED(parent)

        for (htd::index_t index = 0; index < distanceToRoot; ++index)
        {
            outputStream << "  ";
        }

        outputStream << "NODE " << vertex << ": ";

        printBagContent(decomposition.bagContent(vertex), outputStream);

        outputStream << std::endl;
    });
}

void htd::HumanReadableExporter::write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    htd::PreOrderTreeTraversal traversal;

    traversal.traverse(decomposition, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToRoot)
    {
        HTD_UNUSED(parent)

        for (htd::index_t index = 0; index < distanceToRoot; ++index)
        {
            outputStream << "   ";
        }

        outputStream << "NODE " << vertex << ": ";

        printBagContent(decomposition.bagContent(vertex), outputStream, graph);

        outputStream << std::endl;
    });
}

#endif /* HTD_HTD_HUMANREADABLEEXPORTER_CPP */
