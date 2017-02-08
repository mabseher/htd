/*
 * File:   Option.hpp
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

#ifndef HTD_CLI_OPTION_HPP
#define HTD_CLI_OPTION_HPP

#include <htd_cli/PreprocessorDefinitions.hpp>

#include <htd/Globals.hpp>

#include <memory>
#include <string>

namespace htd_cli
{
    /**
     *  Class for the definition of command line options.
     */
    class Option
    {
        public:
            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name         The name of the command line option.
             *  @param[in] description  The description of the command line option.
             *  @param[in] shortName    The abbreviated name of the option which acts as an alias for the option name.
             */
            HTD_CLI_API Option(const char * const name, const char * const description, char shortName = '\0');

            HTD_CLI_API virtual ~Option();

            /**
             *  Getter for the name of the command line option.
             *
             *  @return The name of the command line option.
             */
            HTD_CLI_API const char * name(void) const;

            /**
             *  Getter for the description of the command line option.
             *
             *  @return The description of the command line option.
             */
            HTD_CLI_API const char * description(void) const;

            /**
             *  Check whether the option has a short name.
             *
             *  @return True if the option has a short name, false otherwise.
             */
            HTD_CLI_API bool hasShortName(void) const;

            /**
             *  Getter for the abbreviated name of the option which acts as an alias for the option name.
             *
             *  @return The abbreviated name of the option which acts as an alias for the option name.
             */
            HTD_CLI_API char shortName(void) const;

            /**
             *  Check whether the option was provided via a command line argument.
             *
             *  @return True if the option was provided via a command line argument, false otherwise.
             */
            HTD_CLI_API bool used(void) const;

            /**
             *  Set a flag indicating that the option was provided via a command line argument.
             */
            HTD_CLI_API void setUsed(void);

            /**
             *  Print the help text for the option.
             *
             *  @param[out] stream          The stream to which the help text shall be written.
             *  @param[in] maxNameLength    The maximum length of all option names to allow correct indenting.
             */
            virtual void printHelp(std::ostream & stream, std::size_t maxNameLength = 0) const;

            /**
             *  Get the command line representation of the given option name by putting a single dash ('-') character in front of the name.
             *
             *  @param[in] name The name which shall be converted to its command line representation.
             *
             *  @return The command line representation of the given option name.
             */
            static std::string getCommandLineRepresentation(char name);

            /**
             *  Get the command line representation of the given option name by putting one or two dash ('-') characters in front of the name.
             *  Whether one or two dash characters are used depends on the length of the option name: When the name length is 1, only a single
             *  dash is added, otherwise two dash characters will be added.
             *
             *  @param[in] name The name which shall be converted to its command line representation.
             *
             *  @return The command line representation of the given option name.
             */
            static std::string getCommandLineRepresentation(const std::string & name);

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_CLI_OPTION_HPP */
