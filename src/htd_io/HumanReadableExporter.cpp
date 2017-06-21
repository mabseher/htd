/*
 * File:   HumanReadableExporter.cpp
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

#ifndef HTD_IO_HUMANREADABLEEXPORTER_CPP
#define HTD_IO_HUMANREADABLEEXPORTER_CPP

#include <htd_io/HumanReadableExporter.hpp>

#include <htd/PreOrderTreeTraversal.hpp>

htd_io::HumanReadableExporter::HumanReadableExporter(void)
{

}

htd_io::HumanReadableExporter::~HumanReadableExporter()
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

void printHyperedge(const htd::Hyperedge & hyperedge, std::ostream & outputStream)
{
    outputStream << "HYPEREDGE " << hyperedge.id() << ": [ ";

    const std::vector<htd::vertex_t> & elements = hyperedge.elements();

    if (elements.empty())
    {
        outputStream << "]";
    }
    else
    {
        for (htd::index_t index = 0; index < elements.size(); ++index)
        {
            outputStream << elements.at(index);

            if (index < elements.size() - 1)
            {
                outputStream << ", ";
            }
        }

        outputStream << " ]";
    }
}

void printHyperedge(const htd::Hyperedge & hyperedge, std::ostream & outputStream, const htd::NamedMultiHypergraph<std::string, std::string> & graph)
{
    outputStream << "HYPEREDGE " << hyperedge.id() << ": [ ";

    const std::vector<htd::vertex_t> & elements = hyperedge.elements();

    if (elements.empty())
    {
        outputStream << "]";
    }
    else
    {
        for (htd::index_t index = 0; index < elements.size(); ++index)
        {
            outputStream << graph.vertexName(elements.at(index));

            if (index < elements.size() - 1)
            {
                outputStream << ", ";
            }
        }

        outputStream << " ]";
    }
}

void htd_io::HumanReadableExporter::write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
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

void htd_io::HumanReadableExporter::write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
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

void htd_io::HumanReadableExporter::write(const htd::IHypertreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
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

        for (htd::index_t index = 0; index < distanceToRoot + 1; ++index)
        {
            outputStream << "  ";
        }

        outputStream << "COVERING EDGES: " << std::endl;

        for (const htd::Hyperedge & edge : decomposition.coveringEdges(vertex))
        {
            for (htd::index_t index = 0; index < distanceToRoot + 2; ++index)
            {
                outputStream << "  ";
            }

            outputStream << "HYPEREDGE " << edge.id() << ": " << edge.elements() << std::endl;
        }
    });
}

void htd_io::HumanReadableExporter::write(const htd::IHypertreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
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

        for (htd::index_t index = 0; index < distanceToRoot + 1; ++index)
        {
            outputStream << "  ";
        }

        outputStream << "COVERING EDGES: " << std::endl;

        for (const htd::Hyperedge & edge : decomposition.coveringEdges(vertex))
        {
            for (htd::index_t index = 0; index < distanceToRoot + 2; ++index)
            {
                outputStream << "  ";
            }

            outputStream << "HYPEREDGE " << edge.id() << ": " << edge.elements() << std::endl;
        }
    });
}

#endif /* HTD_IO_HUMANREADABLEEXPORTER_CPP */
