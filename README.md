# htd

[![License](http://img.shields.io/badge/license-GPLv3-blue.svg)](https://www.gnu.org/copyleft/gpl.html)
[![Build Status](https://travis-ci.org/mabseher/htd.svg?branch=master)](https://travis-ci.org/mabseher/htd)
[![Coverity Status](https://scan.coverity.com/projects/8163/badge.svg)](https://scan.coverity.com/projects/mabseher-htd)
[![Code Coverage Status](https://coveralls.io/repos/github/mabseher/htd/badge.svg?branch=master&update=1)](https://coveralls.io/github/mabseher/htd?branch=master)

**A small but efficient C++ library for computing (customized) tree and hypertree decompositions.**

**htd** is a library which does not only compute tree decompositions, it also allows to fully customize them via (custom) manipulations, labelings and optimize them based on a user-provided fitness function. The library provides efficient implementations of well-established techniques for computing tree decompositions (like bucket-elimination based on a vertex elimination ordering of the input graph) and it is optimized for large (hyper)graphs. At the current stage, **htd** is able to decompose graphs containing millions of vertices and several hundreds of thousands of (hyper)edges efficiently. 

For almost each class used in the library, **htd** provides an interface and a corresponding factory class allowing to directly influence the process of generating decompositions without having to re-invent the wheel at any place. That is, if one for instance develops a new heuristic for vertex elimination orderings there is absolutely no need to change anything in the remainder of the library in order to test its influence on the quality of bucket-elimination. (In fact, one does not even need to re-compile **htd** for such a modification as long as all interfaces are implemented properly by the new algorithm and as long as the algorithm is made available to **htd** via the corresponding factory class.)

## BUILD PROCESS

For instructions about the build process, please read the `INSTALL.md` file.

## USAGE

### Using htd via command-line interface

For using **htd** via the command-line interface there is the front-end application **htd_main**. **htd_main** provides access to basic functionality of **htd**.

A program call for **htd_main** is of the following form:

`./htd_main [-h] [-s <SEED>] [--type <DECOMPOSITION_TYPE>] [--input <FORMAT>] [--output <FORMAT>] [--ordering <ALGORITHM>] [--opt <CRITERION>] [--iterations <LIMIT>] [--non-improvement-limit <LIMIT>] [--print-opt-progress] < $FILE`

Options are organized in the following groups:

* General Options:
  * --help, -h                        Print usage information and exit.
  * --seed, -s <seed>                 Set the seed for the random number generator to <seed>

  * Decomposition Options:
  * --type <type>                     Compute a graph decomposition of type <type>.
    * Permitted Values:
      * .) tree        Compute a tree decomposition of the input graph. (default)
      * .) hypertree   Compute a hypertree decomposition of the input graph.

  * Input-Specific Options:
    * --input <format>                  Assume that the input graph is given in format <format>. (See [FORMATS](https://github.com/mabseher/htd/formats.md) for information about the available input formats.)
      * Permitted Values:
        * .) gr    Use the input format 'gr'. (default)
        * .) lp    Use the input format 'lp'.
        * .) mgr   Use the input format 'mgr'.

  * Output-Specific Options:
    * --output <format>                 Set the output format of the decomposition to <format>. (See [FORMATS](https://github.com/mabseher/htd/formats.md) for information about the available output formats.)
      * Permitted Values:
        * .) td      Use the output format 'td'. (default)
        * .) human   Provide a human-readable output of the decomposition.
        * .) width   Provide only the maximum bag size of the decomposition.

  * Algorithm Options:
    * --ordering <algorithm>            Set the ordering algorithm which shall be used to <algorithm>.
      * Permitted Values:
        * .) min-fill+         Advanced minimum-fill ordering algorithm (default)
        * .) min-fill          Standard minimum-fill ordering algorithm
        * .) min-degree        Minimum-degree ordering algorithm
        * .) max-cardinality   Maximum cardinality search ordering algorithm

  * Optimization Options:
    * --opt <criterion>                 Iteratively compute a decomposition which optimizes <criterion>.
      * Permitted Values:
        * .) none    Do not perform any optimization. (default)
        * .) width   Minimize the maximum bag size of the computed decomposition.
    * --iterations <count>              Set the number of iterations to be performed during optimization to <count> (0 = infinite). (Default: 10)
    * --non-improvement-limit <count>   Terminate the algorithm if more than <count> iterations did not lead to an improvement (-1 = infinite). (Default: -1)
    * --print-opt-progress              Print progress whenever a new optimal decomposition is found.

## LICENSE

**htd** is released under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007.

A copy of the license should be provided with the system, otherwise see [http://www.gnu.org/licenses/](http://www.gnu.org/licenses/).
