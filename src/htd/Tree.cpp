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

htd::Tree::Tree(void) : size_(0), root_(htd::Vertex::UNKNOWN), next_vertex_(htd::Vertex::FIRST), nodes_(), deletions_()
{

}

htd::Tree::Tree(const htd::Tree & original) : size_(original.size_), root_(original.root_), next_vertex_(htd::Vertex::FIRST), vertices_(original.vertices_), nodes_(), deletions_(original.deletions_)
{
    nodes_.reserve(original.nodes_.size());
    
    for (auto & node : original.nodes_)
    {
        if (node != nullptr)
        {
            nodes_.push_back(new htd::Tree::Node(*node));
        }
    }
}

//TODO Ensure correctness when htd::Vertex::FIRST does not match for this and original
htd::Tree::Tree(const htd::ITree & original) : size_(0), root_(original.root()), next_vertex_(htd::Vertex::FIRST), nodes_(), deletions_()
{
    htd::vertex_t maximumVertex = 0;

    for (auto & node : original.vertices())
    {
        if (node - htd::Vertex::FIRST > nodes_.size())
        {
            nodes_.insert(nodes_.end(), node - nodes_.size() - htd::Vertex::FIRST, nullptr);

            for (htd::index_t index = nodes_.size(); index < node; index++)
            {
                deletions_.insert(index);
            }
        }

        size_++;

        nodes_.push_back(new htd::Tree::Node(node, original.parent(node)));

        const htd::ConstCollection<htd::vertex_t> & childContainer = original.children(node);

        std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(nodes_[node - htd::Vertex::FIRST]->children));

        if (node > maximumVertex)
        {
            maximumVertex = node;
        }

        vertices_.push_back(node);
    }

    if (maximumVertex >= htd::Vertex::FIRST)
    {
        next_vertex_ = maximumVertex + 1;
    }
    else
    {
        next_vertex_ = htd::Vertex::FIRST;
    }
}

htd::Tree::~Tree()
{
    if (root_ != htd::Vertex::UNKNOWN)
    {
        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            if (*it != nullptr)
            {
                delete *it;

                *it = nullptr;
            }
        }

        nodes_.clear();
    }
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
    return size_ > 0 ? size_ - 1 : 0;
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
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && deletions_.find(vertex) == deletions_.end();
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
        auto & node = nodes_[vertex1 - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                if (node->parent == vertex2)
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
    }
    
    return ret;
}

bool htd::Tree::isConnected(void) const
{
    return edgeCount() > 0;
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
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                ret++;
            }

            ret += node->children.size();
        }
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

    auto & node = nodes_[vertex - htd::Vertex::FIRST];

    if (node != nullptr)
    {
        auto & children = node->children;

        if (node->parent != htd::Vertex::UNKNOWN)
        {
            result.push_back(node->parent);
        }

        for (auto child : children)
        {
            result.push_back(child);
        }
    }

    std::sort(result.begin(), result.end());

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::Tree::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::Tree::neighbor(htd::vertex_t, htd::index_t) const");
    }

    const htd::ConstCollection<htd::vertex_t> & currentNeighbors = neighbors(vertex);

    if (index >= currentNeighbors.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::neighbor(htd::vertex_t, htd::index_t) const");
    }

    return currentNeighbors[index];
}

htd::ConstCollection<htd::vertex_t> htd::Tree::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(vertices_);
}

std::size_t htd::Tree::isolatedVertexCount(void) const
{
    return 0;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::isolatedVertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>();
}

htd::vertex_t htd::Tree::isolatedVertex(htd::index_t index) const
{
    HTD_UNUSED(index)

    throw std::out_of_range("htd::vertex_t htd::Tree::isolatedVertex(htd::index_t index) const");
}

bool htd::Tree::isIsolatedVertex(htd::vertex_t vertex) const
{
    HTD_UNUSED(vertex)

    return false;
}

htd::ConstCollection<htd::edge_t> htd::Tree::edges(void) const
{
    htd::VectorAdapter<htd::edge_t> ret;

    auto & result = ret.container();

    for (auto & currentNode : nodes_)
    {
        if (currentNode != nullptr)
        {
            auto & children = currentNode->children;

            for (auto child : children)
            {
                htd::edge_t edge;

                if (currentNode->id < child)
                {
                    edge.first = currentNode->id;
                    edge.second = child;
                }
                else
                {
                    edge.first = child;
                    edge.second = currentNode->id;
                }

                result.push_back(edge);
            }
        }
    }

    return htd::ConstCollection<htd::edge_t>::getInstance(ret);
}

htd::ConstCollection<htd::edge_t> htd::Tree::edges(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::edge_t> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;

            if (node->parent != htd::Vertex::UNKNOWN)
            {
                htd::edge_t edge;

                if (node->parent < node->id)
                {
                    edge.first = node->parent;
                    edge.second = node->id;
                }
                else
                {
                    edge.first = node->id;
                    edge.second = node->parent;
                }

                result.push_back(edge);
            }

            for (auto child : children)
            {
                htd::edge_t edge;

                if (node->id < child)
                {
                    edge.first = node->id;
                    edge.second = child;
                }
                else
                {
                    edge.first = child;
                    edge.second = node->id;
                }

                result.push_back(edge);
            }
        }
    }
    else
    {
        throw std::logic_error("const htd::IConstCollection<htd::edge_t> htd::Tree::edges(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::edge_t>::getInstance(ret);
}

const htd::edge_t & htd::Tree::edgeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges();

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::Tree::edgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::edge_t & htd::Tree::edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::edge_t> & edgeCollection = edges(vertex);

    if (index >= edgeCollection.size())
    {
        throw std::out_of_range("const htd::edge_t & htd::Tree::edgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::edge_t> it = edgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(void) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    htd::id_t id = 0;

    for (auto & currentNode : nodes_)
    {
        if (currentNode != nullptr)
        {
            auto & children = currentNode->children;

            for (auto child : children)
            {
                htd::Hyperedge hyperedge(id);

                if (currentNode->id < child)
                {
                    hyperedge.push_back(currentNode->id);
                    hyperedge.push_back(child);
                }
                else
                {
                    hyperedge.push_back(child);
                    hyperedge.push_back(currentNode->id);
                }

                result.push_back(hyperedge);

                ++id;
            }
        }
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

htd::ConstCollection<htd::Hyperedge> htd::Tree::hyperedges(htd::vertex_t vertex) const
{
    htd::VectorAdapter<htd::Hyperedge> ret;

    auto & result = ret.container();

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = htd::Tree::hyperedges();

            for (auto it = hyperedgeCollection.begin(); it != hyperedgeCollection.end(); ++it)
            {
                const htd::Hyperedge & currentHyperedge = *it;

                if (std::find(currentHyperedge.begin(), currentHyperedge.end(), vertex) != currentHyperedge.end())
                {
                    result.push_back(currentHyperedge);
                }
            }
        }
    }
    else
    {
        throw std::logic_error("const htd::IConstCollection<htd::Hyperedge> htd::Tree::hyperedges(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::Hyperedge>::getInstance(ret);
}

const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t edgeId) const
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
        throw std::logic_error("const htd::Hyperedge & htd::Tree::hyperedge(htd::id_t) const");
    }

    return *position;
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges();

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    const htd::ConstCollection<htd::Hyperedge> & hyperedgeCollection = hyperedges(vertex);

    if (index >= hyperedgeCollection.size())
    {
        throw std::out_of_range("const htd::Hyperedge & htd::Tree::hyperedgeAtPosition(htd::index_t, htd::vertex_t) const");
    }

    htd::ConstIterator<htd::Hyperedge> it = hyperedgeCollection.begin();

    std::advance(it, index);

    return *it;
}

htd::vertex_t htd::Tree::root(void) const
{
    return root_;
}

bool htd::Tree::isRoot(htd::vertex_t vertex) const
{
    return root_ == vertex;
}

htd::vertex_t htd::Tree::parent(htd::vertex_t vertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->parent;
        }
    }
    
    return ret;
}

