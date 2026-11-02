# 04 - Nested Loops

CMSC 11 machine problems on loops inside loops, followed by a reference covering everything you need to know about nested loops in C.

## Contents

- [Machine Problems](#machine-problems)
  - [Problem A: First n Perfect Numbers](#problem-a-first-n-perfect-numbers--a-nthperfectc)
  - [Problem B: Primality Check without Using Modulo](#problem-b-primality-check-without-using-modulo--b-primalitycheckc)
- [Nested Loops in C](#nested-loops-in-c)
  1. [What a nested loop is](#1-what-a-nested-loop-is)
  2. [Counting iterations](#2-counting-iterations)
  3. [Inner loops that depend on the outer loop](#3-inner-loops-that-depend-on-the-outer-loop)
  4. [Resetting inner variables](#4-resetting-inner-variables)
  5. [`break` and `continue` in nested loops](#5-break-and-continue-in-nested-loops)
  6. [Printing patterns](#6-printing-patterns)
  7. [Grids and tables](#7-grids-and-tables)
  8. [Searching with nested loops](#8-searching-with-nested-loops)
  9. [Modulo without `%`: repeated subtraction](#9-modulo-without--repeated-subtraction)
  10. [Prime checking](#10-prime-checking)
  11. [Perfect numbers and Mersenne primes](#11-perfect-numbers-and-mersenne-primes)
  12. [Bit shifting and `long long`](#12-bit-shifting-and-long-long)
  13. [Making nested loops faster](#13-making-nested-loops-faster)
  14. [Common mistakes](#14-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | File | Concepts |
|---|---|---|
| A: First n Perfect Numbers | [A-nthPerfect.c](A-nthPerfect.c) | Nested prime checks, `<<`, `long long`, Mersenne primes |
| B: Primality Check without Using Modulo | [B-primalityCheck.c](B-primalityCheck.c) | Modulo by repeated subtraction, counting iterations |

All problems print **exact output messages, including case**.

### Problem A: First n Perfect Numbers · `A-nthPerfect.c`

> Ask the user to enter a positive number, say n. Compute and display the first n perfect numbers in one line separated by a space. Sample: n = 3, then display the first 3 perfect numbers, which are: `6 28 496`
>
> If and when the input is invalid, print `INVALID INPUT`.
>
> **Note:** Read about `long long` and the operator `<<` (shifts bits to the left, effectively performing exponentiation, sort of).
>
> **Caveat:** strictly no implementing of functions.

| Input | Output |
|---|---|
| `1` | `6` |
| `3` | `6 28 496` |
| `5` | `6 28 496 8128 33550336` |
| `8` | `6 28 496 8128 33550336 8589869056 137438691328 2305843008139952128` |
| `0` | `INVALID INPUT` |
| `abc` | `INVALID INPUT` |

**Approach:** checking every number for being perfect is far too slow (the 5th perfect number is over 33 million). Instead, the solution uses the fact that every even perfect number has the form

$$2^{p-1} \times (2^p - 1)$$

where both `p` and `2^p − 1` are prime ([section 11](#11-perfect-numbers-and-mersenne-primes)). So the program:

1. Loops over candidate values of `p` (2, 3, 4, ...).
2. **Inner loop 1:** checks whether `p` is prime.
3. If it is, computes `2^p − 1` with `(1LL << p) - 1`.
4. **Inner loop 2:** checks whether `2^p − 1` is prime.
5. If it is, prints `2^(p-1) × (2^p − 1)` and counts it.

`n` can be at most **8**. The 9th perfect number has 37 digits, more than a `long long` can hold ([section 12](#12-bit-shifting-and-long-long)).

### Problem B: Primality Check without Using Modulo · `B-primalityCheck.c`

> Ask the user to enter a positive number, say n. Check whether n is prime or not. **The use of the modulo or division operator is prohibited.** As an alternative, you may use repetitive subtraction (or addition) to achieve modulo.
>
> If and when the input is invalid, print `INVALID INPUT`. Print `YES, n is prime.` if the number is prime. Print `NO, n is not prime.` otherwise.
>
> Apart from that output, print the number of candidate factors that had to be checked to arrive at an answer. Also print the number of iterations that had to be executed for checking whether each candidate factor is indeed a factor (the alternative to modulo).

**Output format:** one line per candidate factor, showing how many subtractions it took, then the number of candidate factors checked, then the verdict.

**Sample run: prime**

```
29
Iterations inside the loop per candidate factor:
9
5
Iterations of the outer loop: 2
YES, 29 is prime.
```

Here, 3 goes into 29 nine times (remainder 2) and 5 goes into 29 five times (remainder 4). The next candidate, 7, is skipped because 7 × 7 = 49 > 29.

**Sample run: not prime**

```
91
Iterations inside the loop per candidate factor:
30
18
13
Iterations of the outer loop: 3
NO, 91 is not prime.
```

The candidates are 3 (remainder 1), 5 (remainder 1) and 7. 7 goes into 91 exactly 13 times, so 91 = 7 × 13.

| Input | Last line of output |
|---|---|
| `1` | `NO, 1 is not prime.` |
| `2` | `YES, 2 is prime.` |
| `29` | `YES, 29 is prime.` |
| `91` | `NO, 91 is not prime.` |
| `97` | `YES, 97 is prime.` |
| `0` | `INVALID INPUT` |

**Approach:**

- **Outer loop:** tries odd candidate factors 3, 5, 7, ... and stops once `candidate × candidate` passes `n`.
  - `candidate²` is built by adding `candidate` to itself `candidate` times, since `*` is still allowed but `/` and `%` are not.
- **Inner loop:** subtracts the candidate from `n` until what's left is smaller than the candidate. What's left is the remainder (`n % candidate`). The number of subtractions is the quotient (`n / candidate`).
- A remainder of `0` means the candidate divides `n`, so `n` is not prime and the outer loop `break`s.

---

## Nested Loops in C

### 1. What a nested loop is

A **nested loop** is a loop inside the body of another loop. For **each** iteration of the outer loop, the inner loop runs **all the way through**.

```c
for (int i = 1; i <= 3; i++) {          // outer loop
    for (int j = 1; j <= 2; j++) {      // inner loop
        printf("i=%d j=%d\n", i, j);
    }
}
```

```
i=1 j=1
i=1 j=2
i=2 j=1
i=2 j=2
i=3 j=1
i=3 j=2
```

Think of a clock: the minute hand (inner loop) goes all the way around for each step of the hour hand (outer loop).

Any loop type can be nested inside any other. Problem A nests `for` loops inside a `while`. Problem B nests `while` loops inside a `while (1)`.

### 2. Counting iterations

If the inner loop always runs the same number of times, the total is a product:

| Outer runs | Inner runs per outer | Inner body runs in total |
|---|---|---|
| `n` | `m` | `n × m` |
| 10 | 10 | 100 |
| 1,000 | 1,000 | 1,000,000 |

That number grows fast, which is why efficiency matters more once loops are nested ([section 13](#13-making-nested-loops-faster)).

Three levels of nesting multiply three counts: `n × m × k`.

### 3. Inner loops that depend on the outer loop

The inner loop's bounds can use the outer loop variable. This makes a **triangle** instead of a rectangle.

```c
for (int i = 1; i <= 4; i++) {
    for (int j = 1; j <= i; j++)   // inner runs i times
        printf("%d ", j);
    printf("\n");
}
```

```
1
1 2
1 2 3
1 2 3 4
```

The inner body runs 1 + 2 + 3 + ... + n = **n(n + 1) / 2** times.

Problem A works the same way: how long the inner prime check runs depends on the outer loop's current candidate.

### 4. Resetting inner variables

Variables the inner loop uses for **one outer iteration** must be reset at the start of each outer iteration. Declaring them inside the outer loop does that automatically.

```c
for (int i = 2; i <= 10; i++) {
    int sum = 0;                    // reset for each i
    for (int j = 1; j < i; j++)
        if (i % j == 0)
            sum += j;
    printf("%d: %d\n", i, sum);
}
```

If `sum` were declared once before the outer loop, it would keep growing across every `i`. Both machine problems reset their flags and counters this way (`isitPrime = 1`, `count = 0`, `remainder = n`).

### 5. `break` and `continue` in nested loops

`break` and `continue` only affect the **innermost loop** they are in.

```c
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        if (j == 2) break;          // leaves the j loop only
        printf("%d%d ", i, j);
    }
}
// 11 21 31
```

To leave **both** loops at once:

**A flag**

```c
int found = 0;
for (int i = 0; i < n && !found; i++)
    for (int j = 0; j < m && !found; j++)
        if (/* match */)
            found = 1;
```

**`return`**, when you are done with the whole function (or program, inside `main`)

```c
for (...)
    for (...)
        if (/* match */) {
            printf("Found\n");
            return 0;
        }
```

**`goto`**, which C allows and some courses discourage

```c
for (...)
    for (...)
        if (/* match */)
            goto done;
done:
    ...
```

### 6. Printing patterns

The classic nested loop exercise. The outer loop picks the **row**, the inner loop(s) print the **columns** of that row, and `printf("\n")` ends the row.

**Rectangle**

```c
for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 5; c++)
        printf("*");
    printf("\n");
}
```

```
*****
*****
*****
```

**Right triangle**

```c
for (int r = 1; r <= 4; r++) {
    for (int c = 1; c <= r; c++)
        printf("*");
    printf("\n");
}
```

```
*
**
***
****
```

**Inverted triangle**

```c
for (int r = 4; r >= 1; r--) {
    for (int c = 1; c <= r; c++)
        printf("*");
    printf("\n");
}
```

```
****
***
**
*
```

**Pyramid** (two inner loops: spaces, then stars)

```c
int h = 4;
for (int r = 1; r <= h; r++) {
    for (int s = 1; s <= h - r; s++)
        printf(" ");
    for (int c = 1; c <= 2 * r - 1; c++)
        printf("*");
    printf("\n");
}
```

```
   *
  ***
 *****
*******
```

**Hollow square**

```c
int n = 5;
for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= n; c++)
        printf(r == 1 || r == n || c == 1 || c == n ? "*" : " ");
    printf("\n");
}
```

```
*****
*   *
*   *
*   *
*****
```

**Number triangle**

```c
for (int r = 1; r <= 4; r++) {
    for (int c = 1; c <= r; c++)
        printf("%d", r);
    printf("\n");
}
```

```
1
22
333
4444
```

**How to design a pattern:** write a table with one row per output line. For each row, write how many spaces and how many symbols it has, then turn those columns into formulas of `r`.

| Row `r` | Spaces | Stars |
|---|---|---|
| 1 | 3 | 1 |
| 2 | 2 | 3 |
| 3 | 1 | 5 |
| 4 | 0 | 7 |
| formula | `h - r` | `2r - 1` |

### 7. Grids and tables

**Multiplication table**

```c
for (int r = 1; r <= 5; r++) {
    for (int c = 1; c <= 5; c++)
        printf("%4d", r * c);     // %4d keeps the columns aligned
    printf("\n");
}
```

```
   1   2   3   4   5
   2   4   6   8  10
   3   6   9  12  15
   4   8  12  16  20
   5  10  15  20  25
```

**Every pair** (e.g. all dice rolls)

```c
for (int a = 1; a <= 6; a++)
    for (int b = 1; b <= 6; b++)
        printf("(%d,%d) ", a, b);
```

**Every unique pair** (start the inner loop after `a`, so `(1,2)` and `(2,1)` aren't both listed)

```c
for (int a = 1; a <= 6; a++)
    for (int b = a + 1; b <= 6; b++)
        printf("(%d,%d) ", a, b);
```

Grids become even more useful with 2D arrays (see [05 - Arrays](../05%20-%20Arrays/)).

### 8. Searching with nested loops

A common structure: the outer loop goes through **candidates**, the inner loop **tests** each candidate.

```c
// Print all primes up to 50
for (int n = 2; n <= 50; n++) {        // candidates
    int isPrime = 1;
    for (int d = 2; d * d <= n; d++) { // test
        if (n % d == 0) {
            isPrime = 0;
            break;
        }
    }
    if (isPrime)
        printf("%d ", n);
}
```

**Find the first n that pass** (Problem A's shape): use a `while` loop with a counter, since you don't know how many candidates you'll need.

```c
int count = 0, candidate = 2;
while (count < n) {
    // inner loop: test candidate
    if (/* passes */) {
        printf("%d ", candidate);
        count++;
    }
    candidate++;
}
```

**Printing "separated by a space" without a trailing space:** print the separator only between items.

```c
printf("%lld", value);
count++;
if (count < n)
    printf(" ");
```

### 9. Modulo without `%`: repeated subtraction

Division is repeated subtraction. Subtract `d` from `n` until what's left is smaller than `d`:

```c
int remainder = n, quotient = 0;
while (remainder >= d) {
    remainder -= d;
    quotient++;
}
// quotient == n / d, remainder == n % d
```

| `n` | `d` | Subtractions | Remainder | Divides? |
|---|---|---|---|---|
| 29 | 3 | 9 | 2 | No |
| 91 | 7 | 13 | 0 | Yes |
| 10 | 4 | 2 | 2 | No |

This only works for non-negative `n` and positive `d`. It also takes `n / d` iterations, so it is much slower than `%` for large `n` and small `d`.

**Squaring without `*`**, by repeated addition:

```c
long long square = 0;
for (long long k = 0; k < cf; k++)
    square += cf;          // square == cf * cf
```

### 10. Prime checking

A **prime** is an integer greater than 1 whose only factors are 1 and itself. `1` is **not** prime. `2` is the only even prime.

**Basic version**

```c
int isPrime = (n >= 2);
for (int d = 2; d < n; d++)
    if (n % d == 0) { isPrime = 0; break; }
```

**Stop at √n.** If `n = a × b`, one of `a` and `b` is at most √n. So if nothing up to √n divides `n`, nothing does. Write the condition as `d * d <= n` to avoid floating-point `sqrt`.

**Skip even candidates.** Handle 2 separately, then only try odd numbers.

```c
int isPrime;
if (n < 2)
    isPrime = 0;
else if (n == 2)
    isPrime = 1;
else if (n % 2 == 0)
    isPrime = 0;            // all other even numbers
else {
    isPrime = 1;
    for (int d = 3; d * d <= n; d += 2)
        if (n % d == 0) { isPrime = 0; break; }
}
```

Skipping evens is only correct if even `n` is handled first. Otherwise numbers like 4, 6 and 10 have no odd factor up to √n and look prime.

| Version | Candidates checked for n = 1,000,003 |
|---|---|
| All `d` from 2 to n − 1 | about 1,000,000 |
| `d * d <= n` | about 1,000 |
| `d * d <= n`, odd only | about 500 |

### 11. Perfect numbers and Mersenne primes

A **perfect number** equals the sum of its factors other than itself.

- 6 = 1 + 2 + 3
- 28 = 1 + 2 + 4 + 7 + 14

A **Mersenne prime** is a prime of the form **2ᵖ − 1**. For it to be prime, `p` must be prime too. The converse isn't always true: 2¹¹ − 1 = 2047 = 23 × 89.

**Euclid–Euler theorem:** every even perfect number is **2ᵖ⁻¹ × (2ᵖ − 1)**, where 2ᵖ − 1 is a Mersenne prime. (No odd perfect number has ever been found.)

| `p` | 2ᵖ − 1 | Prime? | Perfect number |
|---|---|---|---|
| 2 | 3 | yes | 2 × 3 = **6** |
| 3 | 7 | yes | 4 × 7 = **28** |
| 5 | 31 | yes | 16 × 31 = **496** |
| 7 | 127 | yes | 64 × 127 = **8128** |
| 11 | 2047 | no (23 × 89) | – |
| 13 | 8191 | yes | **33550336** |
| 17 | 131071 | yes | **8589869056** |
| 19 | 524287 | yes | **137438691328** |
| 31 | 2147483647 | yes | **2305843008139952128** |
| 61 | 2305843009213693951 | yes | too big for `long long` |

So instead of testing millions of numbers for being perfect, Problem A only tests a few dozen values of `p`.

### 12. Bit shifting and `long long`

Integers are stored in binary. The **shift operators** move all the bits left or right.

| Operator | Meaning | Example |
|---|---|---|
| `x << k` | shift left by `k` bits = multiply by 2ᵏ | `3 << 2` = `12` |
| `x >> k` | shift right by `k` bits = divide by 2ᵏ (for non-negative `x`) | `20 >> 2` = `5` |

```
1 << 0  =  0001  =  1
1 << 1  =  0010  =  2
1 << 2  =  0100  =  4
1 << 3  =  1000  =  8
```

So `1 << p` is 2ᵖ, and `(1 << p) - 1` is 2ᵖ − 1, which is all ones in binary: `1 << 5` is `100000`, and minus 1 is `11111` (31).

**The type of `1` matters.** `1` is an `int` (usually 32 bits), so `1 << 31` and higher overflow. Write `1LL` to make it a `long long` (64 bits):

```c
int bad = 1 << 40;                  // undefined: int has only 32 bits
long long good = 1LL << 40;         // 1099511627776
```

Shifting by a negative amount or by the full width of the type or more is undefined behavior.

**Integer size limits** (typical):

| Type | Bits | Max value | `printf` |
|---|---|---|---|
| `int` | 32 | 2,147,483,647 (2³¹ − 1) | `%d` |
| `long long` | 64 | 9,223,372,036,854,775,807 (2⁶³ − 1) | `%lld` |
| `unsigned long long` | 64 | 18,446,744,073,709,551,615 (2⁶⁴ − 1) | `%llu` |

Suffixes on literals: `10LL` (long long), `10ULL` (unsigned long long), `10U` (unsigned int).

### 13. Making nested loops faster

Because the inner body runs (outer × inner) times, a small improvement inside it adds up.

| Technique | Example |
|---|---|
| Stop the inner loop early with `break` | Stop at the first factor found |
| Shrink the inner range | `d * d <= n` instead of `d < n` |
| Skip impossible candidates | Odd divisors only, after handling 2 |
| Use math to avoid searching | Generate perfect numbers from Mersenne primes instead of testing every number |
| Move work out of the inner loop | Compute `strlen(s)` or `h - r` once per outer iteration, not per inner iteration |

### 14. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Reusing `i` in the inner loop | The inner loop changes the outer counter: wrong output or an infinite loop | Use a different variable (`i`, `j`, `k`) |
| Not resetting inner counters/flags | Values carry over from the previous outer iteration | Declare or reset them inside the outer loop |
| Forgetting `printf("\n")` after the inner loop | All rows print on one line | Print the newline in the outer loop, after the inner loop |
| Putting `printf("\n")` inside the inner loop | Each symbol prints on its own line | Move it out one level |
| Expecting `break` to exit both loops | Only the inner loop ends | Use a flag, `return` or `goto` |
| Trailing space at the end of the line | Auto-checkers that compare exactly mark it wrong | Print the separator only between items |
| `1 << 40` with a plain `int` | Overflow | `1LL << 40` |
| Printing `long long` with `%d` | Wrong number | `%lld` |
| Skipping even candidates without handling even `n` | 4, 6, 10, ... reported as prime | Check `n == 2` and even `n` first |
| `d <= sqrt(n)` with floating point | Rounding can be off by one for large `n` | `d * d <= n` |
| Inner loop runs too long | Program times out | Shrink the range, `break` early ([section 13](#13-making-nested-loops-faster)) |

---

## Quick Reference

```c
for (int r = 0; r < rows; r++) {       // outer: rows
    for (int c = 0; c < cols; c++) {   // inner: columns
        ...
    }
    printf("\n");                      // end of row
}
```

| I want to... | Use |
|---|---|
| Rectangle of `rows × cols` | Inner bound is a constant: `c < cols` |
| Triangle | Inner bound uses the outer variable: `c <= r` |
| Pyramid | Two inner loops: `h - r` spaces, then `2r - 1` symbols |
| Exit both loops | Flag in both conditions, or `return` |
| Find the first n matches | `while (count < n)` with an inner test loop |
| Check a factor without `%` | Subtract until `remainder < d` |
| Check a prime | Try `d` from 2 while `d * d <= n` |
| Compute 2ᵏ | `1LL << k` |
| Even perfect number | `(1LL << (p - 1)) * ((1LL << p) - 1)` when `2^p − 1` is prime |
