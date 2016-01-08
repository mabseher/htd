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

#endif /* HTD_HTD_HELPERS_CPP */
