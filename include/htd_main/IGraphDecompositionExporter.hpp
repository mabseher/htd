/*
 * File:   IGraphDecompositionExporter.hpp
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

#ifndef HTD_MAIN_IGRAPHDECOMPOSITIONEXPORTER_HPP
#define HTD_MAIN_IGRAPHDECOMPOSITIONEXPORTER_HPP

#include <htd_main/ITreeDecompositionExporter.hpp>

#include <iostream>

namespace htd_main
{
    /**
     * Interface for algorithms which can be used to export graph decompositions to streams.
     */
    class IGraphDecompositionExporter : public htd_main::ITreeDecompositionExporter
    {
        public:
            using htd_main::ITreeDecompositionExporter::write;

            virtual ~IGraphDecompositionExporter() = 0;

            /**
             *  Write a graph decomposition to a given stream.
             *
             *  @param[in] decomposition    The graph decomposition which shall be exported.
             *  @param[in] graph            The graph instance from which the given decomposition was constructed.
             *  @param[out] outputStream    The output stream to which the information shall be written.
             */
            virtual void write(const htd::IGraphDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const = 0;

            /**
             *  Write a graph decomposition to a given stream.
             *
             *  @param[in] decomposition    The graph decomposition which shall be exported.
             *  @param[in] graph            The graph instance from which the given decomposition was constructed.
             *  @param[out] outputStream    The output stream to which the information shall be written.
             */
            virtual void write(const htd::IGraphDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const = 0;
    };

    inline htd_main::IGraphDecompositionExporter::~IGraphDecompositionExporter() { }
}

#endif /* HTD_MAIN_IGRAPHDECOMPOSITIONEXPORTER_HPP */
