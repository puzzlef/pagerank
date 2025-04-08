Design of **PageRank algorithm** for link analysis.

All *seventeen* graphs used in below experiments are stored in the
*MatrixMarket (.mtx)* file format, and obtained from the *SuiteSparse*
*Matrix Collection*. These include: *web-Stanford, web-BerkStan,*
*web-Google, web-NotreDame, soc-Slashdot0811, soc-Slashdot0902,*
*soc-Epinions1, coAuthorsDBLP, coAuthorsCiteseer, soc-LiveJournal1,*
*coPapersCiteseer, coPapersDBLP, indochina-2004, italy_osm,*
*great-britain_osm, germany_osm, asia_osm*. The experiments are implemented
in *C++*, and compiled using *GCC 9* with *optimization level 3 (-O3)*.
The system used is a *Dell PowerEdge R740 Rack server* with two *Intel*
*Xeon Silver 4116 CPUs @ 2.10GHz*, *128GB DIMM DDR4 Synchronous Registered*
*(Buffered) 2666 MHz (8x16GB) DRAM*, and running *CentOS Linux release*
*7.9.2009 (Core)*. The execution time of each test case is measured using
*std::chrono::high_performance_timer*. This is done *5 times* for each
test case, and timings are *averaged (AM)*. The *iterations* taken with
each test case is also measured. `500` is the *maximum iterations* allowed.
Statistics of each test case is printed to *standard output (stdout)*, and
redirected to a *log file*, which is then processed with a *script* to
generate a *CSV file*, with each *row* representing the details of a
*single test case*. This *CSV file* is imported into *Google Sheets*,
and necessary tables are set up with the help of the *FILTER* function
to create the *charts*.

<br>


### Comparing with Push computation

There are two ways (algorithmically) to think of the pagerank calculation.
1. Find pagerank by **pushing contribution** to *out-vertices*.
2. Find pagerank by **pulling contribution** from *in-vertices*.

This experiment ([approach-push]) was to try both of these approaches on a
number of different graphs, running each approach 5 times per graph to get a
good time measure. The **push** method is somewhat easier to implement, and is
described in [this lecture]. However, it requires multiple writes per source
vertex. On the other hand, the **pull** method requires 2 additional
calculations per-vertex, i.e., non-teleport contribution of each vertex, and,
total teleport contribution (to all vertices). However, it requires only 1 write
per destination vertex.

While it might seem that pull method would be a clear winner, the results
indicate that although **pull** is always **faster** than *push* approach,
the difference between the two depends on the nature of the graph. Note
that neither approach makes use of *SIMD instructions* which are available
on all modern hardware.

[approach-push]: https://github.com/puzzlef/pagerank/tree/approach-push
[this lecture]: https://www.youtube.com/watch?v=ke9g8hB0MEo

<br>


### Comparing with Direct (class) computation

This experiment ([approach-class]) was for comparing the performance between:
1. Find pagerank using C++ `DiGraph` **class** directly.
2. Find pagerank using **CSR** representation of DiGraph.

Both these approaches were tried on a number of different graphs, running
each approach 5 times per graph to get a good time measure. Using a **CSR**
(Compressed Sparse Row) representation has the potential for **performance**
**improvement** for both the methods due to information on vertices and edges
being stored contiguously. Note that neither approach makes use of *SIMD*
*instructions* which are available on all modern hardware.

[approach-class]: https://github.com/puzzlef/pagerank/tree/approach-class

<br>


### Comparing with Ordered approach

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
of each iteration. Hemalatha Eedi et al. [(1)][eedi] discuss barrierless
non-blocking implementations of the PageRank algorithm, where threads *do not*
*join* together, and thus may be on different iteration number at a time. A
single rank vector is used, and the rank of each vertex is updated once it is
computed (so we should call this the **ordered** approach, where the processing
order of vertices *does* matter).

