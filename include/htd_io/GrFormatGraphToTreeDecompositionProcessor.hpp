/*
 * File:   GrFormatGraphToTreeDecompositionProcessor.hpp
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

#ifndef HTD_IO_GRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP
#define HTD_IO_GRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP

#include <htd_io/PreprocessorDefinitions.hpp>

#include <htd_io/IGraphToTreeDecompositionProcessor.hpp>

namespace htd_io
{
    /**
     *  Importer which allows to read instances in the graph format 'gr'.
     *
     *  (See https://github.com/mabseher/htd/FORMATS.md for information about the available input formats.)
     */
    class GrFormatGraphToTreeDecompositionProcessor : public htd_io::IGraphToTreeDecompositionProcessor
    {
        public:
            /**
             *  Constructor for a new graph processor.
             */
            HTD_IO_API GrFormatGraphToTreeDecompositionProcessor(const htd::LibraryInstance * const manager);

            /**
             *  Destructor of a graph processor.
             */
            HTD_IO_API virtual ~GrFormatGraphToTreeDecompositionProcessor();

            HTD_IO_API void process(const std::string & inputFile, const std::string & outputFile) const HTD_OVERRIDE;

            HTD_IO_API void process(const std::string & inputFile, std::ostream & outputStream) const HTD_OVERRIDE;

            HTD_IO_API void process(std::istream & inputStream, const std::string & outputFile) const HTD_OVERRIDE;

            HTD_IO_API void process(std::istream & inputStream = std::cin, std::ostream & outputStream = std::cout) const HTD_OVERRIDE;

            HTD_IO_API void setExporter(htd_io::ITreeDecompositionExporter * exporter) HTD_OVERRIDE;

            HTD_IO_API void setPreprocessor(htd::IGraphPreprocessor * preprocessor) HTD_OVERRIDE;

            HTD_IO_API void registerParsingCallback(const std::function<void(htd_io::parsing_result_t result, std::size_t vertexCount, std::size_t edgeCount)> & callback) HTD_OVERRIDE;

            HTD_IO_API void registerPreprocessingCallback(const std::function<void(std::size_t vertexCount, std::size_t edgeCount)> & callback) HTD_OVERRIDE;

            HTD_IO_API void registerDecompositionCallback(const std::function<void(const htd::FitnessEvaluation &)> & callback) HTD_OVERRIDE;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_IO_GRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP */
