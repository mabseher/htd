/*
 * File:   TreeDecompositionOptimizationTest.cpp
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

#include <vector>

class TreeDecompositionOptimizationTest : public ::testing::Test
{
    public:
        TreeDecompositionOptimizationTest(void)
        {

        }

        virtual ~TreeDecompositionOptimizationTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
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

TEST(TreeDecompositionOptimizationTest, CheckResultEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_EQ(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), (std::size_t)0);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    const std::vector<htd::vertex_t> & bag = decomposition->bagContent(1);

    EXPECT_EQ(bag.size(), (std::size_t)0);

    ASSERT_TRUE(algorithm.isSafelyInterruptible());
    ASSERT_EQ((std::size_t)1, algorithm.iterationCount());
    ASSERT_EQ((std::size_t)-1, algorithm.nonImprovementLimit());

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance);

    algorithm.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance2);

    htd::IterativeImprovementTreeDecompositionAlgorithm  * clonedAlgorithm = algorithm.clone();

    ASSERT_TRUE(clonedAlgorithm->managementInstance() == libraryInstance2);

    delete decomposition;
    delete clonedAlgorithm;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_EQ(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), (std::size_t)0);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    const std::vector<htd::vertex_t> & bag = decomposition->bagContent(1);

    EXPECT_EQ(bag.size(), (std::size_t)0);

    ASSERT_TRUE(algorithm.isSafelyInterruptible());
    ASSERT_EQ((std::size_t)1, algorithm.iterationCount());

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance);

    algorithm.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance2);

    htd::WidthMinimizingTreeDecompositionAlgorithm  * clonedAlgorithm = algorithm.clone();

    ASSERT_TRUE(clonedAlgorithm->managementInstance() == libraryInstance2);

    delete decomposition;
    delete clonedAlgorithm;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_EQ(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), (std::size_t)0);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    const std::vector<htd::vertex_t> & bag = decomposition->bagContent(1);

    EXPECT_EQ(bag.size(), (std::size_t)0);

    ASSERT_TRUE(algorithm.isSafelyInterruptible());

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance);

    algorithm.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance2);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm * clonedAlgorithm = algorithm.clone();

    ASSERT_TRUE(clonedAlgorithm->managementInstance() == libraryInstance2);

    delete decomposition;
    delete clonedAlgorithm;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(TreeDecompositionOptimizationTest, CheckResultDisconnectedGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultDisconnectedGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultDisconnectedGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckResultSimpleGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultSimpleGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultSimpleGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckResultComplexGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::TreeDecompositionVerifier verifier;

    algorithm.setIterationCount(25);

    ASSERT_EQ((std::size_t)25, algorithm.iterationCount());

    std::size_t iterationCount = 0;
    std::size_t minimalHeight = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph,
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentHeight = currentDecomposition.height();

        ASSERT_EQ(currentHeight, (std::size_t)(-fitness.at(0)));

        if (currentHeight < minimalHeight)
        {
            minimalHeight = currentHeight;
        }

        ++iterationCount;
    });

    ASSERT_EQ((std::size_t)25, iterationCount);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ(minimalHeight, decomposition->height());

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultComplexGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::TreeDecompositionVerifier verifier;

    algorithm.setIterationCount(25);

    ASSERT_EQ((std::size_t)25, algorithm.iterationCount());

    std::size_t iterationCount = 0;
    std::size_t minimalWidth = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph,
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentWidth = currentDecomposition.maximumBagSize();

        ASSERT_EQ(currentWidth, static_cast<std::size_t>(-fitness.at(0)));

        if (currentWidth < minimalWidth)
        {
            minimalWidth = currentWidth;
        }

        ++iterationCount;
    });

    ASSERT_LE(iterationCount, (std::size_t)25);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ(minimalWidth, decomposition->maximumBagSize());

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultComplexGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::TreeDecompositionVerifier verifier;

    std::size_t minimalWidth = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph,
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentWidth = currentDecomposition.maximumBagSize();

        ASSERT_EQ(currentWidth, static_cast<std::size_t>(-fitness.at(0)));

        if (currentWidth < minimalWidth)
        {
            minimalWidth = currentWidth;
        }
    });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ(minimalWidth, decomposition->maximumBagSize());

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

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

TEST(TreeDecompositionOptimizationTest, CheckResultSimpleGraphWithLabelingFunction)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, 1, new BagSizeLabelingFunction(libraryInstance));

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultSimpleGraphWithLabelingFunction)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, 1, new BagSizeLabelingFunction(libraryInstance));

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultSimpleGraphWithLabelingFunction)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, 1, new BagSizeLabelingFunction(libraryInstance));

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

class BagSizeLabelingFunction2 : public htd::ILabelingFunction
{
    public:
        BagSizeLabelingFunction2(const htd::LibraryInstance * const manager) : managementInstance_(manager)
        {

        }

        virtual ~BagSizeLabelingFunction2()
        {

        }

        std::string name() const HTD_OVERRIDE
        {
            return "BAG_SIZE_TIMES_2";
        }

        htd::ILabel * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels)

            return new htd::Label<std::size_t>(vertices.size() + htd::accessLabel<std::size_t>(labels.label("BAG_SIZE")));
        }

        htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels)

            return new htd::Label<std::size_t>(vertices.size() + htd::accessLabel<std::size_t>(labels.label("BAG_SIZE")));
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
        BagSizeLabelingFunction2 * clone(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction2(managementInstance_);
        }
#else
        BagSizeLabelingFunction2 * clone(void) const
        {
            return new BagSizeLabelingFunction2(managementInstance_);
        }

        htd::ILabelingFunction * cloneLabelingFunction(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction2(managementInstance_);
        }

        htd::IDecompositionManipulationOperation * cloneDecompositionManipulationOperation(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction2(managementInstance_);
        }
#endif

    private:
        const htd::LibraryInstance * managementInstance_;
};

TEST(TreeDecompositionOptimizationTest, CheckResultSimpleGraphWithLabelingFunctionVector)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction());

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction(libraryInstance),
                                                                                      new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultSimpleGraphWithLabelingFunctionVector)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction(libraryInstance),
                                                                                      new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultSimpleGraphWithLabelingFunctionVector)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction(libraryInstance),
                                                                                      new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckResultSimpleGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction(),
                                                                  { new BagSizeLabelingFunction(libraryInstance),
                                                                    new htd::JoinNodeReplacementOperation(libraryInstance) });

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultSimpleGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance,
                                                             { new BagSizeLabelingFunction(libraryInstance),
                                                               new htd::JoinNodeReplacementOperation(libraryInstance) });

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultSimpleGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::MultiHypergraph graph(libraryInstance);

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    algorithm.setManipulationOperations({ new BagSizeLabelingFunction(libraryInstance),
                                          new htd::JoinNodeReplacementOperation(libraryInstance) });

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction2(libraryInstance) });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    htd::TreeDecompositionVerifier verifier;

    ASSERT_TRUE(verifier.verify(graph, *decomposition));

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckResultComplexGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::IterativeImprovementTreeDecompositionAlgorithm algorithm(libraryInstance, new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance), new FitnessFunction(),
                                                                  { new BagSizeLabelingFunction(libraryInstance) });

    htd::TreeDecompositionVerifier verifier;

    algorithm.addManipulationOperations({ new htd::JoinNodeReplacementOperation(libraryInstance) });

    algorithm.setIterationCount(50);
    algorithm.setNonImprovementLimit(1);

    ASSERT_EQ((std::size_t)50, algorithm.iterationCount());
    ASSERT_EQ((std::size_t)1, algorithm.nonImprovementLimit());

    std::size_t iterationCount = 0;
    std::size_t nonImprovements = 0;

    std::size_t minimalHeight = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph, { new BagSizeLabelingFunction2(libraryInstance) },
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentHeight = currentDecomposition.height();

        ASSERT_EQ(currentHeight, (std::size_t)(-fitness.at(0)));

        if (currentHeight < minimalHeight)
        {
            minimalHeight = currentHeight;
        }
        else
        {
            ++nonImprovements;
        }

        ++iterationCount;
    });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_LE((std::size_t)1, nonImprovements);

    ASSERT_EQ(minimalHeight, decomposition->height());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckWidthMinimizationResultComplexGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm1 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm2 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    htd::BucketEliminationTreeDecompositionAlgorithm * baseAlgorithm3 =
        new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

    baseAlgorithm1->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));
    baseAlgorithm2->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));
    baseAlgorithm3->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

    algorithm.addDecompositionAlgorithm(baseAlgorithm1);
    algorithm.addDecompositionAlgorithm(baseAlgorithm2);
    algorithm.addDecompositionAlgorithm(baseAlgorithm3);

    algorithm.addDecompositionAlgorithm(new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance));

    algorithm.addManipulationOperations({ new BagSizeLabelingFunction(libraryInstance),
                                          new htd::JoinNodeReplacementOperation(libraryInstance) });

    htd::TreeDecompositionVerifier verifier;

    std::size_t minimalWidth = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph, { new BagSizeLabelingFunction2(libraryInstance) },
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentWidth = currentDecomposition.maximumBagSize();

        ASSERT_EQ(currentWidth, static_cast<std::size_t>(-fitness.at(0)));

        if (currentWidth < minimalWidth)
        {
            minimalWidth = currentWidth;
        }
    });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ(minimalWidth, decomposition->maximumBagSize());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

TEST(TreeDecompositionOptimizationTest, CheckCombinedWidthMinimizationResultComplexGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMultiHypergraph * graph = createInputGraph(libraryInstance);

    htd::WidthMinimizingTreeDecompositionAlgorithm algorithm(libraryInstance,
                                                             { new BagSizeLabelingFunction(libraryInstance) });

    htd::TreeDecompositionVerifier verifier;

    algorithm.addManipulationOperations({ new htd::JoinNodeReplacementOperation(libraryInstance) });

    algorithm.setIterationCount(50);

    ASSERT_EQ((std::size_t)50, algorithm.iterationCount());

    std::size_t iterationCount = 0;
    std::size_t minimalWidth = (std::size_t)-1;

    htd::ITreeDecomposition * decomposition =
        algorithm.computeDecomposition(*graph, { new BagSizeLabelingFunction2(libraryInstance) },
                                       [&](const htd::IMultiHypergraph & currentGraph, const htd::ITreeDecomposition & currentDecomposition, const htd::FitnessEvaluation & fitness){
        ASSERT_EQ(graph, &currentGraph);

        ASSERT_TRUE(verifier.verify(currentGraph, currentDecomposition));

        std::size_t currentWidth = currentDecomposition.maximumBagSize();

        ASSERT_EQ(currentWidth, static_cast<std::size_t>(-fitness.at(0)));

        if (currentWidth < minimalWidth)
        {
            minimalWidth = currentWidth;
        }

        ++iterationCount;
    });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_TRUE(verifier.verify(*graph, *decomposition));

    ASSERT_EQ(minimalWidth, decomposition->maximumBagSize());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete graph;
    delete decomposition;
    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
