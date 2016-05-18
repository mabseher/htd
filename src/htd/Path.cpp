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

#include <algorithm>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

htd::Path::Path(void) : size_(0), root_(htd::Vertex::UNKNOWN), next_vertex_(htd::Vertex::FIRST), nodes_()
{

}

htd::Path::Path(const htd::Path & original) : size_(original.size_), root_(original.root_), next_vertex_(htd::Vertex::FIRST), vertices_(original.vertices_), nodes_()
{
    nodes_.reserve(original.nodes_.size());

    for (const auto & node : original.nodes_)
    {
        nodes_.insert(std::make_pair(node.first, new htd::Path::Node(*(node.second))));
    }
}

htd::Path::Path(const htd::IPath & original) : size_(0), root_(original.root()), next_vertex_(htd::Vertex::FIRST), nodes_()
{
    *this = original;
}

htd::Path::~Path()
{
    if (root_ != htd::Vertex::UNKNOWN)
    {
        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            delete it->second;
        }

        nodes_.clear();
    }
}

std::size_t htd::Path::vertexCount(void) const
{
    return size_;
}

std::size_t htd::Path::vertexCount(htd::vertex_t subPathRoot) const
{
    if (!isVertex(subPathRoot))
    {
        throw std::logic_error("std::size_t htd::Path::vertexCount(htd::vertex_t) const");
    }

    std::size_t ret = 0;

    htd::vertex_t currentVertex = subPathRoot;

    while (currentVertex != htd::Vertex::UNKNOWN)
    {
        ++ret;

        currentVertex = nodes_.at(currentVertex)->child;
    }

    return ret;
}

std::size_t htd::Path::edgeCount(void) const
{
    return size_ > 0 ? size_ - 1 : 0;
}

std::size_t htd::Path::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = neighborCount(vertex);
    }
    else
    {
        throw std::out_of_range("std::size_t htd::Path::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::Path::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && nodes_.find(vertex) != nodes_.end();
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
    if (index >= vertices_.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Path::vertexAtPosition(htd::index_t) const");
    }

    return vertices_[index];
}

bool htd::Path::isNeighbor(htd::vertex_t vertex, htd::vertex_t neighbor) const
{
    bool ret = false;
    
    if (isVertex(vertex) && isVertex(neighbor))
    {
        const auto & node = nodes_.at(vertex);

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
        const auto & node = nodes_.at(vertex);

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
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Path::neighbors(htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    const auto & node = nodes_.at(vertex);

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
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::Path::copyNeighborsTo(std::vector<htd::vertex_t> &, htd::vertex_t) const");
    }

    std::size_t size = target.size();

    const auto & node = nodes_.at(vertex);

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
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::Path::neighborAtPosition(htd::vertex_t, htd::index_t) const");
    }

    const htd::ConstCollection<htd::vertex_t> & currentNeighbors = neighbors(vertex);

    if (index >= currentNeighbors.size())
    {
        throw std::out_of_range("htd::vertex_t htd::Path::neighborAtPosition(htd::vertex_t, htd::index_t) const");
    }
    
    return currentNeighbors[index];
}

htd::ConstCollection<htd::vertex_t> htd::Path::vertices(void) const
{
    return htd::ConstCollection<htd::vertex_t>::getInstance(vertices_);
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

    throw std::out_of_range("htd::vertex_t htd::Path::isolatedVertexAtPosition(htd::index_t index) const");
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

    for (const auto & currentNode : nodes_)
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
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::Hyperedge> htd::Path::hyperedges(htd::vertex_t) const");
    }

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

    for (const auto & currentNode : nodes_)
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

    return htd::FilteredHyperedgeCollection(hyperedges, indices);
}

htd::FilteredHyperedgeCollection htd::Path::hyperedgesAtPositions(std::vector<htd::index_t> && indices) const
{
    std::shared_ptr<std::vector<htd::Hyperedge>> hyperedges = std::make_shared<std::vector<htd::Hyperedge>>();

    htd::id_t id = 0;

    for (const auto & currentNode : nodes_)
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

    return htd::FilteredHyperedgeCollection(hyperedges, std::move(indices));
}

