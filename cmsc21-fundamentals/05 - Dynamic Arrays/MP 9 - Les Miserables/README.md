# MP 9: Les Miserables (Vector MP, not a Hugo)

CMSC 21 machine problem on **dynamic memory**: implement a **vector**, an array that grows as items are added, using `malloc` and `realloc`, along with insert, remove, access, sortedness and duplicate-removal operations.

## Contents

- [Problem](#problem)
  - [The vector](#the-vector)
  - [Required operations](#required-operations)
  - [Input](#input)
  - [Output](#output)
- [Sample](#sample)
- [Sample Walkthrough](#sample-walkthrough)
- [Two Problems with the Statement](#two-problems-with-the-statement)
  - [Test case 6 contradicts the rules](#test-case-6-contradicts-the-rules)
  - [`remove` clashes with `<stdio.h>`](#remove-clashes-with-stdioh)
- [Approach](#approach)
  - [The structure](#the-structure)
  - [`init` and growing](#init-and-growing)
  - [Positions: what's valid](#positions-whats-valid)
  - [Each operation](#each-operation)
  - [Reporting failure without printing](#reporting-failure-without-printing)
  - [`isSorted` and `deleteDuplicates`](#issorted-and-deleteduplicates)
  - [`main`](#main)
- [Dynamic Memory in C](#dynamic-memory-in-c)
- [Edge Cases](#edge-cases)

---

## Problem

### The vector

A **vector** holds items like a C array `A[n]`, but its memory is **allocated dynamically**, so it can **grow** (and shrink) while the program runs.

- **Initial capacity: 5.**
- **Whenever it's full, increase the capacity by 5.**
- An `init` function sets up an empty vector.

### Required operations

| Function | Does | Returns |
|---|---|---|
| `int at(vector *v, int p)` | Gets the item at position `p` | The item |
| `int set(vector *v, int x, int p)` | Replaces the item at `p` with `x` | The **replaced** item |
| `int insert(vector *v, int x, int p)` | Inserts `x` at position `p` (first position is 0) | Success or failure (boolean) |
| `void push_back(vector *v, int x)` | Appends `x` at the end | – |
| `void push_front(vector *v, int x)` | Inserts `x` at the front | – |
| `void display(vector)` | Prints all items on one line, separated by spaces | – |
| `int remove(vector *v, int p)` | Removes the item at `p` | The **removed** item |
| `isSorted` | Is the vector in increasing order? | boolean |
| `deleteDuplicates` | Removes duplicate items | – |

> **No printing inside any function except `display`.** All other output happens in `main`.

### Input

```
t                       number of test cases
── each test case ──
n                       how many integers follow
a1 a2 ... an            pushed into the vector in order
c [args]                one operation (see below)
```

| `c` | Arguments | Operation | Printed on success |
|---|---|---|---|
| 1 | `x` | `push_back(x)` | the vector |
| 2 | `x` | `push_front(x)` | the vector |
| 3 | `x p` | `insert(x, p)` | the vector |
| 4 | `p` | `remove(p)` | the **removed item**, then the vector |
| 5 | `p` | `at(p)` | the **item** (see [note](#sample-walkthrough)) |
| 6 | `x p` | `set(x, p)` | the **replaced item**, then the vector |
| 7 | – | `isSorted` | `SORTED` or `NOT SORTED` |
| 8 | – | `deleteDuplicates` | the vector |

### Output

- After each operation, print the vector on one line, plus the extra lines listed above.
- If the operation **fails** (e.g. an invalid position), print `OPERATION FAILED` **instead of** the vector.

---

## Sample

**Input**

```
13
10
1 2 3 4 5 6 7 8 9 10
1 -10
20
5 5 5 5 5 5 5 5 5 7 5 5 5 5 5 5 5 5 5 7
2 -7
10
49 49 49 49 49 49 49 49 49 49
3 2 7
10
49 49 49 49 49 49 49 49 49 49
3 2 17
10
10 15 20 25 26 26 45 20 21 10
1 1004
20
1 7 3 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8 1
3 12345 10
20
1 7 3 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8 1
4 19
20
1 7 3 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8 1
4 2
10
1 7 3 8 7 3 5 6 8 1
4 11
10
1 7 3 8 7 3 5 6 8 1
5 12
10
1 7 3 8 7 3 5 6 8 1
6 -2 5
10
1 7 3 8 7 3 5 6 8 1
7
10
1 7 3 8 7 3 5 6 8 1
8
```

**Output**

```
1 2 3 4 5 6 7 8 9 10 -10
-7 5 5 5 5 5 5 5 5 5 7 5 5 5 5 5 5 5 5 5 7
49 49 49 49 49 49 49 2 49 49 49
OPERATION FAILED
10 15 20 25 26 26 45 20 21 10 1004
OPERATION FAILED
1
1 7 3 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8
3
1 7 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8 1
OPERATION FAILED
OPERATION FAILED
3
1 7 3 8 7 -2 5 6 8 1
NOT SORTED
1 7 3 8 5 6
```

---

## Sample Walkthrough

| # | Size | Operation | Result |
|---|---|---|---|
| 1 | 10 | `push_back(-10)` | `-10` added at the end |
| 2 | 20 | `push_front(-7)` | `-7` added at the front (21 items) |
| 3 | 10 | `insert(2, 7)` | `2` now at index 7, the rest shift right |
| 4 | 10 | `insert(2, 17)` | 17 > size 10: **fails** |
| 5 | 10 | `push_back(1004)` | Appended |
| 6 | 20 | `insert(12345, 10)` | Sample says **fails**, though position 10 is valid ([see below](#test-case-6-contradicts-the-rules)) |
| 7 | 20 | `remove(19)` | Prints `1` (the last item), then the 19 left |
| 8 | 20 | `remove(2)` | Prints `3`, then the vector without it |
| 9 | 10 | `remove(11)` | 11 ≥ size 10: **fails** |
| 10 | 10 | `at(12)` | 12 ≥ size 10: **fails** |
| 11 | 10 | `set(-2, 5)` | Prints `3` (the old item at index 5), then the vector with `-2` there |
| 12 | 10 | `isSorted` | `NOT SORTED`. The vector itself is **not** printed |
| 13 | 10 | `deleteDuplicates` | `1 7 3 8 5 6`: the first occurrence of each value stays, in its original order |

What the sample shows about the output format:

- **Operations 4 and 6** print **two lines**: the item, then the vector.
- **Operation 7** prints **only** `SORTED` / `NOT SORTED`, without the vector. The statement writes `"NOT SORTED."` with a period, but the sample has none.
- **Operation 5** only appears as a failure in the sample. By analogy with 4 and 6, a successful `at` most likely prints the item and then the vector.
- `OPERATION FAILED` has no period.

---

## Two Problems with the Statement

### Test case 6 contradicts the rules

```
20
1 7 3 8 7 3 5 6 8 1 1 7 3 8 7 3 5 6 8 1
3 12345 10
```

The vector has 20 items, so valid insert positions are 0–20. Position **10** is valid, and test case 3 shows insert works on a full vector (10 items, capacity 10). By the rules, the result should be:

```
1 7 3 8 7 3 5 6 8 1 12345 1 7 3 8 7 3 5 6 8 1
```

But the sample expects `OPERATION FAILED`. Nothing in the statement explains it:

| Possible rule | Ruled out by |
|---|---|
| Insert fails when the vector is full | Test 3 (full at 10 items, insert succeeds) |
| The vector can't exceed 20 items | Test 2 (push_front makes 21 items) |
| Item and position were swapped | Test 3 (`3 2 7` puts 2 at index 7) |

A reference implementation that follows the rules gets every other line of the sample right and differs **only** on this one. It's most likely an error in the sample. Confirm with your instructor if possible, and don't bend the insert logic to match it.

### `remove` clashes with `<stdio.h>`

`<stdio.h>` already declares a standard function `int remove(const char *filename)`, which deletes a file. Defining `int remove(vector *v, int p)` in a file that includes `<stdio.h>` fails:

```
error: conflicting types for 'remove'; have 'int(vector *, int)'
note: previous declaration of 'remove' with type 'int(const char *)'
```

C has no function overloading, so two functions can't share a name. Options:

| Option | Note |
|---|---|
| Rename it: `removeAt`, `vremove`, `erase` | Simplest. Mention the rename in a comment |
| Keep `remove` and avoid `<stdio.h>` in that file | Not practical: `display` needs `printf` |

---

## Approach

### The structure

```c
typedef struct {
    int *items;      // points to the dynamically allocated array
    int size;        // how many items are in use
    int capacity;    // how many items fit before growing
} vector;
```

```
size = 7, capacity = 10

items ──► [ 4 | 8 | 1 | 9 | 2 | 7 | 5 | ? | ? | ? ]
            0   1   2   3   4   5   6   7   8   9
                                        └ free ┘
```

### `init` and growing

```c
void init(vector *v) {
    v->size = 0;
    v->capacity = 5;
    v->items = malloc(v->capacity * sizeof(int));
}

// called before adding an item
void ensureRoom(vector *v) {
    if (v->size == v->capacity) {
        v->capacity += 5;
        v->items = realloc(v->items, v->capacity * sizeof(int));
    }
}
```

Capacity after pushing `n` items:

| Items | 1–5 | 6–10 | 11–15 | 16–20 | 21–25 |
|---|---|---|---|---|---|
| Capacity | 5 | 10 | 15 | 20 | 25 |

`realloc` returns a pointer to a block of the new size, **keeping the old contents**. It may move the block to a new address, which is why the result is assigned back to `v->items`.

**Shrinking** (the statement says the vector "can expand and shrink") isn't given a rule. A matching one would be: after a removal, if `capacity - size >= 5` and `capacity > 5`, reduce the capacity by 5 with `realloc`.

### Positions: what's valid

| Operation | Valid `p` | Why |
|---|---|---|
| `at`, `set`, `remove` | `0 ≤ p < size` | Must refer to an existing item |
| `insert` | `0 ≤ p ≤ size` | `p == size` means "insert at the end" |

### Each operation

**`insert`:** shift everything from `p` onward one slot **right**, starting from the **end** so nothing is overwritten, then place `x`.

```c
int insert(vector *v, int x, int p) {
    if (p < 0 || p > v->size) return 0;
    ensureRoom(v);
    for (int i = v->size; i > p; i--)
        v->items[i] = v->items[i - 1];
    v->items[p] = x;
    v->size++;
    return 1;
}
```

```
insert 2 at position 7 (test 3):

before  49 49 49 49 49 49 49 49 49 49
after   49 49 49 49 49 49 49  2 49 49 49
                             ▲
```

**`push_back` and `push_front`** are inserts at the two ends:

```c
void push_back(vector *v, int x)  { insert(v, x, v->size); }
void push_front(vector *v, int x) { insert(v, x, 0); }
```

**`remove`:** save the item, shift everything after `p` one slot **left**, and shrink `size`.

```c
int removeAt(vector *v, int p) {
    int removed = v->items[p];
    for (int i = p; i < v->size - 1; i++)
        v->items[i] = v->items[i + 1];
    v->size--;
    return removed;
}
```

**`at` and `set`:**

```c
int at(vector *v, int p) { return v->items[p]; }

int set(vector *v, int x, int p) {
    int old = v->items[p];
    v->items[p] = x;
    return old;
}
```

**`display`:** one line, spaces only **between** items.

```c
void display(vector v) {
    for (int i = 0; i < v.size; i++)
        printf(i == 0 ? "%d" : " %d", v.items[i]);
    printf("\n");
}
```

`display` takes the vector **by value**. That copies only the structure (a pointer and two `int`s), not the items. Both copies point to the same array.

### Reporting failure without printing

`at`, `set` and `remove` return the **item**, and any `int` can be a valid item. So there's no return value left to mean "failed". Since the functions can't print either, check the position **in `main` before calling them**:

```c
case 4:
    scanf("%d", &p);
    if (p < 0 || p >= v.size)
        printf("OPERATION FAILED\n");
    else {
        printf("%d\n", removeAt(&v, p));
        display(v);
    }
    break;
```

`insert` returns a boolean, so it can report failure itself.

### `isSorted` and `deleteDuplicates`

**`isSorted`:** sorted unless some item is smaller than the one before it. Equal neighbors are allowed (`5 5 7` counts as sorted).

```c
int isSorted(vector v) {
    for (int i = 1; i < v.size; i++)
        if (v.items[i] < v.items[i - 1])
            return 0;
    return 1;
}
```

**`deleteDuplicates`:** keep the **first** occurrence of each value, in order. Use a **write index** `w`: each item is copied forward only if it isn't already among the kept items.

```c
void deleteDuplicates(vector *v) {
    int w = 0;
    for (int r = 0; r < v->size; r++) {
        int seen = 0;
        for (int k = 0; k < w; k++)
            if (v->items[k] == v->items[r]) { seen = 1; break; }
        if (!seen)
            v->items[w++] = v->items[r];
    }
    v->size = w;
}
```

```
1 7 3 8 7 3 5 6 8 1
      keep: 1 7 3 8 · · 5 6 · ·   → 1 7 3 8 5 6
```

The statement says these two "accept a vector as argument". `deleteDuplicates` changes the vector, so it needs a **pointer** (`vector *`). Passed by value, it would shorten only its own copy of `size`.

### `main`

```c
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        vector v;
        init(&v);

        int n, x, p, c;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            push_back(&v, x);
        }

        scanf("%d", &c);
        switch (c) {
            case 1: /* push_back, display */ break;
            // ...
            case 7: printf(isSorted(v) ? "SORTED\n" : "NOT SORTED\n"); break;
            case 8: deleteDuplicates(&v); display(v); break;
        }

        free(v.items);      // every test case gets a fresh vector
    }
    return 0;
}
```

---

## Dynamic Memory in C

| Function | Header | Does |
|---|---|---|
| `malloc(bytes)` | `<stdlib.h>` | Allocates a block, **uninitialized**. Returns its address, or `NULL` on failure |
| `calloc(count, size)` | `<stdlib.h>` | Allocates `count × size` bytes, **all zero** |
| `realloc(ptr, bytes)` | `<stdlib.h>` | Resizes a block, keeping its contents. **May move it** |
| `free(ptr)` | `<stdlib.h>` | Gives the block back. Don't use `ptr` afterwards |

```c
int *a = malloc(5 * sizeof(int));     // room for 5 ints
a = realloc(a, 10 * sizeof(int));     // now room for 10; first 5 kept
free(a);
```

**Why dynamic?** A normal array's size is fixed when it's declared. With `malloc`, the size can depend on the input and can change later.

**Stack vs. heap:** local variables live on the **stack** and disappear when the function returns. `malloc` memory lives on the **heap** and stays until `free` is called. That's why a function can create a vector and the caller can keep using it.

**Safer `realloc`:** if `realloc` fails it returns `NULL`, and `v->items = realloc(...)` would lose the old block. The careful version:

```c
int *bigger = realloc(v->items, newCap * sizeof(int));
if (bigger == NULL) return 0;          // old block is still valid
v->items = bigger;
```

**Common mistakes:**

| Mistake | Result |
|---|---|
| `malloc(5)` instead of `malloc(5 * sizeof(int))` | Room for 5 **bytes**, not 5 ints |
| Forgetting to assign `realloc`'s result | The pointer may still point to the old, freed block |
| Using memory after `free` | Undefined behavior |
| Never calling `free` | A **memory leak**: harmless in a short program, a real problem in long-running ones |
| Freeing the same pointer twice | Undefined behavior, often a crash |

---

## Edge Cases

| Case | Expected |
|---|---|
| `n = 0` | Empty vector. `display` prints an empty line |
| Insert at `p == size` | Valid: same as `push_back` |
| Insert at `p == 0` | Valid: same as `push_front` |
| Negative position | `OPERATION FAILED` |
| Remove from an empty vector | Any position fails |
| Vector with all equal items | `SORTED`. `deleteDuplicates` leaves one item |
| Items pushed past a multiple of 5 | Capacity grows by 5 each time: 5 → 10 → 15 → … |
| Many test cases | Free each vector, or memory keeps growing |
