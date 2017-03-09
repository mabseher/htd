/*
 * File:   HgrFormatGraphToTreeDecompositionProcessor.cpp
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

#ifndef HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_CPP
#define HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_CPP

#include <htd_main/HgrFormatGraphToTreeDecompositionProcessor.hpp>

#include <htd_main/HgrFormatImporter.hpp>

#include <htd/main.hpp>

#include <fstream>
#include <stdexcept>

/**
 *  Private implementation details of class htd::HgrFormatGraphToTreeDecompositionProcessor.
 */
struct htd_main::HgrFormatGraphToTreeDecompositionProcessor::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), exporter_(nullptr), preprocessor_(nullptr)
    {

    }

    virtual ~Implementation()
    {
        if (exporter_ != nullptr)
        {
            delete exporter_;
        }

        if (preprocessor_ != nullptr)
        {
            delete preprocessor_;
        }
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The exporter which shall be used to export the resulting decomposition.
     */
    htd_main::ITreeDecompositionExporter * exporter_;

    /**
     *  The preprocessor which shall be used to preprocess the input graphs.
     */
    htd::IGraphPreprocessor * preprocessor_;

    /**
     *  A vector of callback functions which are invoked after parsing the input graph is finished.
     */
    std::vector<std::function<void(std::size_t, std::size_t)>> parsingCallbacks_;

    /**
     *  A vector of callback functions which are invoked after preprocessing the input graph.
     */
    std::vector<std::function<void(std::size_t, std::size_t)>> preprocessingCallbacks_;

    /**
     *  A vector of callback functions which are invoked after decomposing the input graph is finished.
     */
    std::vector<std::function<void(void)>> decompositionCallbacks_;

    /**
     *  Invoke all callback functions after parsing the input graph.
     *
     *  @param[in] vertexCount  The vertex count of the input graph.
     *  @param[in] edgeCount    The edge count of the input graph.
     */
    void invokeParsingCallbacks(std::size_t vertexCount, std::size_t edgeCount) const
    {
        for (const std::function<void(std::size_t, std::size_t)> & callback : parsingCallbacks_)
        {
            callback(vertexCount, edgeCount);
        }
    }

    /**
     *  Invoke all callback functions after preprocessing the input graph.
     *
     *  @param[in] vertexCount  The vertex count of the preprocessed input graph.
     *  @param[in] edgeCount    The edge count of the preprocessed input graph.
     */
    void invokePreprocessingCallbacks(std::size_t vertexCount, std::size_t edgeCount) const
    {
        for (const std::function<void(std::size_t, std::size_t)> & callback : preprocessingCallbacks_)
        {
            callback(vertexCount, edgeCount);
        }
    }

    /**
     *  Invoke all callback functions after after decomposing the input graph.
     */
    void invokeDecompositionCallbacks(void) const
    {
        for (const std::function<void(void)> & callback : decompositionCallbacks_)
        {
            callback();
        }
    }
};

htd_main::HgrFormatGraphToTreeDecompositionProcessor::HgrFormatGraphToTreeDecompositionProcessor(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd_main::HgrFormatGraphToTreeDecompositionProcessor::~HgrFormatGraphToTreeDecompositionProcessor(void)
{

}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::process(const std::string & inputFile, const std::string & outputFile) const
{
    std::ifstream inputStream(inputFile);
    std::ofstream outputStream(outputFile);

    process(inputStream, outputStream);
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::process(const std::string & inputFile, std::ostream & outputStream) const
{
    std::ifstream inputStream(inputFile);

    process(inputStream, outputStream);
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::process(std::istream & inputStream, const std::string & outputFile) const
{
    std::ofstream outputStream(outputFile);

    process(inputStream, outputStream);
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::process(std::istream & inputStream, std::ostream & outputStream) const
{
    htd_main::HgrFormatImporter importer(implementation_->managementInstance_);

    htd::IMultiHypergraph * graph = importer.import(inputStream);

    implementation_->invokeParsingCallbacks(graph->vertexCount(), graph->edgeCount());

    htd::ITreeDecompositionAlgorithm * algorithm = implementation_->managementInstance_->treeDecompositionAlgorithmFactory().createInstance();

    htd::ITreeDecomposition * decomposition = nullptr;

    if (implementation_->preprocessor_ != nullptr)
    {
        htd::IPreprocessedGraph * preprocessedGraph = implementation_->preprocessor_->prepare(*graph);

        HTD_ASSERT(preprocessedGraph != nullptr)

        implementation_->invokePreprocessingCallbacks(preprocessedGraph->vertexCount(), preprocessedGraph->edgeCount());

        decomposition = algorithm->computeDecomposition(*graph, *preprocessedGraph);

        delete preprocessedGraph;
    }
    else
    {
        decomposition = algorithm->computeDecomposition(*graph);
    }

    delete algorithm;

    if (decomposition != nullptr)
    {
        implementation_->invokeDecompositionCallbacks();

        if (implementation_->exporter_ != nullptr)
        {
            implementation_->exporter_->write(*decomposition, *graph, outputStream);
        }

        delete decomposition;
    }

    delete graph;
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::setPreprocessor(htd::IGraphPreprocessor * preprocessor)
{
    if (implementation_->preprocessor_ != nullptr)
    {
        delete implementation_->preprocessor_;
    }

    implementation_->preprocessor_ = preprocessor;
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::setExporter(htd_main::ITreeDecompositionExporter * exporter)
{
    if (implementation_->exporter_ != nullptr)
    {
        delete implementation_->exporter_;
    }

    implementation_->exporter_ = exporter;
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::registerParsingCallback(const std::function<void(std::size_t, std::size_t)> & callback)
{
    implementation_->parsingCallbacks_.push_back(callback);
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::registerPreprocessingCallback(const std::function<void(std::size_t, std::size_t)> & callback)
{
    implementation_->preprocessingCallbacks_.push_back(callback);
}

void htd_main::HgrFormatGraphToTreeDecompositionProcessor::registerDecompositionCallback(const std::function<void(void)> & callback)
{
    implementation_->decompositionCallbacks_.push_back(callback);
}

#endif /* HTD_MAIN_HGRFORMATGRAPHTOTREEDECOMPOSITIONPROCESSOR_CPP */
