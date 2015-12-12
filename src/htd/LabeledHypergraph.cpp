/* 
 * File:   LabeledHypergraph.cpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_CPP
#define	HTD_HTD_LABELEDHYPERGRAPH_CPP

#include <htd/LabeledHypergraph.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <htd/Collection.hpp>

htd::LabeledHypergraph::LabeledHypergraph(void) : htd::Hypergraph::Hypergraph(), labelings_(new htd::LabelingCollection())
{

}
            
htd::LabeledHypergraph::LabeledHypergraph(std::size_t size) : htd::Hypergraph::Hypergraph(size), labelings_(new htd::LabelingCollection())
{

}

htd::LabeledHypergraph::LabeledHypergraph(const htd::LabeledHypergraph & original) : htd::Hypergraph::Hypergraph(original), labelings_(original.labelings_->clone())
{

}

htd::LabeledHypergraph::~LabeledHypergraph()
{
    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

void htd::LabeledHypergraph::removeVertex(htd::vertex_t vertex)
{
    htd::Hypergraph::removeVertex(vertex);

    labelings_->removeLabels(vertex);
}

void htd::LabeledHypergraph::removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge)
{
    htd::Hypergraph::removeVertex(vertex, addNeighborHyperedge);

    labelings_->removeLabels(vertex);
}

void htd::LabeledHypergraph::removeEdge(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    htd::Hypergraph::removeEdge(vertex1, vertex2);

    htd::hyperedge_t hyperedge;

    hyperedge.push_back(vertex1);
    hyperedge.push_back(vertex2);

    std::sort(hyperedge.begin(), hyperedge.end());

    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

    labelings_->removeLabels(hyperedge);
}

void htd::LabeledHypergraph::removeEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end)
{
    htd::Hypergraph::removeEdge(begin, end);

    htd::hyperedge_t hyperedge(begin, end);

    std::sort(hyperedge.begin(), hyperedge.end());

    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

    labelings_->removeLabels(hyperedge);
}

void htd::LabeledHypergraph::removeEdge(const htd::edge_t & edge)
{
    removeEdge(edge.first, edge.second);
}

void htd::LabeledHypergraph::removeEdge(const htd::hyperedge_t & edge)
{
    htd::Hypergraph::removeEdge(edge);

    htd::hyperedge_t hyperedge(edge);

    std::sort(hyperedge.begin(), hyperedge.end());

    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

    labelings_->removeLabels(hyperedge);
}

const htd::ILabelingCollection & htd::LabeledHypergraph::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::LabeledHypergraph::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::Collection<std::string> htd::LabeledHypergraph::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::LabeledHypergraph::labelName(htd::index_t index) const
{
    return labelings_->labelName(index);
}

const htd::ILabel & htd::LabeledHypergraph::label(const std::string & labelName, htd::vertex_t vertex) const
{
    return labelings_->labeling(labelName).label(vertex);
}

const htd::ILabel & htd::LabeledHypergraph::label(const std::string & labelName, const htd::hyperedge_t & edge) const
{
    return labelings_->labeling(labelName).label(edge);
}

void htd::LabeledHypergraph::setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setLabel(vertex, label);
}

void htd::LabeledHypergraph::setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label)
{
    if (!labelings_->isLabelingName(labelName))
    {
        labelings_->setLabeling(labelName, new htd::GraphLabeling());
    }

    labelings_->labeling(labelName).setLabel(edge, label);
}

void htd::LabeledHypergraph::removeLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeLabel(vertex);
    }
}

void htd::LabeledHypergraph::removeLabel(const std::string & labelName, const htd::hyperedge_t & edge)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).removeLabel(edge);
    }
}

void htd::LabeledHypergraph::swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    labelings_->swapLabels(vertex1, vertex2);
}

void htd::LabeledHypergraph::swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    labelings_->swapLabels(edge1, edge2);
}

void htd::LabeledHypergraph::swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).swapLabels(vertex1, vertex2);
    }
    else
    {
        throw std::logic_error("void htd::LabeledHypergraph::swapLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }
}

void htd::LabeledHypergraph::swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    if (labelings_->isLabelingName(labelName))
    {
        labelings_->labeling(labelName).swapLabels(edge1, edge2);
    }
    else
    {
        throw std::logic_error("void htd::LabeledHypergraph::swapLabel(const std::string &, htd::vertex_t, htd::vertex_t)");
    }
}

htd::LabeledHypergraph * htd::LabeledHypergraph::clone(void) const
{
    return new htd::LabeledHypergraph(*this);
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_CPP */
