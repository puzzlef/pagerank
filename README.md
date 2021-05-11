Performance of C++ DiGraph class based vs CSR based PageRank (pull method).

This experiment was to compare the performance of *pull* method using either
a C++ `DiGraph` **class** directly, or using a **CSR** (Compressed Sparse
Row) representation instead of the DiGraph instead. Using a CSR
representation has the potential for performance improvement for both the
methods due to information on vertices and edges being stored contiguously.
See ["pagerank-push-vs-pull"] for a discussion on *push* vs *pull* method.
The input data used for this experiment is available at ["graphs"] (for
small ones), and the [SuiteSparse Matrix Collection].

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {}
# order: 5 size: 6 {} (transposeWithDegree)
# [00000.003 ms; 016 iters.] [0.0000e+00 err.] pagerankClass
# [00000.002 ms; 016 iters.] [1.2666e-07 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.006 ms; 039 iters.] [0.0000e+00 err.] pagerankClass
# [00000.006 ms; 039 iters.] [2.2352e-08 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.017 ms; 044 iters.] [0.0000e+00 err.] pagerankClass
# [00000.015 ms; 044 iters.] [6.6124e-08 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 10 {} (transposeWithDegree)
# [00000.005 ms; 023 iters.] [0.0000e+00 err.] pagerankClass
# [00000.003 ms; 023 iters.] [7.0781e-08 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00908.511 ms; 062 iters.] [0.0000e+00 err.] pagerankClass
# [00408.692 ms; 062 iters.] [1.4294e-06 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {}
# order: 685230 size: 7600595 {} (transposeWithDegree)
# [44600.941 ms; 063 iters.] [0.0000e+00 err.] pagerankClass
# [00890.880 ms; 063 iters.] [5.3445e-05 err.] pagerankCsr
#
# Loading graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5105039 {} (transposeWithDegree)
# ...
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University][this lecture]
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/zCbryl4.jpg)](https://www.youtube.com/watch?v=GRvZnN0iiwo)

[this lecture]: http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4
["pagerank-push-vs-pull"]: https://github.com/puzzlef/pagerank-push-vs-pull
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
