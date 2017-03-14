/*
 * File:   HgrFormatGraphToTreeDecompositionProcessor.hpp
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

#ifndef HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP
#define HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP

#include <htd_main/IGraphToTreeDecompositionProcessor.hpp>

namespace htd_main
{
    /**
     *  Importer which allows to read instances in the graph format 'hgr'.
     *
     *  (See https://github.com/mabseher/htd/FORMATS.md for information about the available input formats.)
     */
    class HgrFormatGraphToTreeDecompositionProcessor : public htd_main::IGraphToTreeDecompositionProcessor
    {
        public:
            /**
             *  Constructor for a new graph processor.
             */
            HgrFormatGraphToTreeDecompositionProcessor(const htd::LibraryInstance * const manager);

            /**
             *  Destructor of a graph processor.
             */
            virtual ~HgrFormatGraphToTreeDecompositionProcessor();

            void process(const std::string & inputFile, const std::string & outputFile) const HTD_OVERRIDE;

            void process(const std::string & inputFile, std::ostream & outputStream) const HTD_OVERRIDE;

            void process(std::istream & inputStream, const std::string & outputFile) const HTD_OVERRIDE;

            void process(std::istream & inputStream = std::cin, std::ostream & outputStream = std::cout) const HTD_OVERRIDE;

            void setExporter(htd_main::ITreeDecompositionExporter * exporter) HTD_OVERRIDE;

            void setPreprocessor(htd::IGraphPreprocessor * preprocessor) HTD_OVERRIDE;

            void registerParsingCallback(const std::function<void(htd_main::parsing_result_t result, std::size_t vertexCount, std::size_t edgeCount)> & callback) HTD_OVERRIDE;

            void registerPreprocessingCallback(const std::function<void(std::size_t vertexCount, std::size_t edgeCount)> & callback) HTD_OVERRIDE;

            void registerDecompositionCallback(const std::function<void(const htd::FitnessEvaluation &)> & callback) HTD_OVERRIDE;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP */
