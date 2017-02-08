/* 
 * File:   Algorithm.hpp
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

#ifndef HTD_HTD_ALGORITHM_HPP
#define HTD_HTD_ALGORITHM_HPP

namespace htd
{
    template <class InputIterator1,
              class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2)
    {
        bool ret = true;

        while (ret && first1 != last1 && first2 != last2)
        {
            ret = (*first1 == *first2);

            ++first1;
            ++first2;
        }

        return ret && first1 == last1 && first2 == last2;
    }
}

#endif /* HTD_HTD_ALGORITHM_HPP */
