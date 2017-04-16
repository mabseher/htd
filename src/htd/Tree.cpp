/* 
 * File:   Tree.cpp
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

#ifndef HTD_HTD_TREE_CPP
#define HTD_HTD_TREE_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Tree.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/PreOrderTreeTraversal.hpp>
#include <htd/PostOrderTreeTraversal.hpp>
#include <htd/HyperedgePointerDeque.hpp>
#include <htd/ConstPointerIteratorWrapper.hpp>

#include <htd/Algorithm.hpp>

#include <algorithm>
#include <deque>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>

/**
 *  Private implementation details of class htd::Tree.
 */
struct htd::Tree::Implementation
{
    /**
     *  Structure representing a node of a tree.
     */
    struct Node
    {
        /**
         *  The ID of the tree node.
         */
        htd::id_t id;

        /**
         *  The parent of the tree node.
         */
        htd::vertex_t parent;

        /**
         *  The collection of all edge identifiers containing the tree node.
         */
        std::vector<htd::id_t> edges;

        /**
         *  The collection of all children of the tree node.
         */
        std::vector<htd::vertex_t> children;

        /**
         *  Constructor for a tree node.
         *
         *  @param[in] id       The ID of the constructed tree node.
         *  @param[in] parent   The parent of the constructed tree node.
         */
        Node(htd::id_t id, htd::vertex_t parent) : id(id), parent(parent), edges(), children()
        {

        }

        /**
         *  Copy constructor for a tree node.
         *
         *  @param[in] original  The original tree node.
         */
        Node(const Node & original) : id(original.id), parent(original.parent), edges(original.edges), children(original.children)
        {

        }

