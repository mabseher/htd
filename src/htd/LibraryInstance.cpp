/*
 * File:   LibraryInstance.cpp
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

#ifndef HTD_HTD_LIBRARYINSTANCE_CPP
#define HTD_HTD_LIBRARYINSTANCE_CPP

#include <htd/LibraryInstance.hpp>

#include <htd/ConnectedComponentAlgorithmFactory.hpp>
#include <htd/DirectedGraphFactory.hpp>
#include <htd/DirectedMultiGraphFactory.hpp>
#include <htd/GraphDecompositionAlgorithmFactory.hpp>
#include <htd/GraphDecompositionFactory.hpp>
#include <htd/GraphFactory.hpp>
#include <htd/HypergraphFactory.hpp>
#include <htd/HypertreeDecompositionAlgorithmFactory.hpp>
#include <htd/HypertreeDecompositionFactory.hpp>
#include <htd/LabeledDirectedGraphFactory.hpp>
#include <htd/LabeledDirectedMultiGraphFactory.hpp>
#include <htd/LabeledGraphFactory.hpp>
#include <htd/LabeledHypergraphFactory.hpp>
#include <htd/LabeledMultiGraphFactory.hpp>
#include <htd/LabeledMultiHypergraphFactory.hpp>
#include <htd/LabeledPathFactory.hpp>
#include <htd/LabeledTreeFactory.hpp>
#include <htd/MultiGraphFactory.hpp>
#include <htd/MultiHypergraphFactory.hpp>
#include <htd/OrderingAlgorithmFactory.hpp>
#include <htd/PathDecompositionAlgorithmFactory.hpp>
#include <htd/PathDecompositionFactory.hpp>
#include <htd/SetCoverAlgorithmFactory.hpp>
#include <htd/StronglyConnectedComponentAlgorithmFactory.hpp>
#include <htd/TreeDecompositionAlgorithmFactory.hpp>
#include <htd/TreeDecompositionFactory.hpp>
#include <htd/GraphPreprocessorFactory.hpp>
#include <htd/GraphSeparatorAlgorithmFactory.hpp>

#include <csignal>

/**
 *  Private implementation details of class htd::LibraryInstance.
 */
