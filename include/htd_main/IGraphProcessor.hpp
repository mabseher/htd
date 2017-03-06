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

#ifndef HTD_MAIN_IGRAPHPROCESSOR_HPP
#define HTD_MAIN_IGRAPHPROCESSOR_HPP

#include <htd_main/IGraphDecompositionExporter.hpp>

#include <string>
#include <iostream>
#include <functional>

namespace htd_main
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
             *  Register a new callback function which is invoked after parsing the input graph is finished.
             *
             *  @note It is possible to append multiple callback functions. That is, this function does not
             *  override existing callback functions. Instead, all relevant callback functions are invoked
             *  after parsing is finished. The invocation of the callback functions is guaranteed to happen
             *  in the order the callback functions were registered.
             *
             *  @param[in] callback The new callback function which is invoked after parsing the input graph is finished.
             */
            virtual void registerParsingCallback(const std::function<void(void)> & callback) = 0;
    };

    inline htd_main::IGraphProcessor::~IGraphProcessor() { }
}

#endif /* HTD_MAIN_IGRAPHPROCESSOR_HPP */
