/*
 * File:   Option.cpp
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

#ifndef HTD_CLI_OPTION_CPP
#define HTD_CLI_OPTION_CPP

#include <htd_cli/Option.hpp>

#include <cstring>
#include <iomanip>
#include <ios>
#include <ostream>
#include <sstream>
#include <cctype>

/**
 *  Private implementation details of class htd_cli::Option.
 */
struct htd_cli::Option::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     *
     *  @param[in] name         The name of the command line option.
     *  @param[in] description  The description of the command line option.
     *  @param[in] shortName    The abbreviated name of the option which acts as an alias for the option name.
     */
    Implementation(const std::string & name, const std::string & description, char shortName = '\0') : used_(false), shortName_(shortName), name_(name), description_(description)
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  A boolean flag indicating whether the option was used.
     */
    bool used_;

    /**
     *  The abbreviated name of the option which acts as an alias for the option name.
     */
    char shortName_;

    /**
     *  The name of the command line option.
     */
    std::string name_;

    /**
     *  The description of the command line option.
     */
    std::string description_;
};

htd_cli::Option::Option(const char * const name, const char * const description, char shortName) : implementation_(new Implementation(name, description, shortName))
{

}

htd_cli::Option::~Option()
{

}

const char * htd_cli::Option::name(void) const
{
    return implementation_->name_.c_str();
}

const char * htd_cli::Option::description(void) const
{
    return implementation_->description_.c_str();
}

bool htd_cli::Option::hasShortName(void) const
{
#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
    return std::isprint(implementation_->shortName_) > 0;
#else
    return std::isprint(implementation_->shortName_);
#endif
}

char htd_cli::Option::shortName(void) const
{
    return implementation_->shortName_;
}

bool htd_cli::Option::used(void) const
{
    return implementation_->used_;
}

void htd_cli::Option::setUsed(void)
{
    implementation_->used_ = true;
}

void htd_cli::Option::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ios::fmtflags oldFormat(stream.flags());

    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(implementation_->name_);

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(implementation_->shortName_);
    }

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << implementation_->description_ << std::endl;

    stream.flags(oldFormat);
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