bool htd::Tree::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->parent == parent;
        }
    }
    else
    {
        throw std::out_of_range("bool htd::Tree::isParent(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::Tree::childCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];;

        if (node != nullptr)
        {
            ret = node->children.size();
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::children(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Tree::children(htd::vertex_t) const");
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(nodes_[vertex - htd::Vertex::FIRST]->children);
}

htd::vertex_t htd::Tree::child(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;
            
            if (index < children.size())
            {
                ret = children[index];
            }
            else
            {
                throw std::out_of_range("bool htd::Tree::child(htd::vertex_t, htd::index_t) const");
            }
        }
        else
        {
            throw std::out_of_range("bool htd::Tree::child(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("bool htd::Tree::child(htd::vertex_t, htd::index_t) const");
    }
    
    return ret;
}

bool htd::Tree::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;

            ret = std::find(children.begin(), children.end(), child) != children.end();
        }
    }
    else
    {
        throw std::logic_error("bool htd::Tree::isChild(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

void htd::Tree::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;

            if (node->parent != htd::Vertex::UNKNOWN)
            {
                auto & parent = nodes_[node->parent  - htd::Vertex::FIRST];

                auto & siblings = parent->children;

                switch (children.size())
                {
                    case 0:
                    {
                        break;
                    }
                    case 1:
                    {
                        nodes_[children[0] - htd::Vertex::FIRST]->parent = node->parent;

                        siblings.push_back(children[0]);

                        break;
                    }
                    default:
                    {
                        htd::vertex_t selectedChild = children[0];

                        auto & selectedChildNode = *(nodes_[selectedChild - htd::Vertex::FIRST]);

                        nodes_[selectedChild - htd::Vertex::FIRST]->parent = node->parent;

                        htd::vertex_container & selectedGrandChildren = selectedChildNode.children;

                        auto position = std::lower_bound(siblings.begin(), siblings.end(), selectedChild);

                        if (position == siblings.end() || *position != selectedChild)
                        {
                            siblings.insert(position, selectedChild);
                        }

                        for (auto it = children.begin() + 1; it != children.end(); ++it)
                        {
                            htd::vertex_t child = *it;

                            nodes_[child - htd::Vertex::FIRST]->parent = selectedChild;

                            auto position = std::lower_bound(selectedGrandChildren.begin(), selectedGrandChildren.end(), child);

                            if (position == selectedGrandChildren.end() || *position != child)
                            {
                                selectedGrandChildren.insert(position, child);
                            }
                        }

                        break;
                    }
                }

                deleteNode(node);
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

                        nodes_[root_ - htd::Vertex::FIRST]->parent = htd::Vertex::UNKNOWN;

                        deleteNode(node);

                        break;
                    }
                    default:
                    {
                        root_ = children[0];

                        auto & newRootNode = *(nodes_[root_ - htd::Vertex::FIRST]);

                        htd::vertex_container & newRootChildren = newRootNode.children;

                        newRootNode.parent = htd::Vertex::UNKNOWN;

                        for (auto it = children.begin() + 1; it != children.end(); ++it)
                        {
                            htd::vertex_t child = *it;

                            nodes_[child - htd::Vertex::FIRST]->parent = root_;

                            auto position = std::lower_bound(newRootChildren.begin(), newRootChildren.end(), child);

                            if (position == newRootChildren.end() || *position != child)
                            {
                                newRootChildren.insert(position, child);
                            }
                        }

                        deleteNode(node);

                        break;
                    }
                }
            }
        }
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

        next_vertex_ = root_ + 1;

        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            if (*it != nullptr)
            {
                delete *it;

                *it = nullptr;
            }
        }

        nodes_.clear();
        nodes_.push_back(new htd::Tree::Node(root_, htd::Vertex::UNKNOWN));

        vertices_.push_back(root_);

        size_ = 1;
    }
    
    return root_;
}

void htd::Tree::removeRoot(void)
{
    if (root_ != htd::Vertex::UNKNOWN)
    {
        root_ = htd::Vertex::UNKNOWN;
    
        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            if (*it != nullptr)
            {
                delete *it;

                *it = nullptr;
            }
        }
    }
        
    size_ = 0;
    
    nodes_.clear();

    vertices_.clear();
    
    deletions_.clear();
}

htd::vertex_t htd::Tree::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = next_vertex_;

            node->children.push_back(ret);

            nodes_.push_back(new htd::Tree::Node(ret, vertex));

            vertices_.push_back(ret);

            next_vertex_++;

            size_++;
        }
    }
    
    return ret;
}

void htd::Tree::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;
            
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
}

