/*
 * File:   IHypergraphTest.cpp
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
        VertexCountTestInput(htd::IHypergraph * graph, std::size_t expectedResult) : graph_(graph), expectedResult_(expectedResult)
        {

        }

        ~VertexCountTestInput()
        {

        }

        htd::IHypergraph * graph() const
        {
            return graph_;
        }

        std::size_t expectedResult() const
        {
            return expectedResult_;
        }

    private:
        htd::IHypergraph * graph_;

        std::size_t expectedResult_;
};

class IHypergraphTest : public ::testing::TestWithParam<VertexCountTestInput>
{
    public:
        htd::IHypergraph * graph;

        IHypergraphTest(void) : graph(nullptr)
        {

        }

        ~IHypergraphTest()
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

TEST_P(IHypergraphTest, VertexCountTest)
{
    ASSERT_EQ((std::size_t)GetParam().expectedResult(), graph->vertexCount());
}

INSTANTIATE_TEST_CASE_P(VertexCountTest, IHypergraphTest, ::testing::Values(
    VertexCountTestInput(new htd::Graph(), 0),
    VertexCountTestInput(new htd::Hypergraph(), 0),
    VertexCountTestInput(new htd::DirectedGraph(), 0),
    VertexCountTestInput(new htd::TreeDecomposition(), 0),
    VertexCountTestInput(new htd::HypertreeDecomposition(), 0)
    /* TODO
    VertexCountTestInput(new htd::NamedHypergraph<std::string, std::string>(), 0)
    */
));

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
