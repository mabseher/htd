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

TEST(FilteredHyperedgeCollectionTest, TestConstructors)
{
    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 4, 3);
    htd::Hyperedge h4(4, 5, 5);
    htd::Hyperedge h5(5, 7, 6);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2, h3, h4, h5 };
    std::vector<htd::Hyperedge> inputEdges2 { h1, h2, h3, h4, h5 };
    std::shared_ptr<std::vector<htd::Hyperedge>> inputEdges3 = std::make_shared<std::vector<htd::Hyperedge>>();

    inputEdges3->push_back(h1);
    inputEdges3->push_back(h2);
    inputEdges3->push_back(h3);
    inputEdges3->push_back(h4);
    inputEdges3->push_back(h5);

    htd::FilteredHyperedgeCollection hyperedges1(inputEdges1, std::vector<htd::index_t> { 1, 3, 3, 2 });
    htd::FilteredHyperedgeCollection hyperedges2(inputEdges2, std::vector<htd::index_t> { 1, 3, 2, 3 });

    ASSERT_EQ((std::size_t)4, hyperedges1.size());
    ASSERT_EQ((std::size_t)4, hyperedges2.size());

    ASSERT_TRUE(hyperedges1 == hyperedges1);
    ASSERT_FALSE(hyperedges1 == hyperedges2);
    ASSERT_FALSE(hyperedges2 == hyperedges1);
    ASSERT_TRUE(hyperedges2 == hyperedges2);

    ASSERT_FALSE(hyperedges1 != hyperedges1);
    ASSERT_TRUE(hyperedges1 != hyperedges2);
    ASSERT_TRUE(hyperedges2 != hyperedges1);
    ASSERT_FALSE(hyperedges2 != hyperedges2);

    htd::FilteredHyperedgeCollection hyperedges3(std::vector<htd::Hyperedge> { h1, h2, h3, h4 }, std::vector<htd::index_t> { 1, 3, 2, 3, 0 });

    ASSERT_EQ((std::size_t)5, hyperedges3.size());

    ASSERT_TRUE(hyperedges1 == hyperedges1);
    ASSERT_FALSE(hyperedges1 == hyperedges2);
    ASSERT_FALSE(hyperedges1 == hyperedges3);
    ASSERT_FALSE(hyperedges2 == hyperedges1);
    ASSERT_TRUE(hyperedges2 == hyperedges2);
    ASSERT_FALSE(hyperedges2 == hyperedges3);
    ASSERT_FALSE(hyperedges3 == hyperedges1);
    ASSERT_FALSE(hyperedges3 == hyperedges2);
    ASSERT_TRUE(hyperedges3 == hyperedges3);

    std::vector<htd::index_t> indices4 { 0, 1 };

    htd::FilteredHyperedgeCollection hyperedges4(std::vector<htd::Hyperedge> { h1, h2, h3, h4 }, indices4);

    ASSERT_EQ((std::size_t)2, hyperedges4.size());

    ASSERT_TRUE(hyperedges1 == hyperedges1);
    ASSERT_FALSE(hyperedges1 == hyperedges2);
    ASSERT_FALSE(hyperedges1 == hyperedges3);
    ASSERT_FALSE(hyperedges1 == hyperedges4);
    ASSERT_FALSE(hyperedges2 == hyperedges1);
    ASSERT_TRUE(hyperedges2 == hyperedges2);
    ASSERT_FALSE(hyperedges2 == hyperedges3);
    ASSERT_FALSE(hyperedges2 == hyperedges4);
    ASSERT_FALSE(hyperedges3 == hyperedges1);
    ASSERT_FALSE(hyperedges3 == hyperedges2);
    ASSERT_TRUE(hyperedges3 == hyperedges3);
    ASSERT_FALSE(hyperedges3 == hyperedges4);
    ASSERT_FALSE(hyperedges4 == hyperedges1);
    ASSERT_FALSE(hyperedges4 == hyperedges2);
    ASSERT_FALSE(hyperedges4 == hyperedges3);
    ASSERT_TRUE(hyperedges4 == hyperedges4);

    ASSERT_EQ(4, std::distance(hyperedges1.begin(), hyperedges1.end()));
    ASSERT_EQ(4, std::distance(hyperedges2.begin(), hyperedges2.end()));
    ASSERT_EQ(5, std::distance(hyperedges3.begin(), hyperedges3.end()));
    ASSERT_EQ(2, std::distance(hyperedges4.begin(), hyperedges4.end()));

    htd::FilteredHyperedgeCollection hyperedges5(hyperedges4);

    ASSERT_EQ(2, std::distance(hyperedges5.begin(), hyperedges5.end()));

    ASSERT_TRUE(hyperedges4 == hyperedges5);
    ASSERT_TRUE(hyperedges5 == hyperedges4);

    htd::FilteredHyperedgeCollection hyperedges6(std::move(hyperedges3));

    ASSERT_EQ(5, std::distance(hyperedges6.begin(), hyperedges6.end()));

    htd::FilteredHyperedgeCollection hyperedges7(inputEdges3, std::vector<htd::index_t> { 1, 3, 2, 3 });

    ASSERT_EQ((std::size_t)4, hyperedges7.size());

    ASSERT_TRUE(hyperedges2 == hyperedges2);
    ASSERT_TRUE(hyperedges2 == hyperedges7);
    ASSERT_TRUE(hyperedges7 == hyperedges2);
    ASSERT_TRUE(hyperedges7 == hyperedges7);

    ASSERT_FALSE(hyperedges2 != hyperedges2);
    ASSERT_FALSE(hyperedges2 != hyperedges7);
    ASSERT_FALSE(hyperedges7 != hyperedges2);
    ASSERT_FALSE(hyperedges7 != hyperedges7);
}

TEST(FilteredHyperedgeCollectionTest, TestIterators)
{
    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 4, 3);
    htd::Hyperedge h4(4, 5, 5);
    htd::Hyperedge h5(5, 7, 6);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2, h3, h4, h5 };

    htd::FilteredHyperedgeCollection hyperedges1(inputEdges1, std::vector<htd::index_t> { 1, 3, 3, 2, 0, 4 });
    htd::FilteredHyperedgeCollection hyperedges2(inputEdges1, std::vector<htd::index_t> { 1, 3, 3, 2, 0, 4 });

    ASSERT_EQ(6, std::distance(hyperedges1.begin(), hyperedges1.end()));

    auto it = hyperedges1.begin();

    ASSERT_EQ((htd::id_t)2, it->id());

    it += 1;

    ASSERT_EQ((htd::id_t)4, (*it).id());

    auto it2 = it++;

    ASSERT_EQ((htd::id_t)4, it->id());
    ASSERT_EQ((htd::id_t)4, it->id());

    ASSERT_EQ(-1, std::distance(it, it2));

    it += 2;

    ASSERT_EQ((htd::id_t)1, (*it).id());

    it += 1;

    ASSERT_EQ((htd::id_t)5, it->id());

    auto it3 = ++it;

    ASSERT_TRUE(it == hyperedges1.end());
    ASSERT_TRUE(it3 == hyperedges1.end());

    ASSERT_EQ(6, it - hyperedges1.begin());
    ASSERT_EQ(-6, hyperedges1.begin() - it);

    it--;

    ASSERT_EQ((htd::id_t)5, it->id());

    ASSERT_EQ(5, it - hyperedges1.begin());
    ASSERT_EQ(-5, hyperedges1.begin() - it);

    it -= 2;

    ASSERT_EQ((htd::id_t)3, (*it).id());

    ASSERT_EQ(3, it - hyperedges1.begin());
    ASSERT_EQ(-3, hyperedges1.begin() - it);

    it -= 2;

    ASSERT_EQ((htd::id_t)4, (*it).id());

    ASSERT_EQ(1, it - hyperedges1.begin());
    ASSERT_EQ(-1, hyperedges1.begin() - it);

    ++it;

    ASSERT_EQ((htd::id_t)4, (*it).id());
    ASSERT_TRUE(it != hyperedges1.begin());

    ASSERT_EQ(2, it - hyperedges1.begin());
    ASSERT_EQ(-2, hyperedges1.begin() - it);

    it--;
    --it;

    auto itCopy1 = it;

    ASSERT_EQ((htd::id_t)2, (*it).id());

    ASSERT_TRUE(it == hyperedges1.begin());
    ASSERT_FALSE(it != hyperedges1.begin());

    ASSERT_EQ(0, it - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - it);

    auto itCopy2 = std::move(it);

    ASSERT_TRUE(itCopy1 == hyperedges1.begin());
    ASSERT_FALSE(itCopy1 != hyperedges1.begin());

    ASSERT_EQ(0, itCopy1 - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - itCopy1);

    ASSERT_TRUE(itCopy2 == hyperedges1.begin());
    ASSERT_FALSE(itCopy2 != hyperedges1.begin());

    ASSERT_EQ(0, itCopy2 - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - itCopy2);

    try
    {
        hyperedges1.begin() - hyperedges2.begin();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }
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
