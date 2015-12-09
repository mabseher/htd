/*
 * File:   InducedSubgraphLabelingFunction.cpp
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

#ifndef HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP
#define	HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/InducedSubgraphLabelingFunction.hpp>

#include <htd/ILabel.hpp>
#include <htd/IHypergraph.hpp>
#include <htd/HyperedgeContainerLabel.hpp>

#include <algorithm>
#include <string>

htd::InducedSubgraphLabelingFunction::InducedSubgraphLabelingFunction(const htd::IHypergraph & graph) : graph_(graph)
{
    htd::Collection<htd::hyperedge_t> hyperedges = graph_.hyperedges();

    hyperedges_ = htd::hyperedge_container(hyperedges.begin(), hyperedges.end());
}

htd::InducedSubgraphLabelingFunction::~InducedSubgraphLabelingFunction()
{

}

std::string htd::InducedSubgraphLabelingFunction::name() const
{
    return htd::InducedSubgraphLabelingFunction::INDUCED_SUBGRAPH_LABEL_IDENTIFIER;
}

htd::ILabel * htd::InducedSubgraphLabelingFunction::computeLabel(const htd::vertex_container & vertices) const
{
    htd::hyperedge_container label;

    for (htd::hyperedge_t hyperedge : hyperedges_)
    {
        if (std::includes(vertices.begin(), vertices.end(), hyperedge.begin(), hyperedge.end()))
        {
            label.push_back(hyperedge);
        }
    }

    return new HyperedgeContainerLabel(label);
}

htd::ILabel * htd::InducedSubgraphLabelingFunction::computeLabel(const htd::vertex_container & vertices, const htd::ILabelCollection & labels) const
{
    HTD_UNUSED(labels);

    return computeLabel(vertices);
}

#endif /* HTD_HTD_INDUCEDSUBGRAPHLABELINGFUNCTION_CPP */
