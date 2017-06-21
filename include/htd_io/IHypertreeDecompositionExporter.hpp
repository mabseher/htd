/*
 * File:   IHypertreeDecompositionExporter.hpp
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

#ifndef HTD_IO_IHYPERTREEDECOMPOSITIONEXPORTER_HPP
#define HTD_IO_IHYPERTREEDECOMPOSITIONEXPORTER_HPP

#include <htd/IMultiHypergraph.hpp>
#include <htd/NamedMultiHypergraph.hpp>
#include <htd/IHypertreeDecomposition.hpp>

#include <iostream>

namespace htd_io
{
    /**
     * Interface for algorithms which can be used to export hypertree decompositions to streams.
     */
    class IHypertreeDecompositionExporter
    {
        public:
            virtual ~IHypertreeDecompositionExporter() = 0;

            /**
             *  Write a hypertree decomposition to a given stream.
             *
             *  @param[in] decomposition    The hypertree decomposition which shall be exported.
             *  @param[in] graph            The graph instance from which the given decomposition was constructed.
             *  @param[out] outputStream    The output stream to which the information shall be written.
             */
            virtual void write(const htd::IHypertreeDecomposition & decomposition, const htd::IMultiHypergraph & graph, std::ostream & outputStream) const = 0;

            /**
             *  Write a hypertree decomposition to a given stream.
             *
             *  @param[in] decomposition    The hypertree decomposition which shall be exported.
             *  @param[in] graph            The graph instance from which the given decomposition was constructed.
             *  @param[out] outputStream    The output stream to which the information shall be written.
             */
            virtual void write(const htd::IHypertreeDecomposition & decomposition, const htd::NamedMultiHypergraph<std::string, std::string> & graph, std::ostream & outputStream) const = 0;
    };

    inline htd_io::IHypertreeDecompositionExporter::~IHypertreeDecompositionExporter() { }
}

#endif /* HTD_IO_IHYPERTREEDECOMPOSITIONEXPORTER_HPP */
