Performance of C++ DiGraph class based vs CSR based PageRank ([pull]).

This experiment was for comparing the performance between:
1. Find pagerank using C++ `DiGraph` **class** directly.
2. Find pagerank using **CSR** representation of DiGraph.

Both these approaches were tried on a number of different graphs, running
each approach 5 times per graph to get a good time measure. Using a **CSR**
(Compressed Sparse Row) representation has the potential for performance
improvement for both the methods due to information on vertices and edges
being stored contiguously.

The input data used for this experiment is available at ["graphs"] (for small
ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University][this lecture]
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/MwsC9Av.jpg)](https://www.youtube.com/watch?v=GRvZnN0iiwo)

[this lecture]: http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
