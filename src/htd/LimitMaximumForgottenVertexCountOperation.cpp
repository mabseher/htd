/*
 * File:   LimitMaximumForgottenVertexCountOperation.cpp
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

#ifndef HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP
#define	HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP

#include <htd/Globals.hpp>
#include <htd/LimitMaximumForgottenVertexCountOperation.hpp>

#include <algorithm>
#include <stdexcept>

htd::LimitMaximumForgottenVertexCountOperation::LimitMaximumForgottenVertexCountOperation(std::size_t limit) : limit_(limit)
{
  
}
  
htd::LimitMaximumForgottenVertexCountOperation::~LimitMaximumForgottenVertexCountOperation()
{
  
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutablePathDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container forgetNodes;

    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = decomposition.forgetNodes();

    std::copy(forgetNodeCollection.begin(), forgetNodeCollection.end(), std::back_inserter(forgetNodes));

    for (htd::vertex_t node : forgetNodes)
    {
        htd::vertex_container bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContentVector(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > limit_)
        {
            htd::vertex_container forgottenVertices;

            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(node);

            std::copy(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), std::back_inserter(forgottenVertices));

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / limit_;

            if (intermediatedVertexCount > 0)
            {
                intermediatedVertexCount--;
            }

            if (remainder == 0)
            {
                intermediatedVertexCount--;
            }

            htd::vertex_container children;

            const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

            std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

            if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.end() - limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContentVector(child);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.setBagContent(newNode, newContent);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - limit_;
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContentVector(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.setBagContent(newNode, newContent);

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + limit_)
                        {
                            start = start - limit_;
                            finish = finish - limit_;
                        }
                    }
                }
            }
            else
            {
                throw std::logic_error("void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition &) const");
            }
        }
    }
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition) const
{
    apply(decomposition, std::vector<htd::ILabelingFunction *>());
}

void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition & decomposition, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::vertex_container forgetNodes;

    const htd::ConstCollection<htd::vertex_t> & forgetNodeCollection = decomposition.forgetNodes();

    std::copy(forgetNodeCollection.begin(), forgetNodeCollection.end(), std::back_inserter(forgetNodes));

    for (htd::vertex_t node : forgetNodes)
    {
        htd::vertex_container bagContent;

        const std::vector<htd::vertex_t> & bag = decomposition.bagContentVector(node);

        std::copy(std::begin(bag), std::end(bag), std::back_inserter(bagContent));

        std::size_t forgottenVertexCount = decomposition.forgottenVertexCount(node);

        if (forgottenVertexCount > limit_)
        {
            htd::vertex_container forgottenVertices;

            const htd::ConstCollection<htd::vertex_t> & forgottenVertexCollection = decomposition.forgottenVertices(node);

            std::copy(forgottenVertexCollection.begin(), forgottenVertexCollection.end(), std::back_inserter(forgottenVertices));

            std::size_t remainder = forgottenVertexCount % limit_;

            forgottenVertexCount -= remainder;

            std::size_t intermediatedVertexCount = forgottenVertexCount / limit_;

            if (intermediatedVertexCount > 0)
            {
                intermediatedVertexCount--;
            }

            if (remainder == 0)
            {
                intermediatedVertexCount--;
            }

            htd::vertex_container children;

            const htd::ConstCollection<htd::vertex_t> & childContainer = decomposition.children(node);

            std::copy(childContainer.begin(), childContainer.end(), std::back_inserter(children));

            if (children.size() == 1)
            {
                htd::vertex_t child = children[0];

                auto start = forgottenVertices.end() - limit_;
                auto finish = forgottenVertices.end();

                htd::vertex_t newNode = decomposition.addParent(child);

                std::vector<htd::vertex_t> newContent;

                const std::vector<htd::vertex_t> & bagContent = decomposition.bagContentVector(child);

                std::set_difference(bagContent.begin(), bagContent.end(), start, finish, std::back_inserter(newContent));

                decomposition.setBagContent(newNode, newContent);

                for (auto & labelingFunction : labelingFunctions)
                {
                    htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                    htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                    delete labelCollection;

                    decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                }

                if (intermediatedVertexCount > 0)
                {
                    start = start - limit_;
                    finish = finish - limit_;

                    for (htd::index_t index = 0; index < intermediatedVertexCount; index++)
                    {
                        const std::vector<htd::vertex_t> & bagContent2 = decomposition.bagContentVector(newNode);

                        newNode = decomposition.addParent(newNode);

                        newContent.clear();

                        std::set_difference(bagContent2.begin(), bagContent2.end(), start, finish, std::back_inserter(newContent));

                        decomposition.setBagContent(newNode, newContent);

                        for (auto & labelingFunction : labelingFunctions)
                        {
                            htd::ILabelCollection * labelCollection = decomposition.labelings().exportVertexLabelCollection(newNode);

                            htd::ILabel * newLabel = labelingFunction->computeLabel(newContent, *labelCollection);

                            delete labelCollection;

                            decomposition.setVertexLabel(labelingFunction->name(), newNode, newLabel);
                        }

                        if (index < forgottenVertexCount + limit_)
                        {
                            start = start - limit_;
                            finish = finish - limit_;
                        }
                    }
                }
            }
            else
            {
                throw std::logic_error("void htd::LimitMaximumForgottenVertexCountOperation::apply(htd::IMutableTreeDecomposition &) const");
            }
        }
    }
}

htd::LimitMaximumForgottenVertexCountOperation * htd::LimitMaximumForgottenVertexCountOperation::clone(void) const
{
    return new htd::LimitMaximumForgottenVertexCountOperation(limit_);
}

#endif /* HTD_HTD_LIMITMAXIMUMFORGOTTENVERTEXCOUNTOPERATION_CPP */
