/*
 * File:   LibraryInstanceTest.cpp
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

#include <gtest/gtest.h>

#include <htd/main.hpp>

#include <vector>

class LibraryInstanceTest : public ::testing::Test
{
    public:
        LibraryInstanceTest(void)
        {

        }

        virtual ~LibraryInstanceTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

class TestMultiHypergraph : public htd::MultiHypergraph
{
    public:
        TestMultiHypergraph(const htd::LibraryInstance * const managementInstance) : htd::MultiHypergraph::MultiHypergraph(managementInstance)
        {

        }

        virtual ~TestMultiHypergraph()
        {

        }
};

TEST(LibraryInstanceTest, CheckCreationFunction)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    ASSERT_NE(nullptr, libraryInstance);
    ASSERT_EQ(htd::Id::FIRST, libraryInstance->id());

    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTermination)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    ASSERT_FALSE(libraryInstance->isTerminated());

    libraryInstance->terminate();

    ASSERT_TRUE(libraryInstance->isTerminated());

    libraryInstance->terminate();

    ASSERT_TRUE(libraryInstance->isTerminated());

    libraryInstance->reset();

    ASSERT_FALSE(libraryInstance->isTerminated());

    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiHypergraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiHypergraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableMultiHypergraph * graph = constLibraryInstance.multiHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypergraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableHypergraph * graph = libraryInstance->hypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypergraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableHypergraph * graph = constLibraryInstance.hypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiGraph * graph = libraryInstance->multiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableMultiGraph * graph = constLibraryInstance.multiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableGraph * graph = libraryInstance->graphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableGraph * graph = constLibraryInstance.graphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedMultiGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableDirectedMultiGraph * graph = libraryInstance->directedMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedMultiGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableDirectedMultiGraph * graph = constLibraryInstance.directedMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableDirectedGraph * graph = libraryInstance->directedGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableDirectedGraph * graph = constLibraryInstance.directedGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckOrderingAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IOrderingAlgorithm * algorithm = libraryInstance->orderingAlgorithmFactory().getOrderingAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckOrderingAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IOrderingAlgorithm * algorithm = constLibraryInstance.orderingAlgorithmFactory().getOrderingAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableGraphDecomposition * decomposition = libraryInstance->graphDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableGraphDecomposition * decomposition = constLibraryInstance.graphDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableTreeDecomposition * decomposition = libraryInstance->treeDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableTreeDecomposition * decomposition = constLibraryInstance.treeDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutablePathDecomposition * decomposition = libraryInstance->pathDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutablePathDecomposition * decomposition = constLibraryInstance.pathDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableHypertreeDecomposition * decomposition = libraryInstance->hypertreeDecompositionFactory().getHypertreeDecomposition();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableHypertreeDecomposition * decomposition = constLibraryInstance.hypertreeDecompositionFactory().getHypertreeDecomposition();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionAlgorithFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IGraphDecompositionAlgorithm * algorithm = libraryInstance->graphDecompositionAlgorithmFactory().getGraphDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionAlgorithFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IGraphDecompositionAlgorithm * algorithm = constLibraryInstance.graphDecompositionAlgorithmFactory().getGraphDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::ITreeDecompositionAlgorithm * algorithm = libraryInstance->treeDecompositionAlgorithmFactory().getTreeDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::ITreeDecompositionAlgorithm * algorithm = constLibraryInstance.treeDecompositionAlgorithmFactory().getTreeDecompositionAlgorithm();


    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IPathDecompositionAlgorithm * algorithm = libraryInstance->pathDecompositionAlgorithmFactory().getPathDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IPathDecompositionAlgorithm * algorithm = constLibraryInstance.pathDecompositionAlgorithmFactory().getPathDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IHypertreeDecompositionAlgorithm * algorithm = libraryInstance->hypertreeDecompositionAlgorithmFactory().getHypertreeDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IHypertreeDecompositionAlgorithm * algorithm = constLibraryInstance.hypertreeDecompositionAlgorithmFactory().getHypertreeDecompositionAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckConnectedComponentAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IConnectedComponentAlgorithm * algorithm = libraryInstance->connectedComponentAlgorithmFactory().getConnectedComponentAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckConnectedComponentAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IConnectedComponentAlgorithm * algorithm = constLibraryInstance.connectedComponentAlgorithmFactory().getConnectedComponentAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckStronglyConnectedComponentAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IStronglyConnectedComponentAlgorithm * algorithm = libraryInstance->stronglyConnectedComponentAlgorithmFactory().getStronglyConnectedComponentAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckStronglyConnectedComponentAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IStronglyConnectedComponentAlgorithm * algorithm = constLibraryInstance.stronglyConnectedComponentAlgorithmFactory().getStronglyConnectedComponentAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckSetCoverAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::ISetCoverAlgorithm * algorithm = libraryInstance->setCoverAlgorithmFactory().getSetCoverAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckSetCoverAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::ISetCoverAlgorithm * algorithm = constLibraryInstance.setCoverAlgorithmFactory().getSetCoverAlgorithm();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

int main(int argc, char **argv)
{
    /* GoogleTest may throw. This results in a non-zero exit code and is intended. */
    // coverity[fun_call_w_exception]
    ::testing::InitGoogleTest(&argc, argv);

    /* GoogleTest may throw. This results in a non-zero exit code and is intended. */
    // coverity[fun_call_w_exception]
    return RUN_ALL_TESTS();
}
