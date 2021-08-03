Comparing the effect of using different **functions** for
**convergence check**, with PageRank ([pull], [CSR]).

This experiment was for comparing the performance between:
1. Find pagerank using **L1 norm** for convergence check.
2. Find pagerank using **L2 norm** for convergence check.
3. Find pagerank using **L∞ norm** for convergence check.

Each approach was attempted on a number of graphs, running each approach 5
times per graph to get a good time measure. Although [L1 norm] is commonly
used for convergence check, it appears [nvGraph] uses [L2 norm] instead.
Another person in stackoverflow seems to suggest the use of per-vertex tolerance
comparision, which is essentially [L∞ norm]. Results show that **L∞ norm** is
a faster convergence check for **all graphs**. For *road networks*, which have
a large no. of vertices, using **L∞ norm** causes the ranks to converge in
just `1` iteration. This is possibly because the per-vertex update of ranks
is smaller than `10^-6`. Also note that **L2 norm** is normally slower than
**L1 norm** for most graphs, but is faster for *road networks*, and a few others.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at ["graphs"] (for small ones), and
the [SuiteSparse Matrix Collection]. This experiment was done with guidance
from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [00436.174 ms; 063 iters.] [0.0000e+00 err.] pagerankL1Norm
# [03434.695 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm
# [00283.799 ms; 041 iters.] [6.1306e-05 err.] pagerankLiNorm
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [13047.078 ms; 051 iters.] [0.0000e+00 err.] pagerankL1Norm
# [13306.672 ms; 052 iters.] [8.2882e-07 err.] pagerankL2Norm
# [04355.853 ms; 017 iters.] [1.7652e-03 err.] pagerankLiNorm
#
# ...
```

[![](https://i.imgur.com/JqT3hyq.png)][sheetp]
[![](https://i.imgur.com/u3eYfas.png)][sheetp]
[![](https://i.imgur.com/BL1vDBp.png)][sheetp]
[![](https://i.imgur.com/gNACr6z.png)][sheetp]
[![](https://i.imgur.com/f3OhDzO.gif)][sheetp]
[![](https://i.imgur.com/TJFfxtM.gif)][sheetp]

<br>
<br>


## References

- [RAPIDS nvGraph NVIDIA graph library][nvGraph]
- [How to check for Page Rank convergence?][L∞ norm]
- [L0 Norm, L1 Norm, L2 Norm & L-Infinity Norm](https://montjoile.medium.com/l0-norm-l1-norm-l2-norm-l-infinity-norm-7a7d18a4f40c)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/p8R1WIk.jpg)](https://www.youtube.com/watch?v=04Uv44DRJAU)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[nvGraph]: https://github.com/rapidsai/nvgraph
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[charts]: https://photos.app.goo.gl/WpPKW5ZRj8qHJkPN8
[sheets]: https://docs.google.com/spreadsheets/d/1TpoKE-WkbKvnym5zvm4-0CL-n5nRkxQkSM7f9qFKeLo/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vSN6xnlxOz8u4PMYxUbxP01qFq8lrYa6IC8DH2pYFGkMmWD4-BB4jdk4e3Cp9Yh_GUG5SzF5OG7ZSex/pubhtml
