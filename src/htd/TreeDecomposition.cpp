/* 
 * File:   TreeDecomposition.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_TREEDECOMPOSITION_CPP
#define	HTD_HTD_TREEDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/TreeDecomposition.hpp>
#include <htd/GraphLabeling.hpp>
#include <htd/ILabeledTree.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/VertexContainerLabel.hpp>

#include <algorithm>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <utility>
#include <vector>

//TODO Remove
#include <iostream>

htd::TreeDecomposition::TreeDecomposition(void)
    : size_(0), root_(htd::Vertex::UNKNOWN), next_vertex_(htd::Vertex::FIRST), nodes_(), deletions_(), labelings_(new htd::LabelingCollection())
{
    
}

//TODO Ensure correctness when htd::Vertex::FIRST does not match for this and original
htd::TreeDecomposition::TreeDecomposition(const htd::ILabeledTree & original)
    : size_(0), root_(original.root()), next_vertex_(htd::Vertex::FIRST), nodes_(), deletions_(), labelings_(original.labelings().clone())
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

        nodes_.push_back(new TreeNode(node, original.parent(node)));

        htd::vertex_container children;

        original.getChildren(node, children);

        nodes_[node - htd::Vertex::FIRST]->children = children;

        if (node > maximumVertex)
        {
            maximumVertex = node;
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

htd::TreeDecomposition::TreeDecomposition(const htd::TreeDecomposition & original)
    : size_(original.size_), root_(original.root_), next_vertex_(htd::Vertex::FIRST), nodes_(), deletions_(original.deletions_), labelings_(original.labelings().clone())
{
    nodes_.reserve(original.nodes_.size());
    
    for (auto& node : original.nodes_)
    {
        if (node != nullptr)
        {
            nodes_.push_back(new TreeNode(*node));
        }
    }
}

htd::TreeDecomposition::~TreeDecomposition()
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

    if (labelings_ != nullptr)
    {
        delete labelings_;

        labelings_ = nullptr;
    }
}

std::size_t htd::TreeDecomposition::vertexCount(void) const
{
    return size_;
}

std::size_t htd::TreeDecomposition::edgeCount(void) const
{
    return size_ > 0 ? size_ - 1 : 0;
}

std::size_t htd::TreeDecomposition::edgeCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        ret = neighborCount(vertex);
    }
    else
    {
        throw std::out_of_range("std::size_t htd::TreeDecomposition::edgeCount(htd::vertex_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isVertex(htd::vertex_t vertex) const
{
    return vertex < next_vertex_ && vertex != htd::Vertex::UNKNOWN && !std::binary_search(deletions_.begin(), deletions_.end(), vertex);
}

bool htd::TreeDecomposition::isEdge(const htd::hyperedge_t & edge) const
{
    bool ret = false;

    if (edge.size() == 2 && edge[0] != edge[1])
    {
        ret = isNeighbor(edge[0], edge[1]);
    }

    return ret;
}

htd::vertex_t htd::TreeDecomposition::vertex(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (index < size_ - deletions_.size())
    {
        htd::vertex_t vertex = 0;
        
        std::size_t currentIndex = 0;
        
        while (currentIndex < index)
        {
            if (!std::binary_search(deletions_.begin(), deletions_.end(), vertex))
            {
                ++currentIndex;
            }
            
            ++vertex;
        }
        
        ret = vertex;
    }
    
    return ret;
}

bool htd::TreeDecomposition::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    bool ret = false;
    
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        auto& node = nodes_[vertex1];

        if (node != nullptr)
        {
            auto& children = node->children;
            
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

bool htd::TreeDecomposition::isConnected(void) const
{
    return true;
}

bool htd::TreeDecomposition::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return isVertex(vertex1) && isVertex(vertex2);
}

std::size_t htd::TreeDecomposition::neighborCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                ret++;
            }

            ret += children.size();
        }
    }
    
    return ret;
}

void htd::TreeDecomposition::getNeighbors(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                output.push_back(node->parent);
            }

            for (auto child : children)
            {
                output.push_back(child);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            std::size_t currentIndex = 0;
            
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                if (currentIndex == index)
                {
                    ret = node->parent;
                }
                
                ++currentIndex;
            }

            for (auto child = children.begin(); currentIndex <= index && child != children.end(); child++)
            {
                if (currentIndex == index)
                {
                    ret = *child;
                }
                
                ++currentIndex;
            }
        }
    }
    
    return ret;
}

htd::Collection<htd::vertex_t> htd::TreeDecomposition::vertices(void) const
{
    return Collection<htd::vertex_t>(vertices_);
}

std::size_t htd::TreeDecomposition::isolatedVertexCount(void) const
{
    return 0;
}

void htd::TreeDecomposition::getIsolatedVertices(htd::vertex_container& output) const
{
    HTD_UNUSED(output);
}

htd::vertex_t htd::TreeDecomposition::isolatedVertex(htd::index_t index) const
{
    HTD_UNUSED(index);

    throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::isolatedVertex(htd::index_t index) const");
}

bool htd::TreeDecomposition::isIsolatedVertex(htd::vertex_t vertex) const
{
    HTD_UNUSED(vertex);

    return false;
}

void htd::TreeDecomposition::getEdges(htd::edge_container & output) const
{
    for (auto& currentNode : nodes_)
    {
        if (currentNode != nullptr)
        {
            auto& children = currentNode->children;

            for (auto child : children)
            {
                output.push_back(edge_t(currentNode->id, child));
            }
        }
    }
}

void htd::TreeDecomposition::getEdges(htd::edge_container & output, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                output.push_back(edge_t(node->parent, node->id));
            }

            for (auto child : children)
            {
                output.push_back(edge_t(node->id, child));
            }
        }
    }
}

const htd::edge_t & htd::TreeDecomposition::edge(htd::index_t index) const
{
    htd::edge_container result;

    getEdges(result);

    if (index < result.size())
    {
        return result[index];
    }
    else
    {
        throw std::out_of_range("const htd::edge_t & htd::TreeDecomposition::edge(htd::index_t) const");
    }
}

const htd::edge_t & htd::TreeDecomposition::edge(htd::index_t index, htd::vertex_t vertex) const
{
    htd::edge_container result;

    getEdges(result, vertex);

    if (index < result.size())
    {
        return result[index];
    }
    else
    {
        throw std::out_of_range("const htd::edge_t & htd::TreeDecomposition::edge(htd::index_t, htd::vertex_t) const");
    }
}

void htd::TreeDecomposition::getHyperedges(htd::hyperedge_container & output) const
{
    for (auto& currentNode : nodes_)
    {
        if (currentNode != nullptr)
        {
            auto& children = currentNode->children;

            for (auto child : children)
            {
                htd::hyperedge_t hyperedge;

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

                output.push_back(hyperedge);
            }
        }
    }
}

void htd::TreeDecomposition::getHyperedges(htd::hyperedge_container& output, htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                htd::hyperedge_t hyperedge;

                if (node->parent < node->id)
                {
                    hyperedge.push_back(node->parent);
                    hyperedge.push_back(node->id);
                }
                else
                {
                    hyperedge.push_back(node->id);
                    hyperedge.push_back(node->parent);
                }

                output.push_back(hyperedge);
            }

            for (auto child : children)
            {
                htd::hyperedge_t hyperedge;

                if (node->id < child)
                {
                    hyperedge.push_back(node->id);
                    hyperedge.push_back(child);
                }
                else
                {
                    hyperedge.push_back(child);
                    hyperedge.push_back(node->id);
                }

                output.push_back(hyperedge);
            }
        }
    }
}

const htd::hyperedge_t & htd::TreeDecomposition::hyperedge(htd::index_t index) const
{
    htd::hyperedge_container result;

    getHyperedges(result);

    if (index < result.size())
    {
        return result[index];
    }
    else
    {
        throw std::out_of_range("const htd::hyperedge_t & htd::TreeDecomposition::hyperedge(htd::index_t) const");
    }
}

const htd::hyperedge_t & htd::TreeDecomposition::hyperedge(htd::index_t index, htd::vertex_t vertex) const
{
    htd::hyperedge_container result;

    getHyperedges(result, vertex);

    if (index < result.size())
    {
        return result[index];
    }
    else
    {
        throw std::out_of_range("const htd::hyperedge_t & htd::TreeDecomposition::hyperedge(htd::index_t, htd::vertex_t) const");
    }
}

htd::vertex_t htd::TreeDecomposition::root(void) const
{
    return root_;
}

bool htd::TreeDecomposition::isRoot(htd::vertex_t vertex) const
{
    return root_ == vertex;
}

htd::vertex_t htd::TreeDecomposition::parent(htd::vertex_t vertex) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->parent;
        }
    }
    
    return ret;
}

bool htd::TreeDecomposition::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->parent == parent;
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isParent(htd::vertex_t, htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::childCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];;

        if (node != nullptr)
        {
            ret = node->children.size();
        }
    }

    return ret;
}

void htd::TreeDecomposition::getChildren(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            for (auto child : children)
            {
                output.push_back(child);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::child(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (index < children.size())
            {
                ret = children[index];
            }
            else
            {
                throw std::out_of_range("bool htd::TreeDecomposition::child(htd::vertex_t, htd::index_t) const");
            }
        }
        else
        {
            throw std::out_of_range("bool htd::TreeDecomposition::child(htd::vertex_t, htd::index_t) const");
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::child(htd::vertex_t, htd::index_t) const");
    }
    
    return ret;
}

bool htd::TreeDecomposition::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;

            ret = std::find(children.begin(), children.end(), child) != children.end();
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isChild(htd::vertex_t vertex, htd::vertex_t child) const");
    }

    return ret;
}

void htd::TreeDecomposition::removeVertex(htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
            if (node->parent != htd::Vertex::UNKNOWN)
            {
                auto& parent = nodes_[node->parent  - htd::Vertex::FIRST];
            
                auto& siblings = parent->children;

                switch (children.size())
                {
                    case 0:
                    {
                        deleteNode(node);
                        
                        break;
                    }
                    case 1:
                    {
                        nodes_[children[0] - htd::Vertex::FIRST]->parent = node->parent;

                        siblings.push_back(children[0]);

                        deleteNode(node);

                        break;
                    }
                    default:
                    {
                        //TODO
                        /*
                        std::size_t bestOverlap = 0;
                        
                        htd::vertex_t bestChoice = htd::Vertex::UNKNOWN;
                        
                        auto& parentLabel = vertex_labels[node->id];

                        std::cout << "ELIMINATING VERTEX " << node->id << " (PARENT=" << node->parent << ") ..." << std::endl;
                        std::cout << "   ";
                        htd::print(parentLabel, false);
                        std::cout << std::endl;
                        
                        //Find optimal choice for new root
                        for (auto child : children)
                        {
                            auto& childLabel = vertex_labels[child];

                            std::size_t currentOverlap = htd::compute_set_intersection_size(parentLabel.begin(), parentLabel.end(), childLabel.begin(), childLabel.end());

                            std::cout << "COMPUTING OVERLAP WITH VERTEX " << child << " ..." << std::endl;
                            std::cout << "   ";
                            htd::print(childLabel, false);
                            std::cout << std::endl;
                            
                            std::cout << "OVERLAP: " << currentOverlap << std::endl;
                        
                            //TODO Keep options of same quality and select (randomly) from this pool?
                            if (currentOverlap > bestOverlap)
                            {
                                bestChoice = child;
                                
                                bestOverlap = currentOverlap;
                            }
                        }
                        
                        std::cout << "BEST CHOICE: " << bestChoice << std::endl;
                        
                        if (bestChoice == htd::Vertex::UNKNOWN)
                        {
                            bestChoice = node->children[0];
                        }
                        
                        nodes[bestChoice]->parent = node->parent;

                        siblings.push_back(bestChoice);
                        
                        auto& bestChoiceLabel = vertex_labels[bestChoice];

                        for (auto child : children)
                        {
                            if (child != bestChoice)
                            {
                                auto& childLabel = vertex_labels[child];

                                std::size_t currentOverlap = htd::compute_set_intersection_size(bestChoiceLabel.begin(), bestChoiceLabel.end(), childLabel.begin(), childLabel.end());

                                if (currentOverlap > 0)
                                {
                                    nodes[child]->parent = bestChoice;

                                    nodes[bestChoice]->children.push_back(child);
                                }
                                else
                                {
                                    nodes[child]->parent = node->parent;

                                    siblings.push_back(child);
                                }
                            }
                        }
                        
                        deleteNode(node);
                        */
                        
                        break;
                    }
                }
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
                        root_ = node->children[0];
                        
                        nodes_[root_ - htd::Vertex::FIRST]->parent = htd::Vertex::UNKNOWN;
                        
                        deleteNode(node);
                    
                        break;
                    }
                    default:
                    {
                        std::size_t bestOverlap = 0;
                        
                        htd::vertex_t bestChoice = htd::Vertex::UNKNOWN;

                        auto oldNodeLabel = bagContent(node->id);

                        //Find optimal choice for new root
                        for (auto child : children)
                        {
                            auto childLabel = bagContent(child);

                            std::size_t currentOverlap = htd::compute_set_intersection_size(oldNodeLabel.begin(), oldNodeLabel.end(), childLabel.begin(), childLabel.end());

                            //TODO Keep options of same quality and select (randomly) from this pool?
                            if (currentOverlap > bestOverlap)
                            {
                                bestChoice = child;

                                bestOverlap = currentOverlap;
                            }
                        }
                        
                        if (bestChoice == htd::Vertex::UNKNOWN)
                        {
                            bestChoice = node->children[0];
                        }
                        
                        root_ = bestChoice;
                        
                        nodes_[root_ - htd::Vertex::FIRST]->parent = htd::Vertex::UNKNOWN;

                        for (auto child : children)
                        {
                            if (child != bestChoice)
                            {
                                nodes_[child - htd::Vertex::FIRST]->parent = bestChoice;

                                nodes_[bestChoice - htd::Vertex::FIRST]->children.push_back(child);
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

void htd::TreeDecomposition::removeSubtree(htd::vertex_t subtreeRoot)
{
    if (isVertex(subtreeRoot))
    {
        deleteSubtree(nodes_[subtreeRoot - htd::Vertex::FIRST]);
    }
}

htd::vertex_t htd::TreeDecomposition::insertRoot(void)
{
    if (root_ == htd::Vertex::UNKNOWN)
    {
        root_ = htd::Vertex::FIRST;

        next_vertex_ = root_ + 1;
        
        nodes_.clear();
        nodes_.push_back(new TreeNode(1, htd::Vertex::UNKNOWN));

        for (auto& labeling : *labelings_)
        {
            labeling.second->clear();
        }

        vertices_.clear();
        vertices_.push_back(root_);

        size_ = 1;
    }
    
    return root_;
}

void htd::TreeDecomposition::removeRoot(void)
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

    for (auto& labeling : *labelings_)
    {
        labeling.second->clear();
    }
}

htd::vertex_t htd::TreeDecomposition::addChild(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;
    
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = next_vertex_;

            node->children.push_back(ret);

            nodes_.push_back(new TreeNode(ret, vertex));

            vertices_.push_back(ret);

            next_vertex_++;

            size_++;
        }
    }
    
    return ret;
}

