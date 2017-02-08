/*
 * File:   ValueOption.hpp
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

#ifndef HTD_CLI_VALUEOPTION_HPP
#define HTD_CLI_VALUEOPTION_HPP

#include <htd_cli/Option.hpp>

namespace htd_cli
{
    /**
     *  Class for the definition of command line options which take an argument.
     */
    class ValueOption : public htd_cli::Option
    {
        public:
            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            ValueOption(const char * const name, const char * const description, const char * const valuePlaceholder);

            /**
             *  Constructor for a command line option.
             *
             *  @param[in] name             The name of the command line option.
             *  @param[in] description      The description of the command line option.
             *  @param[in] shortName        The abbreviated name of the option which acts as an alias for the option name.
             *  @param[in] valuePlaceholder The placeholder for the argument which shall be used in the help text.
             */
            ValueOption(const char * const name, const char * const description, const char * const valuePlaceholder, char shortName);

            virtual ~ValueOption();

            /**
             *  Register the given value representing the option's argument.
             *
             *  @param[in] value    The value which shall be registered.
             */
            virtual void registerValue(const char * const value) = 0;

            /**
             *  Getter for the argument's placeholder which shall be used in the help text.
             *
             *  @return The argument's placeholder which shall be used in the help text.
             */
            const char * valuePlaceholder(void) const;

        private:
            std::string valuePlaceholder_;
    };
}

#endif /* HTD_CLI_VALUEOPTION_HPP */