        /**
         *  Move constructor for a tree node.
         *
         *  @param[in] original  The original tree node.
         */
        Node(Node && original) : id(original.id), parent(original.parent), edges(std::move(original.edges)), children(std::move(original.children))
        {

        }
    };

    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] manager   The management instance to which the current object instance belongs.
     */
    Implementation(const htd::LibraryInstance * const manager) : managementInstance_(manager), size_(0), root_(htd::Vertex::UNKNOWN), next_edge_(htd::Id::FIRST), next_vertex_(htd::Vertex::FIRST), vertices_(), nodes_(), edges_(std::make_shared<std::deque<htd::Hyperedge *>>())
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
            nodes_.emplace(node.first, new Node(*(node.second)));
        }

        for (const htd::Hyperedge * edge : *(original.edges_))
        {
            edges_->emplace_back(new htd::Hyperedge(*edge));
        }
    }

    /**
     *  Reset the tree to an empty one.
     */
    void reset(void)
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
     *  The size of the tree.
     */
    std::size_t size_;

    /**
     *  The root vertex of the tree.
     */
    htd::vertex_t root_;

    /**
     *  The ID the next edge added to the tree will get.
     */
    htd::id_t next_edge_;

    /**
     *  The ID the next vertex added to the tree will get.
     */
    htd::vertex_t next_vertex_;

    /**
     *  The collection of all vertices of the tree in ascending order.
     */
    std::vector<htd::vertex_t> vertices_;

    /**
     *  The map of pointers to all tree nodes. It maps vertex IDs to the corresponding node information.
     */
    std::unordered_map<htd::id_t, Node *> nodes_;

    /**
     *  The collection of all hyperedges which exist in the tree.
     */
    std::shared_ptr<std::deque<htd::Hyperedge *>> edges_;

    /**
     *  Delete a node of the tree and perform an update of the internal state.
     *
     *  @param[in] node The node of the tree which shall be removed.
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

htd::Tree::Tree(const htd::LibraryInstance * const manager) : implementation_(new Implementation(manager))
{

}

htd::Tree::Tree(const htd::Tree & original) : implementation_(new Implementation(*(original.implementation_)))
{

}

htd::Tree::Tree(const htd::ITree & original) : implementation_(new Implementation(original.managementInstance()))
{
    *this = original;
}

htd::Tree::~Tree()
{

}

std::size_t htd::Tree::vertexCount(void) const
{
    return implementation_->size_;
}

std::size_t htd::Tree::vertexCount(htd::vertex_t subtreeRoot) const
{
    HTD_ASSERT(isVertex(subtreeRoot))

    std::size_t ret = 0;

    htd::PreOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(vertex)
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        ++ret;
    }, subtreeRoot);

    return ret;
}

std::size_t htd::Tree::edgeCount(void) const
{
    return implementation_->edges_->size();
}

std::size_t htd::Tree::edgeCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return neighborCount(vertex);
}

bool htd::Tree::isVertex(htd::vertex_t vertex) const
{
    return vertex < implementation_->next_vertex_ && vertex != htd::Vertex::UNKNOWN && implementation_->nodes_.count(vertex) == 1;
}

bool htd::Tree::isEdge(htd::id_t edgeId) const
{
    return edgeId > 0 && edgeId <= edgeCount();
}

bool htd::Tree::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isNeighbor(vertex1, vertex2);
}

bool htd::Tree::isEdge(const std::vector<htd::vertex_t> & elements) const
{
    return isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

bool htd::Tree::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    bool ret = false;

    if (elements.size() == 2 && elements[0] != elements[1])
    {
        ret = isNeighbor(elements[0], elements[1]);
    }

    return ret;
}

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    htd::VectorAdapter<htd::id_t> ret;

    auto & result = ret.container();

    for (const htd::Hyperedge & edge : hyperedges())
    {
        if (edge[0] == vertex1 && edge[1] == vertex2)
        {
            result.emplace_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
            {
                result.emplace_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    htd::VectorAdapter<htd::id_t> ret;

    if (elements.size() == 2)
    {
        auto & result = ret.container();

        for (const htd::Hyperedge & edge : hyperedges())
        {
            if (htd::equal(edge.begin(), edge.end(), elements.begin(), elements.end()))
            {
                result.emplace_back(edge.id());
            }
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

bool htd::Tree::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    bool ret = false;
    
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(neighbor))

    const auto & node = *(implementation_->nodes_.at(vertex));

    const auto & children = node.children;

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        if (node.parent == neighbor)
        {
            ret = true;
        }
    }

    if (!ret)
    {
        for (auto it = children.begin(); it != children.end();)
        {
            if (*it == neighbor)
            {
                ret = true;

                it = children.end();
            }
            else
            {
                it++;
            }
        }
    }
    
    return ret;
}

bool htd::Tree::isConnected(void) const
{
    return true;
}

bool htd::Tree::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isVertex(vertex1) && isVertex(vertex2);
}

std::size_t htd::Tree::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    HTD_ASSERT(isVertex(vertex))

    const auto & node = *(implementation_->nodes_.at(vertex));

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        ret++;
    }

    return ret + node.children.size();
}

htd::ConstCollection<htd::vertex_t> htd::Tree::neighbors(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::VectorAdapter<htd::vertex_t> ret;

    copyNeighborsTo(vertex, ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Tree::copyNeighborsTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t size = target.size();

    const auto & node = *(implementation_->nodes_.at(vertex));

    const auto & children = node.children;

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        target.emplace_back(node.parent);
    }

    target.insert(target.end(), children.begin(), children.end());

    std::sort(target.begin() + size, target.end());
}

htd::vertex_t htd::Tree::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const htd::ConstCollection<htd::vertex_t> & currentNeighbors = neighbors(vertex);

    HTD_ASSERT(index < currentNeighbors.size())

    return currentNeighbors[index];
}

htd::ConstCollection<htd::vertex_t> htd::Tree::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->vertices_);
}

const std::vector<htd::vertex_t> & htd::Tree::vertexVector(void) const
{
    return implementation_->vertices_;
}

void htd::Tree::copyVerticesTo(std::vector<htd::vertex_t> & target) const
{
    target.insert(target.end(),
                  implementation_->vertices_.begin(),
                  implementation_->vertices_.end());
}

htd::vertex_t htd::Tree::vertexAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->vertices_.size())

    return implementation_->vertices_[index];
}

std::size_t htd::Tree::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    if (implementation_->size_ == 1)
    {
        ret = 1;
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::isolatedVertices(void) const
{
    if (implementation_->size_ == 1)
    {
        htd::VectorAdapter<htd::vertex_t> result;

        result.container().emplace_back(implementation_->root_);

        return htd::ConstCollection<htd::vertex_t>(result.begin(), result.end());
    }

    return htd::ConstCollection<htd::vertex_t>();
}

htd::vertex_t htd::Tree::isolatedVertexAtPosition(htd::index_t index) const
{
    HTD_UNUSED(index)

    HTD_ASSERT(implementation_->size_ == 1 && index == 0)

    return implementation_->root_;
}

bool htd::Tree::isIsolatedVertex(htd::vertex_t vertex) const
{
    return implementation_->size_ == 1 && vertex == implementation_->root_;
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>(static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(implementation_->edges_->begin())),
                                                static_cast<htd::ConstIteratorBase<htd::Hyperedge> *>(new htd::ConstPointerIteratorWrapper<std::deque<htd::Hyperedge *>::const_iterator, htd::Hyperedge>(implementation_->edges_->end())));
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(htd::vertex_t vertex) const
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

const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t edgeId) const
{
    auto it = htd::hyperedgePointerPosition(implementation_->edges_->begin(), implementation_->edges_->end(), edgeId);

    if (it == implementation_->edges_->end())
    {
        throw std::logic_error("const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t) const");
    }

    return **it;
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->edges_->size())

    return *(implementation_->edges_->at(index));
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
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

    throw std::out_of_range("const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
}

htd::FilteredHyperedgeCollection htd::Tree::hyperedgesAtPositions(const std::vector<htd::index_t> & indices) const
{
    #ifndef NDEBUG
    for (htd::index_t index : indices)
    {
        HTD_ASSERT(index < implementation_->edges_->size())
    }
    #endif

    return htd::FilteredHyperedgeCollection(new htd::HyperedgePointerDeque(implementation_->edges_), indices);
}

htd::FilteredHyperedgeCollection htd::Tree::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    #ifndef NDEBUG
    for (htd::index_t index : indices)
    {
        HTD_ASSERT(index < implementation_->edges_->size())
    }
    #endif

    return htd::FilteredHyperedgeCollection(new htd::HyperedgePointerDeque(implementation_->edges_), std::move(indices));
}

htd::vertex_t htd::Tree::root(void) const
{
    HTD_ASSERT(implementation_->root_ != htd::Vertex::UNKNOWN)

    return implementation_->root_;
}

bool htd::Tree::isRoot(htd::vertex_t vertex) const
{
    return implementation_->root_ == vertex;
}

htd::vertex_t htd::Tree::parent(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t ret = implementation_->nodes_.at(vertex)->parent;

    HTD_ASSERT(ret != htd::Vertex::UNKNOWN)
    
    return ret;
}

bool htd::Tree::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(parent))

    return implementation_->nodes_.at(vertex)->parent == parent;
}

std::size_t htd::Tree::childCount(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->nodes_.at(vertex)->children.size();
}

htd::ConstCollection<htd::vertex_t> htd::Tree::children(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return htd::ConstCollection<htd::vertex_t>::getInstance(implementation_->nodes_.at(vertex)->children);
}

void htd::Tree::copyChildrenTo(htd::vertex_t vertex, std::vector<htd::vertex_t> & target) const
{
    HTD_ASSERT(isVertex(vertex))

    const std::vector<htd::vertex_t> & childCollection = implementation_->nodes_.at(vertex)->children;

    target.insert(target.end(), childCollection.begin(), childCollection.end());
}

htd::vertex_t htd::Tree::childAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    HTD_ASSERT(isVertex(vertex))

    const auto & children = implementation_->nodes_.at(vertex)->children;

    HTD_ASSERT(index < children.size())

    return children[index];
}

bool htd::Tree::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(child))

    const auto & children = implementation_->nodes_.at(vertex)->children;

    return std::find(children.begin(), children.end(), child) != children.end();
}

std::size_t htd::Tree::height(void) const
{
    return height(implementation_->root_);
}

std::size_t htd::Tree::height(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    std::size_t ret = 0;

    htd::PreOrderTreeTraversal traversal;

    traversal.traverse(*this, [&](htd::vertex_t currentVertex, htd::vertex_t parent, std::size_t distanceToVertex)
    {
        HTD_UNUSED(currentVertex)
        HTD_UNUSED(parent)

        if (distanceToVertex > ret)
        {
            ret = distanceToVertex;
        }
    }, vertex);

    return ret;
}

std::size_t htd::Tree::depth(htd::vertex_t vertex) const
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

htd::vertex_t htd::Tree::nextVertex(void) const
{
    return implementation_->next_vertex_;
}

htd::id_t htd::Tree::nextEdgeId(void) const
{
    return implementation_->next_edge_;
}

void htd::Tree::removeVertex(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    Implementation::Node & node = *(implementation_->nodes_.at(vertex));

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

    const auto & children = node.children;

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        Implementation::Node & parentNode = *(implementation_->nodes_.at(node.parent));

        auto & siblings = parentNode.children;

        switch (children.size())
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                htd::vertex_t child = children[0];

                Implementation::Node & childNode = *(implementation_->nodes_.at(child));

                childNode.parent = node.parent;

                auto position = std::lower_bound(siblings.begin(), siblings.end(), child);

                if (position == siblings.end() || *position != child)
                {
                    siblings.insert(position, child);
                }

                if (node.parent < child)
                {
                    implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, node.parent, child));
                }
                else
                {
                    implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, child, node.parent));
                }

                childNode.edges.emplace_back(implementation_->next_edge_);

                parentNode.edges.emplace_back(implementation_->next_edge_);

                ++implementation_->next_edge_;

                break;
            }
            default:
            {
                for (htd::vertex_t child : children)
                {
                    Implementation::Node & childNode = *(implementation_->nodes_.at(child));

                    childNode.parent = node.parent;

                    auto position = std::lower_bound(siblings.begin(), siblings.end(), child);

                    if (position == siblings.end() || *position != child)
                    {
                        siblings.insert(position, child);
                    }

                    if (node.parent < child)
                    {
                        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, node.parent, child));
                    }
                    else
                    {
                        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, child, node.parent));
                    }

                    childNode.edges.emplace_back(implementation_->next_edge_);

                    parentNode.edges.emplace_back(implementation_->next_edge_);

                    implementation_->next_edge_++;
                }

                break;
            }
        }

        implementation_->deleteNode(implementation_->nodes_.at(vertex));
    }
    else
    {
        switch (children.size())
        {
            case 0:
            {
                implementation_->root_ = htd::Vertex::UNKNOWN;

                implementation_->size_ = 0;

                implementation_->nodes_.clear();
                implementation_->edges_->clear();

                implementation_->vertices_.clear();

                break;
            }
            case 1:
            {
                implementation_->root_ = children[0];

                implementation_->nodes_.at(implementation_->root_)->parent = htd::Vertex::UNKNOWN;

                implementation_->deleteNode(implementation_->nodes_.at(vertex));

                break;
            }
            default:
            {
                implementation_->root_ = children[0];

                Implementation::Node & rootNode = *(implementation_->nodes_.at(implementation_->root_));

                rootNode.parent = htd::Vertex::UNKNOWN;

                std::vector<htd::vertex_t> & newRootChildren = rootNode.children;

                for (auto it = children.begin() + 1; it != children.end(); ++it)
                {
                    htd::vertex_t child = *it;

                    Implementation::Node & childNode = *(implementation_->nodes_.at(child));

                    childNode.parent = implementation_->root_;

                    auto position = std::lower_bound(newRootChildren.begin(), newRootChildren.end(), child);

                    if (position == newRootChildren.end() || *position != child)
                    {
                        newRootChildren.insert(position, child);
                    }

                    if (implementation_->root_ < child)
                    {
                        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, implementation_->root_, child));
                    }
                    else
                    {
                        implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, child, implementation_->root_));
                    }

                    childNode.edges.emplace_back(implementation_->next_edge_);

                    rootNode.edges.emplace_back(implementation_->next_edge_);

                    implementation_->next_edge_++;
                }

                implementation_->deleteNode(implementation_->nodes_.at(vertex));

                break;
            }
        }
    }
}

void htd::Tree::removeSubtree(htd::vertex_t subtreeRoot)
{
    HTD_ASSERT(isVertex(subtreeRoot))

    htd::PostOrderTreeTraversal treeTraversal;

    treeTraversal.traverse(*this, [&](htd::vertex_t vertex, htd::vertex_t parent, std::size_t distanceToSubtreeRoot)
    {
        HTD_UNUSED(parent)
        HTD_UNUSED(distanceToSubtreeRoot)

        removeVertex(vertex);
    }, subtreeRoot);
}

htd::vertex_t htd::Tree::insertRoot(void)
{
    if (implementation_->root_ == htd::Vertex::UNKNOWN)
    {
        implementation_->root_ = htd::Vertex::FIRST;

        implementation_->next_edge_ = htd::Id::FIRST;

        implementation_->next_vertex_ = implementation_->root_ + 1;

        implementation_->nodes_.clear();
        implementation_->nodes_.emplace(implementation_->root_, new Implementation::Node(implementation_->root_, htd::Vertex::UNKNOWN));

        implementation_->vertices_.emplace_back(implementation_->root_);

        implementation_->size_ = 1;
    }
    
    return implementation_->root_;
}

void htd::Tree::makeRoot(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    if (vertex != implementation_->root_)
    {
        implementation_->root_ = vertex;

        htd::vertex_t lastVertex = htd::Vertex::UNKNOWN;
        htd::vertex_t nextVertex = htd::Vertex::UNKNOWN;

        while (vertex != htd::Vertex::UNKNOWN)
        {
            Implementation::Node & node = *(implementation_->nodes_[vertex]);

            nextVertex = node.parent;

            std::vector<htd::vertex_t> & currentChildren = node.children;

            if (lastVertex != htd::Vertex::UNKNOWN)
            {
                currentChildren.erase(std::lower_bound(currentChildren.begin(), currentChildren.end(), lastVertex));
            }

            if (nextVertex != htd::Vertex::UNKNOWN)
            {
                currentChildren.insert(std::lower_bound(currentChildren.begin(), currentChildren.end(), nextVertex), nextVertex);
            }

            node.parent = lastVertex;

            lastVertex = vertex;

            vertex = nextVertex;
        }
    }
}

htd::vertex_t htd::Tree::addChild(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    Implementation::Node & node = *(implementation_->nodes_.at(vertex));

    ret = implementation_->next_vertex_;

    node.children.emplace_back(ret);

    Implementation::Node * newNode = new Implementation::Node(ret, vertex);

    implementation_->nodes_.emplace(ret, newNode);

    implementation_->vertices_.emplace_back(ret);

    implementation_->next_vertex_++;

    implementation_->size_++;

    implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, vertex, ret));

    node.edges.push_back(implementation_->next_edge_);

    newNode->edges.push_back(implementation_->next_edge_);

    implementation_->next_edge_++;

    return ret;
}

void htd::Tree::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(child))

    auto & node = *(implementation_->nodes_.at(vertex));

    auto & children = node.children;

    if (!children.empty())
    {
        auto position = children.end();

        for (auto it = children.begin(); position == children.end() && it != children.end(); it++)
        {
            if (*it == child)
            {
                position = it;
            }
        }

        if (position != children.end())
        {
            removeVertex(child);
        }
    }
}

htd::vertex_t htd::Tree::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    HTD_ASSERT(isVertex(vertex))

    if (isRoot(vertex))
    {
        auto & node = implementation_->nodes_.at(vertex);

        ret = implementation_->next_vertex_;

        node->parent = ret;

        Implementation::Node * newRootNode = new Implementation::Node(ret, htd::Vertex::UNKNOWN);

        newRootNode->children.emplace_back(vertex);

        implementation_->nodes_.emplace(ret, newRootNode);

        implementation_->vertices_.emplace_back(ret);

        implementation_->next_vertex_++;

        implementation_->size_++;

        implementation_->root_ = ret;
    }
    else
    {
        htd::vertex_t parentVertex = parent(vertex);

        Implementation::Node & parentNode = *(implementation_->nodes_.at(parentVertex));
        Implementation::Node & selectedNode = *(implementation_->nodes_.at(vertex));

        htd::id_t oldHyperedge = htd::Id::UNKNOWN;

        auto it = selectedNode.edges.begin();

        while (it != selectedNode.edges.end())
        {
            auto position = htd::hyperedgePointerPosition(implementation_->edges_->begin(), implementation_->edges_->end(), *it);

            HTD_ASSERT(position != implementation_->edges_->end())

            if ((*position)->contains(parentVertex))
            {
                oldHyperedge = (*position)->id();

                delete *position;

                implementation_->edges_->erase(position);

                it = selectedNode.edges.end();
            }
            else
            {
                ++it;
            }
        }

        parentNode.edges.erase(std::lower_bound(parentNode.edges.begin(), parentNode.edges.end(), oldHyperedge));
        selectedNode.edges.erase(std::lower_bound(selectedNode.edges.begin(), selectedNode.edges.end(), oldHyperedge));

        ret = htd::Tree::addChild(parentVertex);

        auto & intermediateNode = *(implementation_->nodes_.at(ret));

        intermediateNode.parent = parentVertex;

        intermediateNode.children.emplace_back(vertex);

        auto position = std::find(parentNode.children.begin(), parentNode.children.end(), vertex);

        if (position != parentNode.children.end())
        {
            parentNode.children.erase(position);
        }

        selectedNode.parent = ret;
    }

    implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, vertex, ret));

    implementation_->nodes_.at(vertex)->edges.push_back(implementation_->next_edge_);
    implementation_->nodes_.at(ret)->edges.push_back(implementation_->next_edge_);

    implementation_->next_edge_++;

    return ret;
}

void htd::Tree::setParent(htd::vertex_t vertex, htd::vertex_t newParent)
{
    HTD_ASSERT(isVertex(vertex))
    HTD_ASSERT(isVertex(newParent))
    HTD_ASSERT(vertex != newParent)

    auto & node = *(implementation_->nodes_.at(vertex));

    htd::vertex_t oldParent = node.parent;

    if (oldParent != newParent)
    {
        auto & newParentNode = *(implementation_->nodes_.at(newParent));

        if (oldParent != htd::Vertex::UNKNOWN)
        {
            auto & oldParentNode = *(implementation_->nodes_.at(oldParent));

            oldParentNode.children.erase(std::find(oldParentNode.children.begin(), oldParentNode.children.end(), vertex));

            htd::id_t oldHyperedge = htd::Id::UNKNOWN;

            auto it = oldParentNode.edges.begin();

            while (it != oldParentNode.edges.end())
            {
                auto position = htd::hyperedgePointerPosition(implementation_->edges_->begin(), implementation_->edges_->end(), *it);

                HTD_ASSERT(position != implementation_->edges_->end())

                if ((*position)->contains(vertex))
                {
                    oldHyperedge = (*position)->id();

                    delete *position;

                    implementation_->edges_->erase(position);

                    it = oldParentNode.edges.end();
                }
                else
                {
                    ++it;
                }
            }

            node.edges.erase(std::lower_bound(node.edges.begin(), node.edges.end(), oldHyperedge));
            oldParentNode.edges.erase(std::lower_bound(oldParentNode.edges.begin(), oldParentNode.edges.end(), oldHyperedge));
        }
        else
        {
            htd::vertex_t relevantVertex = newParent;

            while (implementation_->nodes_.at(relevantVertex)->parent != vertex)
            {
                relevantVertex = implementation_->nodes_.at(relevantVertex)->parent;
            }

            std::cout << "RELEVANT: " << relevantVertex << std::endl;

            implementation_->root_ = relevantVertex;

            auto & relevantNode = *(implementation_->nodes_.at(relevantVertex));

            relevantNode.parent = htd::Vertex::UNKNOWN;

            node.children.erase(std::find(node.children.begin(), node.children.end(), relevantVertex));

            htd::id_t oldHyperedge = htd::Id::UNKNOWN;

            auto it = relevantNode.edges.begin();

            while (it != relevantNode.edges.end())
            {
                auto position = htd::hyperedgePointerPosition(implementation_->edges_->begin(), implementation_->edges_->end(), *it);

                HTD_ASSERT(position != implementation_->edges_->end())

                if ((*position)->contains(vertex))
                {
                    oldHyperedge = (*position)->id();

                    delete *position;

                    implementation_->edges_->erase(position);

                    it = relevantNode.edges.end();
                }
                else
                {
                    ++it;
                }
            }

            node.edges.erase(std::lower_bound(node.edges.begin(), node.edges.end(), oldHyperedge));
            relevantNode.edges.erase(std::lower_bound(relevantNode.edges.begin(), relevantNode.edges.end(), oldHyperedge));
        }

        auto position = std::lower_bound(newParentNode.children.begin(), newParentNode.children.end(), vertex);

        newParentNode.children.insert(position, vertex);

        newParentNode.edges.emplace_back(implementation_->next_edge_);

        node.edges.emplace_back(implementation_->next_edge_);

        node.parent = newParent;

        if (vertex < newParent)
        {
            implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, vertex, newParent));
        }
        else
        {
            implementation_->edges_->push_back(new htd::Hyperedge(implementation_->next_edge_, newParent, vertex));
        }

        implementation_->next_edge_++;
    }
}

std::size_t htd::Tree::leafCount(void) const HTD_NOEXCEPT
{
    std::size_t ret = 0;

    for (const auto & node : implementation_->nodes_)
    {
        if (node.second->children.empty())
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::leaves(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    copyLeavesTo(ret.container());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Tree::copyLeavesTo(std::vector<htd::vertex_t> & target) const
{
    for (const auto & node : implementation_->nodes_)
    {
        if (node.second->children.empty())
        {
            target.emplace_back(node.first);
        }
    }

    std::sort(target.begin(), target.end());
}

htd::vertex_t htd::Tree::leafAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & leafNodeCollection = leaves();

    HTD_ASSERT(index < leafNodeCollection.size())

    htd::ConstIterator<htd::vertex_t> it = leafNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::Tree::isLeaf(htd::vertex_t vertex) const
{
    HTD_ASSERT(isVertex(vertex))

    return implementation_->nodes_.at(vertex)->children.empty();
}

void htd::Tree::swapWithParent(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    Implementation::Node & node = *(implementation_->nodes_.at(vertex));

    htd::vertex_t parent = node.parent;

    HTD_ASSERT(parent != htd::Vertex::UNKNOWN)

    Implementation::Node & parentNode = *(implementation_->nodes_.at(parent));

    node.parent = parentNode.parent;

    node.children.insert(std::lower_bound(node.children.begin(), node.children.end(), parent), parent);

    parentNode.parent = vertex;

    parentNode.children.erase(std::lower_bound(parentNode.children.begin(), parentNode.children.end(), vertex));

    if (node.parent == htd::Vertex::UNKNOWN)
    {
        implementation_->root_ = vertex;
    }
    else
    {
        htd::vertex_t grandParent = node.parent;

        Implementation::Node & grandParentNode = *(implementation_->nodes_.at(grandParent));

        implementation_->updateEdgesAfterSwapWithParent(node, parentNode, grandParentNode);

        grandParentNode.children.erase(std::lower_bound(grandParentNode.children.begin(), grandParentNode.children.end(), parent));

        grandParentNode.children.insert(std::lower_bound(grandParentNode.children.begin(), grandParentNode.children.end(), vertex), vertex);
    }
}

void htd::Tree::Implementation::deleteNode(Node * node)
{
    HTD_ASSERT(node != nullptr)

    auto & parent = node->parent;

    htd::vertex_t vertex = node->id;

    if (parent != htd::Vertex::UNKNOWN)
    {
        auto & children = nodes_.at(parent)->children;

        children.erase(std::lower_bound(children.begin(), children.end(), vertex));
    }

    vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), vertex));

    nodes_.erase(vertex);

    delete node;

    size_--;
}

const htd::LibraryInstance * htd::Tree::managementInstance(void) const HTD_NOEXCEPT
{
    return implementation_->managementInstance_;
}

void htd::Tree::setManagementInstance(const htd::LibraryInstance * const manager)
{
    HTD_ASSERT(manager != nullptr)

    implementation_->managementInstance_ = manager;
}

htd::Tree * htd::Tree::clone(void) const
{
    return new htd::Tree(*this);
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
htd::ITree * htd::Tree::cloneTree(void) const
{
    return clone();
}

htd::IGraph * htd::Tree::cloneGraph(void) const
{
    return clone();
}

htd::IMultiGraph * htd::Tree::cloneMultiGraph(void) const
{
    return clone();
}

htd::IHypergraph * htd::Tree::cloneHypergraph(void) const
{
    return clone();
}

htd::IGraphStructure * htd::Tree::cloneGraphStructure(void) const
{
    return clone();
}

htd::IMultiHypergraph * htd::Tree::cloneMultiHypergraph(void) const
{
    return clone();
}

htd::IMutableTree * htd::Tree::cloneMutableTree(void) const
{
    return clone();
}
#endif

htd::Tree & htd::Tree::operator=(const htd::Tree & original)
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

        implementation_->vertices_.clear();

        std::copy(original.implementation_->vertices_.begin(), original.implementation_->vertices_.end(), std::back_inserter(implementation_->vertices_));

        if (original.implementation_->next_vertex_ >= htd::Vertex::FIRST)
        {
            implementation_->next_vertex_ = original.implementation_->next_vertex_;
        }
        else
        {
            implementation_->next_vertex_ = htd::Vertex::FIRST;
        }

        for (htd::Hyperedge * edge : *(original.implementation_->edges_))
        {
            implementation_->edges_->push_back(new htd::Hyperedge(*edge));
        }

        implementation_->next_edge_ = original.implementation_->next_edge_;
    }

    return *this;
}

htd::Tree & htd::Tree::operator=(const htd::ITree & original)
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

                const htd::ConstCollection<htd::vertex_t> & childCollection = original.children(vertex);

                std::copy(childCollection.begin(), childCollection.end(), std::back_inserter(newNode->children));

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

            const htd::ConstCollection<htd::Hyperedge> & originalEdges = original.hyperedges();

            for (auto it = originalEdges.begin(); it != originalEdges.end(); ++it)
            {
                implementation_->edges_->push_back(new htd::Hyperedge(*it));
            }

            if (!implementation_->edges_->empty())
            {
                implementation_->next_edge_ = (*(implementation_->edges_->rbegin()))->id() + 1;
            }
        }
    }

    return *this;
}

#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
void htd::Tree::assign(const htd::ITree & original)
{
    *this = original;
}
#endif

void htd::Tree::Implementation::updateEdgesAfterSwapWithParent(Node & node, Node & parentNode, Node & grandParentNode)
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

#endif /* HTD_HTD_TREE_CPP */