htd::vertex_t htd::Tree::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        if (isRoot(vertex))
        {
            auto & node = nodes_[vertex - htd::Vertex::FIRST];

            if (node != nullptr)
            {
                ret = next_vertex_;

                auto * newRootNode = new htd::Tree::Node(ret, htd::Vertex::UNKNOWN);

                node->parent = ret;

                newRootNode->children.push_back(vertex);

                nodes_.push_back(newRootNode);

                vertices_.push_back(ret);

                next_vertex_++;

                size_++;

                root_ = ret;
            }
        }
        else
        {
            htd::vertex_t parentVertex = parent(vertex);

            ret = addChild(parentVertex);

            auto & parentNode = nodes_[parentVertex - htd::Vertex::FIRST];
            auto & selectedNode = nodes_[vertex - htd::Vertex::FIRST];
            auto & intermediateNode = nodes_[ret - htd::Vertex::FIRST];

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
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::addParent(htd::vertex_t)");
    }

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

    auto & node = nodes_[vertex - htd::Vertex::FIRST];

    if (node->parent != newParent)
    {
        auto & newParentNode = nodes_[newParent - htd::Vertex::FIRST];

        if (isRoot(vertex))
        {
            root_ = newParent;
        }
        else
        {
            auto & parentNode = nodes_[node->parent - htd::Vertex::FIRST];

            auto position = std::find(parentNode->children.begin(), parentNode->children.end(), vertex);

            if (position != parentNode->children.end())
            {
                parentNode->children.erase(position);
            }
        }

        auto position = std::lower_bound(newParentNode->children.begin(), newParentNode->children.end(), vertex);

        newParentNode->children.insert(position, vertex);

        node->parent = newParent;
    }
}

htd::Tree & htd::Tree::operator=(const htd::Tree & other)
{
    if (this != &other)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeRoot();
        }
        
        nodes_.reserve(other.nodes_.size());
    
        for (auto & node : other.nodes_)
        {
            if (node != nullptr)
            {
                nodes_.push_back(new htd::Tree::Node(*node));
            }
        }
        
        this->root_ = other.root_;
        
        this->size_ = other.size_;
        
        this->deletions_ = other.deletions_;
    }
    
    return *this;
}

std::size_t htd::Tree::leafNodeCount(void) const
{
    std::size_t ret = 0;

    for (auto & node : nodes_)
    {
        if (node != nullptr)
        {
            if (node->children.empty())
            {
                ret++;
            }
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Tree::leafNodes(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (auto & node : nodes_)
    {
        if (node != nullptr)
        {
            if (node->children.empty())
            {
                result.push_back(node->id);
            }
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::Tree::leafNode(htd::index_t index) const
{
    const htd::ConstCollection<htd::vertex_t> & leafNodeCollection = leafNodes();

    if (index >= leafNodeCollection.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Tree::leafNode(htd::index_t) const");
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
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->children.empty();
        }
    }
    else
    {
        throw std::out_of_range("bool htd::Tree::isLeafNode(htd::vertex_t) const");
    }

    return ret;
}

void htd::Tree::deleteNode(htd::Tree::Node * node)
{
    if (node != nullptr)
    {
        auto & parent = node->parent;
        
        htd::id_t nodeIdentifier = node->id;
                
        if (parent != htd::Vertex::UNKNOWN)
        {
            auto & children = nodes_[parent - htd::Vertex::FIRST]->children;

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

                    deletions_.insert(nodeIdentifier);

                    if (nodes_[nodeIdentifier - htd::Vertex::FIRST] != nullptr)
                    {
                        delete nodes_[nodeIdentifier - htd::Vertex::FIRST];
                        
                        nodes_[nodeIdentifier - htd::Vertex::FIRST] = nullptr;

                        vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
                    }
                }
            }
        }
        else
        {
            size_--;

            deletions_.insert(nodeIdentifier);

            if (nodes_[nodeIdentifier - htd::Vertex::FIRST] != nullptr)
            {
                delete nodes_[nodeIdentifier - htd::Vertex::FIRST];

                nodes_[nodeIdentifier - htd::Vertex::FIRST] = nullptr;

                vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
            }
        }
    }
}

htd::Tree * htd::Tree::clone(void) const
{
    return new Tree(*this);
}

#endif /* HTD_HTD_TREE_CPP */
