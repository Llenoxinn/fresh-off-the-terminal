# 02 - Iterations in C

CMSC 11 machine problems on loops in C, followed by a reference covering everything you need to know about iteration.

## Contents

- [Machine Problems](#machine-problems)
  - [Problem A: Perfect Number](#problem-a-perfect-number--a-perfectc)
  - [Problem B: Power](#problem-b-power--b-powerc)
  - [Problem C: nth Fibonacci Element](#problem-c-nth-fibonacci-element--c-fibonaccic)
  - [Problem D: Factorial](#problem-d-factorial--d-factorialc)
  - [Guessing Game](#guessing-game--guessing-gamec)
  - [Honor Code](#honor-code)
- [Iterations in C](#iterations-in-c)
  1. [What a loop is](#1-what-a-loop-is)
  2. [`while`](#2-while)
  3. [`do`-`while`](#3-do-while)
  4. [`for`](#4-for)
  5. [Choosing a loop](#5-choosing-a-loop)
  6. [Counters and accumulators](#6-counters-and-accumulators)
  7. [Controlling loops: counter, sentinel, flag](#7-controlling-loops-counter-sentinel-flag)
  8. [`break` and `continue`](#8-break-and-continue)
  9. [Infinite loops](#9-infinite-loops)
  10. [Input validation loops](#10-input-validation-loops)
  11. [Tracing a loop](#11-tracing-a-loop)
  12. [Overflow: when the numbers get too big](#12-overflow-when-the-numbers-get-too-big)
  13. [Random numbers](#13-random-numbers)
  14. [Common patterns](#14-common-patterns)
  15. [Common mistakes](#15-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | File | Concepts |
|---|---|---|
| A: Perfect Number | [A-Perfect.c](A-Perfect.c) | `for`, accumulator, `%` for factors |
| B: Power | [B-Power.c](B-Power.c) | `while`, repeated multiplication, special cases |
| C: nth Fibonacci Element | [C-Fibonacci.c](C-Fibonacci.c) | Rolling variables, overflow limits |
| D: Factorial | [D-Factorial.c](D-Factorial.c) | Accumulating a product, overflow limits |
| Guessing Game | [Guessing Game.c](Guessing%20Game.c) | Limited tries, `break`, early `return` |

All problems print **exact output messages, including case**.

### Problem A: Perfect Number · `A-Perfect.c`

> Ask the user to enter a positive number and determine if it is a perfect number or not. A number is perfect if the sum of all its factors except itself is itself. 6 is perfect because the sum of its factors 1, 2, 3, excluding 6, is 6.
>
> Print `YES` if the input is a perfect number, `NO` when it is not, and `INVALID INPUT` if it is invalid. For invalid input, do not ask the user to re-enter it. Simply print the message.

| Input | Output | Why |
|---|---|---|
| `6` | `YES` | 1 + 2 + 3 = 6 |
| `28` | `YES` | 1 + 2 + 4 + 7 + 14 = 28 |
| `12` | `NO` | 1 + 2 + 3 + 4 + 6 = 16 |
| `-5` | `INVALID INPUT` | Not positive |

**Approach:** loop `i` from 1 to `num - 1`. Whenever `num % i == 0`, `i` is a factor, so add it to `sum`. After the loop, compare `sum` with `num`.

### Problem B: Power · `B-Power.c`

> Ask the user to enter two integers, x and y, and display x raised to y. x and y may be negative, 0, or positive.
>
> When the exponent is negative, print the result as a fraction. For instance, if x is 2 and y is -3, print `1/8`. Do not print it with floating points. When both x and y are 0, print `INDETERMINATE`.

| Input (x y) | Output |
|---|---|
| `2 3` | `8` |
| `2 -3` | `1/8` |
| `-3 3` | `-27` |
| `5 0` | `1` |
| `0 0` | `INDETERMINATE` |
| `0 -2` | `UNDEFINED` |

**Approach:** multiply `answer` by `x`, `|y|` times, using a `while` loop. If `y` was negative, print it as `1/answer`. `y == 0` gives `1`. The solution also prints `UNDEFINED` for 0 raised to a negative power, since that would mean dividing by zero. The problem statement doesn't cover that case.

### Problem C: nth Fibonacci Element · `C-Fibonacci.c`

> Ask the user to enter a positive integer n and display the nth Fibonacci element. The first (n = 1) and second (n = 2) elements are both 1. For n greater than 2, add the (n-1)th and (n-2)th elements.
>
> `1, 1, 2, 3, 5, 8, 13, 21, 34, ...`
>
> Inputs greater than 47 should be flagged as invalid. The 47th Fibonacci element is 2971215073, which can no longer fit in an `int`. Print `INVALID INPUT` when the input is invalid.

| Input | Output |
|---|---|
| `1` | `1` |
| `2` | `1` |
| `10` | `55` |
| `47` | `2971215073` |
| `48` | `INVALID INPUT` |
| `0` | `INVALID INPUT` |

**Approach:** keep only the last two elements, `first` and `second`. Each step computes `next = first + second`, then shifts both forward. No array is needed. The values are stored in `unsigned long long` so the 47th element fits (see [section 12](#12-overflow-when-the-numbers-get-too-big)).

### Problem D: Factorial · `D-Factorial.c`

> Ask the user to enter a non-negative number n and display its factorial. The factorial of 5 (written 5!) is 5 × 4 × 3 × 2 × 1 = 120.
>
> Print `INVALID INPUT` when the input is invalid. Inputs beyond 12 are invalid as well: 13! is already over 6 billion.

| Input | Output |
|---|---|
| `0` | `1` |
| `5` | `120` |
| `12` | `479001600` |
| `13` | `INVALID INPUT` |
| `-1` | `INVALID INPUT` |

**Approach:** start `factorial` at `1` (not 0) and multiply it by every `i` from 1 to `n`. For `n = 0` the loop never runs, so the result stays `1`, which is correct because 0! = 1.

### Guessing Game · `Guessing Game.c`

> Generate a random number from 1–100 and ask the user to guess it. Give them 5 tries, using a HIGHER/LOWER scheme for clues. If they guess it within the allotted tries, congratulate them. If they still haven't guessed it on the 5th try, reveal the magic number.
>
> Implement the game as it should be, but for submission (and auto-checking), **do not generate the magic number: read it as input**.

| Situation | Output |
|---|---|
| Guess is smaller than the magic number | `HIGHER` |
| Guess is bigger than the magic number | `LOWER` |
| Correct guess within 5 tries | `CONGRATULATIONS! YOU GUESSED IT!` |
| 5th guess is still wrong | `SORRY. THE MAGIC NUMBER IS <magic number>.` |

**Sample run: guessed correctly** (first line is the magic number)

```
42
50
LOWER
25
HIGHER
42
CONGRATULATIONS! YOU GUESSED IT!
```

**Sample run: out of tries**

```
42
10
HIGHER
90
LOWER
30
HIGHER
50
LOWER
41
SORRY. THE MAGIC NUMBER IS 42.
```

**Approach:** read the magic number, then loop while there are guesses to read. A correct guess prints the congratulations and ends the program with `return`. Otherwise, count the try and print a hint, except on the 5th try, where the loop `break`s and the magic number is revealed.

To play the real version, generate the number instead of reading it (see [section 13](#13-random-numbers)):

```c
srand((unsigned int) time(NULL));
magic = 1 + rand() % 100;
```

### Honor Code

Every submission starts with one of these declarations as a comment:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

> I declare, upon my honor, that I did this machine problem assignment by myself using online resources from the following (please cite the online sources). Further, my solution is not a copy from the aforementioned sources.

---

## Iterations in C

### 1. What a loop is

A **loop** repeats a block of code while a condition is true. Every loop has the same four parts:

| Part | Example | Purpose |
|---|---|---|
| **Initialization** | `int i = 1;` | Set up the loop variable before the first check |
| **Condition** | `i <= n` | Checked before (or after) each pass; the loop stops when it is false |
| **Body** | `sum += i;` | The work repeated on each pass |
| **Update** | `i++` | Moves toward making the condition false |

If the update never makes the condition false, the loop never ends. One pass through the body is called an **iteration**.

### 2. `while`

Checks the condition **before** each iteration. If it is false at the start, the body runs **zero times**.

```c
int i = 1;
while (i <= 5) {
    printf("%d ", i);
    i++;
}
// 1 2 3 4 5
```

Best when you **don't know in advance** how many times to loop, such as reading input until it runs out:

```c
while (scanf("%d", &guess) == 1) {
    ...
}
```

### 3. `do`-`while`

Checks the condition **after** each iteration, so the body always runs **at least once**. Note the semicolon at the end.

```c
int n;
do {
    printf("Enter a positive number: ");
    scanf("%d", &n);
} while (n <= 0);
```

Best for menus and input prompts, where you have to ask at least once before you can check anything.

### 4. `for`

Puts initialization, condition and update on one line. Best when you **know how many times** to loop.

```c
for (int i = 1; i <= 5; i++) {
    printf("%d ", i);
}
```

Order of execution:

1. Initialization, once.
2. Check the condition. If false, the loop ends.
3. Run the body.
4. Run the update, then go back to step 2.

Any of the three parts can be left out, but the semicolons stay:

```c
int i = 0;
for (; i < 5; ) { i++; }   // same as a while loop
for (;;) { ... }           // infinite loop
```

You can use more than one variable with commas:

```c
for (int i = 0, j = 10; i < j; i++, j--) { ... }
```

A variable declared in the `for` header (`int i = 1`) only exists inside the loop. Declare it before the loop if you need its value afterwards. Declarations inside `for` need C99 or later.

Counting in other steps and directions:

```c
for (int i = 10; i >= 1; i--)      // 10 down to 1
for (int i = 0; i <= 100; i += 5)  // 0, 5, 10, ..., 100
for (int i = 1; i <= 1000; i *= 2) // 1, 2, 4, ..., 512
```

### 5. Choosing a loop

| Loop | Condition checked | Minimum runs | Use when |
|---|---|---|---|
| `for` | before | 0 | The number of iterations is known (1 to n, each index) |
| `while` | before | 0 | You loop until something happens (input runs out, a value is found) |
| `do`-`while` | after | 1 | The body must run once before you can check (prompts, menus) |

Any loop can be rewritten as either of the others. Pick the one that reads most naturally.

### 6. Counters and accumulators

A **counter** counts how many times something happens. Start at `0` and add `1`.

```c
int count = 0;
for (int i = 1; i <= n; i++)
    if (n % i == 0)
        count++;          // number of factors of n
```

An **accumulator** builds up a result. Start at the **identity value** for the operation:

| Operation | Start at | Example |
|---|---|---|
| Sum | `0` | `sum += i;` (Problem A) |
| Product | `1` | `factorial *= i;` (Problem D) |
| Maximum | the first value, or the smallest possible | `if (x > max) max = x;` |
| Minimum | the first value, or the largest possible | `if (x < min) min = x;` |

Starting a product at `0` makes the answer always `0`. Forgetting to initialize at all leaves garbage in the variable.

### 7. Controlling loops: counter, sentinel, flag

**Counter-controlled:** runs a fixed number of times.

```c
for (int t = 1; t <= 5; t++) { ... }   // five tries
```

**Sentinel-controlled:** runs until a special value is entered.

```c
int x, sum = 0;
scanf("%d", &x);
while (x != -1) {          // -1 is the sentinel
    sum += x;
    scanf("%d", &x);
}
```

**Flag-controlled:** runs until a variable signals that the job is done.

```c
int found = 0;
for (int i = 0; i < n && !found; i++)
    if (arr[i] == target)
        found = 1;
```

The Guessing Game combines the first two: it stops after 5 tries **or** when the guess is correct.

### 8. `break` and `continue`

| Statement | Effect |
|---|---|
| `break` | Leaves the innermost loop (or `switch`) immediately |
| `continue` | Skips the rest of this iteration and goes to the next one |

```c
for (int i = 1; i <= 10; i++) {
    if (i == 7) break;       // stop completely at 7
    if (i % 2 == 0) continue; // skip even numbers
    printf("%d ", i);
}
// 1 3 5
```

In a `for` loop, `continue` still runs the update (`i++`). In a `while` loop, `continue` jumps straight to the condition, so if the update is at the bottom of the body it gets skipped, which can cause an infinite loop:

```c
int i = 0;
while (i < 10) {
    if (i == 5) continue;   // i never moves past 5
    i++;
}
```

`return` inside a loop leaves the whole function, not just the loop. The Guessing Game uses it to end the program as soon as the guess is correct.

### 9. Infinite loops

A loop whose condition never becomes false. Sometimes on purpose:

```c
while (1) {
    scanf("%d", &choice);
    if (choice == 0) break;   // the only way out
    ...
}
```

Usually by accident:

```c
for (int i = 0; i < 10; i--)   // i moves away from 10
while (n != 0) n -= 2;         // skips over 0 when n starts odd
while (x < 10);                // the ; is an empty body, so x never changes
```

Press **Ctrl + C** in the terminal to stop a program stuck in an infinite loop.

### 10. Input validation loops

The machine problems here print `INVALID INPUT` once and stop. In interactive programs, you usually ask again instead:

```c
int n;
while (1) {
    printf("Enter a number from 1 to 100: ");
    if (scanf("%d", &n) == 1 && n >= 1 && n <= 100)
        break;
    printf("Invalid, try again.\n");
    while (getchar() != '\n');   // throw away the bad input
}
```

Without that last line, typing a letter leaves it in the input. `scanf` fails on it again on every pass, and the loop never ends.

### 11. Tracing a loop

Write down each variable after every iteration. It is the quickest way to find a bug or check an answer by hand.

Fibonacci for `n = 6`, starting with `first = 1`, `second = 1`:

| `i` | `next = first + second` | `first` | `second` |
|---|---|---|---|
| start | – | 1 | 1 |
| 3 | 2 | 1 | 2 |
| 4 | 3 | 2 | 3 |
| 5 | 5 | 3 | 5 |
| 6 | 8 | 5 | 8 |

Answer: `second = 8`. Check against the sequence `1, 1, 2, 3, 5, 8`.

**Off-by-one check:** count how many times the body runs.

| Loop | Runs |
|---|---|
| `for (i = 0; i < n; i++)` | `n` times (0 to n-1) |
| `for (i = 1; i <= n; i++)` | `n` times (1 to n) |
| `for (i = 0; i <= n; i++)` | `n + 1` times |
| `for (i = 1; i < n; i++)` | `n - 1` times (Problem A: every number below `num`) |

### 12. Overflow: when the numbers get too big

Loops that multiply or add repeatedly grow fast. Every integer type has a maximum. Going past it **overflows**: signed types give undefined behavior (usually a wrong or negative number), and unsigned types wrap around to 0.

Typical sizes on a modern computer:

| Type | Max value | `printf` | Largest factorial | Largest Fibonacci |
|---|---|---|---|---|
| `int` | 2,147,483,647 | `%d` | 12! | 46th |
| `unsigned int` | 4,294,967,295 | `%u` | 12! | 47th |
| `long long` | 9,223,372,036,854,775,807 | `%lld` | 20! | 92nd |
| `unsigned long long` | 18,446,744,073,709,551,615 | `%llu` | 20! | 93rd |

This is why Problem C stops at 47 (2,971,215,073 is above the `int` max) and Problem D stops at 12 (13! = 6,227,020,800). `<limits.h>` defines `INT_MAX`, `LLONG_MAX` and similar constants if you need the exact limits in code.

Use the matching `printf` specifier. Printing an `unsigned long long` with `%d` shows the wrong number.

### 13. Random numbers

```c
#include <stdlib.h>   // rand, srand
#include <time.h>     // time

srand((unsigned int) time(NULL));   // seed ONCE, at the start of main
int r = rand();                     // 0 to RAND_MAX
```

| Range | Expression |
|---|---|
| 0 to n-1 | `rand() % n` |
| 1 to n | `1 + rand() % n` |
| low to high | `low + rand() % (high - low + 1)` |

Without `srand`, `rand()` gives the **same sequence every run**. Calling `srand(time(NULL))` inside a loop re-seeds with the same second, so you get the same number repeatedly. Seed once.

### 14. Common patterns

**Sum from 1 to n**

```c
int sum = 0;
for (int i = 1; i <= n; i++)
    sum += i;
```

**Count the digits of a number**

```c
int digits = 0;
do {
    digits++;
    n /= 10;
} while (n != 0);   // do-while so that 0 counts as 1 digit
```

**Sum of digits**

```c
int sum = 0;
while (n > 0) {
    sum += n % 10;  // last digit
    n /= 10;        // drop the last digit
}
```

**Reverse a number**

```c
int rev = 0;
while (n > 0) {
    rev = rev * 10 + n % 10;
    n /= 10;
}
```

**Prime check**

```c
int isPrime = (n >= 2);
for (int i = 2; i * i <= n; i++) {   // only need to check up to √n
    if (n % i == 0) {
        isPrime = 0;
        break;
    }
}
```

**Greatest common divisor (Euclid's algorithm)**

```c
while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
}
// a is the GCD
```

**Largest of n inputs**

```c
int x, max;
scanf("%d", &max);              // first value starts as the max
for (int i = 1; i < n; i++) {
    scanf("%d", &x);
    if (x > max) max = x;
}
```

**Multiplication table** (a loop inside a loop; see [04 - Nested Loops](../04%20-%20Nested%20Loops/))

```c
for (int r = 1; r <= 10; r++) {
    for (int c = 1; c <= 10; c++)
        printf("%4d", r * c);
    printf("\n");
}
```

### 15. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| `while (x < 10);` or `for (...);` | The `;` is the whole body; the real body runs once or the loop hangs | Remove the semicolon |
| Forgetting the update (`i++`) | Infinite loop | Make sure each pass moves toward ending the loop |
| `<` vs `<=` | Loop runs one time too many or too few | Count the iterations (see [section 11](#11-tracing-a-loop)) |
| Accumulator not initialized | Starts with garbage | `int sum = 0;` before the loop |
| Product starting at `0` | Result is always 0 | Start at `1` |
| Resetting the accumulator inside the loop | Only the last value counts | Initialize before the loop |
| `continue` before the update in a `while` | Update is skipped, so the loop hangs | Update before `continue`, or use `for` |
| Result too big for `int` | Wrong or negative numbers | Use `long long` / `unsigned long long`, or limit the input |
| `srand` inside the loop | Same "random" number every time | Call `srand` once |
| Missing `;` after `do { } while (...)` | Compile error | `} while (cond);` |
| Using a `for`-header variable after the loop | Compile error: out of scope | Declare it before the loop |
| `scanf` failing inside a loop | Bad input stays in the buffer and the loop spins forever | Check `scanf`'s return value and clear the input |

---

## Quick Reference

```c
while (condition) {
    ...
}

do {
    ...
} while (condition);

for (init; condition; update) {
    ...
}

break;      // leave the loop now
continue;   // skip to the next iteration
```

| I want to... | Use |
|---|---|
| Repeat exactly n times | `for (int i = 0; i < n; i++)` |
| Count down | `for (int i = n; i >= 1; i--)` |
| Repeat until input runs out | `while (scanf("%d", &x) == 1)` |
| Run at least once, then check | `do { ... } while (cond);` |
| Stop early | `break` |
| Skip one iteration | `continue` |
| Sum values | `sum = 0;` then `sum += x;` |
| Multiply values | `prod = 1;` then `prod *= x;` |
| Get the last digit | `n % 10` |
| Drop the last digit | `n /= 10` |
| Random number from 1 to n | `1 + rand() % n` (after `srand(time(NULL))` once) |
