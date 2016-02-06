/*
 * File:   HypertreeDecompositionLabelingFunction.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IHypertreeDecomposition.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>

#include <htd/ILabel.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <string>

htd::HypertreeDecompositionLabelingFunction::HypertreeDecompositionLabelingFunction(const htd::IMultiHypergraph & graph) : graph_(graph), hyperedges_()
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = graph.hyperedges();

    hyperedges_.reserve(hyperedgeCollection.size());

    for (const htd::Hyperedge & originalHyperedge : hyperedgeCollection)
    {
        const htd::ConstCollection<htd::vertex_t> & elementCollection = originalHyperedge.elements();

        htd::vertex_container elements(elementCollection.begin(), elementCollection.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        hyperedges_.push_back(htd::Hyperedge(originalHyperedge.id(), htd::ConstCollection<htd::vertex_t>(elements.begin(), elements.end())));
    }

    std::sort(hyperedges_.begin(), hyperedges_.end());

    hyperedges_.erase(std::unique(hyperedges_.begin(), hyperedges_.end()), hyperedges_.end());

    //TODO Remove hyperedges which are subset of another!
}

htd::HypertreeDecompositionLabelingFunction::~HypertreeDecompositionLabelingFunction()
{

}

std::string htd::HypertreeDecompositionLabelingFunction::name() const
{
    return htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER;
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::HypertreeDecompositionLabelingFunction::computeLabel(const std::vector<htd::vertex_t> & vertices) const
{
    return computeLabel(htd::ConstCollection<htd::vertex_t>::getInstance(vertices));
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::HypertreeDecompositionLabelingFunction::computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices) const
{
    std::vector<htd::id_t> relevantContainerIds;

    std::vector<htd::ConstCollection<htd::id_t>> relevantContainers;

    for (auto it1 = hyperedges_.begin(); it1 < hyperedges_.end(); it1++)
    {
        const htd::ConstCollection<htd::vertex_t> & elements1 = it1->elements();

        bool maximal = true;

        for (auto it2 = it1 + 1; it2 < hyperedges_.end(); it2++)
        {
            const htd::ConstCollection<htd::vertex_t> & elements2 = it2->elements();

            if (std::includes(elements2.begin(), elements2.end(), elements1.begin(), elements1.end()))
            {
                maximal = false;
            }
        }

        if (maximal)
        {
            relevantContainers.push_back(htd::ConstCollection<htd::id_t>::getInstance(elements1));

            relevantContainerIds.push_back(it1->id());
        }
    }

    htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::SetCoverAlgorithmFactory::instance().getSetCoverAlgorithm();

    htd::VectorAdapter<htd::Hyperedge> selectedHyperedges;

    for (htd::index_t selectedHyperedgeIndex : setCoverAlgorithm->computeSetCover(vertices, htd::ConstCollection<htd::ConstCollection<htd::id_t>>::getInstance(relevantContainers)))
    {
        selectedHyperedges.container().push_back(htd::Hyperedge(relevantContainerIds[selectedHyperedgeIndex], htd::ConstCollection<htd::vertex_t>::getInstance(relevantContainers[selectedHyperedgeIndex])));
    }

    delete setCoverAlgorithm;

    return new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(selectedHyperedges));
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::HypertreeDecompositionLabelingFunction::computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const
{
    HTD_UNUSED(labels)

    return computeLabel(vertices);
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::HypertreeDecompositionLabelingFunction::computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const
{
    HTD_UNUSED(labels)

    return computeLabel(vertices);
}

htd::HypertreeDecompositionLabelingFunction * htd::HypertreeDecompositionLabelingFunction::clone(void) const
{
    return new htd::HypertreeDecompositionLabelingFunction(graph_);
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONLABELINGFUNCTION_CPP */
