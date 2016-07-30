/*
 * File:   TdFormatExporter.hpp
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

#ifndef HTD_HTD_TDFORMATEXPORTER_HPP
#define	HTD_HTD_TDFORMATEXPORTER_HPP

#include <htd/ITreeDecompositionExporter.hpp>

#include <fstream>
#include <iostream>

namespace htd
{
    /**
     *  Exporter which allows to export tree decompositions in the tree decomposition format 'td'.
     *
     *  (See https://github.com/mabseher/htd/FORMATS.md for information about the available output formats.)
     */
    class HTD_API TdFormatExporter : public htd::ITreeDecompositionExporter
    {
        public:
            TdFormatExporter(void);

            virtual ~TdFormatExporter();

            void write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            void write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;
    };
}

#endif /* HTD_HTD_TDFORMATEXPORTER_HPP */
