/*
 * File:   GraphLabelingTest.cpp
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

class GraphLabelingTest : public ::testing::Test
{
    public:
        GraphLabelingTest(void)
        {

        }

        ~GraphLabelingTest()
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

    try
    {
        labeling.vertexLabel(0);

        FAIL();
    }
    catch (const std::logic_error & error)
    {
        HTD_UNUSED(error);
    }

    try
    {
        labeling.edgeLabel(0);

        FAIL();
    }
    catch (const std::logic_error & error)
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
