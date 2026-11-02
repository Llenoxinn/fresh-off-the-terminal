# 05 - Arrays

CMSC 11 machine problem on arrays and searching, followed by a reference covering everything you need to know about arrays in C.

## Contents

- [Machine Problem](#machine-problem)
  - [Am I i?](#am-i-i--amiic)
- [Arrays in C](#arrays-in-c)
  1. [What an array is](#1-what-an-array-is)
  2. [Declaring and initializing](#2-declaring-and-initializing)
  3. [Indexing and bounds](#3-indexing-and-bounds)
  4. [Array size and `sizeof`](#4-array-size-and-sizeof)
  5. [Reading and printing arrays](#5-reading-and-printing-arrays)
  6. [Capacity vs. size](#6-capacity-vs-size)
  7. [Basic array algorithms](#7-basic-array-algorithms)
  8. [Linear search](#8-linear-search)
  9. [Binary search](#9-binary-search)
  10. [Counting operations and Big-O](#10-counting-operations-and-big-o)
  11. [Sorting](#11-sorting)
  12. [2D arrays](#12-2d-arrays)
  13. [Arrays and functions](#13-arrays-and-functions)
  14. [Reading multiple test cases](#14-reading-multiple-test-cases)
  15. [Common mistakes](#15-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problem

| Problem | File | Concepts |
|---|---|---|
| Am I i? | [amII.c](amII.c) | Arrays, linear search, binary search, counting comparisons, multiple test cases |

### Am I i? · `amII.c`

> Given an array A with size n, determine whether there is an element `A[i]` equal to its index `i`. The elements of A are sorted in increasing order.
>
> Produce **two solutions**, one **linear** and one **sub-linear**, one after another in the same `main` function. You are not allowed to use global variables. Print the number of comparisons made (how many times `A[i] == i` was executed) and whether the answer is yes or no.

**Input**

1. A number `t`, the number of test cases.
2. For each test case:
   - A number `n`, the size of A, where **5 ≤ n ≤ 20** (declare the array with capacity 20).
   - Then `n` integers.

**Output**

Two lines per test case, so `2t` lines in total:

1. The result of the **linear** solution.
2. The result of the **sub-linear** solution.

Each line is `YES` or `NO`, followed by the number of comparisons made.

**Sample**

| Input | Output |
|---|---|
| <pre>2<br>5<br>0 1 2 3 4<br>5<br>1 2 3 4 5</pre> | <pre>YES 1<br>YES 1<br>NO 1<br>NO 2</pre> |

**More test cases**

| Array | Match | Linear | Binary |
|---|---|---|---|
| `0 1 2 3 4` | `A[0..4]` | `YES 1` | `YES 1` |
| `1 2 3 4 5` | none | `NO 1` | `NO 2` |
| `-5 -3 -1 1 4 8 10` | `A[4] = 4` | `YES 5` | `YES 3` |
| `-9 -7 -5 -3 -1 1 3 5 7 9` | `A[9] = 9` | `YES 10` | `YES 4` |

**Approach**

The key idea: if the elements are **distinct integers** in increasing order, then `A[i] - i` never decreases as `i` grows. Each step `i` increases by exactly 1, while `A[i]` increases by at least 1. So:

- If `A[i] < i`, then every element to the **left** also has `A[j] < j`. A match can only be to the **right**.
- If `A[i] > i`, then every element to the **right** also has `A[j] > j`. A match can only be to the **left**.

| Solution | How it works | Comparisons (worst case) |
|---|---|---|
| **Linear** | Check `A[0]`, `A[1]`, ... in order. Stop on a match, or as soon as `A[i] > i` (no match is possible after that) | up to `n` |
| **Sub-linear** (binary search) | Check the middle. On `A[mid] < mid`, search the right half; on `A[mid] > mid`, search the left half | about log₂ n + 1 (5 for n = 20) |

Walking through the binary search for `-5 -3 -1 1 4 8 10`:

| Step | `left` | `right` | `mid` | `A[mid]` | Result |
|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | 1 | 1 < 3, go right |
| 2 | 4 | 6 | 5 | 8 | 8 > 5, go left |
| 3 | 4 | 4 | 4 | 4 | match: `YES 3` |

> **Honor code:** every submission starts with the honor code declaration as a comment, citing any online sources used.

---

## Arrays in C

### 1. What an array is

An **array** is a fixed-size collection of values of the **same type**, stored **next to each other** in memory. Each value is an **element**, and you reach it by its **index**.

```c
int scores[5] = {90, 85, 77, 92, 68};
```

| Index | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| `scores[i]` | 90 | 85 | 77 | 92 | 68 |

Instead of five separate variables (`s1`, `s2`, ...), one array plus a loop handles any number of values.

### 2. Declaring and initializing

```c
int a[5];                       // 5 ints, uninitialized: garbage values
int b[5] = {1, 2, 3, 4, 5};     // all elements given
int c[5] = {1, 2};              // {1, 2, 0, 0, 0}: the rest become 0
int d[5] = {0};                 // all zeros
int e[]  = {4, 8, 15, 16};      // size counted for you: 4
int f[5] = {[2] = 9, [4] = 7};  // {0, 0, 9, 0, 7} (C99 designated initializers)
```

- The size must be a **positive integer**. Use a constant for it so you only change it in one place:

  ```c
  #define MAX 20
  int naur[MAX];
  ```

- **Arrays cannot be assigned** as a whole. `a = b;` is a compile error. Copy element by element (or with `memcpy`).
- Arrays cannot be compared with `==` either. That compares addresses, not contents.

### 3. Indexing and bounds

- The first index is **0**. The last index is **size − 1**.
- `a[i]` works with any integer expression: `a[i + 1]`, `a[n - 1]`, `a[mid]`.
- **C does not check bounds.** `a[5]` on a 5-element array compiles and runs, but it reads or writes memory that isn't yours. This is **undefined behavior**: it can return garbage, silently overwrite other variables, or crash.

```c
int a[5];
for (int i = 0; i <= 5; i++)   // bug: i == 5 is out of bounds
    a[i] = 0;
```

The safe loop shape is `for (i = 0; i < size; i++)`.

### 4. Array size and `sizeof`

`sizeof` gives the size in **bytes**. Divide by the size of one element to get the number of elements:

```c
int a[10];
sizeof a;                      // 40 (if int is 4 bytes)
sizeof a / sizeof a[0];        // 10 elements
```

This works only where the array was declared. Inside a function that receives the array as a parameter, `sizeof` gives the size of a **pointer** ([section 13](#13-arrays-and-functions)).

### 5. Reading and printing arrays

```c
int n, a[20];
scanf("%d", &n);
for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);           // & is needed for each element

for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
printf("\n");
```

`scanf` skips whitespace between numbers, so the input can be on one line (`0 1 2 3 4`) or one per line.

### 6. Capacity vs. size

The **capacity** is how many elements the array can hold (`20` in the machine problem). The **size** is how many you are actually using (`n`). Declare the capacity for the largest allowed input and keep `n` in a separate variable.

```c
#define CAPACITY 20
int a[CAPACITY];
int n;                      // 5 <= n <= 20
scanf("%d", &n);
```

Always loop to `n`, not to `CAPACITY`. Elements past `n` hold leftovers or garbage.

C99 also allows **variable-length arrays** (`int a[n];` after reading `n`). Many courses avoid them, and they can't be initialized with `= {...}`. When the problem gives a maximum, use a fixed capacity.

### 7. Basic array algorithms

**Sum and average**

```c
int sum = 0;
for (int i = 0; i < n; i++)
    sum += a[i];
double avg = (double) sum / n;    // cast, or integer division drops the decimals
```

**Minimum and maximum (with position)**

```c
int maxIdx = 0;
for (int i = 1; i < n; i++)
    if (a[i] > a[maxIdx])
        maxIdx = i;
// a[maxIdx] is the largest value
```

**Count matches**

```c
int evens = 0;
for (int i = 0; i < n; i++)
    if (a[i] % 2 == 0)
        evens++;
```

**Copy**

```c
for (int i = 0; i < n; i++)
    b[i] = a[i];
```

**Reverse in place**

```c
for (int i = 0, j = n - 1; i < j; i++, j--) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
```

**Insert at position `pos`** (shift right, starting from the end)

```c
for (int i = n; i > pos; i--)
    a[i] = a[i - 1];
a[pos] = value;
n++;                               // make sure n < capacity first
```

**Delete at position `pos`** (shift left)

```c
for (int i = pos; i < n - 1; i++)
    a[i] = a[i + 1];
n--;
```

**Frequency count** (values in a small known range, e.g. 0–9)

```c
int freq[10] = {0};
for (int i = 0; i < n; i++)
    freq[a[i]]++;
```

### 8. Linear search

Check every element in order until you find the target.

```c
int found = -1;
for (int i = 0; i < n; i++) {
    if (a[i] == target) {
        found = i;
        break;
    }
}
// found is the index, or -1 if the target isn't there
```

- Works on **any** array, sorted or not.
- Worst case: `n` comparisons (the target is last or missing).
- On a **sorted** array you can stop early once you pass where the target would be:

  ```c
  if (a[i] > target) break;
  ```

  The machine problem's linear solution uses the same idea with `A[i] > i`.

### 9. Binary search

On a **sorted** array, check the middle element and throw away the half that can't contain the target. Repeat on the remaining half.

```c
int left = 0, right = n - 1, found = -1;
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (a[mid] == target) {
        found = mid;
        break;
    } else if (a[mid] < target) {
        left = mid + 1;            // target is in the right half
    } else {
        right = mid - 1;           // target is in the left half
    }
}
```

Searching for `23` in `2 5 8 12 16 23 38 56 72 91`:

| Step | `left` | `right` | `mid` | `a[mid]` | Action |
|---|---|---|---|---|---|
| 1 | 0 | 9 | 4 | 16 | 16 < 23, go right |
| 2 | 5 | 9 | 7 | 56 | 56 > 23, go left |
| 3 | 5 | 6 | 5 | 23 | found at index 5 |

Details that matter:

- The array **must be sorted**. On unsorted data, binary search gives wrong answers.
- The condition is `left <= right`. With `<`, a one-element range is never checked.
- Use `mid + 1` and `mid - 1`. Using `mid` can loop forever.
- `left + (right - left) / 2` is the same as `(left + right) / 2`, but it can't overflow when `left` and `right` are huge.

Binary search works for any question where the answer **changes only once** as you move along the array. "Is `A[i]` less than `i`?" goes from yes to no, which is why it solves the machine problem.

### 10. Counting operations and Big-O

To compare algorithms, count the **key operation** (here, comparisons) as the input size `n` grows.

| n | Linear search (worst) | Binary search (worst) |
|---|---|---|
| 20 | 20 | 5 |
| 1,000 | 1,000 | 10 |
| 1,000,000 | 1,000,000 | 20 |
| 1,000,000,000 | 1,000,000,000 | 30 |

**Big-O** describes how the count grows, ignoring constants:

| Big-O | Name | Example |
|---|---|---|
| O(1) | constant | `a[i]`, accessing one element |
| O(log n) | logarithmic | binary search |
| O(n) | linear | linear search, sum, min/max |
| O(n log n) | linearithmic | good sorting algorithms (merge sort, quicksort) |
| O(n²) | quadratic | nested loops over the array: bubble, selection, insertion sort |

"Sub-linear" means growing slower than O(n), like O(log n). Every element doesn't need to be looked at.

To count comparisons, increment a counter **right before** each comparison you're measuring, as the machine problem does with `count++` and `countered++`.

### 11. Sorting

Binary search needs sorted data. These three simple sorts are all O(n²).

**Bubble sort:** repeatedly swap neighbors that are out of order. After each pass, the largest remaining element "bubbles" to the end.

```c
for (int pass = 0; pass < n - 1; pass++) {
    int swapped = 0;
    for (int i = 0; i < n - 1 - pass; i++) {
        if (a[i] > a[i + 1]) {
            int tmp = a[i]; a[i] = a[i + 1]; a[i + 1] = tmp;
            swapped = 1;
        }
    }
    if (!swapped) break;           // already sorted
}
```

**Selection sort:** find the smallest remaining element and swap it into place.

```c
for (int i = 0; i < n - 1; i++) {
    int minIdx = i;
    for (int j = i + 1; j < n; j++)
        if (a[j] < a[minIdx])
            minIdx = j;
    int tmp = a[i]; a[i] = a[minIdx]; a[minIdx] = tmp;
}
```

**Insertion sort:** take each element and slide it left into its place among the already-sorted ones.

```c
for (int i = 1; i < n; i++) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = key;
}
```

For descending order, flip the comparison (`>` to `<`). The standard library also has `qsort` in `<stdlib.h>`, which needs a comparison function.

### 12. 2D arrays

An array of arrays: a grid of **rows × columns**.

```c
int m[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

m[1][2];   // row 1, column 2: 7
```

Nested loops go through every cell (see [04 - Nested Loops](../04%20-%20Nested%20Loops/)):

```c
for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++)
        printf("%4d", m[r][c]);
    printf("\n");
}
```

**Row and column sums**

```c
for (int r = 0; r < rows; r++) {
    int sum = 0;
    for (int c = 0; c < cols; c++)
        sum += m[r][c];
    printf("Row %d: %d\n", r, sum);
}
```

**Transpose** (rows become columns)

```c
for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
        t[c][r] = m[r][c];
```

**Diagonal of a square matrix:** `m[i][i]`. **Anti-diagonal:** `m[i][n - 1 - i]`.

In memory, a 2D array is stored **row by row** in one block. `m[r][c]` is element number `r * cols + c`.

A string is a `char` array, and an array of strings is a 2D `char` array (see [03 - Strings](../03%20-%20Strings/)).

### 13. Arrays and functions

When you pass an array to a function, C passes the **address of its first element**, not a copy.

```c
int sum(const int a[], int n) {     // n must be passed separately
    int total = 0;
    for (int i = 0; i < n; i++)
        total += a[i];
    return total;
}

void fill(int a[], int n, int value) {
    for (int i = 0; i < n; i++)
        a[i] = value;               // changes the caller's array
}
```

- The function **can modify** the caller's array. Use `const` when it shouldn't.
- The function **doesn't know the size**. `sizeof a` inside gives the pointer size, so pass `n`.
- `int a[]` and `int *a` mean the same thing as parameters.
- A function **can't return** an array. Fill one the caller passed in instead.
- For 2D arrays, every dimension except the first must be given: `void print(int m[][4], int rows)`.

### 14. Reading multiple test cases

Many machine problems read `t` first, then solve `t` independent cases. Declare and reset everything **inside** the test-case loop so nothing leaks from one case to the next.

```c
int t;
scanf("%d", &t);
while (t--) {                      // runs t times
    int n, a[20];
    int count = 0, found = 0;      // fresh for every case
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    // solve and print this case
}
```

`while (t--)` checks `t`, then decreases it, so it runs exactly `t` times.

### 15. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| `for (i = 0; i <= n; i++)` | Reads or writes one past the end | `i < n` |
| Starting at index 1 | Skips `a[0]`, and the last access is out of bounds | Indexes go 0 to n − 1 |
| Using an uninitialized array | Garbage values in sums and comparisons | Initialize (`= {0}`) or fill it first |
| `scanf("%d", a[i])` | Passes a value instead of an address: crash | `scanf("%d", &a[i])` |
| `a = b;` | Compile error | Copy in a loop |
| `if (a == b)` for arrays | Compares addresses | Compare element by element |
| Binary search on unsorted data | Wrong answers | Sort first, or use linear search |
| `while (left < right)` in binary search | Misses the last remaining element | `left <= right` |
| `left = mid` / `right = mid` | Infinite loop | `mid + 1` / `mid - 1` |
| `sizeof a` inside a function | Pointer size, not the element count | Pass `n` as a parameter |
| Counters not reset between test cases | Counts carry over | Declare or reset them inside the test-case loop |
| `n` larger than the capacity | Writes past the end of the array | Check the allowed range, size the array for the maximum |
| Integer division in an average | `7 / 2` is `3` | `(double) sum / n` |

---

## Quick Reference

```c
#define MAX 20
int a[MAX] = {0};           // declare with capacity, all zeros
int n;                      // actual size in use

for (int i = 0; i < n; i++) scanf("%d", &a[i]);     // read
for (int i = 0; i < n; i++) printf("%d ", a[i]);    // print
```

| I want to... | Use |
|---|---|
| First element | `a[0]` |
| Last element | `a[n - 1]` |
| Number of elements (where declared) | `sizeof a / sizeof a[0]` |
| Find a value in any array | Linear search, O(n) |
| Find a value in a sorted array | Binary search, O(log n) |
| Middle index | `left + (right - left) / 2` |
| Swap two elements | `tmp = a[i]; a[i] = a[j]; a[j] = tmp;` |
| Sort a small array | Bubble, selection or insertion sort |
| Grid of values | `int m[ROWS][COLS];` |
| Pass to a function | `f(a, n)` with parameter `int a[], int n` |
| Run t test cases | `while (t--) { ... }` |
