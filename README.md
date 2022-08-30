Effect of using different values of tolerance with ordered [PageRank algorithm]
for [link analysis].

**Unordered PageRank** is the *standard* way of computing PageRank computation,
where *two* *different rank vectors* are maintained; one representing the
*current* ranks of vertices, and the other representing the *previous* ranks.
Conversely, **ordered PageRank** uses *a single rank vector* for the
current ranks of vertices [(1)]. This is similar to barrierfree non-blocking
implementation of PageRank by Hemalatha Eedi et al. [(2)]. Since ranks are
updated in the same vector (with each iteration), the order in which vertices
are processed *affects* the final outcome (hence the modifier *ordered*).
Nonetheless, as PageRank is a converging algorithm, ranks obtained with either
approach are *mostly the same*.

In this experiment, we perform ordered PageRank while adjusting the tolerance
`τ` from `10^-1` to `10^-14` with three different tolerance functions:
`L1-norm`, `L2-norm`, and `L∞-norm`. We also compare it with unordered PageRank
for the same tolerance and tolerance function.  We use a damping factor of `α = 0.85`
and limit the maximum number of iterations to `L = 500`. The error between
the two approaches is calculated with *L1-norm*. The unordered approach is
considered to be the *gold standard*, as it has been described in the original
paper by Larry Page et al. [(3)]. *Dead ends* in the graph are handled by always
teleporting any vertex in the graph at random (*teleport* approach [(4)]). The
teleport contribution to all vertices is calculated *once* (for all vertices) at
the begining of each iteration.

From the results, we observe that the **ordered approach is always faster** than
the *unordered* approach, **in terms of the number of iterations**. This seems
to make sense, as using newer ranks of vertices may accelerate convergence
(especially in case of long chains). However, the **ordered** approach is
**not** **always faster in terms of time**. When `L2-norm` is used for
convergence check, ordered approach is generally faster for a tolerance less
than `τ = 10^-4`. and when `L∞-norm` is used, it is generally faster for a
tolerance less than `τ = 10^-6`. It looks like a **suitable value of tolerance**
with any tolerance function **for the ordered approach** would be
`τ ∈ [10^-6, 10^-11]`. This could be due to the ordered approach having to access
two different vectors (*factors* `f = α/d`, where *d* is the out-degree of each
vertex; and *ranks* `r`), when compared to the *unordered* approach where we
need to access a single vector (*contributions* `c = αr/d`, where *r* denotes
rank of each vertex in the previous iteration). This suggests that **ordered**
**approach is better than the unordered approach when tighter tolerance is**
**used (but not too tight)**.

All outputs are saved in a [gist] and a small part of the output is listed here.
Some [charts] are also included below, generated from [sheets]. The input data
used for this experiment is available from the [SuiteSparse Matrix Collection].
This experiment was done with guidance from [Prof. Kishore Kothapalli],
[Prof. Dip Sankar Banerjee], and [Prof. Sathya Peri].

<br>

```bash
$ g++ -std=c++17 -O3 main.cxx
$ ./a.out ~/data/web-Stanford.mtx
$ ./a.out ~/data/web-BerkStan.mtx
$ ...

# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 [directed] {}
# order: 281903 size: 2312497 [directed] {} (transposeWithDegree)
# [00031.691 ms; 005 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-01}
# [00041.459 ms; 004 iters.] [6.4879e-02 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-01}
# [00074.792 ms; 012 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-02}
# [00074.113 ms; 007 iters.] [1.2687e-02 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-02}
# [00142.674 ms; 023 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-03}
# [00131.097 ms; 013 iters.] [1.7184e-03 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-03}
# ...
# [03095.701 ms; 500 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: Li, tolerance: 1e-12}
# [04948.351 ms; 500 iters.] [1.6800e-07 err.] pagerankSeqOrdered   {tol_norm: Li, tolerance: 1e-12}
# [03093.156 ms; 500 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: Li, tolerance: 1e-13}
# [05002.450 ms; 500 iters.] [1.6800e-07 err.] pagerankSeqOrdered   {tol_norm: Li, tolerance: 1e-13}
# [03097.697 ms; 500 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: Li, tolerance: 1e-14}
# [04956.465 ms; 500 iters.] [1.6800e-07 err.] pagerankSeqOrdered   {tol_norm: Li, tolerance: 1e-14}
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 [directed] {}
# order: 685230 size: 7600595 [directed] {} (transposeWithDegree)
# [00069.909 ms; 005 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-01}
# [00058.967 ms; 004 iters.] [9.5628e-02 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-01}
# [00168.359 ms; 012 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-02}
# [00116.454 ms; 008 iters.] [1.9341e-02 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-02}
# [00331.215 ms; 024 iters.] [0.0000e+00 err.] pagerankSeqUnordered {tol_norm: L1, tolerance: 1e-03}
# [00203.736 ms; 014 iters.] [2.1899e-03 err.] pagerankSeqOrdered   {tol_norm: L1, tolerance: 1e-03}
# ...
```

[![](https://i.imgur.com/Cma57GR.png)][sheetp]
[![](https://i.imgur.com/8jC4eVr.png)][sheetp]

<br>
<br>


## References

- [An Efficient Practical Non-Blocking PageRank Algorithm for Large Scale Graphs; Hemalatha Eedi et al. (2021)](https://ieeexplore.ieee.org/document/9407114)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [The PageRank Citation Ranking: Bringing Order to the Web; Larry Page et al. (1998)](https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5427)
- [The University of Florida Sparse Matrix Collection; Timothy A. Davis et al. (2011)](https://doi.org/10.1145/2049662.2049663)

<br>
<br>


[![](https://i.imgur.com/qp7YIhe.jpg)](https://www.youtube.com/watch?v=69-J2m_GyhI)<br>
[![DOI](https://zenodo.org/badge/530183906.svg)](https://zenodo.org/badge/latestdoi/530183906)


[(1)]: https://github.com/puzzlef/pagerank-ordered-vs-unordered
[(2)]: https://ieeexplore.ieee.org/document/9407114
[(3)]: https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5427
[(4)]: https://gist.github.com/wolfram77/94c38b9cfbf0c855e5f42fa24a8602fc
[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[Prof. Sathya Peri]: https://people.iith.ac.in/sathya_p/
[PageRank algorithm]: https://en.wikipedia.org/wiki/PageRank
[link analysis]: https://en.wikipedia.org/wiki/Network_theory#Link_analysis
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
[gist]: https://gist.github.com/wolfram77/3b3034b62d8d29cd4795256f9bc72320
[charts]: https://imgur.com/a/XwIeDWa
[sheets]: https://docs.google.com/spreadsheets/d/11jkaKek50XPOEpCP5Zhrp3Mslq9Uu_iqQQhULSaqvsM/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vRc6NlKNrmTYCLQMJcxuatq50U8atlYubQLi2G3ZZz-GvXCWhaOQ2TypTVaeMHgI6uYOOL_ww5T1YpZ/pubhtml