In this experiment ([approach-ordered]), we compare the **ordered** and
**unordered** approaches with a sequential PageRank implementation. We use a
damping factor of `α = 0.85`, a tolerance of `τ = 10⁻⁶`, and limit the maximum
number of iterations to `L = 500`. The error between iterations is calculated
with *L1 norm*, and the error between the two approaches is also calculated with
*L1 norm*. The unordered approach is considered the *gold standard*, as it has
been described in the original paper by Larry Page et al. [(2)][page]. *Dead*
*ends* in the graph are handled by always teleporting any vertex in the graph at
random (*teleport* approach [(3)][teleport]). The teleport contribution to all
vertices is calculated *once* (for all vertices) at the begining of each
iteration.

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

[approach-ordered]: https://github.com/puzzlef/pagerank/tree/approach-ordered

<br>


### Adjusting Damping factor

Adjustment of the *damping factor α* is a delicate balancing act. For
smaller values of *α*, the convergence is fast, but the *link structure*
*of the graph* used to determine ranks is less true. Slightly different
values for *α* can produce *very different* rank vectors. Moreover, as
α → 1, convergence *slows down drastically*, and *sensitivity issues*
begin to surface.

For this experiment ([adjust-damping-factor]), the **damping factor** `α` (which
is usually `0.85`) is **varied** from `0.50` to `1.00` in steps of `0.05`. This
is in order to compare the performance variation with each *damping factor*. The
calculated error is the *L1 norm* with respect to default PageRank (`α = 0.85`).
The PageRank algorithm used here is the *standard power-iteration (pull)*
based PageRank. The rank of a vertex in an iteration is calculated as
`c₀ + αΣrₙ/dₙ`, where `c₀` is the *common teleport contribution*, `α` is the
*damping factor*, `rₙ` is the *previous rank of vertex* with an incoming edge,
`dₙ` is the *out-degree* of the incoming-edge vertex, and `N` is the *total*
*number of vertices* in the graph. The *common teleport contribution* `c₀`,
calculated as `(1-α)/N + αΣrₙ/N` , includes the *contribution due to a teleport*
*from any vertex* in the graph due to the damping factor `(1-α)/N`, and
*teleport from dangling vertices* (with *no outgoing edges*) in the graph
`αΣrₙ/N`. This is because a random surfer jumps to a random page upon visiting a
page with *no links*, in order to avoid the *rank-sink* effect.

Results indicate that **increasing the damping factor α beyond** `0.85`
**significantly increases convergence time** , and lowering it below
`0.85` decreases convergence time. As the *damping factor* `α` increases
*linearly*, the iterations needed for PageRank computation *increases*
*almost exponentially*. On average, using a *damping factor* `α = 0.95`
increases *iterations* needed by `190%` (`~2.9x`), and using a *damping*
*factor* `α = 0.75` *decreases* it by `41%` (`~0.6x`), compared to
*damping factor* `α = 0.85`. Note that a higher *damping factor* implies
that a random surfer follows links with *higher probability* (and jumps
to a random page with lower probability).

[adjust-damping-factor]: https://github.com/puzzlef/pagerank/tree/adjust-damping-factor

<br>


### Adjusting Tolerance function

It is observed that a number of *error functions* are in use for checking
convergence of PageRank computation. Although [L1 norm] is commonly used
for convergence check, it appears [nvGraph] uses [L2 norm] instead. Another
person in stackoverflow seems to suggest the use of *per-vertex tolerance*
*comparison*, which is essentially the [L∞ norm]. The **L1 norm** `||E||₁`
between two *(rank) vectors* `r` and `s` is calculated as `Σ|rₙ - sₙ|`, or
as the *sum* of *absolute errors*. The **L2 norm** `||E||₂` is calculated
as `√Σ|rₙ - sₙ|2`, or as the *square-root* of the *sum* of *squared errors*
(*euclidean distance* between the two vectors). The **L∞ norm** `||E||ᵢ`
is calculated as `max(|rₙ - sₙ|)`, or as the *maximum* of *absolute errors*.

