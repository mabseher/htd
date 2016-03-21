/*
 * File:   MinFillOrderingAlgorithmTest.cpp
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

class MinFillOrderingAlgorithmTest : public ::testing::Test
{
    public:
        MinFillOrderingAlgorithmTest(void)
        {

        }

        ~MinFillOrderingAlgorithmTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(MinFillOrderingAlgorithmTest, CheckEmptyGraph)
{
    htd::MultiHypergraph graph;

    htd::MinFillOrderingAlgorithm algorithm;

    const htd::ConstCollection<htd::vertex_t> & ordering = algorithm.computeOrdering(graph);

    ASSERT_TRUE(ordering.empty());
}

TEST(MinFillOrderingAlgorithmTest, CheckSize1Graph)
{
    htd::MultiHypergraph graph(1);

    htd::MinFillOrderingAlgorithm algorithm;

    const htd::ConstCollection<htd::vertex_t> & ordering = algorithm.computeOrdering(graph);

    ASSERT_EQ((std::size_t)1, ordering.size());
    ASSERT_EQ((htd::vertex_t)1, ordering[0]);
}

TEST(MinFillOrderingAlgorithmTest, CheckSize2Graph)
{
    htd::MultiHypergraph graph(2);

    htd::MinFillOrderingAlgorithm algorithm;

    const htd::ConstCollection<htd::vertex_t> & ordering = algorithm.computeOrdering(graph);

    ASSERT_EQ((std::size_t)2, ordering.size());

    if ((ordering[0] != 1 || ordering[1] != 2) && (ordering[0] != 2 || ordering[1] != 1))
    {
        FAIL();
    }
}

TEST(MinFillOrderingAlgorithmTest, CheckSimpleGraph1)
{
    htd::MultiHypergraph graph(7);

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);
    graph.addEdge(3, 4);
    graph.addEdge(3, 7);

    htd::MinFillOrderingAlgorithm algorithm;

    const htd::ConstCollection<htd::vertex_t> & ordering = algorithm.computeOrdering(graph);

    ASSERT_EQ((std::size_t)7, ordering.size());

    htd::index_t position1 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 1));
    htd::index_t position2 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 2));
    htd::index_t position3 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 3));
    htd::index_t position4 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 4));
    htd::index_t position5 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 5));
    htd::index_t position6 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 6));
    htd::index_t position7 = std::distance(ordering.begin(), std::find(ordering.begin(), ordering.end(), 7));

    ASSERT_LT(position1, (htd::index_t)5);
    ASSERT_LT(position4, (htd::index_t)5);
    ASSERT_LT(position5, (htd::index_t)5);
    ASSERT_LT(position6, (htd::index_t)5);
    ASSERT_LT(position7, (htd::index_t)5);
    ASSERT_GE(position2, (htd::index_t)5);
    ASSERT_GE(position3, (htd::index_t)5);
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
