# 02 - Recursion

CMSC 21 machine problems on **recursion**, followed by a reference covering everything you need to know about recursive functions in C.

## Contents

- [Machine Problems](#machine-problems)
- [Recursion in C](#recursion-in-c)
  1. [What recursion is](#1-what-recursion-is)
  2. [Base case and recursive case](#2-base-case-and-recursive-case)
  3. [The call stack](#3-the-call-stack)
  4. [Tracing a recursive function](#4-tracing-a-recursive-function)
  5. [Recursion on numbers](#5-recursion-on-numbers)
  6. [Recursion on arrays](#6-recursion-on-arrays)
  7. [Recursion on strings](#7-recursion-on-strings)
  8. [Divide and conquer: halving the problem](#8-divide-and-conquer-halving-the-problem)
  9. [Recursion on grids (flood fill)](#9-recursion-on-grids-flood-fill)
  10. [Recursion vs. iteration](#10-recursion-vs-iteration)
  11. [Tail recursion](#11-tail-recursion)
  12. [Common mistakes](#12-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 4: Recursion (*definition: see Recursion*) | [MP 4 - See Recursion](MP%204%20-%20See%20Recursion/) | Multiplication without `*` by halving, recursive palindrome check with two bounds, tracing base and recursive cases |

Recursion also drives [MP 7: Count the Objects](../04%20-%20Multidimensional%20Arrays/MP%207%20-%20Count%20the%20Objects/), which labels connected pixels with a recursive flood fill.

---

## Recursion in C

### 1. What recursion is

A **recursive function** solves a problem by calling **itself** on a **smaller version** of the same problem.

```c
int factorial(int n) {
    if (n <= 1) return 1;              // small enough to answer directly
    return n * factorial(n - 1);       // n! = n × (n−1)!
}
```

It works when a problem contains a smaller copy of itself:

| Problem | Smaller copy inside it |
|---|---|
| n! | (n − 1)! |
| Sum of an array of n items | Sum of the first n − 1 items |
| Is a string a palindrome? | Is it a palindrome without its first and last characters? |
| Count the pixels in an object | Count the pixels reachable from each neighbor |

### 2. Base case and recursive case

Every recursive function needs both:

| Part | Role | In `factorial` |
|---|---|---|
| **Base case** | Small enough to answer **without** recursing; stops the chain | `n <= 1` → `1` |
| **Recursive case** | Calls itself on a **smaller** input | `n * factorial(n - 1)` |

And every recursive call must **make progress toward the base case**. `factorial(n - 1)` gets closer to 1. `factorial(n)` would never stop.

Some functions have **more than one base case**: MP 4's palindrome check stops when the bounds meet **or** when a mismatch is found.

### 3. The call stack

Each call gets its **own copy** of its parameters and local variables, stored in a **stack frame**. Calls pile up until a base case is reached, then return in **reverse order**:

```
factorial(4)
│  waits for factorial(3)
│  │  waits for factorial(2)
│  │  │  waits for factorial(1)
│  │  │  └─ returns 1               ← base case
│  │  └─ returns 2 × 1 = 2
│  └─ returns 3 × 2 = 6
└─ returns 4 × 6 = 24
```

This is why, in MP 4, every `Recursive case!` line prints **before** `Base case!`: the prints happen on the way **down**, and the results are combined on the way **back up**.

The stack is limited, typically around 1–8 MB. Recursion that goes too deep (millions of calls, or a missing base case) **overflows** it and crashes the program.

### 4. Tracing a recursive function

Write one line per call, indenting for each level. For `sum(a, 3)` with `a = {4, 7, 2}`:

```c
int sum(int a[], int n) {
    if (n == 0) return 0;
    return sum(a, n - 1) + a[n - 1];
}
```

| Call | Waits for | Returns |
|---|---|---|
| `sum(a, 3)` | `sum(a, 2)` | 11 + 2 = **13** |
| `sum(a, 2)` | `sum(a, 1)` | 4 + 7 = 11 |
| `sum(a, 1)` | `sum(a, 0)` | 0 + 4 = 4 |
| `sum(a, 0)` | – | 0 (base case) |

Fill in the "Returns" column **from the bottom up**.

### 5. Recursion on numbers

**Power** (`x^n`):

```c
int power(int x, int n) {
    if (n == 0) return 1;
    return x * power(x, n - 1);
}
```

**Sum of digits:**

```c
int digitSum(int n) {
    if (n < 10) return n;
    return n % 10 + digitSum(n / 10);
}
```

**GCD (Euclid):** the recursive form of the loop in [MP 1-2](../01%20-%20Functions/MP%201-2%20-%20Relatively%20Prime/):

```c
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
```

**Fibonacci:**

```c
int fib(int n) {
    if (n <= 2) return 1;
    return fib(n - 1) + fib(n - 2);
}
```

This one makes **two** recursive calls, so the work roughly doubles at each level: `fib(40)` makes over 200 million calls. It's a classic example of recursion that's elegant but slow. A loop does it in 40 steps.

### 6. Recursion on arrays

Pass the array plus the **part still to process**, either a length or a pair of bounds:

```c
// largest element among a[0..n-1]
int maxOf(int a[], int n) {
    if (n == 1) return a[0];
    int restMax = maxOf(a, n - 1);
    return a[n - 1] > restMax ? a[n - 1] : restMax;
}

// palindrome: compare the ends, recurse on the middle (MP 4)
int isPalindrome(int a[], int lo, int hi) {
    if (lo >= hi) return 1;
    if (a[lo] != a[hi]) return 0;
    return isPalindrome(a, lo + 1, hi - 1);
}
```

The array itself is never copied. Every call shares the same array, because arrays are passed by address.

### 7. Recursion on strings

Strings end with `'\0'`, which makes a natural base case:

```c
int length(const char *s) {
    if (*s == '\0') return 0;
    return 1 + length(s + 1);          // s + 1 is the rest of the string
}

void printReverse(const char *s) {
    if (*s == '\0') return;
    printReverse(s + 1);               // print the rest first...
    putchar(*s);                       // ...then this character
}
```

Moving the `putchar` **before** the recursive call prints the string forwards instead. Whether work happens before or after the recursive call changes the order completely.

### 8. Divide and conquer: halving the problem

Shrinking the problem by **half** each call, instead of by one, makes recursion dramatically faster. MP 4's multiplication uses this:

```c
int multiply(int a, int b) {
    if (b == 1) return a;
    int half = multiply(a, b / 2);
    return (b % 2 == 0) ? half + half : half + half + a;
}
```

| Approach | Calls for `100 × 50` | Calls for `x × 1,000,000` |
|---|---|---|
| `a + multiply(a, b − 1)` | 50 | 1,000,000 (likely a stack overflow) |
| Halving `b` | 6 | about 20 |

**Binary search** follows the same pattern:

```c
int bsearch(int a[], int lo, int hi, int target) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] < target) return bsearch(a, mid + 1, hi, target);
    return bsearch(a, lo, mid - 1, target);
}
```

Store the result of a recursive call in a variable when you need it twice (`half` above). Writing `multiply(a, b/2) + multiply(a, b/2)` would double the work at every level.

### 9. Recursion on grids (flood fill)

In 2D, a cell's "smaller problems" are its **neighbors**. The flood fill from [MP 7](../04%20-%20Multidimensional%20Arrays/MP%207%20-%20Count%20the%20Objects/) labels every connected pixel:

```c
void fill(int img[100][100], int rows, int cols, int r, int c, int label) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) return;   // off the grid
    if (img[r][c] != 1) return;                             // background or done
    img[r][c] = label;                                      // mark it
    for (int dr = -1; dr <= 1; dr++)
        for (int dc = -1; dc <= 1; dc++)
            if (dr || dc)
                fill(img, rows, cols, r + dr, c + dc, label);
}
```

Here "progress toward the base case" means **every call marks one more cell**, so the number of unmarked cells always shrinks. Without the "already marked" check, two neighbors would call each other forever.

### 10. Recursion vs. iteration

Anything recursive can be written with a loop (sometimes with an explicit stack), and vice versa.

| | Recursion | Iteration |
|---|---|---|
| Reads like | The problem's definition | Step-by-step instructions |
| Memory | One stack frame **per call** | Constant |
| Risk | Stack overflow if too deep | Infinite loop |
| Best for | Problems that branch (grids, trees, divide and conquer) | Simple repetition (sums, counting) |

Factorial and array sums are clearer as loops. Flood fill and tree traversal are much clearer as recursion.

### 11. Tail recursion

A call is **tail recursive** if the recursive call is the **very last** thing the function does, with nothing left to compute afterwards:

```c
// not tail recursive: still has to multiply after the call returns
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }

// tail recursive: carries the running result in an extra parameter
int factAcc(int n, int acc) { return n <= 1 ? acc : factAcc(n - 1, n * acc); }
```

Optimizing compilers (e.g. `gcc -O2`) can turn tail recursion into a loop, removing the stack cost. MP 4's palindrome check (`return isPalindrome(a, lo + 1, hi - 1);`) is tail recursive. Its multiplication isn't, because it still adds `half + half` afterwards.

### 12. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| No base case | Infinite recursion → stack overflow | Handle the smallest input directly |
| Base case never reached | Same (e.g. `multiply(a, 0)` when the base case is `b == 1`) | Make sure every input reaches a base case |
| Recursive call doesn't shrink the input | Same | `f(n - 1)`, `f(n / 2)`, `lo + 1` |
| Forgetting `return` before the recursive call | The result is computed and thrown away | `return f(n - 1);` |
| Calling the same recursion twice | Exponential time (naive Fibonacci) | Store the result in a variable |
| Very deep recursion on big inputs | Stack overflow | Halve the problem, or use a loop |
| Printing in the wrong place | Output appears in reverse order | Print before the call for top-down order, after it for bottom-up |

---

## Quick Reference

```c
type solve(input) {
    if (/* small enough */)
        return /* direct answer */;            // base case
    /* smaller = shrink(input); */
    return /* combine */(solve(smaller));      // recursive case
}
```

| Pattern | Shrinks by | Example |
|---|---|---|
| Count down | 1 | factorial, sum of array |
| Two ends inward | 2 (one from each end) | palindrome |
| Halving | ½ | fast multiplication, binary search |
| Neighbors | marks one cell per call | flood fill |
