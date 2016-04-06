/*
 * File:   IteratorTest.cpp
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

class IteratorTest : public ::testing::Test
{
    public:
        IteratorTest(void)
        {

        }

        ~IteratorTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(IteratorTest, CheckEmptyCollection)
{
    htd::Collection<int> collection1;

    ASSERT_TRUE(collection1.empty());
    ASSERT_EQ((std::size_t)0, collection1.size());

    ASSERT_TRUE(collection1.begin() == collection1.begin());
    ASSERT_TRUE(collection1.begin() == collection1.end());
    ASSERT_TRUE(collection1.end() == collection1.begin());
    ASSERT_TRUE(collection1.end() == collection1.end());

    ASSERT_FALSE(collection1.begin() != collection1.begin());
    ASSERT_FALSE(collection1.begin() != collection1.end());
    ASSERT_FALSE(collection1.end() != collection1.begin());
    ASSERT_FALSE(collection1.end() != collection1.end());
}

TEST(IteratorTest, CheckEmptyConstCollection)
{
    htd::ConstCollection<int> collection1;

    ASSERT_TRUE(collection1.empty());
    ASSERT_EQ((std::size_t)0, collection1.size());

    ASSERT_TRUE(collection1.begin() == collection1.begin());
    ASSERT_TRUE(collection1.begin() == collection1.end());
    ASSERT_TRUE(collection1.end() == collection1.begin());
    ASSERT_TRUE(collection1.end() == collection1.end());

    ASSERT_FALSE(collection1.begin() != collection1.begin());
    ASSERT_FALSE(collection1.begin() != collection1.end());
    ASSERT_FALSE(collection1.end() != collection1.begin());
    ASSERT_FALSE(collection1.end() != collection1.end());
}

TEST(IteratorTest, CheckCollectionWrapper1)
{
    std::vector<int> values { 1, 2, 3 };

    htd::Collection<int> collection1 = htd::Collection<int>::getInstance(values);

    ASSERT_FALSE(collection1.empty());
    ASSERT_EQ((std::size_t)3, collection1.size());

    auto it1 = collection1.begin();

    ASSERT_TRUE(it1 == collection1.begin());
    ASSERT_FALSE(it1 != collection1.begin());

    for (htd::index_t index = 0; index < values.size(); ++index)
    {
        ASSERT_EQ(values[index], *it1);

        ++it1;
    }

    ASSERT_TRUE(collection1.begin() == collection1.begin());
    ASSERT_TRUE(collection1.end() == collection1.end());
    ASSERT_TRUE(it1 == collection1.end());

    ASSERT_FALSE(collection1.begin() != collection1.begin());
    ASSERT_FALSE(collection1.end() != collection1.end());
    ASSERT_FALSE(it1 != collection1.end());
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
