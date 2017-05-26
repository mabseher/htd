/*
 * File:   FilteredHyperedgeCollectionTest.cpp
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

class FilteredHyperedgeCollectionTest : public ::testing::Test
{
    public:
        FilteredHyperedgeCollectionTest(void)
        {

        }

        virtual ~FilteredHyperedgeCollectionTest()
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

    htd::FilteredHyperedgeCollection hyperedges1(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 1, 3, 3, 2 });
    htd::FilteredHyperedgeCollection hyperedges2(new htd::HyperedgeVector(inputEdges2), std::vector<htd::index_t> { 1, 3, 2, 3 });

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

    htd::FilteredHyperedgeCollection hyperedges3(new htd::HyperedgeVector(std::vector<htd::Hyperedge> { h1, h2, h3, h4 }), std::vector<htd::index_t> { 1, 3, 2, 3, 0 });

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

    htd::FilteredHyperedgeCollection hyperedges4(new htd::HyperedgeVector(std::vector<htd::Hyperedge> { h1, h2, h3, h4 }), indices4);

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

    htd::FilteredHyperedgeCollection hyperedges7(new htd::HyperedgeVector(inputEdges3), std::vector<htd::index_t> { 1, 3, 2, 3 });

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

    htd::FilteredHyperedgeCollection hyperedges1(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 1, 3, 3, 2, 0, 4 });

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

    auto itCopy1 = hyperedges1.end();
    auto itCopy2 = hyperedges1.end();

    itCopy1 = it;

    ASSERT_EQ((htd::id_t)2, (*it).id());

    ASSERT_TRUE(it == hyperedges1.begin());
    ASSERT_FALSE(it != hyperedges1.begin());

    ASSERT_EQ(0, it - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - it);

    itCopy2 = std::move(it);

    ASSERT_TRUE(itCopy1 == hyperedges1.begin());
    ASSERT_FALSE(itCopy1 != hyperedges1.begin());

    ASSERT_EQ(0, itCopy1 - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - itCopy1);

    ASSERT_TRUE(itCopy2 == hyperedges1.begin());
    ASSERT_FALSE(itCopy2 != hyperedges1.begin());

    ASSERT_EQ(0, itCopy2 - hyperedges1.begin());
    ASSERT_EQ(0, hyperedges1.begin() - itCopy2);
}

TEST(FilteredHyperedgeCollectionTest, TestRestriction)
{
    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 4, 3);
    htd::Hyperedge h4(4, 5, 5);
    htd::Hyperedge h5(5, 7, 6);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2, h3, h4, h5 };

    htd::FilteredHyperedgeCollection hyperedges1(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 0, 1, 2, 3, 4 });

    htd::FilteredHyperedgeCollection hyperedges2(hyperedges1);

    ASSERT_EQ((std::size_t)5, hyperedges1.size());

    hyperedges1.restrictTo(std::vector<htd::vertex_t> { 1, 2, 3, 5 });

    ASSERT_EQ((std::size_t)3, hyperedges1.size());

    auto it = hyperedges1.begin();

    ASSERT_EQ((htd::id_t)1, it->id());

    ++it;

    ASSERT_EQ((htd::id_t)2, it->id());

    ++it;

    ASSERT_EQ((htd::id_t)4, it->id());

    hyperedges1.restrictTo(std::vector<htd::vertex_t> { 5 });

    ASSERT_EQ((std::size_t)1, hyperedges1.size());

    it = hyperedges1.begin();

    ASSERT_EQ((htd::id_t)4, it->id());

    hyperedges1.restrictTo(std::vector<htd::vertex_t> { 5 });

    ASSERT_EQ((std::size_t)1, hyperedges1.size());

    it = hyperedges1.begin();

    ASSERT_EQ((htd::id_t)4, it->id());

    hyperedges1.restrictTo(std::vector<htd::vertex_t> { 1, 2 });

    ASSERT_EQ((std::size_t)0, hyperedges1.size());

    ASSERT_EQ((std::size_t)5, hyperedges2.size());

    hyperedges2.restrictTo(std::vector<htd::vertex_t> { htd::Vertex::UNKNOWN });

    ASSERT_EQ((std::size_t)0, hyperedges2.size());
}

TEST(FilteredHyperedgeCollectionTest, TestSwapMethod)
{
    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 4, 3);
    htd::Hyperedge h4(4, 5, 5);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2 };
    std::vector<htd::Hyperedge> inputEdges2 { h3, h4 };

    htd::FilteredHyperedgeCollection hyperedges1(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 0, 1 });
    htd::FilteredHyperedgeCollection hyperedges2(new htd::HyperedgeVector(inputEdges2), std::vector<htd::index_t> { 0, 1 });

    ASSERT_EQ((std::size_t)2, hyperedges1.size());
    ASSERT_EQ((std::size_t)2, hyperedges2.size());

    auto it1 = hyperedges1.begin();
    auto it2 = hyperedges2.begin();

    ASSERT_EQ((htd::vertex_t)1, it1->id());
    ASSERT_EQ((htd::vertex_t)3, it2->id());

    ++it1;
    ++it2;

    ASSERT_EQ((htd::vertex_t)2, it1->id());
    ASSERT_EQ((htd::vertex_t)4, it2->id());

    hyperedges1.swap(hyperedges2);

    it1 = hyperedges1.begin();
    it2 = hyperedges2.begin();

    ASSERT_EQ((htd::vertex_t)3, it1->id());
    ASSERT_EQ((htd::vertex_t)1, it2->id());

    ++it1;
    ++it2;

    ASSERT_EQ((htd::vertex_t)4, it1->id());
    ASSERT_EQ((htd::vertex_t)2, it2->id());

    hyperedges2.swap(hyperedges1);

    it1 = hyperedges1.begin();
    it2 = hyperedges2.begin();

    ASSERT_EQ((htd::vertex_t)1, it1->id());
    ASSERT_EQ((htd::vertex_t)3, it2->id());

    ++it1;
    ++it2;

    ASSERT_EQ((htd::vertex_t)2, it1->id());
    ASSERT_EQ((htd::vertex_t)4, it2->id());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
