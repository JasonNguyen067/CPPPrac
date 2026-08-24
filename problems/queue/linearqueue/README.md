# Problem — Queues: Linear Array Implementation

**Topic:** Queues · FIFO · Classes · Array-backed containers · Bounds checking
**Also known as:** simple queue, non-circular array queue
**Difficulty:** Intermediate

## Objective

You have been *using* `std::queue` in the neighbouring folders — `push`, `pop`, `front`,
`back`, `size`, `empty`. Now build one. A fixed-size queue of capacity 5, backed by a
plain array, with the three operations named below.

The point is not just that it works. The point is that this design has a specific,
famous flaw, and Part 3 makes you watch it happen. Fixing that flaw is the next problem.

## The Operations

| Operation | Meaning |
|---|---|
| `enqueue(x)` | Add an element to the **back** |
| `dequeue()` | Remove **and return** the **front** element |
| `isEmpty()` | Is the queue empty? |
| `isFull()` | Is the queue at capacity? *(given to you)* |

A queue is **FIFO** — first in, first out. This is the whole difference from the stack in
Problem 05: there you pushed and popped at the same end, here you add at one end and
remove from the other. That is why one index was enough for a stack and two are not.

## The Two Indices

Everything hinges on two integers, and on you holding their meaning fixed:

- `frontIdx` — index of the first element. Starts at `0`.
- `rearIdx` — index of the **last** element, *not* one past it. Starts at `-1`.
- Empty is therefore `frontIdx > rearIdx` — which is true at construction, since `0 > -1`.
- Full is `rearIdx == CAPACITY - 1`.

`enqueue` increments `rearIdx` first, then writes at that index. `dequeue` reads at
`frontIdx`, then increments it. Notice that neither index ever goes backwards.

Hold that last sentence in mind. It is the flaw.

## A Note on the Class Boilerplate

Two small modern-C++ choices in the scaffold, worth understanding rather than copying:

- `static constexpr int CAPACITY = 5;` rather than `static const`. `constexpr` guarantees a
  compile-time constant usable in constant expressions — array bounds, template arguments —
  and since C++17 it is implicitly `inline`, so it needs no out-of-class definition.
- `Queue() = default;` with the initial values written on the members themselves
  (`int frontIdx = 0;`). These are *default member initializers*. A member-initializer list
  — `Queue() : frontIdx(0), rearIdx(-1) {}` — is equally correct and you will see it
  everywhere; the default-member form just keeps each initial value next to the member it
  belongs to, so adding a fourth member later cannot silently leave it uninitialized.

`data` is deliberately left uninitialized. No slot is ever read before it has been written,
so zeroing all five would be busywork that hides, rather than prevents, a bounds bug.

### Why there is no `currentSize` member here

It is tempting to track a count and write `isFull()` as `currentSize == CAPACITY`. **Do not
do that in this problem.** In a linear queue `currentSize` and `rearIdx` answer different
questions — how many elements you hold, versus how much of the array you have burned
through — and they diverge the moment you dequeue.

Fill 1..5, dequeue twice, then enqueue. `currentSize` is 3, so a count-driven `isFull()`
says "not full", so `enqueue` runs, `rearIdx` becomes `5`, and you write `data[5]` on a
five-element array:

```
before bad enqueue: frontIdx=2 rearIdx=4 currentSize=3
after  bad enqueue: frontIdx=7 rearIdx=5 currentSize=4
```

`data` sits at offset 0 and `frontIdx` at offset 20 — which is exactly where `data[5]`
lands. The enqueued `7` overwrote `frontIdx`. The queue corrupted its own bookkeeping and
kept running. (`g++ -fsanitize=undefined` reports it: *index 5 out of bounds for type
'int[5]'*.)

A count member is the *right* design — for the **circular** queue, where `rearIdx` wraps
with `%` and can never leave the array, and where `front == rear` is ambiguous between full
and empty and needs a counter to tell them apart. Here, only `rearIdx` knows about the
array bounds, so only `rearIdx` may guard them.

## The Two Edge Cases

**Dequeue on an empty queue.** There is no element to return. Print an error to
`std::cerr`, return the sentinel `-1`, and leave both indices untouched. (Same weakness
you accepted in the stack problem: a queue legitimately holding `-1` is indistinguishable
from an error. The extensions address it.)

**Enqueue on a full queue.** Report the overflow to `std::cerr` and discard the value.
Never write past the end of the array.

