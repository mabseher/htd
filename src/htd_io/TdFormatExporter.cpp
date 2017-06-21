/*
 * File:   TdFormatExporter.cpp
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

#ifndef HTD_IO_TDFORMATEXPORTER_CPP
#define HTD_IO_TDFORMATEXPORTER_CPP

#include <htd_io/TdFormatExporter.hpp>

#include <sstream>
#include <unordered_map>

htd_io::TdFormatExporter::TdFormatExporter(void)
{

}

htd_io::TdFormatExporter::~TdFormatExporter()
{

}

void htd_io::TdFormatExporter::write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    std::unordered_map<htd::vertex_t, std::size_t> indices;

    outputStream << "s td " << decomposition.vertexCount() << " " << decomposition.maximumBagSize() << " " << graph.vertexCount() << "\n";

    if (decomposition.vertexCount() > 0)
    {
        std::size_t index = 1;

        std::stringstream tmpStream;

        for (htd::vertex_t node : decomposition.vertices())
        {
            tmpStream << "b " << index << " ";

            indices.emplace(node, index);

            for (htd::vertex_t vertex : decomposition.bagContent(node))
            {
                tmpStream << vertex << " ";
            }

            tmpStream << "\n" << std::flush;

            outputStream << tmpStream.rdbuf();

            tmpStream.clear();

            ++index;
        }

        const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = decomposition.hyperedges();

        std::size_t edgeCount = decomposition.edgeCount();

        auto it = hyperedgeCollection.begin();

        for (htd::index_t index = 0; index < edgeCount; ++index)
        {
            htd::vertex_t vertex1 = indices.at((*it)[0]);
            htd::vertex_t vertex2 = indices.at((*it)[1]);

            outputStream << vertex1 << " " << vertex2 << "\n";

            ++it;
        }
    }
}

void htd_io::TdFormatExporter::write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    std::unordered_map<htd::vertex_t, std::size_t> indices;

    outputStream << "s td " << decomposition.vertexCount() << " " << decomposition.maximumBagSize() << " " << graph.vertexCount() << "\n";

    if (decomposition.vertexCount() > 0)
    {
        std::size_t index = 1;

        std::stringstream tmpStream;

        for (htd::vertex_t node : decomposition.vertices())
        {
            tmpStream << "b " << index << " ";

            indices.emplace(node, index);

            for (htd::vertex_t vertex : decomposition.bagContent(node))
            {
                tmpStream << vertex << " ";
            }

            tmpStream << "\n" << std::flush;

            outputStream << tmpStream.rdbuf();

            tmpStream.clear();

            ++index;
        }

        const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = decomposition.hyperedges();

        std::size_t edgeCount = decomposition.edgeCount();

        auto it = hyperedgeCollection.begin();

        for (htd::index_t index = 0; index < edgeCount; ++index)
        {
            htd::vertex_t vertex1 = indices.at((*it)[0]);
            htd::vertex_t vertex2 = indices.at((*it)[1]);

            outputStream << vertex1 << " " << vertex2 << "\n";

            ++it;
        }
    }
}

#endif /* HTD_IO_TDFORMATEXPORTER_CPP */
