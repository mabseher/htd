/*
 * File:   OptionManager.hpp
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

#ifndef HTD_CLI_OPTIONMANAGER_HPP
#define HTD_CLI_OPTIONMANAGER_HPP

#include <htd_cli/PreprocessorDefinitions.hpp>
#include <htd_cli/Choice.hpp>
#include <htd_cli/Option.hpp>
#include <htd_cli/MultiValueOption.hpp>
#include <htd_cli/SingleValueOption.hpp>
#include <htd_cli/IObserver.hpp>

#include <ostream>

namespace htd_cli
{
    /**
     *  Manager class for command line options.
     */
    class OptionManager
    {
        public:
            HTD_CLI_API OptionManager(void);

            HTD_CLI_API virtual ~OptionManager();

            /**
             *  Parse options from the command line.
             *
             *  @param[in] argc The number of argumens in argv.
             *  @param[in] argv The argument vector.
             */
            HTD_CLI_API void parse(int argc, const char * const * const argv);

            /**
             *  Register a new option.
             *
             *  @param[in] option   The option which shall be registered.
             *  @param[in] section  The title of the section to which the new option belongs.
             *
             *  @note When calling this method the control over the memory region of the new option is transferred to the option
             *  manager. Deleting the option outside the option manager or inserting the same option object multiple times will
             *  lead to undefined behavior.
             */
            HTD_CLI_API void registerOption(htd_cli::Option * option, const char * const section);

            /**
             *  Register a new observer.
             *
             *  @param[in] observer The observer which shall be registered.
             *
             *  @note When calling this method the control over the memory region of the new observer is transferred to the option
             *  manager. Deleting the observer outside the option manager or inserting the same observer object multiple times will
             *  lead to undefined behavior.
             */
            HTD_CLI_API void registerObserver(htd_cli::IObserver * observer);

            /**
             *  Print the help text of all options to stdout.
             */
            HTD_CLI_API void printHelp(void) const;

            /**
             *  Print the help text of all options.
             *
             *  @param[out] stream  The stream to which the help text shall be written.
             */
            void printHelp(std::ostream & stream) const;

            /**
             *  Access the htd_cli::Option object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::Option object which the given name.
             */
            HTD_CLI_API const htd_cli::Option & accessOption(const char * const name) const;

            /**
             *  Access the htd_cli::Choice object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::Choice object which the given name.
             */
            HTD_CLI_API const htd_cli::Choice & accessChoice(const char * const name) const;

            /**
             *  Access the htd_cli::SingleValueOption object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::SingleValueOption object which the given name.
             */
            HTD_CLI_API const htd_cli::SingleValueOption & accessSingleValueOption(const char * const name) const;

            /**
             *  Access the htd_cli::MultiValueOption object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::MultiValueOption object which the given name.
             */
            HTD_CLI_API const htd_cli::MultiValueOption & accessMultiValueOption(const char * const name) const;

        private:
            struct Implementation;

            std::unique_ptr<Implementation> implementation_;
    };
}

#endif /* HTD_CLI_OPTIONMANAGER_HPP */