void htd::TreeDecomposition::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto& children = node->children;
            
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
                    deleteSubtree(nodes_[*position]);
                }
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::addIntermediateParent(htd::vertex_t vertex)
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    if (isVertex(vertex))
    {
        if (isRoot(vertex))
        {

        }
        else
        {
            htd::vertex_t parentVertex = parent(vertex);

            ret = addChild(parentVertex);

            auto& parentNode = nodes_[parentVertex - htd::Vertex::FIRST];
            auto& selectedNode = nodes_[vertex - htd::Vertex::FIRST];
            auto& intermediateNode = nodes_[ret - htd::Vertex::FIRST];

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
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::addIntermediateParent(htd::vertex_t)");
    }

    return ret;
}

const htd::ILabelingCollection & htd::TreeDecomposition::labelings(void) const
{
    return *labelings_;
}

std::size_t htd::TreeDecomposition::labelCount(void) const
{
    return labelings_->labelCount();
}

htd::Collection<std::string> htd::TreeDecomposition::labelNames(void) const
{
    return labelings_->labelNames();
}

const std::string & htd::TreeDecomposition::labelName(htd::index_t index) const
{
    if (index >= labelings_->labelCount())
    {
        throw std::out_of_range("const std::string & htd::TreeDecomposition::labelName(htd::index_t) const");
    }

    auto position = labelings_->begin();

    std::advance(position, index);

    return (*position).first;
}