This experiment ([adjust-tolerance-function]) was for comparing the performance
between PageRank computation with *L1, L2* and *L∞ norms* as convergence check,
for *damping factor* `α = 0.85`, and *tolerance* `τ = 10⁻⁶`. The PageRank
algorithm used here is the *standard power-iteration (pull)* based PageRank. The
rank of a vertex in an iteration is calculated as `c₀ + αΣrₙ/dₙ`, where `c₀` is
the *common teleport contribution*, `α` is the *damping factor*, `rₙ` is the
*previous rank of vertex* with an incoming edge, `dₙ` is the *out-degree* of the
incoming-edge vertex, and `N` is the *total number of vertices* in the graph.
The *common teleport contribution* `c₀`, calculated as `(1-α)/N + αΣrₙ/N` ,
includes the *contribution due to a teleport from* *any vertex* in the graph due
to the damping factor `(1-α)/N`, and *teleport from dangling vertices* (with *no
outgoing edges*) in the graph `αΣrₙ/N`. This is because a random surfer jumps to
a random page upon visiting a page with *no links*, in order to avoid the
*rank-sink* effect.

From the results it is clear that PageRank computation with **L∞ norm**
**as convergence check is the fastest** , quickly followed by *L2 norm*,
and finally *L1 norm*. Thus, when comparing two or more approaches for an
iterative algorithm, it is important to ensure that all of them use the same
error function as convergence check (and the same parameter values). This
would help ensure a level ground for a good relative performance comparison.

Also note that PageRank computation with **L∞ norm** as convergence check
**completes in a single iteration for all the road networks** *(ending with*
*_osm)*. This is likely because it is calculated as `||E||ᵢ = max(|rₙ - sₙ|)`,
and depending upon the *order (number of* *vertices)* `N` of the graph (those
graphs are quite large), the maximum rank change for any single vertex does not
exceed the *tolerance* `τ` value of `10⁻⁶`.

[adjust-tolerance-function]: https://github.com/puzzlef/pagerank/tree/adjust-tolerance-function

<br>


### Adjusting Tolerance

Similar to the *damping factor* `α` and the *error function* used for
convergence check, **adjusting the value of tolerance** `τ` can have a
significant effect. This experiment ([adjust-tolerance]) was for comparing the
performance between PageRank computation with *L1, L2* and *L∞ norms* as
convergence check, for various *tolerance* `τ` values ranging from `10⁻⁰` to
`10⁻¹⁰` (`10⁻⁰`, `5×10⁻⁰`, `10⁻¹`, `5×10⁻¹`, ...). The PageRank algorithm used
here is the *standard power-iteration (pull)* based PageRank. The rank of a
vertex in an iteration is calculated as `c₀ + αΣrₙ/dₙ`, where `c₀` is the
*common teleport contribution*, `α` is the *damping factor*, `rₙ` is the
*previous rank of vertex* with an incoming edge, `dₙ` is the *out-degree* of the
incoming-edge vertex, and `N` is the *total number of vertices* in the graph.
The *common teleport contribution* `c₀`, calculated as `(1-α)/N + αΣrₙ/N` ,
includes the *contribution due to a teleport from any vertex* in the graph due
to the damping factor `(1-α)/N`, and *teleport from dangling vertices* (with *no*
*outgoing edges*) in the graph `αΣrₙ/N`. This is because a random surfer jumps to
a random page upon visiting a page with *no links*, in order to avoid the
*rank-sink* effect.

For various graphs it is observed that PageRank computation with *L1*, *L2*,
or *L∞ norm* as *convergence check* suffers from **sensitivity issues**
beyond certain (*smaller*) tolerance `τ` values, causing the computation to
halt at maximum iteration limit (`500`) without convergence. As *tolerance*
`τ` is decreased from `10⁻⁰` to `10⁻¹⁰`, *L1 norm* is the *first* to suffer
from this issue, followed by *L2 and L∞ norms (except road networks)*. This
*sensitivity issue* was recognized by the fact that a given approach *abruptly*
takes `500` *iterations* for the next lower *tolerance* `τ` value.

It is also observed that PageRank computation with *L∞ norm* as convergence
check **completes in just one iteration** (even for *tolerance* `τ ≥ 10⁻⁶`)
for large graphs *(road networks)*. This again, as mentioned above, is likely
because the maximum rank change for any single vertex for *L∞ norm*, and
the sum of squares of total rank change for all vertices, is quite low for
such large graphs. Thus, it does not exceed the given *tolerance* `τ` value,
causing a single iteration convergence.

