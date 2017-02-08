/*
 * File:   Choice.hpp
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

#ifndef HTD_CLI_CHOICE_HPP
#define HTD_CLI_CHOICE_HPP

#include <htd_cli/SingleValueOption.hpp>

namespace htd_cli
{
    /**
     *  Class for the definition of command line options which take a single argument from a given list of options.
     */
    class Choice : public htd_cli::SingleValueOption
    {
        public:
            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            HTD_CLI_API Choice(const char * const name, const char * const description, const char * const valuePlaceholder);

            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] shortName        The abbreviated name of the option which acts as an alias for the option name.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            HTD_CLI_API Choice(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName);

            HTD_CLI_API virtual ~Choice();

            /**
             *  Add a new possibility one can choose from.
             *
             *  @param[in] value        The value which shall be added as new possibility.
             *  @param[in] description  The description of the new possibility.
             */
            HTD_CLI_API void addPossibility(const char * const value, const char * const description);

            /**
             *  Check whether the htd_cli::Choice object has a default value.
             *
             *  @return True if the htd_cli::Choice object has a default value, false otherwise.
             */
            HTD_CLI_API bool hasDefaultValue(void);

            /**
             *  Set the default value of the htd_cli::Choice object.
             *
             *  @param[in] value    The value of one of the added possibilities which shall be used as the new default value.
             */
            HTD_CLI_API void setDefaultValue(const char * const value);

            HTD_CLI_API const char * value(void) const HTD_OVERRIDE;

            HTD_CLI_API void registerValue(const char * const value) HTD_OVERRIDE;

            void printHelp(std::ostream & stream, std::size_t maxNameLength) const HTD_OVERRIDE;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_CLI_CHOICE_HPP */
