/*
 * File:   WidthExporter.hpp
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

#ifndef HTD_IO_WIDTHEXPORTER_HPP
#define HTD_IO_WIDTHEXPORTER_HPP

#include <htd_io/PreprocessorDefinitions.hpp>

#include <htd_io/IGraphDecompositionExporter.hpp>
#include <htd_io/IHypertreeDecompositionExporter.hpp>

#include <iostream>

namespace htd_io
{
    /**
     *  Exporter which just writes the maximum bag size of the decomposition to the give stream. In the case of a
     *  hypertree decomposition, also the maximum amount of covering edges is written to the stream and the two
     *  numbers are separated by the character sequence ", ".
     */
    class WidthExporter : public htd_io::IGraphDecompositionExporter, public htd_io::IHypertreeDecompositionExporter
    {
        public:
            HTD_IO_API WidthExporter(void);

            HTD_IO_API virtual ~WidthExporter();

            HTD_IO_API void write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void write(const htd::IGraphDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void write(const htd::IHypertreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void write(const htd::IGraphDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void write(const htd::IHypertreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;
    };
}

#endif /* HTD_IO_WIDTHEXPORTER_HPP */
