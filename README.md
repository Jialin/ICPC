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
- [2. Algorithms](#2-algorithms)
  - [2.1. Sliding Window (Template/ds/sliding_window/)](#21-sliding-window-templatedssliding_window)
    - [2.1.1. Problems](#211-problems)
- [3. Tricks](#3-tricks)
  - [3.1. GCD](#31-gcd)

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
- [x] [SPOJ - RMQSQ](https://www.spoj.com/problems/RMQSQ/) - Segment Tree Revisit
- [x] [SPOJ - THRBL](https://www.spoj.com/problems/THRBL/) - Segment Tree Revisit
- [x] [Codechef - MSTICK](https://www.codechef.com/problems/MSTICK)
- [x] [Codechef - SEAD](https://www.codechef.com/problems/SEAD)
- [ ] [Codeforces - CGCDSSQ](http://codeforces.com/contest/475/problem/D) - [GCD Trick](#31-gcd)
- [ ] [Codeforces - R2D2 and Droid Army](http://codeforces.com/problemset/problem/514/D)
- [ ] [Codeforces - Maximum of Maximums of Minimums](http://codeforces.com/problemset/problem/872/B)
- [ ] [SPOJ - Miraculous](https://www.spoj.com/problems/TNVFC1M/)
- [ ] [DevSkills - Multiplication Interval](https://devskill.com/CodingProblems/ViewProblem/19)
- [ ] [Codeforces - Animals and Puzzles](http://codeforces.com/contest/713/problem/D)
- [ ] [Codeforces - Trains and Statistics](http://codeforces.com/contest/675/problem/E)
- [ ] [SPOJ - Postering](https://www.spoj.com/problems/POSTERIN/)
- [ ] [SPOJ - Negative Score](https://www.spoj.com/problems/RPLN/)
- [ ] [SPOJ - A Famous City](https://www.spoj.com/problems/CITY2/)
- [ ] [SPOJ - Diferencija](https://www.spoj.com/problems/DIFERENC/)
- [ ] [Codeforces - Turn off the TV](http://codeforces.com/contest/863/problem/E)
- [ ] [Codeforces - Map](http://codeforces.com/contest/15/problem/D)
- [ ] [Codeforces - Awards for Contestants](http://codeforces.com/contest/873/problem/E)
- [ ] [Codeforces - Longest Regular Bracket Sequence](http://codeforces.com/contest/5/problem/C)
- [ ] [Codechef - SEGPROD](https://www.codechef.com/problems/SEGPROD): Disjoint Sparse Table

# 2. Algorithms

## 2.1. Sliding Window ([Template/ds/sliding_window/](Template/ds/sliding_window/))

### 2.1.1. Problems
- [x] [HackerRank - Queries with Fixed Length](https://www.hackerrank.com/challenges/queries-with-fixed-length/problem)

# 3. Tricks

## 3.1. GCD

- Given a sequence A, for a new sequence B where <img src="https://latex.codecogs.com/gif.latex?b_0=a_0"/>, <img src="https://latex.codecogs.com/gif.latex?b_i=gcd(b_{i-1},a_i)" />. There will be no more than <img src="https://latex.codecogs.com/gif.latex?1+log_2a_0" /> distinct value in the sequence B
  - Example Problems: [Codeforces - CGCDSSQ](http://codeforces.com/contest/475/problem/D)
