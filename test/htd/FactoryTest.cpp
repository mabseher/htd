/*
 * File:   FactoryTest.cpp
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

class FactoryTest : public ::testing::Test
{
    public:
        FactoryTest(void)
        {

        }

        virtual ~FactoryTest()
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
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableHypergraph * hypergraph1 = libraryInstance->hypergraphFactory().createInstance();

    htd::IHypergraph & hypergraphReference1 = *hypergraph1;
    const htd::IHypergraph & hypergraphConstReference1 = *hypergraph1;

    ASSERT_EQ((std::size_t)0, hypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)0, hypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableHypergraph *>(&hypergraphReference1));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableHypergraph *>(&hypergraphConstReference1));

    hypergraph1->addVertex();

    ASSERT_EQ((std::size_t)1, hypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)1, hypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphReference1)));
    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphConstReference1)));

    htd::IMutableHypergraph * hypergraph2 = libraryInstance->hypergraphFactory().createInstance(3);

    htd::IHypergraph & hypergraphReference2 = *hypergraph2;
    const htd::IHypergraph & hypergraphConstReference2 = *hypergraph2;

    ASSERT_EQ((std::size_t)3, hypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)3, hypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableHypergraph *>(&hypergraphReference2));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableHypergraph *>(&hypergraphConstReference2));

    hypergraph2->addVertex();

    ASSERT_EQ((std::size_t)4, hypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)4, hypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphReference2)));
    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphConstReference2)));

    hypergraph1->removeVertex(1);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    libraryInstance->hypergraphFactory().setConstructionTemplate(hypergraph1->clone());
#else
    libraryInstance->hypergraphFactory().setConstructionTemplate(hypergraph1->cloneMutableHypergraph());
#endif

    htd::IMutableHypergraph * hypergraph3 = libraryInstance->hypergraphFactory().createInstance();

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

    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphReference3)));
    ASSERT_NE(nullptr, &(libraryInstance->hypergraphFactory().accessMutableInstance(hypergraphConstReference3)));

    htd::IMutableHypergraph * hypergraph4 = libraryInstance->hypergraphFactory().createInstance(*hypergraph2);

    ASSERT_NE(hypergraph2, hypergraph4);

    ASSERT_EQ((std::size_t)4, hypergraph4->vertexCount());

    htd::IMutableMultiHypergraph * multiHypergraph1 = libraryInstance->multiHypergraphFactory().createInstance(2);

    multiHypergraph1->addEdge(1, 2);
    multiHypergraph1->addEdge(2, 1);
    multiHypergraph1->addEdge(1, 2);
    multiHypergraph1->addEdge(2, 1);

    ASSERT_EQ((std::size_t)2, multiHypergraph1->vertexCount());
    ASSERT_EQ((std::size_t)4, multiHypergraph1->edgeCount());

    delete hypergraph1;
    delete hypergraph2;
    delete hypergraph3;
    delete hypergraph4;
    delete multiHypergraph1;

    delete libraryInstance;
}

TEST(FactoryTest, CheckMultiHypergraphFactory)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::IMutableMultiHypergraph * multiHypergraph1 = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMultiHypergraph & multiHypergraphReference1 = *multiHypergraph1;
    const htd::IMultiHypergraph & multiHypergraphConstReference1 = *multiHypergraph1;

    ASSERT_EQ((std::size_t)0, multiHypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)0, multiHypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableMultiHypergraph *>(&multiHypergraphReference1));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableMultiHypergraph *>(&multiHypergraphConstReference1));

    multiHypergraph1->addVertex();

    ASSERT_EQ((std::size_t)1, multiHypergraphReference1.vertexCount());
    ASSERT_EQ((std::size_t)1, multiHypergraphConstReference1.vertexCount());

    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphReference1)));
    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphConstReference1)));

    htd::IMutableMultiHypergraph * multiHypergraph2 = libraryInstance->multiHypergraphFactory().createInstance(3);

    htd::IMultiHypergraph & multiHypergraphReference2 = *multiHypergraph2;
    const htd::IMultiHypergraph & multiHypergraphConstReference2 = *multiHypergraph2;

    ASSERT_EQ((std::size_t)3, multiHypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)3, multiHypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableMultiHypergraph *>(&multiHypergraphReference2));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableMultiHypergraph *>(&multiHypergraphConstReference2));

    multiHypergraph2->addVertex();

    ASSERT_EQ((std::size_t)4, multiHypergraphReference2.vertexCount());
    ASSERT_EQ((std::size_t)4, multiHypergraphConstReference2.vertexCount());

    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphReference2)));
    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphConstReference2)));

    multiHypergraph1->removeVertex(1);

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    libraryInstance->multiHypergraphFactory().setConstructionTemplate(multiHypergraph1->clone());
#else
    libraryInstance->multiHypergraphFactory().setConstructionTemplate(multiHypergraph1->cloneMutableMultiHypergraph());
#endif

    htd::IMutableMultiHypergraph * multiHypergraph3 = libraryInstance->multiHypergraphFactory().createInstance();

    htd::IMultiHypergraph & multiHypergraphReference3 = *multiHypergraph3;
    const htd::IMultiHypergraph & multiHypergraphConstReference3 = *multiHypergraph3;

    ASSERT_EQ((std::size_t)0, multiHypergraphReference3.vertexCount());
    ASSERT_EQ((std::size_t)0, multiHypergraphConstReference3.vertexCount());

    ASSERT_NE(nullptr, dynamic_cast<htd::IMutableMultiHypergraph *>(&multiHypergraphReference3));
    ASSERT_NE(nullptr, dynamic_cast<const htd::IMutableMultiHypergraph *>(&multiHypergraphConstReference3));

    multiHypergraph3->addVertex();
    multiHypergraph3->addVertex();

    ASSERT_EQ((std::size_t)2, multiHypergraphReference3.vertexCount());
    ASSERT_EQ((std::size_t)2, multiHypergraphConstReference3.vertexCount());

    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphReference3)));
    ASSERT_NE(nullptr, &(libraryInstance->multiHypergraphFactory().accessMutableInstance(multiHypergraphConstReference3)));

    htd::IMutableMultiHypergraph * multiHypergraph4 = libraryInstance->multiHypergraphFactory().createInstance(*multiHypergraph2);

    ASSERT_NE(multiHypergraph2, multiHypergraph4);

    ASSERT_EQ((std::size_t)4, multiHypergraph4->vertexCount());

    delete multiHypergraph1;
    delete multiHypergraph2;
    delete multiHypergraph3;
    delete multiHypergraph4;

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
