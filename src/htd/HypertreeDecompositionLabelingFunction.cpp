/*
 * File:   HypertreeDecompositionLabelingFunction.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>

#include <htd/ILabel.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/HyperedgeContainerLabel.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>

#include <algorithm>
#include <string>

htd::HypertreeDecompositionLabelingFunction::HypertreeDecompositionLabelingFunction(const htd::IHypergraph & graph) : graph_(graph), setCoverAlgorithm_(htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm()), hyperedges_()
{
    htd::Collection<htd::Hyperedge> hyperedgeCollection = graph.hyperedges();

    hyperedges_.reserve(hyperedgeCollection.size());

    for (htd::Hyperedge originalHyperedge : hyperedgeCollection)
    {
        htd::Hyperedge newHyperedge(originalHyperedge.id());

        htd::Collection<htd::vertex_t> elementCollection = originalHyperedge.elements();

        htd::vertex_container elements(elementCollection.begin(), elementCollection.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges_.push_back(newHyperedge);
    }

    //TODO Overload operator < and std::less

    std::sort(hyperedges_.begin(), hyperedges_.end());

    hyperedges_.erase(std::unique(hyperedges_.begin(), hyperedges_.end()), hyperedges_.end());

    //TODO Remove hyperedges which are subset of another!
}

htd::HypertreeDecompositionLabelingFunction::~HypertreeDecompositionLabelingFunction()
{
    if (setCoverAlgorithm_ != nullptr)
    {
        delete setCoverAlgorithm_;

        setCoverAlgorithm_ = nullptr;
    }
}

std::string htd::HypertreeDecompositionLabelingFunction::name() const
{
    return htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER;
}

htd::ILabel * htd::HypertreeDecompositionLabelingFunction::computeLabel(const htd::Collection<htd::vertex_t> & vertices) const
{
    std::vector<htd::id_t> relevantContainerIds;

    std::vector<htd::vertex_container> relevantContainers;

    //TODO Exploit sortedness of hyperedges here and also at other places!
    for (auto it1 = hyperedges_.begin(); it1 < hyperedges_.end(); it1++)
    {
        const htd::Collection<htd::vertex_t> & elements1 = it1->elements();

        bool maximal = true;

        for (auto it2 = it1 + 1; it2 < hyperedges_.end(); it2++)
        {
            const htd::Collection<htd::vertex_t> & elements2 = it2->elements();

            if (std::includes(elements2.begin(), elements2.end(), elements1.begin(), elements1.end()))
            {
                maximal = false;
            }
        }

        if (maximal)
        {
            relevantContainers.push_back(htd::vertex_container(elements1.begin(), elements1.end()));

            relevantContainerIds.push_back(it1->id());
        }
    }

    std::vector<htd::index_t> setCoverResult;

    setCoverAlgorithm_->computeSetCover(vertices, relevantContainers, setCoverResult);

    htd::HyperedgeContainerLabel * label = new HyperedgeContainerLabel();

    htd::hyperedge_container & selectedHyperedges = label->container();

    for (htd::index_t selectedHyperedgeIndex : setCoverResult)
    {
        selectedHyperedges.push_back(htd::Hyperedge(relevantContainerIds[selectedHyperedgeIndex], relevantContainers[selectedHyperedgeIndex]));
    }

    return label;
}

htd::ILabel * htd::HypertreeDecompositionLabelingFunction::computeLabel(const htd::Collection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const
{
    HTD_UNUSED(labels);

    return computeLabel(vertices);
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP */
