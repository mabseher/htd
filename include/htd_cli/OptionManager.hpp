/*
 * File:   OptionManager.hpp
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

#ifndef HTD_CLI_OPTIONMANAGER_HPP
#define	HTD_CLI_OPTIONMANAGER_HPP

#include <htd_cli/Choice.hpp>
#include <htd_cli/Option.hpp>
#include <htd_cli/MultiValueOption.hpp>
#include <htd_cli/SingleValueOption.hpp>
#include <htd_cli/IObserver.hpp>

#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace htd_cli
{
    /**
     *  Manager class for command line options.
     */
    class OptionManager
    {
        public:
            /**
             *  The title of the main section.
             */
            static const std::string GENERAL_SECTION;

            OptionManager(void);

            virtual ~OptionManager();

            /**
             *  Parse options from the command line.
             *
             *  @param[in] argc The number of argumens in argv.
             *  @param[in] argv The argument vector.
             */
            void parse(int argc, const char * const * const argv);

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
            void registerOption(htd_cli::Option * option, const std::string & section = GENERAL_SECTION);

            /**
             *  Register a new observer.
             *
             *  @param[in] observer The observer which shall be registered.
             *
             *  @note When calling this method the control over the memory region of the new observer is transferred to the option
             *  manager. Deleting the observer outside the option manager or inserting the same observer object multiple times will
             *  lead to undefined behavior.
             */
            void registerObserver(htd_cli::IObserver * observer);

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
            const htd_cli::Option & accessOption(const std::string & name) const;

            /**
             *  Access the htd_cli::Choice object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::Choice object which the given name.
             */
            const htd_cli::Choice & accessChoice(const std::string & name) const;

            /**
             *  Access the htd_cli::SingleValueOption object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::SingleValueOption object which the given name.
             */
            const htd_cli::SingleValueOption & accessSingleValueOption(const std::string & name) const;

            /**
             *  Access the htd_cli::MultiValueOption object which the given name.
             *
             *  @param[in] name The name of the object which shall be accessed.
             *
             *  @return A reference to the htd_cli::MultiValueOption object which the given name.
             */
            const htd_cli::MultiValueOption & accessMultiValueOption(const std::string & name) const;

        private:
            std::size_t maxNameLength_;

            std::vector<std::string> sections_;

            std::vector<htd_cli::Option *> options_;

            std::vector<htd_cli::IObserver *> observers_;

            std::unordered_map<std::string, htd_cli::Option *> optionMap_;

            std::unordered_map<std::string, std::vector<htd_cli::Option *>> sectionMap_;

            bool hasNameClash(const htd_cli::Option & option1, const htd_cli::Option & option2) const;
    };
}

#endif /* HTD_CLI_OPTIONMANAGER_HPP */
