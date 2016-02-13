/*
 * File:   BidirectionalGraphNaming.hpp
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

#ifndef HTD_HTD_BIDIRECTIONALGRAPHNAMING_HPP
#define	HTD_HTD_BIDIRECTIONALGRAPHNAMING_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <stdexcept>
#include <unordered_map>

namespace htd
{
    template <typename VertexNameType, typename EdgeNameType,
              typename VertexNameHashFunction = std::hash<VertexNameType>, typename VertexNameEqualityFunction = std::equal_to<VertexNameType>,
              typename EdgeNameHashFunction = std::hash<EdgeNameType>, typename EdgeNameEqualityFunction = std::equal_to<EdgeNameType>>
    class BidirectionalGraphNaming
    {
        public:
            BidirectionalGraphNaming(void) : vertexNames_(), edgeNames_(), vertexNamesReverseMap_(), edgeNamesReverseMap_()
            {

            }

            ~BidirectionalGraphNaming()
            {

            }

            std::size_t vertexNameCount(void) const
            {
                return vertexNames_.size();
            }

            std::size_t edgeNameCount(void) const
            {
                return edgeNames_.size();
            }

            bool isNamedVertex(htd::vertex_t vertex) const
            {
                return vertexNames_.find(vertex) != vertexNames_.end();
            }

            bool isNamedEdge(htd::id_t edgeId) const
            {
                return edgeNames_.find(edgeId) != edgeNames_.end();
            }

            const VertexNameType & vertexName(htd::vertex_t vertex) const
            {
                return vertexNames_.at(vertex);
            }

            const EdgeNameType & edgeName(htd::id_t edgeId) const
            {
                return edgeNames_.at(edgeId);
            }

            void setVertexName(htd::vertex_t vertex, const VertexNameType & name)
            {
                if (vertexNamesReverseMap_.find(name) == vertexNamesReverseMap_.end())
                {
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
                else
                {
                    throw std::logic_error("void htd::BidirectionalGraphNaming::setVertexName(htd::vertex_t, const VertexNameType &)");
                }
            }

            void setEdgeName(htd::id_t edgeId, const EdgeNameType & name)
            {
                if (edgeNamesReverseMap_.find(name) == edgeNamesReverseMap_.end())
                {
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
                else
                {
                    throw std::logic_error("void htd::BidirectionalGraphNaming::setEdgeName(htd::id_t, const EdgeNameType &)");
                }
            }

            std::pair<htd::id_t, bool> insertVertex(const VertexNameType & name, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::pair<htd::id_t, bool> ret(0, false);

                auto result = vertexNamesReverseMap_.insert(std::make_pair(name, 0));

                if (result.second)
                {
                    htd::vertex_t newVertex = vertexCreationFunction();

                    ret.first = newVertex;

                    ret.second = true;

                    result.first->second = newVertex;

                    vertexNames_[newVertex] = name;
                }
                else
                {
                    ret.first = result.first->second;
                }

                return ret;
            }

            std::vector<htd::id_t> insertVertices(const std::vector<VertexNameType> & names, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::vector<htd::id_t> ret;

                ret.reserve(names.size());

                for (const VertexNameType & name : names)
                {
                    auto result = vertexNamesReverseMap_.insert(std::make_pair(name, 0));

                    if (result.second)
                    {
                        htd::vertex_t newVertex = vertexCreationFunction();

                        ret.push_back(newVertex);

                        result.first->second = newVertex;

                        vertexNames_[newVertex] = name;
                    }
                    else
                    {
                        ret.push_back(result.first->second);
                    }
                }

                return ret;
            }

            std::vector<htd::id_t> insertVertices(const htd::ConstCollection<VertexNameType> & names, const std::function<htd::vertex_t(void)> & vertexCreationFunction)
            {
                std::vector<htd::id_t> ret;

                ret.reserve(names.size());

                for (const VertexNameType & name : names)
                {
                    auto result = vertexNamesReverseMap_.insert(std::make_pair(name, 0));

                    if (result.second)
                    {
                        htd::vertex_t newVertex = vertexCreationFunction();

                        ret.push_back(newVertex);

                        result.first->second = newVertex;

                        vertexNames_[newVertex] = name;
                    }
                    else
                    {
                        ret.push_back(result.first->second);
                    }
                }

                return ret;
            }

            void removeVertexName(htd::vertex_t vertex)
            {
                auto position = vertexNames_.find(vertex);

                if (position != vertexNames_.end())
                {
                    auto position2 = vertexNamesReverseMap_.find(position->second);

                    if (position2 != vertexNamesReverseMap_.end())
                    {
                        vertexNamesReverseMap_.erase(position2);
                    }

                    vertexNames_.erase(position);
                }
                else
                {
                    throw std::out_of_range("htd::BidirectionalGraphNaming::removeVertexName(htd::vertex_t)");
                }
            }

            void removeEdgeName(htd::id_t edgeId)
            {
                auto position = edgeNames_.find(edgeId);

                if (position != edgeNames_.end())
                {
                    auto position2 = edgeNamesReverseMap_.find(position->second);

                    if (position2 != edgeNamesReverseMap_.end())
                    {
                        edgeNamesReverseMap_.erase(position2);
                    }

                    edgeNames_.erase(position);
                }
                else
                {
                    throw std::out_of_range("htd::BidirectionalGraphNaming::removeEdgeName(htd::id_t edgeId)");
                }
            }

            bool isVertexName(const VertexNameType & name) const
            {
                return vertexNamesReverseMap_.count(name) > 0;
            }

            bool isEdgeName(const EdgeNameType & name) const
            {
                return edgeNamesReverseMap_.count(name) > 0;
            }

            htd::vertex_t lookupVertex(const VertexNameType & name) const
            {
                return vertexNamesReverseMap_.at(name);
            }

            htd::id_t lookupEdge(const EdgeNameType & name) const
            {
                return edgeNamesReverseMap_.at(name);
            }

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
