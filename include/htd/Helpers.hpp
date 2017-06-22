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

#ifndef HTD_HTD_HELPERS_HPP
#define HTD_HTD_HELPERS_HPP

#include <htd/Globals.hpp>
#include <htd/Hyperedge.hpp>
#include <htd/Collection.hpp>
#include <htd/ConstCollection.hpp>
#include <htd/ILabel.hpp>
#include <htd/Label.hpp>
#include <htd/FilteredHyperedgeCollection.hpp>
#include <htd/LibraryInstance.hpp>
#include <htd/ITreeDecomposition.hpp>

#include <algorithm>
#include <cassert>
#include <functional>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

namespace htd
{
    /**
     *  Create a new management instance.
     *
     *  @param[in] id   The ID of the new management instance.
     *
     *  @return A pointer to the new management instance.
     */
    HTD_API htd::LibraryInstance * createManagementInstance(htd::id_t id);

    template < typename T >
    void print(const T & input, std::ostream & stream)
    {
        stream << input;
    }

    template < typename T >
    void print(const T & input)
    {
        print(input, std::cout);
    }

    template < >
    HTD_API void print<std::string>(const std::string& input);

    template < >
    HTD_API void print<std::string>(const std::string& input, std::ostream & stream);

    template < typename T >
    void print(const htd::ConstCollection<T> & input, std::ostream & stream, bool sorted = false)
    {
        std::vector<T> tmp(input.begin(), input.end());

        if (tmp.empty())
        {
            stream << "<EMPTY>";
        }
        else
        {
            if (sorted)
            {
                std::sort(tmp.begin(), tmp.end());
            }

            stream << "[ ";

            for (auto it = tmp.cbegin(); it != tmp.cend();)
            {
                print(*it, stream);

                if (++it != tmp.cend())
                {
                    stream << ", ";
                }
            }

            stream << " ]";
        }
    }

    template < typename T >
    void print(const htd::ConstCollection<T> & input, bool sorted = false)
    {
        print(input, std::cout, sorted);
    }

    template < typename T >
    void print(const std::vector<T> & input, std::ostream & stream, bool sorted = false)
    {
        std::vector<T> tmp(input);

        if (tmp.empty())
        {
            stream << "<EMPTY>";
        }
        else
        {
            if (sorted)
            {
                std::sort(tmp.begin(), tmp.end());
            }
        
            stream << "[ ";
        
            for (auto it = tmp.cbegin(); it != tmp.cend();)
            {
                print(*it, stream);
                
                if (++it != tmp.cend())
                {
                    stream << ", ";
                }
            }
            
            stream << " ]";
        }
    }

    template < typename T >
    void print(const std::vector<T> & input, bool sorted = false)
    {
        print(input, std::cout, sorted);
    }
    
    template < typename T >
    void print(const std::set<T> & input, std::ostream & stream)
    {
        if (input.empty())
        {
            stream << "<EMPTY>";
        }
        else
        {
            stream << "[ ";
        
            for (auto it = input.cbegin(); it != input.cend();)
            {
                print(*it, stream);
                
                if (++it != input.cend())
                {
                    stream << ", ";
                }
            }
            
            stream << " ]";
        }
    }

    template < typename T >
    void print(const std::set<T> & input)
    {
        print(input, std::cout);
    }
    
    template < typename T >
    void print(const std::unordered_set<T> & input, std::ostream & stream, bool sorted = true)
    {
        std::vector<T> tmp(input.begin(), input.end());

        if (input.empty())
        {
            stream << "<EMPTY>";
        }
        else
        {
            if (sorted)
            {
                std::sort(tmp.begin(), tmp.end());
            }
            
            stream << "[ ";
            
            for (auto it = tmp.cbegin(); it != tmp.cend();)
            {
                print(*it, stream);
                
                if (++it != tmp.cend())
                {
                    stream << ", ";
                }
            }
            
            stream << " ]";
        }
    }

    template < typename T >
    void print(const std::unordered_set<T> & input, bool sorted = true)
    {
        print(input, std::cout, sorted);
    }
    
    template < typename Key, typename T >
    void print(const std::map<Key, T> & input, std::ostream & stream)
    {
        if (input.empty())
        {
            stream << "<EMPTY>";
        }
        else
        {
            stream << "[ ";
        
            for (auto it = input.cbegin(); it != input.cend();)
            {
                print((*it).first, stream);
                        
                stream << " => ";
                
                print((*it).second, stream);
                
                if (++it != input.cend())
                {
                    stream << ", ";
                }
            }
            
            stream << " ]";
        }
    }

