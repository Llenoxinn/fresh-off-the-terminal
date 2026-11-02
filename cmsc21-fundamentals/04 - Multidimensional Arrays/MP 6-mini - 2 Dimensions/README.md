# MP 6-mini: 2 Directions, err, 2-Dimensions

CMSC 21 mini machine problem on **multidimensional arrays**: read an `n × n` matrix into a `10 × 10` array, then print its **last column**, its **last row** and both **diagonals**, using functions that take the 2D array and its size.

## Contents

- [Lesson: Multidimensional Arrays](#lesson-multidimensional-arrays)
  - [Boards and matrices](#boards-and-matrices)
  - [Declaring and initializing](#declaring-and-initializing)
  - [Accessing elements](#accessing-elements)
  - [How a 2D array sits in memory](#how-a-2d-array-sits-in-memory)
  - [Example: matrix addition](#example-matrix-addition)
  - [Three dimensions](#three-dimensions)
- [Mini-MP](#mini-mp)
  - [Task](#task)
  - [Sample](#sample)
- [Approach](#approach)
  - [Last column](#last-column)
  - [Last row](#last-row)
  - [Diagonals](#diagonals)
  - [The random number](#the-random-number)
  - [Capacity vs. size](#capacity-vs-size)
- [Edge Cases](#edge-cases)
- [Testing Checklist](#testing-checklist)

---

## Lesson: Multidimensional Arrays

### Boards and matrices

Tic-tac-toe has a **3 × 3** board, chess an **8 × 8** board, and a matrix can be **3 × 5**. There are three ways to store these:

| Approach | Tic-tac-toe | How a cell is found |
|---|---|---|
| One 1D array | `int tic[9];` | Row `r`, column `c` is `tic[r * 3 + c]`: `tic[0]` is (0, 0), `tic[8]` is (2, 2) |
| Several 1D arrays | `int row0[3], row1[3], row2[3];` | Pick the array, then the index |
| **One 2D array** | `int tic[3][3];` | `tic[r][c]` |

A 2D array keeps the grid shape in the code:

```c
int tictactoeBoard[3][3];   // 3 rows, 3 columns,  9 elements
int chessBoard[8][8];       // 8 rows, 8 columns, 64 elements
int matrix[3][5];           // 3 rows, 5 columns, 15 elements
```

The first size is the number of **rows**, the second the number of **columns**.

### Declaring and initializing

A 2D array is an **array of arrays**. Initialize it with one inner `{ }` per row:

```c
int matrix[2][3] = { {2, 3, 4},
                     {1, 0, 5} };   // 2 rows of 3 elements: 6 in total
```

| | Col 0 | Col 1 | Col 2 |
|---|---|---|---|
| **Row 0** | 2 | 3 | 4 |
| **Row 1** | 1 | 0 | 5 |

### Accessing elements

`matrix[i][j]` is **row `i`, column `j`**, with both counting from 0. `matrix[0]` alone is the entire first row, an array of 3 `int`s, so a second index is needed to reach one element. `matrix[0][1]` is the second element of the first row: `3`.

To visit every element, nest two loops: the **outer** loop goes through rows, the **inner** loop through the columns of that row.

```c
for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
        printf("%i ", matrix[i][j]);
    printf("\n");
}
```

```
2 3 4
1 0 5
```

Swapping the loops (columns outside, rows inside) visits the matrix column by column instead.

### How a 2D array sits in memory

The rows are stored **one after another** in a single block (**row-major order**):

```
matrix:  [ 2 | 3 | 4 ][ 1 | 0 | 5 ]
           row 0        row 1
```

```c
printf("%p\n", matrix[0]);   // 0x7ffeedd97840   (your addresses will differ)
printf("%p\n", matrix[1]);   // 0x7ffeedd9784c
```

The two addresses differ by **0x0c = 12 bytes**: row 0 holds 3 `int`s of 4 bytes each.

This is also why a function parameter must give every size **except the first**. The compiler needs the row length to find where each row starts: `void f(int m[][3], int rows)`.

### Example: matrix addition

Add two matrices of the same size by adding matching elements:

$$
\begin{bmatrix} 2 & 3 & 4 \\ 1 & 0 & 5 \end{bmatrix}
+
\begin{bmatrix} 0 & 2 & 1 \\ 2 & 2 & 2 \end{bmatrix}
=
\begin{bmatrix} 2 & 5 & 5 \\ 3 & 2 & 7 \end{bmatrix}
$$

```c
#include <stdio.h>

void add(int[2][3], int[2][3], int[2][3]);
void display(int[2][3]);

int main() {
    int m1[2][3] = {{2, 3, 4}, {1, 0, 5}};
    int m2[2][3] = {{0, 2, 1}, {2, 2, 2}};
    int ans[2][3];

    add(m1, m2, ans);
    display(m1);
    printf("+\n");
    display(m2);
    printf("=\n");
    display(ans);
    return 0;
}

void add(int A[2][3], int B[2][3], int C[2][3]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void display(int m[2][3]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
            printf("%i ", m[i][j]);
        printf("\n");
    }
}
```

```
2 3 4
1 0 5
+
0 2 1
2 2 2
=
2 5 5
3 2 7
```

`add` writes into `C`, and `main` sees the result in `ans`, because arrays are passed by address, not copied.

### Three dimensions

Add another subscript to get a 3D array. `int m1[3][2][3]` is **three 2 × 3 matrices** in one array:

```c
int m1[3][2][3] = { {{2, 3, 4}, {1, 0, 5}},     // m1[0]
                    {{0, 2, 1}, {2, 2, 2}},     // m1[1]
                    {{0, 0, 0}, {0, 0, 0}} };   // m1[2]
```

Each `m1[k]` is a 2 × 3 matrix, so the **same** `add` and `display` work on the pieces:

```c
add(m1[0], m1[1], m1[2]);     // m1[2] = m1[0] + m1[1]
```

Or treat it as a whole, with three nested loops:

```c
void display(int m[3][2][3]) {
    for (int i = 0; i < 3; i++) {          // each matrix
        for (int j = 0; j < 2; j++) {      // each row
            for (int k = 0; k < 3; k++)    // each column
                printf("%i ", m[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
}
```

```
2 3 4
1 0 5

0 2 1
2 2 2

0 0 0
0 0 0
```

The pattern keeps going: `n` subscripts, `n` nested loops.

> **Caveat (VPL):** when testing the code, use **Run** instead of **Evaluate**.

---

## Mini-MP

### Task

1. Declare a **10 × 10** array of integers.
2. Read a positive integer `n` (**3 ≤ n ≤ 10**), then an **`n × n`** matrix.
3. Implement these as **functions that accept the 10 × 10 array and the size `n`**:
   - print the **last column**
   - print the **last row**
   - print the **diagonals**
4. In the diagonals function, **generate a random number from −1,000,000,000 to 1,000,000,000**. **Do not print it.**

### Sample

**Input**

```
4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
```

**Output**

```
4
8
12
16
13 14 15 16
1 6 11 16
4 7 10 13
```

| Lines | Part | Format |
|---|---|---|
| 1–4 | Last column | One element **per line** |
| 5 | Last row | One line, separated by spaces |
| 6 | Main diagonal (top-left → bottom-right) | One line |
| 7 | Anti-diagonal (top-right → bottom-left) | One line |

```
 [1]  2   3  (4)
  5  [6] (7)  8
  9 (10)[11] 12
(13) 14  15 [16]

[ ] main diagonal    ( ) anti-diagonal    last column: 4 8 12 16    last row: 13 14 15 16
```

---

## Approach

The pattern in all three: **fix one index and loop over the other**, or tie the two indices together.

| Part | Row | Column |
|---|---|---|
| Last column | `i` = 0 … n−1 | **n − 1** (fixed) |
| Last row | **n − 1** (fixed) | `j` = 0 … n−1 |
| Main diagonal | `i` | `i` (row = column) |
| Anti-diagonal | `i` | **n − 1 − i** (row + column = n − 1) |

### Last column

```c
void lastColumn(int m[10][10], int n) {
    for (int i = 0; i < n; i++)
        printf("%d\n", m[i][n - 1]);
}
```

### Last row

```c
void lastRow(int m[10][10], int n) {
    for (int j = 0; j < n; j++)
        printf(j == 0 ? "%d" : " %d", m[n - 1][j]);
    printf("\n");
}
```

Printing the space **before** every element except the first avoids a trailing space at the end of the line.

### Diagonals

```c
void diagonals(int m[10][10], int n) {
    // random number required by the MP, never printed
    long long secret = randomInRange(-1000000000LL, 1000000000LL);
    (void) secret;

    for (int i = 0; i < n; i++)
        printf(i == 0 ? "%d" : " %d", m[i][i]);           // main diagonal
    printf("\n");

    for (int i = 0; i < n; i++)
        printf(i == 0 ? "%d" : " %d", m[i][n - 1 - i]);   // anti-diagonal
    printf("\n");
}
```

`(void) secret;` tells the compiler the unused variable is intentional, which silences the warning.

### The random number

```c
#include <stdlib.h>   // rand, srand
#include <time.h>     // time

srand((unsigned) time(NULL));   // once, at the start of main
```

The usual formula is `low + rand() % (high - low + 1)`. Here the range has **2,000,000,001** values, and `rand()` may not reach that high:

| Platform | `RAND_MAX` | Problem |
|---|---|---|
| Windows (MinGW, MSVC) | 32,767 | `rand()` alone covers only 0–32,767 |
| Linux (glibc) | 2,147,483,647 | Large enough, but `high - low + 1` must not overflow `int` |

Combining several `rand()` calls into a `long long` works on both:

```c
long long randomInRange(long long low, long long high) {
    long long r = ((long long) rand() << 30) ^ ((long long) rand() << 15) ^ rand();
    if (r < 0) r = -r;
    return low + r % (high - low + 1);
}
```

Three 15-bit pieces give at least 45 random bits, which is plenty to cover the range.

> The MP doesn't say what the number is for, only that it must be generated and not printed. Printing it would add an unpredictable line and fail the exact-output check.

### Capacity vs. size

The array is always **10 × 10** (its **capacity**), but only the top-left **`n × n`** part is used (its **size**).

```
n = 4 inside a 10 × 10 array:

 1  2  3  4  .  .  .  .  .  .
 5  6  7  8  .  .  .  .  .  .
 9 10 11 12  .  .  .  .  .  .
13 14 15 16  .  .  .  .  .  .
 .  .  .  .  .  .  .  .  .  .     ← unused, garbage unless initialized
```

- Use `n - 1`, not `9`, for "last". The last column is `m[i][n - 1]`, not `m[i][9]`.
- Loop to `n`, not `10`.
- Read with the same bounds:

```c
int m[10][10];
scanf("%d", &n);
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        scanf("%d", &m[i][j]);
```

---

## Edge Cases

| Case | Note |
|---|---|
| `n = 3` (smallest) | The diagonals share the center element `m[1][1]` |
| Odd `n` | Both diagonals contain the middle element. Print it in both lines |
| `n = 10` (largest) | Uses the full array; `n - 1` is 9 |
| Negative numbers in the matrix | `%d` handles them; nothing special |
| `n` outside 3–10 | Not expected. Writing past 10 rows or columns would overflow the array |

---

## Testing Checklist

**Smallest size**

```
3
1 2 3
4 5 6
7 8 9
```

```
3
6
9
7 8 9
1 5 9
3 5 7
```

**The sample** (`n = 4`) gives the output above.

**Largest size:** a 10 × 10 matrix numbered 1–100 row by row should print the last column `10, 20, …, 100`, the last row `91 … 100`, the main diagonal `1 12 23 … 100` and the anti-diagonal `10 19 28 … 91`.
