# MP 1-1: Sophie's World

CMSC 21 machine problem on **functions and running time**: decide whether a number is a **Sophie Germain prime**, and compare how many loop iterations three versions of a primality check need.

## Contents

- [Problem](#problem)
  - [Sophie Germain primes](#sophie-germain-primes)
  - [Input and output](#input-and-output)
  - [The three primality checks](#the-three-primality-checks)
  - [Skipping even numbers](#skipping-even-numbers)
- [Sample](#sample)
- [How the Counts Work](#how-the-counts-work)
- [Restrictions](#restrictions)
- [Approach](#approach)
  - [Returning "prime or not" and a count in one number](#returning-prime-or-not-and-a-count-in-one-number)
  - [Avoiding overflow](#avoiding-overflow)
- [Edge Cases](#edge-cases)
- [Running Time](#running-time)

---

## Problem

### Sophie Germain primes

A **Sophie Germain prime** is a prime `p` where `2p + 1` is also prime.

| `p` | `2p + 1` | Sophie? |
|---|---|---|
| 2 | 5 | yes |
| 3 | 7 | yes |
| 5 | 11 | yes |
| 7 | 15 = 3 × 5 | no |
| 11 | 23 | yes |
| 13 | 27 = 3 × 9 | no |
| 23 | 47 | yes |

The first few are 2, 3, 5, 11, 23, 29, 41, ...

### Input and output

**Input:** one positive integer `x`, where **2 ≤ x ≤ 2,147,483,647**.

**Output:** one line containing:

1. `Sophie` if `x` is a Sophie Germain prime, otherwise `Nophie`.
2. Three iteration counts, one for each version of the primality check. Each count is the iterations spent checking `x`, **plus** the iterations spent checking `2x + 1`.

### The three primality checks

The course's three versions differ only in **how far** the candidate factor `cf` goes:

| Version | Loop | Stops at |
|---|---|---|
| 1. Naive | `for (cf = 2; cf < n; cf++)` | `n − 1` |
| 2. Half | `for (cf = 2; cf <= n/2; cf++)` | `n / 2` |
| 3. Square root | `for (cf = 2; cf * cf <= n; cf++)` | `√n` |

Each loop body checks `n % cf == 0` and `break`s on the first factor found.

### Skipping even numbers

This MP redoes all three versions so they **skip even numbers and even candidate factors**:

- An even `n` (other than 2) is not prime, so no loop is needed at all.
- An odd `n` has no even factors, so only try `cf = 3, 5, 7, 9, ...` (`cf += 2`).

That roughly halves the work. To check 49, try 3, 5, 7, ... instead of 2, 3, 4, 5, 6, 7, ...

---

## Sample

| Input | Output |
|---|---|
| `11` | `Sophie 14 5 2` |
| `13` | `Nophie 6 3 2` |
| `2147483646` | `Nophie 0 0 0` |

---

## How the Counts Work

An **iteration** is one candidate factor tried, including the one that turns out to divide `n`.

**`x = 11`** (prime), then **`2x + 1 = 23`** (prime), so the answer is `Sophie`:

| Version | Candidates for 11 | Candidates for 23 | Total |
|---|---|---|---|
| Naive | 3, 5, 7, 9 → **4** | 3, 5, 7, ..., 21 → **10** | **14** |
| Half | 3 → **1** | 3, 5, 7, 9 → **4** | **5** |
| Square root | 3 → **1** | 3 → **1** | **2** |

**`x = 13`** (prime), then **`2x + 1 = 27`** (not prime, 3 divides it), so the answer is `Nophie`:

| Version | Candidates for 13 | Candidates for 27 | Total |
|---|---|---|---|
| Naive | 3, 5, 7, 9, 11 → **5** | 3 (divides) → **1** | **6** |
| Half | 3, 5 → **2** | 3 → **1** | **3** |
| Square root | 3 → **1** | 3 → **1** | **2** |

**`x = 2147483646`** is even, so it is rejected before any loop runs. `2x + 1` is never checked, since `x` already failed: **0 0 0**.

Two details that the samples pin down:

- **The half version stops before `n / 2`.** The counts match `cf < n / 2` (integer division), not `cf <= n / 2`. For 23, `n / 2` is 11, and the sample's count of 4 means 11 isn't tried (3, 5, 7, 9). With `<=`, 11 would give `Sophie 14 7 2`.
- **`2x + 1` is only checked when `x` is prime.** If `x` isn't prime, the answer is already `Nophie`.

---

## Restrictions

- **No** `sqrt`. Use `cf * cf <= n`.
- **No** Sieve of Eratosthenes.
- **No** structures, global variables or pointers.
- **Only the primality check functions** besides `main`, one per version. Each one is called twice: for `x`, then for `2x + 1`.
- Each function must return **both** whether `n` is prime **and** the iteration count, as a **single returned value**. You must be able to tell whether `n` is prime from that value alone.

---

## Approach

```
main:
    read x
    for each of the 3 versions:
        r1 = check(x)                       ← prime? and count
        if x is prime:
            r2 = check(2x + 1)
        total = count(r1) + count(r2)
    print Sophie/Nophie and the three totals
```

### Returning "prime or not" and a count in one number

Without pointers or structures, a function can only hand back one value. So **encode** both facts into it.

The count can be **0** for a prime (3, 5 and 7 need no iterations in the square-root version) **and** for a non-prime (an even number). That rules out a plain sign trick like "negative means not prime", because −0 is just 0.

One encoding that always works:

| Situation | Return | Decode |
|---|---|---|
| prime, `count` iterations | `count` (≥ 0) | `r >= 0` → prime, count = `r` |
| not prime, `count` iterations | `-(count + 1)` (≤ −1) | `r < 0` → not prime, count = `-r - 1` |

```c
long long checkSqrt(long long n) {
    long long count = 0;
    if (n < 2) return -1;                  // not prime, 0 iterations
    if (n == 2) return 0;                  // prime, 0 iterations
    if (n % 2 == 0) return -1;             // even: not prime, 0 iterations
    for (long long cf = 3; cf * cf <= n; cf += 2) {
        count++;
        if (n % cf == 0)
            return -(count + 1);           // not prime
    }
    return count;                          // prime
}
```

Another option is to return `count` for a prime and `count + LARGE` for a non-prime, where `LARGE` is bigger than any possible count.

### Avoiding overflow

- `x` can be **2,147,483,647**, the largest `int`. Then `2x + 1` = **4,294,967,295**, which doesn't fit in an `int`. Use `long long`.
- `cf * cf` overflows an `int` once `cf` passes 46,340. Use `long long` for `cf` as well.
- The naive count for a large prime is around 2 billion, which is also past `int`'s range. Use `long long` for the counts too, and print them with `%lld`.

---

## Edge Cases

| Input | What to watch for |
|---|---|
| `2` | The only even prime. Handle it before rejecting even numbers. `2x + 1 = 5`, so 2 **is** Sophie |
| `3` | Every version makes few or no iterations for 3 and for 7 |
| Even `x` | `Nophie 0 0 0`, with no loops |
| Large primes | The naive version makes over a billion iterations. It is slow, but it is what's being measured |

---

## Running Time

How many candidates each version tries for a prime `n`, with even candidates skipped:

| Version | Iterations (about) | For n ≈ 1,000,000 | For n ≈ 2 × 10⁹ |
|---|---|---|---|
| Naive | n / 2 | 500,000 | 1,000,000,000 |
| Half | n / 4 | 250,000 | 500,000,000 |
| Square root | √n / 2 | 500 | 22,000 |

The first two grow **linearly** with `n`. The square-root version grows with **√n**, which is why it is the only one that stays fast for large inputs.

**Why √n is enough:** if `n = a × b` with `a ≤ b`, then `a × a ≤ a × b = n`, so `a ≤ √n`. Any composite number has a factor no bigger than its square root, so if nothing up to √n divides `n`, nothing does.
