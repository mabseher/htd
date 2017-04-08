/* 
 * File:   Path.cpp
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

#ifndef HTD_HTD_PATH_CPP
#define HTD_HTD_PATH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Path.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/HyperedgePointerDeque.hpp>
#include <htd/ConstPointerIteratorWrapper.hpp>

#include <htd/Algorithm.hpp>

#include <algorithm>
#include <deque>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

/**
 *  Private implementation details of class htd::Path.
 */
struct htd::Path::Implementation
{
    /**
     *  Structure representing a node of a path.
     */
    struct Node
    {
        /**
         *  The ID of the path node.
         */
        htd::id_t id;

        /**
         *  The parent of the path node.
         */
        htd::vertex_t parent;

        /**
         *  The child of the path node.
         */
        htd::vertex_t child;

        /**
         *  The collection of all edge identifiers containing the path node.
         */
        std::vector<htd::id_t> edges;

        /**
         *  Constructor for a path node.
         *
         *  @param[in] id       The ID of the constructed path node.
         *  @param[in] parent   The parent of the constructed path node.
         */
        Node(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), child(htd::Vertex::UNKNOWN), edges()
        {

        }
    };

    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), size_(0), root_(htd::Vertex::UNKNOWN), next_edge_(htd::Id::FIRST), next_vertex_(htd::Vertex::FIRST), nodes_(), edges_(std::make_shared<std::deque<htd::Hyperedge *>>())
    {

    }

    virtual ~Implementation()
    {
        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            delete it->second;
        }

        for (htd::Hyperedge * edge : *edges_)
        {
            delete edge;
        }

        edges_->clear();
    }

    /**
     *  Copy constructor of the implementation details structure.
     *
     *  @param[in] original  The original implementation details structure.
     */
    Implementation(const Implementation & original)
        : managementInstance_(original.managementInstance_),
          size_(original.size_),
          root_(original.root_),
          next_edge_(original.next_edge_),
          next_vertex_(original.next_vertex_),
          vertices_(original.vertices_),
          nodes_(),
          edges_(std::make_shared<std::deque<htd::Hyperedge *>>())
    {
        nodes_.reserve(original.nodes_.size());

        for (const auto & node : original.nodes_)
        {
            nodes_.insert(std::make_pair(node.first, new Node(*(node.second))));
        }
    }

    /**
     *  Reset the path to an empty one.
     */
    void reset(void)
    {
        if (root_ != htd::Vertex::UNKNOWN)
        {
            for (auto it = nodes_.begin(); it != nodes_.end(); it++)
            {
                delete it->second;
            }

            nodes_.clear();

            for (htd::Hyperedge * edge : *edges_)
            {
                delete edge;
            }

            edges_->clear();
        }

        size_ = 0;

        root_ = htd::Vertex::UNKNOWN;

        next_edge_ = htd::Id::FIRST;

        next_vertex_ = htd::Vertex::FIRST;

        vertices_.clear();
    }

    /**
     *  The management instance to which the current object instance belongs.
     */
    const htd::LibraryInstance * managementInstance_;

    /**
     *  The size of the path.
     */
    std::size_t size_;

    /**
     *  The root vertex of the path.
     */
    htd::vertex_t root_;

    /**
     *  The ID the next edge added to the tree will get.
     */
    htd::id_t next_edge_;

    /**
     *  The ID the next vertex added to the path will get.
     */
    htd::vertex_t next_vertex_;

    /**
     *  The collection of all vertices of the path in ascending order.
     */
    std::vector<htd::vertex_t> vertices_;

    /**
     *  The map of pointers to all path nodes. It maps vertex IDs to the corresponding node information.
     */
    std::unordered_map<htd::id_t, Node *> nodes_;

    /**
     *  The collection of all hyperedges which exist in the path.
     */
    std::shared_ptr<std::deque<htd::Hyperedge *>> edges_;

    /**
     *  Delete a node of the path and perform an update of the internal state.
     *
     *  @param[in] node The node of the path which shall be removed.
     */
    void deleteNode(Node * node);

    /**
     *  Updates the edge information for the nodes affected by a call to swapWithParent(htd::vertex_t).
     *
     *  @param[in] node             The node for which swapWithParent(htd::vertex_t) was called.
     *  @param[in] parentNode       The parent node of the swapped node.
     *  @param[in] grandParentNode  The grandparent node of the swapped node.
     */
    void updateEdgesAfterSwapWithParent(Node & node, Node & parentNode, Node & grandParentNode);
};

