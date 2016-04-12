/*
 * File:   LabelingCollectionTest.cpp
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

class LabelingCollectionTest : public ::testing::Test
{
    public:
        LabelingCollectionTest(void)
        {

        }

        ~LabelingCollectionTest()
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

    try
    {
        labelings.labelNameAtPosition(0);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }
}

TEST(LabelingCollectionTest, TestLabelingCollectionWithOneLabeling)
{
    htd::LabelingCollection labelings;

    ASSERT_FALSE(labelings.isLabelingName("Label1"));

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

    ASSERT_TRUE(labelings.isLabelingName("Label1"));

    try
    {
        labelings.labelNameAtPosition(1);

        FAIL();
    }
    catch (const std::out_of_range & error)
    {
        HTD_UNUSED(error);
    }
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
