# Table of Contents <!-- omit in toc -->

- [1. Data Structures](#1-data-structures)
  - [1.1. Minimum Stack / Minimum Queue (Template/ds/min_queue/)](#11-minimum-stack--minimum-queue-templatedsmin_queue)
    - [1.1.1. Notes](#111-notes)
    - [1.1.2. Resources](#112-resources)
    - [1.1.3. Problems](#113-problems)
  - [1.2. Sparse Table (Template/ds/rmq/)](#12-sparse-table-templatedsrmq)
    - [Notes](#notes)
    - [1.2.1. Resources](#121-resources)
    - [1.2.2. Problems](#122-problems)
- [2. Algorithms](#2-algorithms)
  - [2.1. Sliding Window (Template/ds/sliding_window/)](#21-sliding-window-templatedssliding_window)
    - [2.1.1. Problems](#211-problems)

# 1. Data Structures

## 1.1. Minimum Stack / Minimum Queue ([Template/ds/min_queue/](Template/ds/min_queue))

### 1.1.1. Notes
- Use 2 minimum stacks to simulate and maintain minimum queue. ([Template/ds/min_queue/base_min_queue.h](Template/ds/min_queue/base_min_queue.h))

### 1.1.2. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/stack_queue_modification.html)

### 1.1.3. Problems
- [x] [CodeChef - Binary Land](https://www.codechef.com/MAY20A/problems/BINLAND)
- [x] [AtCoder - Knapsack And Queries](https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_d)

## 1.2. Sparse Table ([Template/ds/rmq/](Template/ds/rmq))

### Notes
- Normal sparse table answers queries in O(1) if combine function is idempotent.
- Disjoint Sparse Table could answers queries in O(1) for assoicative functions.

### 1.2.1. Resources
- [CP Algorithm](https://cp-algorithms.com/data_structures/sparse-table.html)
- [Disjoint Sparse Table](https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404)

### 1.2.2. Problems
- [ ] [SPOJ - RMQSQ](https://www.spoj.com/problems/RMQSQ/)
- [ ] [SPOJ - THRBL](https://www.spoj.com/problems/THRBL/)
- [ ] [Codechef - MSTICK](https://www.codechef.com/problems/MSTICK)
- [ ] [Codechef - SEAD](https://www.codechef.com/problems/SEAD)
- [ ] [Codeforces - CGCDSSQ](http://codeforces.com/contest/475/problem/D)
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
- [ ] [Codechef - SEGPROD](https://www.codechef.com/problems/SEGPROD): Disjoint

# 2. Algorithms

## 2.1. Sliding Window ([Template/ds/sliding_window/](Template/ds/sliding_window/))

### 2.1.1. Problems
- [x] [HackerRank - Queries with Fixed Length](https://www.hackerrank.com/challenges/queries-with-fixed-length/problem)
