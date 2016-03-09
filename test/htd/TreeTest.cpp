/*
 * File:   TreeTest.cpp
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

class TreeTest : public ::testing::Test
{
    public:
        TreeTest(void)
        {

        }

        ~TreeTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(TreeTest, CheckEmptyTree)
{
    htd::Tree tree;

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafNodeCount());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());

    try
    {
        tree.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }
}

TEST(TreeTest, CheckSize1Tree)
{
    htd::Tree tree;

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafNodeCount());

    try
    {
        tree.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    htd::vertex_t root = tree.insertRoot();

    ASSERT_TRUE(tree.isVertex(root));
    ASSERT_TRUE(tree.isRoot(root));
    ASSERT_EQ(root, tree.root());

    ASSERT_EQ((std::size_t)1, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount(root));

    ASSERT_EQ((std::size_t)1, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)1, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)1, tree.leafNodeCount());

    ASSERT_EQ((std::size_t)1, tree.isolatedVertexCount());
    ASSERT_EQ(root, tree.isolatedVertices()[0]);
    ASSERT_EQ(root, tree.isolatedVertexAtPosition(0));
    ASSERT_TRUE(tree.isIsolatedVertex(root));
}

TEST(TreeTest, CheckSize3Tree)
{
    htd::Tree tree;

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafNodeCount());

    try
    {
        tree.root();

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    htd::vertex_t root = tree.insertRoot();

    htd::vertex_t child = tree.addChild(root);

    ASSERT_NE(root, child);

    ASSERT_TRUE(tree.isVertex(root));
    ASSERT_TRUE(tree.isVertex(child));
    ASSERT_TRUE(tree.isRoot(root));
    ASSERT_EQ(root, tree.root());

    ASSERT_EQ((std::size_t)2, tree.vertexCount());
    ASSERT_EQ((std::size_t)1, tree.edgeCount());
    ASSERT_EQ((std::size_t)1, tree.edgeCount(root));
    ASSERT_EQ((std::size_t)1, tree.edgeCount(child));

    ASSERT_EQ((std::size_t)2, tree.vertices().size());
    ASSERT_EQ((std::size_t)1, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)1, tree.leafNodeCount());

    ASSERT_TRUE(tree.isChild(root, child));
    ASSERT_FALSE(tree.isChild(child, root));

    htd::vertex_t newRoot = tree.addParent(root);

    ASSERT_TRUE(tree.isVertex(root));
    ASSERT_TRUE(tree.isVertex(child));
    ASSERT_TRUE(tree.isVertex(newRoot));
    ASSERT_TRUE(tree.isRoot(newRoot));
    ASSERT_EQ(newRoot, tree.root());

    ASSERT_EQ((std::size_t)3, tree.vertexCount());
    ASSERT_EQ((std::size_t)2, tree.edgeCount());
    ASSERT_EQ((std::size_t)2, tree.edgeCount(root));
    ASSERT_EQ((std::size_t)1, tree.edgeCount(child));
    ASSERT_EQ((std::size_t)1, tree.edgeCount(newRoot));

    ASSERT_EQ((std::size_t)3, tree.vertices().size());
    ASSERT_EQ((std::size_t)2, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)1, tree.leafNodeCount());

    ASSERT_TRUE(tree.isChild(newRoot, root));
    ASSERT_TRUE(tree.isChild(root, child));

    ASSERT_EQ((std::size_t)1, tree.childCount(root));
    ASSERT_EQ((std::size_t)0, tree.childCount(child));
    ASSERT_EQ((std::size_t)1, tree.childCount(newRoot));

    ASSERT_EQ(root, tree.children(newRoot)[0]);
    ASSERT_EQ(child, tree.children(root)[0]);

    ASSERT_FALSE(tree.isLeafNode(root));
    ASSERT_TRUE(tree.isLeafNode(child));
    ASSERT_FALSE(tree.isLeafNode(newRoot));

    ASSERT_EQ((std::size_t)2, tree.neighborCount(root));
    ASSERT_EQ((std::size_t)1, tree.neighborCount(child));
    ASSERT_EQ((std::size_t)1, tree.neighborCount(newRoot));

    ASSERT_EQ((std::size_t)0, tree.associatedEdgeIds(newRoot, root).size());
    ASSERT_EQ((std::size_t)1, tree.associatedEdgeIds(root, newRoot).size());
    ASSERT_EQ((htd::id_t)1, tree.associatedEdgeIds(root, newRoot)[0]);
}

int main(int argc, char **argv)
{
    // coverity[GoogleTest may throw. This results in a non-zero exit code and is intended.]
    ::testing::InitGoogleTest(&argc, argv);

    // coverity[GoogleTest may throw. This results in a non-zero exit code and is intended.]
    return RUN_ALL_TESTS();
}
