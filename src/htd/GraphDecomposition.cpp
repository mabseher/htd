/* 
 * File:   GraphDecomposition.cpp
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

#ifndef HTD_HTD_GRAPHDECOMPOSITION_CPP
#define	HTD_HTD_GRAPHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/GraphDecomposition.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/Label.hpp>

#include <algorithm>
#include <stdexcept>

htd::GraphDecomposition::GraphDecomposition(void) : htd::LabeledGraph::LabeledGraph()
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::GraphDecomposition & original) : htd::LabeledGraph::LabeledGraph(original)
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::IGraph & original) : htd::LabeledGraph::LabeledGraph(original)
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::ILabeledGraph & original) : htd::LabeledGraph::LabeledGraph(original)
{

}

htd::GraphDecomposition::GraphDecomposition(const htd::IGraphDecomposition & original) : htd::LabeledGraph::LabeledGraph(original)
{

}

htd::GraphDecomposition::~GraphDecomposition()
{

}

std::size_t htd::GraphDecomposition::bagSize(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = bagContent(vertex).size();
    }
    else
    {
        throw std::logic_error("std::size_t htd::GraphDecomposition::bagSize(htd::vertex_t) const");
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::GraphDecomposition::bagContent(htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        if (isLabeledVertex(htd::IGraphDecomposition::BAG_LABEL_IDENTIFIER, vertex))
        {
            auto & bagLabel = dynamic_cast<const htd::Label<htd::ConstCollection<htd::vertex_t>> *>(&(vertexLabel(htd::IGraphDecomposition::BAG_LABEL_IDENTIFIER, vertex)))->value();

            return htd::ConstCollection<htd::vertex_t>(bagLabel);
        }
        else
        {
            return htd::ConstCollection<htd::vertex_t>();
        }
    }
    else
    {
        throw std::logic_error("const htd::Collection<htd::vertex_t> htd::GraphDecomposition::bagContent(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>();
}

void htd::GraphDecomposition::setBagContent(htd::vertex_t vertex, const std::vector<htd::vertex_t> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IGraphDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::GraphDecomposition::setBagContent(htd::vertex_t, const std::vector<htd::vertex_t> &)");
    }
}

void htd::GraphDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    if (isVertex(vertex))
    {
        setVertexLabel(htd::IGraphDecomposition::BAG_LABEL_IDENTIFIER, vertex, new htd::Label<htd::ConstCollection<htd::vertex_t>>(htd::ConstCollection<htd::vertex_t>::getInstance(htd::VectorAdapter<htd::vertex_t>(content))));
    }
    else
    {
        throw std::logic_error("void htd::GraphDecomposition::setBagContent(htd::vertex_t, const htd::IConstCollection<htd::vertex_t> &)");
    }
}

std::size_t htd::GraphDecomposition::minimumBagSize(void) const
{
    bool start = true;

    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentBagSize = bagSize(vertex);

        if (start || currentBagSize < ret)
        {
            ret = currentBagSize;

            start = false;
        }
    }

    return ret;
}

std::size_t htd::GraphDecomposition::maximumBagSize(void) const
{
    std::size_t ret = 0;

    for (htd::vertex_t vertex : vertices())
    {
        std::size_t currentBagSize = bagSize(vertex);

        if (currentBagSize > ret)
        {
            ret = currentBagSize;
        }
    }

    return ret;
}

htd::GraphDecomposition * htd::GraphDecomposition::clone(void) const
{
    return new GraphDecomposition(*this);
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::GraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::ILabeledGraph & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);
    }

    return *this;
}

htd::GraphDecomposition & htd::GraphDecomposition::operator=(const htd::IGraphDecomposition & original)
{
    if (this != &original)
    {
        htd::LabeledGraph::operator=(original);
    }

    return *this;
}

#endif /* HTD_HTD_GRAPHDECOMPOSITION_CPP */
