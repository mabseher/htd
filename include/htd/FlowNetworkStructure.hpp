/* 
 * File:   FlowNetworkStructure.hpp
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

#ifndef HTD_HTD_FLOWNETWORKSTRUCTURE_HPP
#define HTD_HTD_FLOWNETWORKSTRUCTURE_HPP

#include <htd/IFlowNetworkStructure.hpp>

namespace htd
{
    /**
     *  Default implementation of the IFlowNetworkStructure interface.
     */
    class FlowNetworkStructure : public htd::IFlowNetworkStructure
    {
        public:
            /**
             *  Constructor for a flow network structure.
             *
             *  @note The vertices of the network are numbered between 0 and vertexCount - 1.
             *
             *  @param[in] vertexCount  The number of vertices of the flow network structure.
             */
            HTD_API FlowNetworkStructure(std::size_t vertexCount);

            /**
             *  Copy constructor for a flow network structure.
             *
             *  @param[in] original  The original flow network structure.
             */
            HTD_API FlowNetworkStructure(const htd::FlowNetworkStructure & original);

            /**
             *  Destructor of a flow network structure.
             */
            HTD_API virtual ~FlowNetworkStructure();

            HTD_API std::size_t vertexCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            HTD_API void copyVerticesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            HTD_API htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            HTD_API bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API void copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            HTD_API htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(void) const HTD_OVERRIDE;

            HTD_API std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            HTD_API bool isConnected(void) const HTD_OVERRIDE;

            HTD_API bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            HTD_API bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            HTD_API std::size_t capacity(htd::vertex_t source, htd::vertex_t target) const HTD_OVERRIDE;

            /**
             *  Update the capacity of edges connecting the source vertex with the target vertex.
             *
             *  @param[in] source   The source vertex.
             *  @param[in] target   The target vertex.
             *  @param[in] capacity The new capacity.
             */
            HTD_API void updateCapacity(htd::vertex_t source, htd::vertex_t target, std::size_t capacity);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            HTD_API FlowNetworkStructure * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current flow network structure.
             *
             *  @return A new IMultiHypergraph object identical to the current flow network structure.
             */
            HTD_API FlowNetworkStructure * clone(void) const;

            HTD_API IGraphStructure * cloneGraphStructure(void) const HTD_OVERRIDE;

            HTD_API IFlowNetworkStructure * cloneFlowNetworkStructure(void) const HTD_OVERRIDE;
#endif

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_FLOWNETWORKSTRUCTURE_HPP */
