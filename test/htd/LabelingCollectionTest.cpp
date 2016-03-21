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
