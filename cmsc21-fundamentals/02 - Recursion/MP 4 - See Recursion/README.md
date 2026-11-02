# MP 4: Recursion (*definition: see Recursion*)

CMSC 21 laboratory machine problem on **recursion**: two small recursive functions, one that **multiplies without `*`** and one that checks whether an array is a **palindrome**, each announcing every recursive and base case as it runs.

## Contents

- [Files](#files)
- [Problem](#problem)
  - [Rules](#rules)
  - [Task 1: Multiplication without `*`](#task-1-multiplication-without-)
  - [Task 2: Palindromic array](#task-2-palindromic-array)
  - [Input](#input)
  - [Output](#output)
- [Sample](#sample)
- [Matching the Sample's Call Count](#matching-the-samples-call-count)
- [Task 1: Recursive Multiplication](#task-1-recursive-multiplication)
- [Task 2: Recursive Palindrome Check](#task-2-recursive-palindrome-check)
- [Recursion Basics](#recursion-basics)
- [Edge Cases](#edge-cases)
- [Testing Checklist](#testing-checklist)
- [About This Solution](#about-this-solution)
- [Honor Code](#honor-code)

---

## Files

| File | Description |
|---|---|
| [recursion.c](recursion.c) | Full solution: `recursedMultiplication` (halving) and `palindromicArray` (two bounds moving inward) |

```bash
gcc -Wall -o recursion recursion.c
./recursion < input.txt
```

---

## Problem

### Rules

- **No collaboration.** This MP and the ones after it are done in the laboratory. Use the **first** honor code only.
- Both tasks must be implemented **recursively**.

### Task 1: Multiplication without `*`

Compute the product of two numbers **using recursion and without the multiplication operator**. The recursive function takes **exactly 2 arguments**.

### Task 2: Palindromic array

Given `n` single-digit positive integers in an array, determine **recursively** whether they form a **palindrome**, meaning they read the same forwards and backwards. The recursive function may take **3 arguments**: the array, a lower bound and an upper bound.

### Input

```
a b             two positive integers to multiply
n               number of array elements
d1 d2 ... dn    n single-digit positive integers
```

### Output

1. For **each recursive call** of the multiplication function, print `Recursive case!`. When it reaches the base case, print `Base case!`.
2. The product on its own line.
3. The same tracing for the palindrome function: `Recursive Case!` for each recursive call, then `Base case!`.
4. `The array is palindromic!` or `The array is not palindromic!`

> **Watch the capitalization.** The statement says `Recursive Case!` and `Base Case!`, but the sample prints:
>
> | Function | Recursive | Base |
> |---|---|---|
> | Multiplication | `Recursive case!` (lowercase c) | `Base case!` |
> | Palindrome | `Recursive Case!` (uppercase C) | `Base case!` |
>
> If output is checked character by character, match the **sample**.

---

## Sample

**Input**

```
100 50
5
1 1 2 1 1
```

**Output**

```
Recursive case!
Recursive case!
Recursive case!
Recursive case!
Recursive case!
Base case!
5000
Recursive Case!
Recursive Case!
Base case!
The array is palindromic!
```

---

## Matching the Sample's Call Count

The obvious recursion, `a × b = a + a × (b − 1)`, makes **50** recursive calls for `100 × 50`, but the sample shows **5**. The count that matches is **halving `b`** each call, until `b` is 1:

| Call | `b` | Case |
|---|---|---|
| 1 | 50 | Recursive |
| 2 | 25 | Recursive |
| 3 | 12 | Recursive |
| 4 | 6 | Recursive |
| 5 | 3 | Recursive |
| 6 | 1 | **Base** |

Five recursive cases and one base case, as in the sample. This is sometimes called **Russian peasant multiplication**: doubling and halving instead of multiplying.

For the palindrome, comparing **one pair per call** from both ends inward matches its count:

| Call | `lo` | `hi` | Compare | Case |
|---|---|---|---|---|
| 1 | 0 | 4 | `1` vs `1` | Recursive |
| 2 | 1 | 3 | `1` vs `1` | Recursive |
| 3 | 2 | 2 | middle | **Base** |

---

## Task 1: Recursive Multiplication

**Idea:** `a × b` is twice `a × (b / 2)`, plus one more `a` when `b` is odd.

| `b` | `a × b` equals |
|---|---|
| even | `a × (b/2) + a × (b/2)` |
| odd | `a × (b/2) + a × (b/2) + a` (since `b/2` rounds down) |
| 1 | `a` (base case) |

```c
int multiply(int a, int b) {
    if (b == 1) {
        printf("Base case!\n");
        return a;
    }
    printf("Recursive case!\n");
    int half = multiply(a, b / 2);              // a × ⌊b/2⌋
    return (b % 2 == 0) ? half + half           // even
                        : half + half + a;      // odd: one more a
}
```

- `half + half` replaces `half * 2`, since `*` isn't allowed. `b / 2` and `b % 2` are division and modulo, not multiplication.
- The recursive call is made **once** and stored in `half`. Writing `multiply(a, b/2) + multiply(a, b/2)` would double the number of calls at every level.

**Tracing `100 × 50` back up the stack:**

```
multiply(100, 1)  = 100                          base
multiply(100, 3)  = 100 + 100 + 100   = 300      odd
multiply(100, 6)  = 300 + 300         = 600
multiply(100, 12) = 600 + 600         = 1200
multiply(100, 25) = 1200 + 1200 + 100 = 2500     odd
multiply(100, 50) = 2500 + 2500       = 5000
```

**The simpler alternative** (if your instructor's checker expects `b` recursive calls instead):

```c
int multiply(int a, int b) {
    if (b == 1) { printf("Base case!\n"); return a; }
    printf("Recursive case!\n");
    return a + multiply(a, b - 1);
}
```

This makes `b − 1` recursive calls: 49 for the sample, which doesn't match the 5 shown.

---

## Task 2: Recursive Palindrome Check

**Idea:** an array is a palindrome if its **first and last** elements match **and** everything between them is a palindrome.

```c
int isPalindrome(int arr[], int lo, int hi) {
    if (lo >= hi) {                       // 0 or 1 elements left
        printf("Base case!\n");
        return 1;
    }
    if (arr[lo] != arr[hi]) {             // mismatch: stop early
        printf("Base case!\n");
        return 0;
    }
    printf("Recursive Case!\n");
    return isPalindrome(arr, lo + 1, hi - 1);
}
```

Called from `main` as `isPalindrome(arr, 0, n - 1)`.

| Array | Calls | Result |
|---|---|---|
| `1 1 2 1 1` (odd length) | (0,4) R, (1,3) R, (2,2) **B** | palindromic |
| `1 2 2 1` (even length) | (0,3) R, (1,2) R, (2,1) **B** | palindromic |
| `1 2 3 1` | (0,3) R, (1,2) **B**: 2 ≠ 3 | not palindromic |
| `5` | (0,0) **B** | palindromic |

`lo >= hi` covers both lengths. With an odd length the bounds meet at the middle (`lo == hi`). With an even length they cross (`lo > hi`).

**Is a mismatch a base case?** It ends the recursion without another call, so in that sense it is one, and printing `Base case!` there is consistent. But the sample only shows a palindrome, so it can't confirm whether the expected output prints `Base case!` on a mismatch or skips it. [recursion.c](recursion.c) skips it ([details](#about-this-solution)).

---

## Recursion Basics

A **recursive function** calls itself on a **smaller** version of the same problem.

Every recursive function needs:

| Part | Purpose | Multiplication | Palindrome |
|---|---|---|---|
| **Base case** | Small enough to answer directly; stops the recursion | `b == 1` | `lo >= hi`, or a mismatch |
| **Recursive case** | Breaks the problem down and calls itself | `multiply(a, b/2)` | `isPalindrome(arr, lo+1, hi-1)` |
| **Progress** | Each call moves closer to the base case | `b` halves | `lo` and `hi` move inward |

Without a reachable base case, the function calls itself until the program runs out of **stack** memory and crashes (a *stack overflow*).

**The call stack:** each call gets its own copy of its parameters and local variables. Calls pile up until the base case, then return one by one in **reverse** order. That's why all the `Recursive case!` lines print first, then `Base case!`, and only then are the results combined on the way back.

```
multiply(100,50)
 └ multiply(100,25)
    └ multiply(100,12)
       └ multiply(100,6)
          └ multiply(100,3)
             └ multiply(100,1)   ← base case, returns 100
```

**Recursion vs. loops:** both tasks could be written with loops. Recursion fits when a problem naturally contains a smaller copy of itself, like "the middle of a palindrome is a palindrome". It's also why this MP's title, *definition: see Recursion*, is a joke: a definition that refers to itself, with no base case.

---

## Edge Cases

| Case | Multiplication | Palindrome |
|---|---|---|
| Multiply by 1 | `Base case!` immediately, no recursive cases | – |
| 1-element array | – | `Base case!` immediately, palindromic |
| Even-length array | – | Base case when the bounds cross (`lo > hi`) |
| Large products | `int` overflows above 2,147,483,647. Use `long long` if inputs can be large | – |
| `b` is the bigger number | Halving `b` makes about log₂ b calls either way | – |
| Multiply by 0 | Not allowed (inputs are positive). `b == 1` would never be reached, so add `if (b == 0) return 0;` if you want to be safe | – |

---

## Testing Checklist

| Input | Expected output |
|---|---|
| `100 50` / `5` / `1 1 2 1 1` | The sample: 5 × `Recursive case!`, `Base case!`, `5000`, 2 × `Recursive Case!`, `Base case!`, `The array is palindromic!` |
| `7 13` / `4` / `1 2 3 1` | 3 × `Recursive case!`, `Base case!`, `91`, 1 × `Recursive Case!`, then `Base case!` *only if a mismatch counts as a base case*, then `The array is not palindromic!` |
| `9 1` / `1` / `5` | `Base case!`, `9`, `Base case!`, `The array is palindromic!` |

For `7 × 13`: `b` goes 13 → 6 → 3 → 1, so there are 3 recursive cases.

---

## About This Solution

[recursion.c](recursion.c) reproduces the sample output exactly.

| Function | Arguments | How it works |
|---|---|---|
| `recursedMultiplication(x, y)` | 2 | Halves `y` each call and returns `halve + halve`, plus `x` when `y` is odd ([Task 1](#task-1-recursive-multiplication)) |
| `palindromicArray(pal, first, last)` | 3 | Compares `pal[first]` and `pal[last]`, then recurses on `first + 1`, `last - 1` ([Task 2](#task-2-recursive-palindrome-check)) |

**Where it goes beyond the reference version above:**

| Input | `recursion.c` | Why |
|---|---|---|
| `x` is 1 (e.g. `1 7`) | `Base case!` immediately, returns `y` | An extra base case: 1 × y = y. The halving version would make 2 recursive calls (7 → 3 → 1) |
| Array mismatch (e.g. `1 2 3 1`) | Returns 0 **without** printing `Base case!` | Only the bounds-meeting case prints `Base case!` |

Both are reasonable, since the sample covers neither. If the checker has hidden test cases, the second one decides whether a non-palindrome passes.

**Small notes:**

- `int arr[n];` is a **variable-length array** (C99). It is sized at run time from the input `n`.
- `if(scanf("%i", &n)!= 1 || n < 0);` ends with `;`, so the `if` has an empty body: the input is read, but an invalid `n` isn't handled. It's harmless for valid input.
- `int *pal` and `int pal[]` mean the same thing as parameters.

---

## Honor Code

Use **only the first** honor code (no collaboration for laboratory MPs), as a comment in the first lines of the solution:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.
