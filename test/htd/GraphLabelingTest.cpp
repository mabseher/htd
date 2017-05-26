/*
 * File:   GraphLabelingTest.cpp
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

#include <memory>
#include <vector>

class GraphLabelingTest : public ::testing::Test
{
    public:
        GraphLabelingTest(void)
        {

        }

        virtual ~GraphLabelingTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(GraphLabelingTest, TestEmptyLabeling)
{
    htd::GraphLabeling labeling;

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());

    ASSERT_FALSE(labeling.isLabeledVertex(0));
    ASSERT_FALSE(labeling.isLabeledEdge(0));
}

TEST(GraphLabelingTest, TestVertexLabelModifications)
{
    htd::GraphLabeling labeling;

    labeling.setVertexLabel(1, new htd::Label<int>(1));
    labeling.setVertexLabel(2, new htd::Label<int>(2));
    labeling.setVertexLabel(3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)3, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());

    ASSERT_FALSE(labeling.isLabeledVertex(0));
    ASSERT_TRUE(labeling.isLabeledVertex(1));
    ASSERT_TRUE(labeling.isLabeledVertex(2));
    ASSERT_TRUE(labeling.isLabeledVertex(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(3, htd::accessLabel<int>(labeling.vertexLabel(3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    labeling.setVertexLabel(3, newLabel);

    ASSERT_FALSE(labeling.isLabeledVertex(0));
    ASSERT_TRUE(labeling.isLabeledVertex(1));
    ASSERT_TRUE(labeling.isLabeledVertex(2));
    ASSERT_TRUE(labeling.isLabeledVertex(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(3)));

    labeling.setVertexLabel(3, newLabel);

    ASSERT_FALSE(labeling.isLabeledVertex(0));
    ASSERT_TRUE(labeling.isLabeledVertex(1));
    ASSERT_TRUE(labeling.isLabeledVertex(2));
    ASSERT_TRUE(labeling.isLabeledVertex(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(3)));

    labeling.swapVertexLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(3)));

    labeling.swapVertexLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(3)));

    labeling.swapVertexLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.vertexLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(3)));

    htd::ILabel * exportedLabel = labeling.transferVertexLabel(1);

    ASSERT_FALSE(labeling.isLabeledVertex(0));
    ASSERT_FALSE(labeling.isLabeledVertex(1));
    ASSERT_TRUE(labeling.isLabeledVertex(2));
    ASSERT_TRUE(labeling.isLabeledVertex(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(2, htd::accessLabel<int>(labeling.vertexLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.vertexLabel(3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    delete exportedLabel;

    ASSERT_EQ((std::size_t)2, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());

    labeling.removeVertexLabel(2);
    labeling.removeVertexLabel(2);

    ASSERT_EQ((std::size_t)1, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());

    labeling.clear();

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());
}

TEST(GraphLabelingTest, TestEdgeLabelModifications)
{
    htd::GraphLabeling labeling;

    labeling.setEdgeLabel(1, new htd::Label<int>(1));
    labeling.setEdgeLabel(2, new htd::Label<int>(2));
    labeling.setEdgeLabel(3, new htd::Label<int>(3));

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)3, labeling.edgeLabelCount());

    ASSERT_FALSE(labeling.isLabeledEdge(0));
    ASSERT_TRUE(labeling.isLabeledEdge(1));
    ASSERT_TRUE(labeling.isLabeledEdge(2));
    ASSERT_TRUE(labeling.isLabeledEdge(3));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(3, htd::accessLabel<int>(labeling.edgeLabel(3)));

    htd::ILabel * newLabel = new htd::Label<int>(33);

    labeling.setEdgeLabel(3, newLabel);

    ASSERT_FALSE(labeling.isLabeledEdge(0));
    ASSERT_TRUE(labeling.isLabeledEdge(1));
    ASSERT_TRUE(labeling.isLabeledEdge(2));
    ASSERT_TRUE(labeling.isLabeledEdge(3));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(3)));

    labeling.setEdgeLabel(3, newLabel);

    ASSERT_TRUE(labeling.isLabeledEdge(1));
    ASSERT_TRUE(labeling.isLabeledEdge(2));
    ASSERT_TRUE(labeling.isLabeledEdge(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(3)));

    labeling.swapEdgeLabels(1, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(3)));

    labeling.swapEdgeLabels(1, 3);

    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(3)));

    labeling.swapEdgeLabels(3, 1);

    ASSERT_EQ(1, htd::accessLabel<int>(labeling.edgeLabel(1)));
    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(3)));

    htd::ILabel * exportedLabel = labeling.transferEdgeLabel(1);

    ASSERT_FALSE(labeling.isLabeledEdge(1));
    ASSERT_TRUE(labeling.isLabeledEdge(2));
    ASSERT_TRUE(labeling.isLabeledEdge(3));
    ASSERT_FALSE(labeling.isLabeledEdge(0));

    ASSERT_EQ(2, htd::accessLabel<int>(labeling.edgeLabel(2)));
    ASSERT_EQ(33, htd::accessLabel<int>(labeling.edgeLabel(3)));

    ASSERT_EQ(1, htd::accessLabel<int>(*exportedLabel));

    delete exportedLabel;

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)2, labeling.edgeLabelCount());

    labeling.removeEdgeLabel(2);
    labeling.removeEdgeLabel(2);

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labeling.edgeLabelCount());

    labeling.clear();

    ASSERT_EQ((std::size_t)0, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labeling.edgeLabelCount());
}

TEST(GraphLabelingTest, TestCloneMethod)
{
    htd::GraphLabeling labeling;

    labeling.setVertexLabel(123, new htd::Label<int>(123));
    labeling.setEdgeLabel(456, new htd::Label<int>(456));

    std::unique_ptr<htd::GraphLabeling> labeling2(labeling.clone());

    ASSERT_EQ((std::size_t)1, labeling.vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labeling.edgeLabelCount());

    ASSERT_EQ(123, htd::accessLabel<int>(labeling2->vertexLabel(123)));
    ASSERT_EQ(456, htd::accessLabel<int>(labeling2->edgeLabel(456)));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
