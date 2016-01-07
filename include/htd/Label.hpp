/*
 * File:   Label.hpp
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

#ifndef HTD_HTD_LABEL_HPP
#define	HTD_HTD_LABEL_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/ILabel.hpp>

#include <memory>

namespace htd
{
    template<typename T>
    class Label : public virtual htd::ILabel
    {
        public:
            Label(T value) : value_(std::make_shared<T>(value))
            {

            }

            Label(const Label<T> & original) : value_(std::make_shared<T>(original.value()))
            {

            }

            ~Label()
            {

            }

            const T & value() const
            {
                return *value_;
            }

            std::size_t hash(void) const
            {
                std::hash<T> hash_function;

                return hash_function(*value_);
            }

            bool operator==(const htd::ILabel & other) const
            {
                 const Label<T> * o = dynamic_cast<const Label<T> *>(&other);

                 return o != nullptr && *value_ == o->value();
            }

            bool operator==(const Label<T> & other) const
            {
                return *value_ == other.value();
            }

            Label<T> * clone(void) const
            {
                return new Label<T>(*value_);
            }

            std::string toString(void) const
            {
                //TODO Implement

                return "";
            }

        private:
            std::shared_ptr<T> value_;
    };
}

#endif /* HTD_HTD_LABEL_HPP */