htd::Path::Path(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::Path::Path(const htd::Path & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::Path::Path(const htd::IPath & original) : implementation_(new Implementation(original.managementInstance()))
{
    *this = original;
}

htd::Path::~Path()
{

}

std::size_t htd::Path::vertexCount(void) const
{
    return implementation_->size_;
}

std::size_t htd::Path::vertexCount(htd::vertex_t subPathRoot) const
{
    HTD_ASSERT(isVertex(subPathRoot))

    std::size_t ret = 0;

    htd::vertex_t currentVertex = subPathRoot;

    while (currentVertex != htd::Vertex::UNKNOWN)
    {
        ++ret;

        currentVertex = implementation_->nodes_.at(currentVertex)->child;
    }

    return ret;
}

std::size_t htd::Path::edgeCount(void) const
{
    return implementation_->size_ > 0 ? implementation_->size_ - 1 : 0;
}

std::size_t htd::Path::edgeCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return neighborCount(vertex);
}

bool htd::Path::isVertex(htd::vertex_t vertex) const
{
    return vertex < implementation_->next_vertex_ && vertex != htd::Vertex::UNKNOWN && implementation_->nodes_.count(vertex) == 1;
}

bool htd::Path::isEdge(htd::id_t edgeId) const
{
    return edgeId > 0 && edgeId <= edgeCount();
}

bool htd::Path::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isNeighbor(vertex1, vertex2);
}

bool htd::Path::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::Path::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    if (elements.size() == 2 && elements[0] != elements[1])
    {
        ret = isNeighbor(elements[0], elements[1]);
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::Path::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge[0] == vertex1 && edge[1] == vertex2)
        {
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::Path::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::Path::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

bool htd::Path::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    bool ret = false;
    
    if (isVertex(vertex) && isVertex(neighbor))
    {
        const auto & node = implementation_->nodes_.at(vertex);

        ret = node->parent == neighbor || node->child == neighbor;
    }
    
    return ret;
}

bool htd::Path::isConnected(void) const
{
    return true;
}

bool htd::Path::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isVertex(vertex1) && isVertex(vertex2);
}

std::size_t htd::Path::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        const auto & node = implementation_->nodes_.at(vertex);

        if (node->parent != htd::Vertex::UNKNOWN)
        {
            ++ret;
        }

        if (node->child != htd::Vertex::UNKNOWN)
        {
            ++ret;
        }
    }
    
    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const auto & node = implementation_->nodes_.at(vertex);

    if (node->parent != htd::Vertex::UNKNOWN)
    {
        result.push_back(node->parent);
    }

    if (node->child != htd::Vertex::UNKNOWN)
    {
        result.push_back(node->child);
    }

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Path::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t size = target.size();

    const auto & node = implementation_->nodes_.at(vertex);

    if (node->parent != htd::Vertex::UNKNOWN)
    {
        target.push_back(node->parent);
    }

    if (node->child != htd::Vertex::UNKNOWN)
    {
        target.push_back(node->child);
    }

    std::sort(target.begin() + size, target.end());
}

htd::vertex_t htd::Path::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const htd::ConstCollection<htd::vertex_t> & currentNeighbors = neighbors(vertex);

    HTD_ASSERT(index < currentNeighbors.size())
    
    return currentNeighbors[index];
}

htd::ConstCollection<htd::vertex_t> htd::Path::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->vertices_);
}

