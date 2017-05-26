/*
 * File:   HypergraphTest.cpp
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

class HypergraphTest : public ::testing::Test
{
    public:
        HypergraphTest(void)
        {

        }

        virtual ~HypergraphTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(HypergraphTest, CheckEmptyGraph)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph(libraryInstance);

    ASSERT_EQ((std::size_t)0, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_EQ((std::size_t)0, graph.vertices().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());

    ASSERT_EQ((std::size_t)0, graph.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, graph.isolatedVertices().size());

    ASSERT_TRUE(graph.isConnected());

    delete libraryInstance;
}

TEST(HypergraphTest, CheckSizeInitializedGraph1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph(libraryInstance, 1);

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

TEST(HypergraphTest, CheckSizeInitializedGraph2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph(libraryInstance, 3);

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

    graph.addEdge(htd::Hyperedge((htd::id_t)1, (htd::vertex_t)2, (htd::vertex_t)1));

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

    graph.addEdge(htd::Hyperedge((htd::id_t)5, std::vector<htd::vertex_t> { 1, 2, 3 }));

    std::vector<htd::vertex_t> edgeElements2 { 1, 2, 3 };

    ASSERT_TRUE(graph.isEdge((htd::id_t)2));
    ASSERT_TRUE(graph.isEdge(edgeElements2));
    ASSERT_TRUE(graph.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())));

    ASSERT_EQ((std::size_t)2, graph.edgeCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)2, graph.edgeCount((htd::vertex_t)2));
    ASSERT_EQ((std::size_t)1, graph.edgeCount((htd::vertex_t)3));

    std::vector<htd::vertex_t> elements3 { 1, 2, 3 };
    std::vector<htd::vertex_t> elements4 { 3, 2, 1 };

    htd::ConstCollection<htd::vertex_t> edgeIds5 = graph.associatedEdgeIds(elements3);
    htd::ConstCollection<htd::vertex_t> edgeIds6 = graph.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(elements4.begin(), elements4.end()));

    ASSERT_EQ((std::size_t)1, edgeIds5.size());
    ASSERT_EQ((std::size_t)0, edgeIds6.size());

    ASSERT_EQ((htd::id_t)2, edgeIds5[0]);

    const htd::Hyperedge & hyperedge2 = graph.hyperedge((htd::id_t)2);

    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_EQ((std::size_t)3, hyperedge2.size());
    ASSERT_TRUE(hyperedge2.contains((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.contains((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge2.contains((htd::vertex_t)3));

    const std::vector<htd::vertex_t> & hyperedgeElements2 = hyperedge2.elements();

    ASSERT_EQ((std::size_t)3, hyperedgeElements2.size());
    ASSERT_EQ((htd::vertex_t)1, hyperedgeElements2[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedgeElements2[1]);
    ASSERT_EQ((htd::vertex_t)3, hyperedgeElements2[2]);

    const std::vector<htd::vertex_t> & sortedHyperedgeElements2 = hyperedge2.sortedElements();

    ASSERT_EQ((std::size_t)3, sortedHyperedgeElements2.size());
    ASSERT_EQ((htd::vertex_t)1, sortedHyperedgeElements2[0]);
    ASSERT_EQ((htd::vertex_t)2, sortedHyperedgeElements2[1]);
    ASSERT_EQ((htd::vertex_t)3, sortedHyperedgeElements2[2]);

    ASSERT_EQ((std::size_t)2, graph.neighborCount((htd::vertex_t)1));
    ASSERT_EQ((std::size_t)2, graph.neighborCount((htd::vertex_t)2));
    ASSERT_EQ((std::size_t)2, graph.neighborCount((htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    ASSERT_TRUE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)3, (htd::vertex_t)3));

    delete libraryInstance;
}

TEST(HypergraphTest, CheckSelfLoop)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph(libraryInstance, 2);

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

    std::vector<htd::vertex_t> edgeElements2 = { 1, 1 };

    htd::id_t edgeId2 = graph.addEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end()));

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

    graph.removeEdge(edgeId1);

    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    htd::id_t edgeId3 = graph.addEdge(std::vector<htd::vertex_t> { 1, 2 });

    ASSERT_EQ((std::size_t)1, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)1, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0).id());
    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)1).id());
    ASSERT_EQ((htd::id_t)2, graph.hyperedgeAtPosition((htd::index_t)0, (htd::vertex_t)2).id());

    graph.removeEdge(edgeId3);

    ASSERT_EQ((std::size_t)0, graph.hyperedges().size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)1).size());
    ASSERT_EQ((std::size_t)0, graph.hyperedges((htd::vertex_t)2).size());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));

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

    delete libraryInstance;
}

TEST(HypergraphTest, CheckGraphModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph(libraryInstance, 3);

    ASSERT_EQ((std::size_t)3, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    htd::id_t edgeId1 = graph.addEdge(std::vector<htd::vertex_t> { 1 });

    ASSERT_EQ((std::size_t)1, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId1));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    htd::id_t edgeId2 = graph.addEdge(std::vector<htd::vertex_t> { 2, 1 });

    ASSERT_EQ((std::size_t)2, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId2));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    htd::id_t edgeId3 = graph.addEdge(std::vector<htd::vertex_t> { 1, 2, 3 });

    ASSERT_EQ((std::size_t)3, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId3));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));

    std::vector<htd::vertex_t> edgeElements4 { 2, 1, 3, 3 };

    htd::id_t edgeId4 = graph.addEdge(htd::ConstCollection<htd::vertex_t>(edgeElements4.begin(), edgeElements4.end()));

    ASSERT_EQ((std::size_t)4, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId4));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)3));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)3, (htd::vertex_t)3));


    ASSERT_EQ((std::size_t)1, graph.hyperedge(edgeId1).size());
    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId2).size());
    ASSERT_EQ((std::size_t)3, graph.hyperedge(edgeId3).size());
    ASSERT_EQ((std::size_t)4, graph.hyperedge(edgeId4).size());

    graph.removeVertex(3);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)4, graph.edgeCount());
    ASSERT_TRUE(graph.isEdge(edgeId1));
    ASSERT_TRUE(graph.isEdge(edgeId2));
    ASSERT_TRUE(graph.isEdge(edgeId3));
    ASSERT_TRUE(graph.isEdge(edgeId4));

    ASSERT_EQ((std::size_t)1, graph.hyperedge(edgeId1).size());
    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId2).size());
    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId3).size());
    ASSERT_EQ((std::size_t)2, graph.hyperedge(edgeId4).size());

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.removeEdge(edgeId1);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)3, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_TRUE(graph.isEdge(edgeId2));
    ASSERT_TRUE(graph.isEdge(edgeId3));
    ASSERT_TRUE(graph.isEdge(edgeId4));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.removeEdge(edgeId3);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)2, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_TRUE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_TRUE(graph.isEdge(edgeId4));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.removeEdge(edgeId2);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)1, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_TRUE(graph.isEdge(edgeId4));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    graph.removeEdge(edgeId4);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)0, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::Hyperedge hyperedge1((htd::id_t)1, std::vector<htd::vertex_t> { 1 });

    htd::id_t edgeId5 = graph.addEdge(hyperedge1);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)1, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::id_t edgeId6 = graph.addEdge(htd::Hyperedge((htd::id_t)1, std::vector<htd::vertex_t> { 1 }));

    ASSERT_EQ(edgeId5, edgeId6);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)1, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));
    ASSERT_TRUE(graph.isEdge(edgeId6));

    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::Hyperedge hyperedge2((htd::id_t)1, std::vector<htd::vertex_t> { 1, 1 });

    htd::id_t edgeId7 = graph.addEdge(hyperedge2);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)2, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));
    ASSERT_TRUE(graph.isEdge(edgeId6));
    ASSERT_TRUE(graph.isEdge(edgeId7));

    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::id_t edgeId8 = graph.addEdge(htd::Hyperedge((htd::id_t)1, std::vector<htd::vertex_t> { 1, 1 }));

    ASSERT_EQ(edgeId7, edgeId8);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)2, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));
    ASSERT_TRUE(graph.isEdge(edgeId6));
    ASSERT_TRUE(graph.isEdge(edgeId7));
    ASSERT_TRUE(graph.isEdge(edgeId8));

    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::Hyperedge hyperedge3((htd::id_t)1, std::vector<htd::vertex_t> { 1, 2, 2, 1 });

    htd::id_t edgeId9 = graph.addEdge(hyperedge3);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)3, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));
    ASSERT_TRUE(graph.isEdge(edgeId6));
    ASSERT_TRUE(graph.isEdge(edgeId7));
    ASSERT_TRUE(graph.isEdge(edgeId8));
    ASSERT_TRUE(graph.isEdge(edgeId9));

    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    htd::id_t edgeId10 = graph.addEdge(htd::Hyperedge((htd::id_t)1, std::vector<htd::vertex_t> { 1, 2, 2, 1 }));

    ASSERT_EQ(edgeId9, edgeId10);

    ASSERT_EQ((std::size_t)2, graph.vertexCount());
    ASSERT_EQ((std::size_t)3, graph.edgeCount());

    ASSERT_FALSE(graph.isEdge(edgeId1));
    ASSERT_FALSE(graph.isEdge(edgeId2));
    ASSERT_FALSE(graph.isEdge(edgeId3));
    ASSERT_FALSE(graph.isEdge(edgeId4));
    ASSERT_TRUE(graph.isEdge(edgeId5));
    ASSERT_TRUE(graph.isEdge(edgeId6));
    ASSERT_TRUE(graph.isEdge(edgeId7));
    ASSERT_TRUE(graph.isEdge(edgeId8));
    ASSERT_TRUE(graph.isEdge(edgeId9));
    ASSERT_TRUE(graph.isEdge(edgeId10));

    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)2));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)1));
    ASSERT_TRUE(graph.isNeighbor((htd::vertex_t)2, (htd::vertex_t)2));

    delete libraryInstance;
}

TEST(HypergraphTest, CheckCopyConstructors)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Hypergraph graph1(libraryInstance, 2);

    ASSERT_EQ((std::size_t)2, graph1.vertexCount());
    ASSERT_EQ((std::size_t)0, graph1.edgeCount());

    htd::Hypergraph graph2(graph1);

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)0, graph2.edgeCount());

    htd::id_t edgeId1 = graph2.addEdge((htd::vertex_t)1, (htd::vertex_t)2);

    ASSERT_EQ((std::size_t)2, graph2.vertexCount());
    ASSERT_EQ((std::size_t)1, graph2.edgeCount());

    htd::Hypergraph graph3(libraryInstance);

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

    const htd::IHypergraph & graphReference1 = graph1;

    graph3 = graphReference1;

    ASSERT_EQ((std::size_t)2, graph3.vertexCount());
    ASSERT_EQ((std::size_t)0, graph3.edgeCount());
    ASSERT_FALSE(graph3.isEdge(edgeId1));

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
