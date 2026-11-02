# CMSC 11 - Introduction to Computer Science

Machine problems and notes from **CMSC 11**, a first course in programming using **C**. The course starts with making decisions in code, then works through loops, strings, nested loops and arrays, and ends with a larger machine problem assignment that combines all of them.

Each topic folder has its own README with the original problem statements, sample runs, a walkthrough of the solution, and a full reference on that topic.

## Contents

- [Course Map](#course-map)
- [Folder Structure](#folder-structure)
- [All Problems](#all-problems)
- [Compiling and Running](#compiling-and-running)
- [Course Conventions](#course-conventions)
- [C Cheat Sheet](#c-cheat-sheet)
  - [Program skeleton](#program-skeleton)
  - [Data types and format specifiers](#data-types-and-format-specifiers)
  - [Operators](#operators)
  - [Selection](#selection)
  - [Loops](#loops)
  - [Arrays](#arrays)
  - [Strings](#strings)
  - [Input patterns](#input-patterns)
- [Problem-Solving Checklist](#problem-solving-checklist)
- [Common Mistakes Across the Course](#common-mistakes-across-the-course)
- [Notes on the Solutions](#notes-on-the-solutions)
- [What's Next](#whats-next)

---

## Course Map

| # | Topic | Key ideas | Problems |
|---|---|---|---|
| 01 | [Selection and Branching](01%20-%20Selection%20and%20Branching%20using%20C/) | `if`, `else if`, nested `if`, `switch`, relational and logical operators | 3 |
| 02 | [Iterations](02%20-%20Iterations%20in%20C/) | `while`, `do`-`while`, `for`, counters, accumulators, `break`, overflow | 5 |
| 03 | [Strings](03%20-%20Strings/) | `char` arrays, `'\0'`, `<string.h>`, `<ctype.h>`, reading lines | 2 |
| 04 | [Nested Loops](04%20-%20Nested%20Loops/) | Loops inside loops, prime checks, bit shifts, `long long` | 2 |
| 05 | [Arrays](05%20-%20Arrays/) | Indexing, linear vs. binary search, counting comparisons, Big-O | 1 |
| – | [Machine Problem Assignment](Machine%20Problem%20Assignment/) | FLAMES game and substring search: everything combined | 1 |
| – | [Mastery](Mastery/) | Digit manipulation: rotating numbers, comparing neighboring digits | 2 |

Each topic builds on the ones before it:

```
Selection ──► Iterations ──► Nested Loops ──┐
                  │                         ├──► Machine Problem Assignment
                  └────► Strings ──► Arrays ┘
```

---

## Folder Structure

```
cmsc11-intro-to-cs/
├── README.md                          ← you are here
├── 01 - Selection and Branching using C/
│   ├── ProblemA.c                     descending order of 3 numbers
│   ├── ProblemB.c                     rainfall warning levels
│   └── ProblemC.c                     zodiac fortune teller
├── 02 - Iterations in C/
│   ├── A-Perfect.c                    perfect number check
│   ├── B-Power.c                      x to the power y, fractions for y < 0
│   ├── C-Fibonacci.c                  nth Fibonacci element
│   ├── D-Factorial.c                  factorial
│   └── Guessing Game.c                guess the number in 5 tries
├── 03 - Strings/
│   ├── prefix.c                       is string 2 a prefix of string 1?
│   └── hexadecimal.c                  is the string a valid hex number?
├── 04 - Nested Loops/
│   ├── A-nthPerfect.c                 first n perfect numbers
│   └── B-primalityCheck.c             prime check without % or /
├── 05 - Arrays/
│   └── amII.c                         is there an A[i] == i? linear vs. binary
├── Machine Problem Assignment/
│   └── flamesAndGenes.c               FLAMES game + gene sequence search
└── Mastery/
    ├── rotateRight.c                  rotate a number's digits right
    └── consecutiveDigits.c            do neighboring digits differ by 1?
```

Every folder also has its own `README.md`.

---

## All Problems

| Topic | Problem | File | Core technique |
|---|---|---|---|
| 01 | Descending Order | [ProblemA.c](01%20-%20Selection%20and%20Branching%20using%20C/ProblemA.c) | Nested `if` over 6 orderings |
| 01 | Rainfall Warning | [ProblemB.c](01%20-%20Selection%20and%20Branching%20using%20C/ProblemB.c) | `else if` ranges on a `float` |
| 01 | Zodiac Fortune Teller | [ProblemC.c](01%20-%20Selection%20and%20Branching%20using%20C/ProblemC.c) | Compound `&&` / `\|\|` conditions, date validation |
| 02 | Perfect Number | [A-Perfect.c](02%20-%20Iterations%20in%20C/A-Perfect.c) | Sum of factors with `%` |
| 02 | Power | [B-Power.c](02%20-%20Iterations%20in%20C/B-Power.c) | Repeated multiplication, special cases |
| 02 | nth Fibonacci Element | [C-Fibonacci.c](02%20-%20Iterations%20in%20C/C-Fibonacci.c) | Two rolling variables |
| 02 | Factorial | [D-Factorial.c](02%20-%20Iterations%20in%20C/D-Factorial.c) | Product accumulator, overflow limit |
| 02 | Guessing Game | [Guessing Game.c](02%20-%20Iterations%20in%20C/Guessing%20Game.c) | Limited tries, `break` |
| 03 | prefix | [prefix.c](03%20-%20Strings/prefix.c) | Character-by-character comparison |
| 03 | isHexadecimal | [hexadecimal.c](03%20-%20Strings/hexadecimal.c) | Walking to `'\0'`, character ranges |
| 04 | First n Perfect Numbers | [A-nthPerfect.c](04%20-%20Nested%20Loops/A-nthPerfect.c) | Mersenne primes, `1LL << p` |
| 04 | Primality without Modulo | [B-primalityCheck.c](04%20-%20Nested%20Loops/B-primalityCheck.c) | Modulo by repeated subtraction |
| 05 | Am I i? | [amII.c](05%20-%20Arrays/amII.c) | Linear and binary search |
| MP | Flame it on the Gene | [flamesAndGenes.c](Machine%20Problem%20Assignment/flamesAndGenes.c) | Letter cancelling, `% 6` cycle, substring search |
| Mastery | Rotate Right | [rotateRight.c](Mastery/rotateRight.c) | `% 10`, `/ 10`, place values |
| Mastery | Consecutive Digits | [consecutiveDigits.c](Mastery/consecutiveDigits.c) | Comparing neighboring digits |

---

## Compiling and Running

You need a C compiler. On Windows, install **MinGW-w64** (for example through MSYS2). On macOS, run `xcode-select --install`. On Linux, install `gcc`.

```bash
# compile
gcc -Wall -Wextra -o prefix "03 - Strings/prefix.c"

# run and type the input
./prefix

# or feed input from a file
./prefix < input.txt

# or pipe it in
echo "mastery master" | ./prefix
```

On Windows the program is `prefix.exe`, and in PowerShell you run it with `.\prefix.exe`. PowerShell doesn't support `<`, so pipe the input instead: `Get-Content input.txt | .\prefix.exe`.

| Flag | Purpose |
|---|---|
| `-o name` | Name of the output program |
| `-Wall -Wextra` | Turn on warnings. Many bugs show up here first |
| `-std=c99` | Allow `for (int i = 0; ...)` on older compilers |
| `-lm` | Link the math library when using `<math.h>` (needed on Linux) |
| `-g` | Include debug info for `gdb` |

**Testing against expected output:** save the sample input and expected output to files, then compare.

```bash
./amII < sample_in.txt > my_out.txt
diff my_out.txt sample_out.txt       # no output means they match
```

---

## Course Conventions

These rules apply to every problem in the course.

**Honor code.** Every source file starts with a signed declaration as a comment:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

or, when online resources were used:

> I declare, upon my honor, that I did this machine problem assignment by myself using online resources from the following: *(list of sources)*. Further, my solution is not a copy from the aforementioned sources.

**Exact output.** Solutions are auto-checked by comparing output character by character. Messages must match **exactly, including case, spacing and punctuation**.

**No prompts unless asked.** Text like `Enter a number:` becomes part of the output and fails the check.

**`INVALID INPUT`.** For bad input, print the message once and stop. Don't ask again.

**Problem-specific restrictions.** Some problems ban certain tools to make you build them yourself. For example, Problem B in topic 04 bans `%` and `/`, and Problem A in topic 04 bans writing your own functions.

---

## C Cheat Sheet

### Program skeleton

```c
#include <stdio.h>     // printf, scanf, fgets
#include <string.h>    // strlen, strcpy, strcmp, strcspn
#include <ctype.h>     // tolower, toupper, isdigit, isalpha
#include <stdlib.h>    // abs, rand, srand, atoi
#include <math.h>      // sqrt, pow (compile with -lm on Linux)

int main() {
    // declarations
    // input
    // processing
    // output
    return 0;
}
```

### Data types and format specifiers

| Type | Typical range | `scanf` | `printf` |
|---|---|---|---|
| `int` | ±2,147,483,647 | `%d` | `%d` |
| `unsigned int` | 0 to 4,294,967,295 | `%u` | `%u` |
| `long long` | ±9.22 × 10¹⁸ | `%lld` | `%lld` |
| `unsigned long long` | 0 to 1.84 × 10¹⁹ | `%llu` | `%llu` |
| `float` | ~7 significant digits | `%f` | `%f` |
| `double` | ~15 significant digits | `%lf` | `%f` |
| `char` | one character | `%c` (use `" %c"` to skip whitespace) | `%c` |
| `char[]` | a string | `%s` (one word) | `%s` |

`printf` options: `%5d` (width 5), `%-5d` (left-aligned), `%05d` (pad with zeros), `%.2f` (2 decimals).

### Operators

| Kind | Operators |
|---|---|
| Arithmetic | `+ - * / %` (integer `/` drops the decimals: `7 / 2` is `3`) |
| Assignment | `= += -= *= /= %=` |
| Increment | `++ --` |
| Relational | `== != < > <= >=` |
| Logical | `&& \|\| !` (short-circuit) |
| Conditional | `cond ? a : b` |
| Bitwise | `& \| ^ ~ << >>` (`1LL << k` is 2ᵏ) |
| Casting | `(double) sum / n` |

### Selection

```c
if (x > 0) {
    ...
} else if (x < 0) {
    ...
} else {
    ...
}

switch (choice) {
    case 1: ...; break;
    case 2: case 3: ...; break;
    default: ...;
}
```

### Loops

```c
for (int i = 0; i < n; i++) { ... }       // known number of times
while (condition) { ... }                  // until something happens
do { ... } while (condition);              // at least once

break;      // leave the loop
continue;   // skip to the next iteration
```

### Arrays

```c
int a[20] = {0};                           // capacity 20, all zeros
for (int i = 0; i < n; i++) scanf("%d", &a[i]);

int m[3][4];                               // 2D: 3 rows, 4 columns
m[r][c] = 0;
```

Indexes run from `0` to `size - 1`. C does not check bounds.

### Strings

```c
char s[101];                               // up to 100 characters + '\0'
scanf("%100s", s);                         // one word
fgets(s, sizeof s, stdin);                 // whole line
s[strcspn(s, "\n")] = '\0';                // remove the newline from fgets

strlen(s);            // length
strcpy(dst, src);     // copy
strcat(dst, src);     // append
strcmp(a, b) == 0;    // equal?
tolower(c);           // per character
```

### Input patterns

```c
// validate input
if (scanf("%d", &n) != 1 || n <= 0) {
    printf("INVALID INPUT");
    return 0;
}

// t test cases
int t;
scanf("%d", &t);
while (t--) { ... }

// read until input runs out
while (scanf("%d", &x) == 1) { ... }

// a number followed by a line of text
scanf("%d", &n);
getchar();                                 // eat the leftover '\n'
fgets(line, sizeof line, stdin);

// digits of a number
while (n > 0) {
    int d = n % 10;
    n /= 10;
}
```

---

## Problem-Solving Checklist

1. **Read the whole problem twice.** Mark the exact output messages and any restrictions.
2. **Work the samples by hand.** If you can't get the sample output on paper, you can't code it yet.
3. **List the edge cases.** Zero, negative, 1-digit, empty, the maximum allowed size, values right on a boundary.
4. **Choose types that fit.** Will the answer pass 2.1 billion? Use `long long`.
5. **Write it in small steps.** Read input → print it back → add processing → format output.
6. **Test with the samples, then your edge cases.** Compare output exactly.
7. **Trace by hand when stuck.** Write a table of variables per loop iteration.
8. **Check the honor code** is at the top of the file.

---

## Common Mistakes Across the Course

| Mistake | Topic | Fix |
|---|---|---|
| `=` instead of `==` in a condition | 01 | `if (x == 5)` |
| `1 <= x <= 12` | 01 | `x >= 1 && x <= 12` |
| `;` right after `if (...)`, `for (...)` or `while (...)` | 01, 02 | Remove it |
| Accumulator not initialized, or a product starting at 0 | 02 | `sum = 0`, `prod = 1` |
| Off-by-one: `<=` vs `<` | 02, 05 | Count the iterations |
| Integer overflow | 02, 04 | `long long`, `1LL << k`, limit the input |
| No room for `'\0'` | 03 | Size strings as length + 1 |
| `scanf("%s")` with no width | 03 | `%99s` for `char s[100]` |
| `fgets` reading the leftover `'\n'` from `scanf` | 03, MP | `getchar()` after `scanf` |
| Comparing strings with `==` | 03 | `strcmp(a, b) == 0` |
| Reusing `i` in an inner loop | 04 | Use `j`, `k` |
| `break` expected to exit both loops | 04 | Flag or `return` |
| Out-of-bounds index | 05 | `i < n`, never `i <= n` |
| Binary search on unsorted data | 05 | Sort first |
| Output that is almost right | all | Compare against the expected output character by character |

---

## Notes on the Solutions

These solutions are kept as they were submitted. While writing the READMEs, the programs were compiled and run against the sample inputs. These differences from the problem statements turned up:

| File | Note |
|---|---|
| [03 - Strings/hexadecimal.c](03%20-%20Strings/hexadecimal.c), [prefix.c](03%20-%20Strings/prefix.c) | Arrays have no room for `'\0'` at the maximum length (`[100]` for 100 characters, `[500]` for 500) |
| [02 - Iterations in C/Guessing Game.c](02%20-%20Iterations%20in%20C/Guessing%20Game.c) | Prints `CONGRATULATIONS.` with a period. The spec says `CONGRATULATIONS!` |
| [02 - Iterations in C/B-Power.c](02%20-%20Iterations%20in%20C/B-Power.c) | Negative base with negative exponent prints `1/-8` instead of `-1/8` |
| [04 - Nested Loops/B-primalityCheck.c](04%20-%20Nested%20Loops/B-primalityCheck.c) | Never tries 2 as a factor, so 4, 6 and 10 are reported as prime |
| [Machine Problem Assignment/flamesAndGenes.c](Machine%20Problem%20Assignment/flamesAndGenes.c) | Prints `MARRIED with`, `ENGAGED with` and `be ACCEPT` instead of `MARRIED to`, `ENGAGED to` and `ACCEPT` |
| [Mastery/](Mastery/) | The problem statement is incomplete. The two programs implement the two ideas it describes |

---

## What's Next

The follow-up course, [CMSC 21 - Fundamentals of Programming](../cmsc21-fundamentals/), continues in C with **functions**, **recursion**, and **structures and enumerations**.
