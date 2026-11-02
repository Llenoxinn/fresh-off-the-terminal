# Mastery

CMSC 11 mastery problem on **working with the digits of a number**: rotating a number to the right, and checking whether every pair of consecutive digits differs by exactly 1.

## Contents

- [Problem](#problem)
  - [Rotating a number to the right](#rotating-a-number-to-the-right)
  - [Consecutive digits that differ by 1](#consecutive-digits-that-differ-by-1)
  - [Worked examples](#worked-examples)
- [Approach](#approach)
- [Digit Manipulation in C](#digit-manipulation-in-c)
  1. [Getting and removing digits](#1-getting-and-removing-digits)
  2. [Counting digits](#2-counting-digits)
  3. [Powers of 10 without `pow`](#3-powers-of-10-without-pow)
  4. [Rotating right](#4-rotating-right)
  5. [Rotating left](#5-rotating-left)
  6. [Comparing neighboring digits](#6-comparing-neighboring-digits)
  7. [Other digit patterns](#7-other-digit-patterns)
  8. [Edge cases](#8-edge-cases)
  9. [Common mistakes](#9-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Problem

### Rotating a number to the right

Rotating a number to the right **once** moves its **last digit to the front**. Every other digit shifts one place right.

| Number | Rotated right once |
|---|---|
| `34567` | `73456` |
| `231456` | `623145` |

### Consecutive digits that differ by 1

In `34567`, every pair of consecutive digits differs by exactly **1**:

| Pair | 3, 4 | 4, 5 | 5, 6 | 6, 7 |
|---|---|---|---|---|
| Difference | 1 | 1 | 1 | 1 |

The difference can go **up or down**. In `123456543`:

| Pair | 1, 2 | 2, 3 | 3, 4 | 4, 5 | 5, 6 | 6, 5 | 5, 4 | 4, 3 |
|---|---|---|---|---|---|---|---|---|
| Difference | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

The property can be checked from either end, left to right or right to left, with the same result.

A **1-digit number has no pairs**, so this property can't be detected for it.

### Worked examples

| Number | Rotated right | Consecutive digits differ by 1? |
|---|---|---|
| `34567` | `73456` | Yes |
| `231456` | `623145` | No: 3 and 1 differ by 2 |
| `123456543` | `312345654` | Yes |
| `9876` | `6987` | Yes |
| `1210` | `0121`, i.e. `121` | Yes |
| `5` | `5` | Not applicable (1 digit) |

---

## Approach

**Rotate right:**

1. Take the last digit: `last = n % 10`.
2. Remove it: `rest = n / 10`.
3. Count the digits of `n` to find the place value of the front: `10^(digits − 1)`.
4. Put the last digit in front: `rotated = last × 10^(digits − 1) + rest`.

For `34567`: `last = 7`, `rest = 3456`, `digits = 5`, so `7 × 10000 + 3456 = 73456`.

**Check consecutive digits:**

1. Compare the last two digits: `n % 10` and `(n / 10) % 10`.
2. If their difference (ignoring sign) isn't 1, the answer is no.
3. Drop the last digit (`n /= 10`) and repeat while at least two digits remain.

---

## Digit Manipulation in C

Integers in C don't have "digits" you can index like a string. You get them with `%` and `/` by 10.

### 1. Getting and removing digits

| Expression | Gives | For `34567` |
|---|---|---|
| `n % 10` | last digit | `7` |
| `n / 10` | the number without its last digit | `3456` |
| `(n / 10) % 10` | second-to-last digit | `6` |
| `n % 100` | last two digits | `67` |
| `n / 10^k % 10` | the digit `k` places from the right | `n / 100 % 10` = `5` |

Going through all digits, right to left:

```c
while (n > 0) {
    int digit = n % 10;
    // use digit
    n /= 10;
}
```

This destroys `n`. Work on a copy if you still need the original:

```c
int temp = n;
while (temp > 0) { ... temp /= 10; }
```

### 2. Counting digits

```c
int digits = 0, temp = n;
do {
    digits++;
    temp /= 10;
} while (temp != 0);
```

A `do`-`while` makes `0` count as 1 digit. A plain `while (temp > 0)` would give 0 digits for it.

### 3. Powers of 10 without `pow`

`pow` (from `<math.h>`) works with `double`, and converting back to `int` can round down (`pow(10, 2)` might come out as `99.999...` → `99`). Build the power with integers instead:

```c
int place = 1;
for (int i = 1; i < digits; i++)
    place *= 10;               // 10^(digits - 1)
```

You can also build it while counting digits:

```c
int place = 1, temp = n;
while (temp >= 10) {
    place *= 10;
    temp /= 10;
}
// place == 10^(digits - 1), temp == first digit
```

### 4. Rotating right

```c
int last = n % 10;
int rest = n / 10;
int rotated = last * place + rest;     // place = 10^(digits - 1)
```

Rotating `k` times means repeating this `k` times. A `d`-digit number returns to itself after `d` rotations, so only `k % d` rotations actually matter. (This holds as long as no zero ends up in front; see [section 8](#8-edge-cases).)

```c
int r = n;
for (int i = 0; i < k % digits; i++)
    r = (r % 10) * place + r / 10;
```

### 5. Rotating left

The opposite: the **first digit moves to the end**.

```c
int first = n / place;                 // place = 10^(digits - 1)
int rest = n % place;
int rotatedLeft = rest * 10 + first;   // 34567 -> 45673
```

### 6. Comparing neighboring digits

```c
#include <stdlib.h>   // abs

int ok = 1, temp = n;
while (temp >= 10) {                   // at least two digits left
    int a = temp % 10;
    int b = (temp / 10) % 10;
    if (abs(a - b) != 1) {
        ok = 0;
        break;
    }
    temp /= 10;
}
```

- `temp >= 10` stops when only one digit is left, since it has no neighbor.
- `abs` makes 6 → 5 count the same as 5 → 6.
- For a 1-digit `n`, the loop never runs. Handle that case separately if the problem gives it a special output.

Other "neighbor" rules work the same way. Only the condition changes:

| Property | Condition that breaks it |
|---|---|
| Differ by exactly 1 | `abs(a - b) != 1` |
| Strictly increasing left to right | `b >= a` (`b` is the left digit) |
| All digits the same | `a != b` |
| Alternating even/odd | `a % 2 == b % 2` |

### 7. Other digit patterns

**Sum of digits**

```c
int sum = 0;
for (int t = n; t > 0; t /= 10)
    sum += t % 10;
```

**Reverse**

```c
int rev = 0;
for (int t = n; t > 0; t /= 10)
    rev = rev * 10 + t % 10;
```

**Palindrome number**: `n == reverse(n)`.

**Largest digit**

```c
int maxD = 0;
for (int t = n; t > 0; t /= 10)
    if (t % 10 > maxD) maxD = t % 10;
```

**Digits left to right**: divide by `place`, then shrink it.

```c
for (int p = place; p > 0; p /= 10)
    printf("%d ", n / p % 10);       // 34567 -> 3 4 5 6 7
```

**Reading the number as a string instead:** `scanf("%s", s)` gives you each digit as `s[i] - '0'`, already in left-to-right order, and keeps leading zeros. Rotating right is then moving the last character to the front (see [03 - Strings](../03%20-%20Strings/)).

### 8. Edge cases

| Case | Example | What happens |
|---|---|---|
| 1-digit number | `5` | Rotating gives `5`. No pairs to compare |
| Last digit is 0 | `120` → `012` | The leading zero is lost: the result is `12`, which has fewer digits. Print with `%0*d` if the zero must show |
| Zero | `0` | 1 digit. A `while (n > 0)` loop skips it entirely |
| Negative numbers | `-345` | `%` and `/` keep the sign: `-345 % 10` is `-5`. Work with `abs(n)` and put the sign back |
| Large numbers | 10-digit input | Past `int`'s limit (2,147,483,647). Use `long long` and `%lld` |
| Rotating may overflow | `1999999999` → `9199999999` | The result can be bigger than the input. Use `long long` |

### 9. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Changing `n` while you still need it | The original value is gone (often 0) | Loop on a copy |
| `pow(10, k)` stored in an `int` | Can round down to `99`, `999`, ... | Multiply by 10 in a loop |
| Off-by-one in the place value | `34567` → `703456` or `7456` | Front place is `10^(digits − 1)` |
| `while (temp > 0)` when comparing neighbors | Compares the last digit with an imaginary `0` | `while (temp >= 10)` |
| `a - b == 1` without `abs` | Descending pairs like 6, 5 fail | `abs(a - b) == 1` |
| Using `%d` for `long long` | Wrong output | `%lld` |
| Not handling 1-digit input | Says "yes" by default, or crashes on a special case | Check `n < 10` first |

---

## Quick Reference

```c
int last   = n % 10;           // last digit
int rest   = n / 10;           // drop last digit
int second = n / 10 % 10;      // second-to-last digit

// place = 10^(digits - 1)
int place = 1;
for (int t = n; t >= 10; t /= 10) place *= 10;

int rotR = (n % 10) * place + n / 10;   // 34567 -> 73456
int rotL = (n % place) * 10 + n / place; // 34567 -> 45673
```

| I want to... | Use |
|---|---|
| Get the last digit | `n % 10` |
| Remove the last digit | `n / 10` |
| Get the first digit | `n / place` |
| Count digits | `do { d++; t /= 10; } while (t);` |
| Rotate right once | `(n % 10) * place + n / 10` |
| Rotate left once | `(n % place) * 10 + n / place` |
| Check neighbors differ by 1 | `abs(t % 10 - t / 10 % 10) == 1` while `t >= 10` |
| Handle big numbers | `long long` with `%lld` |
