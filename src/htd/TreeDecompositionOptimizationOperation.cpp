/*
 * File:   TreeDecompositionOptimizationOperation.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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

#ifndef HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP
#define	HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecompositionOptimizationOperation.hpp>
#include <htd/CompressionOperation.hpp>

#include <algorithm>

htd::TreeDecompositionOptimizationOperation::TreeDecompositionOptimizationOperation(const htd::ITreeDecompositionFitnessFunction & fitnessFunction) : fitnessFunction_(fitnessFunction.clone()), manipulationOperations_()
{

}

htd::TreeDecompositionOptimizationOperation::~TreeDecompositionOptimizationOperation()
{
    delete fitnessFunction_;
}

void htd::TreeDecompositionOptimizationOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::TreeDecompositionOptimizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::TreeDecompositionOptimizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    if (decomposition.vertexCount() > 0)
    {
        const htd::ITreeDecompositionFitnessFunction & fitnessFunction = *fitnessFunction_;

        htd::vertex_t optimalRoot = decomposition.root();

        double optimalFitness = fitnessFunction.fitness(decomposition);

        for (htd::vertex_t vertex : decomposition.vertices())
        {
            if (!decomposition.isRoot(vertex))
            {
                if (!manipulationOperations_.empty())
                {
                    htd::vertex_t currentVertex = vertex;

                    std::vector<htd::vertex_t> affectedVertices;

                    while (!decomposition.isRoot(currentVertex))
                    {
                        affectedVertices.push_back(currentVertex);

                        currentVertex = decomposition.parent(currentVertex);
                    }

                    affectedVertices.push_back(currentVertex);

                    //std::cout << "AFFECTED VERTICES: " << affectedVertices << std::endl;

                    htd::CompressionOperation compressionOperation;

                    compressionOperation.apply(decomposition, affectedVertices);

                    for (const htd::ITreeDecompositionManipulationOperation * operation : manipulationOperations_)
                    {
                        operation->apply(decomposition, affectedVertices, labelingFunctions);
                    }
                }

                decomposition.makeRoot(vertex);

                double currentFitness = fitnessFunction.fitness(decomposition);

                if (currentFitness > optimalFitness)
                {
                    optimalFitness = currentFitness;

                    optimalRoot = vertex;
                }
            }
        }

        decomposition.makeRoot(optimalRoot);
    }
}

void htd::TreeDecompositionOptimizationOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::vertex_t> & relevantVertices, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    HTD_UNUSED(relevantVertices)

    apply(decomposition, labelingFunctions);
}

htd::TreeDecompositionOptimizationOperation * htd::TreeDecompositionOptimizationOperation::clone(void) const
{
    return new htd::TreeDecompositionOptimizationOperation(*fitnessFunction_);
}

#endif /* HTD_HTD_TREEDECOMPOSITIONOPTIMIZATIONOPERATION_CPP */