On average, PageRank computation with **L∞ norm** as the error function is the
**fastest**, quickly **followed by** **L2 norm**, and **then** **L1 norm**. This
is the case with both geometric mean (GM) and arithmetic mean (AM) comparisons
of iterations needed for convergence with each of the three error functions. In
fact, this trend is observed with each of the individual graphs separately.

Based on **GM-RATIO** comparison, the *relative iterations* between
PageRank computation with *L1*, *L2*, and *L∞ norm* as convergence check
is `1.00 : 0.30 : 0.20`. Hence *L2 norm* is on *average* `70%` *faster*
than *L1 norm*, and *L∞ norm* is `33%` *faster* than *L2 norm*. This
ratio is calculated by first finding the *GM* of *iterations* based on
each *error function* for each *tolerance* `τ` value separately. These
*tolerance* `τ` specific means are then combined with *GM* to obtain a
*single mean value* for each *error function (norm)*. The *GM-RATIO* is
then the ratio of each *norm* with respect to the *L∞ norm*. The variation
of *tolerance* `τ` specific means with *L∞ norm* as baseline for various
*tolerance* `τ` values is shown below.

On the other hand, based on **AM-RATIO** comparison, the *relative*
*iterations* between PageRank computation with *L1*, *L2*, and *L∞ norm*
as convergence check is `1.00 : 0.39 : 0.31`. Hence, *L2 norm* is on
*average* `61%` *faster* than *L1 norm*, and *L∞ norm* is `26%` *faster*
than *L2 norm*. This ratio is calculated in a manner similar to that of
*GM-RATIO*, except that it uses *AM* instead of *GM*. The variation of
*tolerance* `τ` specific means with *L∞ norm* as baseline for various
*tolerance* `τ` values is shown below as well.

[adjust-tolerance]: https://github.com/puzzlef/pagerank/tree/adjust-tolerance

<br>


### Adjusting Tolerance (Ordered approach)

**Unordered PageRank** is the *standard* way of computing PageRank computation,
where *two different rank vectors* are maintained; one representing the
*current* ranks of vertices, and the other representing the *previous* ranks.
Conversely, **ordered PageRank** uses *a single rank vector* for the current
ranks of vertices [(1)][pagerank]. This is similar to barrierfree non-blocking
implementation of PageRank by Hemalatha Eedi et al. [(2)][eedi]. Since ranks are
updated in the same vector (with each iteration), the order in which vertices
are processed *affects* the final outcome (hence the modifier *ordered*).
Nonetheless, as PageRank is a converging algorithm, ranks obtained with either
approach are *mostly the same*.

In this experiment ([adjust-tolerance-ordered]), we perform ordered PageRank
while adjusting the tolerance `τ` from `10^-1` to `10^-14` with three different
tolerance functions: `L1-norm`, `L2-norm`, and `L∞-norm`. We also compare it
with unordered PageRank for the same tolerance and tolerance function.  We use a
damping factor of `α = 0.85` and limit the maximum number of iterations to
`L = 500`. The error between the two approaches is calculated with *L1-norm*. The
unordered approach is considered to be the *gold standard*, as it has been
described in the original paper by Larry Page et al. [(3)][page]. *Dead ends* in the
graph are handled by always teleporting any vertex in the graph at random
(*teleport* approach [(4)][teleport]). The teleport contribution to all vertices is
calculated *once* (for all vertices) at the begining of each iteration.

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

[adjust-tolerance-ordered]: https://github.com/puzzlef/pagerank/tree/adjust-tolerance-ordered

<br>


### Adjusting Iteration scaling

[nvGraph PageRank] appears to use [L2-norm per-iteration scaling]. This is
(probably) required for finding a solution to **eigenvalue problem**. However,
as the *eigenvalue* for PageRank is `1`, this is not necessary. This experiement
([adjust-iteration-scaling]) was for observing if this was indeed true, and that
any such *per-iteration scaling* doesn't affect the number of *iterations*
needed to converge. PageRank was computed with **L1**, **L2**, or **L∞-norm**
and the effect of **L1** or **L2-norm** *scaling of ranks* was compared with
**baseline (L0)**.