## Part 3 — The Flaw

Fill the queue with `1..5`, then dequeue twice. Two slots at the front of the array are
now unused. Then try to enqueue.

It fails. `isFull()` still reports true, because `rearIdx` is still `4` and it never moves
back. This condition has a name — **false overflow**: the queue reports itself full while
slots sit free. The queue reports itself full while holding only three elements and owning five
slots. The array has not run out of room — the *indices have run off the end of it*.

There are two ways out, and they are separate problems:

- **[`shiftingqueue/`](../shiftingqueue/)** — pin `front` at `0` and slide every element
  down on dequeue. Kills false overflow outright, but makes dequeue O(n).
- **[`circularbasedarrayqueue/`](../circularbasedarrayqueue/)** — let the indices wrap with
  `%`. Kills false overflow *and* keeps dequeue O(1). This is the real answer.

Do this one first and feel the flaw, then go fix it.

## Requirements

- `data`, `frontIdx` and `rearIdx` are `private`. Only the class methods touch them.
- No `std::queue`, no `std::vector`, no `std::deque`. Build it yourself.
- Never index outside the array, in any operation, for any input.
- `dequeue` must both remove and return — do not split it into two calls.
- Do **not** fix the Part 3 flaw here. Let it happen. That is the lesson.

## Expected Output

```
--- Part 1: basics ---
isEmpty: 1  (expect 1)
enqueued 10 20 30
isEmpty: 0  (expect 0)
dequeue: 10  (expect 10)
dequeue: 20  (expect 20)
dequeue: 30  (expect 30)
isEmpty: 1  (expect 1)

--- Part 2: the edge cases ---
dequeue on empty: -1  (expect -1)
filled with 1..5, isFull: 1  (expect 1)
enqueue 6 on a full queue -- value is discarded

--- Part 3: the flaw ---
dequeue: 1  (expect 1)
dequeue: 2  (expect 2)
two slots are free at the front, but enqueue 7 still fails:
isFull: 1  (expect 1 -- and that is the flaw)
```

Plus three error messages on `std::cerr` — the dequeue on empty, the discarded `6`, and
the discarded `7`:

```
error: dequeue on an empty queue
error: enqueue on a full queue, discarding 6
error: enqueue on a full queue, discarding 7
```

## Before You Write Code

- Why does `rearIdx` start at `-1` and `frontIdx` at `0`? What breaks if you start both
  at `0`?
- Why is `rearIdx` the index of the last element rather than one past it? Write
  `isFull()` both ways and see which one reads better.
- The stack needed one index; the queue needs two. What exactly about FIFO forces that?
- In `enqueue`, why increment *before* writing? In `dequeue`, why read *before*
  incrementing? What goes wrong if you swap either pair?
- Which of your four methods should be `const`, and why?
- Why does guarding `enqueue` with a count instead of `rearIdx` write out of bounds
  here, but not in a circular queue?
- After Part 3, how many elements does the queue actually hold, and how many array slots
  are unused? Where did the slots go?
- What is the complexity of `enqueue` and `dequeue` here? Compare to dequeuing by
  shifting every element down one — what would that cost instead?

## Build and Run

```sh
g++ -std=c++20 -Wall -Wextra main.cpp -o main.out
./main.out
```

The unfinished scaffold warns about unused private fields. Those warnings disappear on
their own once the three methods are actually implemented — treat them as a to-do list.

## Self-Check

- What does FIFO mean, and which index does each operation move?
- Trace `frontIdx` and `rearIdx` through: enqueue, enqueue, dequeue, enqueue. What are
  the two values after each step?
- After dequeuing every element, is `frontIdx` back at `0`? If not, where is it, and what
  does that cost you?
- If you enqueued a 6th item into a 5-slot queue without the `isFull()` check, what
  memory would you be writing to?

## Extensions (optional)

- **Fix the flaw.** Make the indices wrap with `%` — that is the circular queue, and it
  earns its own folder.
- Add `front()` and `back()` that peek without removing, mirroring `std::queue`.
- Add `size()`. In *this* design, what expression gives the count? Does the same
  expression still work once the indices wrap?
- Make `dequeue` report failure honestly instead of returning `-1`: throw, return
  `std::optional<int>`, or make `isEmpty()` a precondition the caller must check. Which
  do you pick, and why?
- Templatize it — `template <typename T> class Queue` — same move as the stack extension,
  and you already have a `templates/` folder to draw on.
