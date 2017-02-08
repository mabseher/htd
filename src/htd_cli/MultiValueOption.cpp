/*
 * File:   MultiValueOption.cpp
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

#ifndef HTD_CLI_MULTIVALUEOPTION_CPP
#define HTD_CLI_MULTIVALUEOPTION_CPP

#include <htd_cli/MultiValueOption.hpp>

#include <cstring>
#include <iomanip>
#include <ios>
#include <ostream>
#include <sstream>
#include <vector>

/**
 *  Private implementation details of class htd_cli::MultiValueOption.
 */
struct htd_cli::MultiValueOption::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     */
    Implementation(void) : values_()
    {

    }

    virtual ~Implementation()
    {

    }

    /**
     *  The values assigned to the option.
     */
    std::vector<std::string> values_;
};

htd_cli::MultiValueOption::MultiValueOption(const char * const name, const char * const description, const char * const valuePlaceholder) : htd_cli::ValueOption(name, description, valuePlaceholder), implementation_(new Implementation())
{

}

htd_cli::MultiValueOption::MultiValueOption(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName) : htd_cli::ValueOption(name, description, valuePlaceholder, shortName), implementation_(new Implementation())
{

}

htd_cli::MultiValueOption::~MultiValueOption()
{

}

std::size_t htd_cli::MultiValueOption::valueCount(void) const
{
    return implementation_->values_.size();
}

const char * htd_cli::MultiValueOption::value(htd::index_t index) const
{
    HTD_ASSERT(index < implementation_->values_.size())

    return implementation_->values_.at(index).c_str();
}

void htd_cli::MultiValueOption::registerValue(const char * const value)
{
    implementation_->values_.emplace_back(value);

    setUsed();
}

void htd_cli::MultiValueOption::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ios::fmtflags oldFormat(stream.flags());

    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name());

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName());
    }

    parameterDefinition << " <" << valuePlaceholder() << ">";

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description() << std::endl;

    stream.flags(oldFormat);
}

#endif /* HTD_CLI_MULTIVALUEOPTION_CPP */