const std::vector<htd::vertex_t> & htd::Path::vertexVector(void) const
{
    return implementation_->vertices_;
}

void htd::Path::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    target.insert(target.end(),
                  implementation_->vertices_.begin(),
                  implementation_->vertices_.end());
}

htd::vertex_t htd::Path::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->vertices_.size())

    return implementation_->vertices_[index];
}

std::size_t htd::Path::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    if (implementation_->size_ == 1)
    {
        ret = 1;
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::isolatedVertices(void) const
{
    if (implementation_->size_ == 1)
    {
        htd::VectorAdapter<htd::vertex_t> result;

        result.container().emplace_back(implementation_->root_);

        return htd::ConstCollection<htd::vertex_t>(result.begin(), result.end());
    }

    return htd::ConstCollection<htd::vertex_t>();
}

htd::vertex_t htd::Path::isolatedVertexAtPosition(htd::index_t index) const
{
    HTD_UNUSED(index)

    HTD_ASSERT(implementation_->size_ == 1 && index == 0)

    return implementation_->root_;
}

bool htd::Path::isIsolatedVertex(htd::vertex_t vertex) const
{
    return implementation_->size_ == 1 && vertex == implementation_->root_;
}

htd::ConstCollection<htd::Hyperedge> htd::Path::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>(static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(implementation_->edges_->begin())),
                                                static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(implementation_->edges_->end())));
}

htd::ConstCollection<htd::Hyperedge> htd::Path::hyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    for (auto & edge : *(implementation_->edges_))
    {
        if (edge->contains(vertex))
        {
            result.emplace_back(*edge);
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

const htd::Hyperedge & htd::Path::hyperedge(htd::id_t edgeId) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    bool found = false;

    auto position = hyperedgeCollection.begin();

    for (auto it = hyperedgeCollection.begin(); !found && it != hyperedgeCollection.end(); ++it)
    {
        if (it->id() == edgeId)
        {
            position = it;

            found = true;
        }
    }

    if (!found)
    {
        throw std::logic_error("const htd::Hyperedge & htd::Path::hyperedge(htd::id_t) const");
    }

    return *position;
}

const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->edges_->size())

    return *(implementation_->edges_->at(index));
}

const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    for (auto it = implementation_->edges_->begin(); it != implementation_->edges_->end(); ++it)
    {
        const htd::Hyperedge & hyperedge = **it;

        if (hyperedge.contains(vertex))
        {
            if (index == 0)
            {
                return hyperedge;
            }

            --index;
        }
    }

    throw std::out_of_range("const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
}

htd::FilteredHyperedgeCollection htd::Path::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    #ifndef NDEBUG
    for (htd::index_t index : indices)
    {
        HTD_ASSERT(index < implementation_->edges_->size())
    }
    #endif

    return htd::FilteredHyperedgeCollection(new htd::HyperedgePointerDeque(implementation_->edges_), indices);
}

htd::FilteredHyperedgeCollection htd::Path::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    #ifndef NDEBUG
    for (htd::index_t index : indices)
    {
        HTD_ASSERT(index < implementation_->edges_->size())
    }
    #endif

    return htd::FilteredHyperedgeCollection(new htd::HyperedgePointerDeque(implementation_->edges_), std::move(indices));
}

htd::vertex_t htd::Path::root(void) const
{
    HTD_ASSERT(implementation_->root_ != htd::Vertex::UNKNOWN)

    return implementation_->root_;
}

bool htd::Path::isRoot(htd::vertex_t vertex) const
{
    return implementation_->root_ == vertex;
}

htd::vertex_t htd::Path::parent(htd::vertex_t vertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        ret = implementation_->nodes_.at(vertex)->parent;
    }
    
    return ret;
}

bool htd::Path::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(parent))

    return implementation_->nodes_.at(vertex)->parent == parent;
}