const htd::ILabel & htd::TreeDecomposition::label(const std::string & labelName, htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::out_of_range("const htd::ILabel & htd::TreeDecomposition::label(const std::string &, htd::vertex_t) const");
    }

    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("const htd::ILabel & htd::TreeDecomposition::label(const std::string &, htd::vertex_t) const");
    }

    return (*labelings_)[labelName].label(vertex);
}

const htd::ILabel & htd::TreeDecomposition::label(const std::string & labelName, const htd::hyperedge_t & edge) const
{
    if (!isEdge(edge))
    {
        throw std::out_of_range("const htd::ILabel & htd::TreeDecomposition::label(const std::string &, const htd::hyperedge_t &) const");
    }

    if (!labelings_->isLabelingName(labelName))
    {
        throw std::logic_error("const htd::ILabel & htd::TreeDecomposition::label(const std::string &, const htd::hyperedge_t &) const");
    }

    return (*labelings_)[labelName].label(edge);
}

void htd::TreeDecomposition::setLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    if (isVertex(vertex))
    {
        if (!labelings_->isLabelingName(labelName))
        {
            labelings_->setLabeling(labelName, new htd::GraphLabeling());
        }

        (*labelings_)[labelName].setLabel(vertex, label);
    }
}

void htd::TreeDecomposition::setLabel(const std::string & labelName, const htd::hyperedge_t & edge, htd::ILabel * label)
{
    if (isEdge(edge))
    {
        if (!labelings_->isLabelingName(labelName))
        {
            labelings_->setLabeling(labelName, new htd::GraphLabeling());
        }

        (*labelings_)[labelName].setLabel(edge, label);
    }
}

