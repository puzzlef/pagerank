Comparison of ordered vs unordered vertex processing in [PageRank algorithm] for
[link analysis].

We generally compute PageRank by initialize the rank of each vertex (to say
`1/N`, where *N* is the total number of vertices in the graph), and iteratively
updating the ranks such that the new rank of each vertex is dependent upon the
ranks of its in-neighbors in the previous iteration. We are calling this the
**unordered** approach, since we can alter the vertex processing order without
affecting the result (order *does not* matter). We use *two* rank vectors
(previous and current) with the *ordered* approach.

In a standard multi-threaded implementation, we split the workload of updating
the ranks of vertices among the threads. Each thread operates on the ranks of
vertices in the previous iteration, and all threads *join* together at the end
of each iteration. Hemalatha Eedi et al. [(1)] discuss barrierless non-blocking
implementations of the PageRank algorithm, where threads *do not join*
together, and thus may be on different iteration number at a time. A single rank
vector is used, and the rank of each vertex is updated once it is computed (so
we should call this the **ordered** approach, where the processing order of
vertices *does* matter).

In this experiment, we compare the **ordered** and **unordered** approaches with
a sequential PageRank implementation. We use a damping factor of `α = 0.85`, a
tolerance of `τ = 10⁻⁶`, and limit the maximum number of iterations to `L = 500`.
The error between iterations is calculated with *L1 norm*, and the error
between the two approaches is also calculated with *L1 norm*. The unordered
approach is considered the *gold standard*, as it has been described in the
original paper by Larry Page et al. [(2)]. *Dead ends* in the graph are handled
by always teleporting any vertex in the graph at random (*teleport* approach
[(3)]). The teleport contribution to all vertices is calculated *once* (for all
vertices) at the begining of each iteration.

From the results, we observe that the **ordered approach is faster** than the
*unordered* approach, **in terms of the number of iterations**. This seems to
make sense, as using newer ranks of vertices may accelerate convergence
(especially in case of long chains). However, the **ordered** approach is **only**
**slightly faster in terms of time**. Why does this happen? This might be due to
having to access two different vectors (*factors* `f = α/d`, where *d* is the
out-degree of each vertex; and *ranks* `r`), when compared to the *unordered*
approach where we need to access a single vector (*contributions* `c = αr/d`,
where *r* denotes rank of each vertex in the previous iteration). This suggests
that **ordered** approach **may not be significatly faster** than the unordered
approach.

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
# [00386.903 ms; 063 iters.] [0.0000e+00 err.] pagerankSeqUnordered
# [00318.363 ms; 033 iters.] [2.6483e-06 err.] pagerankSeqOrdered
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 [directed] {}
# order: 685230 size: 7600595 [directed] {} (transposeWithDegree)
# [00878.410 ms; 064 iters.] [0.0000e+00 err.] pagerankSeqUnordered
# [00506.558 ms; 035 iters.] [2.3710e-06 err.] pagerankSeqOrdered
#
# ...
```

[![](https://i.imgur.com/2lN0NdN.png)][sheetp]
[![](https://i.imgur.com/2EpBpif.png)][sheetp]

<br>
<br>


## References

- [An Efficient Practical Non-Blocking PageRank Algorithm for Large Scale Graphs; Hemalatha Eedi et al. (2021)](https://ieeexplore.ieee.org/document/9407114)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [The PageRank Citation Ranking: Bringing Order to the Web; Larry Page et al. (1998)](https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5427)
- [The University of Florida Sparse Matrix Collection; Timothy A. Davis et al. (2011)](https://doi.org/10.1145/2049662.2049663)

<br>
<br>


[![](https://i.imgur.com/oTdO0LJ.jpg)](https://www.youtube.com/watch?v=2zQb_OitsaY)<br>


[(1)]: https://ieeexplore.ieee.org/document/9407114
[(2)]: https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5427
[(3)]: https://gist.github.com/wolfram77/94c38b9cfbf0c855e5f42fa24a8602fc
[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[Prof. Sathya Peri]: https://people.iith.ac.in/sathya_p/
[PageRank algorithm]: https://en.wikipedia.org/wiki/PageRank
[link analysis]: https://en.wikipedia.org/wiki/Network_theory#Link_analysis
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu
[gist]: https://gist.github.com/wolfram77/e830a5422a8f3ef404af1e91c47b3fc5
[charts]: https://imgur.com/a/Smdzg5m
[sheets]: https://docs.google.com/spreadsheets/d/1HbHH3Vu_nPNTGdK3mGo0MVrde7hqdQFgDcsyodjOHhw/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vRNcm2xZ7wKrGhWoMd_XSuCSAk9S-mmfzlgApbz-AbLWkeEXWWfW7883WGUF4C3WuI7Yvk9DCL17pbV/pubhtml