std::size_t htd::Path::childCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        if (implementation_->nodes_.at(vertex)->child != htd::Vertex::UNKNOWN)
        {
            ++ret;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::children(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    if (implementation_->nodes_.at(vertex)->child != htd::Vertex::UNKNOWN)
    {
        ret.container().emplace_back(implementation_->nodes_.at(vertex)->child);
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Path::copyChildrenTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    if (implementation_->nodes_.at(vertex)->child != htd::Vertex::UNKNOWN)
    {
        target.emplace_back(implementation_->nodes_.at(vertex)->child);
    }
}

htd::vertex_t htd::Path::child(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t child = implementation_->nodes_.at(vertex)->child;

    HTD_ASSERT(child != htd::Vertex::UNKNOWN)

    return child;
}

htd::vertex_t htd::Path::childAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_UNUSED(index)

    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t child = implementation_->nodes_.at(vertex)->child;

    HTD_ASSERT(index == 0 && child != htd::Vertex::UNKNOWN)
    
    return child;
}

bool htd::Path::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(child))

    return implementation_->nodes_.at(vertex)->child == child;
}

std::size_t htd::Path::height(void) const
{
    return height(implementation_->root_);
}

std::size_t htd::Path::height(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t ret = 0;

    htd::vertex_t currentVertex = implementation_->nodes_.at(vertex)->child;

    while (currentVertex != htd::Vertex::UNKNOWN)
    {
        ++ret;

        currentVertex = implementation_->nodes_.at(currentVertex)->child;
    }

    return ret;
}

std::size_t htd::Path::depth(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t ret = 0;

    htd::vertex_t currentVertex = implementation_->nodes_.at(vertex)->parent;

    while (currentVertex != htd::Vertex::UNKNOWN)
    {
        ++ret;

        currentVertex = implementation_->nodes_.at(currentVertex)->parent;
    }

    return ret;
}

htd::vertex_t htd::Path::nextVertex(void) const
{
    return implementation_->next_vertex_;
}

htd::id_t htd::Path::nextEdgeId(void) const
{
    return implementation_->next_edge_;
}

void htd::Path::removeVertex(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    auto & node = *(implementation_->nodes_.at(vertex));

    auto end = implementation_->edges_->end();

    for (auto it = node.edges.rbegin(); it != node.edges.rend(); ++it)
    {
        auto position = htd::hyperedgePointerPosition(implementation_->edges_->begin(), end, *it);

        for (htd::vertex_t currentVertex : (*position)->sortedElements())
        {
            if (currentVertex != vertex)
            {
                std::vector<htd::id_t> & currentEdges = implementation_->nodes_.at(currentVertex)->edges;

                /* Because 'currentVertex' is a neighbor of 'vertex' and 'position' points to the
                 * edge connecting the two vertices, std::lower_bound will always find the edge
                 * with ID '*it' in the collection 'currentEdges'. */
                // coverity[use_iterator]
                currentEdges.erase(std::lower_bound(currentEdges.begin(), currentEdges.end(), *it));
            }
        }

        delete *position;

        end = implementation_->edges_->erase(position);
    }

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        auto & parentNode = *(implementation_->nodes_.at(node.parent));

        parentNode.child = node.child;

        if (node.child != htd::Vertex::UNKNOWN)
        {
            auto & childNode = *(implementation_->nodes_.at(node.child));

            childNode.parent = node.parent;

            if (node.parent < node.child)
            {
                implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, node.parent, node.child));
            }
            else
            {
                implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, node.child, node.parent));
            }

            childNode.edges.emplace_back(implementation_->next_edge_);

            parentNode.edges.emplace_back(implementation_->next_edge_);

            ++implementation_->next_edge_;
        }

        implementation_->deleteNode(&node);
    }
    else
    {
        if (node.child != htd::Vertex::UNKNOWN)
        {
            auto & child = *(implementation_->nodes_.at(node.child));

            child.parent = htd::Vertex::UNKNOWN;

            implementation_->root_ = node.child;

            implementation_->deleteNode(&node);
        }
        else
        {
            implementation_->root_ = htd::Vertex::UNKNOWN;

            implementation_->size_ = 0;

            implementation_->nodes_.clear();
            implementation_->edges_->clear();

            implementation_->vertices_.clear();

            delete &node;
        }
    }
}

