/*
 * File:   OptionManager.cpp
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

#ifndef HTD_CLI_OPTIONMANAGER_CPP
#define	HTD_CLI_OPTIONMANAGER_CPP

#include <htd_cli/OptionManager.hpp>

#include <iomanip>
#include <ostream>
#include <sstream>

const std::string htd_cli::OptionManager::GENERAL_SECTION = "General Options";

htd_cli::OptionManager::OptionManager(void) : maxNameLength_(0), sections_(), options_(), observers_(), optionMap_(), sectionMap_()
{

}

htd_cli::OptionManager::~OptionManager(void)
{
    for (htd_cli::Option * option : options_)
    {
        delete option;
    }

    for (htd_cli::IObserver * observer : observers_)
    {
        delete observer;
    }

    options_.clear();

    observers_.clear();
}

void htd_cli::OptionManager::parse(int argc, const char * const * const argv)
{
    for(int i = 1; i < argc; ++i)
    {
        std::string parameter = argv[i];

        if (optionMap_.count(parameter) == 1)
        {
            htd_cli::Option * option = optionMap_.at(parameter);

            if(dynamic_cast<htd_cli::ValueOption *>(option) != nullptr)
            {
                htd_cli::ValueOption * valueOption = static_cast<htd_cli::ValueOption *>(option);

                ++i;

                if(i == argc)
                {
                    std::ostringstream message;

                    message << "Option '" << htd_cli::Option::getCommandLineRepresentation(option->name()) << "' requires an argument!";

                    throw std::runtime_error(message.str());
                }

                valueOption->registerValue(argv[i]);
            }

            option->setUsed();
        }
        else
        {
            std::ostringstream message;

            message << "Option '" << parameter << "\' is not known!";

            throw std::runtime_error(message.str());
        }
    }

    for(htd_cli::IObserver * observer : observers_)
    {
        observer->notify();
    }
}

void htd_cli::OptionManager::registerOption(htd_cli::Option * option, const std::string & section)
{
    const std::string & name = option->name();

    if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890-_") != std::string::npos)
    {
        std::ostringstream message;

        message << "An option name contains invalid characters: " << htd_cli::Option::getCommandLineRepresentation(name);

        throw std::runtime_error(message.str());
    }

    for (htd_cli::Option * existingOption : options_)
    {
        if (hasNameClash(*option, *existingOption))
        {
            std::ostringstream message;

            message << "Name clash detected between to options: " << htd_cli::Option::getCommandLineRepresentation(name);

            if (option->hasShortName())
            {
                message << ", " << htd_cli::Option::getCommandLineRepresentation(option->shortName()) << " ";
            }

            message << " vs. " << htd_cli::Option::getCommandLineRepresentation(existingOption->name());

            if (existingOption->hasShortName())
            {
                message << ", " << htd_cli::Option::getCommandLineRepresentation(existingOption->shortName());
            }

            throw std::runtime_error(message.str());
        }
    }

    if (sectionMap_.count(section) == 0)
    {
        sections_.push_back(section);

        sectionMap_[section] = std::vector<htd_cli::Option *> { option };
    }
    else
    {
        sectionMap_[section].push_back(option);
    }

    optionMap_[htd_cli::Option::getCommandLineRepresentation(name)] = option;

    if (option->hasShortName())
    {
        optionMap_[htd_cli::Option::getCommandLineRepresentation(option->shortName())] = option;
    }

    options_.push_back(option);

    /// The total name length of an option is given by the length
    /// of the name of the option plus at least one leading dash.
    std::size_t nameLength = name.length() + 1;

    if (nameLength > 2)
    {
        /// If the name of the option plus a leading dash is longer
        /// than 2, we require in total two leading dashes before
        /// the option name.
        ++nameLength;

        if (option->hasShortName())
        {
            /// If the option has a short name of length 1, we require that
            /// it has a leading dash and we assume that it is separated
            /// from the option name by the character sequence ", ".
            nameLength += 4;
        }
    }

    if(dynamic_cast<htd_cli::ValueOption *>(option) != nullptr)
    {
        htd_cli::ValueOption * valueOption = static_cast<htd_cli::ValueOption *>(option);

        /// If the option requires an argument, the parameter definition of its usage information
        /// is assumed to contain a placeholder for the argument encapsulated by the character
        /// sequences " <" and ">".
        nameLength += 3 + valueOption->valuePlaceholder().length();
    }

    if (nameLength > maxNameLength_)
    {
        maxNameLength_ = nameLength;
    }
}

void htd_cli::OptionManager::registerObserver(htd_cli::IObserver * observer)
{
    observers_.push_back(observer);
}

void htd_cli::OptionManager::printHelp(std::ostream & stream) const
{
    std::size_t sectionIndex = 0;

    for (const std::string & section : sections_)
    {
        stream << section << ":" << std::endl;

        for (htd_cli::Option * option : sectionMap_.at(section))
        {
            option->printHelp(stream, maxNameLength_);
        }

        if (sectionIndex < sections_.size())
        {
            stream << std::endl;
        }
    }
}

const htd_cli::Option & htd_cli::OptionManager::accessOption(const std::string & name) const
{
    return *(static_cast<htd_cli::Option *>(optionMap_.at(htd_cli::Option::getCommandLineRepresentation(name))));
}

const htd_cli::Choice & htd_cli::OptionManager::accessChoice(const std::string & name) const
{
    return *(static_cast<htd_cli::Choice *>(optionMap_.at(htd_cli::Option::getCommandLineRepresentation(name))));
}

const htd_cli::SingleValueOption & htd_cli::OptionManager::accessSingleValueOption(const std::string & name) const
{
    return *(static_cast<htd_cli::SingleValueOption *>(optionMap_.at(htd_cli::Option::getCommandLineRepresentation(name))));
}

const htd_cli::MultiValueOption & htd_cli::OptionManager::accessMultiValueOption(const std::string & name) const
{
    return *(static_cast<htd_cli::MultiValueOption *>(optionMap_.at(htd_cli::Option::getCommandLineRepresentation(name))));
}

bool htd_cli::OptionManager::hasNameClash(const htd_cli::Option & option1, const htd_cli::Option & option2) const
{
    const std::string & name1 = option1.name();
    const std::string & name2 = option2.name();

    bool ret = name1 == name2;

    if (!ret)
    {
        if (name1.length() == 1)
        {
            ret = option2.hasShortName() && option2.shortName() == name1.at(0);
        }
        else if (name2.length() == 1)
        {
            ret = option1.hasShortName() && option1.shortName() == name2.at(0);
        }
    }

    if (!ret && option1.hasShortName() && option2.hasShortName())
    {
        ret = option1.shortName() == option2.shortName();
    }

    return ret;
}

#endif /* HTD_CLI_OPTIONMANAGER_CPP */