void htd::TreeDecomposition::removeLabel(const std::string & labelName, htd::vertex_t vertex)
{
    if (isVertex(vertex))
    {
        if (labelings_->isLabelingName(labelName))
        {
            (*labelings_)[labelName].removeLabel(vertex);
        }
    }
}

void htd::TreeDecomposition::removeLabel(const std::string & labelName, const htd::hyperedge_t & edge)
{
    if (isEdge(edge))
    {
        if (labelings_->isLabelingName(labelName))
        {
            (*labelings_)[labelName].removeLabel(edge);
        }
    }
}

htd::TreeDecomposition & htd::TreeDecomposition::operator=(const htd::TreeDecomposition & other)
{
    if (this != &other)
    {
        if (this->root_ != htd::Vertex::UNKNOWN)
        {
            removeRoot();
        }
        
        nodes_.reserve(other.nodes_.size());
    
        for (auto& node : other.nodes_)
        {
            if (node != nullptr)
            {
                nodes_.push_back(new TreeNode(*node));
            }
        }
        
        this->root_ = other.root_;
        
        this->size_ = other.size_;
        
        this->deletions_ = other.deletions_;
        
        this->labelings_ = other.labelings_;
    }
    
    return *this;
}

std::size_t htd::TreeDecomposition::leafNodeCount(void) const
{
    std::size_t ret = 0;

    for (auto& node : nodes_)
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

void htd::TreeDecomposition::getLeafNodes(htd::vertex_container & output) const
{
    for (auto& node : nodes_)
    {
        if (node != nullptr)
        {
            if (node->children.empty())
            {
                output.push_back(node->id);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::leafNode(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container leafNodeContainer;

    getLeafNodes(leafNodeContainer);

    if (index < leafNodeContainer.size())
    {
        ret = leafNodeContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::leafNode(htd::index_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isLeafNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->children.empty();
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isLeafNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::joinNodeCount(void) const
{
    std::size_t ret = 0;

    for (auto& node : nodes_)
    {
        if (node != nullptr)
        {
            if (node->children.size() > 1)
            {
                ret++;
            }
        }
    }

    return ret;
}

void htd::TreeDecomposition::getJoinNodes(htd::vertex_container & output) const
{
    for (auto& node : nodes_)
    {
        if (node != nullptr)
        {
            if (node->children.size() > 1)
            {
                output.push_back(node->id);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::joinNode(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container joinNodeContainer;

    getJoinNodes(joinNodeContainer);

    if (index < joinNodeContainer.size())
    {
        ret = joinNodeContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::joinNode(htd::index_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isJoinNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto& node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            ret = node->children.size() > 1;
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isJoinNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgetNodeCount(void) const
{
    std::size_t ret = 0;

    for (auto& node : nodes_)
    {
        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            if (htd::has_non_empty_set_difference(childLabelContent.begin(), childLabelContent.end(), vertexLabel.begin(), vertexLabel.end()))
            {
                ret++;
            }
        }
    }

    return ret;
}

void htd::TreeDecomposition::getForgetNodes(htd::vertex_container & output) const
{
    for (auto & node : nodes_)
    {
        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            if (htd::has_non_empty_set_difference(childLabelContent.begin(), childLabelContent.end(), vertexLabel.begin(), vertexLabel.end()))
            {
                output.push_back(node->id);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::forgetNode(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container forgetNodeContainer;

    getForgetNodes(forgetNodeContainer);

    if (index < forgetNodeContainer.size())
    {
        ret = forgetNodeContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgetNode(htd::index_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isForgetNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            ret = htd::has_non_empty_set_difference(childLabelContent.begin(), childLabelContent.end(), vertexLabel.begin(), vertexLabel.end());
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isForgetNode(htd::vertex_t) const");
    }

    return ret;
}

std::size_t htd::TreeDecomposition::introduceNodeCount(void) const
{
    std::size_t ret = 0;

    for (auto & node : nodes_)
    {
        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            if (htd::has_non_empty_set_difference(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end()))
            {
                ret++;
            }
        }
    }

    return ret;
}

void htd::TreeDecomposition::getIntroduceNodes(htd::vertex_container & output) const
{
    for (auto & node : nodes_)
    {
        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            if (htd::has_non_empty_set_difference(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end()))
            {
                output.push_back(node->id);
            }
        }
    }
}

htd::vertex_t htd::TreeDecomposition::introduceNode(htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container introduceNodeContainer;

    getIntroduceNodes(introduceNodeContainer);

    if (index < introduceNodeContainer.size())
    {
        ret = introduceNodeContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introduceNode(htd::index_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isIntroduceNode(htd::vertex_t vertex) const
{
    bool ret = false;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(node->id);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(node->id, childLabelContent);

            ret = htd::has_non_empty_set_difference(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end());
        }
    }
    else
    {
        throw std::out_of_range("bool htd::TreeDecomposition::isIntroduceNode(htd::vertex_t) const");
    }

    return ret;
}

htd::Collection<htd::vertex_t> htd::TreeDecomposition::bagContent(htd::vertex_t vertex) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & bagLabeling = (*labelings_)[htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER];

            if (bagLabeling.hasLabel(vertex))
            {
                auto & vertexLabel = dynamic_cast<const htd::VertexContainerLabel *>(&(bagLabeling.label(vertex)))->container();

                return htd::Collection<htd::vertex_t>(vertexLabel);
            }
        }
    }

    return htd::Collection<htd::vertex_t>();
}

std::size_t htd::TreeDecomposition::minimumBagSize(void) const
{
    bool start = true;

    std::size_t ret = 0;

    auto & bagLabeling = (*labelings_)[htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER];

    for (htd::vertex_t vertex : vertices())
    {
        if (bagLabeling.hasLabel(vertex))
        {
            auto vertexLabel = bagContent(vertex);

            std::size_t bagSize = std::distance(vertexLabel.begin(), vertexLabel.end());

            if (start || bagSize < ret)
            {
                ret = bagSize;

                start = false;
            }
        }
    }

    return ret;
}

std::size_t htd::TreeDecomposition::maximumBagSize(void) const
{
    std::size_t ret = 0;

    auto & bagLabeling = (*labelings_)[htd::ITreeDecomposition::BAG_LABEL_IDENTIFIER];

    for (htd::vertex_t vertex : vertices())
    {
        if (bagLabeling.hasLabel(vertex))
        {
            auto vertexLabel = bagContent(vertex);

            std::size_t bagSize = std::distance(vertexLabel.begin(), vertexLabel.end());

            if (bagSize > ret)
            {
                ret = bagSize;
            }
        }
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            ret = htd::compute_set_difference_size(childLabelContent.begin(), childLabelContent.end(), vertexLabel.begin(), vertexLabel.end());
        }
    }

    return ret;
}

std::size_t htd::TreeDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            ret = htd::compute_set_difference_size(childVertexLabel.begin(), childVertexLabel.end(), vertexLabel.begin(), vertexLabel.end());
        }
    }

    return ret;
}

void htd::TreeDecomposition::getForgottenVertices(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            std::set_difference(childLabelContent.begin(), childLabelContent.end(), vertexLabel.begin(), vertexLabel.end(), std::back_inserter(output));
        }
    }
}

void htd::TreeDecomposition::getForgottenVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            std::set_difference(childVertexLabel.begin(), childVertexLabel.end(), vertexLabel.begin(), vertexLabel.end(), std::back_inserter(output));
        }
    }
}

htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container forgottenVerticesContainer;

    getForgottenVertices(vertex, forgottenVerticesContainer);

    if (index < forgottenVerticesContainer.size())
    {
        ret = forgottenVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container forgottenVerticesContainer;

    getForgottenVertices(vertex, forgottenVerticesContainer, child);

    if (index < forgottenVerticesContainer.size())
    {
        ret = forgottenVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::forgottenVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const
{
    bool ret = false;

    htd::vertex_container forgottenVerticesContainer;

    getForgottenVertices(vertex, forgottenVerticesContainer);

    ret = std::find(forgottenVerticesContainer.begin(), forgottenVerticesContainer.end(), forgottenVertex) != forgottenVerticesContainer.end();

    return ret;
}

bool htd::TreeDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const
{
    bool ret = false;

    htd::vertex_container forgottenVerticesContainer;

    getForgottenVertices(vertex, forgottenVerticesContainer, child);

    ret = std::find(forgottenVerticesContainer.begin(), forgottenVerticesContainer.end(), forgottenVertex) != forgottenVerticesContainer.end();

    return ret;
}

std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            ret = htd::compute_set_difference_size(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end());
        }
    }

    return ret;
}

std::size_t htd::TreeDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            ret = htd::compute_set_difference_size(vertexLabel.begin(), vertexLabel.end(), childVertexLabel.begin(), childVertexLabel.end());
        }
    }

    return ret;
}

void htd::TreeDecomposition::getIntroducedVertices(htd::vertex_t vertex, htd::vertex_container& output) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            std::set_difference(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end(), std::back_inserter(output));
        }
    }
}