Results match the above assumptions, and indeed no performance benefit
is observed (except a reduction in a single iteration for *web-Google*
and *web-NotreDame* graphs).

[adjust-iteration-scaling]: https://github.com/puzzlef/pagerank/tree/adjust-iteration-scaling
[nvGraph PageRank]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu
[L2-norm per-iteration scaling]: https://github.com/rapidsai/nvgraph/blob/main/cpp/src/pagerank.cu#L145

<br>
<br>


## References

- Estimating PageRank on graph streams
- Fast Distributed PageRank Computation
- Reducing Pagerank Communication via Propagation Blocking
- Distributed PageRank computation based on iterative aggregation-disaggregation methods
- Incremental Query Processing on Big Data Streams
- PageRank on an evolving graph
- Streaming graph partitioning for large distributed graphs
- Auto-parallelizing stateful distributed streaming applications
- Time-evolving graph processing at scale
- Towards large-scale graph stream processing platform
- An FPGA architecture for the Pagerank eigenvector problem
- Towards Scaling Fully Personalized PageRank: Algorithms, Lower Bounds, and Experiments
- Parallel personalized pagerank on dynamic graphs
- Fast personalized PageRank on MapReduce
- A Dynamical System for PageRank with Time-Dependent Teleportation
- Fast PageRank Computation on a GPU Cluster
- Accelerating PageRank using Partition-Centric Processing
- Evaluation of distributed stream processing frameworks for IoT applications in Smart Cities
- The power of both choices: Practical load balancing for distributed stream processing engine
- A Survey on PageRank Computing
- Benchmarking Distributed Stream Processing Platforms for IoT Applications
- Toward Efficient Hub-Less Real Time Personalized PageRank
- Identifying Key Users in Online Social Networks: A PageRank Based Approach
- RIoTBench: An IoT benchmark for distributed stream processing systems
- Efficient PageRank Tracking in Evolving Networks
- Efficient Computation of PageRank
- Deeper Inside PageRank
- DISTINGER: A distributed graph data structure for massive dynamic graph processing
- The PageRank Problem, Multiagent Consensus, and Web Aggregation: A Systems and Control Viewpoint
- Cognitive spammer: A Framework for PageRank analysis with Split by Over-sampling and Train by Under-fitting
- FrogWild! -- Fast PageRank Approximations on Graph Engines
- RIoTBench: A Real-time IoT Benchmark for Distributed Stream Processing Platforms
- Approximate Personalized PageRank on Dynamic Graphs
- LBSNRank: personalized pagerank on location-based social networks
- DataMPI: Extending MPI to Hadoop-Like Big Data Computing
- Performance evaluation of big data frameworks for large-scale data analytics
- SP-Partitioner: A novel partition method to handle intermediate data skew in spark streaming
- Practice of Streaming Processing of Dynamic Graphs: Concepts, Models, and Systems
- The applications of graph theory to investing
- Scalability! But at what COST?
- Mapreduce is Good Enough? If All You Have is a Hammer, Throw Away Everything That's Not a Nail!
- G-Store: High-Performance Graph Store for Trillion-Edge Processing
- X-Stream: edge-centric graph processing using streaming partitions
- [PageRank Algorithm, Mining massive Datasets (CS246), Stanford University](https://www.youtube.com/watch?v=ke9g8hB0MEo)
- [SuiteSparse Matrix Collection](https://sparse.tamu.edu)

<br>
<br>


[![](https://i.imgur.com/89cRRdY.jpg)](https://www.youtube.com/watch?v=iMdq5_5eib0)
![](https://ga-beacon.deno.dev/G-KD28SG54JQ:hbAybl6nQFOtmVxW4if3xw/github.com/puzzlef/pagerank)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[SuiteSparse Matrix Collection]: https://sparse.tamu.edu/
[this lecture]: https://www.youtube.com/watch?v=ke9g8hB0MEo
[eedi]: https://ieeexplore.ieee.org/document/9407114
[page]: https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.38.5427
[pagerank]: https://github.com/puzzlef/pagerank
[teleport]: https://gist.github.com/wolfram77/94c38b9cfbf0c855e5f42fa24a8602fc
