/*
 * File:   ValueOption.cpp
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

#ifndef HTD_CLI_VALUEOPTION_CPP
#define HTD_CLI_VALUEOPTION_CPP

#include <htd_cli/ValueOption.hpp>

htd_cli::ValueOption::ValueOption(const char * const name, const char * const description, const char * const valuePlaceholder) : htd_cli::Option(name, description), valuePlaceholder_(valuePlaceholder)
{

}

htd_cli::ValueOption::ValueOption(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName) : htd_cli::Option(name, description, shortName), valuePlaceholder_(valuePlaceholder)
{

}

htd_cli::ValueOption::~ValueOption()
{

}

const char * htd_cli::ValueOption::valuePlaceholder(void) const
{
    return valuePlaceholder_.c_str();
}

#endif /* HTD_CLI_VALUEOPTION_CPP */
