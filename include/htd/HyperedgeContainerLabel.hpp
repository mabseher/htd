/*
 * File:   HyperedgeContainerLabel.hpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
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

#ifndef HTD_HTD_HYPEREDGECONTAINERLABEL_HPP
#define	HTD_HTD_HYPEREDGECONTAINERLABEL_HPP

#include <htd/Globals.hpp>
#include <htd/ILabel.hpp>
#include <htd/Iterator.hpp>

namespace htd
{
    class HyperedgeContainerLabel : public virtual htd::ILabel
    {
        public:
            HyperedgeContainerLabel(void);

            HyperedgeContainerLabel(const htd::hyperedge_container & data);

            HyperedgeContainerLabel(const htd::Iterator<htd::hyperedge_t> begin, const htd::Iterator<htd::hyperedge_t> end);

            ~HyperedgeContainerLabel();

            std::size_t hash(void) const HTD_OVERRIDE;

            HyperedgeContainerLabel * clone(void) const HTD_OVERRIDE;

            bool operator==(const htd::ILabel & other) const HTD_OVERRIDE;

            bool operator==(const HyperedgeContainerLabel & other) const;

            std::size_t size(void) const;

            htd::hyperedge_container & container(void);

            const htd::hyperedge_container & container(void) const;

        private:
            htd::hyperedge_container container_;
    };
}

#endif /* HTD_HTD_HYPEREDGECONTAINERLABEL_HPP */
