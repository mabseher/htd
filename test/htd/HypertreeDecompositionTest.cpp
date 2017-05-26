/*
 * File:   HypertreeDecompositionTest.cpp
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

class HypertreeDecompositionTest : public ::testing::Test
{
    public:
        HypertreeDecompositionTest(void)
        {

        }

        virtual ~HypertreeDecompositionTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(HypertreeDecompositionTest, CheckEmptyTree)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition decomposition(libraryInstance);

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafCount());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckSize1Tree)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition decomposition(libraryInstance);

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafCount());

    htd::vertex_t root = decomposition.insertRoot();

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isRoot(root));
    ASSERT_EQ(root, decomposition.root());

    ASSERT_EQ((std::size_t)1, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount(root));

    ASSERT_EQ((std::size_t)1, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafCount());
    ASSERT_EQ((std::size_t)1, decomposition.leaves().size());
    ASSERT_EQ((htd::vertex_t)1, decomposition.leaves()[0]);

    ASSERT_EQ((std::size_t)1, decomposition.isolatedVertexCount());
    ASSERT_EQ(root, decomposition.isolatedVertices()[0]);
    ASSERT_EQ(root, decomposition.isolatedVertexAtPosition(0));
    ASSERT_TRUE(decomposition.isIsolatedVertex(root));

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckSize3Tree)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition decomposition(libraryInstance);

    ASSERT_EQ((std::size_t)0, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)0, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)0, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)0, decomposition.leafCount());

    htd::vertex_t root = decomposition.insertRoot();

    htd::vertex_t child = decomposition.addChild(root);

    ASSERT_NE(root, child);

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isVertex(child));
    ASSERT_TRUE(decomposition.isRoot(root));
    ASSERT_EQ(root, decomposition.root());

    ASSERT_EQ((std::size_t)2, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(child));

    ASSERT_EQ((std::size_t)2, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafCount());

    ASSERT_TRUE(decomposition.isChild(root, child));
    ASSERT_FALSE(decomposition.isChild(child, root));

    htd::vertex_t newRoot = decomposition.addParent(root);

    ASSERT_TRUE(decomposition.isVertex(root));
    ASSERT_TRUE(decomposition.isVertex(child));
    ASSERT_TRUE(decomposition.isVertex(newRoot));
    ASSERT_TRUE(decomposition.isRoot(newRoot));
    ASSERT_EQ(newRoot, decomposition.root());

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)2, decomposition.edgeCount());
    ASSERT_EQ((std::size_t)2, decomposition.edgeCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.edgeCount(newRoot));

    ASSERT_EQ((std::size_t)3, decomposition.vertices().size());
    ASSERT_EQ((std::size_t)2, decomposition.hyperedges().size());

    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, decomposition.isolatedVertices().size());

    ASSERT_TRUE(decomposition.isConnected());

    ASSERT_EQ((std::size_t)1, decomposition.leafCount());

    ASSERT_TRUE(decomposition.isChild(newRoot, root));
    ASSERT_TRUE(decomposition.isChild(root, child));
    ASSERT_FALSE(decomposition.isChild(newRoot, child));
    ASSERT_TRUE(decomposition.isParent(child, root));
    ASSERT_TRUE(decomposition.isParent(root, newRoot));
    ASSERT_FALSE(decomposition.isParent(child, newRoot));

    ASSERT_EQ(child, decomposition.childAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(root, decomposition.childAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ(newRoot, decomposition.parent(root));
    ASSERT_EQ(root, decomposition.parent(child));

    ASSERT_EQ((std::size_t)1, decomposition.childCount(root));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(newRoot));

    ASSERT_EQ(root, decomposition.children(newRoot)[0]);
    ASSERT_EQ(child, decomposition.children(root)[0]);

    ASSERT_FALSE(decomposition.isLeaf(root));
    ASSERT_TRUE(decomposition.isLeaf(child));
    ASSERT_FALSE(decomposition.isLeaf(newRoot));

    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(child));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(newRoot));

    ASSERT_EQ((std::size_t)2, decomposition.neighborCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.neighborCount(child));
    ASSERT_EQ((std::size_t)1, decomposition.neighborCount(newRoot));

    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(newRoot, root).size());
    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(root, newRoot).size());
    ASSERT_EQ((htd::id_t)2, decomposition.associatedEdgeIds(root, newRoot)[0]);

    ASSERT_TRUE(decomposition.isEdge((htd::id_t)1));
    ASSERT_TRUE(decomposition.isEdge(root, newRoot));
    ASSERT_TRUE(decomposition.isEdge(std::vector<htd::vertex_t> { root, newRoot }));
    ASSERT_FALSE(decomposition.isEdge(std::vector<htd::vertex_t> { root, child, newRoot }));

    std::vector<htd::vertex_t> edgeElements1 { root, child };
    std::vector<htd::vertex_t> edgeElements2 { root, child, newRoot };

    ASSERT_TRUE(decomposition.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())));
    ASSERT_FALSE(decomposition.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())));

    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(edgeElements1).size());
    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(edgeElements2).size());
    ASSERT_EQ((htd::id_t)1, decomposition.associatedEdgeIds(edgeElements1)[0]);

    ASSERT_EQ((std::size_t)1, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())).size());
    ASSERT_EQ((std::size_t)0, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())).size());
    ASSERT_EQ((htd::id_t)1, decomposition.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end()))[0]);

    ASSERT_FALSE(decomposition.isNeighbor(root, root));
    ASSERT_TRUE(decomposition.isNeighbor(root, child));
    ASSERT_TRUE(decomposition.isNeighbor(root, newRoot));
    ASSERT_TRUE(decomposition.isNeighbor(child, root));
    ASSERT_FALSE(decomposition.isNeighbor(child, child));
    ASSERT_FALSE(decomposition.isNeighbor(child, newRoot));;
    ASSERT_TRUE(decomposition.isNeighbor(newRoot, root));
    ASSERT_FALSE(decomposition.isNeighbor(newRoot, child));
    ASSERT_FALSE(decomposition.isNeighbor(newRoot, newRoot));

    ASSERT_TRUE(decomposition.isConnected());
    ASSERT_TRUE(decomposition.isConnected(root, root));
    ASSERT_TRUE(decomposition.isConnected(root, child));
    ASSERT_TRUE(decomposition.isConnected(root, newRoot));
    ASSERT_TRUE(decomposition.isConnected(child, root));
    ASSERT_TRUE(decomposition.isConnected(child, child));
    ASSERT_TRUE(decomposition.isConnected(child, newRoot));;
    ASSERT_TRUE(decomposition.isConnected(newRoot, root));
    ASSERT_TRUE(decomposition.isConnected(newRoot, child));
    ASSERT_TRUE(decomposition.isConnected(newRoot, newRoot));

    ASSERT_EQ(root, decomposition.vertexAtPosition((htd::index_t)0));
    ASSERT_EQ(child, decomposition.vertexAtPosition((htd::index_t)1));
    ASSERT_EQ(newRoot, decomposition.vertexAtPosition((htd::index_t)2));

    const htd::ConstCollection<htd::vertex_t> & rootNeighbors = decomposition.neighbors(root);
    const htd::ConstCollection<htd::vertex_t> & childNeighbors = decomposition.neighbors(child);
    const htd::ConstCollection<htd::vertex_t> & newRootNeighbors = decomposition.neighbors(newRoot);

    std::vector<htd::vertex_t> rootNeighbors2;
    std::vector<htd::vertex_t> childNeighbors2;
    std::vector<htd::vertex_t> newRootNeighbors2;

    ASSERT_EQ((std::size_t)2, rootNeighbors.size());
    ASSERT_EQ((std::size_t)1, childNeighbors.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors.size());

    ASSERT_EQ((std::size_t)0, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)0, childNeighbors2.size());
    ASSERT_EQ((std::size_t)0, newRootNeighbors2.size());

    decomposition.copyNeighborsTo(root, rootNeighbors2);
    decomposition.copyNeighborsTo(child, childNeighbors2);
    decomposition.copyNeighborsTo(newRoot, newRootNeighbors2);

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

    ASSERT_EQ(child, decomposition.neighborAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(newRoot, decomposition.neighborAtPosition(root, (htd::index_t)1));
    ASSERT_EQ(root, decomposition.neighborAtPosition(child, (htd::index_t)0));
    ASSERT_EQ(root, decomposition.neighborAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ((std::size_t)2, decomposition.hyperedges(root).size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges(child).size());
    ASSERT_EQ((std::size_t)1, decomposition.hyperedges(newRoot).size());

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckTreeManipulations)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition decomposition(libraryInstance);

    htd::vertex_t root = decomposition.insertRoot();

    htd::vertex_t node11 = decomposition.addChild(root);
    htd::vertex_t node12 = decomposition.addChild(root);
    htd::vertex_t node13 = decomposition.addChild(root);

    htd::vertex_t node111 = decomposition.addChild(node11);
    htd::vertex_t node121 = decomposition.addChild(node12);
    htd::vertex_t node122 = decomposition.addChild(node12);
    htd::vertex_t node131 = decomposition.addChild(node13);
    htd::vertex_t node132 = decomposition.addChild(node13);
    htd::vertex_t node133 = decomposition.addChild(node13);
    htd::vertex_t node134 = decomposition.addChild(node13);

    htd::vertex_t node1331 = decomposition.addChild(node133);

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount());
    ASSERT_EQ((std::size_t)11, decomposition.edgeCount());

    ASSERT_EQ((std::size_t)3, decomposition.childCount(root));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(node11));
    ASSERT_EQ((std::size_t)2, decomposition.childCount(node12));
    ASSERT_EQ((std::size_t)4, decomposition.childCount(node13));

    ASSERT_EQ((std::size_t)0, decomposition.childCount(node111));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node121));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node122));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node131));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node132));
    ASSERT_EQ((std::size_t)1, decomposition.childCount(node133));
    ASSERT_EQ((std::size_t)0, decomposition.childCount(node134));

    ASSERT_EQ((std::size_t)0, decomposition.childCount(node1331));

    ASSERT_EQ((std::size_t)7, decomposition.leafCount());

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.setParent(node12, node111);

    ASSERT_EQ((std::size_t)12, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)6, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node132));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeChild(node13, node132);

    ASSERT_FALSE(decomposition.isVertex(node132));

    ASSERT_EQ((std::size_t)11, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node12));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeVertex(node12);

    ASSERT_EQ((std::size_t)10, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node11));
    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(node13));

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node131));
    ASSERT_EQ((std::size_t)2, decomposition.vertexCount(node133));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node134));

    decomposition.removeSubtree(node13);

    ASSERT_EQ((std::size_t)5, decomposition.vertexCount(root));
    ASSERT_EQ((std::size_t)4, decomposition.vertexCount(node11));

    ASSERT_EQ((std::size_t)3, decomposition.vertexCount(node111));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node121));
    ASSERT_EQ((std::size_t)1, decomposition.vertexCount(node122));

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckCopyConstructors)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Tree tree(libraryInstance);

    htd::vertex_t root1 = tree.insertRoot();
    htd::vertex_t treeNode2 = tree.addChild(root1);
    htd::vertex_t treeNode3 = tree.addChild(root1);
    htd::vertex_t treeNode4 = tree.addChild(treeNode2);
    htd::vertex_t treeNode5 = tree.addChild(treeNode3);

    tree.removeVertex(treeNode4);

    htd::LabeledTree labeledTree(libraryInstance);

    htd::vertex_t root2 = labeledTree.insertRoot();
    htd::vertex_t labeledTreeNode2 = labeledTree.addChild(root2);
    htd::vertex_t labeledTreeNode3 = labeledTree.addChild(root2);

    labeledTree.removeVertex(labeledTreeNode2);

    htd::HypertreeDecomposition treeDecomposition(libraryInstance);

    htd::vertex_t root3 = treeDecomposition.insertRoot();
    htd::vertex_t treeDecompositionNode2 = treeDecomposition.addChild(root3);

    treeDecomposition.removeVertex(root3);

    treeDecomposition.mutableBagContent(treeDecompositionNode2) = std::vector<htd::vertex_t> { 1, 2, 3 };

    const htd::ITreeDecomposition & treeDecompositionReference = treeDecomposition;

    htd::HypertreeDecomposition td1(tree);
    htd::HypertreeDecomposition td2(labeledTree);
    htd::HypertreeDecomposition td3(treeDecomposition);
    htd::HypertreeDecomposition td4(treeDecompositionReference);

    ASSERT_EQ((std::size_t)4, td1.vertexCount());
    ASSERT_TRUE(td1.isVertex(root1));
    ASSERT_TRUE(td1.isVertex(treeNode2));
    ASSERT_TRUE(td1.isVertex(treeNode3));
    ASSERT_FALSE(td1.isVertex(treeNode4));
    ASSERT_TRUE(td1.isVertex(treeNode5));

    ASSERT_EQ((std::size_t)2, td2.vertexCount());
    ASSERT_TRUE(td2.isVertex(root2));
    ASSERT_FALSE(td2.isVertex(labeledTreeNode2));
    ASSERT_TRUE(td2.isVertex(labeledTreeNode3));

    ASSERT_EQ((std::size_t)1, td3.vertexCount());
    ASSERT_FALSE(td3.isVertex(root3));
    ASSERT_TRUE(td3.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)1, td4.vertexCount());
    ASSERT_FALSE(td4.isVertex(root3));
    ASSERT_TRUE(td4.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)0, td1.bagSize(root1));
    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode2));
    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode3));

    ASSERT_EQ((std::size_t)0, td1.bagSize(treeNode5));

    ASSERT_EQ((std::size_t)0, td2.bagSize(root2));

    ASSERT_EQ((std::size_t)0, td2.bagSize(labeledTreeNode3));

    ASSERT_EQ((std::size_t)3, td3.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td3.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td3.bagContent(treeDecompositionNode2)[2]);

    ASSERT_EQ((std::size_t)3, td4.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td4.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td4.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td4.bagContent(treeDecompositionNode2)[2]);

    td1 = treeDecomposition;
    td2 = tree;
    td3 = labeledTree;

    ASSERT_EQ((std::size_t)4, td2.vertexCount());
    ASSERT_TRUE(td2.isVertex(root1));
    ASSERT_TRUE(td2.isVertex(treeNode2));
    ASSERT_TRUE(td2.isVertex(treeNode3));
    ASSERT_FALSE(td2.isVertex(treeNode4));
    ASSERT_TRUE(td2.isVertex(treeNode5));

    ASSERT_EQ((std::size_t)2, td3.vertexCount());
    ASSERT_TRUE(td3.isVertex(root2));
    ASSERT_FALSE(td3.isVertex(labeledTreeNode2));
    ASSERT_TRUE(td3.isVertex(labeledTreeNode3));

    ASSERT_EQ((std::size_t)1, td1.vertexCount());
    ASSERT_FALSE(td1.isVertex(root3));
    ASSERT_TRUE(td1.isVertex(treeDecompositionNode2));

    ASSERT_EQ((std::size_t)0, td2.bagSize(root1));
    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode2));
    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode3));

    ASSERT_EQ((std::size_t)0, td2.bagSize(treeNode5));

    ASSERT_EQ((std::size_t)0, td3.bagSize(root2));

    ASSERT_EQ((std::size_t)0, td3.bagSize(labeledTreeNode3));

    ASSERT_EQ((std::size_t)3, td1.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td1.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td1.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td1.bagContent(treeDecompositionNode2)[2]);

    ASSERT_EQ((std::size_t)1, td1.leafCount());
    ASSERT_EQ((std::size_t)2, td2.leafCount());
    ASSERT_EQ((std::size_t)1, td3.leafCount());

    ASSERT_EQ(treeDecompositionNode2, td1.leaves()[0]);
    ASSERT_EQ(treeDecompositionNode2, td1.leafAtPosition(0));

    ASSERT_EQ(treeNode2, td2.leaves()[0]);
    ASSERT_EQ(treeNode2, td2.leafAtPosition(0));
    ASSERT_EQ(treeNode5, td2.leaves()[1]);
    ASSERT_EQ(treeNode5, td2.leafAtPosition(1));

    ASSERT_EQ(labeledTreeNode3, td3.leaves()[0]);
    ASSERT_EQ(labeledTreeNode3, td3.leafAtPosition(0));

    ASSERT_EQ((std::size_t)0, td1.joinNodeCount());
    ASSERT_EQ((std::size_t)1, td2.joinNodeCount());
    ASSERT_EQ((std::size_t)0, td3.joinNodeCount());

    ASSERT_EQ(root1, td2.joinNodes()[0]);
    ASSERT_EQ(root1, td2.joinNodeAtPosition(0));

    ASSERT_FALSE(td1.isJoinNode(treeDecompositionNode2));

    ASSERT_TRUE(td2.isJoinNode(root1));
    ASSERT_FALSE(td2.isJoinNode(treeNode2));
    ASSERT_FALSE(td2.isJoinNode(treeNode3));
    ASSERT_FALSE(td2.isJoinNode(treeNode5));

    ASSERT_FALSE(td3.isJoinNode(root2));
    ASSERT_FALSE(td3.isJoinNode(labeledTreeNode3));

    ASSERT_EQ((std::size_t)0, td1.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td2.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td3.forgetNodeCount());

    ASSERT_FALSE(td1.isForgetNode(treeDecompositionNode2));

    ASSERT_FALSE(td2.isForgetNode(root1));
    ASSERT_FALSE(td2.isForgetNode(treeNode2));
    ASSERT_FALSE(td2.isForgetNode(treeNode3));
    ASSERT_FALSE(td2.isForgetNode(treeNode5));

    ASSERT_FALSE(td3.isForgetNode(root2));
    ASSERT_FALSE(td3.isForgetNode(labeledTreeNode3));

    ASSERT_EQ((std::size_t)1, td1.introduceNodeCount());

    ASSERT_EQ((std::size_t)0, td2.introduceNodeCount());
    ASSERT_EQ((std::size_t)0, td3.introduceNodeCount());

    ASSERT_TRUE(td1.isIntroduceNode(treeDecompositionNode2));

    ASSERT_FALSE(td2.isIntroduceNode(root1));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode2));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode3));
    ASSERT_FALSE(td2.isIntroduceNode(treeNode5));

    ASSERT_FALSE(td3.isIntroduceNode(root2));
    ASSERT_FALSE(td3.isIntroduceNode(labeledTreeNode3));

    td2 = treeDecompositionReference;

    ASSERT_EQ((std::size_t)1, td2.vertexCount());

    ASSERT_EQ((std::size_t)3, td2.bagSize(treeDecompositionNode2));

    ASSERT_EQ((htd::vertex_t)1, td2.bagContent(treeDecompositionNode2)[0]);
    ASSERT_EQ((htd::vertex_t)2, td2.bagContent(treeDecompositionNode2)[1]);
    ASSERT_EQ((htd::vertex_t)3, td2.bagContent(treeDecompositionNode2)[2]);

    ASSERT_TRUE(td2.isIntroduceNode(treeDecompositionNode2));
    ASSERT_FALSE(td2.isForgetNode(treeDecompositionNode2));
    ASSERT_FALSE(td2.isJoinNode(treeDecompositionNode2));
    ASSERT_TRUE(td2.isLeaf(treeDecompositionNode2));

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckBagContentModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td1(libraryInstance);

    htd::vertex_t root = td1.insertRoot();

    ASSERT_EQ((std::size_t)0, td1.bagSize(root));
    ASSERT_EQ((std::size_t)0, td1.bagContent(root).size());

    std::vector<htd::vertex_t> bagContent { 1, 2, 3 };

    td1.mutableBagContent(root) = bagContent;

    ASSERT_EQ((std::size_t)3, td1.bagSize(root));
    ASSERT_EQ((std::size_t)3, td1.bagContent(root).size());

    ASSERT_EQ((htd::vertex_t)1, td1.bagContent(root)[0]);
    ASSERT_EQ((htd::vertex_t)2, td1.bagContent(root)[1]);
    ASSERT_EQ((htd::vertex_t)3, td1.bagContent(root)[2]);

    td1.mutableBagContent(root) = std::vector<htd::vertex_t> { 4, 5 };

    ASSERT_EQ((std::size_t)2, td1.bagSize(root));
    ASSERT_EQ((std::size_t)2, td1.bagContent(root).size());

    ASSERT_EQ((htd::vertex_t)4, td1.bagContent(root)[0]);
    ASSERT_EQ((htd::vertex_t)5, td1.bagContent(root)[1]);

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckCoveringEdgeModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td1(libraryInstance);

    htd::vertex_t root = td1.insertRoot();

    ASSERT_EQ((std::size_t)0, td1.coveringEdges(root).size());

    std::vector<htd::Hyperedge> coveringEdges1 { htd::Hyperedge(1, 2, 3) };

    td1.setCoveringEdges(root, coveringEdges1);

    ASSERT_EQ((std::size_t)1, td1.coveringEdges(root).size());

    ASSERT_EQ((htd::vertex_t)1, td1.coveringEdges(root)[0].id());
    ASSERT_EQ((htd::vertex_t)2, td1.coveringEdges(root)[0].elements()[0]);
    ASSERT_EQ((htd::vertex_t)3, td1.coveringEdges(root)[0].elements()[1]);

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckNodeTypeDetection)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td1(libraryInstance);
    htd::HypertreeDecomposition td2(libraryInstance);
    htd::HypertreeDecomposition td3(libraryInstance);

    htd::vertex_t root1 = td1.insertRoot();
    htd::vertex_t root2 = td2.insertRoot();
    htd::vertex_t root3 = td3.insertRoot();

    htd::vertex_t node11 = td1.addChild(root1);
    htd::vertex_t node21 = td2.addChild(root2);
    htd::vertex_t node31 = td3.addChild(root3);
    htd::vertex_t node32 = td3.addChild(root3);

    td2.mutableBagContent(node21) = std::vector<htd::vertex_t> { 1, 2 };

    td3.mutableBagContent(root3) = std::vector<htd::vertex_t> { 1, 2 };
    td3.mutableBagContent(node31) = std::vector<htd::vertex_t> { 1 };
    td3.mutableBagContent(node32) = std::vector<htd::vertex_t> { 2 };

    ASSERT_EQ((std::size_t)1, td1.leafCount());
    ASSERT_EQ((std::size_t)1, td2.leafCount());
    ASSERT_EQ((std::size_t)2, td3.leafCount());

    ASSERT_EQ((std::size_t)1, td1.leaves().size());
    ASSERT_EQ((std::size_t)1, td2.leaves().size());
    ASSERT_EQ((std::size_t)2, td3.leaves().size());

    ASSERT_EQ(node11, td1.leaves()[0]);
    ASSERT_EQ(node11, td1.leafAtPosition(0));

    ASSERT_EQ(node21, td2.leaves()[0]);
    ASSERT_EQ(node21, td2.leafAtPosition(0));

    ASSERT_EQ(node31, td3.leaves()[0]);
    ASSERT_EQ(node31, td3.leafAtPosition(0));
    ASSERT_EQ(node32, td3.leaves()[1]);
    ASSERT_EQ(node32, td3.leafAtPosition(1));

    ASSERT_EQ((std::size_t)0, td1.joinNodeCount());
    ASSERT_EQ((std::size_t)0, td2.joinNodeCount());
    ASSERT_EQ((std::size_t)1, td3.joinNodeCount());

    ASSERT_EQ((std::size_t)0, td1.joinNodes().size());
    ASSERT_EQ((std::size_t)0, td2.joinNodes().size());
    ASSERT_EQ((std::size_t)1, td3.joinNodes().size());

    ASSERT_EQ(root3, td3.joinNodes()[0]);
    ASSERT_EQ(root3, td3.joinNodeAtPosition(0));

    ASSERT_EQ((std::size_t)0, td1.forgetNodeCount());
    ASSERT_EQ((std::size_t)1, td2.forgetNodeCount());
    ASSERT_EQ((std::size_t)0, td3.forgetNodeCount());

    ASSERT_EQ((std::size_t)0, td1.forgetNodes().size());
    ASSERT_EQ((std::size_t)1, td2.forgetNodes().size());
    ASSERT_EQ((std::size_t)0, td3.forgetNodes().size());

    ASSERT_EQ(root2, td2.forgetNodes()[0]);
    ASSERT_EQ(root2, td2.forgetNodeAtPosition(0));

    ASSERT_EQ((std::size_t)0, td1.introduceNodeCount());
    ASSERT_EQ((std::size_t)1, td2.introduceNodeCount());
    ASSERT_EQ((std::size_t)2, td3.introduceNodeCount());

    ASSERT_EQ((std::size_t)0, td1.introduceNodes().size());
    ASSERT_EQ((std::size_t)1, td2.introduceNodes().size());
    ASSERT_EQ((std::size_t)2, td3.introduceNodes().size());

    ASSERT_EQ((htd::vertex_t)1, td2.introducedVertexAtPosition(node21, 0));
    ASSERT_EQ((htd::vertex_t)2, td2.introducedVertexAtPosition(node21, 1));

    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertexAtPosition(root3, 0, node32));

    ASSERT_EQ(node31, td3.introduceNodes()[0]);
    ASSERT_EQ(node31, td3.introduceNodeAtPosition(0));
    ASSERT_EQ(node32, td3.introduceNodes()[1]);
    ASSERT_EQ(node32, td3.introduceNodeAtPosition(1));

    ASSERT_EQ((std::size_t)0, td3.introducedVertexCount(root3));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(node31));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(node32));

    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(root3, node31));
    ASSERT_EQ((std::size_t)1, td3.introducedVertexCount(root3, node32));

    ASSERT_EQ((std::size_t)1, td3.introducedVertices(root3, node31).size());
    ASSERT_EQ((std::size_t)1, td3.introducedVertices(root3, node32).size());

    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertices(root3, node31)[0]);
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertices(root3, node32)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.introducedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)1, td3.introducedVertexAtPosition(root3, 0, node32));

    ASSERT_EQ((std::size_t)0, td1.rememberedVertexCount(root1));
    ASSERT_EQ((std::size_t)0, td1.rememberedVertexCount(root1, node11));
    ASSERT_EQ((std::size_t)0, td1.rememberedVertices(root1).size());
    ASSERT_EQ((std::size_t)0, td1.rememberedVertices(root1, node11).size());

    ASSERT_EQ((std::size_t)0, td2.rememberedVertexCount(root2));
    ASSERT_EQ((std::size_t)0, td2.rememberedVertexCount(root2, node21));
    ASSERT_EQ((std::size_t)0, td2.rememberedVertices(root2).size());
    ASSERT_EQ((std::size_t)0, td2.rememberedVertices(root2, node21).size());

    ASSERT_EQ((std::size_t)2, td3.rememberedVertexCount(root3));
    ASSERT_EQ((std::size_t)1, td3.rememberedVertexCount(root3, node31));
    ASSERT_EQ((std::size_t)1, td3.rememberedVertexCount(root3, node32));
    ASSERT_EQ((std::size_t)2, td3.rememberedVertices(root3).size());
    ASSERT_EQ((std::size_t)1, td3.rememberedVertices(root3, node31).size());
    ASSERT_EQ((std::size_t)1, td3.rememberedVertices(root3, node32).size());

    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertices(root3)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertices(root3)[1]);
    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertexAtPosition(root3, 0));
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertexAtPosition(root3, 1));

    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertices(root3, node31)[0]);
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertices(root3, node32)[0]);
    ASSERT_EQ((htd::vertex_t)1, td3.rememberedVertexAtPosition(root3, 0, node31));
    ASSERT_EQ((htd::vertex_t)2, td3.rememberedVertexAtPosition(root3, 0, node32));

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckIntroduceNodeDetection)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    td.mutableBagContent(node1) = std::vector<htd::vertex_t> { 1, 2 };
    td.mutableBagContent(node11) = std::vector<htd::vertex_t> { 1 };
    td.mutableBagContent(node12) = std::vector<htd::vertex_t> { 2 };
    td.mutableBagContent(node121) = std::vector<htd::vertex_t> { };

    ASSERT_EQ((std::size_t)2, td.introduceNodeCount());
    ASSERT_EQ(node11, td.introduceNodes()[0]);
    ASSERT_EQ(node11, td.introduceNodeAtPosition(0));
    ASSERT_EQ(node12, td.introduceNodes()[1]);
    ASSERT_EQ(node12, td.introduceNodeAtPosition(1));

    ASSERT_EQ((std::size_t)0, td.introducedVertexCount(node1));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node11));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.introducedVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)1, td.introducedVertexCount(node12, node121));

    ASSERT_EQ((htd::vertex_t)1, td.introducedVertices(node11)[0]);
    ASSERT_EQ((htd::vertex_t)1, td.introducedVertexAtPosition(node11, 0));
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertices(node12)[0]);
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertexAtPosition(node12, 0));

    ASSERT_EQ((htd::vertex_t)2, td.introducedVertices(node12, node121)[0]);
    ASSERT_EQ((htd::vertex_t)2, td.introducedVertexAtPosition(node12, 0, node121));

    ASSERT_TRUE(td.isIntroducedVertex(node12, 2));
    ASSERT_TRUE(td.isIntroducedVertex(node12, 2, node121));

    ASSERT_FALSE(td.isRememberedVertex(node12, 2));
    ASSERT_FALSE(td.isRememberedVertex(node12, 2, node121));

    std::vector<htd::vertex_t> introducedVertices;

    td.copyIntroducedVerticesTo(node12, introducedVertices);

    ASSERT_EQ((std::size_t)1, introducedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, introducedVertices[0]);

    introducedVertices.clear();

    ASSERT_EQ((std::size_t)0, introducedVertices.size());

    td.copyIntroducedVerticesTo(node12, introducedVertices, node121);

    ASSERT_EQ((std::size_t)1, introducedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, introducedVertices[0]);

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckRememberedVertexDetection)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    td.mutableBagContent(node1) = std::vector<htd::vertex_t> { 1, 2 };
    td.mutableBagContent(node11) = std::vector<htd::vertex_t> { 1 };
    td.mutableBagContent(node12) = std::vector<htd::vertex_t> { 2 };
    td.mutableBagContent(node121) = std::vector<htd::vertex_t> { };

    ASSERT_EQ((std::size_t)2, td.rememberedVertexCount(node1));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node11));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.rememberedVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)1, td.rememberedVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)0, td.rememberedVertexCount(node12, node121));

    ASSERT_EQ((htd::vertex_t)1, td.rememberedVertices(node1)[0]);
    ASSERT_EQ((htd::vertex_t)1, td.rememberedVertexAtPosition(node1, 0));
    ASSERT_EQ((htd::vertex_t)2, td.rememberedVertices(node1)[1]);
    ASSERT_EQ((htd::vertex_t)2, td.rememberedVertexAtPosition(node1, 1));

    ASSERT_TRUE(td.isRememberedVertex(node1, 1));
    ASSERT_TRUE(td.isRememberedVertex(node1, 2));
    ASSERT_FALSE(td.isRememberedVertex(node1, 1, node12));

    std::vector<htd::vertex_t> rememberedVertices;

    td.copyRememberedVerticesTo(node12, rememberedVertices);

    ASSERT_EQ((std::size_t)0, rememberedVertices.size());

    td.copyRememberedVerticesTo(node1, rememberedVertices);

    ASSERT_EQ((std::size_t)2, rememberedVertices.size());
    ASSERT_EQ((htd::vertex_t)1, rememberedVertices[0]);
    ASSERT_EQ((htd::vertex_t)2, rememberedVertices[1]);

    rememberedVertices.clear();

    td.copyRememberedVerticesTo(node1, rememberedVertices, node12);

    ASSERT_EQ((std::size_t)1, rememberedVertices.size());
    ASSERT_EQ((htd::vertex_t)2, rememberedVertices[0]);

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckForgetNodeDetection)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    htd::vertex_t node1 = td.insertRoot();

    htd::vertex_t node11 = td.addChild(node1);
    htd::vertex_t node12 = td.addChild(node1);

    htd::vertex_t node121 = td.addChild(node12);

    htd::vertex_t root = td.addParent(node1);

    td.mutableBagContent(root) = std::vector<htd::vertex_t> { 1 };
    td.mutableBagContent(node1) = std::vector<htd::vertex_t> { 1, 2 };
    td.mutableBagContent(node11) = std::vector<htd::vertex_t> { 1, 2 };
    td.mutableBagContent(node12) = std::vector<htd::vertex_t> { 1, 2 };
    td.mutableBagContent(node121) = std::vector<htd::vertex_t> { 1, 2, 3, 4 };

    ASSERT_EQ((std::size_t)2, td.forgetNodeCount());
    ASSERT_EQ(node12, td.forgetNodes()[0]);
    ASSERT_EQ(node12, td.forgetNodeAtPosition(0));
    ASSERT_EQ(root, td.forgetNodes()[1]);
    ASSERT_EQ(root, td.forgetNodeAtPosition(1));

    ASSERT_EQ((std::size_t)1, td.forgottenVertexCount(root));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node11));
    ASSERT_EQ((std::size_t)2, td.forgottenVertexCount(node12));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node121));

    ASSERT_EQ((std::size_t)1, td.forgottenVertexCount(root, node1));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1, node11));
    ASSERT_EQ((std::size_t)0, td.forgottenVertexCount(node1, node12));
    ASSERT_EQ((std::size_t)2, td.forgottenVertexCount(node12, node121));

    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertices(node12)[0]);
    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertexAtPosition(node12, 0));
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertices(node12)[1]);
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertexAtPosition(node12, 1));

    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertices(node12, node121)[0]);
    ASSERT_EQ((htd::vertex_t)3, td.forgottenVertexAtPosition(node12, 0, node121));
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertices(node12, node121)[1]);
    ASSERT_EQ((htd::vertex_t)4, td.forgottenVertexAtPosition(node12, 1, node121));

    ASSERT_FALSE(td.isForgottenVertex(node12, 1));
    ASSERT_FALSE(td.isForgottenVertex(node12, 2));
    ASSERT_TRUE(td.isForgottenVertex(node12, 3));
    ASSERT_TRUE(td.isForgottenVertex(node12, 4));

    ASSERT_FALSE(td.isForgottenVertex(node12, 1, node121));
    ASSERT_FALSE(td.isForgottenVertex(node12, 2, node121));
    ASSERT_TRUE(td.isForgottenVertex(node12, 3, node121));
    ASSERT_TRUE(td.isForgottenVertex(node12, 4, node121));

    ASSERT_TRUE(td.isRememberedVertex(node12, 1));
    ASSERT_TRUE(td.isRememberedVertex(node12, 2));
    ASSERT_FALSE(td.isRememberedVertex(node12, 3));
    ASSERT_FALSE(td.isRememberedVertex(node12, 4));

    ASSERT_TRUE(td.isRememberedVertex(node12, 1, node121));
    ASSERT_TRUE(td.isRememberedVertex(node12, 2, node121));
    ASSERT_FALSE(td.isRememberedVertex(node12, 3, node121));
    ASSERT_FALSE(td.isRememberedVertex(node12, 4, node121));

    std::vector<htd::vertex_t> forgottenVertices;

    td.copyForgottenVerticesTo(node12, forgottenVertices);

    ASSERT_EQ((std::size_t)2, forgottenVertices.size());
    ASSERT_EQ((htd::vertex_t)3, forgottenVertices[0]);
    ASSERT_EQ((htd::vertex_t)4, forgottenVertices[1]);

    forgottenVertices.clear();

    td.copyForgottenVerticesTo(node12, forgottenVertices, node121);

    ASSERT_EQ((std::size_t)2, forgottenVertices.size());
    ASSERT_EQ((htd::vertex_t)3, forgottenVertices[0]);
    ASSERT_EQ((htd::vertex_t)4, forgottenVertices[1]);

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, CheckInducedHyperedges)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    htd::vertex_t node1 = td.insertRoot();

    ASSERT_EQ((std::size_t)0, td.inducedHyperedges(node1).size());

    htd::Hyperedge h1(1, 1, 2);
    htd::Hyperedge h2(2, 2, 3);
    htd::Hyperedge h3(3, 3, 3);

    std::vector<htd::Hyperedge> inputEdges1 { h1, h2, h3 };

    htd::FilteredHyperedgeCollection hyperedges1(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 0, 1, 2 });
    htd::FilteredHyperedgeCollection hyperedges2(new htd::HyperedgeVector(inputEdges1), std::vector<htd::index_t> { 2, 1, 0 });

    td.mutableInducedHyperedges(node1) = hyperedges1;

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    auto it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)1, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)3, it->id());

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)1, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)3, it->id());

    td.mutableInducedHyperedges(node1) = std::move(hyperedges2);

    ASSERT_EQ((std::size_t)3, td.inducedHyperedges(node1).size());

    it = td.inducedHyperedges(node1).begin();

    ASSERT_EQ((htd::id_t)3, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)2, it->id());
    ++it;
    ASSERT_EQ((htd::id_t)1, it->id());

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, TestVertexLabelModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    td.insertRoot();
    td.addChild(1);
    td.addChild(1);
    td.addChild(2);

    td.setVertexLabel("Label", 1, new htd::Label<int>(1));
    td.setVertexLabel("Label", 2, new htd::Label<int>(2));
    td.setVertexLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, td.labelCount());
    ASSERT_EQ((std::size_t)1, td.labelNames().size());
    ASSERT_EQ("Label", td.labelNames()[0]);
    ASSERT_EQ("Label", td.labelNameAtPosition(0));

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    td.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.setVertexLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_TRUE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.swapVertexLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.swapVertexLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    td.swapVertexLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    htd::ILabel * exportedLabel = td.transferVertexLabel("Label", 1);

    ASSERT_FALSE(td.isLabeledVertex("Label", 0));
    ASSERT_FALSE(td.isLabeledVertex("Label", 1));
    ASSERT_TRUE(td.isLabeledVertex("Label", 2));
    ASSERT_TRUE(td.isLabeledVertex("Label", 3));

    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    td.setVertexLabel("Label2", 2, new htd::Label<int>(1));
    td.setVertexLabel("Label2", 3, new htd::Label<int>(2));

    td.swapVertexLabel("Label", 2, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.vertexLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.vertexLabel("Label2", 3)));

    td.removeVertexLabel("Label", 2);
    td.removeVertexLabel("Label", htd::Vertex::UNKNOWN);
    td.removeVertexLabel("Label3", 2);
    td.removeVertexLabel("Label3", htd::Vertex::UNKNOWN);

    ASSERT_EQ(1, htd::accessLabel<int>(td.vertexLabel("Label2", 2)));

    delete exportedLabel;

    delete libraryInstance;
}

TEST(HypertreeDecompositionTest, TestEdgeLabelModifications)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::HypertreeDecomposition td(libraryInstance);

    td.insertRoot();
    td.addChild(1);
    td.addChild(1);
    td.addChild(2);

    td.setEdgeLabel("Label", 1, new htd::Label<int>(1));
    td.setEdgeLabel("Label", 2, new htd::Label<int>(2));
    td.setEdgeLabel("Label", 3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)1, td.labelCount());
    ASSERT_EQ((std::size_t)1, td.labelNames().size());
    ASSERT_EQ("Label", td.labelNames()[0]);
    ASSERT_EQ("Label", td.labelNameAtPosition(0));

    ASSERT_FALSE(td.isLabeledEdge("Label", 0));
    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(3, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    td.setEdgeLabel("Label", 3, newLabel);

    ASSERT_FALSE(td.isLabeledEdge("Label", 0));
    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.setEdgeLabel("Label", 3, newLabel);

    ASSERT_TRUE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));
    ASSERT_FALSE(td.isLabeledEdge("Label", 0));

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.swapEdgeLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.swapEdgeLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    td.swapEdgeLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label", 1)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    htd::ILabel * exportedLabel = td.transferEdgeLabel("Label", 1);

    ASSERT_FALSE(td.isLabeledEdge("Label", 1));
    ASSERT_TRUE(td.isLabeledEdge("Label", 2));
    ASSERT_TRUE(td.isLabeledEdge("Label", 3));
    ASSERT_FALSE(td.isLabeledEdge("Label", 0));

    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    td.setEdgeLabel("Label2", 2, new htd::Label<int>(1));
    td.setEdgeLabel("Label2", 3, new htd::Label<int>(2));

    td.swapEdgeLabel("Label", 2, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(td.edgeLabel("Label", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label", 3)));
    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label2", 2)));
    ASSERT_EQ(2, htd::accessLabel<int>(td.edgeLabel("Label2", 3)));

    td.removeEdgeLabel("Label", 2);
    td.removeEdgeLabel("Label", htd::Vertex::UNKNOWN);
    td.removeEdgeLabel("Label3", 2);
    td.removeEdgeLabel("Label3", htd::Vertex::UNKNOWN);

    ASSERT_EQ(1, htd::accessLabel<int>(td.edgeLabel("Label2", 2)));

    delete exportedLabel;

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
