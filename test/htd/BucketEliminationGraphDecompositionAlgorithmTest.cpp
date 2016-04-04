/*
 * File:   BucketEliminationGraphDecompositionAlgorithmTest.cpp
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

class BucketEliminationGraphDecompositionAlgorithmTest : public ::testing::Test
{
    public:
        BucketEliminationGraphDecompositionAlgorithmTest(void)
        {

        }

        ~BucketEliminationGraphDecompositionAlgorithmTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultEmptyGraph)
{
    htd::MultiHypergraph graph;

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_EQ(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), (std::size_t)0);

    const std::vector<htd::vertex_t> & bag = decomposition->bagContent(1);

    EXPECT_EQ(bag.size(), (std::size_t)0);

    delete decomposition;
}

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultDisconnectedGraph)
{
    htd::MultiHypergraph graph;

    graph.addVertex();
    graph.addVertex();
    graph.addVertex();

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_LE(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    delete decomposition;
}

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleGraph)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    delete decomposition;
}

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleHypergraph1)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(std::vector<htd::vertex_t> { vertex1 });

    HTD_UNUSED(vertex2);
    HTD_UNUSED(vertex3);

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)3);

    EXPECT_EQ((std::size_t)0, decomposition->edgeCount());

    ASSERT_EQ((std::size_t)1, decomposition->minimumBagSize());
    ASSERT_EQ((std::size_t)1, decomposition->maximumBagSize());

    delete decomposition;
}

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleHypergraph2)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(std::vector<htd::vertex_t> { vertex3, vertex3, vertex2, vertex1, vertex2, vertex3, vertex3 });

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph);

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ((std::size_t)0, decomposition->edgeCount());

    ASSERT_EQ((std::size_t)3, decomposition->minimumBagSize());
    ASSERT_EQ((std::size_t)3, decomposition->maximumBagSize());

    delete decomposition;
}

class BagSizeLabelingFunction : public htd::ILabelingFunction
{
    public:
        BagSizeLabelingFunction(void)
        {

        }

        ~BagSizeLabelingFunction()
        {

        }

        std::string name() const HTD_OVERRIDE
        {
            return "BAG_SIZE";
        }

        htd::ILabel * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels);

            return new htd::Label<std::size_t>(vertices.size());
        }

        htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels);

            return new htd::Label<std::size_t>(vertices.size());
        }

        ILabelingFunction * clone(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction();
        }
};

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleGraphWithLabelingFunction)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    /* False positive of coverity caused by variadic function. */
    // coverity[leaked_storage]
    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph, 1, new BagSizeLabelingFunction());

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
    }

    delete decomposition;
}

class BagSizeLabelingFunction2 : public htd::ILabelingFunction
{
    public:
        BagSizeLabelingFunction2(void)
        {

        }

        ~BagSizeLabelingFunction2()
        {

        }

        std::string name() const HTD_OVERRIDE
        {
            return "BAG_SIZE_TIMES_2";
        }

        htd::ILabel * computeLabel(const std::vector<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels);

            return new htd::Label<std::size_t>(vertices.size() + htd::accessLabel<std::size_t>(labels.label("BAG_SIZE")));
        }

        htd::ILabel * computeLabel(const htd::ConstCollection<htd::vertex_t> & vertices, const htd::ILabelCollection & labels) const HTD_OVERRIDE
        {
            HTD_UNUSED(labels);

            return new htd::Label<std::size_t>(vertices.size() + htd::accessLabel<std::size_t>(labels.label("BAG_SIZE")));
        }

        ILabelingFunction * clone(void) const HTD_OVERRIDE
        {
            return new BagSizeLabelingFunction();
        }
};

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleGraphWithLabelingFunctionVector)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm;

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction(), new BagSizeLabelingFunction2() });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
}

TEST(BucketEliminationGraphDecompositionAlgorithmTest, CheckResultSimpleGraphWithLabelingFunctionVectorAndManipulationOperation)
{
    htd::MultiHypergraph graph;

    htd::vertex_t vertex1 = graph.addVertex();
    htd::vertex_t vertex2 = graph.addVertex();
    htd::vertex_t vertex3 = graph.addVertex();

    graph.addEdge(vertex1, vertex2);
    graph.addEdge(vertex2, vertex3);

    htd::BucketEliminationGraphDecompositionAlgorithm algorithm({ new BagSizeLabelingFunction(), new htd::JoinNodeReplacementOperation() });

    htd::IGraphDecomposition * decomposition = algorithm.computeDecomposition(graph, { new BagSizeLabelingFunction2() });

    ASSERT_NE(decomposition, nullptr);

    ASSERT_GE(decomposition->vertexCount(), (std::size_t)1);

    EXPECT_EQ(decomposition->edgeCount(), decomposition->vertexCount() - 1);

    ASSERT_LE(decomposition->minimumBagSize(), decomposition->maximumBagSize());

    for (htd::vertex_t vertex : decomposition->vertices())
    {
        ASSERT_EQ(decomposition->bagSize(vertex), htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE", vertex)));
        ASSERT_EQ(decomposition->bagSize(vertex) * 2, htd::accessLabel<std::size_t>(decomposition->vertexLabel("BAG_SIZE_TIMES_2", vertex)));
    }

    delete decomposition;
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
