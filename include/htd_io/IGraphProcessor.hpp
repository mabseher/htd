/*
 * File:   IGraphProcessor.hpp
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

#ifndef HTD_IO_IGRAPHPROCESSOR_HPP
#define HTD_IO_IGRAPHPROCESSOR_HPP

#include <htd_io/IGraphDecompositionExporter.hpp>

#include <htd_io/ParsingResult.hpp>
#include <htd/IGraphPreprocessor.hpp>

#include <string>
#include <iostream>
#include <functional>

namespace htd_io
{
    /**
     *  Common interface for classes which process graphs.
     */
    class IGraphProcessor
    {
        public:
            /**
             *  Destructor of a graph processor.
             */
            virtual ~IGraphProcessor() = 0;

            /**
             *  Process the graph stored in the given file.
             *
             *  @param[in] inputFile    The path to the file from which the input information shall be read.
             *  @param[in] outputFile   The path to the file to which the output information shall be written.
             */
            virtual void process(const std::string & inputFile, const std::string & outputFile) const = 0;

            /**
             *  Process the graph stored in the given file.
             *
             *  @param[in] inputFile    The path to the file from which the input information shall be read.
             *  @param[in] outputStream The stream to which the output information shall be written.
             */
            virtual void process(const std::string & inputFile, std::ostream & outputStream) const = 0;

            /**
             *  Process the graph stored in the given file.
             *
             *  @param[in] inputStream    The path to the file from which the input information shall be read.
             *  @param[in] outputFile   The path to the file to which the output information shall be written.
             */
            virtual void process(std::istream & inputStream, const std::string & outputFile) const = 0;

            /**
             *  Process the graph provided through the given input stream.
             *
             *  @param[in] inputStream  The stream from which the input information shall be read.
             *  @param[in] outputStream The stream to which the output information shall be written.
             */
            virtual void process(std::istream & inputStream = std::cin, std::ostream & outputStream = std::cout) const = 0;

            /**
             *  Set the preprocessor which shall be used to preprocess the input graphs.
             *
             *  @note When calling this method the control over the memory regions of the graph preprocessor
             *  is transferred to the graph processor. Deleting a graph preprocessor provided to this method
             *  outside the graph processor will lead to undefined behavior.
             *
             *  @param[in] preprocessor The preprocessor which shall be used to preprocess the input graphs.
             */
            virtual void setPreprocessor(htd::IGraphPreprocessor * preprocessor) = 0;

            /**
             *  Register a new callback function which is invoked after parsing the input graph is finished.
             *
             *  The first argument of the callback indicates whether the parsing process was successful, the
             *  second argument denotes the number of vertices of the input graph and the third argument of
             *  the callback provides the number of edges in the given input graph. In those cases where the
             *  parsing process was not successful, i.e., where the result is not equal to 'OK', the numbers
             *  for vertex and edge count are set to 0.
             *
             *  @note It is possible to append multiple callback functions. That is, this function does not
             *  override existing callback functions. Instead, all relevant callback functions are invoked
             *  after parsing is finished. The invocation of the callback functions is guaranteed to happen
             *  in the order the callback functions were registered.
             *
             *  @param[in] callback The new callback function which is invoked after parsing the input graph is finished.
             */
            virtual void registerParsingCallback(const std::function<void(htd_io::parsing_result_t result, std::size_t vertexCount, std::size_t edgeCount)> & callback) = 0;
    };

    inline htd_io::IGraphProcessor::~IGraphProcessor() { }
}

#endif /* HTD_IO_IGRAPHPROCESSOR_HPP */
