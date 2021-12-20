# Table of Contents <!-- omit in toc -->

- [1. Data Structures](#1-data-structures)
  - [1.1. Minimum Stack / Minimum Queue (Template/ds/min_queue/)](#11-minimum-stack--minimum-queue-templatedsmin_queue)
    - [1.1.1. Notes](#111-notes)
    - [1.1.2. Resources](#112-resources)
    - [1.1.3. Problems](#113-problems)
  - [1.2. Sparse Table (Template/ds/sparse_table/)](#12-sparse-table-templatedssparse_table)
    - [1.2.1. Notes](#121-notes)
    - [1.2.2. Resources](#122-resources)
    - [1.2.3. Problems](#123-problems)
  - [1.3. Disjoint Set Union (Template/ds/disjoint_set/)](#13-disjoint-set-union-templatedsdisjoint_set)
    - [1.3.1. Notes](#131-notes)
    - [1.3.2. Resources](#132-resources)
    - [1.3.3. Problems](#133-problems)
  - [1.4. Fenwick Tree (Template/ds/fenwick/)](#14-fenwick-tree-templatedsfenwick)
    - [1.4.1. Resources](#141-resources)
    - [1.4.2. Problems](#142-problems)
  - [1.5. Treap (Template/ds/treap/)](#15-treap-templatedstreap)
    - [1.5.1. Resources](#151-resources)
    - [1.5.2. Problems](#152-problems)
  - [1.6. Stairs Container (Template/ds/stair_container.h)](#16-stairs-container-templatedsstair_containerh)
    - [1.6.1. Notes](#161-notes)
    - [1.6.2. Problems](#162-problems)
  - [1.7. Sliding Window (Template/ds/sliding_window/)](#17-sliding-window-templatedssliding_window)
    - [1.7.1. Problems](#171-problems)
  - [1.8. Segment Tree (Template/ds/segment_tree/)](#18-segment-tree-templatedssegment_tree)
    - [1.8.1. Resources](#181-resources)
    - [1.8.2. Problems](#182-problems)
- [2. Algorithms](#2-algorithms)
  - [2.1. Sqrt Decomposition (Template/algo/sqrt/)](#21-sqrt-decomposition-templatealgosqrt)
    - [2.1.1. Resources](#211-resources)
    - [2.1.2. Problems](#212-problems)
  - [2.2. Divide and Conquer](#22-divide-and-conquer)
    - [2.2.1. Notes](#221-notes)
    - [2.2.2. Problems](#222-problems)
- [3. Math](#3-math)
  - [3.1. GCD](#31-gcd)
  - [3.2. Modular Fast Division](#32-modular-fast-division)
  - [3.3. Fibonacci number](#33-fibonacci-number)
    - [3.3.1. Definition](#331-definition)
    - [3.3.2. Properties](#332-properties)

# 1. Data Structures

## 1.1. Minimum Stack / Minimum Queue ([Template/ds/min_queue/](Template/ds/min_queue))

### 1.1.1. Notes
- Use 2 minimum stacks to simulate and maintain minimum queue. ([Template/ds/min_queue/base_min_queue.h](Template/ds/min_queue/base_min_queue.h))

### 1.1.2. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/stack_queue_modification.html)

### 1.1.3. Problems
- [x] [CodeChef - Binary Land](https://www.codechef.com/MAY20A/problems/BINLAND)
- [x] [AtCoder - Knapsack And Queries](https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_d)

## 1.2. Sparse Table ([Template/ds/sparse_table/](Template/ds/sparse_table))

### 1.2.1. Notes
- Idempotent function: Normal sparse table ([base_sparse_table.h](Template/ds/sparse_table/base_sparse_table.h))
- Associative function: Disjoint Sparse Table ([base_disjoint_sparse_table.h](Template/ds/sparse_table/base_disjoint_sparse_table.h))

### 1.2.2. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/sparse-table.html)
- [Disjoint Sparse Table](https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404)

### 1.2.3. Problems
- [x] [SPOJ - RMQSQ](https://www.spoj.com/problems/RMQSQ/): TODO: Segment Tree Revisit
- [x] [SPOJ - THRBL](https://www.spoj.com/problems/THRBL/): TODO: Segment Tree Revisit
- [x] [Codechef - MSTICK](https://www.codechef.com/problems/MSTICK)
- [x] [Codechef - SEAD](https://www.codechef.com/problems/SEAD)
- [x] [Codeforces - Animals and Puzzles](http://codeforces.com/contest/713/problem/D)
- [x] [Codeforces - Trains and Statistics](http://codeforces.com/contest/675/problem/E)
- [x] [SPOJ - Negative Score](https://www.spoj.com/problems/RPLN/)
- [x] [Codeforces - Map](http://codeforces.com/contest/15/problem/D)
- [x] [Codeforces - Awards for Contestants](http://codeforces.com/contest/873/problem/E)
- [x] [Codechef - SEGPROD](https://www.codechef.com/problems/SEGPROD): Disjoint Sparse Table
- [ ] [DevSkills - Multiplication Interval](https://devskill.com/CodingProblems/ViewProblem/19): TODO: Segment Tree
- [x] [Codeforces - Wizards and Roads](https://codeforces.com/contest/167/problem/D): TODO: Segment Tree

## 1.3. Disjoint Set Union ([Template/ds/disjoint_set/](Template/ds/disjoint_set/))

### 1.3.1. Notes
- [Compress jumps along a segment](https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-10): each set keeps track of the next empty index ()
- [Arpa's tricks](https://cp-algorithms.com/data_structures/disjoint_set_union.html#arpa): Offline RMQ using Disjoint set

### 1.3.2. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/disjoint_set_union.html)

### 1.3.3. Problems
- [x] [TIMUS - Anansi's Cobweb](https://acm.timus.ru/problem.aspx?space=1&num=1671)
- [x] [Codeforces - Roads not only in Berland](http://codeforces.com/contest/25/problem/D)
- [x] [TIMUS - Parity](https://acm.timus.ru/problem.aspx?space=1&num=1003)
- [x] [SPOJ - Strange Food Chain](https://www.spoj.com/problems/CHAIN/)
- [x] [SPOJ - COLORFUL ARRAY](https://www.spoj.com/problems/CLFLARR/): Compress jumps along a segment
- [x] [SPOJ - Consecutive Letters](https://www.spoj.com/problems/CONSEC/)
- [x] [Toph - Unbelievable Array](https://toph.co/p/unbelievable-array)
- [x] [HackerEarth - Lexicographically minimal string](https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/lexicographically-minimal-string-6edc1406/)
- [x] [HackerEarth - Fight in Ninja World](https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/containers-of-choclates-1/)
- [x] [Codeforces - Knight Tournament](https://codeforces.com/contest/356/problem/A)

## 1.4. Fenwick Tree ([Template/ds/fenwick/](Template/ds/fenwick/))

### 1.4.1. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/fenwick.html)
- [Range updates and queries](https://cp-algorithms.com/data_structures/fenwick.html#toc-tgt-11): Use multiple fenwick trees
- Lazy computation when restricted by memory: Only compute the points in use ([SPOJ - Ada and Species](https://www.spoj.com/problems/ADACABAA/)), [SPOJ - Zig when you Zag](https://www.spoj.com/problems/ZIGZAG2/)

### 1.4.2. Problems
- [x] [UVA 12086 - Potentiometers](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3238)
- [x] [LOJ 1112 - Curious Robin Hood](https://lightoj.com/problem/curious-robin-hood)
- [x] [LOJ 1266 - Points in Rectangle](https://lightoj.com/problem/points-in-rectangle)
- [x] [Codechef - SPREAD](https://www.codechef.com/problems/SPREAD)
- [ ] [SPOJ - CTRICK](https://www.spoj.com/problems/CTRICK/): TODO: Segment Tree
- [x] [SPOJ - MATSUM](https://www.spoj.com/problems/MATSUM/)
- [x] [SPOJ - DQUERY](https://www.spoj.com/problems/DQUERY/)
- [x] [SPOJ - YODANESS](https://www.spoj.com/problems/YODANESS/)
- [ ] [SRM 310 - FloatingMedian](https://community.topcoder.com/stat?c=problem_statement&pm=6551&rd=9990): TODO: Medium
- [x] [SPOJ - Ada and Behives](https://www.spoj.com/problems/ADABEHIVE/)
- [x] [Hackerearth - Counting in Byteland](https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/counting-in-byteland/)
- [x] [Codeforces - Little Artem and Time Machine](http://codeforces.com/contest/669/problem/E)
- [x] [Codeforces - Hanoi Factory](http://codeforces.com/contest/777/problem/E)
- [x] [SPOJ - Tulip and Numbers](https://www.spoj.com/problems/TULIPNUM/)
- [x] [SPOJ - SUMSUM](https://www.spoj.com/problems/SUMSUM/)
- [x] [SPOJ - Sabir and Gifts](https://www.spoj.com/problems/SGIFT/)
- [x] [SPOJ - The Permutation Game Again](https://www.spoj.com/problems/TPGA/)
- [x] [SPOJ - Zig when you Zag](https://www.spoj.com/problems/ZIGZAG2/): Update and calculate the necessary points only
- [x] [SPOJ - Cryon](https://www.spoj.com/problems/CRAYON/)
- [x] [SPOJ - Weird Points](https://www.spoj.com/problems/DCEPC705/)
- [x] [SPOJ - Its a Murder](https://www.spoj.com/problems/DCEPC206/)
- [x] [SPOJ - Bored of Suffixes and Prefixes](https://www.spoj.com/problems/KOPC12G/)
- [x] [SPOJ - Mega Inversions](https://www.spoj.com/problems/TRIPINV/)
- [x] [Codeforces - Subsequences](http://codeforces.com/contest/597/problem/C)
- [x] [Codeforces - Inversions after Shuffle](http://codeforces.com/contest/749/problem/E)
- [x] [GYM - Cairo Market](http://codeforces.com/problemset/gymProblem/101055/D)
- [ ] [Codeforces - Goodbye Souvenir](http://codeforces.com/contest/849/problem/E): TODO: Segment Tree + Fenwick
- [x] [SPOJ - Ada and Species](https://www.spoj.com/problems/ADACABAA/): Fenwick + Stairs Container
- [x] [Latin American Regionals 2017 - Fundraising](https://matcomgrader.com/problem/9346/fundraising/)
- [x] [SPOJ - Horrible Queries](https://www.spoj.com/problems/HORRIBLE/): Range updates & queries
- [x] [SPOJ - Pyramid Sums 2](https://www.spoj.com/problems/PYRSUM2/): Range updates & queries
- [x] [Codeforces - DZY Loves Fibonacci Numbers](https://codeforces.com/contest/446/problem/C): 3 fenwick + d'Ocagne's identity

## 1.5. Treap ([Template/ds/treap/](Template/ds/treap/))

### 1.5.1. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/treap.html)

### 1.5.2. Problems
- [x] [SPOJ - Ada and Aphids](https://www.spoj.com/problems/ADAAPHID/)
- [x] [SPOJ - Ada and Harvest](https://www.spoj.com/problems/ADACROP/)
- [x] [SPOJ - Ghost Town](https://www.spoj.com/problems/COUNT1IT/)
- [x] [SPOJ - Arrangement Validity](https://www.spoj.com/problems/IITWPC4D/): TODO: Segment Tree Revisit
- [x] [SPOJ - All in One](https://www.spoj.com/problems/ALLIN1/)
- [x] [Codeforces - Yet Another Array Queries Problem](https://codeforces.com/contest/863/problem/D): TODO: Splay Tree Revisit
- [x] [SPOJ - TWIST](https://www.spoj.com/problems/TWIST/): TODO: Splay Tree Revisit
- [x] [SPOJ - KOILINE](https://www.spoj.com/problems/KOILINE/): TODO: Segment Tree Revisit
- [x] [CodeChef - The Prestige](https://www.codechef.com/problems/PRESTIGE)
- [x] [Codeforces - T-Shirts](https://codeforces.com/contest/702/problem/F): TODO: Splay Tree Revisit
- [x] [Codeforces - Yaroslav and Points](https://codeforces.com/contest/295/problem/E): TODO: Segment Tree Revisit

## 1.6. Stairs Container ([Template/ds/stair_container.h](Template/ds/stair_container.h))

### 1.6.1. Notes
- Maintains contour of stairs

### 1.6.2. Problems
- [x] [Codeforces - Ball](http://codeforces.com/contest/12/problem/D)
- [x] [SPOJ - NKTEAM](https://www.spoj.com/problems/NKTEAM/)

## 1.7. Sliding Window ([Template/ds/sliding_window/](Template/ds/sliding_window/))

### 1.7.1. Problems
- [x] [HackerRank - Queries with Fixed Length](https://www.hackerrank.com/challenges/queries-with-fixed-length/problem)
- [x] [Codeforces - R2D2 and Droid Army](http://codeforces.com/problemset/problem/514/D): Modified sliding window without fix window size
- [x] [SPOJ - Miraculous](https://www.spoj.com/problems/TNVFC1M/)

## 1.8. Segment Tree ([Template/ds/segment_tree/](Template/ds/segment_tree/))

### 1.8.1. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/segment_tree.html)

### 1.8.2. Problems
- [ ] [SPOJ - KQUERY](http://www.spoj.com/problems/KQUERY/) [Persistent segment tree / Merge sort tree]
- [x] [Codeforces - Xenia and Bit Operations](https://codeforces.com/contest/339/problem/D)
- [ ] [UVA 11402 - Ahoy, Pirates!](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2397)
- [x] [SPOJ - GSS3](http://www.spoj.com/problems/GSS3/)
- [x] [Codeforces - Distinct Characters Queries](https://codeforces.com/contest/1234/problem/D)
- [x] [Codeforces - Ant colony](https://codeforces.com/contest/474/problem/F)
- [x] [Codeforces - Drazil and Park](https://codeforces.com/contest/515/problem/E)
- [x] [Codeforces - Sereja and Brackets](https://codeforces.com/contest/380/problem/C)
- [ ] [TIMUS - Nikita](https://acm.timus.ru/problem.aspx?space=1&num=2042)
- [x] [Codeforces - Circular RMQ](https://codeforces.com/contest/52/problem/C)
- [ ] [Codeforces - Lucky Array](https://codeforces.com/contest/121/problem/E)
- [ ] [Codeforces - The Child and Sequence](https://codeforces.com/contest/438/problem/D)
- [ ] [Codeforces - Alphabet Permutations](https://codeforces.com/contest/610/problem/E)
- [ ] [Codeforces - Eyes Closed](https://codeforces.com/contest/895/problem/E)
- [ ] [Codeforces - Kefa and Watch](https://codeforces.com/contest/580/problem/E)
- [ ] [Codeforces - A Simple Task](https://codeforces.com/contest/558/problem/E)
- [ ] [Codeforces - SUM and REPLACE](https://codeforces.com/contest/920/problem/F)
- [ ] [COCI - Deda](https://oj.uz/problem/view/COCI17_deda) [Last element smaller or equal to x / Binary search]
- [ ] [Codeforces - The Untended Antiquity](https://codeforces.com/contest/869/problem/E) [2D]
- [x] [CSES - Hotel Queries](https://cses.fi/problemset/task/1143)
- [ ] [CSES - Polynomial Queries](https://cses.fi/problemset/task/1736)
- [ ] [CSES - Range Updates and Sums](https://cses.fi/problemset/task/1735)

# 2. Algorithms

## 2.1. Sqrt Decomposition ([Template/algo/sqrt/](Template/algo/sqrt/))

### 2.1.1. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)

### 2.1.2. Problems
- [x] [UVA 12003 - Array Transformer](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3154)
- [x] [UVA 11990 - Dynamic Inversion](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141): Follow up with Partition Tree
- [x] [SPOJ - Give Away](https://www.spoj.com/problems/GIVEAWAY/)
- [x] [SPOJ - Race Against Time](https://www.spoj.com/problems/RACETIME/)
- [ ] [Codeforces - Destiny](https://codeforces.com/contest/840/problem/D): TODO: Implicit Segment Tree
- [x] [Codeforces - Holes](https://codeforces.com/contest/13/problem/E): TODO: Link Cut Tree
- [x] [Codeforces - XOR and Favorite Number](https://codeforces.com/contest/617/problem/E)
- [x] [Codeforces - Powerful array](https://codeforces.com/contest/86/problem/D)

## 2.2. Divide and Conquer

### 2.2.1. Notes
- Typical steps:
  - Split problems into 2 sub-problems
  - Solve sub-problems recurresively
  - Merge 2 sub-problems in certain ways (e.g. sorted)

### 2.2.2. Problems
- [x] [Codeforces - Radio Stations](https://codeforces.com/contest/762/problem/E): Split by radius, merge by frquency + Fenwick
- [x] [SPOJ - Mean of Array](https://www.spoj.com/problems/MEANARR/): TODO: Segment Tree Revisit

# 3. Math

## 3.1. GCD

- Prefix GCD of a sequence has no more than <img src="https://render.githubusercontent.com/render/math?math=1%2Blog_2a_0"/> distinct values
  - Given a sequence A, its prefix GCD sequence B is defined as <img src="https://render.githubusercontent.com/render/math?math=b_0=a_0"/>, <img src="https://render.githubusercontent.com/render/math?math=b_i=gcd(b_{i-1},a_i)" />
  - Problems:
    - [x] [Codeforces - CGCDSSQ](http://codeforces.com/contest/475/problem/D)

## 3.2. Modular Fast Division

- [Code Example](https://www.codechef.com/viewsolution/16271015)

## 3.3. Fibonacci number

### 3.3.1. Definition
<img src="https://render.githubusercontent.com/render/math?math=F_0=0"/>, <img src="https://render.githubusercontent.com/render/math?math=F_1=1"/>
and
<img src="https://render.githubusercontent.com/render/math?math=F_{n}=F_{n-2}%2BF_{n-1}"/>
for <img src="https://render.githubusercontent.com/render/math?math=n>1"/>

### 3.3.2. Properties
- d'Ocagne's identity:
  - <img src="https://render.githubusercontent.com/render/math?math=F_mF_{n%2B1}-F_{m%2B1}F_n=(-1)^nF_{m-n}"/>
  - <img src="https://render.githubusercontent.com/render/math?math=F_{2n}=F_{n%2B1}^2-F_{n-1}^2=F_n(F_{n%2B1}%2BF_{n-1})"/>
  - <img src="https://render.githubusercontent.com/render/math?math=F_{kn%2B+c}=\sum_{i=0}^{k}{k \choose i}F_{c-i}F_n^iF_{n%2B1}^{k-i}"/>
  - <img src="https://render.githubusercontent.com/render/math?math=F_{kn%2B+c}=\sum_{i=0}^{k}{k \choose i}F_{c%2Bi}F_n^iF_{n-1}^{k-i}"/>
  - Problems:
    - [x] [Codeforces - DZY Loves Fibonacci Numbers](https://../Archive/AtCoder/jag2018summer-day2/D.cppcodeforces.com/contest/446/problem/C): 3 fenwick + d'Ocagne's identity
