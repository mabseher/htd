/*
 * File:   HumanReadableExporter.hpp
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

#ifndef HTD_MAIN_HUMANREADABLEEXPORTER_HPP
#define HTD_MAIN_HUMANREADABLEEXPORTER_HPP

#include <htd_main/ITreeDecompositionExporter.hpp>
#include <htd_main/IHypertreeDecompositionExporter.hpp>

#include <iostream>

namespace htd_main
{
    /**
     *  Exporter which allows to export tree decompositions in a human-readable format.
     */
    class HumanReadableExporter : public htd_main::ITreeDecompositionExporter, public htd_main::IHypertreeDecompositionExporter
    {
        public:
            HumanReadableExporter(void);

            virtual ~HumanReadableExporter();

            void write(const htd::ITreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            void write(const htd::ITreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            void write(const htd::IHypertreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const HTD_OVERRIDE;

            void write(const htd::IHypertreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const HTD_OVERRIDE;
    };
}

#endif /* HTD_MAIN_HUMANREADABLEEXPORTER_HPP */
