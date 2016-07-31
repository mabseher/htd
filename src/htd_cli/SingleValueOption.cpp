/*
 * File:   SingleValueOption.cpp
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

#ifndef HTD_CLI_SINGLEVALUEOPTION_CPP
#define	HTD_CLI_SINGLEVALUEOPTION_CPP

#include <htd_cli/SingleValueOption.hpp>

#include <cstring>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>

/**
 *  Private implementation details of class htd_cli::SingleValueOption.
 */
struct htd_cli::SingleValueOption::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     */
    Implementation(void) : value_(new char[1] { '\0' })
    {

    }

    virtual ~Implementation()
    {
        delete[] value_;
    }

    char * value_;
};

htd_cli::SingleValueOption::SingleValueOption(const char * const name, const char * const description, const char * const valuePlaceholder) : htd_cli::ValueOption(name, description, valuePlaceholder), implementation_(new Implementation())
{

}

htd_cli::SingleValueOption::SingleValueOption(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName) : htd_cli::ValueOption(name, description, valuePlaceholder, shortName), implementation_(new Implementation())
{

}

htd_cli::SingleValueOption::~SingleValueOption()
{

}

const char * htd_cli::SingleValueOption::value(void) const
{
    return implementation_->value_;
}

void htd_cli::SingleValueOption::registerValue(const char * const value)
{
    if (used() && (std::strlen(value) != std::strlen(implementation_->value_) || std::strncmp(value, implementation_->value_, std::strlen(value)) != 0))
    {
        std::ostringstream message;

        message << "The option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "' takes only a single argument!";

        throw std::runtime_error(message.str());
    }

    delete[] implementation_->value_;

    std::size_t size = std::strlen(value);

    implementation_->value_ = new char[size + 1];

    std::strncpy(implementation_->value_, value, size + 1);

    setUsed();
}

void htd_cli::SingleValueOption::printHelp(std::ostream & stream, std::size_t maxNameLength) const
{
    std::ostringstream parameterDefinition;

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name());

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName());
    }

    parameterDefinition << " <" << valuePlaceholder() << ">";

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description() << std::endl;
}

#endif /* HTD_CLI_SINGLEVALUEOPTION_CPP */
