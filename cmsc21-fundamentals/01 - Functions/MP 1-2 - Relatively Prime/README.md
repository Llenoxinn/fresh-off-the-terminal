# MP 1-2: Filipinos be like — we all relative(ly prime)

CMSC 21 machine problem on **functions and running time**: decide whether two integers are **relatively prime**, once with a linear-time search and once with the **Euclidean algorithm**, and count the iterations each one takes.

## Contents

- [Files](#files)
- [Problem](#problem)
  - [Relatively prime numbers](#relatively-prime-numbers)
  - [Input and output](#input-and-output)
- [Sample](#sample)
- [Solution 1: Naive (linear)](#solution-1-naive-linear)
- [Solution 2: Euclidean algorithm (sub-linear)](#solution-2-euclidean-algorithm-sub-linear)
- [Constraints](#constraints)
- [Why Euclid Works](#why-euclid-works)
- [Running Time](#running-time)
- [Edge Cases](#edge-cases)

---

## Files

| File | Description |
|---|---|
| [AreWeRelatives.c](AreWeRelatives.c) | Solution: `amINaiveForYou` (linear search down from the smaller number) and `euclideanAlgae` (Euclidean algorithm), each with exactly 2 arguments |

```bash
gcc -Wall -o relatives AreWeRelatives.c
echo "11 23" | ./relatives
```

---

## Problem

### Relatively prime numbers

Two integers are **relatively prime** (or **coprime**) if their greatest common factor (GCF, also called GCD) is **1**.

| Pair | GCF | Relatively prime? |
|---|---|---|
| 11, 23 | 1 | yes |
| 37, 43 | 1 | yes |
| 49, 25 | 1 | yes, even though neither is prime |
| 125, 525 | 25 | no |

### Input and output

**Input:** two positive integers.

**Output:** two lines, one per solution. Each line is `Yes` or `No`, followed by the number of iterations that solution took.

```
<naive answer> <naive iterations>
<euclid answer> <euclid iterations>
```

Only `main` reads input and prints. The two functions just compute.

---

## Sample

| Input | Output |
|---|---|
| `11 23` | `Yes 10`<br>`Yes 2` |
| `23 11` | `Yes 10`<br>`Yes 2` |
| `37 43` | `Yes 36`<br>`Yes 3` |
| `43 37` | `Yes 36`<br>`Yes 3` |
| `25 49` | `Yes 24`<br>`Yes 3` |
| `49 25` | `Yes 24`<br>`Yes 3` |
| `125 525` | `No 101`<br>`No 2` |
| `525 125` | `No 101`<br>`No 2` |

Swapping the inputs never changes the output. Both solutions treat the pair the same way regardless of order.

---

## Solution 1: Naive (linear)

Search for a common factor greater than 1. The sample counts show the search goes **downward**, from the smaller number to 2, and stops at the **first** (largest) common factor:

```c
int naive(int a, int b) {
    int small = a < b ? a : b;
    int count = 0;
    for (int cf = small; cf >= 2; cf--) {
        count++;
        if (a % cf == 0 && b % cf == 0)
            return /* not relatively prime, with count */;
    }
    return /* relatively prime, with count */;
}
```

Checking the counts:

| Pair | Candidates tried | Count | Answer |
|---|---|---|---|
| 11, 23 | 11, 10, ..., 2 | 10 | Yes |
| 37, 43 | 37, 36, ..., 2 | 36 | Yes |
| 25, 49 | 25, 24, ..., 2 | 24 | Yes |
| 125, 525 | 125, 124, ..., **25** (divides both) | 125 − 25 + 1 = **101** | No |

When the numbers are relatively prime, the count is always `min − 1`. When they aren't, it's `min − GCF + 1`.

---

## Solution 2: Euclidean algorithm (sub-linear)

Instead of trying candidates, repeatedly replace the pair `(a, b)` with `(b, a % b)`. When the remainder reaches **0**, the last non-zero value is the GCF.

**49 and 25**

```
49 % 25 = 24
25 % 24 = 1
24 %  1 = 0      → GCF = 1, relatively prime
```

**121 and 55**

```
121 % 55 = 11
 55 % 11 = 0     → GCF = 11, not relatively prime
```

**21 and 13**

```
21 % 13 = 8
13 %  8 = 5
 8 %  5 = 3
 5 %  3 = 2
 3 %  2 = 1
 2 %  1 = 0      → GCF = 1, relatively prime
```

These are consecutive Fibonacci numbers, which are the worst case for Euclid: every step reduces the pair by the least possible amount.

> The original statement labels this example "13 18" but computes it with 21. It also skips the `3 % 2 = 1` step.

**What the sample counts:** one iteration per `%` operation, starting with the **larger** number first.

| Pair | Steps (larger first) | Count |
|---|---|---|
| 11, 23 | 23 % 11 = 1, 11 % 1 = 0 | 2 |
| 37, 43 | 43 % 37 = 6, 37 % 6 = 1, 6 % 1 = 0 | 3 |
| 25, 49 | 49 % 25 = 24, 25 % 24 = 1, 24 % 1 = 0 | 3 |
| 125, 525 | 525 % 125 = 25, 125 % 25 = 0 | 2 |

Starting with the smaller number first adds one extra step: `11 % 23 = 11` just swaps the pair. The statement's `55 % 121` example does this, but the samples give the same count for both orders. So **put the larger number first** before looping:

```c
int euclid(int a, int b) {
    if (a < b) { int t = a; a = b; b = t; }   // larger first
    int count = 0;
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
        count++;
    }
    // a is now the GCF
    return /* (a == 1), with count */;
}
```

---

## Constraints

- Besides `main`, **exactly 2 functions**: one naive, one Euclidean.
- Each function takes **exactly 2 arguments**.
- **No** global variables, pointers or structures.
- **No printing** in the functions.

Since each function can return only **one** value, and there's no pointer or structure to carry a second one, the answer and the count must be **encoded together**. For example:

| Situation | Return | Decode in `main` |
|---|---|---|
| relatively prime, `count` iterations | `count` | `r >= 0` → `Yes`, count = `r` |
| not relatively prime, `count` iterations | `-count` | `r < 0` → `No`, count = `-r` |

Here the plain sign trick is safe, because the count of a `No` result is never 0: at least one candidate (or one `%`) runs before a common factor can be found. A count of 0 can only happen for a `Yes` (when one input is 1), and `0` decodes as `Yes`. Compare this with [Sophie's World](../MP%201-1%20-%20Sophies%20World/), where 0 can mean either answer.

---

## Why Euclid Works

Any number that divides both `a` and `b` also divides `a − b`, `a − 2b`, ..., and so `a % b`, which is `a` minus some multiple of `b`. The reverse holds too. So:

> **gcd(a, b) = gcd(b, a % b)**

Each step replaces the pair with a smaller one that has the **same** GCF, until the second number is 0. Since gcd(g, 0) = g, the first number is then the answer.

---

## Running Time

| Pair | Naive | Euclid |
|---|---|---|
| 11, 23 | 10 | 2 |
| 37, 43 | 36 | 3 |
| 1,000,000 and 999,999 | 999,998 | 2 |
| 1,836,311,903 and 1,134,903,170 (Fibonacci) | about 1.1 billion | 44 |

- **Naive** is **linear**: up to `min(a, b)` iterations.
- **Euclid** is **logarithmic**: every two steps at least halve the larger number, so it takes at most about 2 × log₂(min) steps. Even for the largest `int` values, that's under 50.

---

## Edge Cases

| Case | Note |
|---|---|
| `a == b` | GCF is the number itself, so `No` unless both are 1. The naive count is 1 (the first candidate divides both) |
| One input is 1 | gcd is 1, so `Yes`. The naive loop from 1 down to 2 runs **0** times. Euclid's count is 1 (`a % 1 = 0`) |
| Both inputs are 1 | `Yes`. The naive count is 0 and Euclid's is 1 (`1 % 1 = 0`) |
| Order of inputs | Outputs must be identical. Swap so the larger is first for Euclid |
