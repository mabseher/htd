/*
 * File:   Label.hpp
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

#ifndef HTD_HTD_LABEL_HPP
#define HTD_HTD_LABEL_HPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>
#include <htd/ILabel.hpp>

#include <memory>
#include <stdexcept>

namespace htd
{
    /**
     *  Default implementation of the ILabel interface.
     */
    template<typename T>
    class Label : public htd::ILabel
    {
        public:
            /**
             *  Constructor for a label.
             *
             *  @param[in] value    The value of the label.
             */
            Label(T value) : value_(std::make_shared<T>(value))
            {

            }

            /**
             *  Copy constructor for a label.
             *
             *  @param[in] original  The original label.
             */
            Label(const Label<T> & original) : value_(std::make_shared<T>(*(original.value_)))
            {

            }

            /**
             *  Move constructor for a label.
             *
             *  @param[in] original  The original label.
             */
            Label(Label<T> && original) : value_(std::move(original.value_))
            {

            }

            /**
             *  Destructor for a Label object.
             */
            virtual ~Label()
            {

            }

            /**
             *  Getter for the value of the label.
             *
             *  @return The value of the label.
             */
            const T & value() const
            {
                return *value_;
            }

            std::size_t hash(void) const HTD_OVERRIDE
            {
                std::hash<T> hash_function;

                return hash_function(*value_);
            }

            Label<T> * clone(void) const HTD_OVERRIDE
            {
                return new Label<T>(*value_);
            }

            /**
             *  Copy assignment operator for a label.
             *
             *  @param[in] original  The original label.
             */
            Label<T> & operator=(const Label<T> & original) const
            {
                value_ = original.value_;

                return *this;
            }

            /**
             *  Move assignment operator for a label.
             *
             *  @param[in] original  The original label.
             */
            Label<T> & operator=(Label<T> && original) const
            {
                value_ = std::move(original.value_);

                return *this;
            }

            /**
             *  Equality operator for a label.
             *
             *  @param[in] rhs  The label at the right-hand side of the operator.
             *
             *  @return True if the label value is equal to the value of the label at the right-hand side of the operator, false otherwise.
             */
            bool operator==(const Label<T> & rhs) const
            {
                return *value_ == rhs.value();
            }

            bool operator==(const htd::ILabel & rhs) const HTD_OVERRIDE
            {
                 const Label<T> * o = dynamic_cast<const Label<T> *>(&rhs);

                 return o != nullptr && *value_ == o->value();
            }

            void print(std::ostream & stream) const HTD_OVERRIDE
            {
                stream << *value_;
            }

        private:
            std::shared_ptr<T> value_;
    };

    template<typename OutputType>
    const OutputType & accessLabel(const htd::ILabel & input)
    {
        return static_cast<const htd::Label<OutputType> *>(&input)->value();
    }
}

#endif /* HTD_HTD_LABEL_HPP */
