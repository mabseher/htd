/*
 * File:   TreeTest.cpp
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

class TreeTest : public ::testing::Test
{
    public:
        TreeTest(void)
        {

        }

        virtual ~TreeTest()
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
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafCount());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());

    ASSERT_EQ(htd::Vertex::FIRST, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST, tree.nextEdgeId());

    delete libraryInstance;
}

TEST(TreeTest, CheckSize1Tree)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafCount());

    htd::vertex_t root = tree.insertRoot();

    ASSERT_TRUE(tree.isVertex(root));
    ASSERT_TRUE(tree.isRoot(root));
    ASSERT_EQ(root, tree.root());

    ASSERT_EQ((std::size_t)1, tree.vertexCount());
    ASSERT_EQ((std::size_t)1, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)0, tree.edgeCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount(root));

    ASSERT_EQ((std::size_t)1, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)1, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)1, tree.leafCount());
    ASSERT_EQ((std::size_t)1, tree.leaves().size());
    ASSERT_EQ((htd::vertex_t)1, tree.leaves()[0]);

    ASSERT_EQ((std::size_t)1, tree.isolatedVertexCount());
    ASSERT_EQ(root, tree.isolatedVertices()[0]);
    ASSERT_EQ(root, tree.isolatedVertexAtPosition(0));
    ASSERT_TRUE(tree.isIsolatedVertex(root));

    ASSERT_EQ(htd::Vertex::FIRST + 1, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST, tree.nextEdgeId());

    ASSERT_EQ((std::size_t)0, tree.height());
    ASSERT_EQ((std::size_t)0, tree.height(1));
    ASSERT_EQ((std::size_t)0, tree.depth(1));

    delete libraryInstance;
}

TEST(TreeTest, CheckSize3Tree)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    ASSERT_EQ((std::size_t)0, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    ASSERT_EQ((std::size_t)0, tree.vertices().size());
    ASSERT_EQ((std::size_t)0, tree.hyperedges().size());

    ASSERT_EQ((std::size_t)0, tree.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, tree.isolatedVertices().size());

    ASSERT_TRUE(tree.isConnected());

    ASSERT_EQ((std::size_t)0, tree.leafCount());

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

    ASSERT_EQ((std::size_t)1, tree.leafCount());

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

    ASSERT_EQ((std::size_t)1, tree.leafCount());

    ASSERT_TRUE(tree.isChild(newRoot, root));
    ASSERT_TRUE(tree.isChild(root, child));
    ASSERT_FALSE(tree.isChild(newRoot, child));
    ASSERT_TRUE(tree.isParent(child, root));
    ASSERT_TRUE(tree.isParent(root, newRoot));
    ASSERT_FALSE(tree.isParent(child, newRoot));

    ASSERT_EQ(child, tree.childAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(root, tree.childAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ(newRoot, tree.parent(root));
    ASSERT_EQ(root, tree.parent(child));

    ASSERT_EQ((std::size_t)1, tree.childCount(root));
    ASSERT_EQ((std::size_t)0, tree.childCount(child));
    ASSERT_EQ((std::size_t)1, tree.childCount(newRoot));

    ASSERT_EQ(root, tree.children(newRoot)[0]);
    ASSERT_EQ(child, tree.children(root)[0]);

    ASSERT_FALSE(tree.isLeaf(root));
    ASSERT_TRUE(tree.isLeaf(child));
    ASSERT_FALSE(tree.isLeaf(newRoot));

    ASSERT_EQ((std::size_t)2, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(child));
    ASSERT_EQ((std::size_t)3, tree.vertexCount(newRoot));

    ASSERT_EQ((std::size_t)2, tree.neighborCount(root));
    ASSERT_EQ((std::size_t)1, tree.neighborCount(child));
    ASSERT_EQ((std::size_t)1, tree.neighborCount(newRoot));

    ASSERT_EQ((std::size_t)0, tree.associatedEdgeIds(newRoot, root).size());
    ASSERT_EQ((std::size_t)1, tree.associatedEdgeIds(root, newRoot).size());
    ASSERT_EQ((htd::id_t)2, tree.associatedEdgeIds(root, newRoot)[0]);

    ASSERT_TRUE(tree.isEdge((htd::id_t)1));
    ASSERT_TRUE(tree.isEdge(root, newRoot));
    ASSERT_TRUE(tree.isEdge(std::vector<htd::vertex_t> { root, newRoot }));
    ASSERT_FALSE(tree.isEdge(std::vector<htd::vertex_t> { root, child, newRoot }));

    std::vector<htd::vertex_t> edgeElements1 { root, child };
    std::vector<htd::vertex_t> edgeElements2 { root, child, newRoot };

    ASSERT_TRUE(tree.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())));
    ASSERT_FALSE(tree.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())));

    ASSERT_EQ((std::size_t)1, tree.associatedEdgeIds(edgeElements1).size());
    ASSERT_EQ((std::size_t)0, tree.associatedEdgeIds(edgeElements2).size());
    ASSERT_EQ((htd::id_t)1, tree.associatedEdgeIds(edgeElements1)[0]);

    ASSERT_EQ((std::size_t)1, tree.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())).size());
    ASSERT_EQ((std::size_t)0, tree.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())).size());
    ASSERT_EQ((htd::id_t)1, tree.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end()))[0]);

    ASSERT_FALSE(tree.isNeighbor(root, root));
    ASSERT_TRUE(tree.isNeighbor(root, child));
    ASSERT_TRUE(tree.isNeighbor(root, newRoot));
    ASSERT_TRUE(tree.isNeighbor(child, root));
    ASSERT_FALSE(tree.isNeighbor(child, child));
    ASSERT_FALSE(tree.isNeighbor(child, newRoot));;
    ASSERT_TRUE(tree.isNeighbor(newRoot, root));
    ASSERT_FALSE(tree.isNeighbor(newRoot, child));
    ASSERT_FALSE(tree.isNeighbor(newRoot, newRoot));

    ASSERT_TRUE(tree.isConnected());
    ASSERT_TRUE(tree.isConnected(root, root));
    ASSERT_TRUE(tree.isConnected(root, child));
    ASSERT_TRUE(tree.isConnected(root, newRoot));
    ASSERT_TRUE(tree.isConnected(child, root));
    ASSERT_TRUE(tree.isConnected(child, child));
    ASSERT_TRUE(tree.isConnected(child, newRoot));;
    ASSERT_TRUE(tree.isConnected(newRoot, root));
    ASSERT_TRUE(tree.isConnected(newRoot, child));
    ASSERT_TRUE(tree.isConnected(newRoot, newRoot));

    ASSERT_EQ(root, tree.vertexAtPosition((htd::index_t)0));
    ASSERT_EQ(child, tree.vertexAtPosition((htd::index_t)1));
    ASSERT_EQ(newRoot, tree.vertexAtPosition((htd::index_t)2));

    const htd::ConstCollection<htd::vertex_t> & rootNeighbors = tree.neighbors(root);
    const htd::ConstCollection<htd::vertex_t> & childNeighbors = tree.neighbors(child);
    const htd::ConstCollection<htd::vertex_t> & newRootNeighbors = tree.neighbors(newRoot);

    std::vector<htd::vertex_t> rootNeighbors2;
    std::vector<htd::vertex_t> childNeighbors2;
    std::vector<htd::vertex_t> newRootNeighbors2;

    ASSERT_EQ((std::size_t)2, rootNeighbors.size());
    ASSERT_EQ((std::size_t)1, childNeighbors.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors.size());

    ASSERT_EQ((std::size_t)0, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)0, childNeighbors2.size());
    ASSERT_EQ((std::size_t)0, newRootNeighbors2.size());

    tree.copyNeighborsTo(root, rootNeighbors2);
    tree.copyNeighborsTo(child, childNeighbors2);
    tree.copyNeighborsTo(newRoot, newRootNeighbors2);

    ASSERT_EQ((std::size_t)2, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)1, childNeighbors2.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors2.size());

    ASSERT_EQ(child, rootNeighbors[0]);
    ASSERT_EQ(newRoot, rootNeighbors[1]);
    ASSERT_EQ(root, childNeighbors[0]);
    ASSERT_EQ(root, newRootNeighbors[0]);

    ASSERT_EQ(child, rootNeighbors2[0]);
    ASSERT_EQ(newRoot, rootNeighbors2[1]);
    ASSERT_EQ(root, childNeighbors2[0]);
    ASSERT_EQ(root, newRootNeighbors2[0]);

    ASSERT_EQ(child, tree.neighborAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(newRoot, tree.neighborAtPosition(root, (htd::index_t)1));
    ASSERT_EQ(root, tree.neighborAtPosition(child, (htd::index_t)0));
    ASSERT_EQ(root, tree.neighborAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ((std::size_t)2, tree.hyperedges(root).size());
    ASSERT_EQ((std::size_t)1, tree.hyperedges(child).size());
    ASSERT_EQ((std::size_t)1, tree.hyperedges(newRoot).size());

    ASSERT_EQ(root, tree.hyperedge(1)[0]);
    ASSERT_EQ(child, tree.hyperedge(1)[1]);

    ASSERT_EQ(root, tree.hyperedge(2)[0]);
    ASSERT_EQ(newRoot, tree.hyperedge(2)[1]);

    ASSERT_EQ(root, tree.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(child, tree.hyperedgeAtPosition(0)[1]);

    ASSERT_EQ(root, tree.hyperedgeAtPosition(1)[0]);
    ASSERT_EQ(newRoot, tree.hyperedgeAtPosition(1)[1]);

    ASSERT_EQ(root, tree.hyperedgeAtPosition(0, newRoot)[0]);
    ASSERT_EQ(newRoot, tree.hyperedgeAtPosition(0, newRoot)[1]);

    const htd::FilteredHyperedgeCollection & hyperedges = tree.hyperedgesAtPositions(std::vector<htd::index_t> { 1, 0, 1 });

    auto position = hyperedges.begin();

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(newRoot, (*position)[1]);

    ++position;

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(child, (*position)[1]);

    ++position;

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(newRoot, (*position)[1]);

    ASSERT_EQ(htd::Vertex::FIRST + 3, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 2, tree.nextEdgeId());

    ASSERT_EQ((std::size_t)2, tree.height());
    ASSERT_EQ((std::size_t)2, tree.height(newRoot));
    ASSERT_EQ((std::size_t)1, tree.height(root));
    ASSERT_EQ((std::size_t)0, tree.height(child));
    ASSERT_EQ((std::size_t)0, tree.depth(newRoot));
    ASSERT_EQ((std::size_t)1, tree.depth(root));
    ASSERT_EQ((std::size_t)2, tree.depth(child));

    delete libraryInstance;
}

TEST(TreeTest, CheckTreeManipulations1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    htd::vertex_t root = tree.insertRoot();

    htd::vertex_t node11 = tree.addChild(root);
    htd::vertex_t node12 = tree.addChild(root);
    htd::vertex_t node13 = tree.addChild(root);

    htd::vertex_t node111 = tree.addChild(node11);
    htd::vertex_t node121 = tree.addChild(node12);
    htd::vertex_t node122 = tree.addChild(node12);
    htd::vertex_t node131 = tree.addChild(node13);
    htd::vertex_t node132 = tree.addChild(node13);
    htd::vertex_t node133 = tree.addChild(node13);
    htd::vertex_t node134 = tree.addChild(node13);

    htd::vertex_t node1331 = tree.addChild(node133);

    ASSERT_EQ((std::size_t)12, tree.vertexCount());
    ASSERT_EQ((std::size_t)11, tree.edgeCount());

    ASSERT_EQ((std::size_t)3, tree.childCount(root));
    ASSERT_EQ((std::size_t)1, tree.childCount(node11));
    ASSERT_EQ((std::size_t)2, tree.childCount(node12));
    ASSERT_EQ((std::size_t)4, tree.childCount(node13));

    ASSERT_EQ((std::size_t)0, tree.childCount(node111));
    ASSERT_EQ((std::size_t)0, tree.childCount(node121));
    ASSERT_EQ((std::size_t)0, tree.childCount(node122));
    ASSERT_EQ((std::size_t)0, tree.childCount(node131));
    ASSERT_EQ((std::size_t)0, tree.childCount(node132));
    ASSERT_EQ((std::size_t)1, tree.childCount(node133));
    ASSERT_EQ((std::size_t)0, tree.childCount(node134));

    ASSERT_EQ((std::size_t)0, tree.childCount(node1331));

    ASSERT_EQ((std::size_t)7, tree.leafCount());

    ASSERT_EQ((std::size_t)12, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)2, tree.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, tree.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, tree.vertexCount(node13));

    ASSERT_EQ((std::size_t)1, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, tree.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node134));

    tree.setParent(node12, node111);

    ASSERT_EQ((std::size_t)12, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)5, tree.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, tree.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, tree.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, tree.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node134));

    tree.removeChild(node13, node132);

    ASSERT_FALSE(tree.isVertex(node132));

    ASSERT_EQ((std::size_t)11, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)5, tree.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, tree.vertexCount(node12));
    ASSERT_EQ((std::size_t)5, tree.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, tree.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node134));

    tree.removeVertex(node12);

    ASSERT_EQ((std::size_t)10, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)4, tree.vertexCount(node11));
    ASSERT_EQ((std::size_t)5, tree.vertexCount(node13));

    ASSERT_EQ((std::size_t)3, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, tree.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node134));

    tree.removeSubtree(node13);

    ASSERT_EQ((std::size_t)5, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)4, tree.vertexCount(node11));

    ASSERT_EQ((std::size_t)3, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));

    ASSERT_EQ((std::size_t)5, tree.vertexCount(root));
    ASSERT_EQ((std::size_t)4, tree.vertexCount(node11));

    ASSERT_EQ((std::size_t)3, tree.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, tree.vertexCount(node122));

    delete libraryInstance;
}

TEST(TreeTest, CheckTreeManipulations2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    htd::vertex_t root = tree.insertRoot();

    htd::vertex_t node1 = tree.addChild(root);
    htd::vertex_t node11 = tree.addChild(node1);

    tree.removeVertex(node1);

    ASSERT_EQ((std::size_t)2, tree.vertexCount(root));

    ASSERT_EQ(node11, tree.childAtPosition(root, 0));
    ASSERT_EQ(root, tree.parent(node11));

    ASSERT_EQ((std::size_t)1, tree.edgeCount());
    ASSERT_EQ((htd::id_t)3, tree.hyperedgeAtPosition(0).id());
    ASSERT_EQ(root, tree.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(node11, tree.hyperedgeAtPosition(0)[1]);

    htd::vertex_t newRoot = tree.addParent(root);

    tree.removeVertex(root);

    ASSERT_EQ((std::size_t)1, tree.edgeCount());
    ASSERT_EQ((htd::id_t)5, tree.hyperedgeAtPosition(0).id());
    ASSERT_EQ(node11, tree.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(newRoot, tree.hyperedgeAtPosition(0)[1]);

    htd::vertex_t node2 = tree.addChild(newRoot);

    htd::vertex_t newRoot2 = tree.addParent(newRoot);

    tree.removeVertex(newRoot);

    ASSERT_EQ((std::size_t)2, tree.edgeCount());
    ASSERT_EQ((htd::id_t)8, tree.hyperedgeAtPosition(0).id());
    ASSERT_EQ(node11, tree.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(newRoot2, tree.hyperedgeAtPosition(0)[1]);
    ASSERT_EQ((htd::id_t)9, tree.hyperedgeAtPosition(1).id());
    ASSERT_EQ(node2, tree.hyperedgeAtPosition(1)[0]);
    ASSERT_EQ(newRoot2, tree.hyperedgeAtPosition(1)[1]);

    tree.removeVertex(newRoot2);

    ASSERT_EQ((std::size_t)1, tree.edgeCount());
    ASSERT_EQ((htd::id_t)10, tree.hyperedgeAtPosition(0).id());
    ASSERT_EQ(node11, tree.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(node2, tree.hyperedgeAtPosition(0)[1]);

    tree.removeVertex(node11);

    ASSERT_EQ((std::size_t)1, tree.vertexCount());
    ASSERT_EQ((std::size_t)0, tree.edgeCount());

    tree.removeVertex(node2);

    ASSERT_EQ((std::size_t)0, tree.vertexCount());

    delete libraryInstance;
}

TEST(TreeTest, CheckTreeManipulations3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    htd::vertex_t root = tree.insertRoot();

    htd::vertex_t child = tree.addChild(root);

    htd::vertex_t intermediateNode = tree.addParent(child);

    ASSERT_EQ(htd::Vertex::FIRST + 3, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 3, tree.nextEdgeId());

    ASSERT_EQ((std::size_t)2, tree.height());
    ASSERT_EQ((std::size_t)2, tree.height(root));
    ASSERT_EQ((std::size_t)1, tree.height(intermediateNode));
    ASSERT_EQ((std::size_t)0, tree.height(child));
    ASSERT_EQ((std::size_t)0, tree.depth(root));
    ASSERT_EQ((std::size_t)1, tree.depth(intermediateNode));
    ASSERT_EQ((std::size_t)2, tree.depth(child));

    tree.swapWithParent(child);

    ASSERT_EQ(htd::Vertex::FIRST + 3, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 4, tree.nextEdgeId());

    ASSERT_EQ((std::size_t)2, tree.height());
    ASSERT_EQ((std::size_t)2, tree.height(root));
    ASSERT_EQ((std::size_t)0, tree.height(intermediateNode));
    ASSERT_EQ((std::size_t)1, tree.height(child));
    ASSERT_EQ((std::size_t)0, tree.depth(root));
    ASSERT_EQ((std::size_t)2, tree.depth(intermediateNode));
    ASSERT_EQ((std::size_t)1, tree.depth(child));

    ASSERT_EQ(root, tree.root());

    htd::vertex_t intermediateNode2 = tree.addChild(child);

    ASSERT_EQ(htd::Id::FIRST + 5, tree.nextEdgeId());

    tree.swapWithParent(child);

    ASSERT_EQ(child, tree.root());

    ASSERT_EQ(htd::Vertex::FIRST + 4, tree.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 5, tree.nextEdgeId());

    ASSERT_EQ((std::size_t)1, tree.height());
    ASSERT_EQ((std::size_t)0, tree.height(root));
    ASSERT_EQ((std::size_t)0, tree.height(intermediateNode));
    ASSERT_EQ((std::size_t)0, tree.height(intermediateNode2));
    ASSERT_EQ((std::size_t)1, tree.height(child));
    ASSERT_EQ((std::size_t)1, tree.depth(root));
    ASSERT_EQ((std::size_t)1, tree.depth(intermediateNode));
    ASSERT_EQ((std::size_t)1, tree.depth(intermediateNode2));
    ASSERT_EQ((std::size_t)0, tree.depth(child));

    delete libraryInstance;
}

TEST(TreeTest, CheckMakeRootFunctionality1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    htd::vertex_t node1 = tree.insertRoot();
    htd::vertex_t node2 = tree.addChild(node1);
    htd::vertex_t node3 = tree.addChild(node1);
    htd::vertex_t node4 = tree.addChild(node2);
    htd::vertex_t node5 = tree.addChild(node2);
    htd::vertex_t node6 = tree.addChild(node3);

    tree.makeRoot(node1);

    ASSERT_EQ((std::size_t)6, tree.vertexCount());

    ASSERT_TRUE(tree.isParent(node2, node1));
    ASSERT_TRUE(tree.isParent(node3, node1));
    ASSERT_TRUE(tree.isParent(node4, node2));
    ASSERT_TRUE(tree.isParent(node5, node2));
    ASSERT_TRUE(tree.isParent(node6, node3));

    ASSERT_TRUE(tree.isChild(node1, node2));
    ASSERT_TRUE(tree.isChild(node1, node3));
    ASSERT_TRUE(tree.isChild(node2, node4));
    ASSERT_TRUE(tree.isChild(node2, node5));
    ASSERT_TRUE(tree.isChild(node3, node6));

    tree.makeRoot(node2);

    ASSERT_EQ((std::size_t)6, tree.vertexCount());

    ASSERT_TRUE(tree.isParent(node1, node2));
    ASSERT_TRUE(tree.isParent(node3, node1));
    ASSERT_TRUE(tree.isParent(node4, node2));
    ASSERT_TRUE(tree.isParent(node5, node2));
    ASSERT_TRUE(tree.isParent(node6, node3));

    ASSERT_TRUE(tree.isChild(node2, node1));
    ASSERT_TRUE(tree.isChild(node1, node3));
    ASSERT_TRUE(tree.isChild(node2, node4));
    ASSERT_TRUE(tree.isChild(node2, node5));
    ASSERT_TRUE(tree.isChild(node3, node6));

    tree.makeRoot(node1);

    ASSERT_EQ((std::size_t)6, tree.vertexCount());

    ASSERT_TRUE(tree.isParent(node2, node1));
    ASSERT_TRUE(tree.isParent(node3, node1));
    ASSERT_TRUE(tree.isParent(node4, node2));
    ASSERT_TRUE(tree.isParent(node5, node2));
    ASSERT_TRUE(tree.isParent(node6, node3));

    ASSERT_TRUE(tree.isChild(node1, node2));
    ASSERT_TRUE(tree.isChild(node1, node3));
    ASSERT_TRUE(tree.isChild(node2, node4));
    ASSERT_TRUE(tree.isChild(node2, node5));
    ASSERT_TRUE(tree.isChild(node3, node6));

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
