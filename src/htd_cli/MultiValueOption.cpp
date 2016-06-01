/*
 * File:   MultiValueOption.cpp
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

#ifndef HTD_CLI_MULTIVALUEOPTION_CPP
#define	HTD_CLI_MULTIVALUEOPTION_CPP

#include <htd_cli/MultiValueOption.hpp>

#include <iomanip>
#include <ostream>
#include <sstream>

htd_cli::MultiValueOption::MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder) : htd_cli::ValueOption(name, description, valuePlaceholder)
{

}

htd_cli::MultiValueOption::MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName) : htd_cli::ValueOption(name, description, valuePlaceholder, shortName)
{

}

htd_cli::MultiValueOption::~MultiValueOption()
{

}

const std::vector<std::string> & htd_cli::MultiValueOption::values(void) const
{
    return values_;
}

void htd_cli::MultiValueOption::registerValue(const std::string & value)
{
    values_.push_back(value);

    setUsed();
}

void htd_cli::MultiValueOption::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name_);

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName_);
    }

    parameterDefinition << " <" << valuePlaceholder() << ">";

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description_ << std::endl;
}

#endif /* HTD_CLI_MULTIVALUEOPTION_CPP */
