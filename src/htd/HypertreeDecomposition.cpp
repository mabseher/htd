/* 
 * File:   HypertreeDecomposition.cpp
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

#ifndef HTD_HTD_HYPERTREEDECOMPOSITION_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/HypertreeDecomposition.hpp>
#include <htd/TreeDecomposition.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/Label.hpp>
#include <htd/VectorAdapter.hpp>

#include <algorithm>
#include <stdexcept>

htd::HypertreeDecomposition::HypertreeDecomposition(void) : htd::TreeDecomposition()
{
    
}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::ITreeDecomposition & original) : htd::TreeDecomposition(original)
{

}

htd::HypertreeDecomposition::HypertreeDecomposition(const htd::IHypertreeDecomposition & original) : htd::TreeDecomposition(original)
{

}

htd::HypertreeDecomposition::~HypertreeDecomposition()
{

}

htd::ConstCollection<htd::Hyperedge> htd::HypertreeDecomposition::coveringEdges(htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        auto & edgeLabel = dynamic_cast<const htd::Label<htd::ConstCollection<htd::Hyperedge>> *>(&(vertexLabel(htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER, vertex)))->value();

        return htd::ConstCollection<htd::Hyperedge>(edgeLabel);
    }
    else
    {
        throw std::logic_error("htd::ConstCollection<htd::Hyperedge> htd::HypertreeDecomposition::coveringEdges(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::Hyperedge>();
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const htd::hyperedge_container & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(htd::VectorAdapter<htd::Hyperedge>(content))));
    }
    else
    {
        throw std::logic_error("void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t, const htd::Hyperedge_container &))");
    }
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IHypertreeDecomposition::EDGE_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::Hyperedge>>(htd::ConstCollection<htd::Hyperedge>::getInstance(htd::VectorAdapter<htd::Hyperedge>(content))));
    }
    else
    {
        throw std::logic_error("void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t, const htd::IConstCollection<htd::Hyperedge> &)");
    }
}

htd::HypertreeDecomposition * htd::HypertreeDecomposition::clone(void) const
{
    return new htd::HypertreeDecomposition(*this);
}


htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITree & original)
{
    //TODO Implement!
    HTD_UNUSED(original)

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ILabeledTree & original)
{
    //TODO Implement!
    HTD_UNUSED(original)

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITreeDecomposition & original)
{
    //TODO Implement!
    HTD_UNUSED(original)

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::IHypertreeDecomposition & original)
{
    //TODO Implement!
    HTD_UNUSED(original)

    return *this;
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_CPP */
