# Problem 04 — Find the Maximum Value in an Array

**Topic:** Arrays · Loops · Comparison · Initialization
**Difficulty:** Introductory

## Learning Objective

Traverse an array while carrying state across iterations, and understand why the
*starting value* of that state is the part most people get wrong.

## Problem Statement

Write a C++ program that:

1. Declares an integer array of size `4`.
2. Prompts the user to enter 4 integer values.
3. Stores the values in the array.
4. Finds and displays the largest element.

## Requirements

- **Do not use built-in functions** such as `std::max`, `std::max_element`, or
  `std::sort`. Write the comparison loop yourself.
- The array is fixed at size `4`.
- Your max-finding logic must work for **any** four integers, including all-negative
  input.

## Input

```
4 9 2 7
```

## Expected Output

```
Enter 4 numbers:
The maximum value is: 9
```

## The Trap

Almost everyone writes this first:

```cpp
int max = 0;
for (...) if (arr[i] > max) max = arr[i];
```

It passes the sample input. Now try it on:

```
-4 -9 -2 -7
```

It prints `0` — a number that is not in your array at all. Nothing in the input is
greater than `0`, so `max` is never updated and the seed value leaks into your answer.

The fix is to seed `max` with something that is *actually an element of the array*
rather than a guess about what elements look like. Once you do, the answer is always a
real element, whatever the input.

Test your finished program on all-negative input before you call it done.

## Before You Write Code

- What should `max` be initialized to, and why is that choice safe for every possible
  input?
- If you seed `max` with `arr[0]`, what index should your loop start at? What does the
  comparison at index `0` accomplish?
- `<climits>` gives you `INT_MIN`. That's a second valid seed — what are the tradeoffs
  versus using `arr[0]`?
- What is the time complexity? Could any algorithm find the maximum in fewer
  comparisons?
- What should `find_max` do if `size` were `0`? Is there a right answer?

## Build and Run

```sh
g++ -std=c++20 -Wall -Wextra main.cpp -o main.out
./main.out
```

## Self-Check

- Why does `int max = 0;` produce a wrong answer for all-negative input, and why does it
  still look correct on the sample?
- How many comparisons does your loop perform for an array of 4? Of `n`?
- If you had to also report the *index* of the maximum, what would change?

## Extensions (optional)

- Return the index of the maximum instead of the value. What do you return if the array
  is empty?
- Find the maximum **and** minimum in a single pass.
- Find the second-largest value in one pass. Careful with duplicates — is the
  second-largest of `9 9 2 7` equal to `9` or `7`? Decide, then make your code match.
