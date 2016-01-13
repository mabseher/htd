#!/usr/bin/env python
#
#  This file is part of htd (htd Python API).
#
#  htd, a tree decomposition library.
#
#  htd4Py Copyright 2015
#  Johannes K. Fichte, TU Wien, Austria
#
#  htd Copyright 2015
#  Michael Abseher, TU Wien, Austria
#
#  htd4Py is free software: you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation, either version 3 of the License, or (at
#  your option) any later version.  htd4Py is distributed in the hope
#  that it will be useful, but WITHOUT ANY WARRANTY; without even the
#  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.  See the GNU General Public License for more details.  You
#  should have received a copy of the GNU General Public License along
#  with htd4Py.  If not, see <http://www.gnu.org/licenses/>.
#

import sys

import htd
h=htd.Hypergraph(0)
h.add_vertex()
h.add_vertex()
h.add_vertex()
h.add_vertex()
h.add_edge(1,2)
h.add_edge(2,3)
#h.add_edge(700,3)
#TODO:
#catch runtime errors
#h.add_edge(1,4)

htd.set_seed(1233)

print "vertices=", h.num_vertices(), "edges=", h.num_edges()
ord = htd.MinFillOrdering()
be_decomp = htd.TDecompBE(ord)
print be_decomp
decomp=be_decomp.decompose(h)
for v in decomp.vertices():
    print decomp.bag_content(v)
print "width=", decomp.width()
