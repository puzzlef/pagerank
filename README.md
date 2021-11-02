Comparing the effect of using different **per-iteration rank scaling**,
with PageRank ([pull], [CSR]).

[nvGraph PageRank] appears to use [L2-norm per-iteration scaling]. This
is (probably) required for finding a solution to **eigenvalue problem**.
However, as the *eigenvalue* for PageRank is `1`, this is not necessary.
This experiement was for observing if this was indeed true, and that
any such *per-iteration scaling* doesn't affect the number of *iterations*
needed to converge.

PageRank was computed with **L1**, **L2**, or **L∞-norm** and the
effect of **L1** or **L2-norm** *scaling of ranks* was compared with
**baseline (L0)**. All *seventeen* graphs used in this experiment are
stored in the *MatrixMarket (.mtx)* file format, and obtained from the
*SuiteSparse* *Matrix Collection*. These include: *web-Stanford, web-BerkStan,*
*web-Google, web-NotreDame, soc-Slashdot0811, soc-Slashdot0902,*
*soc-Epinions1, coAuthorsDBLP, coAuthorsCiteseer, soc-LiveJournal1,*
*coPapersCiteseer, coPapersDBLP, indochina-2004, italy_osm,*
*great-britain_osm, germany_osm, asia_osm*. The experiment is implemented
in *C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*.
The *iterations* taken with each test case is measured. `500` is the
*maximum iterations* allowed. Statistics of each test case is
printed to *standard output (stdout)*, and redirected to a *log file*,
which is then processed with a *script* to generate a *CSV file*, with
each *row* representing the details of a *single test case*.

Results match the above assumptions, and indeed no performance benefit
is observed (except a reduction in a single iteration for *web-Google*
and *web-NotreDame* graphs).

All outputs are saved in [out](out/) and a small part of the output is listed
here. The input data used for this experiment is available at ["graphs"] (for
small ones), and the [SuiteSparse Matrix Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# ...
#
# Loading graph /kaggle/input/graphs/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5105039 {} (transposeWithDegree)
# [01813.783 ms; 062 iters.] [0.0000e+00 err.] pagerank
# [01640.350 ms; 061 iters.] [5.1310e-04 err.] pagerankL1Norm [iteration-scaling=L0]
# [01800.358 ms; 062 iters.] [0.0000e+00 err.] pagerankL1Norm [iteration-scaling=L1]
# [14370.214 ms; 500 iters.] [7.2298e+01 err.] pagerankL1Norm [iteration-scaling=L2]
# [01053.020 ms; 040 iters.] [5.0830e-04 err.] pagerankL2Norm [iteration-scaling=L0]
# [01128.224 ms; 039 iters.] [8.9355e-05 err.] pagerankL2Norm [iteration-scaling=L1]
# [14297.734 ms; 500 iters.] [7.2298e+01 err.] pagerankL2Norm [iteration-scaling=L2]
# [00960.368 ms; 036 iters.] [5.3262e-04 err.] pagerankLiNorm [iteration-scaling=L0]
# [01048.550 ms; 036 iters.] [1.5253e-04 err.] pagerankLiNorm [iteration-scaling=L1]
# [14732.606 ms; 500 iters.] [7.2298e+01 err.] pagerankLiNorm [iteration-scaling=L2]
#
# Loading graph /kaggle/input/graphs/web-NotreDame.mtx ...
# order: 325729 size: 1497134 {}
# order: 325729 size: 1497134 {} (transposeWithDegree)
# [00304.237 ms; 059 iters.] [0.0000e+00 err.] pagerank
# [00256.835 ms; 058 iters.] [7.7278e-04 err.] pagerankL1Norm [iteration-scaling=L0]
# [00309.082 ms; 059 iters.] [0.0000e+00 err.] pagerankL1Norm [iteration-scaling=L1]
# [02567.150 ms; 500 iters.] [2.0207e+01 err.] pagerankL1Norm [iteration-scaling=L2]
# [00176.614 ms; 040 iters.] [7.7969e-04 err.] pagerankL2Norm [iteration-scaling=L0]
# [00208.640 ms; 040 iters.] [9.5610e-05 err.] pagerankL2Norm [iteration-scaling=L1]
# [02541.701 ms; 500 iters.] [2.0207e+01 err.] pagerankL2Norm [iteration-scaling=L2]
# [00167.242 ms; 038 iters.] [7.8028e-04 err.] pagerankLiNorm [iteration-scaling=L0]
# [00190.698 ms; 037 iters.] [1.6454e-04 err.] pagerankLiNorm [iteration-scaling=L1]
# [02513.866 ms; 500 iters.] [2.0207e+01 err.] pagerankLiNorm [iteration-scaling=L2]
#
# ...
```

<br>
<br>


## References

- [RAPIDS nvGraph](https://github.com/rapidsai/nvgraph)
- [Deeper Inside PageRank :: Amy N. Langville, Carl D. Meyer](https://www.slideshare.net/SubhajitSahu/deeper-inside-pagerank-notes)
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/BnCiig7.jpg)](https://www.youtube.com/watch?v=IJTvialxf_8)

[nvGraph PageRank]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu
[L2-norm per-iteration scaling]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L145
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
["graphs"]: https://github.com/puzzlef/graphs
[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
