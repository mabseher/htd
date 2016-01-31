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

    htd::print(input.elements());
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

    std::size_t count1 = set1.size();
    std::size_t count2 = set2.size();

    htd::index_t index1 = 0;
    htd::index_t index2 = 0;

    while (index1 < count1 && index2 < count2)
    {
        auto value1 = *first1;
        auto value2 = *first2;

        if (value1 < value2)
        {
            if (value1 != ignoredVertex)
            {
                result.push_back(value1);
            }

            index1++;
            ++first1;
        }
        else if (value2 < value1)
        {
            if (value2 != ignoredVertex)
            {
                result.push_back(value2);
            }

            index2++;
            ++first2;
        }
        else
        {
            if (value1 != ignoredVertex)
            {
                result.push_back(value1);
            }

            index1++;
            ++first1;

            //Skip common value in set 2.
            index2++;
            ++first2;
        }
    }

    if (index1 < count1)
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
    else if (index2 < count2)
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
    auto last1 = set1.end();

    std::size_t count1 = set1.size();
    std::size_t count2 = set2.size();

    htd::index_t index1 = 0;
    htd::index_t index2 = 0;

    while (index1 < count1 && index2 < count2)
    {
        auto value1 = *first1;
        auto value2 = *first2;

        if (value1 < value2)
        {
            result.push_back(value1);

            index1++;
            ++first1;
        }
        else if (value2 < value1)
        {
            index2++;
            ++first2;
        }
        else
        {
            index1++;
            ++first1;

            //Skip common value in set 2.
            index2++;
            ++first2;
        }
    }

    if (index1 < count1)
    {
        std::copy(first1, last1, std::back_inserter(result));
    }
}

void htd::set_intersection(const std::vector<htd::vertex_t> & set1,
                           const std::vector<htd::vertex_t> & set2,
                           std::vector<htd::vertex_t> & result)
{
    auto first1 = set1.begin();
    auto first2 = set2.begin();

    std::size_t count1 = set1.size();
    std::size_t count2 = set2.size();

    htd::index_t index1 = 0;
    htd::index_t index2 = 0;

    while (index1 < count1 && index2 < count2)
    {
        auto value1 = *first1;
        auto value2 = *first2;

        if (value1 < value2)
        {
            index1++;
            ++first1;
        }
        else if (value2 < value1)
        {
            index2++;
            ++first2;
        }
        else
        {
            result.push_back(value1);

            index1++;
            ++first1;

            //Skip common value in set 2.
            index2++;
            ++first2;
        }
    }
}

#endif /* HTD_HTD_HELPERS_CPP */
