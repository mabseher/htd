/*
 * File:   InducedSubgraphLabelingFunction.cpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/InducedSubgraphLabelingFunction.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <string>

htd::InducedSubgraphLabelingFunction::InducedSubgraphLabelingFunction(const htd::IHypergraph & graph) : graph_(graph)
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedges = graph_.hyperedges();

    hyperedges_ = htd::hyperedge_container(hyperedges.begin(), hyperedges.end());
}

htd::InducedSubgraphLabelingFunction::~InducedSubgraphLabelingFunction()
{

}

std::string htd::InducedSubgraphLabelingFunction::name() const
{
    return htd::InducedSubgraphLabelingFunction::INDUCED_SUBGRAPH_LABEL_IDENTIFIER;
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::InducedSubgraphLabelingFunction::computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices) const
{
    htd::VectorAdapter<htd::Hyperedge> label;

    for (const htd::Hyperedge & hyperedge : hyperedges_)
    {
        htd::vertex_container elements(hyperedge.begin(), hyperedge.end());

        std::sort(elements.begin(), elements.end());

        elements.erase(std::unique(elements.begin(), elements.end()), elements.end());

        if (std::includes(vertices.begin(), vertices.end(), elements.begin(), elements.end()))
        {
            label.container().push_back(hyperedge);
        }
    }

    return new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(label));
}

htd::Label<htd::ConstCollection<htd::Hyperedge>> * htd::InducedSubgraphLabelingFunction::computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const
{
    HTD_UNUSED(labels);

    return computeLabel(vertices);
}

htd::InducedSubgraphLabelingFunction * htd::InducedSubgraphLabelingFunction::clone(void) const
{
    return new htd::InducedSubgraphLabelingFunction(graph_);
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP */
