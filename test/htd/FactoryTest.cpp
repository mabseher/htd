/*
 * File:   FactoryTest.cpp
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

class FactoryTest : public ::testing::Test
{
    public:
        FactoryTest(void)
        {

        }

        ~FactoryTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(FactoryTest, CheckHypergraphFactory)
{
    htd::IMutableHypergraph * hypergraph1 = htd::HypergraphFactory::instance().getHypergraph();

    htd::IHypergraph & hypergraphReference1 = *hypergraph1;
    const htd::IHypergraph & hypergraphConstReference1 = *hypergraph1;

    ASSERT_EQ((std::size_t)0, hypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)0, hypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableHypergraph *>(&hypergraphReference1));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableHypergraph *>(&hypergraphConstReference1));

    hypergraph1->addVertex();

    ASSERT_EQ((std::size_t)1, hypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)1, hypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphReference1)));
    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphConstReference1)));

    htd::IMutableHypergraph * hypergraph2 = htd::HypergraphFactory::instance().getHypergraph(3);

    htd::IHypergraph & hypergraphReference2 = *hypergraph2;
    const htd::IHypergraph & hypergraphConstReference2 = *hypergraph2;

    ASSERT_EQ((std::size_t)3, hypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)3, hypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableHypergraph *>(&hypergraphReference2));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableHypergraph *>(&hypergraphConstReference2));

    hypergraph2->addVertex();

    ASSERT_EQ((std::size_t)4, hypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)4, hypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphReference2)));
    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphConstReference2)));

    hypergraph1->removeVertex(1);

    htd::HypergraphFactory::instance().setConstructionTemplate(hypergraph1->clone());

    htd::IMutableHypergraph * hypergraph3 = htd::HypergraphFactory::instance().getHypergraph();

    htd::IHypergraph & hypergraphReference3 = *hypergraph3;
    const htd::IHypergraph & hypergraphConstReference3 = *hypergraph3;

    ASSERT_EQ((std::size_t)0, hypergraphReference3.vertexCount());
    ASSERT_EQ((std::size_t)0, hypergraphConstReference3.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableHypergraph *>(&hypergraphReference3));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableHypergraph *>(&hypergraphConstReference3));

    hypergraph3->addVertex();
    hypergraph3->addVertex();

    ASSERT_EQ((std::size_t)2, hypergraphReference3.vertexCount());
    ASSERT_EQ((std::size_t)2, hypergraphConstReference3.vertexCount());

    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphReference3)));
    ASSERT_NE(nullptr, &(htd::HypergraphFactory::instance().accessMutableHypergraph(hypergraphConstReference3)));

    htd::IMutableHypergraph * hypergraph4 = htd::HypergraphFactory::instance().getHypergraph(*hypergraph2);

    ASSERT_NE(hypergraph2, hypergraph4);

    ASSERT_EQ((std::size_t)4, hypergraph4->vertexCount());

    htd::IMutableMultiHypergraph * multiHypergraph1 = htd::MultiHypergraphFactory::instance().getMultiHypergraph(2);

    multiHypergraph1->addEdge(1, 2);
    multiHypergraph1->addEdge(2, 1);
    multiHypergraph1->addEdge(1, 2);
    multiHypergraph1->addEdge(2, 1);

    ASSERT_EQ((std::size_t)2, multiHypergraph1->vertexCount());
    ASSERT_EQ((std::size_t)4, multiHypergraph1->edgeCount());

    htd::IMutableHypergraph * hypergraph5 = htd::HypergraphFactory::instance().getHypergraph(*multiHypergraph1);

    ASSERT_EQ((std::size_t)2, hypergraph5->vertexCount());
    ASSERT_EQ((std::size_t)2, hypergraph5->edgeCount());

    ASSERT_EQ((htd::vertex_t)1, hypergraph5->hyperedge(1).at(0));
    ASSERT_EQ((htd::vertex_t)2, hypergraph5->hyperedge(1).at(1));

    ASSERT_EQ((htd::vertex_t)2, hypergraph5->hyperedge(2).at(0));
    ASSERT_EQ((htd::vertex_t)1, hypergraph5->hyperedge(2).at(1));

    delete hypergraph1;
    delete hypergraph2;
    delete hypergraph3;
    delete hypergraph4;
    delete hypergraph5;
    delete multiHypergraph1;
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
