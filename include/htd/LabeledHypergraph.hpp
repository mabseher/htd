/* 
 * File:   MutableLabeledHypergraphImpl.hpp
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

#ifndef HTD_HTD_MUTABLELABELEDHYPERGRAPHIMPL_HPP
#define	HTD_HTD_MUTABLELABELEDHYPERGRAPHIMPL_HPP

#include <htd/MutableHypergraphImpl.hpp>
#include <htd/ILabeledHypergraph.hpp>
#include <htd/BidirectionalGraphLabeling.hpp>
#include <htd/Label.hpp>

#include <set>
#include <vector>
#include <stdexcept>

namespace htd
{
    template<typename VertexLabelType, typename HyperedgeLabelType>
    class MutableLabeledHypergraphImpl : public htd::MutableHypergraphImpl
    {
        public:
            MutableLabeledHypergraphImpl<VertexLabelType, HyperedgeLabelType>(void) : MutableHypergraphImpl(), labeling_()
            {

            }
            
            MutableLabeledHypergraphImpl<VertexLabelType, HyperedgeLabelType>(std::size_t size) : MutableHypergraphImpl(size), labeling_()
            {

            }
            
            ~MutableLabeledHypergraphImpl<VertexLabelType, HyperedgeLabelType>()
            {

            }

            std::size_t edgeCount(VertexLabelType vertex) const
            {
                std::size_t ret = 0;

                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    ret = htd::MutableHypergraphImpl::edgeCount(labeling_.getVertex(label));
                }

                return ret;
            }

            bool isVertex(VertexLabelType vertex) const
            {
                bool ret = false;

                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    ret = htd::MutableHypergraphImpl::isVertex(labeling_.getVertex(label));
                }

                return ret;
            }

            bool isConnected(VertexLabelType vertex1, VertexLabelType vertex2) const
            {
                bool ret = false;

                Label<VertexLabelType> label1(vertex1);
                Label<VertexLabelType> label2(vertex2);

                if (labeling_.isVertexLabel(label1) && labeling_.isVertexLabel(label2))
                {
                    ret = htd::MutableHypergraphImpl::isConnected(labeling_.getVertex(label1), labeling_.getVertex(label2));
                }

                return ret;
            }

            bool isNeighbor(VertexLabelType vertex1, VertexLabelType vertex2) const
            {
                bool ret = false;

                Label<VertexLabelType> label1(vertex1);
                Label<VertexLabelType> label2(vertex2);

                if (labeling_.isVertexLabel(label1) && labeling_.isVertexLabel(label2))
                {
                    ret = htd::MutableHypergraphImpl::isNeighbor(labeling_.getVertex(label1), labeling_.getVertex(label2));
                }

                return ret;
            }
            
            std::size_t neighborCount(VertexLabelType vertex) const
            {
                std::size_t ret = 0;

                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    ret = htd::MutableHypergraphImpl::neighborCount(labeling_.getVertex(label));
                }

                return ret;
            }
            
            void getNeighbors(VertexLabelType vertex, htd::vertex_container & output) const
            {
                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    htd::MutableHypergraphImpl::getNeighbors(labeling_.getVertex(label), output);
                }
            }

            htd::vertex_t neighbor(VertexLabelType vertex, htd::index_t index) const
            {
                htd::vertex_t ret = 0;

                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    ret = htd::MutableHypergraphImpl::neighbor(labeling_.getVertex(label), index);
                }
                else
                {
                    throw std::out_of_range("htd::vertex_t htd::MutableLabeledHypergraphImpl::neighbor(VertexLabelType, htd::index_t)");
                }

                return ret;
            }

            bool isIsolatedVertex(VertexLabelType vertex) const
            {
                bool ret = false;

                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    ret = htd::MutableHypergraphImpl::isIsolatedVertex(labeling_.getVertex(label));
                }

                return ret;
            }

            void getHyperedges(htd::hyperedge_container & output, VertexLabelType vertex) const
            {
                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    htd::MutableHypergraphImpl::getHyperedges(output, labeling_.getVertex(label));
                }
            }

            const htd::hyperedge_t & hyperedge(htd::index_t index, VertexLabelType vertex) const
            {
                Label<VertexLabelType> label(vertex);

                if (!labeling_.isVertexLabel(label))
                {
                    throw std::out_of_range("htd::vertex_t htd::MutableLabeledHypergraphImpl::hyperedge(htd::index_t, VertexLabelType)");
                }

                return htd::MutableHypergraphImpl::hyperedge(index, labeling_.getVertex(label));
            }

            htd::vertex_t addVertex(VertexLabelType vertex)
            {
                if (labeling_.isVertexLabel(vertex))
                {
                    throw std::out_of_range("htd::vertex_t htd::MutableLabeledHypergraphImpl::addVertex(VertexLabelType)");
                }

                htd::vertex_t ret = htd::MutableHypergraphImpl::addVertex();

                labeling_.setLabel(ret, vertex);

                return ret;
            }

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE
            {
                if (labeling_.hasLabel(vertex))
                {
                    labeling_.removeLabel(vertex);
                }

                htd::MutableHypergraphImpl::removeVertex(vertex);
            }

            void removeVertex(VertexLabelType vertex)
            {
                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    htd::vertex_t selectedVertex = labeling_.getVertex(label);

                    labeling_.removeLabel(vertex);

                    htd::MutableHypergraphImpl::removeVertex(selectedVertex);
                }
            }

            void removeVertex(htd::vertex_t vertex, bool addNeighborHyperedge) HTD_OVERRIDE
            {
                if (labeling_.hasLabel(vertex))
                {
                    labeling_.removeLabel(vertex);
                }

                htd::MutableHypergraphImpl::removeVertex(vertex, addNeighborHyperedge);
            }

            void removeVertex(VertexLabelType vertex, bool addNeighborHyperedge)
            {
                Label<VertexLabelType> label(vertex);

                if (labeling_.isVertexLabel(label))
                {
                    htd::vertex_t selectedVertex = labeling_.getVertex(label);

                    labeling_.removeLabel(vertex);

                    htd::MutableHypergraphImpl::removeVertex(selectedVertex, addNeighborHyperedge);
                }
            }

            void addEdge(VertexLabelType vertex1, VertexLabelType vertex2)
            {
                Label<VertexLabelType> label1(vertex1);
                Label<VertexLabelType> label2(vertex2);

                if (labeling_.isVertexLabel(label1) && labeling_.isVertexLabel(label2))
                {
                    htd::MutableHypergraphImpl::addEdge(labeling_.getVertex(label1), labeling_.getVertex(label2));
                }
            }

            void addEdge(htd::vertex_t vertex1, htd::vertex_t vertex2, const HyperedgeLabelType & label)
            {
                htd::MutableHypergraphImpl::addEdge(vertex1, vertex2);

                htd::hyperedge_t hyperedge;

                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                labeling_.setLabel(hyperedge, label->clone());
            }

            void addEdge(VertexLabelType vertex1, VertexLabelType vertex2, const HyperedgeLabelType & label)
            {
                Label<VertexLabelType> label1(vertex1);
                Label<VertexLabelType> label2(vertex2);

                if (labeling_.isVertexLabel(label1) && labeling_.isVertexLabel(label2))
                {
                    addEdge(labeling_.getVertex(label1), labeling_.getVertex(label2));
                }
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it) || !labeling_.isVertexLabel(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(labeling_.getVertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::MutableHypergraphImpl::addEdge(hyperedge);
                }
            }

            void addEdge(htd::vertex_container::const_iterator begin, htd::vertex_container::const_iterator end, const HyperedgeLabelType & label)
            {
                htd::MutableHypergraphImpl::addEdge(begin, end);

                htd::hyperedge_t hyperedge(begin, end);

                labeling_.setLabel(hyperedge, label->clone());
            }

            void addEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end, const HyperedgeLabelType & label)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertex(*it) || !labeling_.isVertexLabel(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(labeling_.getVertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::MutableHypergraphImpl::addEdge(hyperedge);

                    labeling_.setLabel(hyperedge, label->clone());
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
                HTD_UNUSED(label);

                //TODO Implement
            }
            
            void removeEdge(VertexLabelType vertex1, VertexLabelType vertex2)
            {
                Label<VertexLabelType> label1(vertex1);
                Label<VertexLabelType> label2(vertex2);

                if (labeling_.isVertexLabel(label1) && labeling_.isVertexLabel(label2))
                {
                    htd::MutableHypergraphImpl::removeEdge(labeling_.getVertex(label1), labeling_.getVertex(label2));
                }
            }
            
            void removeEdge(typename std::vector<VertexLabelType>::const_iterator begin, typename std::vector<VertexLabelType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    ok = isVertex(*it) && labeling_.isVertexLabel(*it);

                    if (ok)
                    {
                        hyperedge.push_back(labeling_.getVertex(*it));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::MutableHypergraphImpl::removeEdge(hyperedge);

                    labeling_.removeLabel(hyperedge);
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
                    ok = isVertex(vertex) && labeling_.isVertexLabel(vertex);

                    if (ok)
                    {
                        hyperedge.push_back(labeling_.getVertex(vertex));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    htd::MutableHypergraphImpl::removeEdge(hyperedge);

                    labeling_.removeLabel(hyperedge);
                }
            }

            std::size_t vertexLabelCount(void) const
            {
                return labeling_.vertexLabelCount();
            }

            std::size_t hyperedgeLabelCount(void) const
            {
                return labeling_.hyperedgeLabelCount();
            }

            bool hasLabel(htd::vertex_t vertex) const
            {
                return labeling_.hasLabel(vertex);
            }

            bool hasLabel(const htd::hyperedge_t & edge) const
            {
                return labeling_.hasLabel(edge);
            }

            const VertexLabelType & label(htd::vertex_t vertex) const
            {
                return labeling_.label(vertex);
            }

            const HyperedgeLabelType & label(const htd::hyperedge_t & edge) const
            {
                return labeling_.label(edge);
            }

            void setLabel(htd::vertex_t vertex, const VertexLabelType & label)
            {
                labeling_.setLabel(vertex, new Label<VertexLabelType>(label));
            }

            void setLabel(const htd::hyperedge_t & edge, const HyperedgeLabelType & label)
            {
                labeling_.setLabel(edge, new Label<HyperedgeLabelType>(label));
            }

            void removeLabel(htd::vertex_t vertex)
            {
                labeling_.removeLabel(vertex);
            }

            void removeLabel(const htd::hyperedge_t & edge)
            {
                labeling_.removeLabel(edge);
            }

            bool isVertexLabel(const VertexLabelType & label) const
            {
                return labeling_.isVertexLabel(label);
            }

            bool isHyperedgeLabel(const HyperedgeLabelType & label) const
            {
                return labeling_.isHyperedgeLabel(label);
            }

            htd::vertex_t getVertex(const VertexLabelType & label) const
            {
                return labeling_.getVertex(label);
            }

            const htd::hyperedge_t & getHyperedge(const HyperedgeLabelType & label) const
            {
                return labeling_.getHyperedge(label);
            }

        private:
            BidirectionalGraphLabeling labeling_;
    };
}

#endif /* HTD_HTD_MUTABLELABELEDHYPERGRAPHIMPL_HPP */