void htd::TreeDecomposition::getIntroducedVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            std::set_difference(vertexLabel.begin(), vertexLabel.end(), childVertexLabel.begin(), childVertexLabel.end(), std::back_inserter(output));
        }
    }
}

htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container introducedVerticesContainer;

    getIntroducedVertices(vertex, introducedVerticesContainer);

    if (index < introducedVerticesContainer.size())
    {
        ret = introducedVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container introducedVerticesContainer;

    getIntroducedVertices(vertex, introducedVerticesContainer, child);

    if (index < introducedVerticesContainer.size())
    {
        ret = introducedVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::introducedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const
{
    bool ret = false;

    htd::vertex_container introducedVerticesContainer;

    getIntroducedVertices(vertex, introducedVerticesContainer);

    ret = std::find(introducedVerticesContainer.begin(), introducedVerticesContainer.end(), introducedVertex) != introducedVerticesContainer.end();

    return ret;
}

bool htd::TreeDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const
{
    bool ret = false;

    htd::vertex_container introducedVerticesContainer;

    getIntroducedVertices(vertex, introducedVerticesContainer, child);

    ret = std::find(introducedVerticesContainer.begin(), introducedVerticesContainer.end(), introducedVertex) != introducedVerticesContainer.end();

    return ret;
}

std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t vertex) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            ret = htd::compute_set_intersection_size(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end());
        }
    }

    return ret;
}

