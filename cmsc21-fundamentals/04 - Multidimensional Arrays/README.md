# 04 - Multidimensional Arrays

CMSC 21 machine problems on **2D arrays** (grids, boards and images), followed by a reference covering everything you need to know about multidimensional arrays in C.

## Contents

- [Machine Problems](#machine-problems)
- [Multidimensional Arrays in C](#multidimensional-arrays-in-c)
  1. [What a 2D array is](#1-what-a-2d-array-is)
  2. [Declaring and initializing](#2-declaring-and-initializing)
  3. [Traversing](#3-traversing)
  4. [Memory layout](#4-memory-layout)
  5. [Passing 2D arrays to functions](#5-passing-2d-arrays-to-functions)
  6. [Capacity vs. size](#6-capacity-vs-size)
  7. [Rows, columns and diagonals](#7-rows-columns-and-diagonals)
  8. [Neighbors and bounds checking](#8-neighbors-and-bounds-checking)
  9. [Matrix operations](#9-matrix-operations)
  10. [Character grids and boards](#10-character-grids-and-boards)
  11. [Three or more dimensions](#11-three-or-more-dimensions)
  12. [Common mistakes](#12-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 6-mini: 2 Dimensions | [MP 6-mini - 2 Dimensions](MP%206-mini%20-%202%20Dimensions/) | Last column, last row and both diagonals of an `n × n` matrix; the lesson notes on 2D and 3D arrays |
| MP 6: Tic-Tac-Toe | [MP 6 - Tic-Tac](MP%206%20-%20Tic-Tac/) | A `char[3][3]` board, box-drawing output, checking 8 winning lines |
| MP 7: Count the Objects | [MP 7 - Count the Objects](MP%207%20-%20Count%20the%20Objects/) | An image as a 2D array, 8-connectivity, recursive component labeling |

---

## Multidimensional Arrays in C

### 1. What a 2D array is

A **2D array** is an **array of arrays**: a grid with **rows** and **columns**.

```c
int m[3][4];       // 3 rows, 4 columns, 12 ints
```

| | col 0 | col 1 | col 2 | col 3 |
|---|---|---|---|---|
| **row 0** | `m[0][0]` | `m[0][1]` | `m[0][2]` | `m[0][3]` |
| **row 1** | `m[1][0]` | `m[1][1]` | `m[1][2]` | `m[1][3]` |
| **row 2** | `m[2][0]` | `m[2][1]` | `m[2][2]` | `m[2][3]` |

`m[r][c]` is always **row first, column second**, and both count from 0. `m[r]` alone is the whole row `r`, an array of 4 `int`s.

Natural fits: game boards (tic-tac-toe, chess), matrices, images, seating charts, spreadsheets.

### 2. Declaring and initializing

```c
int a[2][3] = { {1, 2, 3},
                {4, 5, 6} };          // one inner { } per row

int b[2][3] = {0};                    // all zeros
int c[][3]  = { {1, 2, 3}, {4, 5, 6} };  // row count inferred: 2
char board[3][3] = { {' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '} };
```

Only the **first** size may be left out, because the compiler needs the row length.

### 3. Traversing

Nested loops: the **outer** loop picks the row, the **inner** loop walks its columns.

```c
for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++)
        printf("%d ", m[r][c]);
    printf("\n");                      // end of the row
}
```

Reading works the same way:

```c
for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
        scanf("%d", &m[r][c]);
```

**Column by column:** swap the loops, so the column is outside and the row inside.

### 4. Memory layout

C stores 2D arrays in **row-major order**: row 0, then row 1, and so on, in one continuous block.

```
int a[2][3] = { {1,2,3}, {4,5,6} };

memory:  [ 1 | 2 | 3 ][ 4 | 5 | 6 ]
           row 0        row 1
```

Element `a[r][c]` is element number `r × cols + c` of that block. Consequences:

- The address of row 1 is 3 × 4 = 12 bytes after row 0 (with 4-byte `int`s).
- A 2D grid can be stored in a 1D array of size `rows × cols` and accessed as `a[r * cols + c]`.
- Traversing **row by row** visits memory in order, which is faster than column by column on large arrays.

### 5. Passing 2D arrays to functions

The function must know the **row length** (every size except the first) to compute where each row starts:

```c
void display(int m[3][3]);             // all sizes given
void display(int m[][3], int rows);    // first size left out
void display(int rows, int cols, int m[rows][cols]);   // C99 variable-length: sizes come first
```

As with 1D arrays, the function receives the **address**, so changes it makes are visible to the caller. MP 7's labels written deep in the recursion show up in `countObjects` this way.

**The sizes must match.** In MP 7, a `px[rn][cn]` array passed to a function expecting `int[100][100]` gives garbage: the function assumes rows are 100 elements apart, but they're really `cn` apart.

### 6. Capacity vs. size

Fixed-size declarations often hold a smaller grid:

```c
int m[10][10];     // capacity: 10 × 10
int n;             // size actually used: n × n (3 ≤ n ≤ 10)
```

- Loop to `n`, not to 10.
- The "last" row or column is `n - 1`, not 9.
- Cells outside `n × n` hold garbage unless initialized.

### 7. Rows, columns and diagonals

For an `n × n` grid:

| Part | Cells | Loop |
|---|---|---|
| Row `r` | `m[r][0] … m[r][n-1]` | `for c: m[r][c]` |
| Column `c` | `m[0][c] … m[n-1][c]` | `for r: m[r][c]` |
| Main diagonal (↘) | row = column | `for i: m[i][i]` |
| Anti-diagonal (↙) | row + column = n − 1 | `for i: m[i][n-1-i]` |
| Upper triangle | column > row | `for r, for c = r+1 …` |
| Border | row or column is 0 or n − 1 | `r == 0 \|\| r == n-1 \|\| c == 0 \|\| c == n-1` |

```
main ↘          anti ↙
X . . .         . . . X
. X . .         . . X .
. . X .         . X . .
. . . X         X . . .
```

### 8. Neighbors and bounds checking

Cells on the edge have fewer neighbors. **Check bounds before reading:**

```c
int inBounds(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}
```

Neighbor offsets as arrays (as in MP 7):

```c
// 8-connected: all surrounding cells
int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};
int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};

for (int k = 0; k < 8; k++) {
    int nr = r + dr[k], nc = c + dc[k];
    if (inBounds(nr, nc, rows, cols)) { /* use m[nr][nc] */ }
}
```

For **4-connectivity** (up, down, left, right only), use the four offsets with exactly one zero.

### 9. Matrix operations

**Addition** (same sizes):

```c
for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
        C[r][c] = A[r][c] + B[r][c];
```

**Transpose** (rows become columns):

```c
for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
        T[c][r] = A[r][c];
```

**Multiplication** (`A` is `n × m`, `B` is `m × p`, result `n × p`):

```c
for (int i = 0; i < n; i++)
    for (int j = 0; j < p; j++) {
        C[i][j] = 0;
        for (int k = 0; k < m; k++)
            C[i][j] += A[i][k] * B[k][j];
    }
```

**Row and column sums:** one total per row in the outer loop, or swap the loops for columns.

### 10. Character grids and boards

A `char` 2D array works well for boards:

```c
char board[3][3];
board[r - 1][c - 1] = 'x';     // input counts from 1, arrays from 0
```

**Checking for a line of three** (MP 6): a line wins if its cells are equal **and not empty**.

```c
if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2])   // row i
```

Without the `!= ' '` check, an empty row counts as "three in a row".

**An array of strings** is also a 2D `char` array: `char names[5][30]` holds 5 strings of up to 29 characters each.

### 11. Three or more dimensions

Add a subscript per dimension, and a loop per dimension:

```c
int m[3][2][3];        // 3 matrices, each 2 × 3

for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
        for (int k = 0; k < 3; k++)
            m[i][j][k] = 0;
```

`m[i]` is a whole 2 × 3 matrix, so it can be passed to any function that takes `int[2][3]`.

### 12. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| `m[r, c]` | Means `m[c]` (comma operator), not a cell | `m[r][c]` |
| Swapping rows and columns | Reads the wrong cells, or out of bounds on non-square grids | Row first, always |
| Using 1-based input as indices | Off by one, or out of bounds at 3 | `m[r - 1][c - 1]` |
| Reading neighbors without a bounds check | Garbage or a crash on edge cells | Check `0 ≤ r < rows` and `0 ≤ c < cols` first |
| Looping to the capacity instead of the size | Processes garbage cells | Loop to `n` |
| `printf("\n")` inside the inner loop | One value per line | Put it after the inner loop |
| Leaving out a size other than the first in a parameter | Compile error | `int m[][COLS]` |
| Passing a `[rn][cn]` array to an `[100][100]` parameter | Rows are read from the wrong place | Declare matching sizes |

---

## Quick Reference

```c
int m[ROWS][COLS] = {0};

for (int r = 0; r < rows; r++) {           // visit every cell
    for (int c = 0; c < cols; c++)
        printf("%d ", m[r][c]);
    printf("\n");
}

void f(int m[][COLS], int rows);           // parameter: all sizes but the first
```

| I want... | Use |
|---|---|
| Last row | `m[n-1][c]` for every `c` |
| Last column | `m[r][n-1]` for every `r` |
| Main diagonal | `m[i][i]` |
| Anti-diagonal | `m[i][n-1-i]` |
| Cell from 1-based input | `m[row-1][col-1]` |
| 2D cell in a 1D array | `a[r * cols + c]` |
| The 8 neighbors | `dr`, `dc` offset arrays + a bounds check |