    template < typename Key, typename T >
    void print(const std::map<Key, T> & input)
    {
        print(input, std::cout);
    }

    HTD_API void print(bool input);

    HTD_API void print(bool input, std::ostream & stream);

    HTD_API void print(const htd::Hyperedge & input);

    HTD_API void print(const htd::Hyperedge & input, std::ostream & stream);

    template < typename T >
    void set_union(const std::vector<T> & set1,
                   const std::vector<T> & set2,
                   std::vector<T> & result)
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
                result.push_back(value1);

                index1++;
                ++first1;
            }
            else if (value2 < value1)
            {
                result.push_back(value2);

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

        if (index1 < count1)
        {
            result.insert(result.end(), first1, last1);
        }
        else if (index2 < count2)
        {
            result.insert(result.end(), first2, last2);
        }
    }

    template < typename T, typename Collection >
    const T & selectRandomElement(const Collection & collection)
    {
        auto position = collection.begin();

        /* Coverity complains about std::rand() being not safe for security related operations. We are happy with a pseudo-random number here. */
        // coverity[dont_call]
        std::advance(position, std::rand() % collection.size());

        return *position;
    }

    /**
     *  Check whether a collection is sorted in ascending order and free of duplicates.
     *
     *  @param[in] first    An iterator to the begin of the collection.
     *  @param[in] last     An iterator to the end of the collection.
     *
     *  @return True if the collection is sorted in ascending order and free of duplicates, false otherwise.
     */
    template < class InputIterator >
    bool is_sorted_and_duplicate_free(InputIterator first, InputIterator last)
    {
        bool ret = true;

        if (first != last)
        {
            for (InputIterator next = first; ret && ++next != last; ++first)
            {
                ret = *first < *next;
            }
        }

        return ret;
    }

    HTD_API void set_union(const std::vector<htd::vertex_t> & set1,
                           const std::vector<htd::vertex_t> & set2,
                           htd::vertex_t ignoredVertex,
                           std::vector<htd::vertex_t> & result);

    HTD_API void set_difference(const std::vector<htd::vertex_t> & set1,
                                const std::vector<htd::vertex_t> & set2,
                                std::vector<htd::vertex_t> & result);

    HTD_API void set_intersection(const std::vector<htd::vertex_t> & set1,
                                  const std::vector<htd::vertex_t> & set2,
                                  std::vector<htd::vertex_t> & result);

    HTD_API std::tuple<std::size_t, std::size_t, std::size_t> analyze_sets(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2);

    /**
     *  Decompose two sets of vertices into vertices only in the first set, vertices only in the second set and vertices in both sets.
     *
     *  @param[in] set1                 The first set of vertices, sorted in ascending order.
     *  @param[in] set2                 The second set of vertices, sorted in ascending order.
     *  @param[out] resultOnlySet1      The set of vertices which are found only in the first set, sorted in ascending order.
     *  @param[out] resultOnlySet2      The set of vertices which are found only in the second set, sorted in ascending order.
     *  @param[out] resultIntersection  The set of vertices which are found in both sets, sorted in ascending order.
     */
    void decompose_sets(const std::vector<htd::vertex_t> & set1,
                        const std::vector<htd::vertex_t> & set2,
                        std::vector<htd::vertex_t> & resultOnlySet1,
                        std::vector<htd::vertex_t> & resultOnlySet2,
                        std::vector<htd::vertex_t> & resultIntersection) HTD_NOEXCEPT;

    HTD_API std::pair<std::size_t, std::size_t> symmetric_difference_sizes(const std::vector<htd::vertex_t> & set1, const std::vector<htd::vertex_t> & set2);

    template < class InputIterator1,
               class InputIterator2 >
    std::size_t set_union_size(InputIterator1 first1, InputIterator1 last1,
                               InputIterator2 first2, InputIterator2 last2)
    {
        std::size_t ret = 0;
        
        while (first1 != last1)
        {
            if (first2 == last2)
            {
                ret += std::distance(first1, last1);
                
                first1 = last1;
            }
            else
            {
                ++ret;

                if (*first2 < *first1)
                {
                    ++first2;
                } 
                else
                {
                    if (*first1 == *first2)
                    {
                        ++first2;
                    }

                    ++first1;
                }
            }
        }
        
        return ret + std::distance(first2, last2);
    }
    
    template < class InputIterator1,
               class InputIterator2 >
    std::size_t set_difference_size(InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
        std::size_t ret = 0;

        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                ++ret;

                ++first1;
            } 
            else
            {
                if (*first1 == *first2)
                {
                    ++first1;
                }

                ++first2;
            }
        }
        
        return ret + std::distance(first1, last1);
    }

    template < class InputIterator1,
               class InputIterator2 >
    std::size_t set_intersection_size(InputIterator1 first1, InputIterator1 last1,
                                      InputIterator2 first2, InputIterator2 last2)
    {
        std::size_t ret = 0;

        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                ++first1;
            } 
            else
            {
                if (*first1 == *first2)
                {
                    ++ret;

                    ++first1;
                }

                ++first2;
            }
        }
        
        return ret;
    }

    template < class InputIterator1,
               class InputIterator2 >
    bool has_non_empty_set_difference(InputIterator1 first1, InputIterator1 last1,
                                      InputIterator2 first2, InputIterator2 last2)
    {
        bool ret = false;

        while (first1 != last1 && first2 != last2 && !ret)
        {
            if (*first1 < *first2)
            {
                ret = true;

                ++first1;
            }
            else
            {
                if (*first1 == *first2)
                {
                    ++first1;
                }

                ++first2;
            }
        }

        return ret || first1 != last1;
    }
    
    template < class InputIterator1,
               class InputIterator2 >
    bool has_non_empty_set_intersection(InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
    {
        bool ret = false;

        while (first1 != last1 && first2 != last2 && !ret)
        {
            if (*first1 < *first2)
            {
                ++first1;
            } 
            else
            {
                if (*first1 == *first2)
                {
                    ret = true;

                    ++first1;
                }

                ++first2;
            }
        }
        
        return ret;
    }

    template < typename T >
    void inplace_merge(std::vector<T> & set1, const std::vector<T> & set2)
    {
        if (set2.size() <= 4)
        {
            auto it = set1.begin();

            for (htd::vertex_t newElement : set2)
            {
                it = set1.insert(std::lower_bound(it, set1.end(), newElement), newElement) + 1;
            }
        }
        else
        {
            std::size_t middle = set1.size();

            set1.insert(set1.end(), set2.begin(), set2.end());

            std::inplace_merge(set1.begin(),
                               set1.begin() + middle,
                               set1.end());
        }
    }

    template < typename T >
    void inplace_set_union(std::vector<T> & set1, const std::vector<T> & set2)
    {
        std::vector<T> tmp;
        tmp.reserve(set2.size());

        std::set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(), std::back_inserter(tmp));

        if (!tmp.empty())
        {
            htd::inplace_merge(set1, tmp);
        }
    }

    /**
     *  Getter for the position of a hyperedge within a collection of hyperedges sorted by ID in ascending order.
     *
     *  @param[in] first    An iterator to the start of the hyperedge collection.
     *  @param[in] last     An iterator to the end of the hyperedge collection.
     *  @param[in] id       The identifier of the desired hyperedge.
     *
     *  @return An iterator to the hyperedge within the given collection of hyperedges. If no
     *  hyperedge with the given identifier is found, the result of this function is equal to
     *  last.
     */
    template < class InputIterator >
    InputIterator hyperedgePosition(InputIterator first, InputIterator last, htd::id_t id)
    {
        auto it = first;

        typename std::iterator_traits<InputIterator>::difference_type count = std::distance(first, last);

        typename std::iterator_traits<InputIterator>::difference_type step = count / 2;

        while (count > 0)
        {
            it = first;

            step = count / 2;

            std::advance(it, step);

            if (it->id() < id)
            {
                first = ++it;

                count -= step + 1;
            }
            else
            {
                count = step;
            }
        }

        if (first != last && first->id() != id)
        {
            first = last;
        }

        return first;
    }

    /**
     *  Getter for the position of a hyperedge within a collection of hyperedge pointers sorted by ID in ascending order.
     *
     *  @param[in] first    An iterator to the start of the hyperedge pointer collection.
     *  @param[in] last     An iterator to the end of the hyperedge pointer collection.
     *  @param[in] id       The identifier of the desired hyperedge.
     *
     *  @return An iterator to the hyperedge pointer within the given collection of hyperedge pointers.
     *  If no hyperedge with the given identifier is found, the result of this function is equal to
     *  last.
     */
    template < class InputIterator >
    InputIterator hyperedgePointerPosition(InputIterator first, InputIterator last, htd::id_t id)
    {
        auto it = first;

        typename std::iterator_traits<InputIterator>::difference_type count = std::distance(first, last);

        typename std::iterator_traits<InputIterator>::difference_type step = count / 2;

        while (count > 0)
        {
            it = first;

            step = count / 2;

            std::advance(it, step);

            if ((*it)->id() < id)
            {
                first = ++it;

                count -= step + 1;
            }
            else
            {
                count = step;
            }
        }

        if (first != last && (*first)->id() != id)
        {
            first = last;
        }

        return first;
    }

    template < class Rep, class Period = std::ratio<1> >
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

    template < typename Set, typename Collection >
    void fillSet(const Collection & collection, Set & set)
    {
        auto it = collection.begin();

        for (htd::index_t remainder = collection.size(); remainder > 0; --remainder)
        {
            set.insert(*it);

            ++it;
        }
    }

    /**
     *  Insert a new element into the given vector such that sortedness is preserved.
     *
     *  @param[in] collection   The collection which shall be updated.
     *  @param[in] element      The element which shall be inserted.
     */
    template < typename T >
    void insertSorted(std::vector<T> & collection, const T & element)
    {
        collection.insert(std::lower_bound(collection.begin(), collection.end(), element), element);
    }

    /**
     *  Execute a given unary function for each element of the provided collection.
     *
     *  @param[in] collection   The collection.
     *  @param[in] f            The function.
     *
     *  @return The result of std::move(f).
     */
    template < typename T, typename UnaryFunction >
    UnaryFunction for_each(const htd::ConstCollection<T> & collection, UnaryFunction f)
    {
        std::size_t remainder = collection.size();

        auto it = collection.begin();

        while (remainder > 0)
        {
            f(*it);

            --remainder;

            ++it;
        }

        return std::move(f);
    }

    /**
     *  Compute the collection of all vertices which are present at least two child bags.
     *
     *  @param[in] decomposition    The tree decomposition to which the given vertex belongs.
     *  @param[in] vertex           The vertex which shall be investigated.
     *
     *  @return The collection of all vertices which are present in at least two child bags. The result is sorted in ascending order.
     */
    HTD_API std::vector<htd::vertex_t> * computeJoinVertices(const htd::ITreeDecomposition & decomposition, htd::vertex_t vertex);
}

