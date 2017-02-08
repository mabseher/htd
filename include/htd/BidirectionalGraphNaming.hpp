/*
 * File:   BidirectionalGraphNaming.hpp
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

#ifndef HTD_HTD_BIDIRECTIONALGRAPHNAMING_HPP
#define HTD_HTD_BIDIRECTIONALGRAPHNAMING_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <stdexcept>
#include <unordered_map>

namespace htd
{
    /**
     * Implementation of a graph naming providing bi-directional mappings between vertices (and/or edges) and their names.
     */
    template <typename VertexNameType, typename EdgeNameType,
              typename VertexNameHashFunction = std::hash<VertexNameType>, typename VertexNameEqualityFunction = std::equal_to<VertexNameType>,
              typename EdgeNameHashFunction = std::hash<EdgeNameType>, typename EdgeNameEqualityFunction = std::equal_to<EdgeNameType>>
    class BidirectionalGraphNaming
    {
        public:
            BidirectionalGraphNaming(void) : vertexNames_(), edgeNames_(), vertexNamesReverseMap_(), edgeNamesReverseMap_()
            {

            }

            virtual ~BidirectionalGraphNaming()
            {

            }

            /**
             *  Getter for the number of different vertex names stored in the graph naming.
             *
             *  @return The number of different vertex names stored in the graph naming.
             */
            std::size_t vertexNameCount(void) const
            {
                return vertexNames_.size();
            }

            /**
             *  Getter for the number of different edge names stored in the graph naming.
             *
             *  @return The number of different edge names stored in the graph naming.
             */
            std::size_t edgeNameCount(void) const
            {
                return edgeNames_.size();
            }

            /**
             *  Check whether a given vertex has a name.
             *
             *  @param[in] vertex   The vertex.
             *
             *  @return True if the given vertex has a name, false otherwise.
             */
            bool isNamedVertex(htd::vertex_t vertex) const
            {
                return vertexNames_.count(vertex) == 1;
            }

            /**
             *  Check whether a given edge has a name.
             *
             *  @param[in] edgeId   The ID of the edge.
             *
             *  @return True if the given edge has a name, false otherwise.
             */
            bool isNamedEdge(htd::id_t edgeId) const
            {
                return edgeNames_.count(edgeId) == 1;
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
                return vertexNames_.at(vertex);
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
                return edgeNames_.at(edgeId);
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
                HTD_ASSERT(vertexNamesReverseMap_.count(name) == 0)

                auto position = vertexNames_.find(vertex);

                if (position != vertexNames_.end())
                {
                    if (!(position->second == name))
                    {
                        auto position2 = vertexNamesReverseMap_.find(position->second);

                        if (position2 != vertexNamesReverseMap_.end())
                        {
                            vertexNamesReverseMap_.erase(position2);
                        }
                    }
                }

                vertexNames_[vertex] = name;
                vertexNamesReverseMap_[name] = vertex;
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
                HTD_ASSERT(edgeNamesReverseMap_.count(name) == 0)

                auto position = edgeNames_.find(edgeId);

                if (position != edgeNames_.end())
                {
                    if (!(position->second == name))
                    {
                        auto position2 = edgeNamesReverseMap_.find(position->second);

                        if (position2 != edgeNamesReverseMap_.end())
                        {
                            edgeNamesReverseMap_.erase(position2);
                        }
                    }
                }

                edgeNames_[edgeId] = name;
                edgeNamesReverseMap_[name] = edgeId;
            }

            /**
             *  Insert a vertex with the given name if a vertex with the same name not already exists.
             *
             *  @param[in] name                     The name of the vertex which shall be inserted.
             *  @param[in] vertexCreationFunction   A function which is used to generate a new vertex ID in case that no vertex with the given name already exists.
             *
             *  @note Examples for the vertex creation function are the addVertex() functions of the mutable graph classes, i.e. htd::IMutableMultiHypergraph::addVertex().
             *
             *  @return A pair which's first value is the ID associated with the given vertex name. The second value of the pair is a boolean set to true in
             *  case the vertex was inserted. If the second value of the pair is set to false, this means that a vertex with the same name was already part
             *  of the graph naming and that the vertex creation function was not called.
             */
            std::pair<htd::id_t, bool> insertVertex(const VertexNameType & name, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::pair<htd::id_t, bool> ret(0, false);

                auto result = vertexNamesReverseMap_.insert(std::make_pair(name, 0));

                htd::vertex_t & vertexId = result.first->second;

                if (result.second)
                {
                    htd::vertex_t newVertex = vertexCreationFunction();

                    ret.first = newVertex;

                    ret.second = true;

                    vertexId = newVertex;

                    vertexNames_.emplace(newVertex, name);
                }
                else
                {
                    ret.first = vertexId;
                }

                return ret;
            }

            /**
             *  Insert a set of vertices with the given names. A vertex is only inserted if a vertex with the same name not already exists.
             *
             *  @param[in] names                    The names of the vertices which shall be inserted.
             *  @param[in] vertexCreationFunction   A function which is used to generate a new vertex ID in case that no vertex with the given name already exists.
             *
             *  @note Examples for the vertex creation function are the addVertex() functions of the mutable graph classes, i.e. htd::IMutableMultiHypergraph::addVertex().
             *
             *  @return A vector of the vertex IDs corresponding to the given names.
             */
            std::vector<htd::id_t> insertVertices(const std::vector<VertexNameType> & names, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::vector<htd::id_t> ret;

                ret.reserve(names.size());

                for (const VertexNameType & name : names)
                {
                    auto result = vertexNamesReverseMap_.emplace(name, htd::Vertex::UNKNOWN);

                    htd::vertex_t & vertexId = result.first->second;

                    if (result.second)
                    {
                        htd::vertex_t newVertex = vertexCreationFunction();

                        ret.push_back(newVertex);

                        vertexId = newVertex;

                        vertexNames_.emplace(newVertex, name);
                    }
                    else
                    {
                        ret.push_back(vertexId);
                    }
                }

                return ret;
            }

            /**
             *  Insert a set of vertices with the given names. A vertex is only inserted if a vertex with the same name not already exists.
             *
             *  @param[in] names                    The names of the vertices which shall be inserted.
             *  @param[in] vertexCreationFunction   A function which is used to generate a new vertex ID in case that no vertex with the given name already exists.
             *
             *  @note Examples for the vertex creation function are the addVertex() functions of the mutable graph classes, i.e. htd::IMutableMultiHypergraph::addVertex().
             *
             *  @return A vector of the vertex IDs corresponding to the given names.
             */
            std::vector<htd::id_t> insertVertices(const htd::ConstCollection<VertexNameType> & names, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::vector<htd::id_t> ret;

                ret.reserve(names.size());

                for (const VertexNameType & name : names)
                {
                    auto result = vertexNamesReverseMap_.emplace(name, htd::Vertex::UNKNOWN);

                    htd::vertex_t & vertexId = result.first->second;

                    if (result.second)
                    {
                        htd::vertex_t newVertex = vertexCreationFunction();

                        ret.push_back(newVertex);

                        vertexId = newVertex;

                        vertexNames_.emplace(newVertex, name);
                    }
                    else
                    {
                        ret.push_back(vertexId);
                    }
                }

                return ret;
            }

            /**
             *  Remove the name associated with the given vertex.
             *
             *  @param[in] vertex   The vertex.
             */
            void removeVertexName(htd::vertex_t vertex)
            {
                auto position = vertexNames_.find(vertex);

                HTD_ASSERT(position != vertexNames_.end())

                auto position2 = vertexNamesReverseMap_.find(position->second);

                if (position2 != vertexNamesReverseMap_.end())
                {
                    vertexNamesReverseMap_.erase(position2);
                }

                vertexNames_.erase(position);
            }

            /**
             *  Remove the name associated with the given edge.
             *
             *  @param[in] edgeId   The ID of the edge.
             */
            void removeEdgeName(htd::id_t edgeId)
            {
                auto position = edgeNames_.find(edgeId);

                HTD_ASSERT(position != edgeNames_.end())

                auto position2 = edgeNamesReverseMap_.find(position->second);

                if (position2 != edgeNamesReverseMap_.end())
                {
                    edgeNamesReverseMap_.erase(position2);
                }

                edgeNames_.erase(position);
            }

            /**
             *  Check whether a given vertex name is indeed the name of a known vertex.
             *
             *  @param[in] name The vertex name to test.
             *
             *  @return True if the given vertex name is indeed the name of a known vertex, false otherwise.
             */
            bool isVertexName(const VertexNameType & name) const
            {
                return vertexNamesReverseMap_.count(name) > 0;
            }

            /**
             *  Check whether a given edge name is indeed the name of a known edge.
             *
             *  @param[in] name The edge name to test.
             *
             *  @return True if the given edge name is indeed the name of a known edge, false otherwise.
             */
            bool isEdgeName(const EdgeNameType & name) const
            {
                return edgeNamesReverseMap_.count(name) > 0;
            }

            /**
             *  Access the vertex with the given name.
             *
             *  @param[in] name The name of the vertex which shall be returned.
             *
             *  @return The vertex with the given name.
             */
            htd::vertex_t lookupVertex(const VertexNameType & name) const
            {
                return vertexNamesReverseMap_.at(name);
            }

            /**
             *  Access the ID of the edge with the given name.
             *
             *  @param[in] name The name of the edge which shall be returned.
             *
             *  @return The ID of the edge with the given name.
             */
            htd::id_t lookupEdge(const EdgeNameType & name) const
            {
                return edgeNamesReverseMap_.at(name);
            }

            /**
             *  Create a deep of copy the current graph naming.
             *
             *  @return A new BidirectionalGraphNaming object identical to the current graph naming.
             */
            htd::BidirectionalGraphNaming<VertexNameType, EdgeNameType, VertexNameHashFunction, EdgeNameHashFunction, VertexNameEqualityFunction, EdgeNameEqualityFunction> * clone(void) const
            {
                auto * ret = new BidirectionalGraphNaming<VertexNameType, EdgeNameType, VertexNameHashFunction, EdgeNameHashFunction, VertexNameEqualityFunction, EdgeNameEqualityFunction>();

                for (auto name : vertexNames_)
                {
                    ret->setVertexName(name.first, name.second);
                }

                for (auto name : edgeNames_)
                {
                    ret->setEdgeName(name.first, name.second);
                }

                return ret;
            }

        private:
            std::unordered_map<htd::vertex_t, VertexNameType> vertexNames_;

            std::unordered_map<htd::id_t, EdgeNameType> edgeNames_;

            std::unordered_map<VertexNameType, htd::vertex_t, VertexNameHashFunction, VertexNameEqualityFunction> vertexNamesReverseMap_;

            std::unordered_map<EdgeNameType, htd::id_t, EdgeNameHashFunction, EdgeNameEqualityFunction> edgeNamesReverseMap_;
    };
}

#endif /* HTD_HTD_BIDIRECTIONALGRAPHNAMING_HPP */
