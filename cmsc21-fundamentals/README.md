# CMSC 21 - Fundamentals of Programming

Machine problems and notes from **CMSC 21**, the follow-up to [CMSC 11](../cmsc11-intro-to-cs/). It goes deeper into **C**, covering functions, recursion, structures, 2D arrays, dynamic memory and linked lists, then ends with an introduction to **C++ classes**.

Each topic folder has its own README with a full reference on that topic. Each machine problem has a README with the problem statement, sample runs, a walkthrough of the approach and notes on the solution.

## Contents

- [Course Map](#course-map)
- [Folder Structure](#folder-structure)
- [All Problems](#all-problems)
- [Compiling and Running](#compiling-and-running)
- [Course Conventions](#course-conventions)
- [Cheat Sheet: What's New Since CMSC 11](#cheat-sheet-whats-new-since-cmsc-11)
- [Common Mistakes Across the Course](#common-mistakes-across-the-course)
- [Notes on the Solutions](#notes-on-the-solutions)

---

## Course Map

| # | Topic | Key ideas | MPs |
|---|---|---|---|
| 01 | [Functions](01%20-%20Functions/) | Prototypes, pass by value, returning results, separating computation from I/O, counting iterations | 3 |
| 02 | [Recursion](02%20-%20Recursion/) | Base and recursive cases, the call stack, halving the problem | 1 |
| 03 | [Structures and Enumerations](03%20-%20Structures%20and%20Enumerations/) | `struct`, `typedef`, `enum`, `.` vs `->`, header files | 3 |
| 04 | [Multidimensional Arrays](04%20-%20Multidimensional%20Arrays/) | 2D arrays, boards, diagonals, neighbors, flood fill | 3 |
| 05 | [Dynamic Arrays](05%20-%20Dynamic%20Arrays/) | `malloc`, `realloc`, `free`, the vector | 1 |
| 06 | [Linked Lists](06%20-%20Linked%20Lists/) | Nodes, insertion, removal, sorted lists | 2 |
| 07 | [Classes (C++)](07%20-%20Classes%20%28C++%29/) | Classes, constructors, encapsulation, `cin`/`cout` | 1 |

How the topics build on each other:

```
Functions ──► Recursion ──────────────────────────┐
    │                                             ▼
    └──► Structures ──► 2D Arrays ──► Dynamic Arrays ──► Linked Lists ──► C++ Classes
```

---

## Folder Structure

```
cmsc21-fundamentals/
├── README.md                                   ← you are here
├── 01 - Functions/
│   ├── MPA 1 - Functions Galore/               20 library functions rebuilt by hand
│   ├── MP 1-1 - Sophies World/                 Sophie Germain primes, 3 primality checks
│   └── MP 1-2 - Relatively Prime/              naive vs. Euclidean GCD
├── 02 - Recursion/
│   └── MP 4 - See Recursion/                   multiply without *, recursive palindrome
├── 03 - Structures and Enumerations/
│   ├── MP 2 - Terms of Endearment/             multiply two terms like 4x^3
│   ├── MPA 2 - Bantugans Fight/                turn-based duel simulation
│   └── MP 8 - Show Me the Money/               bank accounts in a list (bank.h, bank.c, main.c)
├── 04 - Multidimensional Arrays/
│   ├── MP 6-mini - 2 Dimensions/               last row, last column, diagonals
│   ├── MP 6 - Tic-Tac/                         tic-tac-toe
│   └── MP 7 - Count the Objects/               count connected objects in an image
├── 05 - Dynamic Arrays/
│   └── MP 9 - Les Miserables/                  a vector that grows
├── 06 - Linked Lists/
│   ├── MP 10 - The Polynomial has many Faces/  polynomial arithmetic
│   └── MP 11 - First and Foremost a Student/   a class list of students
└── 07 - Classes (C++)/
    └── MP 13 - Mambo Number Class/             a Number class (number.h, number.cpp, main.cpp)
```

---

## All Problems

| Topic | Problem | Source | Core technique |
|---|---|---|---|
| 01 | Functions Galore | [FunctionsGalore.c](01%20-%20Functions/MPA%201%20-%20Functions%20Galore/FunctionsGalore.c) | Rebuilding `floor`, `toupper`, `atoi`, `strcmp`, … without libraries |
| 01 | Sophie's World | [Germain.c](01%20-%20Functions/MP%201-1%20-%20Sophies%20World/Germain.c) | Primality to n−1, n/2 and √n; returning two facts in one `int` |
| 01 | Relatively Prime | [AreWeRelatives.c](01%20-%20Functions/MP%201-2%20-%20Relatively%20Prime/AreWeRelatives.c) | Linear search vs. the Euclidean algorithm |
| 02 | See Recursion | [recursion.c](02%20-%20Recursion/MP%204%20-%20See%20Recursion/recursion.c) | Multiplication by halving, two-bound palindrome check |
| 03 | Terms of Endearment | [endearmentDear.c](03%20-%20Structures%20and%20Enumerations/MP%202%20-%20Terms%20of%20Endearment/endearmentDear.c) | A term `struct`, parsing `4x^3`, display rules |
| 03 | Bantugans, Fight! | [Bantugans.c](03%20-%20Structures%20and%20Enumerations/MPA%202%20-%20Bantugans%20Fight/Bantugans.c) | Warrior `struct`, weapon/shield `enum`s, pointers to structures |
| 03 | Show Me the Money | [main.c](03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/main.c), [bank.c](03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/bank.c), [bank.h](03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/bank.h) | Array-based list, multi-file program |
| 04 | 2 Dimensions | [mp6mini.c](04%20-%20Multidimensional%20Arrays/MP%206-mini%20-%202%20Dimensions/mp6mini.c) | Rows, columns, diagonals |
| 04 | Tic-Tac-Toe | [tictactoe.c](04%20-%20Multidimensional%20Arrays/MP%206%20-%20Tic-Tac/tictactoe.c) | `char` board, win and draw checks |
| 04 | Count the Objects | [arrayKoPo.c](04%20-%20Multidimensional%20Arrays/MP%207%20-%20Count%20the%20Objects/arrayKoPo.c) | Recursive flood fill, 8-connectivity |
| 05 | Les Misérables | [miserable.c](05%20-%20Dynamic%20Arrays/MP%209%20-%20Les%20Miserables/miserable.c) | A vector with `malloc`/`realloc` |
| 06 | The Polynomial has many Faces | [polynomics.c](06%20-%20Linked%20Lists/MP%2010%20-%20The%20Polynomial%20has%20many%20Faces/polynomics.c) | Polynomials as linked lists of terms |
| 06 | First and Foremost a Student | [areYouAStud.c](06%20-%20Linked%20Lists/MP%2011%20-%20First%20and%20Foremost%20a%20Student/areYouAStud.c) | Linked list of student records |
| 07 | Mambo Number Class | [main.cpp](07%20-%20Classes%20%28C++%29/MP%2013%20-%20Mambo%20Number%20Class/main.cpp), [number.cpp](07%20-%20Classes%20%28C++%29/MP%2013%20-%20Mambo%20Number%20Class/number.cpp), [number.h](07%20-%20Classes%20%28C++%29/MP%2013%20-%20Mambo%20Number%20Class/number.h) | A C++ class with private data |

---

## Compiling and Running

```bash
# one C file
gcc -Wall -o prog "02 - Recursion/MP 4 - See Recursion/recursion.c"
./prog < input.txt

# several C files (list every .c, never the .h)
cd "03 - Structures and Enumerations/MP 8 - Show Me the Money"
gcc -Wall -o bank main.c bank.c

# C++ (use g++, not gcc)
cd "07 - Classes (C++)/MP 13 - Mambo Number Class"
g++ -Wall -o number main.cpp number.cpp
echo "10 12" | ./number
```

| Flag | Purpose |
|---|---|
| `-Wall -Wextra` | Warnings: many bugs show up here first |
| `-g` | Debug info for `gdb` |
| `-fsanitize=address` | Catch out-of-bounds and use-after-free bugs at run time (useful from topic 05 on) |
| `-lm` | Link the math library when using `<math.h>` (Linux) |

On Windows, run `chcp 65001` first if the tic-tac-toe board's box-drawing characters show up garbled.

---

## Course Conventions

**Honor code.** Every solution starts with a declaration as a comment, before any `#include`:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

or, when online resources were used (**LLMs excluded**, as later MPs specify), the version that lists the sources. MPA 1 also allowed a collaboration version. MP 4 states that it and the laboratory MPs after it allow **no collaboration** and use the first version only.

**Exact output.** Solutions are auto-checked on **VPL**, character by character: case, spacing, punctuation and trailing spaces all matter. Use **Run** to test, not **Evaluate**.

**Functions don't print.** Starting with topic 01, the problem's functions compute and return; only `main` (or a designated `display` function) does input and output.

**Restrictions are part of the problem.** Different MPs ban library functions, global variables, pointers, structures, `sqrt`, or extra function arguments, to make you build the idea yourself.

**Startup files.** Several MPs come with instructor-provided starting code. Those files are reproduced in the MP's README.

---

## Cheat Sheet: What's New Since CMSC 11

**Functions**

```c
int add(int a, int b);                 // prototype above main
int add(int a, int b) { return a + b; }
void fill(int a[], int n);             // arrays are shared, not copied
```

**Recursion**

```c
int fact(int n) {
    if (n <= 1) return 1;              // base case
    return n * fact(n - 1);            // recursive case, smaller input
}
```

**Structures and enumerations**

```c
typedef enum { WOOD = 1, SILVER, DIAMOND } Shield;
typedef struct { int hp; Shield shield; } Warrior;

Warrior w = {10, SILVER};
Warrior *p = &w;
w.hp = 9;                              // structure: .
p->hp = 8;                             // pointer:   ->
```

**2D arrays**

```c
int m[10][10];
m[r][c] = 0;                           // row first
void f(int m[][10], int n);            // all sizes but the first
```

**Dynamic memory**

```c
int *a = malloc(n * sizeof(int));
a = realloc(a, 2 * n * sizeof(int));
free(a);
```

**Linked lists**

```c
typedef struct node { int data; struct node *next; } node;
for (node *c = head; c != NULL; c = c->next) ...;
```

**C++ classes**

```cpp
class Number {
private:
    int value;
public:
    Number(int n) { value = n; }
    int get() { return value; }
};
Number n(10);
cout << n.get() << endl;
```

---

## Common Mistakes Across the Course

| Mistake | Topic | Fix |
|---|---|---|
| Printing inside a function the MP says must only compute | 01 | Return the result; print in `main` |
| No reachable base case | 02 | Every call must shrink toward the base case |
| `.` on a pointer, or `->` on a structure | 03 | `ptr->field`, `obj.field` |
| Passing a structure by value to a function that must change it | 03 | Pass a pointer |
| Off-by-one positions (`p <= size` vs `p < size`) | 05, 06 | Insert allows `size`; access and remove don't |
| Reading neighbors without a bounds check | 04 | Check `0 ≤ r < rows`, `0 ≤ c < cols` first |
| `malloc(n)` instead of `malloc(n * sizeof(int))` | 05 | Always multiply by `sizeof` |
| Losing `head` while traversing | 06 | Traverse with a separate pointer |
| Comparing strings with `==` | 03, 06 | `strcmp(a, b) == 0` |
| Using a name the standard library already has (`remove`) | 05 | Pick another name |
| Compiling C++ with `gcc` | 07 | Use `g++` |
| Output that's almost right | all | Compare with the expected output character by character |

---

## Notes on the Solutions

These solutions are kept as they were submitted. While writing the READMEs, several programs were compiled and run against their samples. Each MP's README has details under **About This Solution**:

| MP | Note |
|---|---|
| [MP 4](02%20-%20Recursion/MP%204%20-%20See%20Recursion/) | Matches the sample. A palindrome mismatch doesn't print `Base case!`; the sample doesn't settle whether it should |
| [MPA 2](03%20-%20Structures%20and%20Enumerations/MPA%202%20-%20Bantugans%20Fight/) | Matches the sample. Item flags are overwritten each turn, so a found item may vanish before it's used |
| [MP 6-mini](04%20-%20Multidimensional%20Arrays/MP%206-mini%20-%202%20Dimensions/) | Correct values, but trailing spaces, no 10 × 10 array, and no random number |
| [MP 6](04%20-%20Multidimensional%20Arrays/MP%206%20-%20Tic-Tac/) | Correct games, but loops forever if the input ends before the game does |
| [MP 7](04%20-%20Multidimensional%20Arrays/MP%207%20-%20Count%20the%20Objects/) | Correct counts, but prints `objects`/`object` instead of the sample's `Objects` |
| [MP 9](05%20-%20Dynamic%20Arrays/MP%209%20-%20Les%20Miserables/) | Matches the sample except test 6, which itself contradicts the problem statement. Some position checks are off by one |

Two samples appear to contain errors: **MP 9** test case 6 and **MP 10** line 1. Both are explained in their READMEs.
