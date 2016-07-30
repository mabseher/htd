/* 
 * File:   Path.cpp
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

#ifndef HTD_HTD_PATH_CPP
#define	HTD_HTD_PATH_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Path.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/HyperedgeVector.hpp>

#include <algorithm>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

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
         *  Constructor for a path node.
         *
         *  @param[in] id       The ID of the constructed path node.
         *  @param[in] parent   The parent of the constructed path node.
         */
        Node(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), child(htd::Vertex::UNKNOWN)
        {

        }
    };

    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), size_(0), root_(htd::Vertex::UNKNOWN), next_edge_(htd::Id::FIRST), next_vertex_(htd::Vertex::FIRST), nodes_()
    {

    }

    virtual ~Implementation()
    {
        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            delete it->second;
        }
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
          vertices_(original.vertices_)
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
     *  Delete a node of the path and perform an update of the internal state.
     *
     *  @param[in] node The node of the path which shall be removed.
     */
    void deleteNode(Node * node);
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
            if (std::equal(edge.begin(), edge.end(), elements.begin()))
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
            if (std::equal(edge.begin(), edge.end(), elements.begin()))
            {
                result.push_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::vertex_t htd::Path::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->vertices_.size())

    return implementation_->vertices_[index];
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
    return edgeCount() > 0;
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

void htd::Path::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
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

std::size_t htd::Path::isolatedVertexCount(void) const
{
    return 0;
}

htd::ConstCollection<htd::vertex_t> htd::Path::isolatedVertices(void) const
{
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
    HTD_UNUSED(vertex)

    return false;
}