std::size_t htd::TreeDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    std::size_t ret = 0;

    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            ret = htd::compute_set_intersection_size(vertexLabel.begin(), vertexLabel.end(), childVertexLabel.begin(), childVertexLabel.end());
        }
    }

    return ret;
}

void htd::TreeDecomposition::getRememberedVertices(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            htd::vertex_container childLabelContent;

            getChildrenVertexLabelSetUnion(vertex, childLabelContent);

            std::set_intersection(vertexLabel.begin(), vertexLabel.end(), childLabelContent.begin(), childLabelContent.end(), std::back_inserter(output));
        }
    }
}

void htd::TreeDecomposition::getRememberedVertices(htd::vertex_t vertex, htd::vertex_container & output, htd::vertex_t child) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto vertexLabel = bagContent(vertex);

            auto childVertexLabel = bagContent(child);

            std::set_intersection(vertexLabel.begin(), vertexLabel.end(), childVertexLabel.begin(), childVertexLabel.end(), std::back_inserter(output));
        }
    }
}

htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container rememberedVerticesContainer;

    getRememberedVertices(vertex, rememberedVerticesContainer);

    if (index < rememberedVerticesContainer.size())
    {
        ret = rememberedVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t, htd::index_t) const");
    }

    return ret;
}

htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    htd::vertex_t ret = htd::Vertex::UNKNOWN;

    htd::vertex_container rememberedVerticesContainer;

    getRememberedVertices(vertex, rememberedVerticesContainer, child);

    if (index < rememberedVerticesContainer.size())
    {
        ret = rememberedVerticesContainer[index];
    }
    else
    {
        throw std::out_of_range("htd::vertex_t htd::TreeDecomposition::rememberedVertex(htd::vertex_t, htd::index_t, htd::vertex_t) const");
    }

    return ret;
}

