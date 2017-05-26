/*
 * File:   SetCoverAlgorithmTest.cpp
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

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <random>
#include <unordered_set>
#include <vector>

class SetCoverAlgorithmTest : public ::testing::Test
{
    public:
        SetCoverAlgorithmTest(void)
        {

        }

        virtual ~SetCoverAlgorithmTest()
        {

        }

        void SetUp()
        {

        }

        void TearDown()
        {

        }
};

std::vector<htd::id_t> * createContainer(htd::id_t minValue,
                                         htd::id_t maxValue,
                                         std::size_t minContainerSize,
                                         std::size_t maxContainerSize)
{
    std::size_t containerSize = minContainerSize + std::rand() % (maxContainerSize - minContainerSize);

    std::vector<htd::id_t> * ret = new std::vector<htd::id_t>();

    std::mt19937 g(static_cast<std::mt19937::result_type>(std::rand()));

    std::vector<htd::id_t> values(maxValue - minValue + 1);

    std::iota(values.begin(), values.end(), minValue);

    std::shuffle(values.begin(), values.end(), g);

    std::copy(values.begin(), values.begin() + containerSize, std::back_inserter(*ret));

    std::sort(ret->begin(), ret->end());

    return ret;
}

std::vector<std::vector<htd::id_t>> * createContainers(htd::id_t minValue,
                                                       htd::id_t maxValue,
                                                       std::size_t containerCount,
                                                       std::size_t minContainerSize,
                                                       std::size_t maxContainerSize)
{
    std::vector<std::vector<htd::id_t>> * ret = new std::vector<std::vector<htd::id_t>>(containerCount);

    for (htd::index_t index = 0; index < containerCount; ++index)
    {
        std::vector<htd::id_t> * newContainer = createContainer(minValue, maxValue, minContainerSize, maxContainerSize);

        ret->at(index) = std::move(*newContainer);

        delete newContainer;
    }

    return ret;
}

std::vector<htd::id_t> * set_union(const std::vector<std::vector<htd::id_t>> & containers)
{
    std::unordered_set<htd::id_t> tmp;

    for (const std::vector<htd::id_t> & container : containers)
    {
        tmp.insert(container.begin(), container.end());
    }

    std::vector<htd::id_t> * ret = new std::vector<htd::id_t>();

    ret->insert(ret->end(), tmp.begin(), tmp.end());

    std::sort(ret->begin(), ret->end());

    return ret;
}

std::vector<htd::id_t> * set_union(const std::vector<std::vector<htd::id_t>> & containers, const std::vector<htd::index_t> & selectedPositions)
{
    std::unordered_set<htd::id_t> tmp;

    for (htd::index_t index : selectedPositions)
    {
        tmp.insert(containers[index].begin(), containers[index].end());
    }

    std::vector<htd::id_t> * ret = new std::vector<htd::id_t>();

    ret->insert(ret->end(), tmp.begin(), tmp.end());

    std::sort(ret->begin(), ret->end());

    return ret;
}

bool isValidSetCover(const std::vector<htd::id_t> & values,
                     const std::vector<std::vector<htd::id_t>> & containers,
                     const std::vector<htd::index_t> & coveringContainers)
{
    std::vector<htd::vertex_t> * combinedValues = set_union(containers);

    bool ret = std::includes(combinedValues->begin(), combinedValues->end(), values.begin(), values.end());

    delete combinedValues;

    if (ret)
    {
        combinedValues = set_union(containers, coveringContainers);

        ret = std::includes(combinedValues->begin(), combinedValues->end(), values.begin(), values.end());

        delete combinedValues;
    }
    else
    {
        ret = coveringContainers.empty();
    }

    if (!ret)
    {
        std::cout << std::endl;
    }

    return ret;
}

TEST(SetCoverAlgorithmTest, CheckSetCoverAlgorithm1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::SetCoverAlgorithm algorithm(libraryInstance);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance);

    algorithm.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance2);

    htd::ISetCoverAlgorithm * clonedAlgorithm = algorithm.clone();

    ASSERT_TRUE(clonedAlgorithm->managementInstance() == libraryInstance2);

    delete clonedAlgorithm;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(SetCoverAlgorithmTest, CheckSetCoverAlgorithm2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::SetCoverAlgorithm algorithm(libraryInstance);

    for (int i = 0; i < 10; ++i)
    {
        std::vector<htd::id_t> * values = createContainer(1, 50, 0, 25);

        std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

        std::vector<htd::index_t> result;

        algorithm.computeSetCover(*values, *containers, result);

        ASSERT_TRUE(isValidSetCover(*values, *containers, result));

        delete containers;
        delete values;
    }

    delete libraryInstance;
}

TEST(SetCoverAlgorithmTest, CheckSetCoverAlgorithm3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::SetCoverAlgorithm algorithm(libraryInstance);

    for (int i = 0; i < 10; ++i)
    {
        std::vector<htd::id_t> * values = createContainer(1, 50, 0, 25);

        std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

        std::vector<htd::index_t> result;

        algorithm.computeSetCover(htd::ConstCollection<htd::id_t>::getInstance(*values),
                                  htd::ConstCollection<std::vector<htd::id_t>>::getInstance(*containers), result);

        ASSERT_TRUE(isValidSetCover(*values, *containers, result));

        delete containers;
        delete values;
    }

    delete libraryInstance;
}

TEST(SetCoverAlgorithmTest, CheckSetCoverAlgorithm4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::SetCoverAlgorithm algorithm(libraryInstance);

    std::vector<htd::id_t> * values = createContainer(101, 150, 0, 25);

    std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

    std::vector<htd::index_t> result;

    algorithm.computeSetCover(*values, *containers, result);

    ASSERT_TRUE(isValidSetCover(*values, *containers, result));

    delete libraryInstance;
    delete containers;
    delete values;
}

TEST(SetCoverAlgorithmTest, CheckSetCoverAlgorithm5)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::SetCoverAlgorithm algorithm(libraryInstance);

    std::vector<htd::id_t> * values = createContainer(101, 150, 0, 25);

    std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

    std::vector<htd::index_t> result;

    algorithm.computeSetCover(htd::ConstCollection<htd::id_t>::getInstance(*values),
                              htd::ConstCollection<std::vector<htd::id_t>>::getInstance(*containers), result);

    ASSERT_TRUE(isValidSetCover(*values, *containers, result));

    delete libraryInstance;
    delete containers;
    delete values;
}

TEST(SetCoverAlgorithmTest, CheckGreedySetCoverAlgorithm1)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::GreedySetCoverAlgorithm algorithm(libraryInstance);

    htd::LibraryInstance * libraryInstance2 = htd::createManagementInstance(2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance);

    algorithm.setManagementInstance(libraryInstance2);

    ASSERT_TRUE(algorithm.managementInstance() == libraryInstance2);

    htd::ISetCoverAlgorithm * clonedAlgorithm = algorithm.clone();

    ASSERT_TRUE(clonedAlgorithm->managementInstance() == libraryInstance2);

    delete clonedAlgorithm;
    delete libraryInstance;
    delete libraryInstance2;
}

TEST(SetCoverAlgorithmTest, CheckGreedySetCoverAlgorithm2)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::GreedySetCoverAlgorithm algorithm(libraryInstance);

    for (int i = 0; i < 10; ++i)
    {
        std::vector<htd::id_t> * values = createContainer(1, 50, 0, 25);

        std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

        std::vector<htd::index_t> result;

        algorithm.computeSetCover(*values, *containers, result);

        ASSERT_TRUE(isValidSetCover(*values, *containers, result));

        delete containers;
        delete values;
    }

    delete libraryInstance;
}

TEST(SetCoverAlgorithmTest, CheckGreedySetCoverAlgorithm3)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::GreedySetCoverAlgorithm algorithm(libraryInstance);

    for (int i = 0; i < 10; ++i)
    {
        std::vector<htd::id_t> * values = createContainer(1, 50, 0, 25);

        std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

        std::vector<htd::index_t> result;

        algorithm.computeSetCover(htd::ConstCollection<htd::id_t>::getInstance(*values),
                                  htd::ConstCollection<std::vector<htd::id_t>>::getInstance(*containers), result);

        ASSERT_TRUE(isValidSetCover(*values, *containers, result));

        delete containers;
        delete values;
    }

    delete libraryInstance;
}

TEST(SetCoverAlgorithmTest, CheckGreedySetCoverAlgorithm4)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::GreedySetCoverAlgorithm algorithm(libraryInstance);

    std::vector<htd::id_t> * values = createContainer(101, 150, 0, 25);

    std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

    std::vector<htd::index_t> result;

    algorithm.computeSetCover(*values, *containers, result);

    ASSERT_TRUE(isValidSetCover(*values, *containers, result));

    delete libraryInstance;
    delete containers;
    delete values;
}

TEST(SetCoverAlgorithmTest, CheckGreedySetCoverAlgorithm5)
{
    htd::LibraryInstance * libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

    htd::GreedySetCoverAlgorithm algorithm(libraryInstance);

    std::vector<htd::id_t> * values = createContainer(101, 150, 0, 25);

    std::vector<std::vector<htd::id_t>> * containers = createContainers(1, 50, 25, 1, 8);

    std::vector<htd::index_t> result;

    algorithm.computeSetCover(htd::ConstCollection<htd::id_t>::getInstance(*values),
                              htd::ConstCollection<std::vector<htd::id_t>>::getInstance(*containers), result);

    ASSERT_TRUE(isValidSetCover(*values, *containers, result));

    delete libraryInstance;
    delete containers;
    delete values;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