namespace std
{
    template < typename T >
    std::ostream & operator<<(std::ostream & stream, const std::vector<T> & input)
    {
        htd::print(input, stream);

        return stream;
    }

    template < typename T >
    std::ostream & operator<<(std::ostream & stream, const htd::ConstCollection<T> & input)
    {
        htd::print(input, stream);

        return stream;
    }

    std::ostream & operator<<(std::ostream & stream, const htd::FilteredHyperedgeCollection & input);

    /**
     *  Combine the given seed with the hash code of the given input.
     *
     *  @param[in] seed     The seed hash value.
     *  @param[in] input    The input which's hash code shall be combined with the seed hash value.
     *
     *  @return The combined hash code.
     */
    template < typename T >
    void hash_combine(std::size_t & seed, const T & input)
    {
        std::hash<T> hashFunction;

        seed ^= hashFunction(input) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    /**
     *  Implementation of std::hash for htd::Hyperedge.
     */
    template < >
    struct hash<htd::Hyperedge>
    {
        public:
            /**
             *  Compute the hash code of a given htd::Hyperedge.
             *
             *  @param[in] data The htd::Hyperedge which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::Hyperedge.
             */
            std::size_t operator()(const htd::Hyperedge & data) const
            {
                std::size_t ret = 31 * data.id();

                for (htd::vertex_t vertex : data)
                {
                    std::hash_combine(ret, vertex);
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for htd::FilteredHyperedgeCollection.
     */
    template < >
    struct hash<htd::FilteredHyperedgeCollection>
    {
        public:
            /**
             *  Compute the hash code of a given htd::FilteredHyperedgeCollection.
             *
             *  @param[in] data The htd::FilteredHyperedgeCollection which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::FilteredHyperedgeCollection.
             */
            std::size_t operator()(const htd::FilteredHyperedgeCollection & data) const
            {
                std::size_t ret = 31;

                for (const htd::Hyperedge & hyperedge : data)
                {
                    std::hash_combine(ret, hyperedge);
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for htd::Collection<htd::vertex_t>.
     */
    template < >
    struct hash<htd::Collection<htd::vertex_t>>
    {
        public:
            /**
             *  Compute the hash code of a given htd::Collection<htd::vertex_t>.
             *
             *  @param[in] data The htd::Collection<htd::vertex_t> which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::Collection<htd::vertex_t>.
             */
            std::size_t operator()(const htd::ConstCollection<htd::vertex_t> & data) const
            {
                std::size_t ret = 31;

                for (htd::vertex_t vertex : data)
                {
                    std::hash_combine(ret, vertex);
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for htd::ConstCollection<htd::vertex_t>.
     */
    template < >
    struct hash<htd::ConstCollection<htd::vertex_t>>
    {
        public:
            /**
             *  Compute the hash code of a given htd::ConstCollection<htd::vertex_t>.
             *
             *  @param[in] data The htd::ConstCollection<htd::vertex_t> which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::ConstCollection<htd::vertex_t>.
             */
            std::size_t operator()(const htd::ConstCollection<htd::vertex_t> & data) const
            {
                std::size_t ret = 31;

                for (htd::vertex_t vertex : data)
                {
                    std::hash_combine(ret, vertex);
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for htd::Collection<htd::Hyperedge>.
     */
    template < >
    struct hash<htd::Collection<htd::Hyperedge>>
    {
        public:
            /**
             *  Compute the hash code of a given htd::Collection<htd::Hyperedge>.
             *
             *  @param[in] data The htd::Collection<htd::Hyperedge> which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::Collection<htd::Hyperedge>.
             */
            std::size_t operator()(const htd::ConstCollection<htd::Hyperedge> & data) const
            {
                std::size_t ret = 31;

                std::hash<htd::Hyperedge> hashFunction;

                for (const htd::Hyperedge & hyperedge : data)
                {
                    std::hash_combine(ret, hashFunction(hyperedge));
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for htd::ConstCollection<htd::Hyperedge>.
     */
    template < >
    struct hash<htd::ConstCollection<htd::Hyperedge>>
    {
        public:
            /**
             *  Compute the hash code of a given htd::ConstCollection<htd::Hyperedge>.
             *
             *  @param[in] data The htd::ConstCollection<htd::Hyperedge> which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::ConstCollection<htd::Hyperedge>.
             */
            std::size_t operator()(const htd::ConstCollection<htd::Hyperedge> & data) const
            {
                std::size_t ret = 31;

                std::hash<htd::Hyperedge> hashFunction;

                for (const htd::Hyperedge & hyperedge : data)
                {
                    std::hash_combine(ret, hashFunction(hyperedge));
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for std::vector<htd::vertex_t>.
     */
    template < >
    struct hash<std::vector<htd::vertex_t>>
    {
        public:
            /**
             *  Compute the hash code of a given std::vector<htd::vertex_t>.
             *
             *  @param[in] data The std::vector<htd::vertex_t> which's hash code shall be returned.
             *
             *  @return The hash code of the given std::vector<htd::vertex_t>.
             */
            std::size_t operator()(const std::vector<htd::vertex_t> & data) const
            {
                std::size_t ret = 31;

                for (htd::vertex_t vertex : data)
                {
                    std::hash_combine(ret, vertex);
                }

                return ret;
            }
    };

    /**
     *  Implementation of std::hash for std::vector<htd::Hyperedge>.
     */
    template < >
    struct hash<std::vector<htd::Hyperedge>>
    {
        public:
            /**
             *  Compute the hash code of a given htd::ConstCollection<htd::Hyperedge>.
             *
             *  @param[in] data The htd::ConstCollection<htd::Hyperedge> which's hash code shall be returned.
             *
             *  @return The hash code of the given htd::ConstCollection<htd::Hyperedge>.
             */
            std::size_t operator()(const std::vector<htd::Hyperedge> & data) const
            {
                std::size_t ret = 31;

                std::hash<htd::Hyperedge> hashFunction;

                for (const htd::Hyperedge & hyperedge : data)
                {
                    std::hash_combine(ret, hashFunction(hyperedge));
                }

                return ret;
            }
    };
}

#endif /* HTD_HTD_HELPERS_HPP */
