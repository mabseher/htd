/*
 * File:   IGraphToTreeDecompositionProcessor.hpp
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

#ifndef HTD_IO_IGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP
#define HTD_IO_IGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP

#include <htd_io/IGraphProcessor.hpp>

#include <htd/FitnessEvaluation.hpp>

#include <string>
#include <iostream>
#include <functional>

namespace htd_io
{
    /**
     *  Common interface for classes which process graphs.
     */
    class IGraphToTreeDecompositionProcessor : public htd_io::IGraphProcessor
    {
        public:
            /**
             *  Destructor of a graph processor.
             */
            virtual ~IGraphToTreeDecompositionProcessor() = 0;

            /**
             *  Set the exporter which shall be used to export the resulting decomposition.
             *
             *  @param[in] exporter  The exporter which shall be used to export the resulting decomposition.
             *
             *  @note When calling this method the control over the memory region of the provided exporter is transferred to the
             *  graph processor. Deleting an exporter provided to this method outside the graph processor or assigning the same
             *  exporter multiple times will lead to undefined behavior.
             */
            virtual void setExporter(htd_io::ITreeDecompositionExporter * exporter) = 0;

            /**
             *  Register a new callback function which is invoked after preprocessing the input graph.
             *
             *  The first argument of the callback denotes the number of vertices of the input graph and
             *  the second argument of the callback provides the number of edges in the given input graph.
             *
             *  @note It is possible to append multiple callback functions. That is, this function does not
             *  override existing callback functions. Instead, all relevant callback functions are invoked
             *  after parsing is finished. The invocation of the callback functions is guaranteed to happen
             *  in the order the callback functions were registered.
             *
             *  @param[in] callback The new callback function which is invoked after preprocessing the input graph.
             */
            virtual void registerPreprocessingCallback(const std::function<void(std::size_t vertexCount, std::size_t edgeCount)> & callback) = 0;

            /**
             *  Register a new callback function which is invoked after decomposing the input graph is finished.
             *
             *  @note It is possible to append multiple callback functions. That is, this function does not
             *  override existing callback functions. Instead, all relevant callback functions are invoked
             *  after parsing is finished. The invocation of the callback functions is guaranteed to happen
             *  in the order the callback functions were registered.
             *
             *  @param[in] callback The new callback function which is invoked after decomposing the input graph is finished.
             */
            virtual void registerDecompositionCallback(const std::function<void(const htd::FitnessEvaluation &)> & callback) = 0;
    };

    inline htd_io::IGraphToTreeDecompositionProcessor::~IGraphToTreeDecompositionProcessor() { }
}

#endif /* HTD_IO_IGRAPHTOTREEDECOMPOSITIONPROCESSOR_HPP */