htd::ConstCollection<htd::Hyperedge> htd::Path::hyperedges(void) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    std::vector<htd::Hyperedge> & target = ret.container();

    htd::id_t id = 0;

    for (const auto & currentNode : implementation_->nodes_)
    {
        htd::vertex_t vertex = currentNode.first;

        htd::vertex_t parent = currentNode.second->parent;
        htd::vertex_t child = currentNode.second->child;

        if (parent != htd::Vertex::UNKNOWN)
        {
            if (parent < vertex)
            {
                target.push_back(htd::Hyperedge(id, parent, vertex));
            }
            else
            {
                target.push_back(htd::Hyperedge(id, vertex, parent));
            }

            ++id;
        }

        if (child != htd::Vertex::UNKNOWN)
        {
            if (child < vertex)
            {
                target.push_back(htd::Hyperedge(id, child, vertex));
            }
            else
            {
                target.push_back(htd::Hyperedge(id, vertex, child));
            }

            ++id;
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

htd::ConstCollection<htd::Hyperedge> htd::Path::hyperedges(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::Hyperedge> ret;

    std::vector<htd::Hyperedge> & target = ret.container();

    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    for (auto it = hyperedgeCollection.begin(); it != hyperedgeCollection.end(); ++it)
    {
        const htd::Hyperedge & currentHyperedge = *it;

        if (std::find(currentHyperedge.begin(), currentHyperedge.end(), vertex) != currentHyperedge.end())
        {
            target.push_back(currentHyperedge);
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
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges(vertex);

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Path::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::FilteredHyperedgeCollection htd::Path::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    std::shared_ptr<std::vector<htd::Hyperedge>> hyperedges = std::make_shared<std::vector<htd::Hyperedge>>();

    htd::id_t id = 0;

    for (const auto & currentNode : implementation_->nodes_)
    {
        htd::vertex_t vertex = currentNode.first;

        htd::vertex_t parent = currentNode.second->parent;
        htd::vertex_t child = currentNode.second->child;

        if (parent != htd::Vertex::UNKNOWN)
        {
            if (parent < vertex)
            {
                hyperedges->push_back(htd::Hyperedge(id, parent, vertex));
            }
            else
            {
                hyperedges->push_back(htd::Hyperedge(id, vertex, parent));
            }

            ++id;
        }

        if (child != htd::Vertex::UNKNOWN)
        {
            if (child < vertex)
            {
                hyperedges->push_back(htd::Hyperedge(id, child, vertex));
            }
            else
            {
                hyperedges->push_back(htd::Hyperedge(id, vertex, child));
            }

            ++id;
        }
    }

    return htd::FilteredHyperedgeCollection(new htd::HyperedgeVector(hyperedges), indices);
}

htd::FilteredHyperedgeCollection htd::Path::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    std::shared_ptr<std::vector<htd::Hyperedge>> hyperedges = std::make_shared<std::vector<htd::Hyperedge>>();

    htd::id_t id = 0;

    for (const auto & currentNode : implementation_->nodes_)
    {
        htd::vertex_t vertex = currentNode.first;

        htd::vertex_t parent = currentNode.second->parent;
        htd::vertex_t child = currentNode.second->child;

        if (parent != htd::Vertex::UNKNOWN)
        {
            if (parent < vertex)
            {
                hyperedges->push_back(htd::Hyperedge(id, parent, vertex));
            }
            else
            {
                hyperedges->push_back(htd::Hyperedge(id, vertex, parent));
            }

            ++id;
        }

        if (child != htd::Vertex::UNKNOWN)
        {
            if (child < vertex)
            {
                hyperedges->push_back(htd::Hyperedge(id, child, vertex));
            }
            else
            {
                hyperedges->push_back(htd::Hyperedge(id, vertex, child));
            }

            ++id;
        }
    }

    return htd::FilteredHyperedgeCollection(new htd::HyperedgeVector(hyperedges), std::move(indices));
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

void htd::Path::copyChildrenTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
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
    if (isVertex(vertex))
    {
        auto & node = *(implementation_->nodes_.at(vertex));

        if (node.parent != htd::Vertex::UNKNOWN)
        {
            auto & parent = implementation_->nodes_.at(node.parent);

            if (node.child != htd::Vertex::UNKNOWN)
            {
                auto & child = implementation_->nodes_.at(node.child);

                child->parent = node.parent;

                parent->child = node.child;
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
                removeSubpath(implementation_->root_);
            }
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

        for (auto it = implementation_->nodes_.begin(); it != implementation_->nodes_.end(); it++)
        {
            delete it->second;
        }

        implementation_->nodes_.clear();
        implementation_->nodes_.emplace(implementation_->root_, new Implementation::Node(implementation_->root_, htd::Vertex::UNKNOWN));

        implementation_->vertices_.push_back(implementation_->root_);

        implementation_->size_ = 1;
    }

    return implementation_->root_;
}

htd::vertex_t htd::Path::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        htd::vertex_t child = implementation_->nodes_.at(vertex)->child;

        ret = implementation_->next_vertex_;

        implementation_->nodes_.emplace(ret, new Implementation::Node(ret, vertex));

        if (child != htd::Vertex::UNKNOWN)
        {
            implementation_->nodes_.at(child)->parent = ret;
            implementation_->nodes_.at(ret)->child = child;
        }

        implementation_->nodes_.at(vertex)->child = ret;

        implementation_->vertices_.emplace_back(ret);

        implementation_->next_vertex_++;

        implementation_->size_++;
    }
    
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
        auto & node = implementation_->nodes_.at(vertex);

        if (node != nullptr)
        {
            ret = implementation_->next_vertex_;

            Implementation::Node * newRootNode = new Implementation::Node(ret, htd::Vertex::UNKNOWN);

            node->parent = ret;

            newRootNode->child = vertex;

            implementation_->nodes_.insert(std::make_pair(ret, newRootNode));

            implementation_->vertices_.push_back(ret);

            implementation_->next_vertex_++;

            implementation_->size_++;

            implementation_->root_ = ret;
        }
    }
    else
    {
        htd::vertex_t parentVertex = parent(vertex);

        ret = addChild(parentVertex);

        auto & parentNode = implementation_->nodes_.at(parentVertex);
        auto & selectedNode = implementation_->nodes_.at(vertex);
        auto & intermediateNode = implementation_->nodes_.at(ret);

        if (parentNode != nullptr && selectedNode != nullptr && intermediateNode != nullptr)
        {
            intermediateNode->parent = parentVertex;

            intermediateNode->child = vertex;

            selectedNode->parent = ret;
        }
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
    }
    else
    {
        implementation_->nodes_.at(node.parent)->child = vertex;
    }

    if (node.child != htd::Vertex::UNKNOWN)
    {
        implementation_->nodes_.at(node.child)->parent = vertex;
    }

    if (parentNode.child != htd::Vertex::UNKNOWN)
    {
        implementation_->nodes_.at(parentNode.child)->parent = parent;
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

            std::copy(vertexCollection.begin(), vertexCollection.end(), std::back_inserter(implementation_->vertices_));

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

#endif /* HTD_HTD_PATH_CPP */
