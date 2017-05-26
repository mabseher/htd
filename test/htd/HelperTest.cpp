/*
 * File:   HelperTest.cpp
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

class HelperTest : public ::testing::Test
{
    public:
        HelperTest(void)
        {

        }

        virtual ~HelperTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(HelperTest, CheckAssemblyInfo)
{
    std::string version = htd_version();

    ASSERT_NE("", version);
}

TEST(HelperTest, CheckPrintBoolToStdout1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    htd::print(true);

    ASSERT_EQ("true", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintBoolToStdout2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    htd::print(false);

    ASSERT_EQ("false", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintStringToStdout)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    htd::print(std::string("abc123!!!"));

    ASSERT_EQ("\"abc123!!!\"", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<int> inputSet { 1, 5, 3 };

    htd::print(inputSet);

    ASSERT_EQ("[ 1, 5, 3 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<int> inputSet { 1, 5, 3 };

    htd::print(inputSet, false);

    ASSERT_EQ("[ 1, 5, 3 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout3)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<int> inputSet { };

    htd::print(inputSet, false);

    ASSERT_EQ("<EMPTY>", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout4)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<std::string> inputSet { "a", "e", "c" };

    htd::print(inputSet);

    ASSERT_EQ("[ \"a\", \"e\", \"c\" ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout5)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<std::string> inputSet { "a", "e", "c" };

    htd::print(inputSet, false);

    ASSERT_EQ("[ \"a\", \"e\", \"c\" ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdout6)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<std::string> inputSet { };

    htd::print(inputSet, false);

    ASSERT_EQ("<EMPTY>", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdoutSorted1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<int> inputSet { 1, 5, 3 };

    htd::print(inputSet, true);

    ASSERT_EQ("[ 1, 3, 5 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdoutSorted2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<int> inputSet {  };

    htd::print(inputSet, true);

    ASSERT_EQ("<EMPTY>", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintVectorToStdoutSorted3)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::vector<std::string> inputSet { "a", "e", "c" };

    htd::print(inputSet, true);

    ASSERT_EQ("[ \"a\", \"c\", \"e\" ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintSetToStdout1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::set<int> inputSet { 1, 3, 5 };

    htd::print(inputSet);

    ASSERT_EQ("[ 1, 3, 5 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintSetToStdout2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::set<int> inputSet { };

    htd::print(inputSet);

    ASSERT_EQ("<EMPTY>", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintSetToStdout3)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::set<std::string> inputSet { "a", "c", "e" };

    htd::print(inputSet);

    ASSERT_EQ("[ \"a\", \"c\", \"e\" ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintUnorderedSetToStdout1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::unordered_set<int> inputSet { 1, 5, 3 };

    htd::print(inputSet);

    std::string output = testing::internal::GetCapturedStdout();

    if (output != "[ 1, 3, 5 ]" && output != "[ 1, 5, 3 ]" &&
        output != "[ 3, 1, 5 ]" && output != "[ 3, 5, 1 ]" &&
        output != "[ 5, 1, 3 ]" && output != "[ 5, 3, 1 ]")
    {
        std::cout << "UNEXPECTED RESULT: \"" << output << "\"" << std::endl;

        FAIL();
    }

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintUnorderedSetToStdout2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::unordered_set<int> inputSet { };

    htd::print(inputSet);

    ASSERT_EQ("<EMPTY>", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintUnorderedSetToStdout3)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::unordered_set<std::string> inputSet { "a", "e", "c" };

    htd::print(inputSet);

    std::string output = testing::internal::GetCapturedStdout();

    if (output != "[ \"a\", \"c\", \"e\" ]" && output != "[ \"a\", \"e\", \"c\" ]" &&
        output != "[ \"c\", \"a\", \"e\" ]" && output != "[ \"c\", \"e\", \"a\" ]" &&
        output != "[ \"e\", \"a\", \"c\" ]" && output != "[ \"e\", \"c\", \"a\" ]")
    {
        std::cout << "UNEXPECTED RESULT: \"" << output << "\"" << std::endl;

        FAIL();
    }

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintUnorderedSetToStdoutSorted1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::unordered_set<int> inputSet { 1, 5, 3 };

    htd::print(inputSet, true);

    ASSERT_EQ("[ 1, 3, 5 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintUnorderedSetToStdoutSorted2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    std::unordered_set<std::string> inputSet { "a", "e", "c" };

    htd::print(inputSet, true);

    ASSERT_EQ("[ \"a\", \"c\", \"e\" ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintHyperedgeToStdout1)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    htd::print(htd::Hyperedge(1, { 1, 5, 3, 5, 3 }));

    ASSERT_EQ("Hyperedge 1: [ 1, 5, 3, 5, 3 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckPrintHyperedgeToStdout2)
{
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();

    htd::print(htd::Hyperedge(3, { 1, 5, 3, 5, 3 }));

    ASSERT_EQ("Hyperedge 3: [ 1, 5, 3, 5, 3 ]", testing::internal::GetCapturedStdout());

    ASSERT_EQ("", testing::internal::GetCapturedStderr());
}

TEST(HelperTest, CheckSetUnion1)
{
    std::vector<int> input1 { 1, 3, 5 };
    std::vector<int> input2 { 0, 2, 4, 6 };

    std::vector<int> actualResult;

    std::vector<int> expectedResult { 0, 1, 2, 3, 4, 5, 6 };

    htd::set_union(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion2)
{
    std::vector<int> input1 { 0, 2, 4, 6 };
    std::vector<int> input2 { 1, 3, 5 };

    std::vector<int> actualResult;

    std::vector<int> expectedResult { 0, 1, 2, 3, 4, 5, 6 };

    htd::set_union(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion3)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 2, 4, 5, 6 };

    htd::set_union(input1, input2, 3, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion4)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 2, 3, 4, 5, 6 };

    htd::set_union(input1, input2, 0, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion5)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 2, 3, 4, 5, 6 };

    htd::set_union(input1, input2, 7, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion6)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 5 };

    htd::set_union(input1, input2, 3, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetUnion7)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 3 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 3, 5 };

    htd::set_union(input1, input2, 0, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetDifference1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 0, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1, 3, 5 };

    htd::set_difference(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetDifference2)
{
    std::vector<htd::vertex_t> input1 { 0, 2, 4, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 0, 2, 4, 6 };

    htd::set_difference(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetDifference5)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 3, 5 };

    htd::set_difference(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetIntersection1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 0, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { };

    htd::set_intersection(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetIntersection2)
{
    std::vector<htd::vertex_t> input1 { 0, 2, 4, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { };

    htd::set_intersection(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetIntersection3)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    std::vector<htd::vertex_t> actualResult;

    std::vector<htd::vertex_t> expectedResult { 1 };

    htd::set_intersection(input1, input2, actualResult);

    ASSERT_TRUE(actualResult == expectedResult);
}

TEST(HelperTest, CheckSetDifferenceSize1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_EQ((std::size_t)1, htd::set_difference_size(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckSetDifferenceSize2)
{
    std::vector<htd::vertex_t> input1 { 1, 2, 4, 5, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    ASSERT_EQ((std::size_t)3, htd::set_difference_size(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckSetIntersectionSize1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_EQ((std::size_t)2, htd::set_intersection_size(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckSetIntersectionSize2)
{
    std::vector<htd::vertex_t> input1 { 1, 2, 4, 5, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    ASSERT_EQ((std::size_t)2, htd::set_intersection_size(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetDifferenceSize1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_TRUE(htd::has_non_empty_set_difference(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetDifferenceSize2)
{
    std::vector<htd::vertex_t> input1 { 1, 2, 4, 5, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    ASSERT_TRUE(htd::has_non_empty_set_difference(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetDifferenceSize3)
{
    std::vector<htd::vertex_t> input1 { 1, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_FALSE(htd::has_non_empty_set_difference(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetIntersectionSize1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_TRUE(htd::has_non_empty_set_intersection(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetIntersectionSize2)
{
    std::vector<htd::vertex_t> input1 { 1, 2, 4, 5, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    ASSERT_TRUE(htd::has_non_empty_set_intersection(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetIntersectionSize3)
{
    std::vector<htd::vertex_t> input1 { 0, 3 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 5, 6 };

    ASSERT_FALSE(htd::has_non_empty_set_intersection(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckHasNonEmptySetIntersectionSize4)
{
    std::vector<htd::vertex_t> input1 { 1, 2, 4, 5, 6 };
    std::vector<htd::vertex_t> input2 { 0, 3 };

    ASSERT_FALSE(htd::has_non_empty_set_intersection(input1.begin(), input1.end(), input2.begin(), input2.end()));
}

TEST(HelperTest, CheckAnalyzeSets1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 0, 2, 4, 6 };

    const std::tuple<std::size_t, std::size_t, std::size_t> & result = htd::analyze_sets(input1, input2);

    ASSERT_EQ((std::size_t)3, std::get<0>(result));
    ASSERT_EQ((std::size_t)0, std::get<1>(result));
    ASSERT_EQ((std::size_t)4, std::get<2>(result));
}

TEST(HelperTest, CheckAnalyzeSets2)
{
    std::vector<htd::vertex_t> input1 { 0, 2, 4, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    const std::tuple<std::size_t, std::size_t, std::size_t> & result = htd::analyze_sets(input1, input2);

    ASSERT_EQ((std::size_t)4, std::get<0>(result));
    ASSERT_EQ((std::size_t)0, std::get<1>(result));
    ASSERT_EQ((std::size_t)3, std::get<2>(result));
}

TEST(HelperTest, CheckAnalyzeSets3)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    const std::tuple<std::size_t, std::size_t, std::size_t> & result = htd::analyze_sets(input1, input2);

    ASSERT_EQ((std::size_t)2, std::get<0>(result));
    ASSERT_EQ((std::size_t)1, std::get<1>(result));
    ASSERT_EQ((std::size_t)3, std::get<2>(result));
}

TEST(HelperTest, CheckSymmetricDifferenceSizes1)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 0, 2, 4, 6 };

    const std::pair<std::size_t, std::size_t> & result = htd::symmetric_difference_sizes(input1, input2);

    ASSERT_EQ((std::size_t)3, result.first);
    ASSERT_EQ((std::size_t)4, result.second);
}

TEST(HelperTest, CheckSymmetricDifferenceSizes2)
{
    std::vector<htd::vertex_t> input1 { 0, 2, 4, 6 };
    std::vector<htd::vertex_t> input2 { 1, 3, 5 };

    const std::pair<std::size_t, std::size_t> & result = htd::symmetric_difference_sizes(input1, input2);

    ASSERT_EQ((std::size_t)4, result.first);
    ASSERT_EQ((std::size_t)3, result.second);
}

TEST(HelperTest, CheckSymmetricDifferenceSizes3)
{
    std::vector<htd::vertex_t> input1 { 1, 3, 5 };
    std::vector<htd::vertex_t> input2 { 1, 2, 4, 6 };

    const std::pair<std::size_t, std::size_t> & result = htd::symmetric_difference_sizes(input1, input2);

    ASSERT_EQ((std::size_t)2, result.first);
    ASSERT_EQ((std::size_t)3, result.second);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
