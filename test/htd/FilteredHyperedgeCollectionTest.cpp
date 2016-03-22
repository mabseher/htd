/*
 * File:   FilteredHyperedgeCollectionTest.cpp
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

class FilteredHyperedgeCollectionTest : public ::testing::Test
{
    public:
        FilteredHyperedgeCollectionTest(void)
        {

        }

        ~FilteredHyperedgeCollectionTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(FilteredHyperedgeCollectionTest, TestEmptyHyperedgeCollection)
{
    htd::FilteredHyperedgeCollection hyperedges;

    ASSERT_EQ((std::size_t)0, hyperedges.size());

    ASSERT_EQ(0, std::distance(hyperedges.begin(), hyperedges.end()));

    ASSERT_TRUE(hyperedges == hyperedges);
    ASSERT_FALSE(hyperedges != hyperedges);

    hyperedges.restrictTo(std::vector<htd::vertex_t> { });

    ASSERT_EQ((std::size_t)0, hyperedges.size());

    ASSERT_EQ(0, std::distance(hyperedges.begin(), hyperedges.end()));

    ASSERT_TRUE(hyperedges == hyperedges);
    ASSERT_FALSE(hyperedges != hyperedges);

    hyperedges.restrictTo(std::vector<htd::vertex_t> { 1, 2, 3 });

    ASSERT_EQ((std::size_t)0, hyperedges.size());

    ASSERT_EQ(0, std::distance(hyperedges.begin(), hyperedges.end()));

    ASSERT_TRUE(hyperedges == hyperedges);
    ASSERT_FALSE(hyperedges != hyperedges);
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
