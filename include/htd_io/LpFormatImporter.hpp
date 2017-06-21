/*
 * File:   LpFormatImporter.hpp
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

#ifndef HTD_IO_LPFORMATIMPORTER_HPP
#define HTD_IO_LPFORMATIMPORTER_HPP

#include <htd_io/PreprocessorDefinitions.hpp>

#include <htd/NamedMultiHypergraph.hpp>

#include <string>
#include <iostream>

namespace htd_io
{
    /**
     *  Importer which allows to read instances in the graph format 'lp'.
     *
     *  (See https://github.com/mabseher/htd/FORMATS.md for information about the available input formats.)
     */
    class LpFormatImporter
    {
        public:
            /**
             *  Constructor for a new graph importer.
             */
            HTD_IO_API LpFormatImporter(const htd::LibraryInstance * const manager);

            /**
             *  Destructor of a graph importer.
             */
            HTD_IO_API virtual ~LpFormatImporter();

            /**
             *  Create a new htd::NamedMultiHypergraph<std::string, std::string> instance based on the information stored in a given file.
             *
             *  @param[in] path The path to the file from which the information can be read.
             *
             *  @return A new htd::NamedMultiHypergraph<std::string, std::string> instance based on the information stored in the given file.
             */
            HTD_IO_API htd::NamedMultiHypergraph<std::string, std::string> * import(const std::string & path) const;

            /**
             *  Create a new htd::NamedMultiHypergraph<std::string, std::string> instance based on the information from a given stream.
             *
             *  @param[in] stream   The input stream from which the information can be read.
             *
             *  @return A new htd::NamedMultiHypergraph<std::string, std::string> instance based on the information from the given stream.
             */
            HTD_IO_API htd::NamedMultiHypergraph<std::string, std::string> * import(std::istream & stream) const;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_IO_LPFORMATIMPORTER_HPP */
