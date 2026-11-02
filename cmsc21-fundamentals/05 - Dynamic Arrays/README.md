# 05 - Dynamic Arrays

CMSC 21 machine problem on **dynamic memory allocation** and the **vector** (a resizable array), followed by a reference covering everything you need to know about `malloc`, `realloc` and `free` in C.

## Contents

- [Machine Problems](#machine-problems)
- [Dynamic Memory in C](#dynamic-memory-in-c)
  1. [Why dynamic memory](#1-why-dynamic-memory)
  2. [Stack vs. heap](#2-stack-vs-heap)
  3. [`malloc` and `calloc`](#3-malloc-and-calloc)
  4. [`realloc`](#4-realloc)
  5. [`free`](#5-free)
  6. [Pointers and dynamic arrays](#6-pointers-and-dynamic-arrays)
  7. [The vector: an array that grows](#7-the-vector-an-array-that-grows)
  8. [Growth strategies](#8-growth-strategies)
  9. [Inserting and removing](#9-inserting-and-removing)
  10. [Dynamic strings and 2D arrays](#10-dynamic-strings-and-2d-arrays)
  11. [Memory bugs](#11-memory-bugs)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 9: Les Misérables (Vector) | [MP 9 - Les Miserables](MP%209%20-%20Les%20Miserables/) | A vector with capacity 5 that grows by 5; `at`, `set`, `insert`, `push_back`, `push_front`, `remove`; `isSorted` and `deleteDuplicates` |

---

## Dynamic Memory in C

### 1. Why dynamic memory

A normal array's size is fixed when it's declared:

```c
int a[100];       // always 100, whether you need 3 or 3,000
```

**Dynamic allocation** asks for memory **while the program runs**, in exactly the amount needed, and lets you **resize** it later.

| | Fixed array | Dynamic array |
|---|---|---|
| Size decided | When the code is written | At run time |
| Can grow | No | Yes (`realloc`) |
| Freed | Automatically, when its scope ends | Manually, with `free` |
| Can outlive the function that made it | No | Yes |

### 2. Stack vs. heap

| | Stack | Heap |
|---|---|---|
| Holds | Local variables, parameters | Memory from `malloc`, `calloc`, `realloc` |
| Size | Small (around 1–8 MB) | Large (most of RAM) |
| Lifetime | Until the function returns | Until `free` is called |
| Managed by | The compiler, automatically | **You** |

This is why a function can't safely return a pointer to its own local array, but **can** return a pointer from `malloc`.

### 3. `malloc` and `calloc`

```c
#include <stdlib.h>

int *a = malloc(n * sizeof(int));        // n ints, contents are garbage
int *b = calloc(n, sizeof(int));         // n ints, all zero

if (a == NULL) {                          // allocation can fail
    printf("Out of memory\n");
    return 1;
}
```

- The argument is a size in **bytes**, so always multiply by `sizeof`.
- `malloc` returns `void *`, which converts to any pointer type automatically in C. The cast `(int *)` is optional in C, but required in C++.
- `sizeof *a` (the size of what `a` points to) is a safe alternative to `sizeof(int)`: it stays right if `a`'s type ever changes.

### 4. `realloc`

```c
a = realloc(a, newCount * sizeof(int));
```

- Resizes the block, **keeping the old contents** (up to the smaller of the two sizes).
- May **move** the block to a new address, which is why its result must be assigned back.
- On failure it returns `NULL` and leaves the old block untouched. Assigning straight back to `a` would lose it, so the careful form is:

```c
int *bigger = realloc(a, newCount * sizeof(int));
if (bigger == NULL) { /* handle failure; a is still valid */ }
else a = bigger;
```

- `realloc(NULL, size)` behaves like `malloc(size)`.

### 5. `free`

```c
free(a);
a = NULL;      // optional, but makes accidental reuse easier to catch
```

- Every `malloc`/`calloc`/`realloc` should eventually be matched by **one** `free`.
- Free only pointers that came from those functions, and only once.
- After `free`, the memory isn't yours. Don't read or write it.

### 6. Pointers and dynamic arrays

A pointer to the first element works exactly like an array name:

```c
int *a = malloc(5 * sizeof(int));
a[0] = 10;            // same as *(a + 0) = 10
a[4] = 50;            // same as *(a + 4) = 50
```

`sizeof a` gives the size of the **pointer** (4 or 8 bytes), not the block. Keep the element count in a separate variable, which is exactly why a vector stores `size` and `capacity`.

### 7. The vector: an array that grows

A **vector** wraps a dynamic array with its bookkeeping:

```c
typedef struct {
    int *items;       // the heap array
    int size;         // items in use
    int capacity;     // items that fit before growing
} vector;
```

```
size 7, capacity 10:

items ──► [ 4 | 8 | 1 | 9 | 2 | 7 | 5 | · | · | · ]
           └──────── in use ────────┘ └─ spare ─┘
```

```c
void init(vector *v) {
    v->size = 0;
    v->capacity = 5;
    v->items = malloc(v->capacity * sizeof(int));
}

void ensureRoom(vector *v) {             // call before adding
    if (v->size == v->capacity) {
        v->capacity += 5;
        v->items = realloc(v->items, v->capacity * sizeof(int));
    }
}

void destroy(vector *v) {
    free(v->items);
    v->items = NULL;
    v->size = v->capacity = 0;
}
```

The rest of the program never deals with `realloc` directly. It just calls `push_back`, `insert` and the like.

### 8. Growth strategies

| Strategy | Example | Copies to reach n items |
|---|---|---|
| **Add a constant** (MP 9: +5) | 5 → 10 → 15 → 20 | Grows like n² / 10: slow for large n |
| **Multiply** (common: ×2) | 5 → 10 → 20 → 40 | Grows like 2n: fast |

Each `realloc` may copy the whole array. Doubling means copies happen rarely, so `push_back` costs a constant amount **on average** (amortized O(1)). This is how C++'s `std::vector` and most real implementations grow. For a class-sized input, +5 is fine.

**Shrinking** works the same way in reverse. A common rule is to halve the capacity when the vector is only a quarter full, so a vector doesn't bounce between growing and shrinking.

### 9. Inserting and removing

| Operation | Shift | Cost |
|---|---|---|
| `push_back` | Nothing | O(1) (plus an occasional resize) |
| `insert` at `p` | Items `p … size−1` move **right**, from the end | O(n) |
| `push_front` | Every item moves right | O(n) |
| `remove` at `p` | Items `p+1 … size−1` move **left** | O(n) |
| `at`, `set` | Nothing | O(1) |

```c
// insert: shift right starting from the END, so nothing is overwritten
for (int i = v->size; i > p; i--)
    v->items[i] = v->items[i - 1];

// remove: shift left starting from p
for (int i = p; i < v->size - 1; i++)
    v->items[i] = v->items[i + 1];
```

**Valid positions:**

| Operation | Valid `p` |
|---|---|
| `at`, `set`, `remove` | `0 ≤ p < size` |
| `insert` | `0 ≤ p ≤ size` (`p == size` appends) |

When inserting and removing in the middle is the common case, a [linked list](../06%20-%20Linked%20Lists/) avoids the shifting.

### 10. Dynamic strings and 2D arrays

**A string of a size known at run time:**

```c
char *s = malloc(len + 1);       // +1 for '\0'
strcpy(s, source);
```

**A 2D array with run-time dimensions:** an array of row pointers, each row allocated separately.

```c
int **grid = malloc(rows * sizeof(int *));
for (int r = 0; r < rows; r++)
    grid[r] = malloc(cols * sizeof(int));

grid[2][3] = 7;                  // used like a normal 2D array

for (int r = 0; r < rows; r++)   // free the rows, then the row array
    free(grid[r]);
free(grid);
```

An `int **` like this is **not** compatible with an `int[100][100]` parameter. Its rows aren't stored contiguously.

### 11. Memory bugs

| Bug | Example | Result |
|---|---|---|
| Forgetting `sizeof` | `malloc(5)` for 5 ints | Room for 5 **bytes**: writes overflow |
| Not checking for `NULL` | Using the result of a failed `malloc` | Crash |
| **Memory leak** | Never calling `free`, or losing the only pointer | Memory use keeps growing |
| **Use after free** | Reading `a[0]` after `free(a)` | Undefined behavior: garbage or a crash |
| **Double free** | `free(a); free(a);` | Undefined behavior, often a crash |
| Ignoring `realloc`'s result | `realloc(a, n);` without assigning | `a` may point to the old, freed block |
| Out-of-bounds write | `a[size]` when `size == capacity` | Corrupts the heap; may crash much later |
| Freeing something not from `malloc` | `int x; free(&x);` | Crash |

Tools that catch these: **Valgrind** (Linux), and gcc/clang's **AddressSanitizer**:

```bash
gcc -g -fsanitize=address -o prog prog.c
```

---

## Quick Reference

```c
#include <stdlib.h>

int *a = malloc(n * sizeof *a);          // allocate n ints (garbage)
int *z = calloc(n, sizeof *z);           // allocate n ints (zeros)
int *t = realloc(a, m * sizeof *a);      // resize to m (may move)
if (t) a = t;
free(a);                                 // give it back, once
```

| I want to... | Use |
|---|---|
| An array sized from input | `malloc(n * sizeof(int))` |
| An array of zeros | `calloc(n, sizeof(int))` |
| Grow or shrink an array | `realloc`, assigning the result back |
| Keep track of the count | A structure with `size` and `capacity` |
| Avoid leaks | One `free` per allocation |
| Find memory bugs | `-fsanitize=address` or Valgrind |
