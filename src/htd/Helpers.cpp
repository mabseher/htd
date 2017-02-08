/* 
 * File:   Helpers.hpp
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

#ifndef HTD_HTD_HELPERS_CPP
#define HTD_HTD_HELPERS_CPP

#include <htd/Helpers.hpp>

htd::LibraryInstance * htd::createManagementInstance(htd::id_t id)
{
    htd::LibraryInstance * ret = new htd::LibraryInstance(id);

    ret->initializeFactoryClasses(ret);

    return ret;
}

void htd::print(bool input)
{
    print(input, std::cout);
}

void htd::print(bool input, std::ostream & stream)
{
    if (input)
    {
        stream << "true";
    }
    else
    {
        stream << "false";
    }
}

template < >
void htd::print<std::string>(const std::string & input)
{
    print(input, std::cout);
}

template < >
void htd::print<std::string>(const std::string & input, std::ostream & stream)
{
    stream << "\"" << input << "\"";
}

void htd::print(const htd::Hyperedge & input)
{
    print(input, std::cout);
}

void htd::print(const htd::Hyperedge & input, std::ostream & stream)
{
    stream << "Hyperedge " << input.id() << ": ";

    htd::print(input.elements(), std::cout, false);
}

void htd::set_union(const std::vector<htd::vertex_t> & set1,
                    const std::vector<htd::vertex_t> & set2,
                    htd::vertex_t ignoredVertex,
                    std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            if (*first1 != ignoredVertex)
            {
                result.push_back(*first1);
            }

            ++first1;
        }
        else if (*first2 < *first1)
        {
            if (*first2 != ignoredVertex)
            {
                result.push_back(*first2);
            }

            ++first2;
        }
        else
        {
            if (*first1 != ignoredVertex)
            {
                result.push_back(*first1);
            }

            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    if (first1 != last1)
    {
        if (*first1 <= ignoredVertex)
        {
            std::copy_if(first1, last1, std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            result.insert(result.end(), first1, last1);
        }
    }
    else if (first2 != last2)
    {
        if (*first2 <= ignoredVertex)
        {
            std::copy_if(first2, last2, std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            result.insert(result.end(), first2, last2);
        }
    }
}

void htd::set_difference(const std::vector<htd::vertex_t> & set1,
                         const std::vector<htd::vertex_t> & set2,
                         std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            result.push_back(*first1);

            ++first1;
        }
        else if (*first2 < *first1)
        {
            ++first2;
        }
        else
        {
            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    result.insert(result.end(), first1, last1);
}

void htd::set_intersection(const std::vector<htd::vertex_t> & set1,
                           const std::vector<htd::vertex_t> & set2,
                           std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            ++first1;
        }
        else if (*first2 < *first1)
        {
            ++first2;
        }
        else
        {
            result.push_back(*first1);

            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }
}

std::tuple<std::size_t, std::size_t, std::size_t> htd::analyze_sets(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    std::size_t onlySet1 = 0;
    std::size_t onlySet2 = 0;
    std::size_t overlap = 0;

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            onlySet1++;

            ++first1;
        }
        else if (*first2 < *first1)
        {
            onlySet2++;

            ++first2;
        }
        else
        {
            overlap++;

            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    onlySet1 += std::distance(first1, last1);
    onlySet2 += std::distance(first2, last2);

    return std::tuple<std::size_t, std::size_t, std::size_t>(onlySet1, overlap, onlySet2);
}

void htd::decompose_sets(const std::vector<htd::vertex_t> & set1,
                         const std::vector<htd::vertex_t> & set2,
                         std::vector<htd::vertex_t> & resultOnlySet1,
                         std::vector<htd::vertex_t> & resultOnlySet2,
                         std::vector<htd::vertex_t> & resultIntersection) HTD_NOEXCEPT
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            resultOnlySet1.push_back(*first1);

            ++first1;
        }
        else if (*first2 < *first1)
        {
            resultOnlySet2.push_back(*first2);

            ++first2;
        }
        else
        {
            resultIntersection.push_back(*first1);

            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    if (first1 != last1)
    {
        resultOnlySet1.insert(resultOnlySet1.end(), first1, last1);
    }
    else if (first2 != last2)
    {
        resultOnlySet2.insert(resultOnlySet2.end(), first2, last2);
    }
}

std::pair<std::size_t, std::size_t> htd::symmetric_difference_sizes(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    auto last1 = set1.end();
    auto last2 = set2.end();

    std::size_t onlySet1 = 0;
    std::size_t onlySet2 = 0;

    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2)
        {
            onlySet1++;

            ++first1;
        }
        else if (*first2 < *first1)
        {
            onlySet2++;

            ++first2;
        }
        else
        {
            ++first1;

            //Skip common value in set 2.
            ++first2;
        }
    }

    onlySet1 += std::distance(first1, last1);
    onlySet2 += std::distance(first2, last2);

    return std::pair<std::size_t, std::size_t>(onlySet1, onlySet2);
}

std::vector<htd::vertex_t> * htd::computeJoinVertices(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex)
{
    HTD_ASSERT(decomposition.isVertex(vertex))

    std::vector<htd::vertex_t> * ret = new std::vector<htd::vertex_t>();

    if (decomposition.childCount(vertex) >= 2)
    {
        std::unordered_set<htd::vertex_t> result;

        std::vector<htd::vertex_t> children;

        decomposition.copyChildrenTo(vertex, children);

        std::unordered_set<htd::vertex_t> visitedVertices;

        for (htd::index_t index = 0; index < children.size(); ++index)
        {
            for (htd::vertex_t bagElement : decomposition.bagContent(children[index]))
            {
                if (visitedVertices.count(bagElement) == 1)
                {
                    result.insert(bagElement);
                }
                else
                {
                    visitedVertices.insert(bagElement);
                }
            }
        }

        ret->insert(ret->end(), result.begin(), result.end());

        std::sort(ret->begin(), ret->end());
    }

    return ret;
}

#endif /* HTD_HTD_HELPERS_CPP */
