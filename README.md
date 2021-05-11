Performance of *contribution-push* based vs *contribution-pull* based PageRank.

There are two ways (algorithmically) to think of the pagerank calculation.
1. Find pagerank by pushing contribution to out-vertices.
2. Find pagerank by pulling contribution from in-vertices.

The **push** method is somewhat easier to implement, and is described in
[this lecture]. However, it requires multiple writes per source vertex.
On the other hand, the **pull** method requires 2 additional calculations
per-vertex, i.e., non-teleport contribution of each vertex, and, total
teleport contribution (to all vertices). However, it requires only 1 write
per destination vertex.

The experiment was to try both of these approaches on a number of different
graphs, running each approach 5 times per graph to get a good time measure.
While it might seem that **pull** method would be a clear winner, the results
indicate that although **pull** is always faster that **push** approach, the
difference between the two depends on the nature of the graph. The data used
for this experiment is available at ["graphs"] (for small ones), and the
[SuiteSparse Matrix Collection].

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/min-1DeadEnd.mtx
$ ./a.out ~/data/min-2SCC.mtx
$ ...

# Loading graph /home/subhajit/data/min-1DeadEnd.mtx ...
# order: 5 size: 6 {}
# order: 5 size: 6 {} (transposeWithDegree)
# [00000.006 ms; 016 iters.] [0.0000e+00 err.] pagerankPush
# [00000.006 ms; 016 iters.] [1.2666e-07 err.] pagerankPull
#
# Loading graph /home/subhajit/data/min-2SCC.mtx ...
# order: 8 size: 12 {}
# order: 8 size: 12 {} (transposeWithDegree)
# [00000.008 ms; 039 iters.] [0.0000e+00 err.] pagerankPush
# [00000.010 ms; 039 iters.] [2.2352e-08 err.] pagerankPull
#
# Loading graph /home/subhajit/data/min-4SCC.mtx ...
# order: 21 size: 35 {}
# order: 21 size: 35 {} (transposeWithDegree)
# [00000.019 ms; 044 iters.] [0.0000e+00 err.] pagerankPush
# [00000.024 ms; 044 iters.] [6.6124e-08 err.] pagerankPull
#
# Loading graph /home/subhajit/data/min-NvgraphEx.mtx ...
# order: 6 size: 10 {}
# order: 6 size: 10 {} (transposeWithDegree)
# [00000.004 ms; 023 iters.] [0.0000e+00 err.] pagerankPush
# [00000.005 ms; 023 iters.] [7.0781e-08 err.] pagerankPull
#
# Loading graph /home/subhajit/data/web-Stanford.mtx ...
# order: 281903 size: 2312497 {}
# order: 281903 size: 2312497 {} (transposeWithDegree)
# [02315.975 ms; 062 iters.] [0.0000e+00 err.] pagerankPush
# [00767.082 ms; 062 iters.] [1.4294e-06 err.] pagerankPull
#
# Loading graph /home/subhajit/data/web-BerkStan.mtx ...
# order: 685230 size: 7600595 {}
# order: 685230 size: 7600595 {} (transposeWithDegree)
# [43267.887 ms; 063 iters.] [0.0000e+00 err.] pagerankPush
# [01381.938 ms; 063 iters.] [5.3445e-05 err.] pagerankPull
#
# Loading graph /home/subhajit/data/web-Google.mtx ...
# order: 916428 size: 5105039 {}
# order: 916428 size: 5105039 {} (transposeWithDegree)
# [1997386.500 ms; 060 iters.] [0.0000e+00 err.] pagerankPush
# [02685.384 ms; 060 iters.] [2.0315e-03 err.] pagerankPull
#
# Loading graph /home/subhajit/data/web-NotreDame.mtx ...
# order: 325729 size: 1497134 {}
# order: 325729 size: 1497134 {} (transposeWithDegree)
# [661632.312 ms; 057 iters.] [0.0000e+00 err.] pagerankPush
# [00396.223 ms; 057 iters.] [1.5100e-03 err.] pagerankPull
#
# Loading graph /home/subhajit/data/soc-Slashdot0811.mtx ...
# order: 77360 size: 905468 {}
# order: 77360 size: 905468 {} (transposeWithDegree)
# [00174.320 ms; 054 iters.] [0.0000e+00 err.] pagerankPush
# [00127.184 ms; 054 iters.] [2.9950e-07 err.] pagerankPull
#
# Loading graph /home/subhajit/data/soc-Slashdot0902.mtx ...
# order: 82168 size: 948464 {}
# order: 82168 size: 948464 {} (transposeWithDegree)
# [03059.213 ms; 055 iters.] [0.0000e+00 err.] pagerankPush
# [00136.453 ms; 055 iters.] [5.5360e-06 err.] pagerankPull
#
# Loading graph /home/subhajit/data/soc-Epinions1.mtx ...
# order: 75888 size: 508837 {}
# order: 75888 size: 508837 {} (transposeWithDegree)
# [10770.703 ms; 053 iters.] [0.0000e+00 err.] pagerankPush
# [00098.932 ms; 053 iters.] [1.1770e-04 err.] pagerankPull
#
# Loading graph /home/subhajit/data/coAuthorsDBLP.mtx ...
# order: 299067 size: 1955352 {}
# order: 299067 size: 1955352 {} (transposeWithDegree)
# [00739.014 ms; 044 iters.] [0.0000e+00 err.] pagerankPush
# [00524.417 ms; 044 iters.] [7.9472e-08 err.] pagerankPull
#
# Loading graph /home/subhajit/data/coAuthorsCiteseer.mtx ...
# order: 227320 size: 1628268 {}
# order: 227320 size: 1628268 {} (transposeWithDegree)
# [00445.284 ms; 047 iters.] [0.0000e+00 err.] pagerankPush
# [00374.876 ms; 047 iters.] [1.0504e-07 err.] pagerankPull
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# ...
```

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University][this lecture]
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/89cRRdY.jpg)](https://www.youtube.com/watch?v=iMdq5_5eib0)

[this lecture]: http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
