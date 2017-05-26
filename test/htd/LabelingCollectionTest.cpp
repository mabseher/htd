/*
 * File:   LabelingCollectionTest.cpp
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

class LabelingCollectionTest : public ::testing::Test
{
    public:
        LabelingCollectionTest(void)
        {

        }

        virtual ~LabelingCollectionTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(LabelingCollectionTest, TestEmptyLabelingCollection)
{
    htd::LabelingCollection labelings;

    ASSERT_EQ((std::size_t)0, labelings.labelCount());

    ASSERT_EQ((std::size_t)0, labelings.labelNames().size());

    ASSERT_EQ(0, std::distance(labelings.begin(), labelings.end()));
}

TEST(LabelingCollectionTest, TestLabelingCollectionWithOneLabeling)
{
    htd::LabelingCollection labelings;

    ASSERT_FALSE(labelings.isLabelName("Label1"));

    labelings.setLabeling("Label1", new htd::GraphLabeling());

    ASSERT_EQ((std::size_t)1, labelings.labelCount());

    ASSERT_EQ((std::size_t)1, labelings.labelNames().size());

    ASSERT_EQ(1, std::distance(labelings.begin(), labelings.end()));

    ASSERT_EQ((std::size_t)0, labelings.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings.labeling("Label1").edgeLabelCount());

    ASSERT_EQ("Label1", labelings.labelNames()[0]);
    ASSERT_EQ("Label1", labelings.labelNameAtPosition(0));
    ASSERT_EQ("Label1", labelings.begin()->first);
    ASSERT_EQ((std::size_t)0, labelings.begin()->second->vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings.begin()->second->edgeLabelCount());

    ASSERT_TRUE(labelings.isLabelName("Label1"));

    const htd::ILabelingCollection & reference1 = labelings;

    htd::LabelingCollection labelings2(labelings);
    htd::LabelingCollection labelings3(reference1);

    ASSERT_EQ((std::size_t)0, reference1.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, reference1.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)0, reference1["Label1"].vertexLabelCount());
    ASSERT_EQ((std::size_t)0, reference1["Label1"].edgeLabelCount());

    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").edgeLabelCount());

    labelings2.labeling("Label1").setVertexLabel(1, new htd::Label<int>(123));
    labelings2.labeling("Label1").setEdgeLabel(3, new htd::Label<int>(456));

    ASSERT_EQ((std::size_t)1, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").edgeLabelCount());

    ASSERT_EQ(123, htd::accessLabel<int>(labelings2.labeling("Label1").vertexLabel(1)));
    ASSERT_EQ(456, htd::accessLabel<int>(labelings2.labeling("Label1").edgeLabel(3)));

    labelings2.setLabeling("Label1", new htd::GraphLabeling());

    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings3.labeling("Label1").edgeLabelCount());

    labelings3.removeLabeling("Label1");

    ASSERT_EQ((std::size_t)0, labelings3.labelCount());

    labelings2.labeling("Label1").setVertexLabel(1, new htd::Label<int>(123));
    labelings2.labeling("Label1").setEdgeLabel(3, new htd::Label<int>(456));

    labelings2.removeVertexLabels(htd::Vertex::UNKNOWN);
    labelings2.removeEdgeLabels(htd::Id::UNKNOWN);

    ASSERT_EQ((std::size_t)1, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)1, labelings2["Label1"].vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labelings2["Label1"].edgeLabelCount());

    labelings2.removeVertexLabels(1);

    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ((std::size_t)0, labelings2["Label1"].vertexLabelCount());
    ASSERT_EQ((std::size_t)1, labelings2["Label1"].edgeLabelCount());

    labelings2.removeEdgeLabels(3);

    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").vertexLabelCount());
    ASSERT_EQ((std::size_t)0, labelings2.labeling("Label1").edgeLabelCount());

    ASSERT_EQ("Label1", reference1.labelNames()[0]);
    ASSERT_EQ("Label1", reference1.labelNameAtPosition(0));
    ASSERT_EQ("Label1", reference1.begin()->first);
    ASSERT_EQ((std::size_t)0, reference1.begin()->second->vertexLabelCount());
    ASSERT_EQ((std::size_t)0, reference1.begin()->second->edgeLabelCount());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
