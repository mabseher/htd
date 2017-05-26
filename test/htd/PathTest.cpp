/*
 * File:   PathTest.cpp
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

class PathTest : public ::testing::Test
{
    public:
        PathTest(void)
        {

        }

        virtual ~PathTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(PathTest, CheckEmptyPath)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path(libraryInstance);

    ASSERT_EQ((std::size_t)0, path.vertexCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount());

    ASSERT_EQ((std::size_t)0, path.vertices().size());
    ASSERT_EQ((std::size_t)0, path.hyperedges().size());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)0, path.leafCount());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());

    ASSERT_EQ(htd::Vertex::FIRST, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST, path.nextEdgeId());

    delete libraryInstance;
}

TEST(PathTest, CheckSize1Path)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path(libraryInstance);

    ASSERT_EQ((std::size_t)0, path.vertexCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount());

    ASSERT_EQ((std::size_t)0, path.vertices().size());
    ASSERT_EQ((std::size_t)0, path.hyperedges().size());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)0, path.leafCount());

    htd::vertex_t root = path.insertRoot();

    ASSERT_TRUE(path.isVertex(root));
    ASSERT_TRUE(path.isRoot(root));
    ASSERT_EQ(root, path.root());

    ASSERT_EQ((std::size_t)1, path.vertexCount());
    ASSERT_EQ((std::size_t)1, path.vertexCount(root));
    ASSERT_EQ((std::size_t)0, path.edgeCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount(root));

    ASSERT_EQ((std::size_t)1, path.vertices().size());
    ASSERT_EQ((std::size_t)0, path.hyperedges().size());

    ASSERT_EQ((std::size_t)1, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)1, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)1, path.leafCount());
    ASSERT_EQ((std::size_t)1, path.leaves().size());
    ASSERT_EQ((htd::vertex_t)1, path.leaves()[0]);

    ASSERT_EQ((std::size_t)1, path.isolatedVertexCount());
    ASSERT_EQ(root, path.isolatedVertices()[0]);
    ASSERT_EQ(root, path.isolatedVertexAtPosition(0));
    ASSERT_TRUE(path.isIsolatedVertex(root));

    ASSERT_EQ(htd::Vertex::FIRST + 1, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST, path.nextEdgeId());

    ASSERT_EQ((std::size_t)0, path.height());
    ASSERT_EQ((std::size_t)0, path.height(1));
    ASSERT_EQ((std::size_t)0, path.depth(1));

    delete libraryInstance;
}

TEST(PathTest, CheckSize3Path)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path(libraryInstance);

    ASSERT_EQ((std::size_t)0, path.vertexCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount());

    ASSERT_EQ((std::size_t)0, path.vertices().size());
    ASSERT_EQ((std::size_t)0, path.hyperedges().size());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)0, path.leafCount());

    htd::vertex_t root = path.insertRoot();

    htd::vertex_t child = path.addChild(root);

    ASSERT_NE(root, child);

    ASSERT_TRUE(path.isVertex(root));
    ASSERT_TRUE(path.isVertex(child));
    ASSERT_TRUE(path.isRoot(root));
    ASSERT_EQ(root, path.root());

    ASSERT_EQ((std::size_t)2, path.vertexCount());
    ASSERT_EQ((std::size_t)1, path.edgeCount());
    ASSERT_EQ((std::size_t)1, path.edgeCount(root));
    ASSERT_EQ((std::size_t)1, path.edgeCount(child));

    ASSERT_EQ((std::size_t)2, path.vertices().size());
    ASSERT_EQ((std::size_t)1, path.hyperedges().size());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)1, path.leafCount());

    ASSERT_TRUE(path.isChild(root, child));
    ASSERT_FALSE(path.isChild(child, root));

    htd::vertex_t newRoot = path.addParent(root);

    ASSERT_TRUE(path.isVertex(root));
    ASSERT_TRUE(path.isVertex(child));
    ASSERT_TRUE(path.isVertex(newRoot));
    ASSERT_TRUE(path.isRoot(newRoot));
    ASSERT_EQ(newRoot, path.root());

    ASSERT_EQ((std::size_t)3, path.vertexCount());
    ASSERT_EQ((std::size_t)2, path.edgeCount());
    ASSERT_EQ((std::size_t)2, path.edgeCount(root));
    ASSERT_EQ((std::size_t)1, path.edgeCount(child));
    ASSERT_EQ((std::size_t)1, path.edgeCount(newRoot));

    ASSERT_EQ((std::size_t)3, path.vertices().size());
    ASSERT_EQ((std::size_t)2, path.hyperedges().size());

    ASSERT_EQ((std::size_t)0, path.isolatedVertexCount());
    ASSERT_EQ((std::size_t)0, path.isolatedVertices().size());

    ASSERT_TRUE(path.isConnected());

    ASSERT_EQ((std::size_t)1, path.leafCount());

    ASSERT_TRUE(path.isChild(newRoot, root));
    ASSERT_TRUE(path.isChild(root, child));
    ASSERT_FALSE(path.isChild(newRoot, child));
    ASSERT_TRUE(path.isParent(child, root));
    ASSERT_TRUE(path.isParent(root, newRoot));
    ASSERT_FALSE(path.isParent(child, newRoot));

    ASSERT_EQ(child, path.childAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(root, path.childAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ(newRoot, path.parent(root));
    ASSERT_EQ(root, path.parent(child));

    ASSERT_EQ((std::size_t)1, path.childCount(root));
    ASSERT_EQ((std::size_t)0, path.childCount(child));
    ASSERT_EQ((std::size_t)1, path.childCount(newRoot));

    ASSERT_EQ(root, path.children(newRoot)[0]);
    ASSERT_EQ(child, path.children(root)[0]);

    ASSERT_FALSE(path.isLeaf(root));
    ASSERT_TRUE(path.isLeaf(child));
    ASSERT_FALSE(path.isLeaf(newRoot));

    ASSERT_EQ((std::size_t)2, path.vertexCount(root));
    ASSERT_EQ((std::size_t)1, path.vertexCount(child));
    ASSERT_EQ((std::size_t)3, path.vertexCount(newRoot));

    ASSERT_EQ((std::size_t)2, path.neighborCount(root));
    ASSERT_EQ((std::size_t)1, path.neighborCount(child));
    ASSERT_EQ((std::size_t)1, path.neighborCount(newRoot));

    ASSERT_EQ((std::size_t)0, path.associatedEdgeIds(newRoot, root).size());
    ASSERT_EQ((std::size_t)1, path.associatedEdgeIds(root, newRoot).size());
    ASSERT_EQ((htd::id_t)2, path.associatedEdgeIds(root, newRoot)[0]);

    ASSERT_TRUE(path.isEdge((htd::id_t)1));
    ASSERT_TRUE(path.isEdge(root, newRoot));
    ASSERT_TRUE(path.isEdge(std::vector<htd::vertex_t> { root, newRoot }));
    ASSERT_FALSE(path.isEdge(std::vector<htd::vertex_t> { root, child, newRoot }));

    std::vector<htd::vertex_t> edgeElements1 { root, child };
    std::vector<htd::vertex_t> edgeElements2 { root, child, newRoot };

    ASSERT_TRUE(path.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())));
    ASSERT_FALSE(path.isEdge(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())));

    ASSERT_EQ((std::size_t)1, path.associatedEdgeIds(edgeElements1).size());
    ASSERT_EQ((std::size_t)0, path.associatedEdgeIds(edgeElements2).size());
    ASSERT_EQ((htd::id_t)1, path.associatedEdgeIds(edgeElements1)[0]);

    ASSERT_EQ((std::size_t)1, path.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end())).size());
    ASSERT_EQ((std::size_t)0, path.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements2.begin(), edgeElements2.end())).size());
    ASSERT_EQ((htd::id_t)1, path.associatedEdgeIds(htd::ConstCollection<htd::vertex_t>(edgeElements1.begin(), edgeElements1.end()))[0]);

    ASSERT_FALSE(path.isNeighbor(root, root));
    ASSERT_TRUE(path.isNeighbor(root, child));
    ASSERT_TRUE(path.isNeighbor(root, newRoot));
    ASSERT_TRUE(path.isNeighbor(child, root));
    ASSERT_FALSE(path.isNeighbor(child, child));
    ASSERT_FALSE(path.isNeighbor(child, newRoot));;
    ASSERT_TRUE(path.isNeighbor(newRoot, root));
    ASSERT_FALSE(path.isNeighbor(newRoot, child));
    ASSERT_FALSE(path.isNeighbor(newRoot, newRoot));

    ASSERT_TRUE(path.isConnected());
    ASSERT_TRUE(path.isConnected(root, root));
    ASSERT_TRUE(path.isConnected(root, child));
    ASSERT_TRUE(path.isConnected(root, newRoot));
    ASSERT_TRUE(path.isConnected(child, root));
    ASSERT_TRUE(path.isConnected(child, child));
    ASSERT_TRUE(path.isConnected(child, newRoot));;
    ASSERT_TRUE(path.isConnected(newRoot, root));
    ASSERT_TRUE(path.isConnected(newRoot, child));
    ASSERT_TRUE(path.isConnected(newRoot, newRoot));

    ASSERT_EQ(root, path.vertexAtPosition((htd::index_t)0));
    ASSERT_EQ(child, path.vertexAtPosition((htd::index_t)1));
    ASSERT_EQ(newRoot, path.vertexAtPosition((htd::index_t)2));

    const htd::ConstCollection<htd::vertex_t> & rootNeighbors = path.neighbors(root);
    const htd::ConstCollection<htd::vertex_t> & childNeighbors = path.neighbors(child);
    const htd::ConstCollection<htd::vertex_t> & newRootNeighbors = path.neighbors(newRoot);

    std::vector<htd::vertex_t> rootNeighbors2;
    std::vector<htd::vertex_t> childNeighbors2;
    std::vector<htd::vertex_t> newRootNeighbors2;

    ASSERT_EQ((std::size_t)2, rootNeighbors.size());
    ASSERT_EQ((std::size_t)1, childNeighbors.size());
    ASSERT_EQ((std::size_t)1, newRootNeighbors.size());

    ASSERT_EQ((std::size_t)0, rootNeighbors2.size());
    ASSERT_EQ((std::size_t)0, childNeighbors2.size());
    ASSERT_EQ((std::size_t)0, newRootNeighbors2.size());

    path.copyNeighborsTo(root, rootNeighbors2);
    path.copyNeighborsTo(child, childNeighbors2);
    path.copyNeighborsTo(newRoot, newRootNeighbors2);

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

    ASSERT_EQ(child, path.neighborAtPosition(root, (htd::index_t)0));
    ASSERT_EQ(newRoot, path.neighborAtPosition(root, (htd::index_t)1));
    ASSERT_EQ(root, path.neighborAtPosition(child, (htd::index_t)0));
    ASSERT_EQ(root, path.neighborAtPosition(newRoot, (htd::index_t)0));

    ASSERT_EQ((std::size_t)2, path.hyperedges(root).size());
    ASSERT_EQ((std::size_t)1, path.hyperedges(child).size());
    ASSERT_EQ((std::size_t)1, path.hyperedges(newRoot).size());

    ASSERT_EQ(root, path.hyperedge(1)[0]);
    ASSERT_EQ(child, path.hyperedge(1)[1]);

    ASSERT_EQ(root, path.hyperedge(2)[0]);
    ASSERT_EQ(newRoot, path.hyperedge(2)[1]);

    ASSERT_EQ(root, path.hyperedgeAtPosition(0)[0]);
    ASSERT_EQ(child, path.hyperedgeAtPosition(0)[1]);

    ASSERT_EQ(root, path.hyperedgeAtPosition(1)[0]);
    ASSERT_EQ(newRoot, path.hyperedgeAtPosition(1)[1]);

    ASSERT_EQ(root, path.hyperedgeAtPosition(0, newRoot)[0]);
    ASSERT_EQ(newRoot, path.hyperedgeAtPosition(0, newRoot)[1]);

    const htd::FilteredHyperedgeCollection & hyperedges = path.hyperedgesAtPositions(std::vector<htd::index_t> { 1, 0, 1 });

    auto position = hyperedges.begin();

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(newRoot, (*position)[1]);

    ++position;

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(child, (*position)[1]);

    ++position;

    ASSERT_EQ(root, (*position)[0]);
    ASSERT_EQ(newRoot, (*position)[1]);

    ASSERT_EQ(htd::Vertex::FIRST + 3, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 2, path.nextEdgeId());

    ASSERT_EQ((std::size_t)2, path.height());
    ASSERT_EQ((std::size_t)2, path.height(newRoot));
    ASSERT_EQ((std::size_t)1, path.height(root));
    ASSERT_EQ((std::size_t)0, path.height(child));
    ASSERT_EQ((std::size_t)0, path.depth(newRoot));
    ASSERT_EQ((std::size_t)1, path.depth(root));
    ASSERT_EQ((std::size_t)2, path.depth(child));

    delete libraryInstance;
}

TEST(PathTest, CheckPathManipulations1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path(libraryInstance);

    htd::vertex_t root = path.insertRoot();

    htd::vertex_t child = path.addChild(root);

    htd::vertex_t intermediateNode = path.addParent(child);

    ASSERT_EQ(htd::Vertex::FIRST + 3, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 3, path.nextEdgeId());

    ASSERT_EQ((std::size_t)2, path.height());
    ASSERT_EQ((std::size_t)2, path.height(root));
    ASSERT_EQ((std::size_t)1, path.height(intermediateNode));
    ASSERT_EQ((std::size_t)0, path.height(child));
    ASSERT_EQ((std::size_t)0, path.depth(root));
    ASSERT_EQ((std::size_t)1, path.depth(intermediateNode));
    ASSERT_EQ((std::size_t)2, path.depth(child));

    path.swapWithParent(child);

    ASSERT_EQ(htd::Vertex::FIRST + 3, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 4, path.nextEdgeId());

    ASSERT_EQ((std::size_t)2, path.height());
    ASSERT_EQ((std::size_t)2, path.height(root));
    ASSERT_EQ((std::size_t)0, path.height(intermediateNode));
    ASSERT_EQ((std::size_t)1, path.height(child));
    ASSERT_EQ((std::size_t)0, path.depth(root));
    ASSERT_EQ((std::size_t)2, path.depth(intermediateNode));
    ASSERT_EQ((std::size_t)1, path.depth(child));

    ASSERT_EQ(root, path.root());

    htd::vertex_t intermediateNode2 = path.addChild(child);

    path.swapWithParent(child);

    ASSERT_EQ(child, path.root());

    ASSERT_EQ(htd::Vertex::FIRST + 4, path.nextVertex());

    ASSERT_EQ(htd::Id::FIRST + 7, path.nextEdgeId());

    ASSERT_EQ((std::size_t)3, path.height());
    ASSERT_EQ((std::size_t)2, path.height(root));
    ASSERT_EQ((std::size_t)0, path.height(intermediateNode));
    ASSERT_EQ((std::size_t)1, path.height(intermediateNode2));
    ASSERT_EQ((std::size_t)3, path.height(child));
    ASSERT_EQ((std::size_t)1, path.depth(root));
    ASSERT_EQ((std::size_t)3, path.depth(intermediateNode));
    ASSERT_EQ((std::size_t)2, path.depth(intermediateNode2));
    ASSERT_EQ((std::size_t)0, path.depth(child));

    delete libraryInstance;
}

TEST(PathTest, CheckPathModifications2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path(libraryInstance);

    htd::vertex_t vertex1 = path.insertRoot();
    htd::vertex_t vertex2 = path.addChild(vertex1);
    htd::vertex_t vertex3 = path.addChild(vertex2);
    htd::vertex_t vertex4 = path.addChild(vertex3);

    ASSERT_EQ((std::size_t)4, path.vertexCount());
    ASSERT_EQ((std::size_t)3, path.edgeCount());

    path.removeVertex(vertex2);

    ASSERT_FALSE(path.isVertex(vertex2));

    ASSERT_EQ((std::size_t)3, path.vertexCount());
    ASSERT_EQ((std::size_t)2, path.edgeCount());

    ASSERT_TRUE(path.isNeighbor(vertex1, vertex3));
    ASSERT_TRUE(path.isNeighbor(vertex3, vertex4));

    path.removeSubpath(vertex3);

    ASSERT_EQ((std::size_t)1, path.vertexCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount());

    path.removeVertex(vertex1);

    ASSERT_EQ((std::size_t)0, path.vertexCount());

    htd::vertex_t vertex5 = path.insertRoot();
    htd::vertex_t vertex6 = path.addChild(vertex5);
    htd::vertex_t vertex7 = path.addChild(vertex6);

    ASSERT_EQ((std::size_t)3, path.vertexCount());
    ASSERT_EQ((std::size_t)2, path.edgeCount());

    path.removeChild(vertex5);

    ASSERT_EQ((std::size_t)2, path.vertexCount());
    ASSERT_EQ((std::size_t)1, path.edgeCount());

    path.removeChild(vertex5, vertex7);

    ASSERT_EQ((std::size_t)1, path.vertexCount());
    ASSERT_EQ((std::size_t)0, path.edgeCount());

    delete libraryInstance;
}

TEST(PathTest, CheckCopyConstructors)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::Path path1(libraryInstance);

    htd::vertex_t vertex1 = path1.insertRoot();
    htd::vertex_t vertex2 = path1.addChild(vertex1);
    htd::vertex_t vertex3 = path1.addChild(vertex2);

    path1.removeVertex(vertex2);

    ASSERT_EQ((std::size_t)2, path1.vertexCount());
    ASSERT_EQ((std::size_t)1, path1.edgeCount());

    htd::Path path2(path1);

    path2.addChild(vertex3);

    ASSERT_EQ((std::size_t)3, path2.vertexCount());
    ASSERT_EQ((std::size_t)2, path2.edgeCount());

    htd::Path path3(libraryInstance);

    ASSERT_EQ((std::size_t)0, path3.vertexCount());
    ASSERT_EQ((std::size_t)0, path3.edgeCount());

    path3 = path1;

    ASSERT_EQ((std::size_t)2, path3.vertexCount());
    ASSERT_EQ((std::size_t)1, path3.edgeCount());

    path3 = path2;

    ASSERT_EQ((std::size_t)3, path3.vertexCount());
    ASSERT_EQ((std::size_t)2, path3.edgeCount());

    const htd::IPath & pathReference1 = path1;

    path3 = pathReference1;

    ASSERT_EQ((std::size_t)2, path3.vertexCount());
    ASSERT_EQ((std::size_t)1, path3.edgeCount());

    htd::Path path4(pathReference1);

    ASSERT_EQ((std::size_t)2, path4.vertexCount());
    ASSERT_EQ((std::size_t)1, path4.edgeCount());

    delete libraryInstance;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
