/*
 * File:   WidthExporter.cpp
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

#ifndef HTD_HTD_WIDTHEXPORTER_CPP
#define	HTD_HTD_WIDTHEXPORTER_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/WidthExporter.hpp>

#include <iostream>
#include <unordered_map>

htd::WidthExporter::WidthExporter(void)
{

}

htd::WidthExporter::~WidthExporter()
{

}

void htd::WidthExporter::write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph);

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd::WidthExporter::write(const htd::IGraphDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph);

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd::WidthExporter::write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph);

    outputStream << decomposition.maximumBagSize() << std::endl;
}

void htd::WidthExporter::write(const htd::IGraphDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const
{
    HTD_UNUSED(graph);

    outputStream << decomposition.maximumBagSize() << std::endl;
}

#endif /* HTD_HTD_WIDTHEXPORTER_CPP */
