# Problem 03 — Collision Handling with Chaining

**Topic:** Hashing · Linked lists · Pointers · Dynamic memory · Ownership
**Difficulty:** Intermediate
**Builds on:** [Problem 01](../01-hash-table-insertion/README.md) · [Problem 02](../02-hash-table-search/README.md)

## Learning Objective

Fix the data loss you saw in Problems 01 and 02 by giving every slot a linked list
instead of a single value. Along the way: heap allocation, pointer traversal, node
removal, and who is responsible for freeing what.

## Background

Problems 01 and 02 used one `int` per slot, so inserting `12`, `22`, and `32` left only
`32` alive — the other two were overwritten. Problem 02 then had to report `Key 22 not
found` for a key you had definitely inserted.

**Chaining** solves this. Each slot holds a pointer to a linked list of every key that
hashed there. Nothing is overwritten, so nothing is lost:

```
Index 2: 32 -> 22 -> 12 -> NULL
```

You will also move from loose functions in `main` to a `HashTable` **class**. The table
array becomes private state, and insert/search/remove/display become the public
operations that are allowed to touch it.

## What to Build

A `HashTable` class of `TABLE_SIZE = 10` slots, where each slot is a `Node*`.

```cpp
struct Node {
    int key;
    Node* next;
};
```

### Part A — Construction, insert, display

- The constructor sets every slot to `nullptr` (an empty chain).
- `insert(key)` allocates a new node and links it at the **head** of the chain for
  `key % 10`. Head insertion is O(1); appending to the tail would be O(n).
- `display()` prints all 10 indices with their full chains.

### Part B — Search

- `search(key)` returns `true` if the key is in the table.
- Hash to the right slot first, then walk **only that chain**. Do not scan all 10 slots.

### Part C — Remove

- `remove(key)` unlinks the node holding `key` and frees it.
- The head case (`prev == nullptr`) and the middle case need different pointer surgery.
  Removing a key that isn't present must be safe and do nothing.

### Part D — The destructor

Every `insert` calls `new`. Nothing in Steps A–C frees those nodes when the table dies,
so every node still in a chain at the end of `main` is a **memory leak**.

Write a destructor that walks all 10 chains and deletes every node. Watch out for the
classic bug: once you `delete curr`, reading `curr->next` is use-after-free. Save the
next pointer *before* you delete.

## Requirements

- `table` and `hashFunction` are `private`. Only the class touches the array.
- Search and remove must hash first — no scanning the whole table.
- `display()` prints, for each index: `<i>: ` then `<key> -> ` for each node, then `NULL`.
- No leaks: every `new` has a matching `delete`.

## Expected Output

For `insert(12)`, `insert(22)`, `insert(32)`:

```
0: NULL
1: NULL
2: 32 -> 22 -> 12 -> NULL
3: NULL
4: NULL
5: NULL
6: NULL
7: NULL
8: NULL
9: NULL
```

`32` is at the front because each insertion goes at the head — the chain is in reverse
insertion order. All three keys survive. Compare that to Problem 01, where the same
three inserts left only `32`.

## Before You Write Code

- `Node* table[10]` — is that an array of nodes, or an array of pointers to nodes? How
  many bytes is it, and where do the nodes themselves live?
- In `insert`, why must `newNode->next = table[index]` come *before*
  `table[index] = newNode`? What breaks if you swap those two lines?
- In `remove`, why do you need a `prev` pointer at all? Why can't you just use `curr`?
- Who owns the nodes? What does "owns" mean here — what obligation does it create?
- What is the complexity of `search` in the average case? In the worst case, where every
  key collides?

## Build and Run

```sh
g++ -std=c++20 -Wall -Wextra main.cpp -o main.out
./main.out
```

To catch memory bugs — leaks, use-after-free, double frees:

```sh
g++ -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined main.cpp -o main.out
./main.out
```

If your destructor is missing or wrong, the sanitizer will say so. A silent run is the
goal.

## Self-Check

- Why does chaining lose no data when four keys hash to the same index?
- Trace what `insert(42)` does to a chain that already holds `32 -> 22 -> 12`. Which
  pointers change, and in what order?
- If all 5 keys hash to index 2, what has your table effectively become?
- What happens if you `delete curr` and then read `curr->next`?

## Extensions (optional)

- Make `remove` return `bool` so callers know whether anything was removed.
- Reject duplicate keys in `insert` — where does that check go, and what does it cost?
- Add a `size()` and a load-factor report (`size / TABLE_SIZE`).
- **Rule of three:** copy this `HashTable` into another variable and run it under the
  sanitizer. The default copy constructor copies the pointers, so two tables now own the
  same nodes and both destructors free them — a double free. Fix it, or delete the copy
  operations to make the mistake impossible.
- Replace the raw `Node*` chains with `std::unique_ptr<Node>` and see how much of the
  destructor disappears.
