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

const std::vector<htd::Hyperedge> & htd::HypertreeDecomposition::coveringEdges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return coveringEdges_.at(vertex);
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const std::vector<htd::Hyperedge> & content)
{
    HTD_ASSERT(isVertex(vertex))

    coveringEdges_[vertex] = content;
}

void htd::HypertreeDecomposition::setCoveringEdges(htd::vertex_t vertex, const htd::ConstCollection<htd::Hyperedge> & content)
{
    HTD_ASSERT(isVertex(vertex))

    std::vector<htd::Hyperedge> & coveringEdges = coveringEdges_[vertex];

    coveringEdges.clear();

    std::copy(content.begin(), content.end(), std::back_inserter(coveringEdges));
}

htd::HypertreeDecomposition * htd::HypertreeDecomposition::clone(void) const
{
    return new htd::HypertreeDecomposition(*this);
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ILabeledTree & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::ITreeDecomposition & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = std::vector<htd::Hyperedge>();
        }
    }

    return *this;
}

htd::HypertreeDecomposition & htd::HypertreeDecomposition::operator=(const htd::IHypertreeDecomposition & original)
{
    if (this != &original)
    {
        htd::TreeDecomposition::operator=(original);

        for (htd::vertex_t vertex : original.vertices())
        {
            coveringEdges_[vertex] = original.coveringEdges(vertex);
        }
    }

    return *this;
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITION_CPP */