struct htd::LibraryInstance::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] id   The identifier of the management instance.
     */
    Implementation(htd::id_t id) : id_(id), nextHandlerId_(htd::Id::FIRST), terminated_(false)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  Initialize all factory classes corresponding to the management instance.
     *
     *  @param[in] manager   A shared pointer to the current management instance.
     */
    void initializeFactoryClasses(const htd::LibraryInstance * const manager)
    {
        HTD_ASSERT(&(*(manager->implementation_)) == this)

        multiHypergraphFactory_.reset(new htd::MultiHypergraphFactory(manager));
        hypergraphFactory_.reset(new htd::HypergraphFactory(manager));
        multiGraphFactory_.reset(new htd::MultiGraphFactory(manager));
        graphFactory_.reset(new htd::GraphFactory(manager));
        directedMultiGraphFactory_.reset(new htd::DirectedMultiGraphFactory(manager));
        directedGraphFactory_.reset(new htd::DirectedGraphFactory(manager));
        connectedComponentAlgorithmFactory_.reset(new htd::ConnectedComponentAlgorithmFactory(manager));
        graphDecompositionFactory_.reset(new htd::GraphDecompositionFactory(manager));
        hypertreeDecompositionFactory_.reset(new htd::HypertreeDecompositionFactory(manager));
        labeledDirectedGraphFactory_.reset(new htd::LabeledDirectedGraphFactory(manager));
        labeledDirectedMultiGraphFactory_.reset(new htd::LabeledDirectedMultiGraphFactory(manager));
        labeledGraphFactory_.reset(new htd::LabeledGraphFactory(manager));
        labeledHypergraphFactory_.reset(new htd::LabeledHypergraphFactory(manager));
        labeledMultiGraphFactory_.reset(new htd::LabeledMultiGraphFactory(manager));
        labeledMultiHypergraphFactory_.reset(new htd::LabeledMultiHypergraphFactory(manager));
        labeledPathFactory_.reset(new htd::LabeledPathFactory(manager));
        labeledTreeFactory_.reset(new htd::LabeledTreeFactory(manager));
        orderingAlgorithmFactory_.reset(new htd::OrderingAlgorithmFactory(manager));
        graphDecompositionAlgorithmFactory_.reset(new htd::GraphDecompositionAlgorithmFactory(manager));
        treeDecompositionAlgorithmFactory_.reset(new htd::TreeDecompositionAlgorithmFactory(manager));
        hypertreeDecompositionAlgorithmFactory_.reset(new htd::HypertreeDecompositionAlgorithmFactory(manager));
        pathDecompositionAlgorithmFactory_.reset(new htd::PathDecompositionAlgorithmFactory(manager));
        pathDecompositionFactory_.reset(new htd::PathDecompositionFactory(manager));
        setCoverAlgorithmFactory_.reset(new htd::SetCoverAlgorithmFactory(manager));
        stronglyConnectedComponentAlgorithmFactory_.reset(new htd::StronglyConnectedComponentAlgorithmFactory(manager));
        treeDecompositionFactory_.reset(new htd::TreeDecompositionFactory(manager));
        graphDecompositionFactory_.reset(new htd::GraphDecompositionFactory(manager));
        graphPreprocessorFactory_.reset(new htd::GraphPreprocessorFactory(manager));
        graphSeparatorAlgorithmFactory_.reset(new htd::GraphSeparatorAlgorithmFactory(manager));
    }

    /**
     *  The identifier of the management instance.
     */
    htd::id_t id_;

    /**
     *  The identifier which will be assigned to the next signal handler.
     */
    htd::id_t nextHandlerId_;

    /**
     *  A boolean flag indicating whether the current management instance was terminated.
     */
    bool terminated_;

    /**
     *  The factory class for the default implementation of the htd::IConnectedComponentAlgorithm interface.
     */
    std::unique_ptr<htd::ConnectedComponentAlgorithmFactory> connectedComponentAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IDirectedGraph interface.
     */
    std::unique_ptr<htd::DirectedGraphFactory> directedGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IDirectedMultiGraph interface.
     */
    std::unique_ptr<htd::DirectedMultiGraphFactory> directedMultiGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IGraphDecompositionAlgorithm interface.
     */
    std::unique_ptr<htd::GraphDecompositionAlgorithmFactory> graphDecompositionAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IGraphDecomposition interface.
     */
    std::unique_ptr<htd::GraphDecompositionFactory> graphDecompositionFactory_;

    /**
     *  The factory class for the default implementation of the htd::IGraph interface.
     */
    std::unique_ptr<htd::GraphFactory> graphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IHypergraph interface.
     */
    std::unique_ptr<htd::HypergraphFactory> hypergraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IHypertreeDecompositionAlgorithm interface.
     */
    std::unique_ptr<htd::HypertreeDecompositionAlgorithmFactory> hypertreeDecompositionAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IHypertreeDecomposition interface.
     */
    std::unique_ptr<htd::HypertreeDecompositionFactory> hypertreeDecompositionFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledDirectedGraph interface.
     */
    std::unique_ptr<htd::LabeledDirectedGraphFactory> labeledDirectedGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledDirectedMultiGraph interface.
     */
    std::unique_ptr<htd::LabeledDirectedMultiGraphFactory> labeledDirectedMultiGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledGraph interface.
     */
    std::unique_ptr<htd::LabeledGraphFactory> labeledGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledHypergraph interface.
     */
    std::unique_ptr<htd::LabeledHypergraphFactory> labeledHypergraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledMultiGraph interface.
     */
    std::unique_ptr<htd::LabeledMultiGraphFactory> labeledMultiGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledMultiHypergraph interface.
     */
    std::unique_ptr<htd::LabeledMultiHypergraphFactory> labeledMultiHypergraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledPath interface.
     */
    std::unique_ptr<htd::LabeledPathFactory> labeledPathFactory_;

    /**
     *  The factory class for the default implementation of the htd::ILabeledTree interface.
     */
    std::unique_ptr<htd::LabeledTreeFactory> labeledTreeFactory_;

    /**
     *  The factory class for the default implementation of the htd::IMultiGraph interface.
     */
    std::unique_ptr<htd::MultiGraphFactory> multiGraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IMultiHypergraph interface.
     */
    std::unique_ptr<htd::MultiHypergraphFactory> multiHypergraphFactory_;

    /**
     *  The factory class for the default implementation of the htd::IOrderingAlgorithm interface.
     */
    std::unique_ptr<htd::OrderingAlgorithmFactory> orderingAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IPathDecompositionAlgorithm interface.
     */
    std::unique_ptr<htd::PathDecompositionAlgorithmFactory> pathDecompositionAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IPathDecomposition interface.
     */
    std::unique_ptr<htd::PathDecompositionFactory> pathDecompositionFactory_;

    /**
     *  The factory class for the default implementation of the htd::ISetCoverAlgorithm interface.
     */
    std::unique_ptr<htd::SetCoverAlgorithmFactory> setCoverAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::IStronglyConnectedComponentAlgorithm interface.
     */
    std::unique_ptr<htd::StronglyConnectedComponentAlgorithmFactory> stronglyConnectedComponentAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::ITreeDecompositionAlgorithm interface.
     */
    std::unique_ptr<htd::TreeDecompositionAlgorithmFactory> treeDecompositionAlgorithmFactory_;

    /**
     *  The factory class for the default implementation of the htd::ITreeDecomposition interface.
     */
    std::unique_ptr<htd::TreeDecompositionFactory> treeDecompositionFactory_;

    /**
     *  The factory class for the default implementation of the htd::IGraphPreprocessor interface.
     */
    std::unique_ptr<htd::GraphPreprocessorFactory> graphPreprocessorFactory_;

    /**
     *  The factory class for the default implementation of the htd::IGraphSeparatorAlgorithm interface.
     */
    std::unique_ptr<htd::GraphSeparatorAlgorithmFactory> graphSeparatorAlgorithmFactory_;
};

