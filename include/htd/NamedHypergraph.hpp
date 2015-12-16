/* 
 * File:   NamedHypergraph.hpp
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

#ifndef HTD_HTD_NAMEDHYPERGRAPH_HPP
#define	HTD_HTD_NAMEDHYPERGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledHypergraph.hpp>
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
    template<typename VertexNameType, typename HyperedgeNameType>
    class NamedHypergraph
    {
        public:
            NamedHypergraph(void) : base_(new htd::LabeledHypergraph()), nameLabeling_(new htd::BidirectionalGraphLabeling())
            {

            }

            NamedHypergraph(const NamedHypergraph<VertexNameType, HyperedgeNameType> & original) : base_(original.base_->clone()), nameLabeling_(original.nameLabeling_->clone())
            {

            }

            ~NamedHypergraph<VertexNameType, HyperedgeNameType>()
            {
                if (base_ != nullptr)
                {
                    delete base_;

                    base_ = nullptr;
                }

                if (nameLabeling_ != nullptr)
                {
                    delete nameLabeling_;

                    nameLabeling_ = nullptr;
                }
            }

            std::size_t vertexCount(void) const
            {
                return base_->vertexCount();
            }

            std::size_t edgeCount(void) const
            {
                return base_->edgeCount();
            }

            bool isVertexName(const VertexNameType & vertexName) const
            {
                return nameLabeling_->isVertexLabel(Label<VertexNameType>(vertexName));
            }

            void setVertexName(htd::vertex_t vertex, const VertexNameType & vertexName)
            {
                if (!base_->isVertex(vertex))
                {
                    throw std::logic_error("void htd::NamedHypergraph<VertexNameType, HyperedgeNameType>::setVertexName(htd::vertex_t, const VertexNameType &)");
                }

                nameLabeling_->setLabel(vertex, new htd::Label<VertexNameType>(vertexName));
            }

            bool isEdgeName(const HyperedgeNameType & edgeName) const
            {
                return nameLabeling_->isHyperedgeLabel(Label<HyperedgeNameType>(edgeName));
            }

            void setEdgeName(htd::vertex_t vertex1, htd::vertex_t vertex2, const HyperedgeNameType & edgeName)
            {
                htd::hyperedge_t hyperedge;

                hyperedge.push_back(vertex1);
                hyperedge.push_back(vertex2);

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                if (!base_->isEdge(hyperedge))
                {
                    throw std::logic_error("void htd::NamedHypergraph<VertexNameType, HyperedgeNameType>::setEdgeName(htd::vertex_t, htd::vertex_t, const HyperedgeNameType &)");
                }

                nameLabeling_->setLabel(hyperedge, new htd::Label<VertexNameType>(edgeName));
            }

            void setEdgeName(const htd::hyperedge_t & edge, const HyperedgeNameType & edgeName)
            {
                if (!base_->isEdge(edge))
                {
                    throw std::logic_error("void htd::NamedHypergraph<VertexNameType, HyperedgeNameType>::setEdgeName(const htd::hyperedge_t &, const HyperedgeNameType &)");
                }

                nameLabeling_->setLabel(edge, new htd::Label<VertexNameType>(edgeName));
            }

            const VertexNameType & name(htd::vertex_t vertex) const
            {
                if (!nameLabeling_->hasLabel(vertex))
                {
                    throw std::logic_error("const VertexNameType & htd::NamedHypergraph::name(htd::vertex_t) const");
                }

                return dynamic_cast<const htd::Label<VertexNameType> *>(&(nameLabeling_->label(vertex)))->value();
            }

            const HyperedgeNameType & name(const htd::hyperedge_t & edge) const
            {
                if (!nameLabeling_->hasLabel(edge))
                {
                    throw std::logic_error("const HyperedgeNameType & htd::NamedHypergraph::name(const htd::hyperedge_t &) const");
                }

                return dynamic_cast<const htd::Label<VertexNameType> *>(&(nameLabeling_->label(edge)))->value();
            }

            htd::vertex_t lookupVertex(const VertexNameType & vertexName) const
            {
                htd::Label<VertexNameType> label(vertexName);

                if (!nameLabeling_->isVertexLabel(label))
                {
                    throw std::logic_error("htd::vertex_t htd::NamedHypergraph<VertexNameType, HyperedgeNameType>::lookupVertex(const VertexNameType &) const");
                }

                return nameLabeling_->lookupVertex(label);
            }

            const htd::hyperedge_t & lookupHyperedge(const HyperedgeNameType & edgeName) const
            {
                htd::Label<HyperedgeNameType> label(edgeName);

                if (!nameLabeling_->isHyperedgeLabel(label))
                {
                    throw std::logic_error("const htd::hyperedge_t & htd::NamedHypergraph<VertexNameType, HyperedgeNameType>::lookupHyperedge(const HyperedgeNameType &) const");
                }

                return nameLabeling_->lookupHyperedge(label);
            }

            std::size_t edgeCount(const VertexNameType & vertexName) const
            {
                return base_->edgeCount(lookupVertex(vertexName));
            }

            void isEdge(typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (isVertex(*it))
                    {
                        hyperedge.push_back(lookupVertex(*it));
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

            bool isConnected(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                return base_->isConnected(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            bool isNeighbor(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                return base_->isNeighbor(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }
            
            std::size_t neighborCount(const VertexNameType & vertexName) const
            {
                return base_->neighborCount(lookupVertex(vertexName));
            }

            const htd::Collection<htd::vertex_t> neighbors(const VertexNameType & vertexName) const
            {
                return base_->neighbors(lookupVertex(vertexName));
            }

            htd::vertex_t neighbor(const VertexNameType & vertexName, htd::index_t index) const
            {
                return base_->neighbor(lookupVertex(vertexName), index);
            }

            std::size_t isolatedVertexCount(void) const
            {
                return base_->isolatedVertexCount();
            }

            const htd::Collection<htd::vertex_t> isolatedVertices(void) const
            {
                return base_->isolatedVertices();
            }

            htd::vertex_t isolatedVertex(htd::index_t index) const
            {
                return base_->isolatedVertex(index);
            }

            bool isIsolatedVertex(const VertexNameType & vertexName) const
            {
                return base_->isIsolatedVertex(lookupVertex(vertexName));
            }

            const htd::Collection<htd::hyperedge_t> hyperedges(const VertexNameType & vertexName) const
            {
                return base_->hyperedges(lookupVertex(vertexName));
            }

            const htd::hyperedge_t & hyperedge(htd::index_t index, const VertexNameType & vertexName) const
            {
                return base_->hyperedge(index, lookupVertex(vertexName));
            }

            htd::vertex_t addVertex(const VertexNameType & vertexName)
            {
                htd::vertex_t ret = htd::Vertex::UNKNOWN;

                if (isVertexName(vertexName))
                {
                    ret = lookupVertex(vertexName);
                }
                else
                {
                    ret = base_->addVertex();

                    nameLabeling_->setLabel(ret, new htd::Label<VertexNameType>(vertexName));
                }

                return ret;
            }

            void removeVertex(const VertexNameType & vertexName)
            {
                if (isVertexName(vertexName))
                {
                    htd::vertex_t locatedVertex = lookupVertex(vertexName);

                    base_->removeVertex(locatedVertex);

                    nameLabeling_->removeLabel(locatedVertex);
                }
            }

            void removeVertex(const VertexNameType & vertexName, bool addNeighborHyperedge)
            {
                if (isVertexName(vertexName))
                {
                    htd::vertex_t locatedVertex = lookupVertex(vertexName);

                    base_->removeVertex(locatedVertex, addNeighborHyperedge);

                    nameLabeling_->removeLabel(locatedVertex);
                }
            }

            void addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                htd::vertex_t locatedVertex1 = lookupVertex(vertexName1);

                if (locatedVertex1 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex1 = addVertex(vertexName1);
                }

                htd::vertex_t locatedVertex2 = lookupVertex(vertexName2);

                if (locatedVertex2 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex2 = addVertex(vertexName2);
                }

                base_->addEdge(locatedVertex1, locatedVertex2);
            }

            void addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2, const HyperedgeNameType & name)
            {
                htd::vertex_t locatedVertex1 = lookupVertex(vertexName1);

                if (locatedVertex1 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex1 = addVertex(vertexName1);
                }

                htd::vertex_t locatedVertex2 = lookupVertex(vertexName2);

                if (locatedVertex2 == htd::Vertex::UNKNOWN)
                {
                    locatedVertex2 = addVertex(vertexName2);
                }

                base_->addEdge(locatedVertex1, locatedVertex2);

                setEdgeName(locatedVertex1, locatedVertex2, name);
            }

            void addEdge(typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertexName(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(lookupVertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    base_->addEdge(hyperedge);
                }
            }

            void addEdge(typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end, const HyperedgeNameType & name)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    if (!isVertexName(*it))
                    {
                        addVertex(*it);
                    }

                    hyperedge.push_back(lookupVertex(*it));
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    base_->addEdge(hyperedge);

                    setEdgeName(hyperedge, name);
                }
            }

            void addEdge(const std::pair<VertexNameType, VertexNameType> & edge)
            {
                addEdge(edge.first, edge.second);
            }

            void addEdge(const std::pair<VertexNameType, VertexNameType> & edge, const HyperedgeNameType & name)
            {
                addEdge(edge.first, edge.second, name);
            }
            
            void addEdge(const std::vector<VertexNameType> & edge)
            {
                addEdge(edge.begin(), edge.end());
            }

            void addEdge(const std::vector<VertexNameType> & edge, const HyperedgeNameType & name)
            {
                addEdge(edge.begin(), edge.end(), name);
            }

            void removeEdge(const HyperedgeNameType & edgeName)
            {
                if (isVertexName(edgeName))
                {
                    const htd::hyperedge_t & locatedHyperedge = lookupHyperedge(edgeName);

                    base_->removeEdge(locatedHyperedge);

                    nameLabeling_->removeLabel(locatedHyperedge);
                }
            }
            
            void removeEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                htd::vertex_t locatedVertex1 = lookupVertex(vertexName1);
                htd::vertex_t locatedVertex2 = lookupVertex(vertexName2);

                if (locatedVertex1 != htd::Vertex::UNKNOWN && locatedVertex2 != htd::Vertex::UNKNOWN)
                {
                    base_->removeEdge(locatedVertex1, locatedVertex2);
                }
            }
            
            void removeEdge(typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto it = begin; ok && it != end; it++)
                {
                    ok = isVertex(*it);

                    if (ok)
                    {
                        hyperedge.push_back(lookupVertex(*it));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    base_->removeEdge(hyperedge);

                    nameLabeling_->removeLabel(hyperedge);
                }
            }
            
            void removeEdge(const std::pair<VertexNameType, VertexNameType> & edge)
            {
                removeEdge(edge.first, edge.second);
            }
            
            void removeEdge(const std::vector<VertexNameType> & edge)
            {
                bool ok = true;

                htd::hyperedge_t hyperedge;

                for (auto & vertex : edge)
                {
                    ok = isVertex(vertex);

                    if (ok)
                    {
                        hyperedge.push_back(lookupVertex(vertex));
                    }
                }

                if (ok)
                {
                    std::sort(hyperedge.begin(), hyperedge.end());

                    hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                    base_->removeEdge(hyperedge);

                    nameLabeling_->removeLabel(hyperedge);
                }
            }

            std::size_t labelCount(void) const
            {
                return base_->labelCount();
            }

            htd::Collection<std::string> labelNames(void) const
            {
                return base_->labelNames();
            }

            const std::string & labelName(htd::index_t index) const
            {
                return base_->labelName(index);
            }

            const htd::ILabel & vertexLabel(const std::string & labelName, const VertexNameType & vertexName) const
            {
                return base_->label(labelName, lookupVertex(vertexName));
            }

            const htd::ILabel & hyperedgeLabel(const std::string & labelName, const HyperedgeNameType & edgeName) const
            {
                return base_->label(labelName, lookupHyperedge(edgeName));
            }

            const htd::ILabel & hyperedgeLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                htd::hyperedge_t hyperedge;

                hyperedge.push_back(lookupVertex(vertexName1));
                hyperedge.push_back(lookupVertex(vertexName2));

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                return base_->label(labelName, hyperedge);
            }

            const htd::ILabel & hyperedgeLabel(const std::string & labelName, typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end) const
            {
                htd::hyperedge_t hyperedge;

                for (auto it = begin; it != end; it++)
                {
                    hyperedge.push_back(lookupVertex(*it));
                }

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                return base_->label(labelName, hyperedge);
            }

            const htd::ILabel & hyperedgeLabel(const std::string & labelName, const std::pair<VertexNameType, VertexNameType> & edge) const
            {
                return hyperedgeLabel(labelName, edge.first, edge.second);
            }

            const htd::ILabel & hyperedgeLabel(const std::string & labelName, const std::vector<VertexNameType> & edge)
            {
                return hyperedgeLabel(labelName, edge.begin(), edge.end());
            }

            void setVertexLabel(const std::string & labelName, const VertexNameType & vertexName, htd::ILabel * label)
            {
                base_->setLabel(labelName, lookupVertex(vertexName), label);
            }

            void setHyperedgeLabel(const std::string & labelName, const HyperedgeNameType & edgeName, htd::ILabel * label)
            {
                base_->setLabel(labelName, lookupHyperedge(edgeName), label);
            }

            void setHyperedgeLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2, htd::ILabel * label)
            {
                htd::hyperedge_t hyperedge;

                hyperedge.push_back(lookupVertex(vertexName1));
                hyperedge.push_back(lookupVertex(vertexName2));

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                base_->setLabel(labelName, hyperedge, label);
            }

            void setHyperedgeLabel(const std::string & labelName, typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end, htd::ILabel * label)
            {
                htd::hyperedge_t hyperedge;

                for (auto it = begin; it != end; it++)
                {
                    hyperedge.push_back(lookupVertex(*it));
                }

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                base_->setLabel(labelName, hyperedge, label);
            }

            void setHyperedgeLabel(const std::string & labelName, const std::pair<VertexNameType, VertexNameType> & edge, htd::ILabel * label)
            {
                setHyperedgeLabel(labelName, edge.first, edge.second, label);
            }

            void setHyperedgeLabel(const std::string & labelName, const std::vector<VertexNameType> & edge, htd::ILabel * label)
            {
                setHyperedgeLabel(labelName, edge.begin(), edge.end(), label);
            }

            void removeVertexLabel(const std::string & labelName, const VertexNameType & vertexName)
            {
                base_->removeLabel(labelName, lookupVertex(vertexName));
            }

            void removeHyperedgeLabel(const std::string & labelName, const HyperedgeNameType & edgeName)
            {
                base_->removeLabel(labelName, lookupHyperedge(edgeName));
            }

            void removeHyperedgeLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                htd::hyperedge_t hyperedge;

                hyperedge.push_back(lookupVertex(vertexName1));
                hyperedge.push_back(lookupVertex(vertexName2));

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                base_->removeLabel(labelName, hyperedge);
            }

            void removeHyperedgeLabel(const std::string & labelName, typename std::vector<VertexNameType>::const_iterator begin, typename std::vector<VertexNameType>::const_iterator end)
            {
                htd::hyperedge_t hyperedge;

                for (auto it = begin; it != end; it++)
                {
                    hyperedge.push_back(lookupVertex(*it));
                }

                std::sort(hyperedge.begin(), hyperedge.end());

                hyperedge.erase(std::unique(hyperedge.begin(), hyperedge.end()), hyperedge.end());

                base_->removeLabel(labelName, hyperedge);
            }

            void removeHyperedgeLabel(const std::string & labelName, const std::pair<VertexNameType, VertexNameType> & edge)
            {
                removeHyperedgeLabel(labelName, edge.first, edge.second);
            }

            void removeHyperedgeLabel(const std::string & labelName, const std::vector<VertexNameType> & edge)
            {
                removeHyperedgeLabel(labelName, edge.begin(), edge.end());
            }

            void swapVertexLabels(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapLabels(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            void swapHyperedgeLabels(const HyperedgeNameType & edgeName1, const HyperedgeNameType & edgeName2)
            {
                base_->swapLabels(lookupHyperedge(edgeName1), lookupHyperedge(edgeName2));
            }

            void swapVertexLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapLabel(labelName, lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            void swapHyperedgeLabel(const std::string & labelName, const HyperedgeNameType & edgeName1, const HyperedgeNameType & edgeName2)
            {
                base_->swapLabel(labelName, lookupHyperedge(edgeName1), lookupHyperedge(edgeName2));
            }

            void swapHyperedgeLabel(const std::string & labelName, const VertexNameType & edge1VertexName1, const VertexNameType & edge1VertexName2, const VertexNameType & edge2VertexName1, const VertexNameType & edge2VertexName2)
            {
                htd::hyperedge_t hyperedge1;
                htd::hyperedge_t hyperedge2;

                hyperedge1.push_back(lookupVertex(edge1VertexName1));
                hyperedge1.push_back(lookupVertex(edge1VertexName2));

                hyperedge2.push_back(lookupVertex(edge2VertexName1));
                hyperedge2.push_back(lookupVertex(edge2VertexName2));

                std::sort(hyperedge1.begin(), hyperedge1.end());
                std::sort(hyperedge2.begin(), hyperedge2.end());

                hyperedge1.erase(std::unique(hyperedge1.begin(), hyperedge1.end()), hyperedge1.end());
                hyperedge2.erase(std::unique(hyperedge2.begin(), hyperedge2.end()), hyperedge2.end());

                base_->swapLabel(labelName, hyperedge1, hyperedge2);
            }

            void swapHyperedgeLabel(const std::string & labelName, typename std::vector<VertexNameType>::const_iterator begin1, typename std::vector<VertexNameType>::const_iterator end1, typename std::vector<VertexNameType>::const_iterator begin2, typename std::vector<VertexNameType>::const_iterator end2)
            {
                htd::hyperedge_t hyperedge1;
                htd::hyperedge_t hyperedge2;

                for (auto it = begin1; it != end1; it++)
                {
                    hyperedge1.push_back(lookupVertex(*it));
                }

                for (auto it = begin2; it != end2; it++)
                {
                    hyperedge2.push_back(lookupVertex(*it));
                }

                std::sort(hyperedge1.begin(), hyperedge1.end());
                std::sort(hyperedge2.begin(), hyperedge2.end());

                hyperedge1.erase(std::unique(hyperedge1.begin(), hyperedge1.end()), hyperedge1.end());
                hyperedge2.erase(std::unique(hyperedge2.begin(), hyperedge2.end()), hyperedge2.end());

                base_->swapLabel(labelName, hyperedge1, hyperedge2);
            }

            void swapHyperedgeLabel(const std::string & labelName, const std::pair<VertexNameType, VertexNameType> & edge1, const std::pair<VertexNameType, VertexNameType> & edge2)
            {
                swapHyperedgeLabel(labelName, edge1.first, edge1.second, edge2.first, edge2.second);
            }

            void swapHyperedgeLabel(const std::string & labelName, const std::vector<VertexNameType> & edge1, const std::vector<VertexNameType> & edge2)
            {
                swapHyperedgeLabel(labelName, edge1.begin(), edge1.end(), edge2.begin(), edge2.end());
            }

            NamedHypergraph<VertexNameType, HyperedgeNameType> * clone(void) const
            {
                return new NamedHypergraph<VertexNameType, HyperedgeNameType>(*this);
            }

            const htd::ILabeledHypergraph & internalGraph(void) const
            {
                return *base_;
            }

        private:
            htd::IMutableLabeledHypergraph * base_;

            htd::IBidirectionalGraphLabeling * nameLabeling_;
    };
}

#endif /* HTD_HTD_NAMEDHYPERGRAPH_HPP */
