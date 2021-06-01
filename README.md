Comparing the effect of using different functions for convergence check, with
PageRank ([pull], [CSR]).

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
the [SuiteSparse Matrix Collection].

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
# [00423.118 ms; 063 iters.] [0.0000e+00 err.] pagerank
# [00007.327 ms; 001 iters.] [6.0894e-01 err.] pagerankL1Norm [tolerance=1e+00]
# [00007.331 ms; 001 iters.] [6.0894e-01 err.] pagerankL2Norm [tolerance=1e+00]
# [00007.323 ms; 001 iters.] [6.0894e-01 err.] pagerankLiNorm [tolerance=1e+00]
# [00014.132 ms; 002 iters.] [3.3244e-01 err.] pagerankL1Norm [tolerance=5e-01]
# [00007.339 ms; 001 iters.] [6.0894e-01 err.] pagerankL2Norm [tolerance=5e-01]
# [00007.322 ms; 001 iters.] [6.0894e-01 err.] pagerankLiNorm [tolerance=5e-01]
# [00034.321 ms; 005 iters.] [9.4240e-02 err.] pagerankL1Norm [tolerance=1e-01]
# [00007.406 ms; 001 iters.] [6.0894e-01 err.] pagerankL2Norm [tolerance=1e-01]
# [00007.347 ms; 001 iters.] [6.0894e-01 err.] pagerankLiNorm [tolerance=1e-01]
# [00040.999 ms; 006 iters.] [6.9689e-02 err.] pagerankL1Norm [tolerance=5e-02]
# [00007.332 ms; 001 iters.] [6.0894e-01 err.] pagerankL2Norm [tolerance=5e-02]
# [00007.330 ms; 001 iters.] [6.0894e-01 err.] pagerankLiNorm [tolerance=5e-02]
# [00081.310 ms; 012 iters.] [1.6086e-02 err.] pagerankL1Norm [tolerance=1e-02]
# [00034.222 ms; 005 iters.] [9.4240e-02 err.] pagerankL2Norm [tolerance=1e-02]
# [00020.831 ms; 003 iters.] [1.9915e-01 err.] pagerankLiNorm [tolerance=1e-02]
# [00101.503 ms; 015 iters.] [8.5030e-03 err.] pagerankL1Norm [tolerance=5e-03]
# [00034.225 ms; 005 iters.] [9.4240e-02 err.] pagerankL2Norm [tolerance=5e-03]
# [00020.826 ms; 003 iters.] [1.9915e-01 err.] pagerankLiNorm [tolerance=5e-03]
# [00155.208 ms; 023 iters.] [1.7352e-03 err.] pagerankL1Norm [tolerance=1e-03]
# [00437.157 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=1e-03]
# [00040.973 ms; 006 iters.] [6.9689e-02 err.] pagerankLiNorm [tolerance=1e-03]
# [00182.057 ms; 027 iters.] [8.1235e-04 err.] pagerankL1Norm [tolerance=5e-04]
# [00436.277 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=5e-04]
# [00040.973 ms; 006 iters.] [6.9689e-02 err.] pagerankLiNorm [tolerance=5e-04]
# [00242.514 ms; 036 iters.] [1.5340e-04 err.] pagerankL1Norm [tolerance=1e-04]
# [00436.740 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=1e-04]
# [00087.954 ms; 013 iters.] [1.2954e-02 err.] pagerankLiNorm [tolerance=1e-04]
# [00269.483 ms; 040 iters.] [7.4190e-05 err.] pagerankL1Norm [tolerance=5e-05]
# [00436.287 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=5e-05]
# [00114.783 ms; 017 iters.] [5.6468e-03 err.] pagerankLiNorm [tolerance=5e-05]
# [00329.760 ms; 049 iters.] [1.3774e-05 err.] pagerankL1Norm [tolerance=1e-05]
# [00436.052 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=1e-05]
# [00181.867 ms; 027 iters.] [8.1235e-04 err.] pagerankLiNorm [tolerance=1e-05]
# [00356.233 ms; 053 iters.] [6.1334e-06 err.] pagerankL1Norm [tolerance=5e-06]
# [00436.831 ms; 065 iters.] [3.7542e-07 err.] pagerankL2Norm [tolerance=5e-06]
# [00208.627 ms; 031 iters.] [3.8458e-04 err.] pagerankLiNorm [tolerance=5e-06]
# [00423.686 ms; 063 iters.] [0.0000e+00 err.] pagerankL1Norm [tolerance=1e-06]
# [03337.069 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=1e-06]
# [00275.648 ms; 041 iters.] [6.1306e-05 err.] pagerankLiNorm [tolerance=1e-06]
# [00450.261 ms; 067 iters.] [6.3236e-07 err.] pagerankL1Norm [tolerance=5e-07]
# [03338.348 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=5e-07]
# [00302.424 ms; 045 iters.] [2.9406e-05 err.] pagerankLiNorm [tolerance=5e-07]
# [00514.874 ms; 077 iters.] [1.1385e-06 err.] pagerankL1Norm [tolerance=1e-07]
# [03290.667 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=1e-07]
# [00364.174 ms; 055 iters.] [3.9247e-06 err.] pagerankLiNorm [tolerance=1e-07]
# [00555.245 ms; 084 iters.] [1.2488e-06 err.] pagerankL1Norm [tolerance=5e-08]
# [03287.860 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=5e-08]
# [00390.604 ms; 059 iters.] [1.2932e-06 err.] pagerankLiNorm [tolerance=5e-08]
# [03288.131 ms; 500 iters.] [1.2680e-06 err.] pagerankL1Norm [tolerance=1e-08]
# [03289.104 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=1e-08]
# [00463.145 ms; 070 iters.] [1.0973e-06 err.] pagerankLiNorm [tolerance=1e-08]
# [03289.938 ms; 500 iters.] [1.2680e-06 err.] pagerankL1Norm [tolerance=5e-09]
# [03288.659 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=5e-09]
# [00482.664 ms; 073 iters.] [1.0328e-06 err.] pagerankLiNorm [tolerance=5e-09]
# [03289.120 ms; 500 iters.] [1.2680e-06 err.] pagerankL1Norm [tolerance=1e-09]
# [03288.354 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=1e-09]
# [03289.023 ms; 500 iters.] [1.2680e-06 err.] pagerankLiNorm [tolerance=1e-09]
# [03288.772 ms; 500 iters.] [1.2680e-06 err.] pagerankL1Norm [tolerance=5e-10]
# [03289.153 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=5e-10]
# [03289.799 ms; 500 iters.] [1.2680e-06 err.] pagerankLiNorm [tolerance=5e-10]
# [03288.177 ms; 500 iters.] [1.2680e-06 err.] pagerankL1Norm [tolerance=1e-10]
# [03288.137 ms; 500 iters.] [1.2680e-06 err.] pagerankL2Norm [tolerance=1e-10]
# [03287.469 ms; 500 iters.] [1.2680e-06 err.] pagerankLiNorm [tolerance=1e-10]
#
# ...
```

[![](https://i.imgur.com/f3OhDzO.gif)][sheets]
[![](https://i.imgur.com/TJFfxtM.gif)][sheets]

<br>
<br>


## References

- [RAPIDS nvGraph NVIDIA graph library][nvGraph]
- [How to check for Page Rank convergence?][L∞ norm]
- [L0 Norm, L1 Norm, L2 Norm & L-Infinity Norm](https://montjoile.medium.com/l0-norm-l1-norm-l2-norm-l-infinity-norm-7a7d18a4f40c)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/p8R1WIk.jpg)](https://www.youtube.com/watch?v=04Uv44DRJAU)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[nvGraph]: https://github.com/rapidsai/nvgraph
[L1 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L154
[L2 norm]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L149
[L∞ norm]: https://stackoverflow.com/a/29321153/1413259
[charts]: https://photos.app.goo.gl/WpPKW5ZRj8qHJkPN8
[sheets]: https://docs.google.com/spreadsheets/d/1TpoKE-WkbKvnym5zvm4-0CL-n5nRkxQkSM7f9qFKeLo/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
