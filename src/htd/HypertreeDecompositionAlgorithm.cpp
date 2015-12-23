/* 
 * File:   HypertreeDecompositionAlgorithm.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/HypertreeDecompositionAlgorithm.hpp>

#include <htd/IHypertreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>

#include <cstdarg>
#include <vector>

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(void)
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const std::vector<htd::ILabelingFunction *> & labelingFunctions)
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::HypertreeDecompositionAlgorithm::~HypertreeDecompositionAlgorithm()
{

}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    return computeDecomposition(graph, std::vector<htd::ILabelingFunction *>());
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const
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

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

    if (algorithm == nullptr)
    {
        throw std::logic_error("htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph &, const std::vector<htd::ILabelingFunction *> &) const");
    }

    htd::ITreeDecomposition * treeDecomposition = algorithm->computeDecomposition(graph);

    delete algorithm;

    ret = htd::HypertreeDecompositionFactory::instance().getHypertreeDecomposition(*treeDecomposition);

    if (ret != nullptr)
    {
        htd::HypertreeDecompositionLabelingFunction hypertreeDecompositionLabelingFunction(graph);

        for (htd::vertex_t vertex : ret->vertices())
        {
            htd::ILabel * newLabel = hypertreeDecompositionLabelingFunction.computeLabel(ret->bagContent(vertex));

            ret->setVertexLabel(hypertreeDecompositionLabelingFunction.name(), vertex, newLabel);
        }

        for (auto & labelingFunction : labelingFunctions)
        {
            for (htd::vertex_t vertex : ret->vertices())
            {
                htd::ILabelCollection * labelCollection = ret->labelings().exportVertexLabelCollection(vertex);

                htd::ILabel * newLabel = labelingFunction->computeLabel(ret->bagContent(vertex), *labelCollection);

                delete labelCollection;

                ret->setVertexLabel(labelingFunction->name(), vertex, newLabel);
            }
        }

        delete treeDecomposition;
    }

    return ret;
}

//TODO Consider labeling functions!
htd::HypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithm::clone(void) const
{
    return new HypertreeDecompositionAlgorithm();
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP */
