# Traveler Salesman Problem

Discution and possible solutions of the Traveler Salesman Problem.

> Find the shortest path that connects a set of cities, visiting each of them exactly once, ending in the same city it started from.

The problem is solved in two different ways:

- __Brute Force__: chek every possible path and find the shortest one $\left(O\left(\frac{(n_{cities}-1)!}{2}\right)\right)$.
- __Minimum Spanning Trees__: find an approximate solution using the _MST_ and _Prim's algorithm_ $\left(O\left(n_{nodes}\log\left(\frac{m_{edges}}{n_{nodes}}\right)\right)\right)$.

## Code

- [SRC](src/)
    - [Main](src/main.cpp)
    - [Brute Force](src/Bruteforce.cpp)
    - MST - uploading.

## Setting Parameters

It's possible to sets the parameters using the [Makefile](Makefile).

```bash
# PARAMETERS
NCITIES = 8

# MAKEFILE CODE Continues
```
