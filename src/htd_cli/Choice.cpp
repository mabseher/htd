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

#include <cstring>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 *  Private implementation details of class htd_cli::MultiValueOption.
 */
struct htd_cli::Choice::Implementation
{
    /**
     *  Constructor for the implementation details structure.
     */
    Implementation(void) : defaultValue_(new char[1] { '\0' }), maxPossibilityNameLength_(0), possibilities_()
    {

    }

    virtual ~Implementation()
    {
        delete[] defaultValue_;

        for (Possibility * possibility : possibilities_)
        {
            delete possibility;
        }
    }

    /**
     *  Internal structure for the possibilities which one can choose from.
     */
    struct Possibility
    {
        /**
         *  Constructor for a new choice possibility.
         *
         *  @param[in] value        The value which can be selected.
         *  @param[in] description  The description of the choice possibility.
         */
        Possibility(const char * const value, const char * const description) : value_(new char[std::strlen(value) + 1]), description_(new char[std::strlen(description) + 1])
        {
            std::strncpy(value_, value, std::strlen(value) + 1);

            std::strncpy(description_, description, std::strlen(description) + 1);
        }

        ~Possibility()
        {
            delete[] value_;
            delete[] description_;
        }

        /**
         *  The value which can be selected.
         */
        char * value_;

        /**
         *  The description of the choice possibility.
         */
        char * description_;
    };

    /**
     *  The default value of the choice option.
     */
    char * defaultValue_;

    /**
     *  The maximum length of the name of a possibility. This value is used for aligning the help texts properly.
     */
    std::size_t maxPossibilityNameLength_;

    /**
     *  The available possibilities for the choice option.
     */
    std::vector<Possibility *> possibilities_;
};

htd_cli::Choice::Choice(const char * const name, const char * const description, const char * const valuePlaceholder) : htd_cli::SingleValueOption::SingleValueOption(name, description, valuePlaceholder), implementation_(new Implementation())
{

}

htd_cli::Choice::Choice(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName) : htd_cli::SingleValueOption::SingleValueOption(name, description, valuePlaceholder, shortName), implementation_(new Implementation())
{

}

htd_cli::Choice::~Choice()
{

}

void htd_cli::Choice::addPossibility(const char * const value, const char * const description)
{
    std::size_t size = std::strlen(value);

    for (const Implementation::Possibility * const possibility : implementation_->possibilities_)
    {
        if (size == std::strlen(possibility->value_) && std::strncmp(value, possibility->value_, size) == 0)
        {
            std::ostringstream message;

            message << "Name clash detected between possibilities of option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "': Possibility '" << value << "'";

            throw std::runtime_error(message.str());
        }
    }

    if (size > implementation_->maxPossibilityNameLength_)
    {
        implementation_->maxPossibilityNameLength_ = std::strlen(value);
    }

    implementation_->possibilities_.emplace_back(new Implementation::Possibility(value, description));
}

bool htd_cli::Choice::hasDefaultValue(void)
{
    return std::strlen(implementation_->defaultValue_) > 0;
}

void htd_cli::Choice::setDefaultValue(const char * const value)
{
    bool valid = false;

    std::size_t size = std::strlen(value);

    for (auto it = implementation_->possibilities_.begin(); !valid && it != implementation_->possibilities_.end(); ++it)
    {
        const Implementation::Possibility & possibility = **it;

        if (size == std::strlen(possibility.value_) && std::strncmp(value, possibility.value_, size) == 0)
        {
            valid = true;
        }
    }

    if (valid)
    {
        delete[] implementation_->defaultValue_;

        implementation_->defaultValue_ = new char[size + 1];

        std::strncpy(implementation_->defaultValue_, value, size + 1);
    }
    else
    {
        std::ostringstream message;

        message << "The value '" << value << "' cannot be used as default value for option '" << htd_cli::Option::getCommandLineRepresentation(name()) << "'!";

        throw std::runtime_error(message.str());
    }
}

const char * htd_cli::Choice::value(void) const
{
    if (used())
    {
        return htd_cli::SingleValueOption::value();
    }

    return implementation_->defaultValue_;
}

void htd_cli::Choice::registerValue(const char * const value)
{
    bool valid = false;

    std::size_t size = std::strlen(value);

    for (auto it = implementation_->possibilities_.begin(); !valid && it != implementation_->possibilities_.end(); ++it)
    {
        const Implementation::Possibility & possibility = **it;

        if (size == std::strlen(possibility.value_) && std::strncmp(value, possibility.value_, size) == 0)
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

    parameterDefinition << htd_cli::Option::getCommandLineRepresentation(name());

    if (hasShortName())
    {
        parameterDefinition << ", " << htd_cli::Option::getCommandLineRepresentation(shortName());
    }

    parameterDefinition << " <" << valuePlaceholder() << ">";

    stream << std::left << std::setw(maxNameLength) << parameterDefinition.str() << "   " << description() << std::endl;

    stream << "   Permitted Values:" << std::endl;

    for (const Implementation::Possibility * const possibility : implementation_->possibilities_)
    {
        stream << "      .) " << std::left << std::setw(implementation_->maxPossibilityNameLength_) << possibility->value_ << "   " << possibility->description_;

        if (std::strlen(possibility->value_) == std::strlen(implementation_->defaultValue_) && std::strncmp(possibility->value_, implementation_->defaultValue_, std::strlen(possibility->value_)) == 0)
        {
            stream << " (default)";
        }

        stream << std::endl;
    }
}

#endif /* HTD_CLI_CHOICE_CPP */
