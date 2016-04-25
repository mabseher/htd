/* 
 * File:   Tree.cpp
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

#ifndef HTD_HTD_TREE_CPP
#define	HTD_HTD_TREE_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/Tree.hpp>
#include <htd/VectorAdapter.hpp>
#include <htd/PreOrderTreeTraversal.hpp>
#include <htd/PostOrderTreeTraversal.hpp>

#include <algorithm>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

htd::Tree::Tree(void) : size_(0), root_(htd::Vertex::UNKNOWN), next_edge_(htd::Id::FIRST), next_vertex_(htd::Vertex::FIRST), nodes_(), edges_(std::make_shared<htd::hyperedge_container>()), signalHandlerId_(htd::Library::instance().registerSignalHandler(std::bind(&htd::Tree::handleSignal, this, std::placeholders::_1)))
{

}

htd::Tree::Tree(const htd::Tree & original) : size_(original.size_), root_(original.root_), next_edge_(original.next_edge_), next_vertex_(original.next_vertex_ >= htd::Vertex::FIRST ? original.next_vertex_ : htd::Vertex::FIRST), vertices_(original.vertices_), nodes_(), edges_(std::make_shared<htd::hyperedge_container>(*(original.edges_))), signalHandlerId_(htd::Library::instance().registerSignalHandler(std::bind(&htd::Tree::handleSignal, this, std::placeholders::_1)))
{
    nodes_.reserve(original.nodes_.size());
    
    for (const auto & node : original.nodes_)
    {
        nodes_.insert(std::make_pair(node.first, std::unique_ptr<htd::Tree::Node>(new htd::Tree::Node(*(node.second)))));
    }
}

htd::Tree::Tree(const htd::ITree & original) : size_(0), root_(htd::Vertex::UNKNOWN), next_edge_(htd::Vertex::FIRST), next_vertex_(htd::Vertex::FIRST), nodes_(), edges_(std::make_shared<htd::hyperedge_container>()), signalHandlerId_(htd::Library::instance().registerSignalHandler(std::bind(&htd::Tree::handleSignal, this, std::placeholders::_1)))
{
    *this = original;
}

htd::Tree::~Tree()
{
    htd::Library::instance().unregisterSignalHandler(signalHandlerId_);
}

std::size_t htd::Tree::vertexCount(void) const
{
    return size_;
}

std::size_t htd::Tree::vertexCount(htd::vertex_t subtreeRoot) const
{
    if (!isVertex(subtreeRoot))
    {
        throw std::logic_error("std::size_t htd::Tree::vertexCount(htd::vertex_t) const");
    }

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
    return edges_->size();
}

std::size_t htd::Tree::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = neighborCount(vertex);
    }
    else
    {
        throw std::out_of_range("std::size_t htd::Tree::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::Tree::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && nodes_.count(vertex) > 0;
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
            result.push_back(edge.id());
        }
    }

    return htd::ConstCollection<htd::id_t>::getInstance(ret);
}

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(const std::vector<htd::vertex_t> & elements) const
{
    return associatedEdgeIds(htd::ConstCollection<htd::vertex_t>::getInstance(elements));
}

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(const htd::Collection<htd::vertex_t> & elements) const
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

htd::ConstCollection<htd::id_t> htd::Tree::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
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

htd::vertex_t htd::Tree::vertexAtPosition(htd::index_t index) const
{
    if (index >= vertices_.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::vertexAtPosition(htd::index_t) const");
    }

    return vertices_[index];
}

bool htd::Tree::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = false;
    
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        const auto & node = *(nodes_.at(vertex1));

        const auto & children = node.children;
            
        if (node.parent != htd::Vertex::UNKNOWN)
        {
            if (node.parent == vertex2)
            {
                ret = true;
            }
        }

        if (!ret)
        {
            for (auto it = children.begin(); it != children.end();)
            {
                if (*it == vertex2)
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
    
    if (isVertex(vertex))
    {
        const auto & node = *(nodes_.at(vertex));

        if (node.parent != htd::Vertex::UNKNOWN)
        {
            ret++;
        }

        ret += node.children.size();
    }
    
    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::neighbors(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Tree::neighbors(htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const auto & node = *(nodes_.at(vertex));

    const auto & children = node.children;

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        result.push_back(node.parent);
    }

    std::copy(children.begin(), children.end(), std::back_inserter(result));

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

void htd::Tree::copyNeighborsTo(std::vector<htd::vertex_t> & target, htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::Tree::copyNeighborsTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }

    std::size_t size = target.size();

    const auto & node = *(nodes_.at(vertex));

    const auto & children = node.children;

    if (node.parent != htd::Vertex::UNKNOWN)
    {
        target.push_back(node.parent);
    }

    std::copy(children.begin(), children.end(), std::back_inserter(target));

    std::sort(target.begin() + size, target.end());
}

htd::vertex_t htd::Tree::neighborAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::Tree::neighborAtPosition(htd::vertex_t, htd::index_t) const");
    }

    const htd::ConstCollection<htd::vertex_t> & currentNeighbors = neighbors(vertex);

    if (index >= currentNeighbors.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::neighborAtPosition(htd::vertex_t, htd::index_t) const");
    }

    return currentNeighbors[index];
}

htd::ConstCollection<htd::vertex_t> htd::Tree::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(vertices_);
}

std::size_t htd::Tree::isolatedVertexCount(void) const
{
    std::size_t ret = 0;

    if (size_ == 1)
    {
        ret = 1;
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::isolatedVertices(void) const
{
    if (size_ == 1)
    {
        htd::VectorAdapter<htd::vertex_t> result;

        result.container().push_back(root_);

        return htd::ConstCollection<htd::vertex_t>(result.begin(), result.end());
    }

    return htd::ConstCollection<htd::vertex_t>();
}

htd::vertex_t htd::Tree::isolatedVertexAtPosition(htd::index_t index) const
{
    HTD_UNUSED(index)

    if (size_ != 1 || index > 0)
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::isolatedVertexAtPosition(htd::index_t index) const");
    }

    return root_;
}

bool htd::Tree::isIsolatedVertex(htd::vertex_t vertex) const
{
    return size_ == 1 && vertex == root_;
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(void) const
{
    return htd::ConstCollection<htd::Hyperedge>::getInstance(*edges_);
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    for (auto & edge : *edges_)
    {
        if (edge.containsVertex(vertex))
        {
            result.push_back(edge);
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t edgeId) const
{
    bool found = false;

    auto position = edges_->begin();

    for (auto it = edges_->begin(); !found && it != edges_->end(); ++it)
    {
        if (it->id() == edgeId)
        {
            position = it;

            found = true;
        }
    }

    if (!found)
    {
        throw std::logic_error("const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t) const");
    }

    return *position;
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index) const
{
    if (index >= edges_->size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t) const");
    }

    return edges_->at(index);
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    for (auto it = edges_->begin(); it != edges_->end(); ++it)
    {
        const htd::Hyperedge & hyperedge = *it;

        if (hyperedge.containsVertex(vertex))
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
    for (htd::index_t index : indices)
    {
        if (index >= edges_->size())
        {
            throw std::logic_error("htd::FilteredHyperedgeCollection htd::Tree::hyperedgesAtPositions(const std::vector<htd::index_t> &) const");
        }
    }

    return htd::FilteredHyperedgeCollection(edges_, indices);
}

htd::vertex_t htd::Tree::root(void) const
{
    if (root_ == htd::Vertex::UNKNOWN)
    {
        throw std::logic_error("htd::vertex_t htd::Tree::root(void) const");
    }

    return root_;
}

bool htd::Tree::isRoot(htd::vertex_t vertex) const
{
    return root_ == vertex;
}

htd::vertex_t htd::Tree::parent(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::Tree::parent(htd::vertex_t) const");
    }

    htd::vertex_t ret = nodes_.at(vertex)->parent;

    if (ret == htd::Vertex::UNKNOWN)
    {
        throw std::logic_error("htd::vertex_t htd::Tree::parent(htd::vertex_t) const");
    }
    
    return ret;
}

bool htd::Tree::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    if (!isVertex(vertex) || !isVertex(parent))
    {
        throw std::logic_error("bool htd::Tree::isParent(htd::vertex_t, htd::vertex_t) const");
    }

    return nodes_.at(vertex)->parent == parent;
}

std::size_t htd::Tree::childCount(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("std::size_t htd::Tree::childCount(htd::vertex_t) const");
    }

    return nodes_.at(vertex)->children.size();
}

htd::ConstCollection<htd::vertex_t> htd::Tree::children(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Tree::children(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(nodes_.at(vertex)->children);
}

htd::vertex_t htd::Tree::childAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (!isVertex(vertex))
    {
        throw std::logic_error("bool htd::Tree::childAtPosition(htd::vertex_t, htd::index_t) const");
    }

    const auto & node = *(nodes_.at(vertex));

    const auto & children = node.children;

    if (index < children.size())
    {
        ret = children[index];
    }
    else
    {
        throw std::out_of_range("bool htd::Tree::childAtPosition(htd::vertex_t, htd::index_t) const");
    }
    
    return ret;
}

bool htd::Tree::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    if (!isVertex(vertex) || !isVertex(child))
    {
        throw std::logic_error("bool htd::Tree::isChild(htd::vertex_t, htd::vertex_t) const");
    }

    const auto & children = nodes_.at(vertex)->children;

    return std::find(children.begin(), children.end(), child) != children.end();
}

void htd::Tree::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        auto & node = *(nodes_.at(vertex));

        const auto & children = node.children;

        if (node.parent != htd::Vertex::UNKNOWN)
        {
            auto & parent = nodes_.at(node.parent);

            auto & siblings = parent->children;

            switch (children.size())
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    htd::vertex_t child = children[0];

                    nodes_.at(child)->parent = node.parent;

                    auto position = std::lower_bound(siblings.begin(), siblings.end(), child);

                    if (position == siblings.end() || *position != child)
                    {
                        siblings.insert(position, child);
                    }

                    if (node.parent < child)
                    {
                        edges_->push_back(htd::Hyperedge(next_edge_, node.parent, child));
                    }
                    else
                    {
                        edges_->push_back(htd::Hyperedge(next_edge_, child, node.parent));
                    }

                    ++next_edge_;

                    break;
                }
                default:
                {
                    for (htd::vertex_t child : children)
                    {
                        nodes_.at(child)->parent = node.parent;

                        auto position = std::lower_bound(siblings.begin(), siblings.end(), child);

                        if (position == siblings.end() || *position != child)
                        {
                            siblings.insert(position, child);
                        }

                        if (node.parent < child)
                        {
                            edges_->push_back(htd::Hyperedge(next_edge_, node.parent, child));
                        }
                        else
                        {
                            edges_->push_back(htd::Hyperedge(next_edge_, child, node.parent));
                        }

                        ++next_edge_;
                    }

                    break;
                }
            }

            deleteNode(nodes_.at(vertex));
        }
        else
        {
            switch (children.size())
            {
                case 0:
                {
                    removeRoot();

                    break;
                }
                case 1:
                {
                    root_ = children[0];

                    nodes_.at(root_)->parent = htd::Vertex::UNKNOWN;

                    deleteNode(nodes_.at(vertex));

                    break;
                }
                default:
                {
                    root_ = children[0];

                    auto & newRootNode = *(nodes_.at(root_));

                    htd::vertex_container & newRootChildren = newRootNode.children;

                    newRootNode.parent = htd::Vertex::UNKNOWN;

                    for (auto it = children.begin() + 1; it != children.end(); ++it)
                    {
                        htd::vertex_t child = *it;

                        nodes_.at(child)->parent = root_;

                        auto position = std::lower_bound(newRootChildren.begin(), newRootChildren.end(), child);

                        if (position == newRootChildren.end() || *position != child)
                        {
                            newRootChildren.insert(position, child);
                        }

                        if (root_ < child)
                        {
                            edges_->push_back(htd::Hyperedge(next_edge_, root_, child));
                        }
                        else
                        {
                            edges_->push_back(htd::Hyperedge(next_edge_, child, root_));
                        }
                    }

                    deleteNode(nodes_.at(vertex));

                    break;
                }
            }
        }

        edges_->erase(std::remove_if(edges_->begin(), edges_->end(), [&](const htd::Hyperedge & edge) { return edge.containsVertex(vertex); }), edges_->end());
    }
}

void htd::Tree::removeSubtree(htd::vertex_t subtreeRoot)
{
    if (!isVertex(subtreeRoot))
    {
        throw std::logic_error("void htd::Tree::removeSubtree(htd::vertex_t)");
    }

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
    if (root_ == htd::Vertex::UNKNOWN)
    {
        root_ = htd::Vertex::FIRST;

        next_edge_ = htd::Id::FIRST;

        next_vertex_ = root_ + 1;

        nodes_.clear();
        nodes_.insert(std::make_pair(root_, std::unique_ptr<htd::Tree::Node>(new htd::Tree::Node(root_, htd::Vertex::UNKNOWN))));

        vertices_.push_back(root_);

        size_ = 1;
    }
    
    return root_;
}

void htd::Tree::removeRoot(void)
{
    root_ = htd::Vertex::UNKNOWN;

    size_ = 0;

    nodes_.clear();

    edges_->clear();

    vertices_.clear();
}

htd::vertex_t htd::Tree::addChild(htd::vertex_t vertex)
{
    HTD_ASSERT(isVertex(vertex))

    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    auto & node = nodes_.at(vertex);

    ret = next_vertex_;

    node->children.push_back(ret);

    nodes_.insert(std::make_pair(ret, std::unique_ptr<htd::Tree::Node>(new htd::Tree::Node(ret, vertex))));

    vertices_.push_back(ret);

    ++next_vertex_;

    size_++;

    edges_->push_back(htd::Hyperedge(next_edge_, vertex, ret));

    ++next_edge_;
    
    return ret;
}

void htd::Tree::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    if (isVertex(vertex))
    {
        auto & node = *(nodes_.at(vertex));

        auto & children = node.children;

        if (children.size() > 0)
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
}

htd::vertex_t htd::Tree::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (!isVertex(vertex))
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::addParent(htd::vertex_t)");
    }

    if (isRoot(vertex))
    {
        auto & node = nodes_.at(vertex);

        if (node != nullptr)
        {
            ret = next_vertex_;

            node->parent = ret;

            std::unique_ptr<htd::Tree::Node> newRootNode(new htd::Tree::Node(ret, htd::Vertex::UNKNOWN));

            newRootNode->children.push_back(vertex);

            nodes_.insert(std::make_pair(ret, std::move(newRootNode)));

            vertices_.push_back(ret);

            ++next_vertex_;

            size_++;

            root_ = ret;
        }
    }
    else
    {
        htd::vertex_t parentVertex = parent(vertex);

        ret = addChild(parentVertex);

        auto & parentNode = nodes_.at(parentVertex);
        auto & selectedNode = nodes_.at(vertex);
        auto & intermediateNode = nodes_.at(ret);

        if (parentNode != nullptr && selectedNode != nullptr && intermediateNode != nullptr)
        {
            intermediateNode->parent = parentVertex;

            intermediateNode->children.push_back(vertex);

            auto position = std::find(parentNode->children.begin(), parentNode->children.end(), vertex);

            if (position != parentNode->children.end())
            {
                parentNode->children.erase(position);
            }

            selectedNode->parent = ret;
        }
    }

    edges_->push_back(htd::Hyperedge(next_edge_, vertex, ret));

    ++next_edge_;

    return ret;
}

void htd::Tree::setParent(htd::vertex_t vertex, htd::vertex_t newParent)
{
    if (!isVertex(vertex) || !isVertex(newParent))
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::setParent(htd::vertex_t, htd::vertex_t)");
    }

    if (vertex == newParent)
    {
        throw std::logic_error("htd::vertex_t htd::Tree::setParent(htd::vertex_t, htd::vertex_t)");
    }

    auto & node = nodes_.at(vertex);

    htd::vertex_t oldParent = node->parent;

    if (oldParent != newParent)
    {
        auto & newParentNode = nodes_.at(newParent);

        if (isRoot(vertex))
        {
            root_ = newParent;
        }
        else
        {
            auto & parentNode = nodes_.at(node->parent);

            auto position = std::find(parentNode->children.begin(), parentNode->children.end(), vertex);

            if (position != parentNode->children.end())
            {
                parentNode->children.erase(position);
            }
        }

        auto position = std::lower_bound(newParentNode->children.begin(), newParentNode->children.end(), vertex);

        newParentNode->children.insert(position, vertex);

        node->parent = newParent;

        //TODO Optimize!
        edges_->erase(std::remove_if(edges_->begin(), edges_->end(), [&](const htd::Hyperedge & edge) { return edge.containsVertex(oldParent) && edge.containsVertex(vertex); }), edges_->end());

        if (vertex < newParent)
        {
            edges_->push_back(htd::Hyperedge(next_edge_, vertex, newParent));
        }
        else
        {
            edges_->push_back(htd::Hyperedge(next_edge_, newParent, vertex));
        }

        ++next_edge_;
    }
}

std::size_t htd::Tree::leafNodeCount(void) const
{
    std::size_t ret = 0;

    for (const auto & node : nodes_)
    {
        if (node.second->children.empty())
        {
            ret++;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::leafNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (const auto & node : nodes_)
    {
        if (node.second->children.empty())
        {
            result.push_back(node.first);
        }
    }

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::Tree::leafNodeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & leafNodeCollection = leafNodes();

    if (index >= leafNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::leafNodeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::vertex_t> it = leafNodeCollection.begin();

    std::advance(it, index);

    return *it;
}

bool htd::Tree::isLeafNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = nodes_.at(vertex)->children.empty();
    }
    else
    {
        throw std::out_of_range("bool htd::Tree::isLeafNode(htd::vertex_t) const");
    }

    return ret;
}

void htd::Tree::deleteNode(const std::unique_ptr<htd::Tree::Node> & node)
{
    if (node != nullptr)
    {
        auto & parent = node->parent;
        
        htd::id_t nodeIdentifier = node->id;
                
        if (parent != htd::Vertex::UNKNOWN)
        {
            auto & children = nodes_.at(parent)->children;

            if (children.size() > 0)
            {
                auto position = children.end();

                for (auto it = children.begin(); position == children.end() && it != children.end(); it++)
                {
                    if (*it == nodeIdentifier)
                    {
                        position = it;
                    }
                }

                if (position != children.end())
                {
                    size_--;

                    children.erase(position);

                    nodes_.erase(nodeIdentifier);

                    vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
                }
            }
        }
        else
        {
            size_--;

            nodes_.erase(nodeIdentifier);

            vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
        }
    }
}

htd::Tree * htd::Tree::clone(void) const
{
    return new Tree(*this);
}

htd::Tree & htd::Tree::operator=(const htd::Tree & original)
{
    if (this != &original)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeRoot();
        }

        nodes_.reserve(original.nodes_.size());

        for (const auto & node : original.nodes_)
        {
            nodes_.insert(std::make_pair(node.first, std::unique_ptr<htd::Tree::Node>(new htd::Tree::Node(*(node.second)))));
        }

        this->root_ = original.root_;

        this->size_ = original.size_;

        vertices_.clear();

        std::copy(original.vertices_.begin(), original.vertices_.end(), std::back_inserter(vertices_));

        if (original.next_vertex_ >= htd::Vertex::FIRST)
        {
            next_vertex_ = original.next_vertex_;
        }
        else
        {
            next_vertex_ = htd::Vertex::FIRST;
        }

        edges_ = std::make_shared<htd::hyperedge_container>(*(original.edges_));

        next_edge_ = original.next_edge_;
    }

    return *this;
}

htd::Tree & htd::Tree::operator=(const htd::ITree & original)
{
    if (this != &original)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeRoot();
        }

        size_ = original.vertexCount();

        if (size_ > 0)
        {
            root_ = original.root();

            htd::vertex_t maximumVertex = root_;

            const htd::ConstCollection<htd::vertex_t> & vertexCollection = original.vertices();

            std::copy(vertexCollection.begin(), vertexCollection.end(), std::back_inserter(vertices_));

            for (htd::vertex_t vertex : vertices_)
            {
                htd::Tree::Node * newNode = nullptr;

                if (original.isRoot(vertex))
                {
                    newNode = new htd::Tree::Node(vertex, htd::Vertex::UNKNOWN);
                }
                else
                {
                    newNode = new htd::Tree::Node(vertex, original.parent(vertex));
                }

                const htd::ConstCollection<htd::vertex_t> & childCollection = original.children(vertex);

                std::copy(childCollection.begin(), childCollection.end(), std::back_inserter(newNode->children));

                nodes_.insert(std::make_pair(vertex, std::unique_ptr<htd::Tree::Node>(newNode)));

                if (vertex > maximumVertex)
                {
                    maximumVertex = vertex;
                }
            }

            if (maximumVertex >= htd::Vertex::FIRST)
            {
                next_vertex_ = maximumVertex + 1;
            }
            else
            {
                next_vertex_ = htd::Vertex::FIRST;
            }

            const htd::ConstCollection<htd::Hyperedge> & originalEdges = original.hyperedges();

            edges_ = std::make_shared<htd::hyperedge_container>(originalEdges.begin(), originalEdges.end());

            if (!edges_->empty())
            {
                next_edge_ = edges_->rend()->id();
            }
        }
    }

    return *this;
}

void htd::Tree::handleSignal(int signal)
{
    HTD_UNUSED(signal);

    removeRoot();
}

#endif /* HTD_HTD_TREE_CPP */