htd::LibraryInstance::LibraryInstance(htd::id_t id) : implementation_(new Implementation(id))
{

}

htd::LibraryInstance::~LibraryInstance()
{

}

void htd::LibraryInstance::initializeFactoryClasses(const htd::LibraryInstance * const manager)
{
    implementation_->initializeFactoryClasses(manager);
}

htd::id_t htd::LibraryInstance::id(void) const
{
    return implementation_->id_;
}

bool htd::LibraryInstance::isTerminated(void) const
{
    return implementation_->terminated_;
}

void htd::LibraryInstance::terminate(void)
{
    implementation_->terminated_ = true;
}

void htd::LibraryInstance::reset(void)
{
    implementation_->terminated_ = false;
}

htd::ConnectedComponentAlgorithmFactory & htd::LibraryInstance::connectedComponentAlgorithmFactory(void)
{
    return *(implementation_->connectedComponentAlgorithmFactory_);
}

const htd::ConnectedComponentAlgorithmFactory & htd::LibraryInstance::connectedComponentAlgorithmFactory(void) const
{
    return *(implementation_->connectedComponentAlgorithmFactory_);
}

htd::DirectedGraphFactory & htd::LibraryInstance::directedGraphFactory(void)
{
    return *(implementation_->directedGraphFactory_);
}

const htd::DirectedGraphFactory & htd::LibraryInstance::directedGraphFactory(void) const
{
    return *(implementation_->directedGraphFactory_);
}

htd::DirectedMultiGraphFactory & htd::LibraryInstance::directedMultiGraphFactory(void)
{
    return *(implementation_->directedMultiGraphFactory_);
}

const htd::DirectedMultiGraphFactory & htd::LibraryInstance::directedMultiGraphFactory(void) const
{
    return *(implementation_->directedMultiGraphFactory_);
}

htd::GraphDecompositionAlgorithmFactory & htd::LibraryInstance::graphDecompositionAlgorithmFactory(void)
{
    return *(implementation_->graphDecompositionAlgorithmFactory_);
}

const htd::GraphDecompositionAlgorithmFactory & htd::LibraryInstance::graphDecompositionAlgorithmFactory(void) const
{
    return *(implementation_->graphDecompositionAlgorithmFactory_);
}

htd::GraphDecompositionFactory & htd::LibraryInstance::graphDecompositionFactory(void)
{
    return *(implementation_->graphDecompositionFactory_);
}

const htd::GraphDecompositionFactory & htd::LibraryInstance::graphDecompositionFactory(void) const
{
    return *(implementation_->graphDecompositionFactory_);
}

htd::GraphFactory & htd::LibraryInstance::graphFactory(void)
{
    return *(implementation_->graphFactory_);
}

const htd::GraphFactory & htd::LibraryInstance::graphFactory(void) const
{
    return *(implementation_->graphFactory_);
}

htd::HypergraphFactory & htd::LibraryInstance::hypergraphFactory(void)
{
    return *(implementation_->hypergraphFactory_);
}

const htd::HypergraphFactory & htd::LibraryInstance::hypergraphFactory(void) const
{
    return *(implementation_->hypergraphFactory_);
}

htd::HypertreeDecompositionAlgorithmFactory & htd::LibraryInstance::hypertreeDecompositionAlgorithmFactory(void)
{
    return *(implementation_->hypertreeDecompositionAlgorithmFactory_);
}

const htd::HypertreeDecompositionAlgorithmFactory & htd::LibraryInstance::hypertreeDecompositionAlgorithmFactory(void) const
{
    return *(implementation_->hypertreeDecompositionAlgorithmFactory_);
}

htd::HypertreeDecompositionFactory & htd::LibraryInstance::hypertreeDecompositionFactory(void)
{
    return *(implementation_->hypertreeDecompositionFactory_);
}

const htd::HypertreeDecompositionFactory & htd::LibraryInstance::hypertreeDecompositionFactory(void) const
{
    return *(implementation_->hypertreeDecompositionFactory_);
}

htd::LabeledDirectedGraphFactory & htd::LibraryInstance::labeledDirectedGraphFactory(void)
{
    return *(implementation_->labeledDirectedGraphFactory_);
}

const htd::LabeledDirectedGraphFactory & htd::LibraryInstance::labeledDirectedGraphFactory(void) const
{
    return *(implementation_->labeledDirectedGraphFactory_);
}

htd::LabeledDirectedMultiGraphFactory & htd::LibraryInstance::labeledDirectedMultiGraphFactory(void)
{
    return *(implementation_->labeledDirectedMultiGraphFactory_);
}

const htd::LabeledDirectedMultiGraphFactory & htd::LibraryInstance::labeledDirectedMultiGraphFactory(void) const
{
    return *(implementation_->labeledDirectedMultiGraphFactory_);
}

htd::LabeledGraphFactory & htd::LibraryInstance::labeledGraphFactory(void)
{
    return *(implementation_->labeledGraphFactory_);
}

const htd::LabeledGraphFactory & htd::LibraryInstance::labeledGraphFactory(void) const
{
    return *(implementation_->labeledGraphFactory_);
}

htd::LabeledHypergraphFactory & htd::LibraryInstance::labeledHypergraphFactory(void)
{
    return *(implementation_->labeledHypergraphFactory_);
}

const htd::LabeledHypergraphFactory & htd::LibraryInstance::labeledHypergraphFactory(void) const
{
    return *(implementation_->labeledHypergraphFactory_);
}

htd::LabeledMultiGraphFactory & htd::LibraryInstance::labeledMultiGraphFactory(void)
{
    return *(implementation_->labeledMultiGraphFactory_);
}

const htd::LabeledMultiGraphFactory & htd::LibraryInstance::labeledMultiGraphFactory(void) const
{
    return *(implementation_->labeledMultiGraphFactory_);
}

htd::LabeledMultiHypergraphFactory & htd::LibraryInstance::labeledMultiHypergraphFactory(void)
{
    return *(implementation_->labeledMultiHypergraphFactory_);
}

const htd::LabeledMultiHypergraphFactory & htd::LibraryInstance::labeledMultiHypergraphFactory(void) const
{
    return *(implementation_->labeledMultiHypergraphFactory_);
}

htd::LabeledPathFactory & htd::LibraryInstance::labeledPathFactory(void)
{
    return *(implementation_->labeledPathFactory_);
}

const htd::LabeledPathFactory & htd::LibraryInstance::labeledPathFactory(void) const
{
    return *(implementation_->labeledPathFactory_);
}

htd::LabeledTreeFactory & htd::LibraryInstance::labeledTreeFactory(void)
{
    return *(implementation_->labeledTreeFactory_);
}

const htd::LabeledTreeFactory & htd::LibraryInstance::labeledTreeFactory(void) const
{
    return *(implementation_->labeledTreeFactory_);
}

htd::MultiGraphFactory & htd::LibraryInstance::multiGraphFactory(void)
{
    return *(implementation_->multiGraphFactory_);
}

const htd::MultiGraphFactory & htd::LibraryInstance::multiGraphFactory(void) const
{
    return *(implementation_->multiGraphFactory_);
}

htd::MultiHypergraphFactory & htd::LibraryInstance::multiHypergraphFactory(void)
{
    return *(implementation_->multiHypergraphFactory_);
}

const htd::MultiHypergraphFactory & htd::LibraryInstance::multiHypergraphFactory(void) const
{
    return *(implementation_->multiHypergraphFactory_);
}

htd::OrderingAlgorithmFactory & htd::LibraryInstance::orderingAlgorithmFactory(void)
{
    return *(implementation_->orderingAlgorithmFactory_);
}

const htd::OrderingAlgorithmFactory & htd::LibraryInstance::orderingAlgorithmFactory(void) const
{
    return *(implementation_->orderingAlgorithmFactory_);
}

htd::PathDecompositionAlgorithmFactory & htd::LibraryInstance::pathDecompositionAlgorithmFactory(void)
{
    return *(implementation_->pathDecompositionAlgorithmFactory_);
}

const htd::PathDecompositionAlgorithmFactory & htd::LibraryInstance::pathDecompositionAlgorithmFactory(void) const
{
    return *(implementation_->pathDecompositionAlgorithmFactory_);
}

htd::PathDecompositionFactory & htd::LibraryInstance::pathDecompositionFactory(void)
{
    return *(implementation_->pathDecompositionFactory_);
}

const htd::PathDecompositionFactory & htd::LibraryInstance::pathDecompositionFactory(void) const
{
    return *(implementation_->pathDecompositionFactory_);
}

htd::SetCoverAlgorithmFactory & htd::LibraryInstance::setCoverAlgorithmFactory(void)
{
    return *(implementation_->setCoverAlgorithmFactory_);
}

const htd::SetCoverAlgorithmFactory & htd::LibraryInstance::setCoverAlgorithmFactory(void) const
{
    return *(implementation_->setCoverAlgorithmFactory_);
}

htd::StronglyConnectedComponentAlgorithmFactory & htd::LibraryInstance::stronglyConnectedComponentAlgorithmFactory(void)
{
    return *(implementation_->stronglyConnectedComponentAlgorithmFactory_);
}

const htd::StronglyConnectedComponentAlgorithmFactory & htd::LibraryInstance::stronglyConnectedComponentAlgorithmFactory(void) const
{
    return *(implementation_->stronglyConnectedComponentAlgorithmFactory_);
}

htd::TreeDecompositionAlgorithmFactory & htd::LibraryInstance::treeDecompositionAlgorithmFactory(void)
{
    return *(implementation_->treeDecompositionAlgorithmFactory_);
}

const htd::TreeDecompositionAlgorithmFactory & htd::LibraryInstance::treeDecompositionAlgorithmFactory(void) const
{
    return *(implementation_->treeDecompositionAlgorithmFactory_);
}

htd::TreeDecompositionFactory & htd::LibraryInstance::treeDecompositionFactory(void)
{
    return *(implementation_->treeDecompositionFactory_);
}

const htd::TreeDecompositionFactory & htd::LibraryInstance::treeDecompositionFactory(void) const
{
    return *(implementation_->treeDecompositionFactory_);
}

htd::GraphPreprocessorFactory & htd::LibraryInstance::graphPreprocessorFactory(void)
{
    return *(implementation_->graphPreprocessorFactory_);
}

const htd::GraphPreprocessorFactory & htd::LibraryInstance::graphPreprocessorFactory(void) const
{
    return *(implementation_->graphPreprocessorFactory_);
}

htd::GraphSeparatorAlgorithmFactory & htd::LibraryInstance::graphSeparatorAlgorithmFactory(void)
{
    return *(implementation_->graphSeparatorAlgorithmFactory_);
}

const htd::GraphSeparatorAlgorithmFactory & htd::LibraryInstance::graphSeparatorAlgorithmFactory(void) const
{
    return *(implementation_->graphSeparatorAlgorithmFactory_);
}

#endif /* HTD_HTD_LIBRARYINSTANCE_CPP */
