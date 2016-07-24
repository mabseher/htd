/*
 * File:   Option.cpp
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

#ifndef HTD_CLI_OPTION_CPP
#define	HTD_CLI_OPTION_CPP

#include <htd_cli/Option.hpp>

#include <iomanip>
#include <ostream>
#include <sstream>
#include <cctype>

htd_cli::Option::Option(const std::string & name, const std::string & description) : used_(false), shortName_(0), name_(name), description_(description)
{

}

htd_cli::Option::Option(const std::string & name, const std::string & description, char shortName) : used_(false), shortName_(shortName), name_(name), description_(description)
{

}

htd_cli::Option::~Option()
{

}

const std::string & htd_cli::Option::name(void) const
{
    return name_;
}

const std::string & htd_cli::Option::description(void) const
{
    return description_;
}

bool htd_cli::Option::hasShortName(void) const
{
    return std::isprint(shortName_);
}

char htd_cli::Option::shortName(void) const
{
    return shortName_;
}

bool htd_cli::Option::used(void) const
{
    return used_;
}

void htd_cli::Option::setUsed(void)
{
    used_ = true;
}

void htd_cli::Option::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name_);

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName_);
    }

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description_ << std::endl;
}

std::string htd_cli::Option::getCommandLineRepresentation(char name)
{
    std::ostringstream result;

    result << "-" << name;

    return result.str();
}

std::string htd_cli::Option::getCommandLineRepresentation(const std::string & name)
{
    std::ostringstream result;

    if (name.length() == 1)
    {
        result << "-" << name;
    }
    else
    {
        result << "--" << name;
    }

    return result.str();
}

#endif /* HTD_CLI_OPTION_CPP */
