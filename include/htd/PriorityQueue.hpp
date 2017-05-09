/* 
 * File:   PriorityQueue.hpp
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

#ifndef HTD_HTD_PRIORITYQUEUE_HPP
#define HTD_HTD_PRIORITYQUEUE_HPP

#include <htd/Globals.hpp>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace htd
{
    /**
     *  Flexible priority queue allowing to efficiently access values of identical priority.
     */
    template < typename ValueType, typename PriorityType, typename Compare = std::less<PriorityType> >
    class PriorityQueue
    {
        public:
            /**
             *  Constructor of a new priority queue.
             */
            PriorityQueue(void) : compare_(), heap_(), priorityMap_(), size_(0)
            {

            }

            /**
             *  Destructor of a priority queue.
             */
            ~PriorityQueue(void)
            {

            }

            /**
             *  Check whether the priority queue is emtpy.
             *
             *  @return True if the priority queue is empty, false otherwise.
             */
            bool empty(void) const
            {
                return size_ == 0;
            }

            /**
             *  Getter for the number of elements in the priority queue.
             *
             *  @return The number of elements in the priority queue.
             */
            std::size_t size(void) const
            {
                return size_;
            }

            /**
             *  Access the top element.
             *
             *  @return The top element.
             */
            const ValueType & top(void) const
            {
                HTD_ASSERT(size_ > 0)

                return topCollection()[0];
            }

            /**
             *  Access the top priority.
             *
             *  @return The top priority.
             */
            const PriorityType & topPriority(void) const
            {
                HTD_ASSERT(size_ > 0)

                return heap_[0].first;
            }

            /**
             *  Access the collection of elements with top priority.
             *
             *  @return The collection of elements with top priority.
             */
            const std::vector<ValueType> & topCollection(void) const
            {
                HTD_ASSERT(size_ > 0)

                return *(heap_[0].second);
            }

            /**
             *  Insert a new element with the given priority.
             *
             *  @param[in] value    The element which shall be inserted.
             *  @param[in] priority The priority of the element which shall be inserted.
             */
            void push(const ValueType & value, const PriorityType & priority)
            {
                htd::index_t currentPosition = heap_.size();

                if (currentPosition == 0)
                {
                    heap_.emplace_back(priority, new std::vector<ValueType> { value });

                    priorityMap_.emplace(priority, currentPosition);
                }
                else
                {
                    if (!insert(value, priority))
                    {
                        heap_.emplace_back(priority, new std::vector<ValueType>());

                        priorityMap_.emplace(priority, currentPosition);

                        siftUp(currentPosition, value, priority);
                    }
                }

                ++size_;
            }

            /**
             *  Remove the top element.
             */
            void pop(void)
            {
                HTD_ASSERT(size_ > 0)

                std::vector<ValueType> & relevantCollection = *(heap_[0].second);

                if (relevantCollection.size() > 1)
                {
                    relevantCollection.erase(relevantCollection.begin());
                }
                else
                {
                    eraseCollection(0);
                }

                --size_;
            }

            /**
             *  Erase the specific element.
             *
             *  @param[in] value    The element which shall be deleted.
             *
             *  @return True if the element was successfully erased, false otherwise.
             */
            bool erase(const ValueType & value)
            {
                bool ret = false;

                for (auto it = heap_.begin(); !ret && it != heap_.end(); ++it)
                {
                    std::vector<ValueType> & currentCollection = *(it->second);

                    auto position = currentCollection.begin();

                    while (!ret && position != currentCollection.end())
                    {
                       if (compare_(value, *position) || compare_(*position, value))
                       {
                           ++position;
                       }
                       else
                       {
                           ret = true;
                       }
                    }

                    if (ret)
                    {
                        if (currentCollection.size() > 1)
                        {
                            currentCollection.erase(position);
                        }
                        else
                        {
                            eraseCollection(std::distance(heap_.begin(), it));
                        }

                        --size_;
                    }
                }

                return ret;
            }

            /**
             *  Erase the specific element from the collection of elements with the given priority.
             *
             *  @param[in] value    The element which shall be deleted.
             *  @param[in] priority The priority of the element which shall be deleted.
             *
             *  @return True if the element was successfully erased from the collection of elements with the given priority, false otherwise.
             */
            bool erase(const ValueType & value, const PriorityType & priority)
            {
                bool ret = false;

                auto position = locate(priority);

                if (position != heap_.end())
                {
                    std::vector<ValueType> & collection = *(position->second);

                    auto currentPosition = collection.begin();

                    while (!ret && currentPosition != collection.end())
                    {
                       if (compare_(value, *currentPosition) || compare_(*currentPosition, value))
                       {
                           ++currentPosition;
                       }
                       else
                       {
                           ret = true;
                       }
                    }

                    if (ret)
                    {
                        if (collection.size() > 1)
                        {
                            collection.erase(currentPosition);
                        }
                        else
                        {
                            eraseCollection(std::distance(heap_.begin(), position));
                        }

                        --size_;
                    }
                }

                return ret;
            }

            /**
             *  Erase the specific element from the top collection.
             *
             *  @param[in] value    The element which shall be deleted.
             *
             *  @return True if the element was successfully erased from the top collection, false otherwise.
             */
            bool eraseFromTopCollection(const ValueType & value)
            {
                bool ret = false;

                if (size_ > 0)
                {
                    std::vector<ValueType> & currentCollection = *(heap_[0].second);

                    auto position = currentCollection.begin();

                    while (!ret && position != currentCollection.end())
                    {
                       if (compare_(value, *position) || compare_(*position, value))
                       {
                           ++position;
                       }
                       else
                       {
                           ret = true;
                       }
                    }

                    if (ret)
                    {
                        if (currentCollection.size() > 1)
                        {
                            currentCollection.erase(position);
                        }
                        else
                        {
                            eraseCollection(0);
                        }

                        --size_;
                    }
                }

                return ret;
            }

        private:
            /**
             *  A comparison operator on which the heap is based.
             */
            Compare compare_;

            /**
             *  The data structure underlying the priority queue.
             */
            std::vector<std::pair<PriorityType, std::vector<ValueType> *>> heap_;

            /**
             *  A map for fast lookup of the position of elements within the heap.
             */
            std::unordered_map<PriorityType, htd::index_t> priorityMap_;

            /**
             *  The number of elements stored on the heap.
             */
            std::size_t size_;

            /**
             *  Try to locate the position of the collection of elements with a specific priority on the heap.
             *
             *  @note If the specific priority is not yet present on the heap, the result of calling this function is equal to heap_.end().
             *
             *  @param[in] priority The priority of the collection of elements which shall be located.
             *
             *  @return An iterator to the collection of elements with the specific priority on the heap.
             */
            typename std::vector<std::pair<PriorityType, std::vector<ValueType> *>>::iterator locate(const PriorityType & priority)
            {
                typename std::vector<std::pair<PriorityType, std::vector<ValueType> *>>::iterator ret = heap_.end();

                auto position = priorityMap_.find(priority);

                if (position != priorityMap_.end())
                {
                    ret = heap_.begin() + position->second;
                }

                return ret;
            }

            /**
             *  Try to insert a new element with a specific priority.
             *
             *  @param[in] value    The element which shall be inserted.
             *  @param[in] priority The priority of the element which shall be inserted.
             *
             *  @return True if a collection of elements with the given priority already existed and the value was successfully inserted into the respective collection, false otherwise.
             */
            bool insert(const ValueType & value, const PriorityType & priority)
            {
                bool ret = false;

                auto position = locate(priority);

                if (position != heap_.end())
                {
                    position->second->push_back(value);

                    ret = true;
                }

                return ret;
            }

            /**
             *  Erase the collection of elements at the specific position.
             *
             *  @param[in] position The position of the collection of elements which shall be deleted.
             */
            void eraseCollection(htd::index_t position)
            {
                HTD_ASSERT(position < heap_.size())

                ValueType value = heap_[position].first;

                std::size_t heapSize = heap_.size() - 1;

                delete heap_[position].second;

                if (position == heapSize)
                {
                    heap_.erase(heap_.begin() + position);
                }
                else
                {
                    std::pair<PriorityType, std::vector<ValueType> *> movedElement(std::move(heap_[heapSize]));

                    heap_.erase(heap_.begin() + heapSize);

                    siftDown(position, movedElement.second, movedElement.first);

                    if (!compare_(heap_[position].first, movedElement.first) && !compare_(movedElement.first, heap_[position].first))
                    {
                        siftUp(position, movedElement.second, movedElement.first);
                    }
                }

                priorityMap_.erase(value);
            }

            /**
             *  Insert an element with a specific priority at the given position.
             *
             *  @note The heap invariant is preserved by promoting the element up the tree repeatedly
             *  until the specific priority is less than or equal to the priority of its parent or it
             *  is the root of the tree.
             *
             *  @param[in] position The position at which the collection of elements shall be inserted.
             *  @param[in] values   The collection of elements which shall be inserted.
             *  @param[in] priority The priority of each of the inserted elements.
             */
            void siftUp(htd::index_t position, const ValueType & value, const PriorityType & priority)
            {
                bool found = false;

                while (!found && position > 0)
                {
                    htd::index_t parent = (position - 1) >> 1;

                    const PriorityType & parentPriority = heap_[parent].first;

                    if (!compare_(parentPriority, priority))
                    {
                        found = true;
                    }
                    else
                    {
                        std::swap(priorityMap_[heap_[position].first], priorityMap_[heap_[parent].first]);

                        heap_[position].swap(heap_[parent]);

                        position = parent;
                    }
                }

                heap_[position].second->push_back(value);
            }

            /**
             *  Insert the collection of elements with a specific priority at the given position.
             *
             *  @note The heap invariant is preserved by promoting the collection of elements up the
             *  tree repeatedly until the specific priority is less than or equal to the priority of
             *  its parent or it is the root of the tree.
             *
             *  @param[in] position The position at which the collection of elements shall be inserted.
             *  @param[in] values   The collection of elements which shall be inserted.
             *  @param[in] priority The priority of each of the inserted elements.
             */
            void siftUp(htd::index_t position, std::vector<ValueType> * values, const PriorityType & priority)
            {
                bool found = false;

                while (!found && position > 0)
                {
                    htd::index_t parent = (position - 1) >> 1;

                    const PriorityType & parentPriority = heap_[parent].first;

                    if (!compare_(parentPriority, priority))
                    {
                        found = true;
                    }
                    else
                    {
                        std::swap(priorityMap_[heap_[position].first], priorityMap_[heap_[parent].first]);

                        heap_[position].swap(heap_[parent]);

                        position = parent;
                    }
                }

                heap_[position].second = values;
            }

            /**
             *  Insert the collection of elements with a specific priority at the given position.
             *
             *  @note The heap invariant is preserved by demoting the collection of elements down the
             *  tree repeatedly until the specific priority is greater than or equal to the priority
             *  of its children or it is a leaf.
             *
             *  @param[in] position The position at which the collection of elements shall be inserted.
             *  @param[in] values   The collection of elements which shall be inserted.
             *  @param[in] priority The priority of each of the inserted elements.
             */
            void siftDown(htd::index_t position, std::vector<ValueType> * values, const PriorityType & priority)
            {
                bool found = false;

                std::size_t heapSize = heap_.size();

                std::size_t halfHeapSize = heapSize >> 1;

                while (!found && position < halfHeapSize)
                {
                    htd::index_t child = (position << 1) + 1;

                    PriorityType * childPriority = &(heap_[child].first);

                    htd::index_t rightChild = child + 1;

                    if (rightChild < heapSize && compare_(*childPriority, heap_[rightChild].first))
                    {
                        child = rightChild;

                        childPriority = &(heap_[rightChild].first);
                    }

                    if (!compare_(priority, *childPriority))
                    {
                        found = true;
                    }
                    else
                    {
                        std::swap(priorityMap_[heap_[position].first], priorityMap_[heap_[child].first]);

                        heap_[position].swap(heap_[child]);

                        position = child;
                    }
                }

                heap_[position].first = priority;
                heap_[position].second = values;

                priorityMap_[priority] = position;
            }
    };
}

#endif /* HTD_HTD_PRIORITYQUEUE_HPP */
