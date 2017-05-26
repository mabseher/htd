/*
 * File:   GraphTest.cpp
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

class GraphTest : public ::testing::Test
{
    public:
        GraphTest(void)
        {

        }

        virtual ~GraphTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(GraphTest, CheckEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph(libraryInstance);

    ASSERT_EQ((std::size_t)0, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_EQ((std::size_t)0, graph.vertices().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());

    ASSERT_EQ((std::size_t)0, graph.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, graph.isolatedVertices().size());

    ASSERT_TRUE(graph.isConnected());

    delete libraryInstance;
}

TEST(GraphTest, CheckSizeInitializedGraph1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph(libraryInstance, 1);

    ASSERT_EQ((std::size_t)1, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    htd::ConstCollection<htd::vertex_t> vertices = graph.vertices();

    ASSERT_EQ((std::size_t)1, vertices.size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());

    htd::ConstCollection<htd::vertex_t> isolatedVertices = graph.isolatedVertices();

    ASSERT_EQ((std::size_t)1, graph.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, isolatedVertices.size());

    ASSERT_EQ((htd::vertex_t)1, vertices[0]);
    ASSERT_EQ((htd::vertex_t)1, graph.vertexAtPosition((htd::index_t)0));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)1));

    ASSERT_EQ((htd::vertex_t)1, isolatedVertices[0]);
    ASSERT_EQ((htd::vertex_t)1, graph.isolatedVertexAtPosition((htd::index_t)0));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)1));

    ASSERT_EQ((std::size_t)0, graph.edgeCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());

    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));

    ASSERT_TRUE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));

    delete libraryInstance;
}

TEST(GraphTest, CheckSizeInitializedGraph2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph(libraryInstance, 3);

    ASSERT_EQ((std::size_t)3, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    htd::ConstCollection<htd::vertex_t> vertices = graph.vertices();

    ASSERT_EQ((std::size_t)3, vertices.size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());

    htd::ConstCollection<htd::vertex_t> isolatedVertices = graph.isolatedVertices();

    ASSERT_EQ((std::size_t)3, graph.isolatedVertexCount());
    ASSERT_EQ((std::size_t)3, isolatedVertices.size());

    ASSERT_EQ((htd::vertex_t)1, vertices[0]);
    ASSERT_EQ((htd::vertex_t)2, vertices[1]);
    ASSERT_EQ((htd::vertex_t)3, vertices[2]);
    ASSERT_EQ((htd::vertex_t)1, graph.vertexAtPosition((htd::index_t)0));
    ASSERT_EQ((htd::vertex_t)2, graph.vertexAtPosition((htd::index_t)1));
    ASSERT_EQ((htd::vertex_t)3, graph.vertexAtPosition((htd::index_t)2));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)1));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)2));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)3));

    ASSERT_EQ((htd::vertex_t)1, isolatedVertices[0]);
    ASSERT_EQ((htd::vertex_t)2, isolatedVertices[1]);
    ASSERT_EQ((htd::vertex_t)3, isolatedVertices[2]);
    ASSERT_EQ((htd::vertex_t)1, graph.isolatedVertexAtPosition((htd::index_t)0));
    ASSERT_EQ((htd::vertex_t)2, graph.isolatedVertexAtPosition((htd::index_t)1));
    ASSERT_EQ((htd::vertex_t)3, graph.isolatedVertexAtPosition((htd::index_t)2));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)1));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)2));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)3));

    ASSERT_EQ((std::size_t)0, graph.edgeCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());

    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)2));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    ASSERT_FALSE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)3));

    graph.addEdge(2, 1);

    ASSERT_TRUE(graph.isEdge((htd::id_t)1));
    ASSERT_FALSE(graph.isEdge((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isEdge((htd::vertex_t)2, (htd::vertex_t)1));

    ASSERT_EQ((std::size_t)1, graph.edgeCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)1, graph.edgeCount((htd::vertex_t)2));
    ASSERT_EQ((std::size_t)0, graph.edgeCount((htd::vertex_t)3));

    std::vector<htd::vertex_t> elements1 { 1, 2 };
    std::vector<htd::vertex_t> elements2 { 2, 1 };

    htd::ConstCollection<htd::vertex_t> edgeIds1 = graph.associatedEdgeIds(elements1);
    htd::ConstCollection<htd::vertex_t> edgeIds2 = graph.associatedEdgeIds((htd::vertex_t)1, (htd::vertex_t)2);
    htd::ConstCollection<htd::vertex_t> edgeIds3 = graph.associatedEdgeIds((htd::vertex_t)2, (htd::vertex_t)1);
    htd::ConstCollection<htd::vertex_t> edgeIds4 = graph.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(elements2.begin(), elements2.end()));

    ASSERT_EQ((std::size_t)0, edgeIds1.size());
    ASSERT_EQ((std::size_t)0, edgeIds2.size());
    ASSERT_EQ((std::size_t)1, edgeIds3.size());
    ASSERT_EQ((std::size_t)1, edgeIds4.size());

    ASSERT_EQ((htd::id_t)1, edgeIds3[0]);
    ASSERT_EQ((htd::id_t)1, edgeIds4[0]);

    const htd::Hyperedge & hyperedge1 = graph.hyperedge((htd::id_t)1);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_TRUE(hyperedge1.contains((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge1.contains((htd::vertex_t)2));
    ASSERT_FALSE(hyperedge1.contains((htd::vertex_t)3));

    const std::vector<htd::vertex_t> & hyperedgeElements1 = hyperedge1.elements();

    ASSERT_EQ((std::size_t)2, hyperedgeElements1.size());
    ASSERT_EQ((htd::vertex_t)2, hyperedgeElements1[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedgeElements1[1]);

    const std::vector<htd::vertex_t> & sortedHyperedgeElements1 = hyperedge1.sortedElements();

    ASSERT_EQ((std::size_t)2, sortedHyperedgeElements1.size());
    ASSERT_EQ((htd::vertex_t)1, sortedHyperedgeElements1[0]);
    ASSERT_EQ((htd::vertex_t)2, sortedHyperedgeElements1[1]);

    ASSERT_EQ((std::size_t)1, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)1, graph.neighborCount((htd::vertex_t)2));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    ASSERT_FALSE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)3));

    delete libraryInstance;
}

TEST(GraphTest, CheckSelfLoop)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph(libraryInstance, 2);

    std::vector<htd::vertex_t> edge11 { 1, 1 };
    std::vector<htd::vertex_t> edge12 { 1, 2 };
    std::vector<htd::vertex_t> edge21 { 2, 1 };
    std::vector<htd::vertex_t> edge122 { 1, 2, 2 };

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    htd::id_t edgeId1 = graph.addEdge((htd::vertex_t)1, (htd::vertex_t)1);

    ASSERT_EQ((std::size_t)1, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_EQ((htd::id_t)1, graph.hyperedgeAtPosition((htd::index_t)0).id());
    ASSERT_EQ((htd::id_t)1, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)1).id());

    ASSERT_TRUE(graph.isEdge(edgeId1));

    ASSERT_EQ((std::size_t)1, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    ASSERT_FALSE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)2));

    ASSERT_EQ((htd::vertex_t)1, graph.neighborAtPosition((htd::vertex_t)1, (htd::index_t)0));

    htd::id_t edgeId2 = graph.addEdge(1, 1);

    ASSERT_EQ(edgeId1, edgeId2);

    ASSERT_EQ((std::size_t)1, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_EQ((htd::id_t)1, graph.hyperedgeAtPosition((htd::index_t)0).id());
    ASSERT_EQ((htd::id_t)1, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)1).id());

    ASSERT_TRUE(graph.isEdge(edgeId2));

    ASSERT_EQ((std::size_t)1, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)2));

    ASSERT_EQ((htd::vertex_t)1, graph.neighborAtPosition((htd::vertex_t)1, (htd::index_t)0));

    ASSERT_EQ((std::size_t)1, graph.hyperedges().size());

    ASSERT_TRUE(graph.isEdge(std::vector<htd::vertex_t> { 1, 1 }));

    ASSERT_TRUE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge11)));

    graph.removeEdge(edgeId1);

    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    htd::id_t edgeId3 = graph.addEdge(1, 2);

    ASSERT_EQ((std::size_t)1, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0).id());
    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)1).id());
    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)2).id());

    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 1, 1 }));
    ASSERT_TRUE(graph.isEdge(std::vector<htd::vertex_t> { 1, 2 }));
    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 2, 1 }));

    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge11)));
    ASSERT_TRUE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge12)));
    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge21)));

    graph.removeEdge(edgeId3);

    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));

    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 1, 1 }));
    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 1, 2 }));
    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 2, 1 }));

    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge11)));
    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge12)));
    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge21)));

    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)0, graph.neighborCount((htd::vertex_t)2));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    ASSERT_FALSE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)2));

    ASSERT_FALSE(graph.isEdge(std::vector<htd::vertex_t> { 1, 2, 2 }));

    ASSERT_FALSE(graph.isEdge(htd::ConstCollection<htd::vertex_t>::getInstance(edge122)));

    delete libraryInstance;
}

TEST(GraphTest, CheckGraphModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph(libraryInstance, 3);

    ASSERT_EQ((std::size_t)3, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    htd::id_t edgeId1 = graph.addEdge(2, 1);

    ASSERT_EQ((std::size_t)1, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId1));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId1).size());

    graph.removeVertex(3);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)1, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId1));

    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId1).size());

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.removeEdge(edgeId1);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.addVertices(2);

    ASSERT_EQ((std::size_t)4, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_EQ((htd::vertex_t)1, graph.vertexAtPosition(0));
    ASSERT_EQ((htd::vertex_t)2, graph.vertexAtPosition(1));
    ASSERT_EQ((htd::vertex_t)4, graph.vertexAtPosition(2));
    ASSERT_EQ((htd::vertex_t)5, graph.vertexAtPosition(3));

    graph.addEdge(4, 5);

    ASSERT_EQ((std::size_t)1, graph.edgeCount());

    graph.removeEdge(4, 5);

    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    delete libraryInstance;
}

TEST(GraphTest, CheckCopyConstructors)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Graph graph1(libraryInstance, 2);

    ASSERT_EQ((std::size_t)2, graph1.vertexCount());
    ASSERT_EQ((std::size_t)0, graph1.edgeCount());

    htd::Graph graph2(graph1);

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)0, graph2.edgeCount());

    htd::id_t edgeId1 = graph2.addEdge((htd::vertex_t)1, (htd::vertex_t)2);

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)1, graph2.edgeCount());

    htd::Graph graph3(libraryInstance);

    ASSERT_EQ((std::size_t)0, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    graph3 = graph1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    graph3 = graph2;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)1, graph3.edgeCount());
    ASSERT_TRUE(graph3.isEdge(edgeId1));

    const htd::IGraph & graphReference1 = graph1;

    graph3 = graphReference1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    htd::Graph graph4(graphReference1);

    ASSERT_EQ((std::size_t)2, graph4.vertexCount());
    ASSERT_EQ((std::size_t)0, graph4.edgeCount());
    ASSERT_FALSE(graph4.isEdge(edgeId1));

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
