/*
 * File:   GraphTypeFactory.hpp
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

#ifndef HTD_HTD_GRAPHTYPEFACTORY_HPP
#define HTD_HTD_GRAPHTYPEFACTORY_HPP

#include <htd/Globals.hpp>
#include <htd/LibraryInstance.hpp>

namespace htd
{
    /**
     *  Template class providing uniform structure for graph factory classes.
     */
    template <typename GraphType, typename MutableGraphType>
    class GraphTypeFactory
    {
        public:
            /**
             *  Constructor for the factory class.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the default implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] constructionTemplate The default implementation of the interface MutableGraphType.
             */
            GraphTypeFactory(MutableGraphType * constructionTemplate) : managementInstance_(constructionTemplate->managementInstance()), constructionTemplate_(constructionTemplate)
            {

            }

            /**
             *  Copy constructor for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            GraphTypeFactory(const htd::GraphTypeFactory<GraphType, MutableGraphType> & original) = delete;

            /**
             *  Copy assignment operator for the factory class.
             *
             *  @param[in] original The original factory class which shall be copied.
             */
            GraphTypeFactory & operator=(const htd::GraphTypeFactory<GraphType, MutableGraphType> & original) = delete;

            /**
             *  Destructor of the factory class.
             */
            virtual ~GraphTypeFactory()
            {
                delete constructionTemplate_;
            }

            /**
             *  Create a new object of type MutableGraphType.
             *
             *  @return A new object of type MutableGraphType.
             */
            virtual MutableGraphType * createInstance(void) const = 0;

            /**
             *  Create a new object of type MutableGraphType.
             *
             *  @param[in] original The original graph acting as template for the created graph.
             *
             *  @return A new object of type MutableGraphType identical to the given original graph.
             */
            MutableGraphType * createInstance(const GraphType & original) const
            {
                MutableGraphType * ret = createInstance();

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
                *ret = original;
#else
                ret->assign(original);
#endif

                return ret;
            }

            /**
             *  Set the default implementation of the interface MutableGraphType.
             *
             *  @note When calling this method the control over the memory regions of the object instance of the original implementation
             *  is transferred to the factory class. Deleting the object instance provided to this method outside the factory class or
             *  assigning the same object instance multiple times will lead to undefined behavior.
             *
             *  @param[in] original The new default implementation of the interface MutableGraphType.
             */
            void setConstructionTemplate(MutableGraphType * original)
            {
                HTD_ASSERT(original != nullptr)
                HTD_ASSERT(original->vertexCount() == 0)

                delete constructionTemplate_;

                constructionTemplate_ = original;

                constructionTemplate_->setManagementInstance(managementInstance_);
            }

            /**
             *  Access the mutable interface of a given graph.
             *
             *  @param[in] graph    The graph whose mutable interface shall be accessed.
             *
             *  @return The mutable interface of the given graph.
             */
            MutableGraphType & accessMutableInstance(GraphType & graph) const
            {
                return *(dynamic_cast<MutableGraphType *>(&graph));
            }

            /**
             *  Access the mutable interface of a given graph.
             *
             *  @param[in] graph    The graph whose mutable interface shall be accessed.
             *
             *  @return The mutable interface of the given graph.
             */
            const MutableGraphType & accessMutableInstance(const GraphType & graph) const
            {
                return *(dynamic_cast<const MutableGraphType *>(&graph));
            }

        protected:
            /**
             *  The management instance to which the current object instance belongs.
             */
            const htd::LibraryInstance * managementInstance_;

            /**
             *  A pointer to a clean instance of the default implementation.
             */
            MutableGraphType * constructionTemplate_;
    };
}

#endif /* HTD_HTD_GRAPHTYPEFACTORY_HPP */