void htd::Path::removeSubpath(htd::vertex_t subpathRoot)
{
    HTD_ASSERT(isVertex(subpathRoot))

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubPathRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubPathRoot)

        removeVertex(vertex);
    }, subpathRoot);
}

htd::vertex_t htd::Path::insertRoot(void)
{
    if (implementation_->root_ == htd::Vertex::UNKNOWN)
    {
        implementation_->root_ = htd::Vertex::FIRST;

        implementation_->next_vertex_ = implementation_->root_ + 1;

        implementation_->nodes_.emplace(implementation_->root_, new Implementation::Node(implementation_->root_, htd::Vertex::UNKNOWN));

        implementation_->vertices_.push_back(implementation_->root_);

        implementation_->size_ = 1;
    }

    return implementation_->root_;
}

htd::vertex_t htd::Path::addChild(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    Implementation::Node & node = *(implementation_->nodes_.at(vertex));

    ret = implementation_->next_vertex_;

    htd::vertex_t child = node.child;

    Implementation::Node * newNode = new Implementation::Node(ret, vertex);

    implementation_->nodes_.emplace(ret, newNode);

    if (child != htd::Vertex::UNKNOWN)
    {
        Implementation::Node & childNode = *(implementation_->nodes_.at(child));

        htd::id_t oldHyperedge = htd::Id::UNKNOWN;

        auto it = node.edges.begin();

        while (it != node.edges.end())
        {
            auto position = htd::hyperedgePointerPosition(implementation_->edges_->begin(), implementation_->edges_->end(), *it);

            HTD_ASSERT(position != implementation_->edges_->end())

            if ((*position)->contains(child))
            {
                oldHyperedge = (*position)->id();

                delete *position;

                implementation_->edges_->erase(position);

                it = node.edges.end();
            }
            else
            {
                ++it;
            }
        }

        node.edges.erase(std::lower_bound(node.edges.begin(), node.edges.end(), oldHyperedge));
        childNode.edges.erase(std::lower_bound(childNode.edges.begin(), childNode.edges.end(), oldHyperedge));

        childNode.parent = ret;
        newNode->child = child;

        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, child, ret));

        newNode->edges.push_back(implementation_->next_edge_);
        childNode.edges.push_back(implementation_->next_edge_);

        implementation_->next_edge_++;
    }

    node.child = ret;

    implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, vertex, ret));

    node.edges.push_back(implementation_->next_edge_);
    newNode->edges.push_back(implementation_->next_edge_);

    implementation_->vertices_.emplace_back(ret);

    implementation_->next_vertex_++;

    implementation_->next_edge_++;

    implementation_->size_++;

    return ret;
}

void htd::Path::removeChild(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t child = implementation_->nodes_.at(vertex)->child;

    HTD_ASSERT(child != htd::Vertex::UNKNOWN)

    removeVertex(child);
}

void htd::Path::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(child))

    const auto & node = implementation_->nodes_.at(vertex);

    if (node->child == child)
    {
        removeVertex(child);
    }
}

htd::vertex_t htd::Path::addParent(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isRoot(vertex))
    {
        auto & node = *(implementation_->nodes_.at(vertex));

        ret = implementation_->next_vertex_;

        Implementation::Node * newRootNode = new Implementation::Node(ret, htd::Vertex::UNKNOWN);

        node.parent = ret;

        newRootNode->child = vertex;

        implementation_->nodes_.emplace(ret, newRootNode);

        implementation_->vertices_.push_back(ret);

        implementation_->next_vertex_++;

        implementation_->size_++;

        implementation_->root_ = ret;

        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, vertex, ret));

        implementation_->nodes_.at(vertex)->edges.push_back(implementation_->next_edge_);
        newRootNode->edges.push_back(implementation_->next_edge_);

        implementation_->next_edge_++;
    }
    else
    {
        htd::vertex_t parentVertex = parent(vertex);

        ret = addChild(parentVertex);

        auto & selectedNode = *(implementation_->nodes_.at(vertex));
        auto & intermediateNode = *(implementation_->nodes_.at(ret));

        intermediateNode.parent = parentVertex;

        intermediateNode.child = vertex;

        selectedNode.parent = ret;
    }

    return ret;
}