bool htd::TreeDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const
{
    bool ret = false;

    htd::vertex_container rememberedVerticesContainer;

    getRememberedVertices(vertex, rememberedVerticesContainer);

    ret = std::find(rememberedVerticesContainer.begin(), rememberedVerticesContainer.end(), rememberedVertex) != rememberedVerticesContainer.end();

    return ret;
}

bool htd::TreeDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const
{
    bool ret = false;

    htd::vertex_container rememberedVerticesContainer;

    getRememberedVertices(vertex, rememberedVerticesContainer, child);

    ret = std::find(rememberedVerticesContainer.begin(), rememberedVerticesContainer.end(), rememberedVertex) != rememberedVerticesContainer.end();

    return ret;
}

void htd::TreeDecomposition::getChildrenVertexLabelSetUnion(htd::vertex_t vertex, htd::vertex_container & output) const
{
    if (isVertex(vertex))
    {
        auto & node = nodes_[vertex - htd::Vertex::FIRST];

        if (node != nullptr)
        {
            auto & children = node->children;

            for (auto child : children)
            {
                auto childLabel = bagContent(child);

                std::copy(childLabel.begin(), childLabel.end(), std::back_inserter(output));
            }

            std::sort(output.begin(), output.end());

            output.erase(std::unique(output.begin(), output.end()), output.end());
        }
    }
}
            
std::size_t htd::TreeDecomposition::size(htd::TreeDecomposition::TreeNode * start) const
{
    std::size_t ret = 0;
    
    if (start != nullptr)
    {
        TreeNode * currentNode = start;

        htd::index_t currentIndex = 0;

        std::stack<std::pair<TreeNode *, htd::index_t>> parentStack;

        while (parentStack.size() > 0 || currentNode != nullptr)
        {
            if (currentNode != nullptr)
            {
                ret++;
                
                if (currentIndex < currentNode->children.size())
                {
                    parentStack.push(std::make_pair(currentNode, currentIndex + 1));

                    currentNode = nodes_[currentNode->children[currentIndex]];

                    currentIndex = 0;
                }
                else
                {
                    currentNode = nullptr;
                }
            }
            else
            {
                currentNode = parentStack.top().first;

                currentIndex = parentStack.top().second;

                parentStack.pop();
            }
        }
    }
    
    return ret;
}