htd::vertex_t htd::Path::root(void) const
{
    if (root_ == htd::Vertex::UNKNOWN)
    {
        throw std::logic_error("htd::vertex_t htd::Path::root(void) const");
    }

    return root_;
}

bool htd::Path::isRoot(htd::vertex_t vertex) const
{
    return root_ == vertex;
}

htd::vertex_t htd::Path::parent(htd::vertex_t vertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        ret = nodes_.at(vertex)->parent;
    }
    
    return ret;
}

bool htd::Path::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = nodes_.at(vertex)->parent == parent;
    }
    else
    {
        throw std::out_of_range("bool htd::Path::isParent(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::Path::childCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        if (nodes_.at(vertex)->child != htd::Vertex::UNKNOWN)
        {
            ++ret;
        }
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::children(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::ConstCollection<htd::vertex_t> htd::Path::children(htd::vertex_t) const");
    }

    htd::VectorAdapter<htd::vertex_t> ret;

    if (nodes_.at(vertex)->child != htd::Vertex::UNKNOWN)
    {
        ret.container().push_back(nodes_.at(vertex)->child);
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::Path::child(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::Path::child(htd::vertex_t) const");
    }

    const auto & node = *(nodes_.at(vertex));

    if (node.child == htd::Vertex::UNKNOWN)
    {
        throw std::out_of_range("htd::vertex_t htd::Path::child(htd::vertex_t) const");
    }

    return node.child;
}

htd::vertex_t htd::Path::childAtPosition(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (!isVertex(vertex))
    {
        throw std::logic_error("bool htd::Path::childAtPosition(htd::vertex_t, htd::index_t) const");
    }

    const auto & node = *(nodes_.at(vertex));

    if (index == 0 && node.child != htd::Vertex::UNKNOWN)
    {
        ret = node.child;
    }
    else
    {
        throw std::out_of_range("bool htd::Path::childAtPosition(htd::vertex_t, htd::index_t) const");
    }
    
    return ret;
}

bool htd::Path::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = nodes_.at(vertex)->child == child;
    }
    else
    {
        throw std::logic_error("bool htd::Path::isChild(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

void htd::Path::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        auto & node = *(nodes_.at(vertex));

        if (node.parent != htd::Vertex::UNKNOWN)
        {
            auto & parent = nodes_.at(node.parent);

            if (node.child != htd::Vertex::UNKNOWN)
            {
                auto & child = nodes_.at(node.child);

                child->parent = node.parent;

                parent->child = node.child;
            }

            deleteNode(&node);
        }
        else
        {
            if (node.child != htd::Vertex::UNKNOWN)
            {
                auto & child = *(nodes_.at(node.child));

                child.parent = htd::Vertex::UNKNOWN;

                root_ = node.child;

                deleteNode(&node);
            }
            else
            {
                removeSubpath(root_);
            }
        }
    }
}

void htd::Path::removeSubpath(htd::vertex_t subpathRoot)
{
    if (!isVertex(subpathRoot))
    {
        throw std::logic_error("void htd::Path::removeSubPath(htd::vertex_t)");
    }

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
    if (root_ == htd::Vertex::UNKNOWN)
    {
        root_ = htd::Vertex::FIRST;

        next_vertex_ = root_ + 1;

        for (auto it = nodes_.begin(); it != nodes_.end(); it++)
        {
            delete it->second;
        }

        nodes_.clear();
        nodes_.insert(std::make_pair(root_, new htd::Path::Node(root_, htd::Vertex::UNKNOWN)));

        vertices_.push_back(root_);

        size_ = 1;
    }

    return root_;
}

htd::vertex_t htd::Path::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        htd::vertex_t child = nodes_.at(vertex)->child;

        ret = next_vertex_;

        nodes_.insert(std::make_pair(ret, new htd::Path::Node(ret, vertex)));

        if (child != htd::Vertex::UNKNOWN)
        {
            nodes_.at(child)->parent = ret;
            nodes_.at(ret)->child = child;
        }

        nodes_.at(vertex)->child = ret;

        vertices_.push_back(ret);

        next_vertex_++;

        size_++;
    }
    
    return ret;
}

