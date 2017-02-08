/* 
 * File:   LabeledGraphType.hpp
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

#ifndef HTD_HTD_LABELEDGRAPHTYPE_HPP
#define HTD_HTD_LABELEDGRAPHTYPE_HPP

#include <htd/ILabelingCollection.hpp>
#include <htd/LabelingCollection.hpp>
#include <htd/GraphLabeling.hpp>

#include <stdexcept>

MSVC_PRAGMA_WARNING_PUSH
MSVC_PRAGMA_DISABLE_WARNING_C4250

namespace htd
{
    /**
     *  Template wrapper class for graph types which allow to assign vertex and hyperedge labels.
     */
    template <typename GraphType>
    class LabeledGraphType : public GraphType
    {
        public:
#ifdef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            using GraphType::assign;
#endif

            /**
             *  Constructor for a htd::LabeledGraphType object.
             *
             *  @param[in] manager   The management instance to which the new labeled graph type belongs.
             */
            LabeledGraphType(const htd::LibraryInstance * const manager) : GraphType(manager), labelings_(new htd::LabelingCollection())
            {

            }

            /**
             *  Copy constructor for a htd::LabeledGraphType object.
             *
             *  @param[in] original  The original htd::LabeledGraphType object.
             */
            LabeledGraphType(const LabeledGraphType<GraphType> & original) : GraphType(original), labelings_(original.labelings_->clone())
            {

            }

            /**
             *  Destructor for a htd::LabeledGraphType object.
             */
            virtual ~LabeledGraphType()
            {
                delete labelings_;
            }

            /**
             *  Remove a vertex from the graph.
             *
             *  @param[in] vertex   The ID of the vertex which shall be removed.
             */
            void removeVertex(htd::vertex_t vertex) HTD_OVERRIDE
            {
                GraphType::removeVertex(vertex);

                labelings_->removeVertexLabels(vertex);
            }

            /**
             *  Access the collection of all labelings used in the graph.
             *
             *  @return The collection of all labelings used in the graph.
             */
            virtual const htd::ILabelingCollection & labelings(void) const
            {
                return *labelings_;
            }

            /**
             *  Getter for the number of different label names in the graph.
             *
             *  @return The number of different label names in the graph.
             */
            virtual std::size_t labelCount(void) const
            {
                return labelings_->labelCount();
            }

            /**
             *  Access the collection of all label names used in the graph.
             *
             *  @return The collection of all label names used in the graph sorted in lexicographically ascending order.
             */
            virtual htd::ConstCollection<std::string> labelNames(void) const
            {
                return labelings_->labelNames();
            }

            /**
             *  Access the label name at the specific position.
             *
             *  @param[in] index    The position of the label name.
             *
             *  @return The label name at the specific position.
             */
            virtual const std::string & labelNameAtPosition(htd::index_t index) const
            {
                return labelings_->labelNameAtPosition(index);
            }

            /**
             *  Check whether a given vertex has a label with the specific name.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] vertex       The vertex.
             *
             *  @return True if the given vertex has a label with the specific name, false otherwise.
             */
            virtual bool isLabeledVertex(const std::string & labelName, htd::vertex_t vertex) const
            {
                return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledVertex(vertex);
            }

            /**
             *  Check whether a given edge has a label with the specific name.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeId       The ID of the edge.
             *
             *  @return True if the given edge has a label with the specific name, false otherwise.
             */
            virtual bool isLabeledEdge(const std::string & labelName, htd::id_t edgeId) const
            {
                return labelings_->isLabelName(labelName) && labelings_->labeling(labelName).isLabeledEdge(edgeId);
            }

            /**
             *  Access the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] vertex       The vertex.
             *
             *  @return The label associated with the given vertex.
             */
            virtual const htd::ILabel & vertexLabel(const std::string & labelName, htd::vertex_t vertex) const
            {
                return labelings_->labeling(labelName).vertexLabel(vertex);
            }

            /**
             *  Access the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label.
             *  @param[in] edgeId       The ID of the edge.
             *
             *  @return The label associated with the given edge.
             */
            virtual const htd::ILabel & edgeLabel(const std::string & labelName, htd::id_t edgeId) const
            {
                return labelings_->labeling(labelName).edgeLabel(edgeId);
            }

            /**
             *  Set the label associated with the given vertex.
             *
             *  If the vertex is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  graph. Deleting the label outside the graph or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] vertex       The vertex to be labeled.
             *  @param[in] label        The new label.
             */
            virtual void setVertexLabel(const std::string & labelName, htd::vertex_t vertex, htd::ILabel * label)
            {
                if (!labelings_->isLabelName(labelName))
                {
                    labelings_->setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_->labeling(labelName).setVertexLabel(vertex, label);
            }

            /**
             *  Set the label associated with the given edge.
             *
             *  If the edge is already labeled, the existing label will
             *  be replaced and the memory of the previous label is freed.
             *
             *  @note When calling this method the control over the memory region of the new label is transferred to the
             *  graph. Deleting the label outside the graph or assigning the same label object to multiple vertices or
             *  edges will lead to undefined behavior.
             *
             *  @param[in] labelName    The name of the new label.
             *  @param[in] edgeId       The ID of the edge to be labeled.
             *  @param[in] label        The new label.
             */
            virtual void setEdgeLabel(const std::string & labelName, htd::id_t edgeId, htd::ILabel * label)
            {
                if (!labelings_->isLabelName(labelName))
                {
                    labelings_->setLabeling(labelName, new htd::GraphLabeling());
                }

                labelings_->labeling(labelName).setEdgeLabel(edgeId, label);
            }

            /**
             *  Remove the label associated with the given vertex.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] vertex       The vertex.
             */
            virtual void removeVertexLabel(const std::string & labelName, htd::vertex_t vertex)
            {
                if (labelings_->isLabelName(labelName))
                {
                    labelings_->labeling(labelName).removeVertexLabel(vertex);
                }
            }

            /**
             *  Remove the label associated with the given edge.
             *
             *  @param[in] labelName    The name of the label which shall be removed.
             *  @param[in] edgeId       The ID of the edge.
             */
            virtual void removeEdgeLabel(const std::string & labelName, htd::id_t edgeId)
            {
                if (labelings_->isLabelName(labelName))
                {
                    labelings_->labeling(labelName).removeEdgeLabel(edgeId);
                }
            }

            /**
             *  Swap the labels of two vertices.
             *
             *  @param[in] vertex1  The first vertex.
             *  @param[in] vertex2  The second vertex.
             */
            virtual void swapVertexLabels(htd::vertex_t vertex1, htd::vertex_t vertex2)
            {
                labelings_->swapVertexLabels(vertex1, vertex2);
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] edgeId1  The ID of the first edge.
             *  @param[in] edgeId2  The ID of the second edge.
             */
            virtual void swapEdgeLabels(htd::id_t edgeId1, htd::id_t edgeId2)
            {
                labelings_->swapEdgeLabels(edgeId1, edgeId2);
            }

            /**
             *  Swap the labels of two vertices.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] vertex1      The first vertex.
             *  @param[in] vertex2      The second vertex.
             */
            virtual void swapVertexLabel(const std::string & labelName, htd::vertex_t vertex1, htd::vertex_t vertex2)
            {
                HTD_ASSERT(labelings_->isLabelName(labelName))

                labelings_->labeling(labelName).swapVertexLabels(vertex1, vertex2);
            }

            /**
             *  Swap the labels of two edges.
             *
             *  @param[in] labelName    The name of the label which shall be swapped.
             *  @param[in] edgeId1      The ID of the first edge.
             *  @param[in] edgeId2      The ID of the second edge.
             */
            virtual void swapEdgeLabel(const std::string & labelName, htd::id_t edgeId1, htd::id_t edgeId2)
            {
                HTD_ASSERT(labelings_->isLabelName(labelName))

                labelings_->labeling(labelName).swapEdgeLabels(edgeId1, edgeId2);
            }

            /**
             *  Transfer the control over a vertex label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] vertex       The vertex which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the vertex is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the vertex label.
             */
            virtual htd::ILabel * transferVertexLabel(const std::string & labelName, htd::vertex_t vertex)
            {
                HTD_ASSERT(labelings_->isLabelName(labelName))

                return labelings_->labeling(labelName).transferVertexLabel(vertex);
            }

            /**
             *  Transfer the control over an edge label to a new owner.
             *
             *  @param[in] labelName    The name of the labeling which will be affected by the operation.
             *  @param[in] edgeId       The ID of the edge which's label shall be transferred.
             *
             *  @note After calling this function the labeling is no longer aware of the label, hence - in the context of the
             *        labeling - the edge is in the same state as it was never labeled. Furthermore, the new owner has to
             *        take care that the memory allocated by the label gets freed.
             *
             *  @return A pointer to the edge label.
             */
            virtual htd::ILabel * transferEdgeLabel(const std::string & labelName, htd::id_t edgeId)
            {
                HTD_ASSERT(labelings_->isLabelName(labelName))

                return labelings_->labeling(labelName).transferEdgeLabel(edgeId);
            }

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Create a deep copy of the current htd::LabeledGraphType object.
             *
             *  @return A new htd::LabeledGraphType object identical to the current htd::LabeledGraphType object.
             */
            LabeledGraphType<GraphType> * clone(void) const HTD_OVERRIDE
            {
                return new LabeledGraphType<GraphType>(*this);
            }
#else
            /**
             *  Create a deep copy of the current htd::LabeledGraphType object.
             *
             *  @return A new htd::LabeledGraphType object identical to the current htd::LabeledGraphType object.
             */
            virtual LabeledGraphType<GraphType> * clone(void) const
            {
                return new LabeledGraphType<GraphType>(*this);
            }

            /**
             *  Create a deep copy of the current htd::LabeledGraphType object.
             *
             *  @return A new htd::LabeledGraphType object identical to the current htd::LabeledGraphType object.
             */
            virtual LabeledGraphType<GraphType> * cloneLabeledGraphType(void) const
            {
                return clone();
            }
#endif

            /**
             *  Copy assignment operator for a htd::LabeledGraphType object.
             *
             *  @param[in] original  The original htd::LabeledGraphType object.
             */
            virtual LabeledGraphType<GraphType> & operator=(const LabeledGraphType<GraphType> & original)
            {
                if (this != &original)
                {
                    GraphType::operator=(original);

                    delete labelings_;

                    labelings_ = original.labelings_->clone();
                }

                return *this;
            }

#ifndef HTD_USE_VISUAL_STUDIO_COMPATIBILITY_MODE
            /**
             *  Copy assignment operator for a htd::LabeledGraphType object.
             *
             *  @param[in] original  The original GraphType object.
             */
            virtual LabeledGraphType<GraphType> & operator=(const GraphType & original)
            {
                if (this != &original)
                {
                    GraphType::operator=(original);

                    delete labelings_;

                    labelings_ = new htd::LabelingCollection();
                }

                return *this;
            }
#else
            /**
             *  Copy assignment operator for a htd::LabeledGraphType object.
             *
             *  @param[in] original  The original GraphType object.
             */
            virtual void assign(const GraphType & original)
            {
                if (this != &original)
                {
                    GraphType::operator=(original);

                    delete labelings_;

                    labelings_ = new htd::LabelingCollection();
                }
            }
#endif

        protected:
            /**
             *  The collection of graph labelings underlying the labeled graph type.
             */
            htd::ILabelingCollection * labelings_;
    };
}

#endif /* HTD_HTD_LABELEDGRAPHTYPE_HPP */
