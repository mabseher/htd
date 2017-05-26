/*
 * File:   IteratorTest.cpp
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

#include <utility>
#include <vector>

class IteratorTest : public ::testing::Test
{
    public:
        IteratorTest(void)
        {

        }

        virtual ~IteratorTest()
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
    htd::Collection<int> collection2;

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

    ASSERT_TRUE(collection1 == collection2);
    ASSERT_FALSE(collection1 != collection2);
}

TEST(IteratorTest, CheckEmptyConstCollection)
{
    htd::ConstCollection<int> collection1;
    htd::ConstCollection<int> collection2;

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

    ASSERT_TRUE(collection1 == collection2);
    ASSERT_FALSE(collection1 != collection2);
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

    auto begin = collection1.begin();
    auto end = collection1.end();
    auto beginPtr = static_cast<htd::IteratorBase<int> *>(&begin);
    auto endPtr = static_cast<htd::IteratorBase<int> *>(&end);

    ASSERT_TRUE(collection1.begin() == *beginPtr);
    ASSERT_TRUE(collection1.end() == *endPtr);
    ASSERT_TRUE(it1 == *endPtr);

    ASSERT_FALSE(collection1.begin() != *beginPtr);
    ASSERT_FALSE(collection1.end() != *endPtr);
    ASSERT_FALSE(it1 != *endPtr);
}

TEST(IteratorTest, CheckCollectionWrapper2)
{
    std::vector<std::pair<int, int>> values { std::make_pair<int, int>(1, 2) };

    htd::Collection<std::pair<int, int>> collection1 = htd::Collection<std::pair<int, int>>::getInstance(values);

    ASSERT_FALSE(collection1.empty());
    ASSERT_EQ((std::size_t)1, collection1.size());

    auto it1 = collection1.begin();

    ASSERT_TRUE(it1 == collection1.begin());

    ASSERT_EQ(1, it1->first);
    ASSERT_EQ(2, it1->second);

    ++it1;

    ASSERT_TRUE(it1 == collection1.end());
}

TEST(IteratorTest, CheckIteratorCloneMethod1)
{
    htd::Collection<int> collection1;

    auto it1 = collection1.begin();

    auto it2 = it1.clone();

    ASSERT_TRUE(it1 == *it2);
    ASSERT_FALSE(it1 != *it2);

    delete it2;
}

TEST(IteratorTest, CheckIteratorCloneMethod2)
{
    std::vector<int> values { 1, 2, 3 };

    htd::Collection<int> collection1 = htd::Collection<int>::getInstance(values);

    auto it1 = collection1.begin();

    ++it1;

    auto it2 = it1.clone();

    ASSERT_EQ(2, *(*it2));

    ASSERT_TRUE(it1 == *it2);
    ASSERT_FALSE(it1 != *it2);

    delete it2;
}

TEST(IteratorTest, CheckConstCollectionWrapper1)
{
    std::vector<int> values { 1, 2, 3 };

    htd::ConstCollection<int> collection1 = htd::ConstCollection<int>::getInstance(values);

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

    auto begin = collection1.begin();
    auto end = collection1.end();
    auto beginPtr = static_cast<htd::ConstIteratorBase<int> *>(&begin);
    auto endPtr = static_cast<htd::ConstIteratorBase<int> *>(&end);

    ASSERT_TRUE(collection1.begin() == *beginPtr);
    ASSERT_TRUE(collection1.end() == *endPtr);
    ASSERT_TRUE(it1 == *endPtr);

    ASSERT_FALSE(collection1.begin() != *beginPtr);
    ASSERT_FALSE(collection1.end() != *endPtr);
    ASSERT_FALSE(it1 != *endPtr);
}

TEST(IteratorTest, CheckConstCollectionWrapper2)
{
    std::vector<std::pair<int, int>> values { std::make_pair<int, int>(1, 2) };

    htd::ConstCollection<std::pair<int, int>> collection1 = htd::ConstCollection<std::pair<int, int>>::getInstance(values);

    ASSERT_FALSE(collection1.empty());
    ASSERT_EQ((std::size_t)1, collection1.size());

    auto it1 = collection1.begin();

    ASSERT_TRUE(it1 == collection1.begin());

    ASSERT_EQ(1, it1->first);
    ASSERT_EQ(2, it1->second);

    ++it1;

    ASSERT_TRUE(it1 == collection1.end());
}

TEST(IteratorTest, CheckConstIteratorCloneMethod1)
{
    htd::ConstCollection<int> collection1;

    auto it1 = collection1.begin();

    auto it2 = it1.clone();

    ASSERT_TRUE(it1 == *it2);
    ASSERT_FALSE(it1 != *it2);

    delete it2;
}

TEST(IteratorTest, CheckConstIteratorCloneMethod2)
{
    std::vector<int> values { 1, 2, 3 };

    htd::ConstCollection<int> collection1 = htd::ConstCollection<int>::getInstance(values);

    auto it1 = collection1.begin();

    ++it1;

    auto it2 = it1.clone();

    ASSERT_EQ(2, *(*it2));

    ASSERT_TRUE(it1 == *it2);
    ASSERT_FALSE(it1 != *it2);

    delete it2;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