void htd::Path::removeChild(htd::vertex_t vertex)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("void htd::Path::removeChild(htd::vertex_t)");
    }

    const auto & node = nodes_.at(vertex);

    if (node->child == htd::Vertex::UNKNOWN)
    {
        throw std::logic_error("void htd::Path::removeChild(htd::vertex_t)");
    }

    removeVertex(node->child);
}

void htd::Path::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    if (isVertex(vertex) && isVertex(child))
    {
        const auto & node = nodes_.at(vertex);

        if (node != nullptr && node->child == child)
        {
            removeVertex(child);
        }
        else
        {
            throw std::logic_error("void htd::Path::removeChild(htd::vertex_t, htd::vertex_t)");
        }
    }
}

htd::vertex_t htd::Path::addParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        if (isRoot(vertex))
        {
            auto & node = nodes_.at(vertex);

            if (node != nullptr)
            {
                ret = next_vertex_;

                auto * newRootNode = new htd::Path::Node(ret, htd::Vertex::UNKNOWN);

                node->parent = ret;

                newRootNode->child = vertex;

                nodes_.insert(std::make_pair(ret, newRootNode));

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

            auto & parentNode = nodes_.at(parentVertex);
            auto & selectedNode = nodes_.at(vertex);
            auto & intermediateNode = nodes_.at(ret);

            if (parentNode != nullptr && selectedNode != nullptr && intermediateNode != nullptr)
            {
                intermediateNode->parent = parentVertex;

                intermediateNode->child = vertex;

                selectedNode->parent = ret;
            }
        }
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::Path::addParent(htd::vertex_t)");
    }

    return ret;
}

std::size_t htd::Path::leafCount(void) const
{
    std::size_t ret = 0;

    if (size_ > 0)
    {
        ++ret;
    }

    return ret;
}

htd::ConstCollection<htd::vertex_t> htd::Path::leaves(void) const
{
    htd::VectorAdapter<htd::vertex_t> ret;

    auto & result = ret.container();

    for (const auto & node : nodes_)
    {
        if (node.second->child == htd::Vertex::UNKNOWN)
        {
            result.push_back(node.first);
        }
    }

    return htd::ConstCollection<htd::vertex_t>::getInstance(ret);
}

htd::vertex_t htd::Path::leaf(void) const
{
    if (size_ == 0)
    {
        throw std::out_of_range("htd::vertex_t htd::Path::leaf(void) const");
    }

    for (const auto & node : nodes_)
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
    if (size_ == 0 || index >= 1)
    {
        throw std::out_of_range("htd::vertex_t htd::Path::leafAtPosition(htd::index_t) const");
    }

    return leaf();
}

bool htd::Path::isLeaf(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        ret = nodes_.at(vertex)->child == htd::Vertex::UNKNOWN;
    }
    else
    {
        throw std::out_of_range("bool htd::Path::isLeaf(htd::vertex_t) const");
    }

    return ret;
}

void htd::Path::deleteNode(htd::Path::Node * node)
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

htd::Path * htd::Path::clone(void) const
{
    return new htd::Path(*this);
}

htd::Path & htd::Path::operator=(const htd::Path & original)
{
    if (this != &original)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeSubpath(root_);
        }

        nodes_.reserve(original.nodes_.size());

        for (const auto & node : original.nodes_)
        {
            nodes_.insert(std::make_pair(node.first, new htd::Path::Node(*(node.second))));
        }

        this->root_ = original.root_;

        this->size_ = original.size_;

        if (original.next_vertex_ >= htd::Vertex::FIRST)
        {
            next_vertex_ = original.next_vertex_;
        }
        else
        {
            next_vertex_ = htd::Vertex::FIRST;
        }
    }

    return *this;
}

htd::Path & htd::Path::operator=(const htd::IPath & original)
{
    if (this != &original)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeSubpath(root_);
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
                htd::Path::Node * newNode = nullptr;

                if (original.isRoot(vertex))
                {
                    newNode = new htd::Path::Node(vertex, htd::Vertex::UNKNOWN);
                }
                else
                {
                    newNode = new htd::Path::Node(vertex, original.parent(vertex));
                }

                if (!original.isLeaf(vertex))
                {
                    newNode->child = original.child(vertex);
                }

                nodes_.insert(std::make_pair(vertex, newNode));

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
        }
    }

    return *this;
}

#endif /* HTD_HTD_PATH_CPP */
