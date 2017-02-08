/*
 * File:   NamedGraph.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2017, Michael Abseher
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

#ifndef HTD_HTD_NAMEDGRAPH_HPP
#define HTD_HTD_NAMEDGRAPH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/LabeledGraphFactory.hpp>
#include <htd/BidirectionalGraphNaming.hpp>
#include <htd/Label.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/NamedVertexHyperedge.hpp>

#include <functional>
#include <vector>
#include <stdexcept>

namespace htd
{
    /**
     *  Implementation of a graph in which vertices and edges can be accessed by their names.
     */
    template<typename VertexNameType, typename EdgeNameType>
    class NamedGraph
    {
        public:
            /**
             *  Constructor for a graph.
             */
            NamedGraph(const htd::LibraryInstance * const manager) : base_(manager->labeledGraphFactory().createInstance()), names_(), vertexCreationFunction_(std::bind(&htd::IMutableLabeledGraph::addVertex, base_))
            {

            }

            /**
             *  Copy constructor for a graph.
             *
             *  @param[in] original  The original graph.
             */
            NamedGraph(const NamedGraph<VertexNameType, EdgeNameType> & original) : base_(original.base_->clone()), names_(original.names_), vertexCreationFunction_(std::bind(&htd::IMutableLabeledGraph::addVertex, base_))
            {

            }

            /**
             *  Destructor for a NamedGraph object.
             */
            virtual ~NamedGraph()
            {
                if (base_ != nullptr)
                {
                    delete base_;

                    base_ = nullptr;
                }
            }

            /**
             *  Getter for the number of vertices in the graph.
             *
             *  @return The number of vertices in the graph.
             */
            std::size_t vertexCount(void) const
            {
                return base_->vertexCount();
            }

            /**
             *  Getter for the number of edges in the graph.
             *
             *  @return The number of edges in the graph.
             */
            std::size_t edgeCount(void) const
            {
                return base_->edgeCount();
            }

            /**
             *  Check whether a given vertex name is indeed the name of a vertex of the graph.
             *
             *  @param[in] vertexName   The vertex name to test.
             *
             *  @return True if the given vertex name is indeed the name of a vertex of the graph, false otherwise.
             */
            bool isVertexName(const VertexNameType & vertexName) const
            {
                return names_.isVertexName(vertexName);
            }

            /**
             *  Set the name associated with the given vertex.
             *
             *  If the vertex is already named, the existing name will be replaced.
             *
             *  @param[in] vertex   The vertex to be named.
             *  @param[in] name     The new name.
             */
            void setVertexName(htd::vertex_t vertex, const VertexNameType & name)
            {
                HTD_ASSERT(base_->isVertex(vertex))

                names_.setVertexName(vertex, name);
            }

            /**
             *  Check whether a given edge name is indeed the name of an edge of the graph.
             *
             *  @param[in] edgeName The edge name to test.
             *
             *  @return True if the given edge name is indeed the name of an edge of the graph, false otherwise.
             */
            bool isEdgeName(const EdgeNameType & edgeName) const
            {
                return names_.isEdgeName(edgeName);
            }

            /**
             *  Set the name associated with the given edge.
             *
             *  If the edge is already named, the existing name will be replaced.
             *
             *  @param[in] edgeId   The ID of the edge to be named.
             *  @param[in] name     The new name.
             */
            void setEdgeName(htd::id_t edgeId, const EdgeNameType & name)
            {
                HTD_ASSERT(base_->isEdge(edgeId))

                names_.setEdgeName(edgeId, name);
            }

            /**
             *  Access the name associated with the given vertex.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return The name associated with the given vertex.
             */
            const VertexNameType & vertexName(htd::vertex_t vertex) const
            {
                HTD_ASSERT(names_.isNamedVertex(vertex))

                return names_.vertexName(vertex);
            }

            /**
             *  Access the name associated with the given edge.
             *
             *  @param[in] edgeId   The ID of the edge.
             *
             *  @return The name associated with the given edge.
             */
            const EdgeNameType & edgeName(htd::id_t edgeId) const
            {
                HTD_ASSERT(names_.isNamedEdge(edgeId))

                return names_.edgeName(edgeId);
            }

            /**
             *  Access the vertex with the given name.
             *
             *  @param[in] vertexName   The name of the vertex which shall be returned.
             *
             *  @return The vertex with the given name.
             */
            htd::vertex_t lookupVertex(const VertexNameType & vertexName) const
            {
                HTD_ASSERT(names_.isVertexName(vertexName))

                return names_.lookupVertex(vertexName);
            }

            /**
             *  Access the hyperedge with the given name.
             *
             *  @param[in] edgeName The name of the hyperedge which shall be returned.
             *
             *  @return The hyperedge with the given name.
             */
            htd::NamedVertexHyperedge<VertexNameType> lookupHyperedge(const EdgeNameType & edgeName) const
            {
                HTD_ASSERT(names_.isEdgeName(edgeName))

                htd::id_t edgeId = names_.lookupEdge(edgeName);

                NamedVertexHyperedge<VertexNameType> ret(edgeId);

                std::vector<VertexNameType> & elements = ret.elements();

                for (htd::vertex_t vertex : base_->hyperedge(edgeId))
                {
                    elements.push_back(vertexName(vertex));
                }

                return ret;
            }

            /**
             *  Getter for the number of edges in the graph containing a specific vertex.
             *
             *  @param[in] vertexName   The name of the vertex which shall be contained in the edges.
             *
             *  @return The number of edges in the graph containing the specific vertex.
             */
            std::size_t edgeCount(const VertexNameType & vertexName) const
            {
                return base_->edgeCount(lookupVertex(vertexName));
            }

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
            bool isEdge(const std::vector<VertexNameType> & elements)
            {
                return isEdge(htd::ConstCollection<VertexNameType>::getInstance(elements));
            }

            /**
             *  Check whether a given edge is part of the graph.
             *
             *  @param[in] elements The endpoints of the hyperedge.
             *
             *  @return True if the edge is part of the graph, false otherwise.
             */
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

            /**
             *  Get the associated edge ID.
             *
             *  @param[in] edgeName The name of the edge.
             *
             *  @return The ID of the edge with the given name.
             */
            htd::id_t associatedEdgeId(const EdgeNameType & edgeName) const
            {
                HTD_ASSERT(names_.isEdgeName(edgeName))

                return names_.lookupEdge(edgeName);
            }

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] vertexName1  The first endpoint of the edge.
             *  @param[in] vertexName2  The second endpoint of the edge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            htd::ConstCollection<htd::id_t> associatedEdgeIds(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                if (isVertexName(vertexName1) && isVertexName(vertexName2))
                {
                    return base_->associatedEdgeIds(lookupVertex(vertexName1), lookupVertex(vertexName2));
                }

                return htd::ConstCollection<htd::id_t>::getInstance(htd::VectorAdapter<htd::id_t>());
            }

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<VertexNameType> & elements) const
            {
                return associatedEdgeIds(htd::ConstCollection<VertexNameType>::getInstance(elements));
            }

            /**
             *  Access the collection of all vertices in the graph.
             *
             *  @return The collection of all vertices in the graph sorted in ascending order.
             */
            htd::ConstCollection<VertexNameType> vertices(void) const
            {
                htd::VectorAdapter<VertexNameType> ret;

                std::vector<VertexNameType> & container = ret.container();

                for (htd::vertex_t vertex : base_->vertices())
                {
                    container.push_back(vertexName(vertex));
                }

                return htd::ConstCollection<VertexNameType>::getInstance(ret);
            }

            /**
             *  Access the vertex at the specific position.
             *
             *  @param[in] index     The position of the vertex.
             *
             *  @return The vertex at the specific position.
             */
            const VertexNameType & vertexAtPosition(htd::index_t index) const
            {
                return vertexName(base_->vertexAtPosition(index));
            }

            /**
             *  Get all associated edge IDs.
             *
             *  @param[in] elements  The endpoints of the hyperedge.
             *
             *  @return The collection of all edges containing exactly the provided endpoints in the given order.
             */
            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<VertexNameType> & elements) const
            {
                std::vector<htd::vertex_t> hyperedge;

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
                    return htd::ConstCollection<htd::id_t>();;
                }

                return base_->associatedEdgeIds(htd::ConstCollection<htd::vertex_t>::getInstance(hyperedge));
            }

            /**
             *  Check whether the graph is connected.
             *
             *  @return True if the graph is connected, false otherwise.
             */
            bool isConnected(void) const
            {
                return base_->isConnected();
            }

            /**
             *  Check whether two vertices are contained in the same connected component.
             *
             *  @param[in] vertexName1  The first vertex.
             *  @param[in] vertexName2  The second vertex.
             *
             *  @return True if the two vertices are contained in the same connected component, false otherwise.
             */
            bool isConnected(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                return base_->isConnected(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            /**
             *  Check whether two vertices are neighbors.
             *
             *  @param[in] vertexName1  The first vertex.
             *  @param[in] vertexName2  The second vertex.
             *
             *  @return True if the two vertices are neighbors, false otherwise.
             */
            bool isNeighbor(const VertexNameType & vertexName1, const VertexNameType & vertexName2) const
            {
                return base_->isNeighbor(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            /**
             *  Getter for the number of neighbors of a given vertex in the graph.
             *
             *  @param[in] vertexName   The name of the vertex for which the number of neighbors shall be computed.
             *
             *  @return The number of neighbors of the given vertex in the graph.
             */
            std::size_t neighborCount(const VertexNameType & vertexName) const
            {
                return base_->neighborCount(lookupVertex(vertexName));
            }

            /**
             *  Access the collection of all neighbors of a given vertex in the graph.
             *
             *  @param[in] vertexName   The name of the vertex for which the collection of neighbors shall be returned.
             *
             *  @return The collection of all neighbors of the given vertex in the graph in ascending order.
             */
            htd::ConstCollection<VertexNameType> neighbors(const VertexNameType & vertexName) const
            {
                htd::VectorAdapter<VertexNameType> ret;

                std::vector<VertexNameType> & container = ret.container();

                for (htd::vertex_t neighbor : base_->neighbors(lookupVertex(vertexName)))
                {
                    container.push_back(this->vertexName(neighbor));
                }

                return htd::ConstCollection<VertexNameType>::getInstance(ret);
            }

            /**
             *  Access the neighbor at the specific position.
             *
             *  @param[in] vertexName   The name of the vertex for which the neighbor shall be returned.
             *  @param[in] index        The position of the neighbor.
             *
             *  @return The neighbor of the given vertex at the specific position.
             */
            const VertexNameType & neighborAtPosition(const VertexNameType & vertexName, htd::index_t index) const
            {
                return vertexName(base_->neighborAtPosition(lookupVertex(vertexName), index));
            }

            /**
             *  Getter for the number of isolated vertices in the graph.
             *
             *  @return The number of isolated vertices in the graph.
             */
            std::size_t isolatedVertexCount(void) const
            {
                return base_->isolatedVertexCount();
            }

            /**
             *  Access the collection of all isolated vertices in the graph.
             *
             *  @return The collection of all isolated vertices in the graph sorted in ascending order.
             */
            htd::ConstCollection<VertexNameType> isolatedVertices(void) const
            {
                htd::VectorAdapter<VertexNameType> ret;

                std::vector<VertexNameType> & container = ret.container();

                for (htd::vertex_t isolatedVertex : base_->isolatedVertices())
                {
                    container.push_back(vertexName(isolatedVertex));
                }

                return htd::ConstCollection<VertexNameType>::getInstance(ret);
            }

            /**
             *  Access the isolated vertex at the specific position.
             *
             *  @param[in] index    The position of the isolated vertex.
             *
             *  @return The isolated vertex at the specific position.
             */
            const VertexNameType & isolatedVertexAtPosition(htd::index_t index) const
            {
                return vertexName(base_->isolatedVertexAtPosition(index));
            }

            /**
             *  Check whether a given vertex is isolated.
             *
             *  @param[in] vertexName   The name of the vertex to test for isolation.
             *
             *  @return True if the vertex has no neighbors in the graph, false otherwise.
             */
            bool isIsolatedVertex(const VertexNameType & vertexName) const
            {
                return base_->isIsolatedVertex(lookupVertex(vertexName));
            }

            /**
             *  Access the collection of all hyperedges in the graph.
             *
             *  @return The collection of all hyperedges in the graph sorted by ID in ascending order.
             */
            htd::ConstCollection<NamedVertexHyperedge<VertexNameType>> hyperedges(void) const
            {
                htd::VectorAdapter<NamedVertexHyperedge<VertexNameType>> ret;

                std::vector<NamedVertexHyperedge<VertexNameType>> & container = ret.container();

                for (const htd::Hyperedge & hyperedge : base_->hyperedges())
                {
                    container.push_back(NamedVertexHyperedge<VertexNameType>(hyperedge.id()));

                    NamedVertexHyperedge<VertexNameType> & newHyperedge = container[container.size() - 1];

                    std::vector<VertexNameType> & elements = newHyperedge.elements();

                    for (htd::vertex_t vertex : hyperedge)
                    {
                        elements.push_back(vertexName(vertex));
                    }
                }

                return htd::ConstCollection<NamedVertexHyperedge<VertexNameType>>::getInstance(ret);
            }

            /**
             *  Access the collection of all hyperedges containing a specific vertex.
             *
             *  @param[in] vertexName   The name of the vertex which shall be contained in the edges.
             *
             *  @return The collection of all hyperedges containing the specific vertex sorted by ID in ascending order.
             */
            htd::ConstCollection<NamedVertexHyperedge<VertexNameType>> hyperedges(const VertexNameType & vertexName) const
            {
                htd::VectorAdapter<NamedVertexHyperedge<VertexNameType>> ret;

                std::vector<NamedVertexHyperedge<VertexNameType>> & container = ret.container();

                for (const htd::Hyperedge & hyperedge : base_->hyperedges(lookupVertex(vertexName)))
                {
                    container.push_back(NamedVertexHyperedge<VertexNameType>(hyperedge.id()));

                    NamedVertexHyperedge<VertexNameType> & newHyperedge = container[container.size() - 1];

                    std::vector<VertexNameType> & elements = newHyperedge.elements();

                    for (htd::vertex_t vertex : hyperedge)
                    {
                        elements.push_back(vertexName(vertex));
                    }
                }

                return htd::ConstCollection<NamedVertexHyperedge<VertexNameType>>::getInstance(ret);
            }

            /**
             *  Access the hyperedge with a specific ID.
             *
             *  @param[in] edgeId   The ID of the hyperedge.
             *
             *  @return The hyperedge with the specific ID.
             */
            NamedVertexHyperedge<VertexNameType> hyperedge(htd::id_t edgeId) const
            {
                NamedVertexHyperedge<VertexNameType> ret(edgeId);

                std::vector<VertexNameType> & elements = ret.elements();

                for (htd::vertex_t vertex : base_->hyperedge(edgeId))
                {
                    elements.push_back(vertexName(vertex));
                }

                return ret;
            }

            /**
             *  Access the hyperedge at the specific position. Edges not containing the given vertex are ignored.
             *
             *  @param[in] index        The position of the hyperedge.
             *  @param[in] vertexName   The name of the vertex which shall be contained in the edge.
             *
             *  @return The hyperedge at the specific position. Edges not containing the given vertex are ignored.
             */
            NamedVertexHyperedge<VertexNameType> hyperedgeAtPosition(htd::index_t index, const VertexNameType & vertexName) const
            {
                const htd::Hyperedge & hyperedge = base_->hyperedgeAtPosition(index, lookupVertex(vertexName));

                NamedVertexHyperedge<VertexNameType> ret(hyperedge.id());

                std::vector<VertexNameType> & elements = ret.elements();

                for (htd::vertex_t vertex : hyperedge)
                {
                    elements.push_back(vertexName(vertex));
                }

                return ret;
            }

            /**
             *  Add a new vertex to the graph if it does not already exist.
             *
             *  @param[in] vertexName   The name of the vertex which shall be added.
             *
             *  @return The ID of the new vertex if the vertex name did not exist before. Otherwise, the ID of the existing vertex is returned.
             */
            htd::vertex_t addVertex(const VertexNameType & vertexName)
            {
                return names_.insertVertex(vertexName, vertexCreationFunction_).first;
            }

            /**
             *  Add new vertices to the graph if they do not already exist.
             *
             *  @param[in] vertexNames  The names of the vertices which shall be added.
             *
             *  @return A vector containing for each provided vertex name the ID of the vertex in the graph. Existing vertices keep their ID.
             */
            std::vector<htd::vertex_t> addVertices(const std::vector<VertexNameType> & vertexNames)
            {
                return names_.insertVertices(vertexNames, vertexCreationFunction_);
            }

            /**
             *  Add new vertices to the graph if they do not already exist.
             *
             *  @param[in] vertexNames  The names of the vertices which shall be added.
             *
             *  @return A vector containing for each provided vertex name the ID of the vertex in the graph. Existing vertices keep their ID.
             */
            std::vector<htd::vertex_t> addVertices(const htd::ConstCollection<VertexNameType> & vertexNames)
            {
                return names_.insertVertices(vertexNames, vertexCreationFunction_);
            }

            /**
             *  Remove a vertex from the graph.
             *
             *  @param[in] vertexName   The name of the vertex which shall be removed.
             */
            void removeVertex(const VertexNameType & vertexName)
            {
                if (isVertexName(vertexName))
                {
                    htd::vertex_t locatedVertex = lookupVertex(vertexName);

                    base_->removeVertex(locatedVertex);

                    names_.removeVertexName(locatedVertex);
                }
            }

            /**
             *  Add a new edge to the graph if it does not already exist.
             *
             *  @param[in] vertexName1  The first endpoint of the edge.
             *  @param[in] vertexName2  The second endpoint of the edge.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            htd::id_t addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                return base_->addEdge(addVertex(vertexName1), addVertex(vertexName2));
            }

            /**
             *  Add a new edge to the graph if it does not already exist.
             *
             *  @param[in] vertexName1  The first endpoint of the edge.
             *  @param[in] vertexName2  The second endpoint of the edge.
             *  @param[in] name         The name assigned to the edge in the case it is added.
             *
             *  @return The ID of the new edge if the edge did not exist before. Otherwise, the ID of the existing edge is returned.
             */
            htd::id_t addEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2, const EdgeNameType & name)
            {
                htd::id_t edgeId = base_->addEdge(addVertex(vertexName1), addVertex(vertexName2));

                setEdgeName(edgeId, name);

                return edgeId;
            }

            /**
             *  Remove an edge from the graph.
             *
             *  @param[in] edgeId   The ID of the edge which shall be removed.
             */
            void removeEdge(htd::id_t edgeId)
            {
                base_->removeEdge(edgeId);

                names_.removeEdgeName(edgeId);
            }

            /**
             *  Remove an edge from the graph.
             *
             *  @param[in] edgeName The name of the edge which shall be removed.
             */
            void removeEdge(const EdgeNameType & edgeName)
            {
                if (isEdgeName(edgeName))
                {
                    htd::id_t edgeId = names_.lookupEdge(edgeName);

                    base_->removeEdge(edgeId);

                    names_.removeEdgeName(edgeId);
                }
            }

            /**
             *  Remove an edge from the graph.
             *
             *  @param[in] vertexName1  The first endpoint of the edge.
             *  @param[in] vertexName2  The second endpoint of the edge.
             */
            void removeEdge(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                HTD_ASSERT(isVertexName(vertexName1) && isVertexName(vertexName2))

                base_->removeEdge(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            /**
             *  Getter for the number of different label names in the graph.
             *
             *  @return The number of different label names in the graph.
             */
            std::size_t labelCount(void) const
            {
                return base_->labelCount();
            }

            /**
             *  Access the collection of all label names used in the graph.
             *
             *  @return The collection of all label names used in the graph sorted in ascending order.
             */
            htd::ConstCollection<std::string> labelNames(void) const
            {
                return base_->labelNames();
            }

            /**
             *  Access the label name at the specific position.
             *
             *  @param[in] index    The position of the label name.
             *
             *  @return The label name at the specific position.
             */
            const std::string & labelNameAtPosition(htd::index_t index) const
            {
                return base_->labelNameAtPosition(index);
            }

            /**
             *  Access the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] vertexName   The name of the vertex.
             *
             *  @return The label associated with the given vertex.
             */
            const htd::ILabel & vertexLabel(const std::string & labelName, const VertexNameType & vertexName) const
            {
                return base_->vertexLabel(labelName, lookupVertex(vertexName));
            }

            /**
             *  Access the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeId       The ID of the edge.
             *
             *  @return The label associated with the given edge.
             */
            const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const
            {
                return base_->edgeLabel(labelName, edgeId);
            }

            /**
             *  Access the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeName     The name of the edge.
             *
             *  @return The label associated with the given edge.
             */
            const htd::ILabel & edgeLabel(const std::string & labelName, const EdgeNameType & edgeName) const
            {
                return base_->edgeLabel(labelName, names_.lookupEdge(edgeName));
            }

            /**
             *  Set the label associated with the given vertex.
             *
             *  If the vertex is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  graph. Deleting the label outside the graph or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] vertexName   The name of the vertex to be labeled.
             *  @param[in] label        The new label.
             */
            void setVertexLabel(const std::string & labelName, const VertexNameType & vertexName, htd::ILabel * label)
            {
                base_->setVertexLabel(labelName, lookupVertex(vertexName), label);
            }

            /**
             *  Set the label associated with the given edge.
             *
             *  If the edge is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  graph. Deleting the label outside the graph or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] edgeId       The ID of the edge to be labeled.
             *  @param[in] label        The new label.
             */
            void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
            {
                base_->setEdgeLabel(labelName, edgeId, label);
            }

            /**
             *  Set the label associated with the given edge.
             *
             *  If the edge is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  graph. Deleting the label outside the graph or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] edgeName     The name of the edge to be labeled.
             *  @param[in] label        The new label.
             */
            void setEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName, htd::ILabel * label)
            {
                base_->setEdgeLabel(labelName, names_.lookupEdge(edgeName), label);
            }

            /**
             *  Remove the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] vertexName   The name of the vertex.
             */
            void removeVertexLabel(const std::string & labelName, const VertexNameType & vertexName)
            {
                base_->removeVertexLabel(labelName, lookupVertex(vertexName));
            }

            /**
             *  Remove the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] edgeId       The ID of the edge.
             */
            void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
            {
                base_->removeEdgeLabel(labelName, edgeId);
            }

            /**
             *  Remove the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] edgeName     The name of the edge.
             */
            void removeEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName)
            {
                base_->removeEdgeLabel(labelName, names_.lookupEdge(edgeName));
            }

            /**
             *  Swap the labels of two vertices.
             *
             *  @param[in] vertexName1  The name of the first vertex.
             *  @param[in] vertexName2  The name of the second vertex.
             */
            void swapVertexLabels(const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapVertexLabels(lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] edgeId1  The ID of the first edge.
             *  @param[in] edgeId2  The ID of the second edge.
             */
            void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
            {
                base_->swapEdgeLabels(edgeId1, edgeId2);
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] edgeName1    The name of the first edge.
             *  @param[in] edgeName2    The name of the second edge.
             */
            void swapEdgeLabels(const EdgeNameType & edgeName1, const EdgeNameType & edgeName2)
            {
                base_->swapEdgeLabels(names_.lookupEdge(edgeName1), names_.lookupEdge(edgeName2));
            }

            /**
             *  Swap the labels of two vertices.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] vertexName1  The name of the first vertex.
             *  @param[in] vertexName2  The name of the second vertex.
             */
            void swapVertexLabel(const std::string & labelName, const VertexNameType & vertexName1, const VertexNameType & vertexName2)
            {
                base_->swapVertexLabel(labelName, lookupVertex(vertexName1), lookupVertex(vertexName2));
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] edgeId1      The ID of the first edge.
             *  @param[in] edgeId2      The ID of the second edge.
             */
            void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
            {
                base_->swapEdgeLabel(labelName, edgeId1, edgeId2);
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] edgeName1    The name of the first edge.
             *  @param[in] edgeName2    The name of the second edge.
             */
            void swapEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName1, const EdgeNameType & edgeName2)
            {
                base_->swapEdgeLabel(labelName, names_.lookupEdge(edgeName1), names_.lookupEdge(edgeName2));
            }

            /**
             *  Transfer the control over a vertex label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] vertexName   The name of the vertex which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the vertex is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the vertex label.
             */
            htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertexName)
            {
                return base_->transferVertexLabel(labelName, lookupVertex(vertexName));
            }

            /**
             *  Transfer the control over an edge label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] edgeId       The ID of the edge which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the edge is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the edge label.
             */
            htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
            {
                return base_->transferEdgeLabel(labelName, edgeId);
            }

            /**
             *  Transfer the control over an edge label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] edgeName     The name of the edge which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the edge is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the edge label.
             */
            htd::ILabel * transferEdgeLabel(const std::string & labelName, const EdgeNameType & edgeName)
            {
                return base_->transferEdgeLabel(labelName, names_.lookupEdge(edgeName));
            }

            /**
             *  Create a deep copy of the current graph.
             *
             *  @return A new NamedGraph object identical to the current graph.
             */
            NamedGraph<VertexNameType, EdgeNameType> * clone(void) const
            {
                return new NamedGraph<VertexNameType, EdgeNameType>(*this);
            }

            /**
             *  Access the underlying ILabeledGraph object.
             *
             *  @return The underlying ILabeledGraph object.
             */
            const htd::ILabeledGraph & internalGraph(void) const
            {
                return *base_;
            }

        private:
            htd::IMutableLabeledGraph * base_;

            htd::BidirectionalGraphNaming<VertexNameType, EdgeNameType> names_;

            std::function<htd::vertex_t(void)> vertexCreationFunction_;
    };
}

#endif /* HTD_HTD_NAMEDGRAPH_HPP */
