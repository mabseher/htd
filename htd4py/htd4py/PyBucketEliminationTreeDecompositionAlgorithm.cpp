/*
 This file is part of htd (htd Python API).

 htd, a tree decomposition library.

 htd4Py Copyright 2015
 Johannes K. Fichte, TU Wien, Austria

 htd Copyright 2015
 Michael Abseher, TU Wien, Austria

 htd4Py is free software: you can redistribute it and/or modify it
 under the terms of the GNU General Public License as published by the
 Free Software Foundation, either version 3 of the License, or (at
 your option) any later version.  htd4Py is distributed in the hope
 that it will be useful, but WITHOUT ANY WARRANTY; without even the
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the GNU General Public License for more details.  You
 should have received a copy of the GNU General Public License along
 with htd4Py.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Python.h>
#include <boost/python.hpp>

namespace py = boost::python;

#include <htd/ITreeDecomposition.hpp>
#include <htd/ITreeDecompositionAlgorithm.hpp>
#include <htd/BucketEliminationTreeDecompositionAlgorithm.hpp>
//TODO: change to interface??
#include <htd/MinFillOrderingAlgorithm.hpp>
#include <htd/Hypergraph.hpp>

#include <PyMutableHypergraphImpl.h>


namespace htd {
  htd::ITreeDecomposition *(htd::BucketEliminationTreeDecompositionAlgorithm::*decompose)(const htd::IHypergraph &graph)
  const HTD_OVERRIDE = &htd::BucketEliminationTreeDecompositionAlgorithm::computeDecomposition;

    htd::BucketEliminationTreeDecompositionAlgorithm *algo_init_(const htd::MinFillOrderingAlgorithm *o) {
        htd::BucketEliminationTreeDecompositionAlgorithm *algo = new htd::BucketEliminationTreeDecompositionAlgorithm(
                *o);
        return algo;
    }

    htd::ITreeDecomposition *decompose_(htd::BucketEliminationTreeDecompositionAlgorithm &algo,
                                 htd::Hypergraph graph) {
      htd::ITreeDecomposition *decomposition = algo.computeDecomposition(graph);
      return decomposition;
    }

  void export_BucketEliminationTreeDecompositionAlgorithm(){
  py::class_<htd::BucketEliminationTreeDecompositionAlgorithm>("TDecompBE", py::no_init)
      //TODO: with_custodian_and_ward<1,2>()
    .def("__init__", py::make_constructor(&htd::algo_init_))
    .def("decompose", &htd::decompose_, (py::arg("graph")), py::return_value_policy<py::manage_new_object>());

  }
}
