/*
 * File:   IMutableHypergraphTest.cpp
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

class VertexCountTestInput
{
    public:
        VertexCountTestInput(htd::IMutableHypergraph * graph, std::size_t expectedResult) : graph_(graph), expectedResult_(expectedResult)
        {

        }

        ~VertexCountTestInput()
        {

        }

        htd::IMutableHypergraph * graph() const
        {
            return graph_;
        }

        std::size_t expectedResult() const
        {
            return expectedResult_;
        }

    private:
        htd::IMutableHypergraph * graph_;

        std::size_t expectedResult_;
};

class IMutableHypergraphTest : public ::testing::TestWithParam<VertexCountTestInput>
{
    public:
        htd::IMutableHypergraph * graph;

        IMutableHypergraphTest(void) : graph(nullptr)
        {

        }

        ~IMutableHypergraphTest()
        {

        }

        void SetUp()
        {
            graph = ::testing::TestWithParam<VertexCountTestInput>::GetParam().graph()->clone();
        }

        void TearDown()
        {
            delete graph;

            graph = nullptr;
        }
};

TEST_P(IMutableHypergraphTest, VertexCountTest)
{
    ASSERT_EQ((std::size_t)GetParam().expectedResult(), graph->vertexCount());
}

TEST_P(IMutableHypergraphTest, ManipulationTest)
{
    ASSERT_EQ((std::size_t)GetParam().expectedResult(), graph->vertexCount());

    htd::vertex_t vertex1 = graph->addVertex();
    htd::vertex_t vertex2 = graph->addVertex();

    ASSERT_EQ((std::size_t)GetParam().expectedResult() + 2, graph->vertexCount());

    graph->addEdge(vertex1, vertex2);

    ASSERT_EQ((std::size_t)1, graph->edgeCount());
}

INSTANTIATE_TEST_CASE_P(VertexCountTest, IMutableHypergraphTest, ::testing::Values(
    VertexCountTestInput(new htd::Hypergraph(), 0),
    VertexCountTestInput(new htd::Hypergraph(5), 5)
    /* TODO
    VertexCountTestInput(new htd::LabeledHypergraph<std::string, std::string>(), 0),
    VertexCountTestInput(new htd::LabeledHypergraph<std::string, std::string>(5), 5)
    */
));

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
