/* 
 * File:   Helpers.hpp
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

#ifndef HTD_HTD_HELPERS_HPP
#define	HTD_HTD_HELPERS_HPP

#include <htd/Globals.hpp>
#include <htd/IHypertreeDecompositionAlgorithm.hpp>
#include <htd/IMutableGraph.hpp>
#include <htd/IMutableHypergraph.hpp>
#include <htd/IMutableDirectedGraph.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/IOrderingAlgorithm.hpp>
#include <htd/ITreeDecomposition.hpp>
#include <htd/IHypertreeDecomposition.hpp>
#include <htd/IMutableTreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/ISetCoverAlgorithm.hpp>

#include <algorithm>
#include <functional>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

#define HTD_UNUSED(x) (void)(x)

#ifdef NDEBUG
    #define DEBUGGING_CODE(x) 
#else
    #define DEBUGGING_CODE(x) x
#endif

#ifdef NDEBUG
    #define DEBUGGING_CODE_LEVEL2(x) 
#else
    #ifndef DEBUG2
        #define DEBUGGING_CODE_LEVEL2(x) 
    #else
        #define DEBUGGING_CODE_LEVEL2(x) x
    #endif
#endif

namespace std
{
    template<typename T>
    void hash_combine(std::size_t & seed, const T & v)
    {
        std::hash<T> hash_function;

        seed ^= hash_function(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template<>
    class hash<htd::hyperedge_t>
    {
        public:
            std::size_t operator()(const htd::hyperedge_t & data) const
            {
                std::size_t ret = 31;

                for (htd::vertex_t vertex : data)
                {
                    std::hash_combine(ret, vertex);
                }

                return ret;
            }
    };
}

namespace htd
{   
    void print(bool input);
    
    template < typename T >
    void print(const T& input)
    {
        std::cout << input;
    }
    
    template < >
    void print<std::string>(const std::string& input);
    
    template < typename T >
    void print(const std::vector<T> & input, bool sorted = false)
    {
        std::vector<T> tmp(input);
        
        std::cout << "std::vector ";
        
        if (tmp.size() > 0)
        {
            if (sorted)
            {
                std::sort(tmp.begin(), tmp.end());
            }
        
            std::cout << "[ ";
        
            for (auto it = tmp.cbegin(); it != tmp.cend();)
            {
                print(*it);
                
                if (++it != tmp.cend())
                {
                    std::cout << ", ";
                }
            }
            
            std::cout << " ] (SIZE: " << input.size() << ")";
        }
        else
        {
            std::cout << "<EMPTY>";
        }
    }
    
    template < typename T >
    void print(const std::set<T> & input)
    {
        std::cout << "std::set ";
        
        if (input.size() > 0)
        {
            std::cout << "[ ";
        
            for (auto it = input.cbegin(); it != input.cend();)
            {
                print(*it);
                
                if (++it != input.cend())
                {
                    std::cout << ", ";
                }
            }
            
            std::cout << " ] (SIZE: " << input.size() << ")";
        }
        else
        {
            std::cout << "<EMPTY>";
        }
    }
    
    template < typename T >
    void print(const std::unordered_set<T> & input, bool sorted = true)
    {
        std::vector<T> tmp(input.begin(), input.end());
        
        std::cout << "std::unordered_set ";
        
        if (input.size() > 0)
        {
            if (sorted)
            {
                std::sort(tmp.begin(), tmp.end());
            }
            
            std::cout << "[ ";
            
            for (auto it = tmp.cbegin(); it != tmp.cend();)
            {
                print(*it);
                
                if (++it != tmp.cend())
                {
                    std::cout << ", ";
                }
            }
            
            std::cout << " ] (SIZE: " << input.size() << ")";
        }
        else
        {
            std::cout << "<EMPTY>";
        }
    }
    
    template < typename Key, typename T >
    void print(const std::map<Key, T> & input)
    {
        std::cout << "std::map ";
        
        if (input.size() > 0)
        {
            std::cout << "[ ";
        
            for (auto it = input.cbegin(); it != input.cend();)
            {
                print((*it).first);
                        
                std::cout << " => ";
                
                print((*it).second);
                
                if (++it != input.cend())
                {
                    std::cout << ", ";
                }
            }
            
            std::cout << " ] (SIZE: " << input.size() << ")";
        }
        else
        {
            std::cout << "<EMPTY>";
        }
    }
    
    template <class InputIterator1, 
              class InputIterator2>
    std::size_t compute_set_union_size(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                       InputIterator2 firstSet2, InputIterator2 lastSet2)
    {
        size_t ret = 0;
        
        while (firstSet1 != lastSet1) 
        {
            if (firstSet2 == lastSet2)
            {
                ret += std::distance(firstSet1, lastSet1);
                
                firstSet1 = lastSet1;
            }
            else
            {
                auto value1 = *firstSet1;
                auto value2 = *firstSet2;
                
                ret++;

                if (value2 < value1) 
                {
                    ++firstSet2;
                } 
                else
                {
                    if (!(value1 < value2))
                    {
                        ++firstSet2;
                    }

                    ++firstSet1;
                }
            }
        }
        
        return ret + std::distance(firstSet2, lastSet2);
    }
    
    template <class InputIterator1, 
              class InputIterator2>
    std::size_t compute_set_difference_size(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                            InputIterator2 firstSet2, InputIterator2 lastSet2)
    {
        std::size_t ret = 0;
        
        std::size_t count1 = std::distance(firstSet1, lastSet1);
        std::size_t count2 = std::distance(firstSet2, lastSet2);
        
        htd::index_t index1 = 0;
        htd::index_t index2 = 0;
        
        while (index1 < count1 && index2 < count2)
        {
            auto value1 = *firstSet1;
            auto value2 = *firstSet2;

            if (value1 < value2)
            {
                ret++;

                index1++;
                
                ++firstSet1;
            } 
            else 
            {
                if (!(value2 < value1)) 
                {
                    index1++;
                
                    ++firstSet1;
                }

                index2++;
                
                ++firstSet2;
            }
        }
        
        return ret + count1 - index1;
    }
    
    template <class InputIterator1, 
              class InputIterator2>
    std::size_t compute_set_intersection_size(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                              InputIterator2 firstSet2, InputIterator2 lastSet2)
    {
        size_t ret = 0;
        
        std::size_t count1 = std::distance(firstSet1, lastSet1);
        std::size_t count2 = std::distance(firstSet2, lastSet2);
        
        htd::index_t index1 = 0;
        htd::index_t index2 = 0;
        
        while (index1 < count1 && index2 < count2) 
        {
            auto value1 = *firstSet1;
            auto value2 = *firstSet2;

            if (value1 < value2) 
            {
                index1++;
                
                ++firstSet1;
            } 
            else
            {
                if (!(value2 < value1)) 
                {
                    ret++;

                    index1++;
                
                    ++firstSet1;
                }

                index2++;
                
                ++firstSet2;
            }
        }
        
        return ret;
    }

    template <class InputIterator1,
              class InputIterator2>
    bool has_non_empty_set_difference(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                      InputIterator2 firstSet2, InputIterator2 lastSet2)
    {
        bool ret = false;

        std::size_t count1 = std::distance(firstSet1, lastSet1);
        std::size_t count2 = std::distance(firstSet2, lastSet2);

        htd::index_t index1 = 0;
        htd::index_t index2 = 0;

        while (index1 < count1 && index2 < count2 && !ret)
        {
            auto value1 = *firstSet1;
            auto value2 = *firstSet2;

            if (value1 < value2)
            {
                ret = true;

                index1++;

                ++firstSet1;
            }
            else
            {
                if (!(value2 < value1))
                {
                    index1++;

                    ++firstSet1;
                }

                index2++;

                ++firstSet2;
            }
        }

        return ret || index1 < count1;
    }
    
    template <class InputIterator1, 
              class InputIterator2>
    bool has_non_empty_set_intersection(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                        InputIterator2 firstSet2, InputIterator2 lastSet2)
    {
        bool ret = false;

        std::size_t count1 = std::distance(firstSet1, lastSet1);
        std::size_t count2 = std::distance(firstSet2, lastSet2);

        htd::index_t index1 = 0;
        htd::index_t index2 = 0;

        while (index1 < count1 && index2 < count2 && !ret)
        {
            auto value1 = *firstSet1;
            auto value2 = *firstSet2;

            if (value1 < value2) 
            {
                index1++;

                ++firstSet1;
            } 
            else
            {
                if (!(value2 < value1)) 
                {
                    ret = true;

                    index1++;

                    ++firstSet1;
                }

                index2++;

                ++firstSet2;
            }
        }
        
        return ret;
    }
    
    template <class InputIterator1, 
              class InputIterator2,
              class InputIterator3>
    std::size_t compute_filtered_set_union_size(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                                InputIterator2 firstSet2, InputIterator2 lastSet2,
                                                InputIterator3 firstFilterSet, InputIterator3 lastFilterSet)
    {
        std::size_t ret = 0;
        
        if (firstFilterSet == lastFilterSet)
        {
            ret = htd::compute_set_union_size(firstSet1, lastSet1,
                                              firstSet2, lastSet2);
        }
        else
        {
            InputIterator3 tmp1 = firstFilterSet;
            InputIterator3 tmp2 = firstFilterSet;

            while (firstSet1 != lastSet1 && *firstSet1 < *firstSet2)
            {
                if (*firstSet1 < *tmp1) 
                {
                    ret++;
                            
                    ++firstSet1;
                }
                else
                {
                    if (!(*tmp1 < *firstSet1)) 
                    {
                        ++firstSet1;
                    }

                    ++tmp1;
                    ++tmp2;
                }
            }

            while (firstSet1 != lastSet1 && firstSet2 != lastSet2) 
            {
                while (tmp1 != lastFilterSet && *tmp1 < *firstSet1) 
                {
                    ++tmp1;
                }

                while (tmp2 != lastFilterSet && *tmp2 < *firstSet2)
                {
                    ++tmp2;
                }

                if (*firstSet2 < *firstSet1)
                {
                    if (tmp2 == lastFilterSet || *firstSet2 < *tmp2) 
                    {
                        ret++;
                    }

                    ++firstSet2;
                }
                else 
                {
                    if (tmp1 == lastFilterSet || *firstSet1 < *tmp1) 
                    {
                        ret++;
                    }

                    if (!(*firstSet1 < *firstSet2))
                    {
                        ++firstSet2;
                    }

                    ++firstSet1;
                }
            }

            if (firstSet1 != lastSet1) 
            {
                ret += htd::compute_set_difference_size(firstSet1, lastSet1, tmp1, lastFilterSet);
            }
            else if (firstSet2 != lastSet2) 
            {
                ret += htd::compute_set_difference_size(firstSet2, lastSet2, tmp2, lastFilterSet);
            }
        }

        return ret;
    }
    
    template <class InputIterator1, 
              class InputIterator2,
              class InputIterator3, 
              class OutputIterator>
    OutputIterator filtered_set_union(InputIterator1 firstSet1, InputIterator1 lastSet1,
                                      InputIterator2 firstSet2, InputIterator2 lastSet2,
                                      InputIterator3 firstFilterSet, InputIterator3 lastFilterSet,
                                      OutputIterator result)
    {
        if (firstFilterSet == lastFilterSet)
        {
            std::set_union(firstSet1, lastSet1,
                           firstSet2, lastSet2,
                           result);
        }
        else
        {
            InputIterator3 tmp1 = firstFilterSet;
            InputIterator3 tmp2 = firstFilterSet;

            while (firstSet1 != lastSet1 && firstSet2 != lastSet2) 
            {
                auto value1 = *firstSet1;
                auto value2 = *firstSet2;

                while (tmp1 != lastFilterSet && *tmp1 < value1) 
                {
                    ++tmp1;
                }

                while (tmp2 != lastFilterSet && *tmp2 < value2)
                {
                    ++tmp2;
                }

                if (value2 < value1)
                {
                    if (tmp2 == lastFilterSet || value2 < *tmp2) 
                    {
                        *result++ = value2;
                    }

                    ++firstSet2;
                }
                else 
                {
                    if (tmp1 == lastFilterSet || value1 < *tmp1) 
                    {
                        *result++ = value1;
                    }

                    if (!(value1 < value2))
                    {
                        ++firstSet2;
                    }

                    ++firstSet1;
                }
            }

            if (firstSet1 != lastSet1) 
            {
                std::set_difference(firstSet1, lastSet1, tmp1, lastFilterSet, result);
            }
            else if (firstSet2 != lastSet2) 
            {
                std::set_difference(firstSet2, lastSet2, tmp2, lastFilterSet, result);
            }
        }

        return result;
    }
    
    template <class Rep, class Period = std::ratio<1> >
    void printDuration(const std::chrono::duration<Rep, Period>& duration)
    {
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() < 1000)
        {
            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << " nanoseconds";
        }
        else if (std::chrono::duration_cast<std::chrono::microseconds>(duration).count() < 1000)
        {
            std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / 1000 << "." << std::setw(3) << std::setfill('0') << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() % 1000 << " microseconds";
        }
        else if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() < 1000)
        {
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000 << "." << std::setw(3) << std::setfill('0') << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % 1000 << " milliseconds";
        }
        else if (std::chrono::duration_cast<std::chrono::seconds>(duration).count() < 1000)
        {
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1000 << "." << std::setw(3) << std::setfill('0') << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000 << " seconds";
        }
    }

    htd::IMutableGraph * getDefaultGraph(void);

    htd::IMutableGraph * getDefaultGraph(std::size_t size);

    htd::IMutableHypergraph * getDefaultHypergraph(void);

    htd::IMutableHypergraph * getDefaultHypergraph(std::size_t size);

    htd::IMutableDirectedGraph * getDefaultDirectedGraph(void);

    htd::IMutableDirectedGraph * getDefaultDirectedGraph(std::size_t size);

    htd::IMutableTreeDecomposition * getDefaultTreeDecomposition(void);

    htd::IMutableTreeDecomposition * getDefaultTreeDecomposition(const htd::ITreeDecomposition & decomposition);

    htd::IMutableHypertreeDecomposition * getDefaultHypertreeDecomposition(void);

    htd::IMutableHypertreeDecomposition * getDefaultHypertreeDecomposition(const htd::ITreeDecomposition & decomposition);

    htd::IMutableHypertreeDecomposition * getDefaultHypertreeDecomposition(const htd::IHypertreeDecomposition & decomposition);

    htd::ITreeDecompositionAlgorithm * getDefaultTreeDecompositionAlgorithm(const htd::IOrderingAlgorithm & orderingAlgorithm);

    htd::IHypertreeDecompositionAlgorithm * getDefaultHypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm, const htd::ISetCoverAlgorithm & setCoverAlgorithm);

    htd::IOrderingAlgorithm * getDefaultOrderingAlgorithm(void);
    
    htd::ISetCoverAlgorithm * getDefaultSetCoverAlgorithm(void);
    
}

#endif /* HTD_HTD_HELPERS_HPP */
