# Problem 01 — Hash Table Insertion

**Topic:** Hashing · Arrays · Modulo arithmetic
**Difficulty:** Introductory

## Learning Objective

Understand hash function computation and basic insertion into a fixed-size table.

## Problem Statement

Write a C++ program that:

1. Initializes a fixed-size hash table — an array of size `10` — where every slot starts
   out marked as empty.
2. Reads **5 integer keys** and inserts each one into the table using the hash function
   `h(key) = key % 10`.
3. Prints the full contents of the table, one index per line, using `-1` to represent an
   empty slot.

## Requirements

- Table size is a fixed constant of `10`. Do not resize it.
- The hash function is exactly `key % 10`.
- An empty slot prints as `-1`.
- Print **all 10 indices**, in order, including the empty ones.

## Input

Five integers, whitespace-separated:

```
12 22 32 42 52
```

## Expected Output

```
Index 0: -1
Index 1: -1
Index 2: 52
Index 3: -1
Index 4: -1
Index 5: -1
Index 6: -1
Index 7: -1
Index 8: -1
Index 9: -1
```

### Why does only `52` appear?

This is intentional, not a bug in the sample. Every one of `12 22 32 42 52` hashes to the
same index:

```
12 % 10 == 2
22 % 10 == 2
32 % 10 == 2
42 % 10 == 2
52 % 10 == 2
```

That is a **collision** — five keys competing for one slot. This exercise has *no*
collision handling, so each insertion simply overwrites the previous occupant, and the
last key written (`52`) is the one that survives. Losing four out of five keys is the
whole point: it motivates the next problem, which is collision resolution.

## Before You Write Code

Answer these for yourself first:

- What value marks a slot as empty, and why can't you just use `0`?
- What is the type and size of your table, and where does it live — stack or heap?
- What happens to your hash function if a key is negative? What does `-7 % 10` evaluate
  to in C++?
- What is the time complexity of one insertion here? Of printing the table?

## Build and Run

```sh
g++ -std=c++20 -Wall -Wextra main.cpp -o main.out
./main.out
```

Then type the five keys and press Enter.

## Self-Check

Once it runs, make sure you can explain:

- Why the modulo operator maps any integer into the range `[0, 9]`.
- What specifically was lost when `22` was inserted after `12`.
- What would change if the table size were `11` instead of `10`.

## Extensions (optional)

- Report a collision to `stderr` when you overwrite a non-empty slot.
- Count and print how many keys were actually retained.
- Make the sentinel a named constant instead of a bare `-1` scattered through the code.
