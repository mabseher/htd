/*
 * File:   WidthExporter.cpp
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

#ifndef HTD_IO_WIDTHEXPORTER_CPP
#define HTD_IO_WIDTHEXPORTER_CPP

#include <htd_io/WidthExporter.hpp>

htd_io::WidthExporter::WidthExporter(void)
{

}

htd_io::WidthExporter::~WidthExporter()
{

}

void htd_io::WidthExporter::write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd_io::WidthExporter::write(const htd::IGraphDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd_io::WidthExporter::write(const htd::IHypertreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << ", " << decomposition.maximumCoveringEdgeAmount() << std::endl;
}

void htd_io::WidthExporter::write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd_io::WidthExporter::write(const htd::IGraphDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd_io::WidthExporter::write(const htd::IHypertreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph)

    outputStream << decomposition.maximumBagSize() << ", " << decomposition.maximumCoveringEdgeAmount() << std::endl;
}

#endif /* HTD_IO_WIDTHEXPORTER_CPP */
