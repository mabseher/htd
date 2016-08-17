/* 
 * File:   Helpers.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015-2016, Michael Abseher
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
#define	HTD_HTD_HELPERS_CPP

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

void htd::merge(const std::vector<htd::vertex_t> & set1,
                const std::vector<htd::vertex_t> & set2,
                htd::vertex_t ignoredVertex,
                std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t remainder1 = set1.size();
    std::size_t remainder2 = set2.size();

    while (remainder1 > 0 && remainder2 > 0)
    {
        htd::vertex_t value1 = *first1;
        htd::vertex_t value2 = *first2;

        if (value1 < value2)
        {
            if (value1 != ignoredVertex)
            {
                result.push_back(value1);
            }

            remainder1--;
            ++first1;
        }
        else
        {
            if (value2 != ignoredVertex)
            {
                result.push_back(value2);
            }

            remainder2--;
            ++first2;
        }
    }

    if (remainder1 > 0)
    {
        if (*first1 <= ignoredVertex)
        {
            std::copy_if(first1, set1.end(), std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first1, set1.end(), std::back_inserter(result));
        }
    }
    else if (remainder2 > 0)
    {
        if (*first2 <= ignoredVertex)
        {
            std::copy_if(first2, set2.end(), std::back_inserter(result), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first2, set2.end(), std::back_inserter(result));
        }
    }
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
            std::copy(first1, last1, std::back_inserter(result));
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
            std::copy(first2, last2, std::back_inserter(result));
        }
    }
}

void htd::set_difference(const std::vector<htd::vertex_t> & set1,
                         const std::vector<htd::vertex_t> & set2,
                         std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t remainder1 = set1.size();
    std::size_t remainder2 = set2.size();

    while (remainder1 > 0 && remainder2 > 0)
    {
        htd::vertex_t value1 = *first1;
        htd::vertex_t value2 = *first2;

        if (value1 < value2)
        {
            result.push_back(value1);

            --remainder1;
            ++first1;
        }
        else if (value2 < value1)
        {
            --remainder2;
            ++first2;
        }
        else
        {
            --remainder1;
            ++first1;

            //Skip common value in set 2.
            --remainder2;
            ++first2;
        }
    }

    if (remainder1 > 0)
    {
        std::copy(first1, set1.end(), std::back_inserter(result));
    }
}

void htd::set_intersection(const std::vector<htd::vertex_t> & set1,
                           const std::vector<htd::vertex_t> & set2,
                           std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t remainder1 = set1.size();
    std::size_t remainder2 = set2.size();

    while (remainder1 > 0 && remainder2 > 0)
    {
        htd::vertex_t value1 = *first1;
        htd::vertex_t value2 = *first2;

        if (value1 < value2)
        {
            --remainder1;
            ++first1;
        }
        else if (value2 < value1)
        {
            --remainder2;
            ++first2;
        }
        else
        {
            result.push_back(value1);

            --remainder1;
            ++first1;

            //Skip common value in set 2.
            --remainder2;
            ++first2;
        }
    }
}

std::tuple<std::size_t, std::size_t, std::size_t> htd::analyze_sets(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t remainder1 = set1.size();
    std::size_t remainder2 = set2.size();

    std::size_t onlySet1 = 0;
    std::size_t onlySet2 = 0;
    std::size_t overlap = 0;

    while (remainder1 > 0 && remainder2 > 0)
    {
        htd::vertex_t value1 = *first1;
        htd::vertex_t value2 = *first2;

        if (value1 < value2)
        {
            onlySet1++;

            --remainder1;
            ++first1;
        }
        else if (value2 < value1)
        {
            onlySet2++;

            --remainder2;
            ++first2;
        }
        else
        {
            overlap++;

            --remainder1;
            ++first1;

            //Skip common value in set 2.
            --remainder2;
            ++first2;
        }
    }

    onlySet1 += remainder1;
    onlySet2 += remainder2;

    return std::tuple<std::size_t, std::size_t, std::size_t>(onlySet1, overlap, onlySet2);
}

void htd::decompose_sets(const std::vector<htd::vertex_t> & set1,
                         const std::vector<htd::vertex_t> & set2,
                         htd::vertex_t ignoredVertex,
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
            if (*first1 != ignoredVertex)
            {
                resultOnlySet1.push_back(*first1);
            }

            ++first1;
        }
        else if (*first2 < *first1)
        {
            if (*first2 != ignoredVertex)
            {
                resultOnlySet2.push_back(*first2);
            }

            ++first2;
        }
        else
        {
            if (*first1 != ignoredVertex)
            {
                resultIntersection.push_back(*first1);
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
            std::copy_if(first1, last1, std::back_inserter(resultOnlySet1), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first1, last1, std::back_inserter(resultOnlySet1));
        }
    }
    else if (first2 != last2)
    {
        if (*first2 <= ignoredVertex)
        {
            std::copy_if(first2, last2, std::back_inserter(resultOnlySet2), [&](const htd::vertex_t vertex) { return vertex != ignoredVertex; });
        }
        else
        {
            std::copy(first2, last2, std::back_inserter(resultOnlySet2));
        }
    }
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
        std::copy(first1, last1, std::back_inserter(resultOnlySet1));
    }
    else if (first2 != last2)
    {
        std::copy(first2, last2, std::back_inserter(resultOnlySet2));
    }
}

std::pair<std::size_t, std::size_t> htd::symmetric_difference_sizes(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t remainder1 = set1.size();
    std::size_t remainder2 = set2.size();

    std::size_t onlySet1 = 0;
    std::size_t onlySet2 = 0;

    while (remainder1 > 0 && remainder2 > 0)
    {
        htd::vertex_t value1 = *first1;
        htd::vertex_t value2 = *first2;

        if (value1 < value2)
        {
            onlySet1++;

            --remainder1;
            ++first1;
        }
        else if (value2 < value1)
        {
            onlySet2++;

            --remainder2;
            ++first2;
        }
        else
        {
            --remainder1;
            ++first1;

            //Skip common value in set 2.
            --remainder2;
            ++first2;
        }
    }

    onlySet1 += remainder1;
    onlySet2 += remainder2;

    return std::pair<std::size_t, std::size_t>(onlySet1, onlySet2);
}

#endif /* HTD_HTD_HELPERS_CPP */
