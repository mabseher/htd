/* 
 * File:   LabeledHypergraph.hpp
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

#ifndef HTD_HTD_LABELEDHYPERGRAPH_HPP
#define	HTD_HTD_LABELEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Hypergraph.hpp>
#include <htd/IMutableLabeledHypergraph.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/BidirectionalGraphLabeling.hpp>
#include <htd/Label.hpp>
#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>

#include <set>
#include <vector>
#include <stdexcept>

namespace htd
{
    template<typename VertexLabelType, typename HyperedgeLabelType>
    class LabeledHypergraph : public virtual htd::Hypergraph, public virtual htd::IMutableLabeledHypergraph
    {
        public:
            using htd::Hypergraph::vertexCount;
            using htd::Hypergraph::edgeCount;
            using htd::Hypergraph::isVertex;
            using htd::Hypergraph::isEdge;
            using htd::Hypergraph::vertex;
            using htd::Hypergraph::isConnected;
            using htd::Hypergraph::isNeighbor;
            using htd::Hypergraph::neighborCount;
            using htd::Hypergraph::getNeighbors;
            using htd::Hypergraph::neighbor;
            using htd::Hypergraph::isIsolatedVertex;
            using htd::Hypergraph::getHyperedges;
            using htd::Hypergraph::hyperedge;
            using htd::Hypergraph::addVertex;
            using htd::Hypergraph::removeVertex;
            using htd::Hypergraph::addEdge;
            using htd::Hypergraph::removeEdge;

            /**
             *  Constant for the identifier of the name label.
             */
            static constexpr const char * NAME_LABEL_IDENTIFIER = "Name";

            LabeledHypergraph(void) : htd::Hypergraph(), labelings_()
            {
                labelings_.setLabeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER, new htd::BidirectionalGraphLabeling());
            }
            
            LabeledHypergraph(std::size_t size) : htd::Hypergraph(size), labelings_()
            {
                labelings_.setLabeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER, new htd::BidirectionalGraphLabeling());
            }

            ~LabeledHypergraph<VertexLabelType, HyperedgeLabelType>()
            {

            }

            std::size_t edgeCount(const VertexLabelType & vertexLabel) const
            {
                std::size_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::edgeCount(locatedVertex);
                }
                else
                {
                    throw std::logic_error("std::size_t htd::LabeledHypergraph::edgeCount(const VertexLabelType &) const");
                }

                return ret;
            }

            bool isVertex(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        ret = labeling->isVertexLabel(label);
                    }
                }

                return ret;
            }

            bool isEdge(const HyperedgeLabelType & edgeLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                    if (labeling != nullptr)
                    {
                        Label<HyperedgeLabelType> label(edgeLabel);

                        ret = labeling->isHyperedgeLabel(label);
                    }
                }

                return ret;
            }

            void isEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (isVertex(*it))
                    {
                        hyperedge.push_back(vertex(*it));
                    }
                    else
                    {
                        ok = false;
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    ok = htd::Hypergraph::isEdge(hyperedge);
                }

                return ok;
            }

            bool isConnected(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::Vertex::UNKNOWN && locatedVertex2 != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::isConnected(locatedVertex1, locatedVertex2);
                }

                return ret;
            }

            bool isNeighbor(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::Vertex::UNKNOWN && locatedVertex2 != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::isNeighbor(locatedVertex1, locatedVertex2);
                }

                return ret;
            }
            
            std::size_t neighborCount(const VertexLabelType & vertexLabel) const
            {
                std::size_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::neighborCount(locatedVertex);
                }

                return ret;
            }
            
            void getNeighbors(const VertexLabelType & vertexLabel, htd::vertex_container & output) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    htd::Hypergraph::getNeighbors(locatedVertex, output);
                }
            }

            htd::vertex_t neighbor(const VertexLabelType & vertexLabel, htd::index_t index) const
            {
                htd::vertex_t ret = 0;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::neighbor(locatedVertex, index);
                }
                else
                {
                    throw std::out_of_range("htd::vertex_t htd::LabeledHypergraph::neighbor(const VertexLabelType &, htd::index_t)");
                }

                return ret;
            }

            bool isIsolatedVertex(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    ret = htd::Hypergraph::isIsolatedVertex(locatedVertex);
                }

                return ret;
            }

            void getHyperedges(htd::hyperedge_container & output, const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    htd::Hypergraph::getHyperedges(output, locatedVertex);
                }
            }

            const htd::hyperedge_t & hyperedge(htd::index_t index, const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex == htd::Vertex::UNKNOWN)
                {
                    throw std::out_of_range("htd::vertex_t htd::LabeledHypergraph::hyperedge(htd::index_t, const VertexLabelType &)");
                }

                return htd::Hypergraph::hyperedge(index, locatedVertex);
            }

            htd::vertex_t addVertex(const VertexLabelType & vertexLabel)
            {
                htd::vertex_t locatedVertex = lookupVertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::addVertex(const VertexLabelType &)");
                }

                htd::vertex_t ret = htd::Hypergraph::addVertex();

                setVertexName(ret, vertexLabel);

                return ret;
            }

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE
            {
                labelings_.removeLabels(vertex);

                htd::Hypergraph::removeVertex(vertex);
            }

            void removeVertex(const VertexLabelType & vertexLabel)
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    labelings_.removeLabels(locatedVertex);

                    htd::Hypergraph::removeVertex(locatedVertex);
                }
            }

            void removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge) HTD_OVERRIDE
            {
                labelings_.removeLabels(vertex);

                htd::Hypergraph::removeVertex(vertex, addNeighborHyperedge);
            }

            void removeVertex(const VertexLabelType & vertexLabel, bool addNeighborHyperedge)
            {
                htd::vertex_t locatedVertex = vertex(vertexLabel);

                if (locatedVertex != htd::Vertex::UNKNOWN)
                {
                    htd::Hypergraph::removeVertex(locatedVertex, addNeighborHyperedge);

                    labelings_.removeLabels(locatedVertex);
                }
            }

            void addEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2)
            {
                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);

                if (locatedVertex1 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex1 = addVertex(vertexLabel1);
                }

                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex2 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex2 = addVertex(vertexLabel2);
                }

                htd::Hypergraph::addEdge(locatedVertex1, locatedVertex2);
            }

            void addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2, const HyperedgeLabelType & label)
            {
                htd::Hypergraph::addEdge(vertex1, vertex2);

                htd::hyperedge_t hyperedge;

                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                setHyperedgeName(hyperedge, label);
            }

            void addEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2, const HyperedgeLabelType & label)
            {
                htd::vertex_t locatedVertex1 = lookupVertex(vertexLabel1);

                if (locatedVertex1 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex1 = addVertex(vertexLabel1);
                }

                htd::vertex_t locatedVertex2 = lookupVertex(vertexLabel2);

                if (locatedVertex2 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex2 = addVertex(vertexLabel2);
                }

                addEdge(locatedVertex1, locatedVertex2, label);
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(lookupVertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::addEdge(hyperedge);
                }
            }

            void addEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end, const HyperedgeLabelType & label)
            {
                htd::Hypergraph::addEdge(begin, end);

                htd::hyperedge_t hyperedge(begin, end);

                setHyperedgeName(hyperedge, label);
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end, const HyperedgeLabelType & label)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(vertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::addEdge(hyperedge);

                    setHyperedgeName(hyperedge, label);
                }
            }

            void addEdge(const std::pair<VertexLabelType, VertexLabelType> & edge)
            {
                addEdge(edge.first, edge.second);
            }

            void addEdge(const htd::edge_t & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.first, edge.second, label);
            }

            void addEdge(const std::pair<VertexLabelType, VertexLabelType> & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.first, edge.second, label);
            }
            
            void addEdge(const std::vector<VertexLabelType> & edge)
            {
                addEdge(edge.begin(), edge.end());
            }

            void addEdge(const std::vector<VertexLabelType> & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.begin(), edge.end(), label);
            }

            void addEdge(const htd::hyperedge_t & edge, const HyperedgeLabelType & label)
            {
                addEdge(edge.begin(), edge.end(), label);
            }

            void removeEdge(const HyperedgeLabelType & label)
            {
                if (isHyperedgeName(label))
                {
                    const htd::hyperedge_t & hyperedge = lookupHyperedge(label);

                    htd::Hypergraph::removeEdge(hyperedge);

                    labelings_.removeLabels(hyperedge);
                }
            }
            
            void removeEdge(const VertexLabelType & vertexLabel1, const VertexLabelType & vertexLabel2)
            {
                htd::vertex_t locatedVertex1 = vertex(vertexLabel1);
                htd::vertex_t locatedVertex2 = vertex(vertexLabel2);

                if (locatedVertex1 != htd::Vertex::UNKNOWN && locatedVertex2 != htd::Vertex::UNKNOWN)
                {
                    htd::Hypergraph::removeEdge(locatedVertex1, locatedVertex2);
                }
            }
            
            void removeEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    ok = isVertex(*it);

                    if (ok)
                    {
                        hyperedge.push_back(vertex(*it));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::removeEdge(hyperedge);

                    labelings_.removeLabels(hyperedge);
                }
            }
            
            void removeEdge(const std::pair<VertexLabelType, VertexLabelType> & edge)
            {
                removeEdge(edge.first, edge.second);
            }
            
            void removeEdge(const std::vector<VertexLabelType> & edge)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto & vertex : edge)
                {
                    ok = isVertex(vertex);

                    if (ok)
                    {
                        hyperedge.push_back(vertex(vertex));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::Hypergraph::removeEdge(hyperedge);

                    labelings_.removeLabels(hyperedge);
                }
            }

            const htd::ILabelingCollection & labelings(void) const HTD_OVERRIDE
            {
                return labelings_;
            }

            std::size_t labelCount(void) const HTD_OVERRIDE
            {
                return labelings_.labelCount();
            }


            htd::Collection<std::string> labelNames(void) const HTD_OVERRIDE
            {
                return labelings_.labelNames();
            }

            const std::string & labelName(htd::index_t index) const HTD_OVERRIDE
            {
                if (index >= labelings_.labelCount())
                {
                    throw std::out_of_range("const std::string & htd::LabeledHypergraph::labelName(htd::index_t) const");
                }

                return labelings_.labelName(index);
            }

            const htd::ILabel & label(const std::string & labelName, htd::vertex_t vertex) const HTD_OVERRIDE
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::out_of_range("const htd::ILabel & htd::LabeledHypergraph::label(const std::string &, htd::vertex_t) const");
                }

                auto & labeling = labelings_.labeling(labelName);

                if (!labeling.hasLabel(vertex))
                {
                    throw std::logic_error("const htd::ILabel & htd::LabeledHypergraph::label(const std::string &, htd::vertex_t) const");
                }

                return labeling.label(vertex);
            }

            const htd::ILabel & label(const std::string & labelName, const htd::hyperedge_t & edge) const HTD_OVERRIDE
            {
                if (!labelings_.isLabelingName(labelName))
                {
                    throw std::out_of_range("const htd::ILabel & htd::LabeledHypergraph::label(const std::string &, const htd::hyperedge_t &) const");
                }

                auto & labeling = labelings_.labeling(labelName);

                if (!labeling.hasLabel(edge))
                {
                    throw std::logic_error("const htd::ILabel & htd::LabeledHypergraph::label(const std::string &, const htd::hyperedge_t &) const");
                }

                return labeling.label(edge);
            }

            void swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE
            {
                if (isVertex(vertex1) && isVertex(vertex2))
                {
                    labelings_.swapLabels(vertex1, vertex2);
                }
            }

            void swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE
            {
                if (isEdge(edge1) && isEdge(edge2))
                {
                    labelings_.swapLabels(edge1, edge2);
                }
            }

            void swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2) HTD_OVERRIDE
            {
                if (isVertex(vertex1) && isVertex(vertex2))
                {
                    if (labelings_.isLabelingName(labelName))
                    {
                        labelings_[labelName].swapLabels(vertex1, vertex2);
                    }
                }
            }

            void swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2) HTD_OVERRIDE
            {
                if (isEdge(edge1) && isEdge(edge2))
                {
                    if (labelings_.isLabelingName(labelName))
                    {
                        labelings_[labelName].swapLabels(edge1, edge2);
                    }
                }
            }

            bool hasName(htd::vertex_t vertex) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(vertex);
                    }
                }

                return ret;
            }

            bool hasName(const htd::hyperedge_t & edge) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(edge);
                    }
                }

                return ret;
            }

            bool hasLabel(const std::string & labelName, htd::vertex_t vertex) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(labelName))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(labelings_.labeling(labelName));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(vertex);
                    }
                }

                return ret;
            }

            bool hasLabel(const std::string & labelName, const htd::hyperedge_t & edge) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(labelName))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(labelings_.labeling(labelName));

                    if (labeling != nullptr)
                    {
                        ret = labeling->hasLabel(edge);
                    }
                }

                return ret;
            }

            const VertexLabelType & name(htd::vertex_t vertex) const
            {
                if (!labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::name(htd::vertex_t) const");
                }

                auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::name(htd::vertex_t) const");
                }

                if (!labeling->hasLabel(vertex))
                {
                    throw std::logic_error("const VertexLabelType & htd::LabeledHypergraph::name(htd::vertex_t) const");
                }

                auto label = dynamic_cast<const htd::Label<VertexLabelType> *>(&(labeling->label(vertex)));

                return label->value();
            }

            const HyperedgeLabelType & name(const htd::hyperedge_t & edge) const
            {
                if (!labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::name(const htd::hyperedge_t &) const");
                }

                auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::name(const htd::hyperedge_t &) const");
                }

                if (!labeling->hasLabel(vertex))
                {
                    throw std::logic_error("const HyperedgeLabelType & htd::LabeledHypergraph::name(const htd::hyperedge_t &) const");
                }

                auto label = dynamic_cast<const htd::Label<HyperedgeLabelType> *>(labeling->label(edge));

                return label->value();
            }

            void setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_[labelName].setLabel(vertex, label);
            }

            void setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_[labelName].setLabel(edge, label);
            }

            void removeLabel(const std::string & labelName, htd::vertex_t vertex)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_[labelName].removeLabel(vertex);
            }

            void removeLabel(const std::string & labelName, const htd::hyperedge_t & edge)
            {
                if (labelings_.isLabelingName(labelName))
                {
                    labelings_.setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_[labelName].removeLabel(edge);
            }

            bool isVertexName(const VertexLabelType & vertexLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_.labeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER)));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        ret = labeling->isVertexLabel(label);
                    }
                }

                return ret;
            }

            bool isHyperedgeName(const HyperedgeLabelType & edgeLabel) const
            {
                bool ret = false;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_.labeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER)));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(edgeLabel);

                        ret = labeling->isHyperedgeLabel(label);
                    }
                }

                return ret;
            }

            htd::vertex_t getVertex(const VertexLabelType & label) const
            {
                if (isVertex(label))
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::getVertex(const VertexLabelType &) const");
                }

                return vertex(label);
            }

            const htd::hyperedge_t & getHyperedge(const HyperedgeLabelType & label) const
            {
                if (isHyperedge(label))
                {
                    throw std::logic_error("htd::vertex_t htd::LabeledHypergraph::getHyperedge(const HyperedgeLabelType &) const");
                }

                return hyperedge(label);
            }

        private:
            htd::LabelingCollection labelings_;

            htd::vertex_t lookupVertex(const VertexLabelType & vertexLabel) const
            {
                htd::vertex_t ret = htd::Vertex::UNKNOWN;

                if (labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                    if (labeling != nullptr)
                    {
                        Label<VertexLabelType> label(vertexLabel);

                        if (labeling->isVertexLabel(label))
                        {
                            ret = labeling->getVertex(label);
                        }
                    }
                }

                return ret;
            }

            const htd::hyperedge_t & lookupHyperedge(const HyperedgeLabelType & edgeLabel) const
            {
                if (!labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                auto labeling = dynamic_cast<const htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                if (labeling == nullptr)
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                Label<VertexLabelType> label(edgeLabel);

                if (!labeling->isHyperedgeLabel(label))
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::LabeledHypergraph::hyperedge(const HyperedgeLabelType &) const");
                }

                return labeling->getHyperedge(label);
            }

            void setVertexName(htd::vertex_t vertex, const VertexLabelType & vertexLabel)
            {
                if (!labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    labelings_.setLabeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER, new htd::BidirectionalGraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                if (labeling != nullptr)
                {
                    labeling->setLabel(vertex, new htd::Label<VertexLabelType>(vertexLabel));
                }
            }

            void setHyperedgeName(const htd::hyperedge_t & edge, const HyperedgeLabelType & edgeLabel)
            {
                if (!labelings_.isLabelingName(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER))
                {
                    labelings_.setLabeling(htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER, new htd::BidirectionalGraphLabeling());
                }

                auto labeling = dynamic_cast<htd::IBidirectionalGraphLabeling *>(&(labelings_[htd::LabeledHypergraph<VertexLabelType, HyperedgeLabelType>::NAME_LABEL_IDENTIFIER]));

                if (labeling != nullptr)
                {
                    labeling->setLabel(edge, new htd::Label<HyperedgeLabelType>(edgeLabel));
                }
            }

            LabeledHypergraph<VertexLabelType, HyperedgeLabelType> * clone(void) const
            {
                return new LabeledHypergraph<VertexLabelType, HyperedgeLabelType>(*this);
            }
    };
}

#endif /* HTD_HTD_LABELEDHYPERGRAPH_HPP */
