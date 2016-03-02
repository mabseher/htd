/*
 * File:   HyperedgeTest.cpp
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

class HyperedgeTest : public ::testing::Test
{
    public:
        HyperedgeTest(void)
        {

        }

        ~HyperedgeTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(HyperedgeTest, CheckEmptyHyperedge)
{
    std::vector<htd::vertex_t> elements1 { };

    htd::Hyperedge hyperedge1((htd::id_t)1, elements1);
    htd::Hyperedge hyperedge2((htd::id_t)2, std::vector<htd::vertex_t> { });
    htd::Hyperedge hyperedge3((htd::id_t)3, htd::ConstCollection<htd::vertex_t>(elements1.begin(), elements1.end()));

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)0, hyperedge1.size());
    ASSERT_EQ((std::size_t)0, hyperedge2.size());
    ASSERT_EQ((std::size_t)0, hyperedge3.size());

    ASSERT_TRUE(hyperedge1.empty());
    ASSERT_TRUE(hyperedge2.empty());
    ASSERT_TRUE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge2);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge2 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    ASSERT_FALSE(hyperedge1 != hyperedge1);
    ASSERT_FALSE(hyperedge1 != hyperedge2);
    ASSERT_FALSE(hyperedge1 != hyperedge3);
    ASSERT_FALSE(hyperedge2 != hyperedge1);
    ASSERT_FALSE(hyperedge2 != hyperedge2);
    ASSERT_FALSE(hyperedge2 != hyperedge3);
    ASSERT_FALSE(hyperedge3 != hyperedge1);
    ASSERT_FALSE(hyperedge3 != hyperedge2);
    ASSERT_FALSE(hyperedge3 != hyperedge3);

    for (htd::vertex_t vertex : hyperedge1)
    {
        HTD_UNUSED(vertex);

        FAIL();
    }

    for (htd::vertex_t vertex : hyperedge2)
    {
        HTD_UNUSED(vertex);

        FAIL();
    }

    for (htd::vertex_t vertex : hyperedge3)
    {
        HTD_UNUSED(vertex);

        FAIL();
    }

    ASSERT_FALSE(hyperedge1 < hyperedge1);
    ASSERT_FALSE(hyperedge1 > hyperedge1);
    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge2 < hyperedge1);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge3 < hyperedge1);

    ASSERT_FALSE(hyperedge2 < hyperedge2);
    ASSERT_FALSE(hyperedge2 > hyperedge2);
    ASSERT_TRUE(hyperedge2 < hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
    ASSERT_FALSE(hyperedge3 < hyperedge2);

    ASSERT_FALSE(hyperedge3 < hyperedge3);
    ASSERT_FALSE(hyperedge3 > hyperedge3);

    hyperedge2 = hyperedge1;

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)0, hyperedge1.size());
    ASSERT_EQ((std::size_t)0, hyperedge2.size());
    ASSERT_EQ((std::size_t)0, hyperedge3.size());

    ASSERT_TRUE(hyperedge1.empty());
    ASSERT_TRUE(hyperedge2.empty());
    ASSERT_TRUE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge2);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge2 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    hyperedge3 = std::move(hyperedge2);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge3.id());

    ASSERT_EQ((std::size_t)0, hyperedge1.size());
    ASSERT_EQ((std::size_t)0, hyperedge3.size());

    ASSERT_TRUE(hyperedge1.empty());
    ASSERT_TRUE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge3);
}

TEST(HyperedgeTest, CheckSize1Hyperedge)
{
    std::vector<htd::vertex_t> elements1 { 1 };

    htd::Hyperedge hyperedge1((htd::id_t)1, elements1);
    htd::Hyperedge hyperedge2((htd::id_t)2, std::vector<htd::vertex_t> { 1 });
    htd::Hyperedge hyperedge3((htd::id_t)3, htd::ConstCollection<htd::vertex_t>(elements1.begin(), elements1.end()));

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)1, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge1.sortedElements().size());
    ASSERT_EQ((std::size_t)1, hyperedge2.size());
    ASSERT_EQ((std::size_t)1, hyperedge2.sortedElements().size());
    ASSERT_EQ((std::size_t)1, hyperedge3.size());
    ASSERT_EQ((std::size_t)1, hyperedge3.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge2);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge2 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    ASSERT_FALSE(hyperedge1 != hyperedge1);
    ASSERT_FALSE(hyperedge1 != hyperedge2);
    ASSERT_FALSE(hyperedge1 != hyperedge3);
    ASSERT_FALSE(hyperedge2 != hyperedge1);
    ASSERT_FALSE(hyperedge2 != hyperedge2);
    ASSERT_FALSE(hyperedge2 != hyperedge3);
    ASSERT_FALSE(hyperedge3 != hyperedge1);
    ASSERT_FALSE(hyperedge3 != hyperedge2);
    ASSERT_FALSE(hyperedge3 != hyperedge3);

    ASSERT_EQ((htd::vertex_t)1, *(hyperedge1.begin()));
    ASSERT_EQ((htd::vertex_t)1, *(hyperedge2.begin()));
    ASSERT_EQ((htd::vertex_t)1, *(hyperedge3.begin()));

    ASSERT_FALSE(hyperedge1 < hyperedge1);
    ASSERT_FALSE(hyperedge1 > hyperedge1);
    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge2 < hyperedge1);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge3 < hyperedge1);

    ASSERT_FALSE(hyperedge2 < hyperedge2);
    ASSERT_FALSE(hyperedge2 > hyperedge2);
    ASSERT_TRUE(hyperedge2 < hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
    ASSERT_FALSE(hyperedge3 < hyperedge2);

    ASSERT_FALSE(hyperedge3 < hyperedge3);
    ASSERT_FALSE(hyperedge3 > hyperedge3);

    hyperedge2 = hyperedge1;

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)1, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge2.size());
    ASSERT_EQ((std::size_t)1, hyperedge3.size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge2);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge2 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    hyperedge3 = std::move(hyperedge2);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge3.id());

    ASSERT_EQ((std::size_t)1, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge3.size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    hyperedge1.erase((htd::vertex_t)2);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge3.id());

    ASSERT_EQ((std::size_t)1, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge3.size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 == hyperedge3);
    ASSERT_TRUE(hyperedge3 == hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    hyperedge1.erase((htd::vertex_t)1);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)1, hyperedge3.id());

    ASSERT_EQ((std::size_t)0, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge3.size());

    ASSERT_TRUE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge1 != hyperedge3);
    ASSERT_TRUE(hyperedge3 != hyperedge1);
    ASSERT_TRUE(hyperedge3 == hyperedge3);

    ASSERT_FALSE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)1));
}

TEST(HyperedgeTest, CheckSize2Hyperedge1)
{
    htd::Hyperedge hyperedge1((htd::id_t)1, 1, 1);
    htd::Hyperedge hyperedge2((htd::id_t)2, 1, 2);
    htd::Hyperedge hyperedge3((htd::id_t)3, 2, 1);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge1.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge2.size());
    ASSERT_EQ((std::size_t)2, hyperedge2.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge3.size());
    ASSERT_EQ((std::size_t)2, hyperedge3.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);
    ASSERT_FALSE(hyperedge1 == hyperedge2);
    ASSERT_FALSE(hyperedge1 == hyperedge3);
    ASSERT_FALSE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge1 != hyperedge2);
    ASSERT_TRUE(hyperedge1 != hyperedge3);
    ASSERT_TRUE(hyperedge2 != hyperedge3);

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)2));

    ASSERT_TRUE(hyperedge2.sortedElements() == hyperedge3.sortedElements());

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge2.elements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge2.elements()[1]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge3.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge3.elements()[1]);

    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_TRUE(hyperedge2 < hyperedge3);

    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
}

TEST(HyperedgeTest, CheckSize2Hyperedge2)
{
    htd::Hyperedge hyperedge1((htd::id_t)1, std::vector<htd::vertex_t> { 1, 1 });
    htd::Hyperedge hyperedge2((htd::id_t)2, std::vector<htd::vertex_t> { 1, 2 });
    htd::Hyperedge hyperedge3((htd::id_t)3, std::vector<htd::vertex_t> { 2, 1 });

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge1.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge2.size());
    ASSERT_EQ((std::size_t)2, hyperedge2.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge3.size());
    ASSERT_EQ((std::size_t)2, hyperedge3.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);
    ASSERT_FALSE(hyperedge1 == hyperedge2);
    ASSERT_FALSE(hyperedge1 == hyperedge3);
    ASSERT_FALSE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge1 != hyperedge2);
    ASSERT_TRUE(hyperedge1 != hyperedge3);
    ASSERT_TRUE(hyperedge2 != hyperedge3);

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)2));

    ASSERT_TRUE(hyperedge2.sortedElements() == hyperedge3.sortedElements());

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge2.elements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge2.elements()[1]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge3.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge3.elements()[1]);

    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_TRUE(hyperedge2 < hyperedge3);

    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
}

TEST(HyperedgeTest, CheckSize2Hyperedge3)
{
    std::vector<htd::vertex_t> elements1 { 1, 1 };
    std::vector<htd::vertex_t> elements2 { 1, 2 };
    std::vector<htd::vertex_t> elements3 { 2, 1 };

    htd::Hyperedge hyperedge1((htd::id_t)1, elements1);
    htd::Hyperedge hyperedge2((htd::id_t)2, elements2);
    htd::Hyperedge hyperedge3((htd::id_t)3, elements3);

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge1.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge2.size());
    ASSERT_EQ((std::size_t)2, hyperedge2.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge3.size());
    ASSERT_EQ((std::size_t)2, hyperedge3.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);
    ASSERT_FALSE(hyperedge1 == hyperedge2);
    ASSERT_FALSE(hyperedge1 == hyperedge3);
    ASSERT_FALSE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge1 != hyperedge2);
    ASSERT_TRUE(hyperedge1 != hyperedge3);
    ASSERT_TRUE(hyperedge2 != hyperedge3);

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)2));

    ASSERT_TRUE(hyperedge2.sortedElements() == hyperedge3.sortedElements());

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge2.elements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge2.elements()[1]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge3.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge3.elements()[1]);

    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_TRUE(hyperedge2 < hyperedge3);

    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
}

TEST(HyperedgeTest, CheckSize2Hyperedge4)
{
    std::vector<htd::vertex_t> elements1 { 1, 1 };
    std::vector<htd::vertex_t> elements2 { 1, 2 };
    std::vector<htd::vertex_t> elements3 { 2, 1 };

    htd::Hyperedge hyperedge1((htd::id_t)1, htd::ConstCollection<htd::vertex_t>(elements1.begin(), elements1.end()));
    htd::Hyperedge hyperedge2((htd::id_t)2, htd::ConstCollection<htd::vertex_t>(elements2.begin(), elements2.end()));
    htd::Hyperedge hyperedge3((htd::id_t)3, htd::ConstCollection<htd::vertex_t>(elements3.begin(), elements3.end()));

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());
    ASSERT_EQ((htd::id_t)2, hyperedge2.id());
    ASSERT_EQ((htd::id_t)3, hyperedge3.id());

    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_EQ((std::size_t)1, hyperedge1.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge2.size());
    ASSERT_EQ((std::size_t)2, hyperedge2.sortedElements().size());
    ASSERT_EQ((std::size_t)2, hyperedge3.size());
    ASSERT_EQ((std::size_t)2, hyperedge3.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());
    ASSERT_FALSE(hyperedge2.empty());
    ASSERT_FALSE(hyperedge3.empty());

    ASSERT_TRUE(hyperedge1 == hyperedge1);
    ASSERT_TRUE(hyperedge2 == hyperedge2);
    ASSERT_TRUE(hyperedge3 == hyperedge3);
    ASSERT_FALSE(hyperedge1 == hyperedge2);
    ASSERT_FALSE(hyperedge1 == hyperedge3);
    ASSERT_FALSE(hyperedge2 == hyperedge3);
    ASSERT_TRUE(hyperedge1 != hyperedge2);
    ASSERT_TRUE(hyperedge1 != hyperedge3);
    ASSERT_TRUE(hyperedge2 != hyperedge3);

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge2.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge3.containsVertex((htd::vertex_t)2));

    ASSERT_TRUE(hyperedge2.sortedElements() == hyperedge3.sortedElements());

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge2.elements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge2.elements()[1]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge3.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge3.elements()[1]);

    ASSERT_TRUE(hyperedge1 < hyperedge2);
    ASSERT_TRUE(hyperedge1 < hyperedge3);
    ASSERT_TRUE(hyperedge2 < hyperedge3);

    ASSERT_FALSE(hyperedge1 > hyperedge2);
    ASSERT_FALSE(hyperedge1 > hyperedge3);
    ASSERT_FALSE(hyperedge2 > hyperedge3);
}

TEST(HyperedgeTest, CheckSize3Hyperedge)
{
    htd::Hyperedge hyperedge1((htd::id_t)1, std::vector<htd::vertex_t> { 3, 2, 2, 1 });

    ASSERT_EQ((htd::id_t)1, hyperedge1.id());

    ASSERT_EQ((std::size_t)4, hyperedge1.size());
    ASSERT_EQ((std::size_t)3, hyperedge1.sortedElements().size());

    ASSERT_FALSE(hyperedge1.empty());

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)3));

    ASSERT_EQ((htd::vertex_t)3, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge1.elements()[1]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge1.elements()[2]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[3]);

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.sortedElements()[0]);
    ASSERT_EQ((htd::vertex_t)2, hyperedge1.sortedElements()[1]);
    ASSERT_EQ((htd::vertex_t)3, hyperedge1.sortedElements()[2]);

    hyperedge1.erase((htd::vertex_t)2);

    ASSERT_EQ((std::size_t)2, hyperedge1.size());
    ASSERT_EQ((std::size_t)2, hyperedge1.sortedElements().size());

    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)1));
    ASSERT_FALSE(hyperedge1.containsVertex((htd::vertex_t)2));
    ASSERT_TRUE(hyperedge1.containsVertex((htd::vertex_t)3));

    ASSERT_EQ((htd::vertex_t)3, hyperedge1.elements()[0]);
    ASSERT_EQ((htd::vertex_t)1, hyperedge1.elements()[1]);

    ASSERT_EQ((htd::vertex_t)1, hyperedge1.sortedElements()[0]);
    ASSERT_EQ((htd::vertex_t)3, hyperedge1.sortedElements()[1]);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
