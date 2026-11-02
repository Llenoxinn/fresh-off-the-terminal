# MP 7: How do I love thee? Let me count the Objects — My First Pseudo-Image Processing

CMSC 21 machine problem on **2D arrays and recursion**: treat a grid of `0`s and `1`s as a black-and-white image, and count its **objects** (groups of connected foreground pixels) using **recursive component labeling**.

## Contents

- [Files](#files)
- [Problem](#problem)
  - [Input](#input)
  - [Output](#output)
  - [Required functions](#required-functions)
- [Sample](#sample)
- [Connectivity: 4 vs. 8](#connectivity-4-vs-8)
- [Recursive Component Labeling](#recursive-component-labeling)
  - [Walkthrough](#walkthrough)
  - [`labeling`](#labeling)
  - [`countObjects`](#countobjects)
  - [Why the labels start at 2](#why-the-labels-start-at-2)
- [Sample 2, Labeled](#sample-2-labeled)
- [Recursion Notes](#recursion-notes)
- [Edge Cases](#edge-cases)
- [Testing Checklist](#testing-checklist)
- [About This Solution](#about-this-solution)

---

## Files

| File | Description |
|---|---|
| [arrayKoPo.c](arrayKoPo.c) | Solution: `countObjects` scans the image, `labeling` recursively labels each object using direction arrays |

```bash
gcc -Wall -o arrayKoPo arrayKoPo.c
./arrayKoPo < input.txt
```

---

## Problem

### Input

1. A positive integer `t`, the number of test cases.
2. For each test case:
   - Two positive integers: the number of **rows** and **columns** of the image.
   - The image itself: `rows` lines of `cols` values each, where **`1` is a foreground (black) pixel** and **`0` is background (white)**.

### Output

One line per test case:

```
<count> Objects found
```

An **object** is a group of foreground pixels that are **8-connected** to each other ([what that means](#connectivity-4-vs-8)).

### Required functions

```c
int countObjects(int[100][100], int, int);
//                image          rows, cols

void labeling(int[100][100], int, int, int, int, int);
//            image          rows, cols, row, col, label
//                                       └ pixel ┘ └ current label
```

- `labeling` gives **one object** its label, by labeling a pixel and then **recursively** labeling its 8 neighbors.
- `countObjects` goes through **every pixel** and calls `labeling` each time it finds an unlabeled foreground pixel. That's how it counts the objects.

> **Caveat:** be careful with **out-of-bounds indices**, and only label a pixel that **hasn't been labeled yet**.

---

## Sample

**Input**

```
2
5 5
0 0 0 0 0
0 1 1 1 0
1 1 1 0 0
0 0 0 0 1
1 1 1 1 1
8 10
0 0 0 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 1 1
0 1 1 1 0 0 1 0 1 1
0 0 0 0 0 1 0 0 1 0
0 1 0 0 1 1 1 0 0 0
0 0 1 0 0 0 0 1 1 1
0 1 1 1 0 0 1 0 1 1
1 0 0 0 0 1 1 1 1 0
```

**Output**

```
2 Objects found
4 Objects found
```

---

## Connectivity: 4 vs. 8

Which pixels count as "touching" the center pixel `P`:

```
4-connectivity        8-connectivity

 .  N  .               N  N  N
 N  P  N               N  P  N
 .  N  .               N  N  N

up, down, left,       the 4 neighbors
right only            plus the 4 diagonals
```

This MP uses **8-connectivity**, so pixels that touch **only at a corner** belong to the same object:

```
1 0
0 1      → 1 object with 8-connectivity (2 objects with 4-connectivity)
```

The 8 neighbors of pixel `(r, c)` are every `(r + dr, c + dc)` where `dr` and `dc` are each `-1`, `0` or `1`, except `(0, 0)` (the pixel itself):

| | `c − 1` | `c` | `c + 1` |
|---|---|---|---|
| **`r − 1`** | ↖ | ↑ | ↗ |
| **`r`** | ← | P | → |
| **`r + 1`** | ↙ | ↓ | ↘ |

---

## Recursive Component Labeling

### Walkthrough

Start with `label = 2`. Scan the image row by row. At the **first** foreground pixel (`1`), label it `2`, then recursively label every foreground pixel connected to it. When the recursion finishes, **one whole object** is labeled. Increase the label to `3` and keep scanning.

**Sample 1, before:**

```
0 0 0 0 0
0 1 1 1 0
1 1 1 0 0
0 0 0 0 1
1 1 1 1 1
```

**After the first object** (found at row 1, column 1):

```
0 0 0 0 0
0 2 2 2 0
2 2 2 0 0
0 0 0 0 1
1 1 1 1 1
```

The `1`s at the bottom aren't touched: no pixel of object 2 is next to them, not even diagonally. Row 3 is all `0` under the left part, and `(2,2)` and `(3,4)` are two columns apart.

**After the second object** (found at row 3, column 4):

```
0 0 0 0 0
0 2 2 2 0
2 2 2 0 0
0 0 0 0 3
3 3 3 3 3
```

No `1`s are left. Labels 2 and 3 were used, so there are **2 objects**.

### `labeling`

A **flood fill**: label this pixel, then try all 8 neighbors.

```c
void labeling(int img[100][100], int rows, int cols, int r, int c, int label) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)   // base case: outside the image
        return;
    if (img[r][c] != 1)                             // base case: background or already labeled
        return;

    img[r][c] = label;                              // label this pixel

    for (int dr = -1; dr <= 1; dr++)                // recursive case: the 8 neighbors
        for (int dc = -1; dc <= 1; dc++)
            if (dr != 0 || dc != 0)
                labeling(img, rows, cols, r + dr, c + dc, label);
}
```

The two base cases are exactly the MP's two caveats:

| Check | Prevents |
|---|---|
| `r < 0 \|\| r >= rows \|\| c < 0 \|\| c >= cols` | Reading outside the image: pixels on the edge have neighbors that don't exist |
| `img[r][c] != 1` | Labeling background (`0`), and **relabeling** a pixel that already has a label (2, 3, …) |

The second check is what makes the recursion **stop**. Without it, two neighboring pixels would keep calling each other forever.

Writing the 8 calls out one by one also works, and may read more clearly:

```c
labeling(img, rows, cols, r - 1, c - 1, label);   // ↖
labeling(img, rows, cols, r - 1, c,     label);   // ↑
labeling(img, rows, cols, r - 1, c + 1, label);   // ↗
labeling(img, rows, cols, r,     c - 1, label);   // ←
labeling(img, rows, cols, r,     c + 1, label);   // →
labeling(img, rows, cols, r + 1, c - 1, label);   // ↙
labeling(img, rows, cols, r + 1, c,     label);   // ↓
labeling(img, rows, cols, r + 1, c + 1, label);   // ↘
```

### `countObjects`

```c
int countObjects(int img[100][100], int rows, int cols) {
    int label = 2;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (img[r][c] == 1) {               // a pixel no object has claimed yet
                labeling(img, rows, cols, r, c, label);
                label++;                        // that object is done
            }
    return label - 2;                           // labels used: 2, 3, ..., label - 1
}
```

Every object is found **exactly once**. The first pixel the scan reaches starts the labeling, and by the time the scan reaches the object's other pixels they're no longer `1`.

Printing in `main`:

```c
printf("%d Objects found\n", countObjects(img, rows, cols));
```

### Why the labels start at 2

`0` already means background and `1` means "foreground, not labeled yet". Starting at **2** keeps labels from being confused with either. That's what lets `img[r][c] == 1` mean "not labeled yet".

---

## Sample 2, Labeled

After `countObjects` runs, the second sample image looks like this:

```
0 0 0 0 0 0 0 0 0 0
0 2 2 2 0 0 0 0 3 3
0 2 2 2 0 0 4 0 3 3
0 0 0 0 0 4 0 0 3 0
0 5 0 0 4 4 4 0 0 0
0 0 5 0 0 0 0 4 4 4
0 5 5 5 0 0 4 0 4 4
5 0 0 0 0 4 4 4 4 0
```

| Label | Object | Note |
|---|---|---|
| 2 | The 2 × 3 block at the top left | |
| 3 | The shape at the top right | |
| 4 | The large shape in the middle and bottom right | Held together by **diagonal** links, e.g. `(2,6)`–`(3,5)`–`(4,4)` |
| 5 | The shape at the bottom left | `(4,1)`–`(5,2)`–`(6,1)`–`(7,0)` are diagonal links only |

**4 objects.** With 4-connectivity the diagonal links would break, and the same image would count **8** objects.

Labels follow the **scan order** (row by row, left to right). That's why the top-right shape gets 3 before the middle shape gets 4: its first pixel `(1,8)` comes before `(2,6)`.

---

## Recursion Notes

- **Each call** handles one pixel and hands the rest of the work to its neighbors. The base cases cover "nothing to do here": outside the image, background, or already labeled.
- **Every foreground pixel is labeled once**, and each labeled pixel makes 8 calls, so the work is proportional to the image size: at most 100 × 100 × 9 calls.
- **Recursion depth:** in the worst case (an image of all `1`s), the chain of calls can be as deep as the number of pixels, 10,000 for a 100 × 100 image. That fits in the default stack. An all-ones 100 × 100 image was tested and works (`1 Objects found`). Much larger images would need an explicit stack or a queue instead of recursion.
- **Passing the array:** `int img[100][100]` passes the address of the image, so every recursive call works on the **same** image. Labels written deep in the recursion are visible to `countObjects`.
- **Big local arrays:** declaring `int img[100][100]` (40,000 bytes) inside `main` is fine. Declaring it inside `labeling` would take 40 KB per call and overflow the stack quickly. Only pass it, never copy it.

---

## Edge Cases

| Case | Expected |
|---|---|
| All `0`s | `0 Objects found` |
| All `1`s | `1 Objects found` |
| One object | `1 Objects found`. The statement doesn't say whether this should be "Object". Following the sample format literally gives `Objects` |
| Diagonal-only chain (`1 0 / 0 1`) | 1 object: 8-connected |
| Object on the image border | Must not read outside the array (bounds check) |
| `1 × 1` image | `1` → 1 object, `0` → 0 objects |
| Single row or column | Neighbors above/below or left/right are out of bounds; the bounds check handles it |
| Multiple test cases | Each image is read fresh, so old labels never carry over |

---

## Testing Checklist

```
6
5 5
0 0 0 0 0
0 1 1 1 0
1 1 1 0 0
0 0 0 0 1
1 1 1 1 1
2 2
1 0
0 1
3 3
0 0 0
0 0 0
0 0 0
3 3
1 0 1
0 0 0
1 0 1
1 1
1
1 5
1 0 1 0 1
```

Expected:

```
2 Objects found
1 Objects found
0 Objects found
4 Objects found
1 Objects found
3 Objects found
```

---

## About This Solution

[arrayKoPo.c](arrayKoPo.c) finds the **correct number of objects** for both samples and all six images in the [testing checklist](#testing-checklist). It also handles an all-ones 100 × 100 image without running out of stack.

| Piece | Role |
|---|---|
| `int px[100][100]` | The image, declared at the full 100 × 100 capacity in `main`. Only the top-left `rn × cn` part is used |
| `countObjects(px, rn, cn)` | Scans row by row. Each unlabeled `1` starts a new object: it calls `labeling`, then increments the label. Returns `labelpx - 2` |
| `labeling(px, rn, cn, row, column, label)` | Bounds check, then "already labeled or background" check, then labels the pixel and recurses on all 8 neighbors |
| `directionrow[]`, `directioncolumn[]` | The 8 neighbor offsets as two parallel arrays, so one loop replaces the 8 written-out calls (still in the comments) |

**Why `px[rn][cn]` didn't work** (the comment in `main`): the functions take `int[100][100]`, so inside them, row `i` starts at element `i × 100`. A variable-length `int px[rn][cn]` stores its rows `cn` elements apart instead. When the two disagree, `px[i][j]` inside the function reads the wrong memory for every row after the first. Declaring `int px[100][100]` makes both sides agree. (The other option is changing the parameters to `int px[rn][cn]` with `rn` and `cn` first, as in [MP 6-mini](../MP%206-mini%20-%202%20Dimensions/#about-this-solution), but the MP fixes the signature at `int[100][100]`.)

**Output wording differs from the sample:**

| Count | Sample expects | `arrayKoPo.c` prints |
|---|---|---|
| 2 | `2 Objects found` | `2 objects found` |
| 1 | `1 Objects found` (by the sample's format) | `1 object found` |
| 0 | `0 Objects found` | `0 object found` |

The counts are right, but the word is lowercase and changes with the count, so an exact-match checker would reject every line. Two details:

- **Capital O:** the sample uses `Objects`.
- **Singular vs. plural:** `objects > 1 ? ... : ...` treats 0 as singular. In English, 0 takes the plural ("0 objects"). If you do want proper grammar, the condition should be `objects == 1`.

To match the sample exactly:

```c
printf("%i Objects found\n", objects);
```
