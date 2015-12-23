/* 
 * File:   PostProcessingPathDecompositionAlgorithm.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/PostProcessingPathDecompositionAlgorithm.hpp>

#include <htd/IPathDecomposition.hpp>
#include <htd/IMutablePathDecomposition.hpp>
#include <htd/PathDecompositionFactory.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/CompressionOperation.hpp>
#include <htd/JoinNodeReplacementOperation.hpp>

#include <cstdarg>
#include <vector>

htd::PostProcessingPathDecompositionAlgorithm::PostProcessingPathDecompositionAlgorithm(void)
{

}

htd::PostProcessingPathDecompositionAlgorithm::PostProcessingPathDecompositionAlgorithm(const std::vector<htd::ILabelingFunction *> & labelingFunctions)
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::PostProcessingPathDecompositionAlgorithm::~PostProcessingPathDecompositionAlgorithm()
{

}

htd::IPathDecomposition * htd::PostProcessingPathDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::ILabelingFunction *>());
}

htd::IPathDecomposition * htd::PostProcessingPathDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const
{
    va_list arguments;

    va_start(arguments, labelingFunctionCount);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    for (int labelingFunctionIndex = 0; labelingFunctionIndex < labelingFunctionCount; labelingFunctionIndex++)
    {
        labelingFunctions.push_back(va_arg(arguments, htd::ILabelingFunction *));
    }

    return computeDecomposition(graph, labelingFunctions);
}

htd::IPathDecomposition * htd::PostProcessingPathDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::IMutablePathDecomposition * ret = nullptr;

    htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

    if (algorithm == nullptr)
    {
        throw std::logic_error("htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph &, const std::vector<htd::ILabelingFunction *> &) const");
    }

    htd::ITreeDecomposition * treeDecomposition = algorithm->computeDecomposition(graph);

    delete algorithm;

    htd::IMutableTreeDecomposition * mutableTreeDecomposition = htd::TreeDecompositionFactory::instance().getTreeDecomposition(*treeDecomposition);

    delete treeDecomposition;

    htd::CompressionOperation compressionOperation;

    compressionOperation.apply(*mutableTreeDecomposition);

    htd::JoinNodeReplacementOperation joinNodeReplacementOperation(graph);

    joinNodeReplacementOperation.apply(*mutableTreeDecomposition);

    ret = toPathDecomposition(*mutableTreeDecomposition);

    delete mutableTreeDecomposition;

    for (auto & labelingFunction : labelingFunctions)
    {
        for (htd::vertex_t vertex : ret->vertices())
        {
            htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

            //TODO Optimize
            htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

            delete labelCollection;

            ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
        }
    }

    return ret;
}

htd::IMutablePathDecomposition * htd::PostProcessingPathDecompositionAlgorithm::toPathDecomposition(const htd::ITreeDecomposition & decomposition) const
{
    htd::IMutablePathDecomposition * ret = htd::PathDecompositionFactory::instance().getPathDecomposition();

    if (decomposition.vertexCount() > 0)
    {
        const htd::Collection<std::string> labelNames = decomposition.labelNames();

        htd::vertex_t currentVertex = decomposition.root();

        htd::vertex_t newVertex = ret->insertRoot();

        for (const std::string & labelName : labelNames)
        {
            if (decomposition.isLabeledVertex(labelName, currentVertex))
            {
                ret->setVertexLabel(labelName, newVertex, decomposition.vertexLabel(labelName, currentVertex).clone());
            }
        }

        while (decomposition.childCount(currentVertex) == 1)
        {
            currentVertex = decomposition.child(currentVertex, 0);

            newVertex = ret->addChild(newVertex);

            for (const std::string & labelName : labelNames)
            {
                if (decomposition.isLabeledVertex(labelName, currentVertex))
                {
                    ret->setVertexLabel(labelName, newVertex, decomposition.vertexLabel(labelName, currentVertex).clone());
                }
            }
        }

        if (decomposition.childCount(currentVertex) != 0)
        {
            throw std::logic_error("htd::IMutablePathDecomposition * htd::PostProcessingPathDecompositionAlgorithm::toPathDecomposition(const htd::ITreeDecomposition &) const");
        }
    }

    return ret;
}

//TODO Consider labeling functions!
htd::PostProcessingPathDecompositionAlgorithm * htd::PostProcessingPathDecompositionAlgorithm::clone(void) const
{
    return new PostProcessingPathDecompositionAlgorithm();
}

#endif /* HTD_HTD_POSTPROCESSINGPATHDECOMPOSITIONALGORITHM_CPP */
