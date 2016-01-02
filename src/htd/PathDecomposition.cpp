/* 
 * File:   PathDecomposition.cpp
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

#ifndef HTD_HTD_PATHDECOMPOSITION_CPP
#define	HTD_HTD_PATHDECOMPOSITION_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/PathDecomposition.hpp>
#include <htd/TreeDecompositionFactory.hpp>

//TODO Remove
#include <iostream>

htd::PathDecomposition::PathDecomposition(void) : base_(htd::TreeDecompositionFactory::instance().getTreeDecomposition())
{

}

htd::PathDecomposition::PathDecomposition(const htd::PathDecomposition & original) : base_(original.base_->clone())
{

}

htd::PathDecomposition::PathDecomposition(const htd::IPathDecomposition & original) : base_(htd::TreeDecompositionFactory::instance().getTreeDecomposition())
{
    if (original.vertexCount() > 0)
    {
        htd::vertex_t currentVertex = original.root();

        htd::vertex_t insertedVertex = base_->insertRoot();

        while (original.childCount(currentVertex) > 0)
        {
            currentVertex = original.child(currentVertex);

            insertedVertex = base_->addChild(insertedVertex);
        }
    }
}

htd::PathDecomposition::~PathDecomposition()
{
    if (base_ != nullptr)
    {
        delete base_;

        base_ = nullptr;
    }
}

std::size_t htd::PathDecomposition::vertexCount(void) const
{
    return base_->vertexCount();
}

std::size_t htd::PathDecomposition::edgeCount(void) const
{
    return base_->edgeCount();
}

std::size_t htd::PathDecomposition::edgeCount(htd::vertex_t vertex) const
{
    return base_->edgeCount(vertex);
}

bool htd::PathDecomposition::isVertex(htd::vertex_t vertex) const
{
    return base_->isVertex(vertex);
}

bool htd::PathDecomposition::isEdge(htd::id_t edgeId) const
{
    return base_->isEdge(edgeId);
}

bool htd::PathDecomposition::isEdge(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isNeighbor(vertex1, vertex2);
}

bool htd::PathDecomposition::isEdge(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->isEdge(elements);
}

htd::ConstCollection<htd::id_t> htd::PathDecomposition::associatedEdgeIds(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->associatedEdgeIds(vertex1, vertex2);
}

htd::ConstCollection<htd::id_t> htd::PathDecomposition::associatedEdgeIds(const htd::ConstCollection<htd::vertex_t> & elements) const
{
    return base_->associatedEdgeIds(elements);
}

htd::vertex_t htd::PathDecomposition::vertexAtPosition(htd::index_t index) const
{
    return base_->vertexAtPosition(index);
}

bool htd::PathDecomposition::isNeighbor(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isNeighbor(vertex1, vertex2);
}

bool htd::PathDecomposition::isConnected(void) const
{
    return edgeCount() > 0;
}

bool htd::PathDecomposition::isConnected(htd::vertex_t vertex1, htd::vertex_t vertex2) const
{
    return base_->isConnected(vertex1, vertex2);
}

std::size_t htd::PathDecomposition::neighborCount(htd::vertex_t vertex) const
{
    return base_->neighborCount(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::neighbors(htd::vertex_t vertex) const
{
    return base_->neighbors(vertex);
}

htd::vertex_t htd::PathDecomposition::neighbor(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->neighbor(vertex, index);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::vertices(void) const
{
    return base_->vertices();
}

std::size_t htd::PathDecomposition::isolatedVertexCount(void) const
{
    return base_->isolatedVertexCount();
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::isolatedVertices(void) const
{
    return base_->isolatedVertices();
}

htd::vertex_t htd::PathDecomposition::isolatedVertex(htd::index_t index) const
{
    HTD_UNUSED(index);

    throw std::out_of_range("htd::vertex_t htd::PathDecomposition::isolatedVertex(htd::index_t index) const");
}

bool htd::PathDecomposition::isIsolatedVertex(htd::vertex_t vertex) const
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("bool htd::PathDecomposition::isIsolatedVertex(htd::vertex_t) const");
    }

    return false;
}

htd::ConstCollection<htd::edge_t> htd::PathDecomposition::edges(void) const
{
    return base_->edges();
}

htd::ConstCollection<htd::edge_t> htd::PathDecomposition::edges(htd::vertex_t vertex) const
{
    return base_->edges(vertex);
}

const htd::edge_t & htd::PathDecomposition::edgeAtPosition(htd::index_t index) const
{
    return base_->edgeAtPosition(index);
}

const htd::edge_t & htd::PathDecomposition::edgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->edgeAtPosition(index, vertex);
}

htd::ConstCollection<htd::Hyperedge> htd::PathDecomposition::hyperedges(void) const
{
    return base_->hyperedges();
}

htd::ConstCollection<htd::Hyperedge> htd::PathDecomposition::hyperedges(htd::vertex_t vertex) const
{
    return base_->hyperedges(vertex);
}

const htd::Hyperedge & htd::PathDecomposition::hyperedge(htd::id_t edgeId) const
{
    return base_->hyperedge(edgeId);
}

const htd::Hyperedge & htd::PathDecomposition::hyperedgeAtPosition(htd::index_t index) const
{
    return base_->hyperedgeAtPosition(index);
}

const htd::Hyperedge & htd::PathDecomposition::hyperedgeAtPosition(htd::index_t index, htd::vertex_t vertex) const
{
    return base_->hyperedgeAtPosition(index, vertex);
}

htd::vertex_t htd::PathDecomposition::root(void) const
{
    return base_->root();
}

bool htd::PathDecomposition::isRoot(htd::vertex_t vertex) const
{
    return base_->isRoot(vertex);
}

htd::vertex_t htd::PathDecomposition::parent(htd::vertex_t vertex) const
{
    return base_->parent(vertex);
}

bool htd::PathDecomposition::isParent(htd::vertex_t vertex, htd::vertex_t parent) const
{
    return base_->isParent(vertex, parent);
}

std::size_t htd::PathDecomposition::childCount(htd::vertex_t vertex) const
{
    return base_->childCount(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::children(htd::vertex_t vertex) const
{
    return base_->children(vertex);
}

htd::vertex_t htd::PathDecomposition::child(htd::vertex_t vertex) const
{
    if (base_->childCount(vertex) == 0)
    {
        throw std::logic_error("htd::vertex_t htd::PathDecomposition::child(htd::vertex_t) const");
    }

    return base_->child(vertex, 0);
}

htd::vertex_t htd::PathDecomposition::child(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->child(vertex, index);
}

bool htd::PathDecomposition::isChild(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->isChild(vertex, child);
}

void htd::PathDecomposition::removeVertex(htd::vertex_t vertex)
{
    base_->removeVertex(vertex);
}

void htd::PathDecomposition::removeSubpath(htd::vertex_t subpathRoot)
{
    base_->removeSubtree(subpathRoot);
}

htd::vertex_t htd::PathDecomposition::insertRoot(void)
{
    return base_->insertRoot();
}

void htd::PathDecomposition::removeRoot(void)
{
    base_->removeRoot();
}

htd::vertex_t htd::PathDecomposition::addChild(htd::vertex_t vertex)
{
    if (!isVertex(vertex))
    {
        throw std::logic_error("htd::vertex_t htd::PathDecomposition::addChild(htd::vertex_t)");
    }

    const htd::ConstCollection<htd::vertex_t> & childCollection = base_->children(vertex);

    if (childCollection.size() > 0)
    {
        return base_->addParent(childCollection[0]);
    }

    return base_->addChild(vertex);
}

void htd::PathDecomposition::removeChild(htd::vertex_t vertex)
{
    if (base_->childCount(vertex) == 0)
    {
        throw std::logic_error("void htd::PathDecomposition::removeChild(htd::vertex_t)");
    }

    base_->removeChild(vertex, base_->child(vertex, 0));
}

void htd::PathDecomposition::removeChild(htd::vertex_t vertex, htd::vertex_t child)
{
    base_->removeChild(vertex, child);
}

htd::vertex_t htd::PathDecomposition::addParent(htd::vertex_t vertex)
{
    return base_->addParent(vertex);
}

void htd::PathDecomposition::setParent(htd::vertex_t vertex, htd::vertex_t newParent)
{
    base_->setParent(vertex, newParent);
}

const htd::ILabelingCollection & htd::PathDecomposition::labelings(void) const
{
    return base_->labelings();
}

std::size_t htd::PathDecomposition::labelCount(void) const
{
    return base_->labelCount();
}

htd::ConstCollection<std::string> htd::PathDecomposition::labelNames(void) const
{
    return base_->labelNames();
}

const std::string & htd::PathDecomposition::labelName(htd::index_t index) const
{
    return base_->labelName(index);
}

bool htd::PathDecomposition::isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
{
    return base_->isLabeledVertex(labelName, vertex);
}

bool htd::PathDecomposition::isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
{
    return base_->isLabeledEdge(labelName, edgeId);
}

const htd::ILabel & htd::PathDecomposition::vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
{
    return base_->vertexLabel(labelName, vertex);
}

void htd::PathDecomposition::setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
{
    base_->setVertexLabel(labelName, vertex, label);
}

void htd::PathDecomposition::removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
{
    base_->removeVertexLabel(labelName, vertex);
}

const htd::ILabel & htd::PathDecomposition::edgeLabel(const std::string & labelName, htd::id_t edgeId) const
{
    return base_->edgeLabel(labelName, edgeId);
}

void htd::PathDecomposition::setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
{
    base_->setEdgeLabel(labelName, edgeId, label);
}

void htd::PathDecomposition::removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
{
    base_->removeEdgeLabel(labelName, edgeId);
}

htd::PathDecomposition & htd::PathDecomposition::operator=(const htd::PathDecomposition & other)
{
    if (this != &other)
    {
        if (base_ != nullptr)
        {
            delete base_;
        }

        base_ = other.base_->clone();
    }
    
    return *this;
}

std::size_t htd::PathDecomposition::leafNodeCount(void) const
{
    return base_->leafNodeCount();
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::leafNodes(void) const
{
    return base_->leafNodes();
}

htd::vertex_t htd::PathDecomposition::leafNode(void) const
{
    return base_->leafNode(0);
}

htd::vertex_t htd::PathDecomposition::leafNode(htd::index_t index) const
{
    return base_->leafNode(index);
}

bool htd::PathDecomposition::isLeafNode(htd::vertex_t vertex) const
{
    return base_->isLeafNode(vertex);
}

std::size_t htd::PathDecomposition::joinNodeCount(void) const
{
    return base_->joinNodeCount();
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::joinNodes(void) const
{
    return base_->joinNodes();
}

htd::vertex_t htd::PathDecomposition::joinNode(htd::index_t index) const
{
    return base_->joinNode(index);
}

bool htd::PathDecomposition::isJoinNode(htd::vertex_t vertex) const
{
    return base_->isJoinNode(vertex);
}

std::size_t htd::PathDecomposition::forgetNodeCount(void) const
{
    return base_->forgetNodeCount();
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgetNodes(void) const
{
    return base_->forgetNodes();
}

htd::vertex_t htd::PathDecomposition::forgetNode(htd::index_t index) const
{
    return base_->forgetNode(index);
}

bool htd::PathDecomposition::isForgetNode(htd::vertex_t vertex) const
{
    return base_->isForgetNode(vertex);
}

std::size_t htd::PathDecomposition::introduceNodeCount(void) const
{
    return base_->introduceNodeCount();
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introduceNodes(void) const
{
    return base_->introduceNodes();
}

htd::vertex_t htd::PathDecomposition::introduceNode(htd::index_t index) const
{
    return base_->introduceNode(index);
}

bool htd::PathDecomposition::isIntroduceNode(htd::vertex_t vertex) const
{
    return base_->isIntroduceNode(vertex);
}

std::size_t htd::PathDecomposition::bagSize(htd::vertex_t vertex) const
{
    return base_->bagSize(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::bagContent(htd::vertex_t vertex) const
{
    return base_->bagContent(vertex);
}

void htd::PathDecomposition::setBagContent(htd::vertex_t vertex, const htd::vertex_container & content)
{
    base_->setBagContent(vertex, content);
}

void htd::PathDecomposition::setBagContent(htd::vertex_t vertex, const htd::ConstCollection<htd::vertex_t> & content)
{
    base_->setBagContent(vertex, content);
}

std::size_t htd::PathDecomposition::minimumBagSize(void) const
{
    return base_->minimumBagSize();
}

std::size_t htd::PathDecomposition::maximumBagSize(void) const
{
    return base_->maximumBagSize();
}

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex) const
{
    return base_->forgottenVertexCount(vertex);
}

std::size_t htd::PathDecomposition::forgottenVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->forgottenVertexCount(vertex, child);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex) const
{
    return base_->forgottenVertices(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::forgottenVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->forgottenVertices(vertex, child);
}

htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->forgottenVertex(vertex, index);
}

htd::vertex_t htd::PathDecomposition::forgottenVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    return base_->forgottenVertex(vertex, index, child);
}

bool htd::PathDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex) const
{
    return base_->isForgottenVertex(vertex, forgottenVertex);
}

bool htd::PathDecomposition::isForgottenVertex(htd::vertex_t vertex, htd::vertex_t forgottenVertex, htd::vertex_t child) const
{
    return base_->isForgottenVertex(vertex, forgottenVertex, child);
}

std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t vertex) const
{
    return base_->introducedVertexCount(vertex);
}

std::size_t htd::PathDecomposition::introducedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->introducedVertexCount(vertex, child);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex) const
{
    return base_->introducedVertices(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::introducedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->introducedVertices(vertex, child);
}

htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->introducedVertex(vertex, index);
}

htd::vertex_t htd::PathDecomposition::introducedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    return base_->introducedVertex(vertex, index, child);
}

bool htd::PathDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex) const
{
    return base_->isIntroducedVertex(vertex, introducedVertex);
}

bool htd::PathDecomposition::isIntroducedVertex(htd::vertex_t vertex, htd::vertex_t introducedVertex, htd::vertex_t child) const
{
    return base_->isIntroducedVertex(vertex, introducedVertex, child);
}

std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t vertex) const
{
    return base_->rememberedVertexCount(vertex);
}

std::size_t htd::PathDecomposition::rememberedVertexCount(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->rememberedVertexCount(vertex, child);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex) const
{
    return base_->rememberedVertices(vertex);
}

htd::ConstCollection<htd::vertex_t> htd::PathDecomposition::rememberedVertices(htd::vertex_t vertex, htd::vertex_t child) const
{
    return base_->rememberedVertices(vertex, child);
}

htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index) const
{
    return base_->rememberedVertex(vertex, index);
}

htd::vertex_t htd::PathDecomposition::rememberedVertex(htd::vertex_t vertex, htd::index_t index, htd::vertex_t child) const
{
    return base_->rememberedVertex(vertex, index, child);
}

bool htd::PathDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex) const
{
    return base_->isRememberedVertex(vertex, rememberedVertex);
}

bool htd::PathDecomposition::isRememberedVertex(htd::vertex_t vertex, htd::vertex_t rememberedVertex, htd::vertex_t child) const
{
    return base_->isRememberedVertex(vertex, rememberedVertex, child);
}

void htd::PathDecomposition::swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    base_->swapVertexLabels(vertex1, vertex2);
}

void htd::PathDecomposition::swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
{
    base_->swapEdgeLabels(edgeId1, edgeId2);
}

void htd::PathDecomposition::swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
{
    base_->swapVertexLabel(labelName, vertex1, vertex2);
}

void htd::PathDecomposition::swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
{
    base_->swapEdgeLabel(labelName, edgeId1, edgeId2);
}

htd::PathDecomposition * htd::PathDecomposition::clone(void) const
{
    return new PathDecomposition(*this);
}

#endif /* HTD_HTD_PATHDECOMPOSITION_CPP */
