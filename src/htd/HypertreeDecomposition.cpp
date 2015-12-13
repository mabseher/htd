/* 
 * File:   HypertreeDecomposition.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/HyperedgeContainerLabel.hpp>

#include <algorithm>

htd::HypertreeDecomposition::HypertreeDecomposition(void) : TreeDecomposition()
{
    
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::ILabeledTree & original) : TreeDecomposition(original)
{

}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::HypertreeDecomposition & original) : TreeDecomposition(original)
{

}

htd::HypertreeDecomposition::~HypertreeDecomposition()
{

}

void htd::HypertreeDecomposition::getEdgeLabel(htd::vertex_t vertex, htd::hyperedge_container & output) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & bagLabeling = (*labelings_)[htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER];

            auto & edgeLabel = dynamic_cast<const htd::HyperedgeContainerLabel *>(&(bagLabeling.label(vertex)))->container();

            std::copy(edgeLabel.begin(), edgeLabel.end(), std::back_inserter(output));
        }
    }
}

void htd::HypertreeDecomposition::setEdgeLabel(htd::vertex_t vertex, const htd::hyperedge_container & content)
{
    if (isVertex(vertex))
    {
        auto & edgeLabeling = (*labelings_)[htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER];

        edgeLabeling.setLabel(vertex, new htd::HyperedgeContainerLabel(content));
    }
    else
    {
        throw std::logic_error("void htd::HypertreeDecomposition::setEdgeLabel(htd::vertex_t, const htd::hyperedge_container &))");
    }
}

void htd::HypertreeDecomposition::setEdgeLabel(htd::vertex_t vertex, const htd::Collection<htd::hyperedge_t> & content)
{
    if (isVertex(vertex))
    {
        auto & edgeLabeling = (*labelings_)[htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER];

        edgeLabeling.setLabel(vertex, new htd::HyperedgeContainerLabel(content.begin(), content.end()));
    }
    else
    {
        throw std::logic_error("void htd::HypertreeDecomposition::setEdgeLabel(htd::vertex_t, const htd::Collection<htd::hyperedge_t> &)");
    }
}

htd::HypertreeDecomposition * htd::HypertreeDecomposition::clone(void) const
{
    return new HypertreeDecomposition(*this);
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_CPP */
