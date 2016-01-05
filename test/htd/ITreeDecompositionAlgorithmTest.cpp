/*
 * File:   ITreeDecompositionAlgorithmTest.cpp
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

TEST(ITreeDecompositionAlgorithmTest, DecompositionTest01)
{
    htd::Hypergraph graph(3);

    std::vector<htd::vertex_t> vertices;

    ASSERT_EQ((std::size_t)3, graph.vertexCount());

    const htd::ConstCollection<htd::vertex_t> & collection = graph.vertices();

    std::copy(collection.begin(), collection.end(), std::back_inserter(vertices));

    ASSERT_EQ((std::size_t)3, vertices.size());

    //TODO Use GoogleMock's ASSERT_THAT to compare whole collections at once!
    ASSERT_EQ((htd::vertex_t)1, vertices[0]);
    ASSERT_EQ((htd::vertex_t)2, vertices[1]);
    ASSERT_EQ((htd::vertex_t)3, vertices[2]);

    graph.addEdge(1,2);
    graph.addEdge(1,3);

    ASSERT_EQ((std::size_t)2, graph.edgeCount());

    ASSERT_TRUE(graph.isNeighbor(1, 2));
    ASSERT_TRUE(graph.isNeighbor(1, 3));
    ASSERT_TRUE(graph.isNeighbor(2, 1));
    ASSERT_TRUE(graph.isNeighbor(3, 1));
    ASSERT_FALSE(graph.isNeighbor(2, 3));
    ASSERT_FALSE(graph.isNeighbor(3, 2));

    ASSERT_TRUE(graph.isConnected(1, 1));
    ASSERT_TRUE(graph.isConnected(1, 2));
    ASSERT_TRUE(graph.isConnected(1, 3));
    ASSERT_TRUE(graph.isConnected(2, 1));
    ASSERT_TRUE(graph.isConnected(2, 2));
    ASSERT_TRUE(graph.isConnected(2, 3));
    ASSERT_TRUE(graph.isConnected(3, 1));
    ASSERT_TRUE(graph.isConnected(3, 2));
    ASSERT_TRUE(graph.isConnected(3, 3));

    htd::IOrderingAlgorithm * orderingAlgorithm = new htd::MinFillOrderingAlgorithm();

    const htd::ConstCollection<htd::vertex_t> & ordering = orderingAlgorithm->computeOrdering(graph);

    ASSERT_EQ((std::size_t)3, ordering.size());

    htd::BucketEliminationTreeDecompositionAlgorithm algorithm;

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    ASSERT_LE((std::size_t)2, decomposition->maximumBagSize());
    ASSERT_GE((std::size_t)3, decomposition->maximumBagSize());

    delete orderingAlgorithm;

    delete decomposition;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
