/*
 * File:   MultiHypergraphTest.cpp
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

class MultiHypergraphTest : public ::testing::Test
{
    public:
        MultiHypergraphTest(void)
        {

        }

        ~MultiHypergraphTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(MultiHypergraphTest, CheckEmptyGraph)
{
    htd::MultiHypergraph graph;

    ASSERT_EQ(graph.vertexCount(), (std::size_t)0);
    ASSERT_EQ(graph.edgeCount(), (std::size_t)0);

    ASSERT_EQ(graph.vertices().size(), (std::size_t)0);
    ASSERT_EQ(graph.hyperedges().size(), (std::size_t)0);

    ASSERT_EQ(graph.isolatedVertexCount(), (std::size_t)0);
    ASSERT_EQ(graph.isolatedVertices().size(), (std::size_t)0);

    ASSERT_TRUE(graph.isConnected());
}

TEST(MultiHypergraphTest, CheckSizeInitializedGraph1)
{
    htd::MultiHypergraph graph(1);

    ASSERT_EQ(graph.vertexCount(), (std::size_t)1);
    ASSERT_EQ(graph.edgeCount(), (std::size_t)0);

    htd::ConstCollection<htd::vertex_t> vertices = graph.vertices();

    ASSERT_EQ(vertices.size(), (std::size_t)1);
    ASSERT_EQ(graph.hyperedges().size(), (std::size_t)0);

    htd::ConstCollection<htd::vertex_t> isolatedVertices = graph.isolatedVertices();

    ASSERT_EQ(graph.isolatedVertexCount(), (std::size_t)1);
    ASSERT_EQ(isolatedVertices.size(), (std::size_t)1);

    ASSERT_EQ(vertices[0], (htd::vertex_t)1);
    ASSERT_EQ(graph.vertexAtPosition((htd::index_t)0), (htd::vertex_t)1);
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)1));

    ASSERT_EQ(isolatedVertices[0], (htd::vertex_t)1);
    ASSERT_EQ(graph.isolatedVertexAtPosition((htd::index_t)0), (htd::vertex_t)1);
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)1));

    ASSERT_EQ(graph.edgeCount((htd::vertex_t)1), (std::size_t)0);
    ASSERT_EQ(graph.hyperedges((htd::vertex_t)1).size(), (std::size_t)0);

    ASSERT_EQ(graph.neighborCount((htd::vertex_t)1), (std::size_t)0);
    ASSERT_FALSE(graph.isNeighbor((htd::vertex_t)1, (htd::vertex_t)1));

    ASSERT_TRUE(graph.isConnected());
    ASSERT_TRUE(graph.isConnected((htd::vertex_t)1, (htd::vertex_t)1));
}

TEST(MultiHypergraphTest, CheckSizeInitializedGraph2)
{
    htd::MultiHypergraph graph(3);

    ASSERT_EQ(graph.vertexCount(), (std::size_t)3);
    ASSERT_EQ(graph.edgeCount(), (std::size_t)0);

    htd::ConstCollection<htd::vertex_t> vertices = graph.vertices();

    ASSERT_EQ(vertices.size(), (std::size_t)3);
    ASSERT_EQ(graph.hyperedges().size(), (std::size_t)0);

    htd::ConstCollection<htd::vertex_t> isolatedVertices = graph.isolatedVertices();

    ASSERT_EQ(graph.isolatedVertexCount(), (std::size_t)3);
    ASSERT_EQ(isolatedVertices.size(), (std::size_t)3);

    ASSERT_EQ(vertices[0], (htd::vertex_t)1);
    ASSERT_EQ(vertices[1], (htd::vertex_t)2);
    ASSERT_EQ(vertices[2], (htd::vertex_t)3);
    ASSERT_EQ(graph.vertexAtPosition((htd::index_t)0), (htd::vertex_t)1);
    ASSERT_EQ(graph.vertexAtPosition((htd::index_t)1), (htd::vertex_t)2);
    ASSERT_EQ(graph.vertexAtPosition((htd::index_t)2), (htd::vertex_t)3);
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)1));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)2));
    ASSERT_TRUE(graph.isVertex((htd::vertex_t)3));

    ASSERT_EQ(isolatedVertices[0], (htd::vertex_t)1);
    ASSERT_EQ(isolatedVertices[1], (htd::vertex_t)2);
    ASSERT_EQ(isolatedVertices[2], (htd::vertex_t)3);
    ASSERT_EQ(graph.isolatedVertexAtPosition((htd::index_t)0), (htd::vertex_t)1);
    ASSERT_EQ(graph.isolatedVertexAtPosition((htd::index_t)1), (htd::vertex_t)2);
    ASSERT_EQ(graph.isolatedVertexAtPosition((htd::index_t)2), (htd::vertex_t)3);
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)1));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)2));
    ASSERT_TRUE(graph.isIsolatedVertex((htd::vertex_t)3));

    ASSERT_EQ(graph.edgeCount((htd::vertex_t)1), (std::size_t)0);
    ASSERT_EQ(graph.hyperedges((htd::vertex_t)1).size(), (std::size_t)0);

    ASSERT_EQ(graph.neighborCount((htd::vertex_t)1), (std::size_t)0);
    ASSERT_EQ(graph.neighborCount((htd::vertex_t)2), (std::size_t)0);
    ASSERT_EQ(graph.neighborCount((htd::vertex_t)3), (std::size_t)0);
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

    graph.addEdge(htd::Hyperedge((htd::id_t)1, (htd::vertex_t)1, (htd::vertex_t)2));

    ASSERT_TRUE(graph.isEdge((htd::id_t)1));

    std::vector<htd::vertex_t> elements1 { 1, 2 };
    std::vector<htd::vertex_t> elements2 { 2, 3 };

    htd::ConstCollection<htd::vertex_t> edgeIds1 = graph.associatedEdgeIds(elements1);
    htd::ConstCollection<htd::vertex_t> edgeIds2 = graph.associatedEdgeIds(htd::Collection<htd::vertex_t>(elements2.begin(), elements2.end()));

    ASSERT_EQ(edgeIds1.size(), (std::size_t)1);
    ASSERT_EQ(edgeIds2.size(), (std::size_t)0);

    ASSERT_EQ(edgeIds1[0], (htd::id_t)1);

    const htd::Hyperedge & hyperedge1 = graph.hyperedge((std::size_t)1);

    ASSERT_EQ(hyperedge1.id(), (htd::id_t)1);
    ASSERT_EQ(hyperedge1.size(), (std::size_t)2);
    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)2));
    ASSERT_FALSE(hyperedge1.containsVertex((htd::vertex_t)3));

    ASSERT_EQ(graph.neighborCount((htd::vertex_t)1), (std::size_t)1);
    ASSERT_EQ(graph.neighborCount((htd::vertex_t)2), (std::size_t)1);
    ASSERT_EQ(graph.neighborCount((htd::vertex_t)3), (std::size_t)0);
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
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
