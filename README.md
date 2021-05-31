Comparing the effect of using different values of damping factor, with PageRank
([pull], [CSR]).

For this experiment, the damping factor `d` (which is usually `0.85`) is
varied from `0.50` to `1.00` in steps of `0.05`. This is in order to compare
the performace variation with each damping factor. The calculated error
is the L1-norm wrt default pagerank (`d=0.85`). As expected, increasing
the damping factor beyond `0.85` significantly increases convergence time,
and lowering it below `0.85` decreases convergence time. Note that a higher
damping factor implies that a random surfer follows links with higher
probability (and jumps to ransom page with lower probability). Also note that
`500` is the maximum iterations allowed here.

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
# [00405.436 ms; 063 iters.] [0.0000e+00 err.] pagerank
# [03199.666 ms; 500 iters.] [1.1731e+00 err.] pagerank [damping=1.00]
# [01233.223 ms; 192 iters.] [3.3279e-01 err.] pagerank [damping=0.95]
# [00617.424 ms; 096 iters.] [1.3471e-01 err.] pagerank [damping=0.90]
# [00405.537 ms; 063 iters.] [2.1264e-07 err.] pagerank [damping=0.85]
# [00302.939 ms; 047 iters.] [1.0787e-01 err.] pagerank [damping=0.80]
# [00238.925 ms; 037 iters.] [2.0008e-01 err.] pagerank [damping=0.75]
# [00193.744 ms; 030 iters.] [2.8214e-01 err.] pagerank [damping=0.70]
# [00161.573 ms; 025 iters.] [3.5654e-01 err.] pagerank [damping=0.65]
# [00135.776 ms; 021 iters.] [4.2481e-01 err.] pagerank [damping=0.60]
# [00116.598 ms; 018 iters.] [4.8881e-01 err.] pagerank [damping=0.55]
# [00103.777 ms; 016 iters.] [5.5010e-01 err.] pagerank [damping=0.50]
#
# ...
#
# Loading graph /home/subhajit/data/soc-LiveJournal1.mtx ...
# order: 4847571 size: 68993773 {}
# order: 4847571 size: 68993773 {} (transposeWithDegree)
# [11693.781 ms; 051 iters.] [0.0000e+00 err.] pagerank
# [121446.203 ms; 500 iters.] [8.6730e-01 err.] pagerank [damping=1.00]
# [35313.477 ms; 152 iters.] [1.9719e-01 err.] pagerank [damping=0.95]
# [17886.010 ms; 077 iters.] [8.6216e-02 err.] pagerank [damping=0.90]
# [11846.550 ms; 051 iters.] [1.1429e-07 err.] pagerank [damping=0.85]
# [08593.597 ms; 037 iters.] [7.3479e-02 err.] pagerank [damping=0.80]
# [06973.961 ms; 030 iters.] [1.3968e-01 err.] pagerank [damping=0.75]
# [06038.274 ms; 026 iters.] [1.9829e-01 err.] pagerank [damping=0.70]
# [05117.046 ms; 022 iters.] [2.5813e-01 err.] pagerank [damping=0.65]
# [04184.997 ms; 018 iters.] [3.1309e-01 err.] pagerank [damping=0.60]
# [03957.167 ms; 017 iters.] [3.5808e-01 err.] pagerank [damping=0.55]
# [03489.042 ms; 015 iters.] [3.9641e-01 err.] pagerank [damping=0.50]
#
# ...
```

[![](https://i.imgur.com/sJVNiOU.gif)][sheets]
[![](https://i.imgur.com/JGJOuoT.gif)][sheets]

<br>
<br>


## References

- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](http://snap.stanford.edu/class/cs246-videos-2019/lec9_190205-cs246-720.mp4)
- [SuiteSparse Matrix Collection]

<br>
<br>

[![](https://i.imgur.com/CxwDsTm.jpg)](https://www.youtube.com/watch?v=jcqkqJnTydU)

[pull]: https://github.com/puzzlef/pagerank-push-vs-pull
[CSR]: https://github.com/puzzlef/pagerank-class-vs-csr
[charts]: https://photos.app.goo.gl/pNs2QeAfC2ainMMy5
[sheets]: https://docs.google.com/spreadsheets/d/1wXeWc4yzw-TotI8hKkJeQXBQHimrgaeiASJKRypSNH4/edit?usp=sharing
["graphs"]: https://github.com/puzzlef/graphs
[SuiteSparse Matrix Collection]: https://suitesparse-collection-website.herokuapp.com
