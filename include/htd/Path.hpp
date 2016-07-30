/* 
 * File:   Path.hpp
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

#ifndef HTD_HTD_PATH_HPP
#define	HTD_HTD_PATH_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/IMutablePath.hpp>

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace htd
{
    /**
     *  Default implementation of the IMutablePath interface.
     */
    class HTD_API Path : public virtual htd::IMutablePath
    {
        public:
            /**
             *  Constructor for a path.
             */
            Path(const htd::LibraryInstance * const manager);

            /**
             *  Copy constructor for a path.
             *
             *  @param[in] original  The original path.
             */
            Path(const Path & original);

            /**
             *  Copy constructor for a path.
             *
             *  @param[in] original  The original path.
             */
            Path(const htd::IPath & original);
            
            virtual ~Path();
            
            std::size_t vertexCount(void) const HTD_OVERRIDE;

            std::size_t vertexCount(htd::vertex_t subPathRoot) const HTD_OVERRIDE;

            std::size_t edgeCount(void) const HTD_OVERRIDE;

            std::size_t edgeCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isEdge(htd::id_t edgeId) const HTD_OVERRIDE;

            bool isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            bool isEdge(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            bool isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::ConstCollection<htd::id_t> associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const HTD_OVERRIDE;

            htd::vertex_t vertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isConnected(void) const HTD_OVERRIDE;
            
            bool isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const HTD_OVERRIDE;

            std::size_t neighborCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> neighbors(htd::vertex_t vertex) const HTD_OVERRIDE;

            void copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> vertices(void) const HTD_OVERRIDE;

            /**
             *  Access the vector of all vertices in the tree.
             *
             *  @return The vector of all vertices in the tree sorted in ascending order.
             */
            const std::vector<htd::vertex_t> & vertexVector(void) const;

            std::size_t isolatedVertexCount(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> isolatedVertices(void) const HTD_OVERRIDE;

            htd::vertex_t isolatedVertexAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isIsolatedVertex(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(void) const HTD_OVERRIDE;

            htd::ConstCollection<htd::Hyperedge> hyperedges(htd::vertex_t vertex) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedge(htd::id_t edgeId) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index) const HTD_OVERRIDE;

            const htd::Hyperedge & hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const HTD_OVERRIDE;

            htd::FilteredHyperedgeCollection hyperedgesAtPositions(std::vector<htd::index_t> && indices) const HTD_OVERRIDE;

            htd::vertex_t root(void) const HTD_OVERRIDE;

            bool isRoot(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t leafCount(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> leaves(void) const HTD_OVERRIDE;

            void copyLeavesTo(std::vector<htd::vertex_t> & target) const HTD_OVERRIDE;

            htd::vertex_t leaf(void) const HTD_OVERRIDE;

            htd::vertex_t leafAtPosition(htd::index_t index) const HTD_OVERRIDE;

            bool isLeaf(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t parent(htd::vertex_t vertex) const HTD_OVERRIDE;

            bool isParent(htd::vertex_t vertex, htd::vertex_t parent) const HTD_OVERRIDE;

            std::size_t childCount(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::ConstCollection<htd::vertex_t> children(htd::vertex_t vertex) const HTD_OVERRIDE;

            void copyChildrenTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t child(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t childAtPosition(htd::vertex_t vertex, htd::index_t index) const HTD_OVERRIDE;

            bool isChild(htd::vertex_t vertex, htd::vertex_t child) const HTD_OVERRIDE;

            std::size_t height(void) const HTD_OVERRIDE;

            std::size_t height(htd::vertex_t vertex) const HTD_OVERRIDE;

            std::size_t depth(htd::vertex_t vertex) const HTD_OVERRIDE;

            htd::vertex_t nextVertex(void) const HTD_OVERRIDE;

            htd::id_t nextEdgeId(void) const HTD_OVERRIDE;

            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeSubpath(htd::vertex_t subpathRoot) HTD_OVERRIDE;

            htd::vertex_t insertRoot(void) HTD_OVERRIDE;

            htd::vertex_t addChild(htd::vertex_t vertex) HTD_OVERRIDE;

            htd::vertex_t addParent(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex) HTD_OVERRIDE;

            void removeChild(htd::vertex_t vertex, htd::vertex_t child) HTD_OVERRIDE;

            void swapWithParent(htd::vertex_t vertex) HTD_OVERRIDE;

            const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE;

            void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            Path * clone(void) const HTD_OVERRIDE;
#else
            /**
             *  Create a deep copy of the current mutable path.
             *
             *  @return A new Path object identical to the current mutable path.
             */
            Path * clone(void) const;

            htd::IPath * clonePath(void) const HTD_OVERRIDE;

            htd::ITree * cloneTree(void) const HTD_OVERRIDE;

            htd::IGraph * cloneGraph(void) const HTD_OVERRIDE;

            htd::IMultiGraph * cloneMultiGraph(void) const HTD_OVERRIDE;

            htd::IHypergraph * cloneHypergraph(void) const HTD_OVERRIDE;

            htd::IMultiHypergraph * cloneMultiHypergraph(void) const HTD_OVERRIDE;

            htd::IMutablePath * cloneMutablePath(void) const HTD_OVERRIDE;
#endif

            /**
             *  Copy assignment operator for a mutable path.
             *
             *  @param[in] original  The original path.
             */
            Path & operator=(const Path & original);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            Path & operator=(const htd::IPath & original) HTD_OVERRIDE;
#else
            Path & operator=(const htd::IPath & original);

            void assign(const htd::IPath & original) HTD_OVERRIDE;
#endif

        private:
            HTD_IMPLEMENTATION Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_HTD_PATH_HPP */
