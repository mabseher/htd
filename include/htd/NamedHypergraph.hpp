/* 
 * File:   NamedHypergraph.hpp
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
#include <htd/VectorAdapter.hpp>

#include <set>
#include <vector>
#include <stdexcept>

namespace htd
{
    template<typename VertexNameType, typename EdgeNameType>
    class NamedHypergraph
    {
        public:
            NamedHypergraph(void) : base_(new htd::LabeledHypergraph()), nameLabeling_(new htd::BidirectionalGraphLabeling())
            {

            }

            NamedHypergraph(const NamedHypergraph<VertexNameType, EdgeNameType> & original) : base_(original.base_->clone()), nameLabeling_(original.nameLabeling_->clone())
            {

            }

            ~NamedHypergraph<VertexNameType, EdgeNameType>()
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
                    throw std::logic_error("void htd::NamedHypergraph<VertexNameType, EdgeNameType>::setVertexName(htd::vertex_t, const VertexNameType &)");
                }

                nameLabeling_->setVertexLabel(vertex, new htd::Label<VertexNameType>(vertexName));
            }

            bool isEdgeName(const EdgeNameType & edgeName) const
            {
                return nameLabeling_->isEdgeLabel(Label<EdgeNameType>(edgeName));
            }

            void setEdgeName(htd::id_t edgeId, const EdgeNameType & edgeName)
            {
                if (!base_->isEdge(edgeId))
                {
                    throw std::logic_error("void htd::NamedHypergraph<VertexNameType, EdgeNameType>::setEdgeName(htd::id_t, const EdgeNameType &)");
                }

                nameLabeling_->setEdgeLabel(edgeId, new htd::Label<VertexNameType>(edgeName));
            }

            const VertexNameType & vertexName(htd::vertex_t vertex) const
            {
                if (!nameLabeling_->isLabeledVertex(vertex))
                {
                    std::cout << "NOT NAMED: " << vertex << std::endl;

                    throw std::logic_error("const VertexNameType & htd::NamedHypergraph<VertexNameType, EdgeNameType>::vertexName(htd::vertex_t) const");
                }

                return dynamic_cast<const htd::Label<VertexNameType> *>(&(nameLabeling_->vertexLabel(vertex)))->value();
            }

            const EdgeNameType & edgeName(htd::id_t edgeId) const
            {
                if (!nameLabeling_->isLabeledEdge(edgeId))
                {
                    throw std::logic_error("const EdgeNameType & htd::NamedHypergraph<VertexNameType, EdgeNameType>::edgeName(htd::id_t) const");
                }

                return dynamic_cast<const htd::Label<VertexNameType> *>(&(nameLabeling_->edgeLabel(edgeId)))->value();
            }

            htd::vertex_t lookupVertex(const VertexNameType & vertexName) const
            {
                htd::Label<VertexNameType> label(vertexName);

                if (!nameLabeling_->isVertexLabel(label))
                {
                    throw std::logic_error("htd::vertex_t htd::NamedHypergraph<VertexNameType, EdgeNameType>::lookupVertex(const VertexNameType &) const");
                }

                return nameLabeling_->lookupVertex(label);
            }

            std::size_t edgeCount(const VertexNameType & vertexName) const
            {
                return base_->edgeCount(lookupVertex(vertexName));
            }

            bool isEdge(const htd::ConstCollection<VertexNameType> & elements)
            {
                bool ok = true;

                for (auto it = elements.begin(); ok && it != elements.end(); it++)
                {
                    if (!isVertex(*it))
                    {
                        ok = false;
                    }
                }

                if (ok)
                {
                    ok = base_->isEdge(elements);
                }

                return ok;
            }

            htd::id_t associatedEdgeId(const EdgeNameType & edgeName) const
            {
                htd::Label<EdgeNameType> label(edgeName);

                if (!nameLabeling_->isEdgeLabel(label))
                {
                    throw std::logic_error("htd::id_t htd::NamedHypergraph<VertexNameType, EdgeNameType>::correspondingEdgeId(const EdgeNameType &) const");
                }

                return nameLabeling_->lookupEdge(label);
            }

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                if (isVertexName(vertexName1) && isVertexName(vertexName2))
                {
                    return base_->associatedEdgeIds(lookupVertex(vertexName1), lookupVertex(vertexName2));
                }

                return htd::VectorAdapter<htd::id_t>();
            }

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<VertexNameType> & elements) const
            {
                htd::vertex_container hyperedge;

                bool ok = true;

                for (auto it = elements.begin(); ok && it != elements.end(); ++it)
                {
                    ok = isVertexName(*it);

                    if (ok)
                    {
                        hyperedge.push_back(lookupVertex(*it));
                    }
                }

                if (!ok)
                {
                    return htd::VectorAdapter<htd::id_t>();
                }

                return base_->associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(hyperedge));
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

            htd::ConstCollection<htd::vertex_t> neighbors(const VertexNameType & vertexName) const
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

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const
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

            htd::ConstCollection<htd::Hyperedge> hyperedges(const VertexNameType & vertexName) const
            {
                return base_->hyperedges(lookupVertex(vertexName));
            }

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const
            {
                return base_->hyperedge(edgeId);
            }

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, const VertexNameType & vertexName) const
            {
                return base_->hyperedgeAtPosition(index, lookupVertex(vertexName));
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

                    nameLabeling_->setVertexLabel(ret, new htd::Label<VertexNameType>(vertexName));
                }

                return ret;
            }

            void removeVertex(const VertexNameType & vertexName)
            {
                if (isVertexName(vertexName))
                {
                    htd::vertex_t locatedVertex = lookupVertex(vertexName);

                    base_->removeVertex(locatedVertex);

                    nameLabeling_->removeVertexLabel(locatedVertex);
                }
            }

            htd::id_t addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
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

                return base_->addEdge(locatedVertex1, locatedVertex2);
            }

            htd::id_t addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2, const EdgeNameType & name)
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

                htd::id_t edgeId = base_->addEdge(locatedVertex1, locatedVertex2);

                setEdgeName(edgeId, name);

                return edgeId;
            }

            htd::id_t addEdge(const htd::ConstCollection<VertexNameType> & elements)
            {
                htd::vertex_container hyperedge;

                for (auto & vertex : elements)
                {
                    if (!isVertexName(vertex))
                    {
                        addVertex(vertex);
                    }

                    hyperedge.push_back(lookupVertex(vertex));
                }

                return base_->addEdge(htd::ConstCollection<htd::vertex_t>(hyperedge));
            }

            htd::id_t addEdge(const htd::ConstCollection<VertexNameType> & elements, const EdgeNameType & name)
            {
                htd::vertex_container hyperedge;

                for (auto & vertex : elements)
                {
                    if (!isVertexName(vertex))
                    {
                        addVertex(vertex);
                    }

                    hyperedge.push_back(lookupVertex(vertex));
                }

                htd::id_t edgeId = base_->addEdge(htd::ConstCollection<htd::vertex_t>(hyperedge));

                setEdgeName(edgeId, name);

                return edgeId;
            }

            htd::id_t addEdge(const std::pair<VertexNameType, VertexNameType> & edge)
            {
                return addEdge(edge.first, edge.second);
            }

            htd::id_t addEdge(const std::pair<VertexNameType, VertexNameType> & edge, const EdgeNameType & name)
            {
                return addEdge(edge.first, edge.second, name);
            }

            void removeEdge(htd::id_t edgeId)
            {
                base_->removeEdge(edgeId);

                nameLabeling_->removeEdgeLabel(edgeId);
            }

            void removeEdge(const EdgeNameType & edgeName)
            {
                if (isVertexName(edgeName))
                {
                    htd::id_t edgeId = lookupHyperedge(edgeName);

                    base_->removeEdge(edgeId);

                    nameLabeling_->removeEdgeLabel(edgeId);
                }
            }

            std::size_t labelCount(void) const
            {
                return base_->labelCount();
            }

            htd::ConstCollection<std::string> labelNames(void) const
            {
                return base_->labelNames();
            }

            const std::string & labelName(htd::index_t index) const
            {
                return base_->labelName(index);
            }

            const htd::ILabel & vertexLabel(const std::string & labelName, const VertexNameType & vertexName) const
            {
                return base_->vertexLabel(labelName, lookupVertex(vertexName));
            }

            const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const
            {
                return base_->edgeLabel(labelName, edgeId);
            }

            const htd::ILabel & edgeLabel(const std::string & labelName, const EdgeNameType & edgeName) const
            {
                return base_->edgeLabel(labelName, lookupEdge(edgeName));
            }

            void setVertexLabel(const std::string & labelName, const VertexNameType & vertexName, htd::ILabel * label)
            {
                base_->setVertexLabel(labelName, lookupVertex(vertexName), label);
            }

            void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
            {
                base_->setEdgeLabel(labelName, edgeId, label);
            }

            void setEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName, htd::ILabel * label)
            {
                base_->setEdgeLabel(labelName, lookupHyperedge(edgeName), label);
            }

            void removeVertexLabel(const std::string & labelName, const VertexNameType & vertexName)
            {
                base_->removeVertexLabel(labelName, lookupVertex(vertexName));
            }

            void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
            {
                base_->removeEdgeLabel(labelName, edgeId);
            }

            void removeEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName)
            {
                base_->removeEdgeLabel(labelName, lookupHyperedge(edgeName));
            }

            void swapVertexLabels(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapVertexLabels(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
            {
                base_->swapEdgeLabels(edgeId1, edgeId2);
            }

            void swapEdgeLabels(const EdgeNameType & edgeName1, const EdgeNameType & edgeName2)
            {
                base_->swapEdgeLabels(lookupHyperedge(edgeName1), lookupHyperedge(edgeName2));
            }

            void swapVertexLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapVertexLabel(labelName, lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
            {
                base_->swapEdgeLabel(labelName, edgeId1, edgeId2);
            }

            void swapEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName1, const EdgeNameType & edgeName2)
            {
                base_->swapEdgeLabel(labelName, lookupHyperedge(edgeName1), lookupHyperedge(edgeName2));
            }

            NamedHypergraph<VertexNameType, EdgeNameType> * clone(void) const
            {
                return new NamedHypergraph<VertexNameType, EdgeNameType>(*this);
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
