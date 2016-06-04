/*
 * File:   MultiValueOption.hpp
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

#ifndef HTD_CLI_MULTIVALUEOPTION_HPP
#define	HTD_CLI_MULTIVALUEOPTION_HPP

#include <htd_cli/ValueOption.hpp>

#include <htd/Globals.hpp>

#include <vector>

namespace htd_cli
{
    /**
     *  Class for the definition of command line options which take multiple arguments.
     */
    class MultiValueOption : public htd_cli::ValueOption
    {
        public:
            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder);

            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] shortName        The abbreviated name of the option which acts as an alias for the option name.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            MultiValueOption(const std::string & name, const std::string & description, const std::string & valuePlaceholder, char shortName);

            ~MultiValueOption();

            /**
             *  Getter for the argument values assigned to the option.
             *
             *  @return The argument values assigned to the option.
             */
            const std::vector<std::string> & values(void) const;

            /**
             *  Register the given value representing the option's argument.
             *
             *  The new value will be added to the previous ones and the getter htd::MultiValueOption::used() will return true after calling this method.
             *
             *  @param[in] value    The value which shall be registered.
             */
            void registerValue(const std::string & value) HTD_OVERRIDE;

            void printHelp(std::ostream & stream, std::size_t maxNameLength) const HTD_OVERRIDE;

        private:
            std::vector<std::string> values_;
    };
}

#endif /* HTD_CLI_MULTIVALUEOPTION_HPP */
