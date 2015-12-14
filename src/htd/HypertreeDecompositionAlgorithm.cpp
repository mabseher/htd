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
#include <htd/VertexContainerLabel.hpp>
#include <htd/HyperedgeContainerLabel.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>

#include <cstdarg>
#include <stack>
#include <vector>

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(void) : treeDecompositionAlgorithm_(htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm()), setCoverAlgorithm_(htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm())
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const std::vector<htd::ILabelingFunction *> & labelingFunctions) : treeDecompositionAlgorithm_(htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm()), setCoverAlgorithm_(htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm())
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm, const htd::ISetCoverAlgorithm & setCoverAlgorithm) : treeDecompositionAlgorithm_(treeDecompositionAlgorithm.clone()), setCoverAlgorithm_(setCoverAlgorithm.clone())
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm, const htd::ISetCoverAlgorithm & setCoverAlgorithm, const std::vector<htd::ILabelingFunction *> & labelingFunctions) : treeDecompositionAlgorithm_(treeDecompositionAlgorithm.clone()), setCoverAlgorithm_(setCoverAlgorithm.clone())
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::HypertreeDecompositionAlgorithm::~HypertreeDecompositionAlgorithm()
{
    if (treeDecompositionAlgorithm_ != nullptr)
    {
        delete treeDecompositionAlgorithm_;

        treeDecompositionAlgorithm_ = nullptr;
    }

    if (setCoverAlgorithm_ != nullptr)
    {
        delete setCoverAlgorithm_;

        setCoverAlgorithm_ = nullptr;
    }
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecomposition * treeDecomposition = treeDecompositionAlgorithm_->computeDecomposition(graph);

    if (treeDecomposition != nullptr)
    {
        ret = htd::HypertreeDecompositionFactory::instance().getHypertreeDecomposition(*treeDecomposition);

        if (ret != nullptr)
        {
            htd::HypertreeDecompositionLabelingFunction hypertreeDecompositionLabelingFunction(graph, *setCoverAlgorithm_);

            for (htd::vertex_t vertex : ret->vertices())
            {
                auto label = (dynamic_cast<const htd::VertexContainerLabel *>(&(ret->label(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex))))->container();

                htd::ILabel * newLabel = hypertreeDecompositionLabelingFunction.computeLabel(label);

                ret->setLabel(hypertreeDecompositionLabelingFunction.name(), vertex, newLabel);
            }

            delete treeDecomposition;
        }
    }

    return ret;
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

    htd::ITreeDecomposition * treeDecomposition = treeDecompositionAlgorithm_->computeDecomposition(graph);

    if (treeDecomposition != nullptr)
    {
        ret = htd::HypertreeDecompositionFactory::instance().getHypertreeDecomposition(*treeDecomposition);

        if (ret != nullptr)
        {
            htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm();

            if (setCoverAlgorithm != nullptr)
            {
                htd::HypertreeDecompositionLabelingFunction hypertreeDecompositionLabelingFunction(graph, *setCoverAlgorithm);

                for (htd::vertex_t vertex : ret->vertices())
                {
                    auto label = (dynamic_cast<const htd::VertexContainerLabel *>(&(ret->label(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex))))->container();

                    htd::ILabel * newLabel = hypertreeDecompositionLabelingFunction.computeLabel(label);

                    ret->setLabel(hypertreeDecompositionLabelingFunction.name(), vertex, newLabel);
                }

                delete setCoverAlgorithm;

                for (auto & labelingFunction : labelingFunctions)
                {
                    for (htd::vertex_t vertex : ret->vertices())
                    {
                        auto label = (dynamic_cast<const htd::VertexContainerLabel *>(&(ret->label(htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER, vertex))))->container();

                        htd::ILabelCollection * labelCollection = ret->labelings().exportLabelCollection(vertex);

                        //TODO Optimize
                        htd::ILabel * newLabel = labelingFunction->computeLabel(label, *labelCollection);

                        delete labelCollection;

                        ret->setLabel(labelingFunction->name(), vertex, newLabel);
                    }
                }
            }

            delete treeDecomposition;
        }
    }

    return ret;
}

htd::HypertreeDecompositionAlgorithm * htd::HypertreeDecompositionAlgorithm::clone(void) const
{
    return new HypertreeDecompositionAlgorithm(*treeDecompositionAlgorithm_, *setCoverAlgorithm_);
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP */
