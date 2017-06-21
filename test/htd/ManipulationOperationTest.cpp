/*
 * File:   ManipulationOperationTest.cpp
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

#include <gtest/gtest.h>

#include <htd/main.hpp>

#include <utility>
#include <vector>

class ManipulationOperationTest : public ::testing::Test
{
    public:
        ManipulationOperationTest(void)
        {

        }

        virtual ~ManipulationOperationTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

class BagSizeLabelingFunction : public htd::ILabelingFunction
{
    public:
        BagSizeLabelingFunction(const htd::LibraryInstance * const manager) : managementInstance_(manager)
        {

        }

        virtual ~BagSizeLabelingFunction()
        {

        }

        std::string name() const HTD_OVERRIDE
        {
            return "BAG_SIZE";
        }

        htd::ILabel * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels)

            return new htd::Label<std::size_t>(vertices.size());
        }

        htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels)

            return new htd::Label<std::size_t>(vertices.size());
        }

        const htd::LibraryInstance * managementInstance(void) const HTD_NOEXCEPT HTD_OVERRIDE
        {
            return managementInstance_;
        }

        void setManagementInstance(const htd::LibraryInstance * const manager) HTD_OVERRIDE
        {
            HTD_ASSERT(manager != nullptr)

            managementInstance_ = manager;
        }

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
        BagSizeLabelingFunction * clone(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction(managementInstance_);
        }
#else
        BagSizeLabelingFunction * clone(void) const
        {
            return new BagSizeLabelingFunction(managementInstance_);
        }

        htd::ILabelingFunction * cloneLabelingFunction(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction(managementInstance_);
        }

        htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction(managementInstance_);
        }
#endif

    private:
        const htd::LibraryInstance * managementInstance_;
};

class FitnessFunction : public htd::ITreeDecompositionFitnessFunction
{
    public:
        FitnessFunction(void)
        {

        }

        ~FitnessFunction()
        {

        }

        htd::FitnessEvaluation * fitness(const htd::IMultiHypergraph & graph,
                                         const htd::ITreeDecomposition & decomposition) const
        {
            HTD_UNUSED(graph)

            return new htd::FitnessEvaluation(1,
                                              -(double)(decomposition.height()));
        }

        FitnessFunction * clone(void) const
        {
            return new FitnessFunction();
        }
};

htd::IMultiHypergraph * createInputGraph(const htd::LibraryInstance * const libraryInstance)
{
    htd::MultiHypergraph * graph = new htd::MultiHypergraph(libraryInstance, 50);

    graph->addEdge(1,35);
    graph->addEdge(1,50);
    graph->addEdge(1,47);
    graph->addEdge(1,22);
    graph->addEdge(1,44);
    graph->addEdge(1,7);
    graph->addEdge(1,19);
    graph->addEdge(1,30);
    graph->addEdge(2,42);
    graph->addEdge(2,5);
    graph->addEdge(2,9);
    graph->addEdge(2,20);
    graph->addEdge(2,13);
    graph->addEdge(2,6);
    graph->addEdge(2,48);
    graph->addEdge(2,18);
    graph->addEdge(2,37);
    graph->addEdge(2,38);
    graph->addEdge(2,14);
    graph->addEdge(2,26);
    graph->addEdge(3,40);
    graph->addEdge(3,46);
    graph->addEdge(3,9);
    graph->addEdge(3,12);
    graph->addEdge(3,47);
    graph->addEdge(3,39);
    graph->addEdge(3,30);
    graph->addEdge(4,20);
    graph->addEdge(4,48);
    graph->addEdge(4,47);
    graph->addEdge(4,29);
    graph->addEdge(4,43);
    graph->addEdge(4,14);
    graph->addEdge(4,30);
    graph->addEdge(5,15);
    graph->addEdge(5,35);
    graph->addEdge(5,6);
    graph->addEdge(5,12);
    graph->addEdge(5,31);
    graph->addEdge(5,28);
    graph->addEdge(5,47);
    graph->addEdge(5,10);
    graph->addEdge(6,15);
    graph->addEdge(6,21);
    graph->addEdge(6,23);
    graph->addEdge(6,50);
    graph->addEdge(6,8);
    graph->addEdge(6,18);
    graph->addEdge(6,41);
    graph->addEdge(6,44);
    graph->addEdge(6,7);
    graph->addEdge(7,13);
    graph->addEdge(7,48);
    graph->addEdge(7,33);
    graph->addEdge(7,45);
    graph->addEdge(7,4);
    graph->addEdge(7,10);
    graph->addEdge(7,29);
    graph->addEdge(7,19);
    graph->addEdge(7,25);
    graph->addEdge(7,27);
    graph->addEdge(8,42);
    graph->addEdge(8,20);
    graph->addEdge(8,21);
    graph->addEdge(8,50);
    graph->addEdge(8,37);
    graph->addEdge(8,22);
    graph->addEdge(8,39);
    graph->addEdge(8,30);
    graph->addEdge(9,35);
    graph->addEdge(9,42);
    graph->addEdge(9,5);
    graph->addEdge(9,21);
    graph->addEdge(9,6);
    graph->addEdge(9,11);
    graph->addEdge(9,24);
    graph->addEdge(9,34);
    graph->addEdge(9,3);
    graph->addEdge(9,17);
    graph->addEdge(10,15);
    graph->addEdge(10,9);
    graph->addEdge(10,13);
    graph->addEdge(10,6);
    graph->addEdge(10,33);
    graph->addEdge(10,47);
    graph->addEdge(10,34);
    graph->addEdge(10,22);
    graph->addEdge(10,39);
    graph->addEdge(10,7);
    graph->addEdge(10,49);
    graph->addEdge(10,27);
    graph->addEdge(11,12);
    graph->addEdge(11,41);
    graph->addEdge(11,14);
    graph->addEdge(11,36);
    graph->addEdge(11,30);
    graph->addEdge(12,40);
    graph->addEdge(12,5);
    graph->addEdge(12,32);
    graph->addEdge(12,24);
    graph->addEdge(12,50);
    graph->addEdge(12,31);
    graph->addEdge(12,8);
    graph->addEdge(12,4);
    graph->addEdge(12,29);
    graph->addEdge(12,49);
    graph->addEdge(12,27);
    graph->addEdge(13,46);
    graph->addEdge(13,6);
    graph->addEdge(13,11);
    graph->addEdge(13,12);
    graph->addEdge(13,31);
    graph->addEdge(13,45);
    graph->addEdge(13,37);
    graph->addEdge(13,22);
    graph->addEdge(13,49);
    graph->addEdge(14,40);
    graph->addEdge(14,32);
    graph->addEdge(14,12);
    graph->addEdge(14,16);
    graph->addEdge(14,18);
    graph->addEdge(14,34);
    graph->addEdge(14,36);
    graph->addEdge(15,21);
    graph->addEdge(15,6);
    graph->addEdge(15,11);
    graph->addEdge(15,16);
    graph->addEdge(15,31);
    graph->addEdge(15,48);
    graph->addEdge(15,4);
    graph->addEdge(15,18);
    graph->addEdge(15,34);
    graph->addEdge(15,41);
    graph->addEdge(15,43);
    graph->addEdge(15,49);
    graph->addEdge(16,42);
    graph->addEdge(16,5);
    graph->addEdge(16,20);
    graph->addEdge(16,50);
    graph->addEdge(16,47);
    graph->addEdge(16,39);
    graph->addEdge(16,2);
    graph->addEdge(16,7);
    graph->addEdge(16,13);
    graph->addEdge(16,34);
    graph->addEdge(16,43);
    graph->addEdge(16,49);
    graph->addEdge(16,14);
    graph->addEdge(17,20);
    graph->addEdge(17,21);
    graph->addEdge(17,24);
    graph->addEdge(17,50);
    graph->addEdge(17,16);
    graph->addEdge(17,33);
    graph->addEdge(17,37);
    graph->addEdge(17,7);
    graph->addEdge(17,43);
    graph->addEdge(17,49);
    graph->addEdge(17,25);
    graph->addEdge(18,40);
    graph->addEdge(18,9);
    graph->addEdge(18,24);
    graph->addEdge(18,12);
    graph->addEdge(18,48);
    graph->addEdge(18,34);
    graph->addEdge(18,10);
    graph->addEdge(18,19);
    graph->addEdge(18,14);
    graph->addEdge(18,36);
    graph->addEdge(19,8);
    graph->addEdge(19,45);
    graph->addEdge(19,4);
    graph->addEdge(19,1);
    graph->addEdge(19,39);
    graph->addEdge(19,7);
    graph->addEdge(19,23);
    graph->addEdge(19,13);
    graph->addEdge(19,11);
    graph->addEdge(19,12);
    graph->addEdge(19,10);
    graph->addEdge(19,29);
    graph->addEdge(19,3);
    graph->addEdge(20,46);
    graph->addEdge(20,13);
    graph->addEdge(20,6);
    graph->addEdge(20,24);
    graph->addEdge(20,33);
    graph->addEdge(20,47);
    graph->addEdge(20,41);
    graph->addEdge(20,44);
    graph->addEdge(20,43);
    graph->addEdge(20,3);
    graph->addEdge(21,11);
    graph->addEdge(21,22);
    graph->addEdge(21,29);
    graph->addEdge(21,43);
    graph->addEdge(21,14);
    graph->addEdge(21,26);
    graph->addEdge(21,17);
    graph->addEdge(22,42);
    graph->addEdge(22,32);
    graph->addEdge(22,24);
    graph->addEdge(22,33);
    graph->addEdge(22,45);
    graph->addEdge(22,47);
    graph->addEdge(22,4);
    graph->addEdge(22,38);
    graph->addEdge(22,44);
    graph->addEdge(22,36);
    graph->addEdge(23,40);
    graph->addEdge(23,9);
    graph->addEdge(23,21);
    graph->addEdge(23,31);
    graph->addEdge(23,28);
    graph->addEdge(23,45);
    graph->addEdge(23,47);
    graph->addEdge(23,38);
    graph->addEdge(23,7);
    graph->addEdge(23,36);
    graph->addEdge(23,17);
    graph->addEdge(24,21);
    graph->addEdge(24,50);
    graph->addEdge(24,8);
    graph->addEdge(24,33);
    graph->addEdge(24,34);
    graph->addEdge(24,10);
    graph->addEdge(24,43);
    graph->addEdge(24,49);
    graph->addEdge(24,36);
    graph->addEdge(24,30);
    graph->addEdge(25,5);
    graph->addEdge(25,9);
    graph->addEdge(25,21);
    graph->addEdge(25,4);
    graph->addEdge(25,1);
    graph->addEdge(25,22);
    graph->addEdge(25,17);
    graph->addEdge(25,35);
    graph->addEdge(25,40);
    graph->addEdge(25,23);
    graph->addEdge(25,10);
    graph->addEdge(25,43);
    graph->addEdge(25,3);
    graph->addEdge(26,40);
    graph->addEdge(26,9);
    graph->addEdge(26,20);
    graph->addEdge(26,23);
    graph->addEdge(26,29);
    graph->addEdge(26,44);
    graph->addEdge(26,2);
    graph->addEdge(26,49);
    graph->addEdge(26,17);
    graph->addEdge(27,15);
    graph->addEdge(27,6);
    graph->addEdge(27,24);
    graph->addEdge(27,28);
    graph->addEdge(27,45);
    graph->addEdge(27,4);
    graph->addEdge(27,2);
    graph->addEdge(27,19);
    graph->addEdge(27,14);
    graph->addEdge(27,30);
    graph->addEdge(28,15);
    graph->addEdge(28,20);
    graph->addEdge(28,50);
    graph->addEdge(28,12);
    graph->addEdge(28,48);
    graph->addEdge(28,29);
    graph->addEdge(28,41);
    graph->addEdge(28,38);
    graph->addEdge(28,43);
    graph->addEdge(28,36);
    graph->addEdge(28,17);
    graph->addEdge(29,20);
    graph->addEdge(29,21);
    graph->addEdge(29,32);
    graph->addEdge(29,28);
    graph->addEdge(29,33);
    graph->addEdge(29,45);
    graph->addEdge(29,47);
    graph->addEdge(29,1);
    graph->addEdge(29,43);
    graph->addEdge(29,3);
    graph->addEdge(29,17);
    graph->addEdge(30,40);
    graph->addEdge(30,5);
    graph->addEdge(30,23);
    graph->addEdge(30,11);
    graph->addEdge(30,8);
    graph->addEdge(30,47);
    graph->addEdge(30,1);
    graph->addEdge(30,2);
    graph->addEdge(30,43);
    graph->addEdge(30,36);
    graph->addEdge(30,25);
    graph->addEdge(31,15);
    graph->addEdge(31,9);
    graph->addEdge(31,20);
    graph->addEdge(31,21);
    graph->addEdge(31,28);
    graph->addEdge(31,47);
    graph->addEdge(31,1);
    graph->addEdge(31,39);
    graph->addEdge(31,7);
    graph->addEdge(31,17);
    graph->addEdge(31,32);
    graph->addEdge(31,12);
    graph->addEdge(31,30);
    graph->addEdge(32,42);
    graph->addEdge(32,11);
    graph->addEdge(32,12);
    graph->addEdge(32,1);
    graph->addEdge(32,38);
    graph->addEdge(32,14);
    graph->addEdge(32,3);
    graph->addEdge(33,42);
    graph->addEdge(33,5);
    graph->addEdge(33,11);
    graph->addEdge(33,47);
    graph->addEdge(33,37);
    graph->addEdge(33,44);
    graph->addEdge(33,30);
    graph->addEdge(34,46);
    graph->addEdge(34,16);
    graph->addEdge(34,18);
    graph->addEdge(34,29);
    graph->addEdge(34,36);
    graph->addEdge(34,3);
    graph->addEdge(35,42);
    graph->addEdge(35,5);
    graph->addEdge(35,21);
    graph->addEdge(35,28);
    graph->addEdge(35,45);
    graph->addEdge(35,47);
    graph->addEdge(35,4);
    graph->addEdge(35,44);
    graph->addEdge(35,7);
    graph->addEdge(35,17);
    graph->addEdge(35,16);
    graph->addEdge(35,34);
    graph->addEdge(35,14);
    graph->addEdge(36,35);
    graph->addEdge(36,5);
    graph->addEdge(36,47);
    graph->addEdge(36,34);
    graph->addEdge(36,1);
    graph->addEdge(36,29);
    graph->addEdge(36,38);
    graph->addEdge(36,14);
    graph->addEdge(36,25);
    graph->addEdge(36,30);
    graph->addEdge(37,15);
    graph->addEdge(37,40);
    graph->addEdge(37,46);
    graph->addEdge(37,9);
    graph->addEdge(37,50);
    graph->addEdge(37,29);
    graph->addEdge(37,49);
    graph->addEdge(37,30);
    graph->addEdge(38,15);
    graph->addEdge(38,31);
    graph->addEdge(38,48);
    graph->addEdge(38,45);
    graph->addEdge(38,47);
    graph->addEdge(38,4);
    graph->addEdge(38,1);
    graph->addEdge(38,23);
    graph->addEdge(38,13);
    graph->addEdge(38,24);
    graph->addEdge(38,16);
    graph->addEdge(38,18);
    graph->addEdge(38,14);
    graph->addEdge(39,8);
    graph->addEdge(39,47);
    graph->addEdge(39,4);
    graph->addEdge(39,34);
    graph->addEdge(39,10);
    graph->addEdge(39,19);
    graph->addEdge(39,14);
    graph->addEdge(40,42);
    graph->addEdge(40,31);
    graph->addEdge(40,48);
    graph->addEdge(40,47);
    graph->addEdge(40,4);
    graph->addEdge(40,39);
    graph->addEdge(40,19);
    graph->addEdge(40,49);
    graph->addEdge(40,14);
    graph->addEdge(40,30);
    graph->addEdge(41,21);
    graph->addEdge(41,23);
    graph->addEdge(41,13);
    graph->addEdge(41,16);
    graph->addEdge(41,31);
    graph->addEdge(41,45);
    graph->addEdge(41,2);
    graph->addEdge(41,7);
    graph->addEdge(41,26);
    graph->addEdge(42,23);
    graph->addEdge(42,6);
    graph->addEdge(42,8);
    graph->addEdge(42,37);
    graph->addEdge(42,22);
    graph->addEdge(42,36);
    graph->addEdge(42,17);
    graph->addEdge(43,35);
    graph->addEdge(43,20);
    graph->addEdge(43,6);
    graph->addEdge(43,31);
    graph->addEdge(44,15);
    graph->addEdge(44,31);
    graph->addEdge(44,4);
    graph->addEdge(44,1);
    graph->addEdge(44,41);
    graph->addEdge(44,38);
    graph->addEdge(44,49);
    graph->addEdge(44,14);
    graph->addEdge(45,20);
    graph->addEdge(45,11);
    graph->addEdge(45,24);
    graph->addEdge(45,12);
    graph->addEdge(45,31);
    graph->addEdge(45,10);
    graph->addEdge(45,38);
    graph->addEdge(46,35);
    graph->addEdge(46,18);
    graph->addEdge(46,29);
    graph->addEdge(46,41);
    graph->addEdge(46,19);
    graph->addEdge(47,24);
    graph->addEdge(47,50);
    graph->addEdge(47,10);
    graph->addEdge(47,49);
    graph->addEdge(47,25);
    graph->addEdge(48,9);
    graph->addEdge(48,20);
    graph->addEdge(48,6);
    graph->addEdge(48,10);
    graph->addEdge(48,7);
    graph->addEdge(48,25);
    graph->addEdge(48,26);
    graph->addEdge(48,3);
    graph->addEdge(49,20);
    graph->addEdge(49,21);
    graph->addEdge(49,23);
    graph->addEdge(49,24);
    graph->addEdge(49,50);
    graph->addEdge(49,12);
    graph->addEdge(49,31);
    graph->addEdge(49,38);
    graph->addEdge(49,19);
    graph->addEdge(50,42);
    graph->addEdge(50,32);
    graph->addEdge(50,16);
    graph->addEdge(50,22);
    graph->addEdge(50,41);
    graph->addEdge(50,2);
    graph->addEdge(50,14);
    graph->addEdge(50,26);

    return graph;
}

std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> computeTreeDecomposition(const htd::LibraryInstance * const libraryInstance, const std::vector<htd::IDecompositionManipulationOperation *> & operations = std::vector<htd::IDecompositionManipulationOperation *>())
{
    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm algorithm(libraryInstance);

    return std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *>(graph, dynamic_cast<htd::IMutableTreeDecomposition *>(algorithm.computeDecomposition(*graph, operations)));
}

std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> computePathDecomposition(const htd::LibraryInstance * const libraryInstance, const std::vector<htd::IDecompositionManipulationOperation *> & operations = std::vector<htd::IDecompositionManipulationOperation *>())
{
    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::PostProcessingPathDecompositionAlgorithm algorithm(libraryInstance);

    return std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *>(graph, dynamic_cast<htd::IMutablePathDecomposition *>(algorithm.computeDecomposition(*graph, operations)));
}

bool isValidInducedEdgeLabel(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, const std::string & labelName, htd::vertex_t vertex)
{
    bool ret = true;

    HTD_ASSERT(decomposition.isVertex(vertex))

    const std::vector<htd::vertex_t> & bag = decomposition.bagContent(vertex);

    std::vector<htd::Hyperedge> requiredEdges;

    const std::vector<htd::Hyperedge> & coveringEdges =
        htd::accessLabel<std::vector<htd::Hyperedge>>(decomposition.vertexLabel(labelName, vertex));

    for (const htd::Hyperedge & edge : graph.hyperedges())
    {
        const std::vector<htd::vertex_t> & elements = edge.sortedElements();

        if (std::includes(bag.begin(), bag.end(), elements.begin(), elements.end()))
        {
            requiredEdges.push_back(edge);

            ret = false;

            for (auto it = coveringEdges.begin(); !ret && it != coveringEdges.end(); ++it)
            {
                ret = it->id() == edge.id() && it->elements() == edge.elements() && it->sortedElements() == edge.sortedElements();
            }
        }

        if (ret == false)
        {
            continue;
        }
    }

    for (const htd::Hyperedge & edge : coveringEdges)
    {
        ret = false;

        for (auto it = requiredEdges.begin(); !ret && it != requiredEdges.end(); ++it)
        {
            ret = it->id() == edge.id() && it->elements() == edge.elements() && it->sortedElements() == edge.sortedElements();
        }

        if (ret == false)
        {
            continue;
        }
    }

    return ret;
}

bool isValidInducedEdgeLabel(const htd::IMultiHypergraph & graph, const htd::ITreeDecomposition & decomposition, const std::string & labelName)
{
    bool ret = true;

    for (htd::vertex_t vertex : decomposition.vertices())
    {
        ret = isValidInducedEdgeLabel(graph, decomposition, labelName, vertex);

        if (ret == false)
        {
            continue;
        }
    }

    return ret;
}

TEST(ManipulationOperationTest, CheckLimitChildCountOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    std::size_t maxChildCount = 0;

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        std::size_t childCount = decomposition->childCount(vertex);

        if (childCount > maxChildCount)
        {
            maxChildCount = childCount;
        }
    }

    htd::LimitChildCountOperation operation(libraryInstance, 3);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        ASSERT_LE(decomposition->childCount(vertex), (std::size_t)3);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::LimitChildCountOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckLimitChildCountOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::LimitChildCountOperation operation1(libraryInstance, 2);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        ASSERT_LE(decomposition->childCount(vertex), (std::size_t)3);
    }

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckLimitChildCountOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(root, { 2, 3 }, htd::FilteredHyperedgeCollection());

    htd::vertex_t node3 = decomposition->addChild(root, { 3, 5, 6 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5, 6 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitChildCountOperation operation(libraryInstance, 2);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->childCount(createdVertex), (std::size_t)2);

        for (htd::vertex_t child : decomposition->children(createdVertex))
        {
            ASSERT_LE(decomposition->childCount(child), (std::size_t)2);
        }

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckLimitChildCountOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());

    htd::vertex_t node2 = decomposition->addChild(root, { 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(root, { 3, 5, 6 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5, 6 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitChildCountOperation operation(libraryInstance, 2);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node3 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)4, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_LE(decomposition->childCount(createdVertex), (std::size_t)2);
        for (htd::vertex_t child : decomposition->children(createdVertex))
        {
            ASSERT_LE(decomposition->childCount(child), (std::size_t)2);
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ(root, decomposition->parent(createdVertices[0]));

    ASSERT_LE(decomposition->childCount(createdVertices[0]), (std::size_t)2);
    for (htd::vertex_t child : decomposition->children(createdVertices[0]))
    {
        ASSERT_LE(decomposition->childCount(child), (std::size_t)2);
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckLimitChildCountOperation5)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(root, { 2, 3 }, htd::FilteredHyperedgeCollection());

    htd::vertex_t node3 = decomposition->addChild(root, { 3, 5, 6 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 6 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 5, 6 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitChildCountOperation operation(libraryInstance, 2);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { node3 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)4, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_LE(decomposition->childCount(node3), (std::size_t)2);

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_LE(decomposition->childCount(createdVertex), (std::size_t)2);

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeNormalizationOperation operation1(libraryInstance);

    ASSERT_TRUE(operation1.isLocalOperation());
    ASSERT_TRUE(operation1.createsTreeNodes());
    ASSERT_FALSE(operation1.removesTreeNodes());
    ASSERT_FALSE(operation1.modifiesBagContents());
    ASSERT_FALSE(operation1.createsSubsetMaximalBags());
    ASSERT_FALSE(operation1.createsLocationDependendLabels());

    operation1.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            const std::vector<htd::vertex_t> & childBag = decomposition->bagContent(child);

            ASSERT_TRUE(childBag == bag);
        }
    }

    htd::JoinNodeNormalizationOperation operation2(libraryInstance, true);

    operation2.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            const std::vector<htd::vertex_t> & childBag = decomposition->bagContent(child);

            ASSERT_TRUE(childBag == bag);
        }

        if (!decomposition->isRoot(vertex))
        {
            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == bag);
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation1.managementInstance() == libraryInstance);

    operation1.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation1.managementInstance() == libraryInstance2);

    htd::JoinNodeNormalizationOperation * clonedOperation = operation1.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckJoinNodeNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::JoinNodeNormalizationOperation operation1(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            const std::vector<htd::vertex_t> & childBag = decomposition->bagContent(child);

            ASSERT_TRUE(childBag == bag);
        }
    }

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::JoinNodeNormalizationOperation operation2(libraryInstance, true);

    operation2.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            const std::vector<htd::vertex_t> & childBag = decomposition->bagContent(child);

            ASSERT_TRUE(childBag == bag);
        }

        ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == bag);
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node1, { 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeNormalizationOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(node1, decomposition->parent(createdVertex));

        ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
        ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
        ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertex)[1]);
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)4, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->parent(createdVertex) == root)
        {
            ASSERT_EQ((std::size_t)3, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)2, decomposition->bagContent(createdVertex)[1]);
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[2]);
        }
        else if (decomposition->parent(createdVertex) == node2)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)5, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeNormalizationOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node1, { 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeNormalizationOperation operation(libraryInstance, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)3, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->parent(createdVertex) == root || decomposition->parent(createdVertex) == node1)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)6, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->isRoot(createdVertex) || decomposition->parent(createdVertex) == root)
        {
            ASSERT_EQ((std::size_t)3, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)2, decomposition->bagContent(createdVertex)[1]);
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[2]);
        }
        else if (decomposition->parent(node2) == createdVertex || decomposition->parent(createdVertex) == node2)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)5, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionExchangeNodeReplacementOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->exchangeNodeCount());

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::ExchangeNodeReplacementOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionExchangeNodeReplacementOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->exchangeNodeCount());

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::ExchangeNodeReplacementOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionExchangeNodeReplacementOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->exchangeNodeCount());

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionExchangeNodeReplacementOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->exchangeNodeCount());

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionExchangeNodeReplacementOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ(node1, decomposition->parent(createdVertices[0]));

    ASSERT_EQ((std::size_t)1, decomposition->bagSize(createdVertices[0]));
    ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertices[0])[0]);

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    if (decomposition->parent(createdVertices[0]) == node2)
    {
        ASSERT_EQ((std::size_t)1, decomposition->bagSize(createdVertices[0]));
        ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertices[0])[0]);
    }
    else
    {
        FAIL();
    }

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionExchangeNodeReplacementOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::ExchangeNodeReplacementOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ(node1, decomposition->parent(createdVertices[0]));

    ASSERT_EQ((std::size_t)1, decomposition->bagSize(createdVertices[0]));
    ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertices[0])[0]);

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    if (decomposition->parent(createdVertices[0]) == node2)
    {
        ASSERT_EQ((std::size_t)1, decomposition->bagSize(createdVertices[0]));
        ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertices[0])[0]);
    }
    else
    {
        FAIL();
    }

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionOptimizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition1 = input.second;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableTreeDecomposition * decomposition2 = input.second->clone();
#else
    htd::IMutableTreeDecomposition * decomposition2 = input.second->cloneMutableTreeDecomposition();
#endif

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));
    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    std::size_t heightBefore = decomposition2->height();

    htd::TreeDecompositionOptimizationOperation operation(libraryInstance);

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.setVertexSelectionStrategy(new htd::ExhaustiveVertexSelectionStrategy());

    operation.addManipulationOperation(new htd::NormalizationOperation(libraryInstance));

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition1);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));

    ASSERT_GE(decomposition1->height(), heightBefore);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::TreeDecompositionOptimizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition1;
    delete decomposition2;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionOptimizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition1 = input.second;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableTreeDecomposition * decomposition2 = input.second->clone();
#else
    htd::IMutableTreeDecomposition * decomposition2 = input.second->cloneMutableTreeDecomposition();
#endif

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));
    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    htd::NormalizationOperation normalizationOperation(libraryInstance);

    normalizationOperation.apply(*graph, *decomposition2);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    std::size_t heightBefore = decomposition2->height();

    htd::TreeDecompositionOptimizationOperation operation(libraryInstance, new FitnessFunction());

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.setVertexSelectionStrategy(new htd::ExhaustiveVertexSelectionStrategy());

    operation.apply(*graph, *decomposition1);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));

    ASSERT_LE(decomposition1->height(), heightBefore);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::TreeDecompositionOptimizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition1;
    delete decomposition2;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionOptimizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition1 = input.second;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableTreeDecomposition * decomposition2 = input.second->clone();
#else
    htd::IMutableTreeDecomposition * decomposition2 = input.second->cloneMutableTreeDecomposition();
#endif

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));
    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    htd::NormalizationOperation normalizationOperation(libraryInstance);

    normalizationOperation.apply(*graph, *decomposition2);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    std::size_t heightBefore = decomposition2->height();

    htd::TreeDecompositionOptimizationOperation operation(libraryInstance, new FitnessFunction());

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.setVertexSelectionStrategy(new htd::ExhaustiveVertexSelectionStrategy());

    operation.addManipulationOperations({ new htd::NormalizationOperation(libraryInstance) });

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition1);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));

    ASSERT_LE(decomposition1->height(), heightBefore);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::TreeDecompositionOptimizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition1;
    delete decomposition2;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionOptimizationOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition1 = input.second;

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    htd::IMutableTreeDecomposition * decomposition2 = input.second->clone();
#else
    htd::IMutableTreeDecomposition * decomposition2 = input.second->cloneMutableTreeDecomposition();
#endif

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));
    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    std::size_t heightInitial = decomposition1->height();

    htd::NormalizationOperation normalizationOperation(libraryInstance);

    normalizationOperation.apply(*graph, *decomposition2);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition2));

    std::size_t heightBefore = decomposition2->height();

    htd::TreeDecompositionOptimizationOperation operation(libraryInstance, new FitnessFunction(), true);

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.setVertexSelectionStrategy(new htd::ExhaustiveVertexSelectionStrategy());

    operation.addManipulationOperation(new htd::NormalizationOperation(libraryInstance));

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition1);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));

    std::size_t heightAfter1 = decomposition1->height();

    ASSERT_LE(heightAfter1, heightBefore);

    operation.setManipulationOperations({ new htd::CompressionOperation(libraryInstance) });

    ASSERT_FALSE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_TRUE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition1);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition1));

    ASSERT_LE(decomposition1->height(), heightInitial);
    ASSERT_LE(decomposition1->height(), heightAfter1);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::TreeDecompositionOptimizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition1;
    delete decomposition2;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyRootOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(decomposition->root()));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::AddEmptyRootOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyRootOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(decomposition->root()));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::AddEmptyRootOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyRootOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction } );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(decomposition->root()));
    ASSERT_EQ(decomposition->bagSize(decomposition->root()), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", decomposition->root())));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyRootOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction } );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(decomposition->root()));
    ASSERT_EQ(decomposition->bagSize(decomposition->root()), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", decomposition->root())));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyRootOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_TRUE(decomposition->isRoot(createdVertices[0]));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(createdVertices[0]));

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyRootOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyRootOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(createdVertices[0]));

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyLeavesOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->leaves())
    {
        ASSERT_EQ((std::size_t)0, decomposition->bagSize(vertex));
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::AddEmptyLeavesOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyLeavesOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->leaves())
    {
        ASSERT_EQ((std::size_t)0, decomposition->bagSize(vertex));
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::AddEmptyLeavesOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyLeavesOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction } );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->leaves())
    {
        ASSERT_EQ((std::size_t)0, decomposition->bagSize(vertex));
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyLeavesOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction } );

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->leaves())
    {
        ASSERT_EQ((std::size_t)0, decomposition->bagSize(vertex));
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionAddEmptyLeavesOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node4 = decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2, node4 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_TRUE(decomposition->isLeaf(createdVertices[0]));

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(createdVertices[0]));

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionAddEmptyLeavesOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node4 = decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddEmptyLeavesOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2, node4 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ((std::size_t)0, decomposition->bagSize(createdVertices[0]));

    ASSERT_EQ(decomposition->bagSize(createdVertices[0]), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertices[0])));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckAddIdenticalJoinNodeParentOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddIdenticalJoinNodeParentOperation operation1(libraryInstance, false);

    ASSERT_TRUE(operation1.isLocalOperation());
    ASSERT_TRUE(operation1.createsTreeNodes());
    ASSERT_FALSE(operation1.removesTreeNodes());
    ASSERT_FALSE(operation1.modifiesBagContents());
    ASSERT_FALSE(operation1.createsSubsetMaximalBags());
    ASSERT_FALSE(operation1.createsLocationDependendLabels());

    operation1.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);
        const std::vector<htd::vertex_t> & parentBag = decomposition->bagContent(decomposition->parent(vertex));

        ASSERT_TRUE(parentBag == bag);
    }

    htd::AddIdenticalJoinNodeParentOperation operation2(libraryInstance, true);

    operation2.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);
        const std::vector<htd::vertex_t> & parentBag = decomposition->bagContent(decomposition->parent(vertex));
        const std::vector<htd::vertex_t> & grandparentBag = decomposition->bagContent(decomposition->parent(decomposition->parent(vertex)));

        ASSERT_TRUE(parentBag == bag);
        ASSERT_TRUE(grandparentBag == bag);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation1.managementInstance() == libraryInstance);

    operation1.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation1.managementInstance() == libraryInstance2);

    htd::AddIdenticalJoinNodeParentOperation * clonedOperation = operation1.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckAddIdenticalJoinNodeParentOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::AddIdenticalJoinNodeParentOperation operation1(libraryInstance, false);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);
        const std::vector<htd::vertex_t> & parentBag = decomposition->bagContent(decomposition->parent(vertex));

        ASSERT_TRUE(parentBag == bag);
    }

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::AddIdenticalJoinNodeParentOperation operation2(libraryInstance, true);

    operation2.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        const std::vector<htd::vertex_t> & bag = decomposition->bagContent(vertex);
        const std::vector<htd::vertex_t> & parentBag = decomposition->bagContent(decomposition->parent(vertex));
        const std::vector<htd::vertex_t> & grandparentBag = decomposition->bagContent(decomposition->parent(decomposition->parent(vertex)));

        ASSERT_TRUE(parentBag == bag);
        ASSERT_TRUE(grandparentBag == bag);
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckAddIdenticalJoinNodeParentOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node1, { 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddIdenticalJoinNodeParentOperation operation(libraryInstance, false);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ(node1, decomposition->childAtPosition(createdVertices[0], 0));

    ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertices[0]));
    ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertices[0])[0]);
    ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertices[0])[1]);

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->childAtPosition(createdVertex, 0) == root)
        {
            ASSERT_EQ((std::size_t)3, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)2, decomposition->bagContent(createdVertex)[1]);
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[2]);
        }
        else if (decomposition->childAtPosition(createdVertex, 0) == node2)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)5, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckAddIdenticalJoinNodeParentOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node1, { 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node2, { 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::AddIdenticalJoinNodeParentOperation operation(libraryInstance, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertices[0]));
    ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertices[0])[0]);
    ASSERT_EQ((htd::vertex_t)4, decomposition->bagContent(createdVertices[0])[1]);

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->childAtPosition(createdVertex, 0) == root)
        {
            ASSERT_EQ((std::size_t)3, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)2, decomposition->bagContent(createdVertex)[1]);
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[2]);
        }
        else if (decomposition->childAtPosition(createdVertex, 0) == node2)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)5, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    createdVertices.clear();

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        if (decomposition->childAtPosition(createdVertex, 0) == root)
        {
            ASSERT_EQ((std::size_t)3, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)1, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)2, decomposition->bagContent(createdVertex)[1]);
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[2]);
        }
        else if (decomposition->childAtPosition(createdVertex, 0) == node2)
        {
            ASSERT_EQ((std::size_t)2, decomposition->bagSize(createdVertex));
            ASSERT_EQ((htd::vertex_t)3, decomposition->bagContent(createdVertex)[0]);
            ASSERT_EQ((htd::vertex_t)5, decomposition->bagContent(createdVertex)[1]);
        }
        else
        {
            FAIL();
        }
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumIntroducedVertexCountOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input =
        computeTreeDecomposition(libraryInstance, { new htd::JoinNodeNormalizationOperation(libraryInstance),
                                                    new htd::LimitChildCountOperation(libraryInstance, 2),
                                                    new htd::ExchangeNodeReplacementOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 2);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (!decomposition->isLeaf(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex), (std::size_t)2);
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::LimitMaximumIntroducedVertexCountOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumIntroducedVertexCountOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input =
        computePathDecomposition(libraryInstance, { new htd::ExchangeNodeReplacementOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 2);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (!decomposition->isLeaf(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex), (std::size_t)2);
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::LimitMaximumIntroducedVertexCountOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumIntroducedVertexCountOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input =
        computeTreeDecomposition(libraryInstance, { new htd::JoinNodeNormalizationOperation(libraryInstance),
                                                    new htd::LimitChildCountOperation(libraryInstance, 2),
                                                    new htd::ExchangeNodeReplacementOperation(libraryInstance),
                                                    new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::LimitMaximumIntroducedVertexCountOperation operation1(libraryInstance, 2, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->introducedVertexCount(vertex), (std::size_t)2);

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumIntroducedVertexCountOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input =
            computePathDecomposition(libraryInstance, { new htd::ExchangeNodeReplacementOperation(libraryInstance),
                                                        new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::LimitMaximumIntroducedVertexCountOperation operation1(libraryInstance, 2, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->introducedVertexCount(vertex), (std::size_t)2);

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumIntroducedVertexCountOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 1 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 1, true);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1, node2 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->introducedVertexCount(createdVertex), (std::size_t)1);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumIntroducedVertexCountOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(10);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3, 4, 5, 6, 7 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 5, 8, 9, 10 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 2, true);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node2 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->introducedVertexCount(createdVertex), (std::size_t)2);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumIntroducedVertexCountOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(6);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 1 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 1, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->introducedVertexCount(createdVertex), (std::size_t)1);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumIntroducedVertexCountOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(10);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3, 4, 5, 6, 7 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 3, 5 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 5, 8, 9, 10 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumIntroducedVertexCountOperation operation(libraryInstance, 2, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->introducedVertexCount(createdVertex), (std::size_t)2);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumForgottenVertexCountOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input =
        computeTreeDecomposition(libraryInstance, { new htd::JoinNodeNormalizationOperation(libraryInstance),
                                                    new htd::LimitChildCountOperation(libraryInstance, 2),
                                                    new htd::ExchangeNodeReplacementOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 2);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->forgottenVertexCount(vertex), (std::size_t)2);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::LimitMaximumForgottenVertexCountOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumForgottenVertexCountOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input =
        computePathDecomposition(libraryInstance, { new htd::ExchangeNodeReplacementOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 2);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->forgottenVertexCount(vertex), (std::size_t)2);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::LimitMaximumForgottenVertexCountOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumForgottenVertexCountOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input =
        computeTreeDecomposition(libraryInstance, { new htd::JoinNodeNormalizationOperation(libraryInstance),
                                                    new htd::LimitChildCountOperation(libraryInstance, 2),
                                                    new htd::ExchangeNodeReplacementOperation(libraryInstance),
                                                    new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::LimitMaximumForgottenVertexCountOperation operation1(libraryInstance, 2);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->forgottenVertexCount(vertex), (std::size_t)2);

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumForgottenVertexCountOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input =
            computePathDecomposition(libraryInstance, { new htd::ExchangeNodeReplacementOperation(libraryInstance),
                                                        new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::LimitMaximumForgottenVertexCountOperation operation1(libraryInstance, 2);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_LE(decomposition->forgottenVertexCount(vertex), (std::size_t)2);

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumForgottenVertexCountOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 1);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->forgottenVertexCount(createdVertex), (std::size_t)1);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumForgottenVertexCountOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(10);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6, 7 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 7, 8, 9, 10 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 2);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node2 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->forgottenVertexCount(createdVertex), (std::size_t)2);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionLimitMaximumForgottenVertexCountOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(6);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(1, 4);
    graph->addEdge(2, 3);
    graph->addEdge(3, 5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 1);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node1 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->forgottenVertexCount(createdVertex), (std::size_t)1);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionLimitMaximumForgottenVertexCountOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(10);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6, 7 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 7, 8, 9, 10 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LimitMaximumForgottenVertexCountOperation operation(libraryInstance, 2);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_NE((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_LE(decomposition->introducedVertexCount(createdVertex), (std::size_t)2);

        ASSERT_TRUE(std::binary_search(createdVertices.begin(), createdVertices.end(), createdVertex));

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionInducedSubgraphLabelingOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::InducedSubgraphLabelingOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_TRUE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_TRUE(isValidInducedEdgeLabel(*graph, *decomposition, htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::InducedSubgraphLabelingOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionInducedSubgraphLabelingOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::InducedSubgraphLabelingOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_TRUE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_TRUE(isValidInducedEdgeLabel(*graph, *decomposition, htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::InducedSubgraphLabelingOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionInducedSubgraphLabelingOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::InducedSubgraphLabelingOperation operation1(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_TRUE(isValidInducedEdgeLabel(*graph, *decomposition, htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionInducedSubgraphLabelingOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::InducedSubgraphLabelingOperation operation1(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_TRUE(isValidInducedEdgeLabel(*graph, *decomposition, htd::InducedSubgraphLabelingOperation::INDUCED_SUBGRAPH_LABEL_IDENTIFIER));

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionCompressionOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new htd::NormalizationOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation(libraryInstance, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_TRUE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex1 : decomposition->vertices())
    {
        bool supersetFound = false;

        const std::vector<htd::vertex_t> & bag1 = decomposition->bagContent(vertex1);

        for (htd::vertex_t vertex2 : decomposition->vertices())
        {
            if (vertex1 != vertex2)
            {
                const std::vector<htd::vertex_t> & bag2 = decomposition->bagContent(vertex2);

                supersetFound = supersetFound || std::includes(bag2.begin(), bag2.end(), bag1.begin(), bag1.end());
            }
        }

        ASSERT_FALSE(supersetFound);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::CompressionOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionCompressionOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new htd::NormalizationOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_FALSE(operation.createsTreeNodes());
    ASSERT_TRUE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex1 : decomposition->vertices())
    {
        bool supersetFound = false;

        const std::vector<htd::vertex_t> & bag1 = decomposition->bagContent(vertex1);

        for (htd::vertex_t vertex2 : decomposition->vertices())
        {
            if (vertex1 != vertex2)
            {
                const std::vector<htd::vertex_t> & bag2 = decomposition->bagContent(vertex2);

                supersetFound = supersetFound || std::includes(bag2.begin(), bag2.end(), bag1.begin(), bag1.end());
            }
        }

        ASSERT_FALSE(supersetFound);
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::CompressionOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionCompressionOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new htd::NormalizationOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation1(libraryInstance, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex1 : decomposition->vertices())
    {
        bool supersetFound = false;

        const std::vector<htd::vertex_t> & bag1 = decomposition->bagContent(vertex1);

        for (htd::vertex_t vertex2 : decomposition->vertices())
        {
            if (vertex1 != vertex2)
            {
                const std::vector<htd::vertex_t> & bag2 = decomposition->bagContent(vertex2);

                supersetFound = supersetFound || std::includes(bag2.begin(), bag2.end(), bag1.begin(), bag1.end());
            }
        }

        ASSERT_FALSE(supersetFound);
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionCompressionOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new htd::NormalizationOperation(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation1(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex1 : decomposition->vertices())
    {
        bool supersetFound = false;

        const std::vector<htd::vertex_t> & bag1 = decomposition->bagContent(vertex1);

        for (htd::vertex_t vertex2 : decomposition->vertices())
        {
            if (vertex1 != vertex2)
            {
                const std::vector<htd::vertex_t> & bag2 = decomposition->bagContent(vertex2);

                supersetFound = supersetFound || std::includes(bag2.begin(), bag2.end(), bag1.begin(), bag1.end());
            }
        }

        ASSERT_FALSE(supersetFound);
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionCompressionOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(12);

    htd::vertex_t root = decomposition->insertRoot({ }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(root, { 11, 12 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node1, { }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node4 = decomposition->addChild(node2, { 11 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation1(libraryInstance, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation1.apply(*graph, *decomposition, { node1, node2, node3, node4 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)3, removedVertices.size());

    ASSERT_EQ(root, removedVertices[0]);
    ASSERT_EQ(node3, removedVertices[1]);
    ASSERT_EQ(node4, removedVertices[2]);

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionCompressionOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(12);

    htd::vertex_t root = decomposition->insertRoot({ }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 1 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 11, 12 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::CompressionOperation operation1(libraryInstance, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation1.apply(*graph, *decomposition, { root, node1, node2 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)2, removedVertices.size());

    ASSERT_EQ(root, removedVertices[0]);
    ASSERT_EQ(node2, removedVertices[1]);

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeComplexityReductionOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeComplexityReductionOperation operation(libraryInstance);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_EQ((std::size_t)0, decomposition->forgottenVertexCount(vertex, child));
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::JoinNodeComplexityReductionOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckJoinNodeComplexityReductionOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::JoinNodeComplexityReductionOperation operation1(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation1.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->joinNodes())
    {
        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_EQ((std::size_t)0, decomposition->forgottenVertexCount(vertex, child));
        }
    }

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeComplexityReductionOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(root, { 1, 4, 5 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(root, { 2, 3 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeComplexityReductionOperation operation(libraryInstance);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    htd::vertex_t lastVertex = decomposition->vertexAtPosition(decomposition->vertexCount() - 1);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t createdVertex = lastVertex + 1; createdVertex <= decomposition->vertexAtPosition(decomposition->vertexCount() - 1); ++createdVertex)
    {
        ASSERT_EQ((std::size_t)0, decomposition->forgottenVertexCount(decomposition->parent(createdVertex), createdVertex));

        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckJoinNodeComplexityReductionOperation4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    htd::vertex_t root = decomposition->insertRoot({ 1 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(root, { 1, 4 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(root, { 2 }, htd::FilteredHyperedgeCollection());

    htd::vertex_t node3 = decomposition->addChild(root, { 3 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 3 }, htd::FilteredHyperedgeCollection());
    decomposition->addChild(node3, { 3, 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::JoinNodeComplexityReductionOperation operation(libraryInstance);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { root }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)3, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ((std::size_t)0, decomposition->forgottenVertexCount(decomposition->parent(createdVertex), createdVertex));
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { node3 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    for (htd::vertex_t child : decomposition->children(decomposition->parent(createdVertices[0])))
    {
        ASSERT_EQ((std::size_t)0, decomposition->forgottenVertexCount(decomposition->parent(createdVertices[0]), child));
    }

    for (htd::vertex_t createdVertex : createdVertices)
    {
        ASSERT_EQ(decomposition->bagSize(createdVertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", createdVertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());
    ASSERT_TRUE(operation.leafNodesTreatedAsIntroduceNodes());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }

            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::NormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());
    ASSERT_TRUE(operation.leafNodesTreatedAsIntroduceNodes());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::NormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }

            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node1, { 3, 4, 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node2, node3 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)4, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node2);
    createdVertices.push_back(node3);

    for (htd::vertex_t vertex : createdVertices)
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }

            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { node1 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)5, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node1);

    for (htd::vertex_t vertex : createdVertices)
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }

            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }

        if (vertex != node1)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::NormalizationOperation operation(libraryInstance, true, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node1);

    for (htd::vertex_t vertex : createdVertices)
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)4, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(root);
    createdVertices.push_back(node2);

    for (htd::vertex_t vertex : createdVertices)
    {
        ASSERT_FALSE(decomposition->isExchangeNode(vertex));

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            ASSERT_LE(decomposition->introducedVertexCount(vertex, child), (std::size_t)1);
            ASSERT_LE(decomposition->forgottenVertexCount(vertex, child), (std::size_t)1);
        }

        if (vertex != root && vertex != node2)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionSemiNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::SemiNormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionSemiNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::SemiNormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionSemiNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionSemiNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionSemiNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node1, { 3, 4, 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node2, node3 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node2);
    createdVertices.push_back(node3);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { node1 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)3, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node1);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }

        if (vertex != node1)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionSemiNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::SemiNormalizationOperation operation(libraryInstance, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(root);
    createdVertices.push_back(node2);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (vertex != root && vertex != node2)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionWeakNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }
    }

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::WeakNormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckPathDecompositionWeakNormalizationOperation1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance);

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    ASSERT_TRUE(operation.isLocalOperation());
    ASSERT_TRUE(operation.createsTreeNodes());
    ASSERT_FALSE(operation.removesTreeNodes());
    ASSERT_FALSE(operation.modifiesBagContents());
    ASSERT_FALSE(operation.createsSubsetMaximalBags());
    ASSERT_FALSE(operation.createsLocationDependendLabels());

    operation.apply(*graph, *decomposition);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance);

    operation.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(operation.managementInstance() == libraryInstance2);

    htd::WeakNormalizationOperation * clonedOperation = operation.clone();

    ASSERT_TRUE(clonedOperation->managementInstance() == libraryInstance2);

    delete graph;
    delete decomposition;
    delete clonedOperation;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionWeakNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutableTreeDecomposition *> input = computeTreeDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutableTreeDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }

        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionWeakNormalizationOperation2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    std::pair<htd::IMultiHypergraph *, htd::IMutablePathDecomposition *> input = computePathDecomposition(libraryInstance, { new BagSizeLabelingFunction(libraryInstance) });

    htd::IMultiHypergraph * graph = input.first;

    htd::IMutablePathDecomposition * decomposition = input.second;

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { labelingFunction });

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckTreeDecompositionWeakNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node1, { 3, 4, 5 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node2, node3 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)2, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node2);
    createdVertices.push_back(node3);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }
    }

    createdVertices.clear();

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { node1 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)3, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(node1);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (decomposition->isJoinNode(vertex))
        {
            ASSERT_EQ((std::size_t)2, decomposition->childCount(vertex));

            ASSERT_TRUE(decomposition->bagContent(decomposition->parent(vertex)) == decomposition->bagContent(vertex));
        }

        for (htd::vertex_t child : decomposition->children(vertex))
        {
            if (decomposition->isJoinNode(vertex))
            {
                ASSERT_TRUE(decomposition->bagContent(vertex) == decomposition->bagContent(child));
            }
        }

        if (vertex != node1)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

TEST(ManipulationOperationTest, CheckPathDecompositionWeakNormalizationOperation3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    graph->addVertices(5);

    graph->addEdge(1, 2);
    graph->addEdge(1, 3);
    graph->addEdge(2, 3);
    graph->addEdge(3, 4);

    htd::vertex_t root = decomposition->insertRoot({ 1, 2, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node1 = decomposition->addChild(root, { 1, 3 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node2 = decomposition->addChild(node1, { 3, 4 }, htd::FilteredHyperedgeCollection());
    htd::vertex_t node3 = decomposition->addChild(node2, { 4, 5 }, htd::FilteredHyperedgeCollection());

    decomposition->addChild(node3, { 4 }, htd::FilteredHyperedgeCollection());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    htd::WeakNormalizationOperation operation(libraryInstance, true, true, true);

    std::vector<htd::vertex_t> createdVertices;
    std::vector<htd::vertex_t> removedVertices;

    operation.apply(*graph, *decomposition, { node1 }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)0, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    BagSizeLabelingFunction * labelingFunction = new BagSizeLabelingFunction(libraryInstance);

    operation.apply(*graph, *decomposition, { root, node2 }, { labelingFunction }, createdVertices, removedVertices);

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ((std::size_t)1, createdVertices.size());
    ASSERT_EQ((std::size_t)0, removedVertices.size());

    createdVertices.push_back(root);
    createdVertices.push_back(node2);

    for (htd::vertex_t vertex : createdVertices)
    {
        if (vertex != root && vertex != node2)
        {
            ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        }
    }

    delete graph;
    delete decomposition;
    delete labelingFunction;
    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
