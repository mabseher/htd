# SUPPORTED FILE FORMATS

## Input Formats

**htd** supports the following input file formats:

* gr:

  The input file format of the 1st Parameterized Algorithms and Computational Experiments Challenge.
  For more information see [https://pacechallenge.wordpress.com/track-a-treewidth/](https://pacechallenge.wordpress.com/track-a-treewidth/).

* lp:

  This format is inspired by logic-programming. Vertices of the given input graph are defined via facts of 
  format `vertex(<IDENTIFIER>)` and edges are specified using facts of format `edge(<VERTEX1>, <VERTEX2>)`.

* hgr:

  Similar to format 'gr' where hyperedges (edges with more than two end-points) are allowed.

## Output Formats

**htd** supports the following input file formats:

* td:

  The output file format of the 1st Parameterized Algorithms and Computational Experiments Challenge.
  For more information see [https://pacechallenge.wordpress.com/track-a-treewidth/](https://pacechallenge.wordpress.com/track-a-treewidth/).

* human:

  Print the decomposition in an human-readable format.

* width:

  Print only the maximum bag size of the computed decomposition.

(Note that output is written to `stdout`!)
