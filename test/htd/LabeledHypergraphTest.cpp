/*
 * File:   LabeledHypergraphTest.cpp
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

class LabeledHypergraphTest : public ::testing::Test
{
    public:
        LabeledHypergraphTest(void)
        {

        }

        virtual ~LabeledHypergraphTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(LabeledHypergraphTest, CheckEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    ASSERT_EQ((std::size_t)0, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_EQ((std::size_t)0, graph.vertices().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());

    ASSERT_EQ((std::size_t)0, graph.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, graph.isolatedVertices().size());

    ASSERT_TRUE(graph.isConnected());

    delete libraryInstance;
}

TEST(LabeledHypergraphTest, CheckSize1Graph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance, 1);

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

TEST(LabeledHypergraphTest, CheckSize3Graph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    graph.addVertices(3);

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

TEST(LabeledHypergraphTest, CheckSelfLoop)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    graph.addVertices(2);

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

TEST(LabeledHypergraphTest, CheckGraphModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    graph.addVertices(3);

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

    delete libraryInstance;
}

TEST(LabeledHypergraphTest, CheckCopyConstructors)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph1(libraryInstance);

    graph1.addVertices(2);

    graph1.setVertexLabel("Label", 1, new htd::Label<int>(1));

    ASSERT_EQ((std::size_t)2, graph1.vertexCount());
    ASSERT_EQ((std::size_t)0, graph1.edgeCount());

    htd::LabeledHypergraph graph2(graph1);

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)0, graph2.edgeCount());

    htd::id_t edgeId1 = graph2.addEdge((htd::vertex_t)1, (htd::vertex_t)2);

    graph2.setEdgeLabel("Label", edgeId1, new htd::Label<int>(123));

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)1, graph2.edgeCount());

    htd::LabeledHypergraph graph3(libraryInstance);

    ASSERT_EQ((std::size_t)0, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    graph3 = graph1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    ASSERT_TRUE(graph3.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph3.vertexLabel("Label", 1)));

    graph3 = graph2;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)1, graph3.edgeCount());
    ASSERT_TRUE(graph3.isEdge(edgeId1));

    ASSERT_TRUE(graph3.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph3.vertexLabel("Label", 1)));

    ASSERT_TRUE(graph3.isLabeledEdge("Label", edgeId1));
    ASSERT_EQ(123, htd::accessLabel<int>(graph3.edgeLabel("Label", 1)));

    const htd::IHypergraph & hypergraphReference1 = graph1;

    const htd::ILabeledHypergraph & labeledHypergraphReference1 = graph1;

    graph3 = hypergraphReference1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    ASSERT_FALSE(graph3.isLabeledVertex("Label", 1));
    ASSERT_FALSE(graph3.isLabeledEdge("Label", edgeId1));

    htd::LabeledHypergraph graph4(hypergraphReference1);

    ASSERT_EQ((std::size_t)2, graph4.vertexCount());
    ASSERT_EQ((std::size_t)0, graph4.edgeCount());
    ASSERT_FALSE(graph4.isEdge(edgeId1));

    ASSERT_FALSE(graph4.isLabeledVertex("Label", 1));
    ASSERT_FALSE(graph4.isLabeledEdge("Label", edgeId1));

    graph3 = labeledHypergraphReference1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    ASSERT_TRUE(graph3.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph3.vertexLabel("Label", 1)));
    ASSERT_FALSE(graph3.isLabeledEdge("Label", edgeId1));

    htd::LabeledHypergraph graph5(labeledHypergraphReference1);

    ASSERT_EQ((std::size_t)2, graph5.vertexCount());
    ASSERT_EQ((std::size_t)0, graph5.edgeCount());
    ASSERT_FALSE(graph5.isEdge(edgeId1));

    ASSERT_TRUE(graph5.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph5.vertexLabel("Label", 1)));
    ASSERT_FALSE(graph5.isLabeledEdge("Label", edgeId1));

    graph3 = labeledHypergraphReference1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    ASSERT_TRUE(graph3.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph3.vertexLabel("Label", 1)));
    ASSERT_FALSE(graph3.isLabeledEdge("Label", edgeId1));

    htd::LabeledHypergraph graph6(labeledHypergraphReference1);

    ASSERT_EQ((std::size_t)2, graph6.vertexCount());
    ASSERT_EQ((std::size_t)0, graph6.edgeCount());
    ASSERT_FALSE(graph6.isEdge(edgeId1));

    ASSERT_TRUE(graph6.isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(graph6.vertexLabel("Label", 1)));
    ASSERT_FALSE(graph6.isLabeledEdge("Label", edgeId1));

    htd::LabeledHypergraph * clonedGraph = graph6.clone();

    ASSERT_EQ((std::size_t)2, clonedGraph->vertexCount());
    ASSERT_EQ((std::size_t)0, clonedGraph->edgeCount());
    ASSERT_FALSE(clonedGraph->isEdge(edgeId1));

    ASSERT_TRUE(clonedGraph->isLabeledVertex("Label", 1));
    ASSERT_EQ(1, htd::accessLabel<int>(clonedGraph->vertexLabel("Label", 1)));
    ASSERT_FALSE(clonedGraph->isLabeledEdge("Label", edgeId1));

    delete clonedGraph;
    delete libraryInstance;
}

TEST(LabeledHypergraphTest, TestVertexLabelModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    graph.addVertices(3);

    graph.setVertexLabel("Label", 1, new htd::Label<int>(1));
    graph.setVertexLabel("Label", 2, new htd::Label<int>(2));
    graph.setVertexLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, graph.labelCount());
    ASSERT_EQ((std::size_t)1, graph.labelNames().size());
    ASSERT_EQ("Label", graph.labelNames()[0]);
    ASSERT_EQ("Label", graph.labelNameAtPosition(0));

    ASSERT_FALSE(graph.isLabeledVertex("Label", 0));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 1));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 2));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    graph.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(graph.isLabeledVertex("Label", 0));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 1));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 2));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    graph.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(graph.isLabeledVertex("Label", 0));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 1));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 2));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    graph.swapVertexLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    graph.swapVertexLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    graph.swapVertexLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    htd::ILabel * exportedLabel = graph.transferVertexLabel("Label", 1);

    ASSERT_FALSE(graph.isLabeledVertex("Label", 0));
    ASSERT_FALSE(graph.isLabeledVertex("Label", 1));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 2));
    ASSERT_TRUE(graph.isLabeledVertex("Label", 3));

    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    graph.setVertexLabel("Label2", 2, new htd::Label<int>(1));
    graph.setVertexLabel("Label2", 3, new htd::Label<int>(2));

    graph.swapVertexLabel("Label", 2, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(graph.vertexLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.vertexLabel("Label2", 3)));

    graph.removeVertexLabel("Label", 2);
    graph.removeVertexLabel("Label", htd::Vertex::UNKNOWN);
    graph.removeVertexLabel("Label3", 2);
    graph.removeVertexLabel("Label3", htd::Vertex::UNKNOWN);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.vertexLabel("Label2", 2)));

    delete exportedLabel;

    delete libraryInstance;
}

TEST(LabeledHypergraphTest, TestEdgeLabelModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::LabeledHypergraph graph(libraryInstance);

    graph.addVertices(3);

    graph.addEdge(1, 1);
    graph.addEdge(2, 2);
    graph.addEdge(3, 3);

    graph.setEdgeLabel("Label", 1, new htd::Label<int>(1));
    graph.setEdgeLabel("Label", 2, new htd::Label<int>(2));
    graph.setEdgeLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, graph.labelCount());
    ASSERT_EQ((std::size_t)1, graph.labelNames().size());
    ASSERT_EQ("Label", graph.labelNames()[0]);
    ASSERT_EQ("Label", graph.labelNameAtPosition(0));

    ASSERT_FALSE(graph.isLabeledEdge("Label", 0));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 1));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 2));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    graph.setEdgeLabel("Label", 3, newLabel);

    ASSERT_FALSE(graph.isLabeledEdge("Label", 0));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 1));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 2));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    graph.setEdgeLabel("Label", 3, newLabel);

    ASSERT_TRUE(graph.isLabeledEdge("Label", 1));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 2));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 3));
    ASSERT_FALSE(graph.isLabeledEdge("Label", 0));

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    graph.swapEdgeLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    graph.swapEdgeLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    graph.swapEdgeLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    htd::ILabel * exportedLabel = graph.transferEdgeLabel("Label", 1);

    ASSERT_FALSE(graph.isLabeledEdge("Label", 1));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 2));
    ASSERT_TRUE(graph.isLabeledEdge("Label", 3));
    ASSERT_FALSE(graph.isLabeledEdge("Label", 0));

    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    graph.setEdgeLabel("Label2", 2, new htd::Label<int>(1));
    graph.setEdgeLabel("Label2", 3, new htd::Label<int>(2));

    graph.swapEdgeLabel("Label", 2, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(graph.edgeLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(graph.edgeLabel("Label2", 3)));

    graph.removeEdgeLabel("Label", 2);
    graph.removeEdgeLabel("Label", htd::Vertex::UNKNOWN);
    graph.removeEdgeLabel("Label3", 2);
    graph.removeEdgeLabel("Label3", htd::Vertex::UNKNOWN);

    ASSERT_EQ(1, htd::accessLabel<int>(graph.edgeLabel("Label2", 2)));

    delete exportedLabel;

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
