/*
 * File:   BucketEliminationTreeDecompositionAlgorithmTest.cpp
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

class BucketEliminationTreeDecompositionAlgorithmTest : public ::testing::Test
{
    public:
        BucketEliminationTreeDecompositionAlgorithmTest(void)
        {

        }

        ~BucketEliminationTreeDecompositionAlgorithmTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(CheckResultEmptyGraph, BucketEliminationTreeDecompositionAlgorithmTest)
{
    htd::Graph graph;

    htd::BucketEliminationTreeDecompositionAlgorithm algorithm;

    htd::ITreeDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_EQ(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), (std::size_t)0);

    ASSERT_EQ(decomposition->root(), (htd::vertex_t)1);

    const std::vector<htd::vertex_t> & bag = decomposition->bagContent(1);

    EXPECT_EQ(bag.size(), (std::size_t)0);

    delete decomposition;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
