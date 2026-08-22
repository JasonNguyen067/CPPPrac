# Problem 02 — Searching in a Hash Table

**Topic:** Hashing · Lookup · Sentinel values
**Difficulty:** Introductory
**Builds on:** [Problem 01 — Hash Table Insertion](../01-hash-table-insertion/README.md)

## Learning Objective

Understand hash table lookup — why a hash table can find a key without scanning the
whole array, and what makes that guarantee break down.

## Problem Statement

Extend your Problem 01 program so that, after building the table, it can search it.

1. Initialize a fixed-size hash table (array of size `10`), all slots empty (`-1`).
2. Read **5 integer keys** and insert each using `h(key) = key % 10`.
3. Print the table, same format as Problem 01.
4. Read **one more integer** — the search key.
5. Report whether that key is in the table, and if so, at which index.

## Requirements

- Search must use the **same hash function** as insertion. Do not loop over the array
  looking for the key — that defeats the entire purpose of a hash table.
- A successful search prints: `Key 22 found at index 2`
- An unsuccessful search prints: `Key 99 not found`
- Searching must not modify the table.

## Input

Five keys to insert, then one key to search for:

```
12 22 33 44 55
22
```

## Expected Output

```
Index 0: -1
Index 1: -1
Index 2: 22
Index 3: 33
Index 4: 44
Index 5: 55
Index 6: -1
Index 7: -1
Index 8: -1
Index 9: -1
Key 22 found at index 2
```

## The Case That Matters

Now run your finished program on Problem 01's original input, and search for `22`:

```
12 22 32 42 52
22
```

You will get:

```
Key 22 not found
```

**You inserted 22. The program says it isn't there.** Sit with that before moving on.

Nothing is wrong with your search function — it is behaving exactly as specified. The
damage was done at insert time: `32`, `42`, and `52` each hashed to index 2 and
overwrote whatever was sitting there. By the time you search, `22` genuinely is gone.

This is the cost of a hash table with no collision handling. Lookup is fast — one
modulo, one array access, O(1) — but the table silently loses data, and a search that
returns "not found" cannot tell you whether the key was never inserted or was evicted.
Collision resolution, the next problem, is what buys back correctness.

## Before You Write Code

- Your `search` needs to communicate two things: found or not, and where. What are your
  options for returning both? Which would you pick, and why?
- If you return `-1` to mean "not found", and `-1` is also the sentinel for an empty
  slot — are those the same `-1`? What breaks if a user inserts the key `-1`?
- Should `search` take the table by `const` reference or plain array? What does `const`
  buy you here?
- What is the complexity of your search? How does it compare to scanning a plain
  unsorted array of 10 elements?

## Build and Run

```sh
g++ -std=c++20 -Wall -Wextra main.cpp -o main.out
./main.out
```

## Self-Check

- Why doesn't search need a loop?
- If the table had 1,000,000 slots instead of 10, how much slower would search get?
- Give an input where searching for a key you inserted correctly returns "not found",
  and explain the exact moment the key was lost.

## Extensions (optional)

- Distinguish "never inserted" from "evicted by a collision" — what extra state would
  that require?
- Add a `remove(key)` operation. What should a removed slot be set to, and why is
  reusing `EMPTY` a subtle trap for search?