std::size_t htd::Path::leafCount(void) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    if (implementation_->size_ > 0)
    {
        ++ret;
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::leaves(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    copyLeavesTo(ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Path::copyLeavesTo(std::vector<htd::vertex_t> & target) const
{
    for (const auto & node : implementation_->nodes_)
    {
        if (node.second->child == htd::Vertex::UNKNOWN)
        {
            target.push_back(node.first);
        }
    }

    std::sort(target.begin(), target.end());
}

htd::vertex_t htd::Path::leaf(void) const
{
    HTD_ASSERT(implementation_->size_ > 0)

    for (const auto & node : implementation_->nodes_)
    {
        if (node.second->child == htd::Vertex::UNKNOWN)
        {
            return node.first;
        }
    }

    return htd::Vertex::UNKNOWN;
}

htd::vertex_t htd::Path::leafAtPosition(htd::index_t index) const
{
    HTD_UNUSED(index)

    HTD_ASSERT(implementation_->size_ > 0 && index == 0)

    return leaf();
}

bool htd::Path::isLeaf(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->nodes_.at(vertex)->child == htd::Vertex::UNKNOWN;
}

void htd::Path::Implementation::deleteNode(Node * node)
{
    if (node != nullptr)
    {
        auto & parent = node->parent;

        htd::id_t nodeIdentifier = node->id;

        if (parent != htd::Vertex::UNKNOWN)
        {
            auto & parentNode = nodes_.at(parent);

            htd::vertex_t child = parentNode->child;

            if (child != htd::Vertex::UNKNOWN)
            {
                auto & childNode = nodes_.at(child);

                parentNode->child = child;
                childNode->parent = parent;
            }

            size_--;

            delete nodes_.at(nodeIdentifier);

            nodes_.erase(nodeIdentifier);

            vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
        }
        else
        {
            size_--;

            delete nodes_.at(nodeIdentifier);

            nodes_.erase(nodeIdentifier);

            vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
        }
    }
}

void htd::Path::swapWithParent(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    Implementation::Node & node = *(implementation_->nodes_.at(vertex));

    htd::vertex_t parent = node.parent;

    HTD_ASSERT(parent != htd::Vertex::UNKNOWN)

    Implementation::Node & parentNode = *(implementation_->nodes_.at(parent));

    std::swap(node.child, parentNode.child);

    node.parent = parentNode.parent;

    parentNode.parent = vertex;

    node.child = parent;

    if (node.parent == htd::Vertex::UNKNOWN)
    {
        implementation_->root_ = vertex;

        if (parentNode.child != htd::Vertex::UNKNOWN)
        {
            Implementation::Node & childNode = *(implementation_->nodes_.at(parentNode.child));

            implementation_->updateEdgesAfterSwapWithParent(parentNode, node, childNode);

            childNode.parent = parent;
        }
    }
    else
    {
        htd::vertex_t grandParent = node.parent;

        Implementation::Node & grandParentNode = *(implementation_->nodes_.at(grandParent));

        grandParentNode.child = vertex;

        implementation_->updateEdgesAfterSwapWithParent(node, parentNode, grandParentNode);
    }
}

const htd::LibraryInstance * htd::Path::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::Path::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::Path * htd::Path::clone(void) const
{
    return new htd::Path(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::IPath * htd::Path::clonePath(void) const
{
    return clone();
}

htd::ITree * htd::Path::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::Path::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::Path::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::Path::cloneHypergraph(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::Path::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::Path::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMutablePath * htd::Path::cloneMutablePath(void) const
{
    return clone();
}
#endif

htd::Path & htd::Path::operator=(const htd::Path & original)
{
    if (this != &original)
    {
        implementation_->reset();

        implementation_->nodes_.reserve(original.implementation_->nodes_.size());

        for (const auto & node : original.implementation_->nodes_)
        {
            implementation_->nodes_.emplace(node.first, new Implementation::Node(*(node.second)));
        }

        implementation_->root_ = original.implementation_->root_;

        implementation_->size_ = original.implementation_->size_;

        if (original.implementation_->next_vertex_ >= htd::Vertex::FIRST)
        {
            implementation_->next_vertex_ = original.implementation_->next_vertex_;
        }
        else
        {
            implementation_->next_vertex_ = htd::Vertex::FIRST;
        }
    }

    return *this;
}

htd::Path & htd::Path::operator=(const htd::IPath & original)
{
    if (this != &original)
    {
        implementation_->reset();

        implementation_->size_ = original.vertexCount();

        if (implementation_->size_ > 0)
        {
            implementation_->root_ = original.root();

            htd::vertex_t maximumVertex = implementation_->root_;

            const htd::ConstCollection<htd::vertex_t> & vertexCollection = original.vertices();

            implementation_->vertices_.insert(implementation_->vertices_.end(), vertexCollection.begin(), vertexCollection.end());

            for (htd::vertex_t vertex : implementation_->vertices_)
            {
                Implementation::Node * newNode = nullptr;

                if (original.isRoot(vertex))
                {
                    newNode = new Implementation::Node(vertex, htd::Vertex::UNKNOWN);
                }
                else
                {
                    newNode = new Implementation::Node(vertex, original.parent(vertex));
                }

                if (!original.isLeaf(vertex))
                {
                    newNode->child = original.child(vertex);
                }

                implementation_->nodes_.emplace(vertex, newNode);

                if (vertex > maximumVertex)
                {
                    maximumVertex = vertex;
                }
            }

            if (maximumVertex >= htd::Vertex::FIRST)
            {
                implementation_->next_vertex_ = maximumVertex + 1;
            }
            else
            {
                implementation_->next_vertex_ = htd::Vertex::FIRST;
            }
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::Path::assign(const htd::IPath & original)
{
    *this = original;
}
#endif

void htd::Path::Implementation::updateEdgesAfterSwapWithParent(Node & node, Node & parentNode, Node & grandParentNode)
{
    htd::vertex_t vertex = node.id;
    htd::vertex_t parent = parentNode.id;
    htd::vertex_t grandParent = grandParentNode.id;

    auto relevantEdgePosition = edges_->end();

    for (auto it = grandParentNode.edges.begin(); it != grandParentNode.edges.end() && relevantEdgePosition == edges_->end(); ++it)
    {
        auto edgePosition = htd::hyperedgePointerPosition(edges_->begin(), edges_->end(), *it);

        if ((*edgePosition)->contains(parent))
        {
            relevantEdgePosition = edgePosition;
        }
    }

    htd::id_t oldEdgeId = (*relevantEdgePosition)->id();

    parentNode.edges.erase(std::lower_bound(parentNode.edges.begin(), parentNode.edges.end(), oldEdgeId));

    grandParentNode.edges.erase(std::lower_bound(grandParentNode.edges.begin(), grandParentNode.edges.end(), oldEdgeId));

    node.edges.emplace_back(next_edge_);

    grandParentNode.edges.emplace_back(next_edge_);

    (*relevantEdgePosition)->setId(next_edge_);

    if (vertex < grandParent)
    {
        (*relevantEdgePosition)->setElements(vertex, grandParent);
    }
    else
    {
        (*relevantEdgePosition)->setElements(grandParent, vertex);
    }

    ++next_edge_;

    std::rotate(relevantEdgePosition, relevantEdgePosition + 1, edges_->end());
}

#endif /* HTD_HTD_PATH_CPP */