void htd::TreeDecomposition::deleteSubtree(htd::TreeDecomposition::TreeNode * start)
{
    if (start != nullptr)
    {
        TreeNode * lastNode = nullptr;

        TreeNode * peekNode = nullptr;

        TreeNode * currentNode = start;

        htd::index_t lastIndex = 0;

        htd::index_t peekIndex = 0;

        htd::index_t currentIndex = 0;
        
        std::stack<std::pair<TreeNode *, htd::index_t>> parentStack;

        if (currentNode != nullptr)
        {
            currentIndex = currentNode->children.size() - 1;
        }
        
        while (parentStack.size() > 0 || currentNode != nullptr)
        {
            if (currentNode != nullptr)
            {
                if (currentIndex < currentNode->children.size())
                {
                    parentStack.push(std::make_pair(currentNode, currentIndex));

                    currentNode = nodes_[currentNode->children[currentIndex]];
                    
                    currentIndex = currentNode->children.size() - 1;
                }
                else
                {
                    if (parentStack.size() > 0 && parentStack.top().first != nullptr)
                    {
                        deleteNode(currentNode);
                        
                        parentStack.top().second--;
                    }
                    else
                    {
                        removeRoot();
                    }
                    
                    currentNode = nullptr;
                }
            }
            else
            {
                peekNode = parentStack.top().first;
                peekIndex = parentStack.top().second;
                
                if (peekIndex < peekNode->children.size() && !(lastNode == peekNode && lastIndex == peekIndex))
                {
                    currentNode = nodes_[peekNode->children[peekIndex]];
                        
                    currentIndex = currentNode->children.size() - 1;
                    
                    parentStack.top().second--;
                }
                else
                {
                    lastNode = peekNode;
                    lastIndex = peekIndex;
                    
                    currentNode = nullptr;
                    
                    parentStack.pop();
                    
                    if (parentStack.size() > 0 && parentStack.top().first != nullptr)
                    {
                        deleteNode(peekNode);
                        
                        parentStack.top().second--;
                    }
                    else
                    {        
                        removeRoot();
                    }
                }
            }
        }
    }
}

void htd::TreeDecomposition::deleteNode(TreeNode * node)
{
    if (node != nullptr)
    {
        auto& parent = node->parent;
        
        htd::id_t nodeIdentifier = node->id;
                
        if (parent != htd::Vertex::UNKNOWN)
        {
            auto& children = nodes_[parent - htd::Vertex::FIRST]->children;

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

                    for (auto& labeling : *labelings_)
                    {
                        labeling.second->removeLabel(nodeIdentifier);
                    }

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

            for (auto& labeling : *labelings_)
            {
                labeling.second->removeLabel(nodeIdentifier);
            }

            if (nodes_[nodeIdentifier - htd::Vertex::FIRST] != nullptr)
            {
                delete nodes_[nodeIdentifier - htd::Vertex::FIRST];

                nodes_[nodeIdentifier - htd::Vertex::FIRST] = nullptr;

                vertices_.erase(std::lower_bound(vertices_.begin(), vertices_.end(), nodeIdentifier));
            }
        }
    }
}

void htd::TreeDecomposition::swapLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        labelings_->swapLabels(vertex1, vertex2);
    }
}

void htd::TreeDecomposition::swapLabels(const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    if (isEdge(edge1) && isEdge(edge2))
    {
        labelings_->swapLabels(edge1, edge2);
    }
}

void htd::TreeDecomposition::swapLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    if (isVertex(vertex1) && isVertex(vertex2))
    {
        if (labelings_->isLabelingName(labelName))
        {
            (*labelings_)[labelName].swapLabels(vertex1, vertex2);
        }
    }
}

void htd::TreeDecomposition::swapLabel(const std::string & labelName, const htd::hyperedge_t & edge1, const htd::hyperedge_t & edge2)
{
    if (isEdge(edge1) && isEdge(edge2))
    {
        if (labelings_->isLabelingName(labelName))
        {
            (*labelings_)[labelName].swapLabels(edge1, edge2);
        }
    }
}

htd::TreeDecomposition * htd::TreeDecomposition::clone(void) const
{
    return new TreeDecomposition(*this);
}

#endif /* HTD_HTD_TREEDECOMPOSITION_CPP */
