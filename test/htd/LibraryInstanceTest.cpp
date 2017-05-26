/*
 * File:   LibraryInstanceTest.cpp
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

TEST(LibraryInstanceTest, CheckMultiHypergraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * graph = libraryInstance->multiHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiHypergraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableMultiHypergraph * graph = constLibraryInstance.multiHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

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

TEST(LibraryInstanceTest, CheckHypergraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableHypergraph * graph = libraryInstance->hypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypergraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableHypergraph * graph = constLibraryInstance.hypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

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

TEST(LibraryInstanceTest, CheckMultiGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiGraph * graph = libraryInstance->multiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckMultiGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableMultiGraph * graph = constLibraryInstance.multiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

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

TEST(LibraryInstanceTest, CheckGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableGraph * graph = libraryInstance->graphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableGraph * graph = constLibraryInstance.graphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

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

TEST(LibraryInstanceTest, CheckDirectedMultiGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableDirectedMultiGraph * graph = libraryInstance->directedMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedMultiGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableDirectedMultiGraph * graph = constLibraryInstance.directedMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

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

TEST(LibraryInstanceTest, CheckDirectedGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableDirectedGraph * graph = libraryInstance->directedGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckDirectedGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableDirectedGraph * graph = constLibraryInstance.directedGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiHypergraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledMultiHypergraph * graph = libraryInstance->labeledMultiHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiHypergraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledMultiHypergraph * graph = constLibraryInstance.labeledMultiHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiHypergraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledMultiHypergraph * graph = libraryInstance->labeledMultiHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiHypergraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledMultiHypergraph * graph = constLibraryInstance.labeledMultiHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledHypergraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledHypergraph * graph = libraryInstance->labeledHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledHypergraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledHypergraph * graph = constLibraryInstance.labeledHypergraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledHypergraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledHypergraph * graph = libraryInstance->labeledHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledHypergraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledHypergraph * graph = constLibraryInstance.labeledHypergraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledMultiGraph * graph = libraryInstance->labeledMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledMultiGraph * graph = constLibraryInstance.labeledMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledMultiGraph * graph = libraryInstance->labeledMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledMultiGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledMultiGraph * graph = constLibraryInstance.labeledMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledGraph * graph = libraryInstance->labeledGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledGraph * graph = constLibraryInstance.labeledGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledGraph * graph = libraryInstance->labeledGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledGraph * graph = constLibraryInstance.labeledGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedMultiGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledDirectedMultiGraph * graph = libraryInstance->labeledDirectedMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedMultiGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledDirectedMultiGraph * graph = constLibraryInstance.labeledDirectedMultiGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedMultiGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledDirectedMultiGraph * graph = libraryInstance->labeledDirectedMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedMultiGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledDirectedMultiGraph * graph = constLibraryInstance.labeledDirectedMultiGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedGraphFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledDirectedGraph * graph = libraryInstance->labeledDirectedGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedGraphFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledDirectedGraph * graph = constLibraryInstance.labeledDirectedGraphFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedGraphFactory3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledDirectedGraph * graph = libraryInstance->labeledDirectedGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledDirectedGraphFactory4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledDirectedGraph * graph = constLibraryInstance.labeledDirectedGraphFactory().createInstance(10);

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());
    ASSERT_EQ((std::size_t)10, graph->vertexCount());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledTreeFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledTree * graph = libraryInstance->labeledTreeFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledTreeFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledTree * graph = constLibraryInstance.labeledTreeFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledPathFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableLabeledPath * graph = libraryInstance->labeledPathFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckLabeledPathFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableLabeledPath * graph = constLibraryInstance.labeledPathFactory().createInstance();

    ASSERT_NE(nullptr, graph);
    ASSERT_EQ(libraryInstance, graph->managementInstance());

    delete graph;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckOrderingAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IOrderingAlgorithm * algorithm = libraryInstance->orderingAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckOrderingAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IOrderingAlgorithm * algorithm = constLibraryInstance.orderingAlgorithmFactory().createInstance();

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

    htd::IMutableHypertreeDecomposition * decomposition = libraryInstance->hypertreeDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IMutableHypertreeDecomposition * decomposition = constLibraryInstance.hypertreeDecompositionFactory().createInstance();

    ASSERT_NE(nullptr, decomposition);
    ASSERT_EQ(libraryInstance, decomposition->managementInstance());

    delete decomposition;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionAlgorithFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IGraphDecompositionAlgorithm * algorithm = libraryInstance->graphDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckGraphDecompositionAlgorithFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IGraphDecompositionAlgorithm * algorithm = constLibraryInstance.graphDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::ITreeDecompositionAlgorithm * algorithm = libraryInstance->treeDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckTreeDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::ITreeDecompositionAlgorithm * algorithm = constLibraryInstance.treeDecompositionAlgorithmFactory().createInstance();


    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IPathDecompositionAlgorithm * algorithm = libraryInstance->pathDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckPathDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IPathDecompositionAlgorithm * algorithm = constLibraryInstance.pathDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IHypertreeDecompositionAlgorithm * algorithm = libraryInstance->hypertreeDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckHypertreeDecompositionAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IHypertreeDecompositionAlgorithm * algorithm = constLibraryInstance.hypertreeDecompositionAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckConnectedComponentAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IConnectedComponentAlgorithm * algorithm = libraryInstance->connectedComponentAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckConnectedComponentAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IConnectedComponentAlgorithm * algorithm = constLibraryInstance.connectedComponentAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckStronglyConnectedComponentAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IStronglyConnectedComponentAlgorithm * algorithm = libraryInstance->stronglyConnectedComponentAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckStronglyConnectedComponentAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::IStronglyConnectedComponentAlgorithm * algorithm = constLibraryInstance.stronglyConnectedComponentAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckSetCoverAlgorithmFactory1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::ISetCoverAlgorithm * algorithm = libraryInstance->setCoverAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

TEST(LibraryInstanceTest, CheckSetCoverAlgorithmFactory2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    const htd::LibraryInstance & constLibraryInstance = *libraryInstance;

    htd::ISetCoverAlgorithm * algorithm = constLibraryInstance.setCoverAlgorithmFactory().createInstance();

    ASSERT_NE(nullptr, algorithm);
    ASSERT_EQ(libraryInstance, algorithm->managementInstance());

    delete algorithm;
    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
