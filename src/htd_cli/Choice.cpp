/*
 * File:   Choice.cpp
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

#ifndef HTD_CLI_CHOICE_CPP
#define	HTD_CLI_CHOICE_CPP

#include <htd_cli/Choice.hpp>

#include <iomanip>
#include <ostream>
#include <sstream>

htd_cli::Choice::Choice(const std::string & name, const std::string & description, const std::string & valuePlaceholder) : htd_cli::SingleValueOption::SingleValueOption(name, description, valuePlaceholder), defaultValue_(), maxPossibilityNameLength_(0), possibilities_()
{

}

htd_cli::Choice::Choice(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName) : htd_cli::SingleValueOption::SingleValueOption(name, description, valuePlaceholder, shortName), defaultValue_(), maxPossibilityNameLength_(0), possibilities_()
{

}

htd_cli::Choice::~Choice()
{

}

void htd_cli::Choice::addPossibility(const std::string & value, const std::string & description)
{
    for (const Possibility & possibility : possibilities_)
    {
        if (value == possibility.value)
        {
            std::ostringstream message;

            message << "Name clash detected between possibilities of option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "': Possibility '" << value << "'";

            throw std::runtime_error(message.str());
        }
    }

    if (value.length() > maxPossibilityNameLength_)
    {
        maxPossibilityNameLength_ = value.length();
    }

    possibilities_.emplace_back(value, description);
}

bool htd_cli::Choice::hasDefaultValue(void)
{
    return !defaultValue_.empty();
}

void htd_cli::Choice::setDefaultValue(const std::string & value)
{
    bool valid = false;

    for (auto it = possibilities_.begin(); !valid && it != possibilities_.end(); ++it)
    {
        if (it->value == value)
        {
            valid = true;
        }
    }

    if (valid)
    {
        defaultValue_ = value;
    }
    else
    {
        std::ostringstream message;

        message << "The value '" << value << "' cannot be used as default value for option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "'!";

        throw std::runtime_error(message.str());
    }
}

const std::string & htd_cli::Choice::value(void) const
{
    if (used())
    {
        return htd_cli::SingleValueOption::value();
    }

    return defaultValue_;
}

void htd_cli::Choice::registerValue(const std::string & value)
{
    bool valid = false;

    for (auto it = possibilities_.begin(); !valid && it != possibilities_.end(); ++it)
    {
        if (it->value == value)
        {
            valid = true;
        }
    }

    if (valid)
    {
        htd_cli::SingleValueOption::registerValue(value);
    }
    else
    {
        std::ostringstream message;

        message << "The value '" << value << "' is not a valid choice for the option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "'!";

        throw std::runtime_error(message.str());
    }
}

void htd_cli::Choice::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name_);

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName_);
    }

    parameterDefinition << " <" << valuePlaceholder() << ">";

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description_ << std::endl;

    stream << "   Permitted Values:" << std::endl;

    for (const Possibility & possibility : possibilities_)
    {
        stream << "      .) " << std::left << std::setw(maxPossibilityNameLength_) << possibility.value << "   " << possibility.description;

        if (possibility.value == defaultValue_)
        {
            stream << " (default)";
        }

        stream << std::endl;
    }
}

#endif /* HTD_CLI_CHOICE_CPP */
