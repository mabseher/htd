/*
 * File:   LabelCollectionTest.cpp
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

class LabelCollectionTest : public ::testing::Test
{
    public:
        LabelCollectionTest(void)
        {

        }

        virtual ~LabelCollectionTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(LabelCollectionTest, TestEmptyLabelCollection)
{
    htd::LabelCollection labels;

    ASSERT_EQ((std::size_t)0, labels.labelCount());

    ASSERT_EQ((std::size_t)0, labels.labelNames().size());
}

TEST(LabelCollectionTest, TestLabelCollection)
{
    htd::LabelCollection labels;

    std::vector<htd::vertex_t> content { 1, 2, 3 };

    labels.setLabel("Label1", new htd::Label<int>(1));
    labels.setLabel("Label2", new htd::Label<std::vector<htd::vertex_t>>(content));

    ASSERT_EQ((std::size_t)2, labels.labelCount());
    ASSERT_EQ("Label1", labels.labelNames()[0]);
    ASSERT_EQ("Label1", labels.labelNameAtPosition(0));
    ASSERT_EQ("Label2", labels.labelNames()[1]);
    ASSERT_EQ("Label2", labels.labelNameAtPosition(1));

    ASSERT_EQ(1, htd::accessLabel<int>(labels.label("Label1")));
    ASSERT_TRUE(htd::accessLabel<std::vector<htd::vertex_t>>(labels.label("Label2")) == content);

    const htd::ILabelCollection & reference1 = labels;

    htd::LabelCollection labels2(labels);
    htd::LabelCollection labels3(reference1);

    ASSERT_EQ((std::size_t)2, labels2.labelCount());
    ASSERT_EQ("Label1", labels2.labelNames()[0]);
    ASSERT_EQ("Label1", labels2.labelNameAtPosition(0));
    ASSERT_EQ("Label2", labels2.labelNames()[1]);
    ASSERT_EQ("Label2", labels2.labelNameAtPosition(1));

    ASSERT_EQ(1, htd::accessLabel<int>(labels2.label("Label1")));
    ASSERT_TRUE(htd::accessLabel<std::vector<htd::vertex_t>>(labels2.label("Label2")) == content);

    ASSERT_EQ((std::size_t)2, labels3.labelCount());
    ASSERT_EQ("Label1", labels3.labelNames()[0]);
    ASSERT_EQ("Label1", labels3.labelNameAtPosition(0));
    ASSERT_EQ("Label2", labels3.labelNames()[1]);
    ASSERT_EQ("Label2", labels3.labelNameAtPosition(1));

    ASSERT_EQ(1, htd::accessLabel<int>(labels3.label("Label1")));
    ASSERT_TRUE(htd::accessLabel<std::vector<htd::vertex_t>>(labels3.label("Label2")) == content);

    labels2.setLabel("Label1", new htd::Label<int>(123));
    labels2.setLabel("Label2", new htd::Label<int>(456));

    ASSERT_EQ((std::size_t)2, labels2.labelCount());
    ASSERT_EQ("Label1", labels2.labelNames()[0]);
    ASSERT_EQ("Label1", labels2.labelNameAtPosition(0));
    ASSERT_EQ("Label2", labels2.labelNames()[1]);
    ASSERT_EQ("Label2", labels2.labelNameAtPosition(1));

    ASSERT_EQ(123, htd::accessLabel<int>(labels2.label("Label1")));
    ASSERT_EQ(456, htd::accessLabel<int>(labels2.label("Label2")));

    labels2.removeLabel("Label1");

    ASSERT_EQ((std::size_t)1, labels2.labelCount());
    ASSERT_EQ("Label2", labels2.labelNames()[0]);
    ASSERT_EQ("Label2", labels2.labelNameAtPosition(0));

    htd::LabelCollection * clonedLabelCollection = labels2.clone();

    ASSERT_EQ((std::size_t)1, clonedLabelCollection->labelCount());
    ASSERT_EQ("Label2", clonedLabelCollection->labelNames()[0]);
    ASSERT_EQ("Label2", clonedLabelCollection->labelNameAtPosition(0));

    ASSERT_EQ(456, htd::accessLabel<int>(clonedLabelCollection->label("Label2")));

    delete clonedLabelCollection;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
