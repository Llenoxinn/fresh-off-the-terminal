# 01 - Functions

CMSC 21 machine problems on **writing and using functions in C**, followed by a reference covering everything you need to know about functions.

## Contents

- [Machine Problems](#machine-problems)
- [Functions in C](#functions-in-c)
  1. [What a function is](#1-what-a-function-is)
  2. [Anatomy of a function](#2-anatomy-of-a-function)
  3. [Calling a function](#3-calling-a-function)
  4. [Prototypes (declarations)](#4-prototypes-declarations)
  5. [Return values](#5-return-values)
  6. [`void` functions](#6-void-functions)
  7. [Pass by value](#7-pass-by-value)
  8. [Passing arrays and strings](#8-passing-arrays-and-strings)
  9. [Scope and lifetime](#9-scope-and-lifetime)
  10. [Why no global variables](#10-why-no-global-variables)
  11. [Returning more than one result](#11-returning-more-than-one-result)
  12. [Separating computation from I/O](#12-separating-computation-from-io)
  13. [Helper functions and reuse](#13-helper-functions-and-reuse)
  14. [Measuring running time by counting](#14-measuring-running-time-by-counting)
  15. [Common mistakes](#15-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MPA 1: Functions Galore | [MPA 1 - Functions Galore](MPA%201%20-%20Functions%20Galore/) | 20 functions that rebuild library functions (`floor`, `toupper`, `atoi`, `strcmp`, ...) from scratch |
| MP 1-1: Sophie's World | [MP 1-1 - Sophies World](MP%201-1%20-%20Sophies%20World/) | Three primality checks as functions, counting iterations, returning two facts in one value |
| MP 1-2: We all relative(ly prime) | [MP 1-2 - Relatively Prime](MP%201-2%20-%20Relatively%20Prime/) | Linear search vs. the Euclidean algorithm, 2-argument functions |

Rules shared by the three:

- **Functions compute, `main` does the I/O.** No `printf` inside the problem's functions.
- **No global variables.** Everything a function needs comes in through its parameters.
- **Restricted tools.** MPA 1 allows no library functions except `scanf` and `printf`. MPs 1-1 and 1-2 allow no pointers or structures, and MP 1-1 bans `sqrt`.

---

## Functions in C

### 1. What a function is

A **function** is a named block of code that takes inputs (**parameters**), does a job, and optionally gives back a result (**return value**).

Functions let you:

- **Name** a piece of logic (`isPrime(n)` reads better than the loop it contains).
- **Reuse** it without copying code (MP 1-1 calls each primality check twice).
- **Test** pieces separately.
- **Hide** details: `main` only needs to know *what* a function does, not *how*.

You have been using functions all along: `main`, `printf`, `scanf`, `strlen`.

### 2. Anatomy of a function

```c
// return type   name   parameters
   int           max    (int a, int b) {
       return a > b ? a : b;           // body
   }
```

| Part | Meaning |
|---|---|
| Return type | Type of the value given back: `int`, `double`, `char`, ... or `void` for nothing |
| Name | Follows variable naming rules. Use a verb or a question: `reverseInt`, `isUpper` |
| Parameters | Typed inputs, separated by commas. `(void)` or `()` for none |
| Body | The statements, between `{ }` |
| `return` | Ends the function and gives back a value |

### 3. Calling a function

```c
int bigger = max(3, 8);           // use the result
printf("%d\n", max(x, y));        // directly inside another call
max(1, 2);                        // allowed, but the result is thrown away
```

The **arguments** (`3`, `8`) are copied into the **parameters** (`a`, `b`) in order. Their number and types must match.

When a function is called, execution jumps into it, runs until `return` (or the closing `}`), then continues right after the call.

### 4. Prototypes (declarations)

C reads top to bottom. A function must be **declared before it is called**. Either define it above `main`, or put a **prototype** at the top and the full definition anywhere below:

```c
#include <stdio.h>

int isPrime(int n);              // prototype: return type, name, parameter types

int main() {
    printf("%d\n", isPrime(7));
    return 0;
}

int isPrime(int n) {             // definition
    ...
}
```

Prototypes let `main` sit at the top, where it reads like a summary of the program. Parameter names are optional in prototypes (`int isPrime(int);`), but they help readability.

### 5. Return values

- `return expr;` ends the function immediately and gives back `expr`, converted to the return type.
- A function can have **several** `return` statements, for example one inside a loop to exit early.
- **Every path** through a non-`void` function must return a value. Falling off the end gives garbage.

```c
int absValue(int n) {
    if (n < 0)
        return -n;
    return n;                    // the other path
}
```

A function returns **one** value. For "two results", see [section 11](#11-returning-more-than-one-result).

### 6. `void` functions

A `void` function returns nothing. Use `return;` (with no value) to leave early, or just reach the closing `}`.

```c
void printLine(int n) {
    for (int i = 0; i < n; i++)
        printf("-");
    printf("\n");
}
```

You can't use the "result" of a `void` function: `int x = printLine(5);` is an error.

### 7. Pass by value

C passes arguments **by value**: the parameter is a **copy**. Changing it inside the function does **not** change the caller's variable.

```c
void tryToChange(int x) {
    x = 100;                     // changes the copy only
}

int main() {
    int a = 5;
    tryToChange(a);
    printf("%d\n", a);           // still 5
}
```

This is why `reverseInt(n)` can freely do `n /= 10` without destroying `main`'s copy of `n`.

### 8. Passing arrays and strings

Arrays are the exception that **feels** like pass-by-reference. Passing an array actually passes the **address of its first element**, so the function works on the **caller's array**, not a copy.

```c
void toUpperAll(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;          // changes the caller's string
}

int main() {
    char word[51] = "hello";
    toUpperAll(word);
    printf("%s\n", word);        // HELLO
}
```

Consequences:

- A function **can modify** an array argument. MPA 1's copy, camel case and reverse items rely on this.
- Mark arrays the function shouldn't change as `const`: `int strLength(const char s[])`.
- The function **doesn't know the array's size**. Strings stop at `'\0'`; for other arrays, pass the size as another parameter.
- A function **cannot return** an array. Have the caller pass in the array to fill.
- `char s[]` and `char *s` mean the same thing as parameters. MPs 1-1 and 1-2 don't involve arrays, so their "no pointers" rule never comes up.

### 9. Scope and lifetime

| Kind | Declared | Visible | Lives |
|---|---|---|---|
| **Local** | inside a function or block | only inside that block | until the block ends |
| **Parameter** | in the function header | inside the function | until the function returns |
| **Global** | outside all functions | everywhere below it | the whole program |
| **`static` local** | inside a function, with `static` | inside the function | the whole program (keeps its value between calls) |

Two functions can have local variables with the **same name**. They are completely separate.

```c
int square(int n) { int result = n * n; return result; }
int cube(int n)   { int result = n * n * n; return result; }   // a different `result`
```

A local variable's value is gone after the function returns. **Never return the address of a local array.**

### 10. Why no global variables

Global variables are visible to every function, so any function might change them. That makes programs harder to follow and test, and it hides what a function depends on. The rule forces each function's inputs to be its **parameters** and its output to be its **return value**, so you can understand it on its own.

### 11. Returning more than one result

MP 1-1 and MP 1-2 need two facts from one call ("is it prime?" **and** "how many iterations?"), but they ban pointers, structures and globals. The way out is to **encode** both facts in one number:

| Encoding | Prime / Yes | Not prime / No | Works when count can be 0 for both? |
|---|---|---|---|
| Sign | `count` | `-count` | No: `0` is ambiguous |
| Shifted sign | `count` | `-(count + 1)` | Yes |
| Offset | `count` | `count + 1000000000` | Yes, if counts stay below the offset |

```c
long long r = checkSqrt(n);
int isPrime = (r >= 0);
long long count = isPrime ? r : -r - 1;
```

Once pointers or structures are allowed (later in the course), these are the usual ways:

```c
// pointer output parameter
int isPrimeCount(long long n, long long *count);

// structure return
struct Result { int isPrime; long long count; };
struct Result check(long long n);
```

### 12. Separating computation from I/O

All three MPs say **no printing inside the functions**. Functions that only compute and return:

- can be **reused** anywhere: in `main`, in other functions, in tests.
- can be **combined**: `isAlnum` can call `isAlpha`, which can call `isUpper` and `isLower`.
- keep the output format in **one place** (`main`), so changing `YES` to `Yes` is one edit.

```c
// computes only
int isUpper(char c) { return c >= 'A' && c <= 'Z'; }

// main decides how to show it
printf("%s\n", isUpper(c) ? "YES" : "NO");
```

### 13. Helper functions and reuse

Small helpers keep the larger functions short. MPA 1 forbids library functions but allows your own, so write the basics once and reuse them:

```c
int strLength(const char s[]) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

int isLower(char c) { return c >= 'a' && c <= 'z'; }
char toUpper(char c) { return isLower(c) ? c - 'a' + 'A' : c; }

void reverseStr(char s[]) {
    for (int i = 0, j = strLength(s) - 1; i < j; i++, j--) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
    }
}
```

A good function does **one thing**, has a name that says what, and is short enough to read at a glance.

### 14. Measuring running time by counting

MPs 1-1 and 1-2 compare algorithms by **counting iterations** instead of timing them, since the count doesn't depend on how fast the computer is.

```c
long long count = 0;
for (...) {
    count++;                     // one per iteration, before any early exit
    if (/* done */) break;
}
```

| Growth | Example from this topic | Iterations for n = 1,000,000 |
|---|---|---|
| Linear, n | Naive primality check, naive GCF | ~1,000,000 |
| n / 2, n / 4 | Primality skipping evens, half version | ~500,000, ~250,000 |
| Square root, √n | Primality up to `cf * cf <= n` | ~1,000 |
| Logarithmic, log n | Euclidean algorithm | ~30 |

Halving the work (skipping evens) helps, but changing the **growth rate** (√n, log n) helps far more as `n` grows.

### 15. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Calling a function before it's declared | Compiler warning or error | Add a prototype above `main` |
| Prototype and definition don't match | Compile error or wrong values | Same return type and parameter types in both |
| Missing `return` on some path | Garbage result | Return a value on every path |
| Expecting a parameter change to reach the caller | The caller's variable is unchanged | Return the new value (or use a pointer, once allowed) |
| Returning a local array | Dangling memory | Fill an array the caller passes in |
| `sizeof` on an array parameter | Pointer size, not the array size | Pass the length, or stop at `'\0'` |
| Printing inside a "compute" function | Breaks the MP rules; output in the wrong place | Return the result and print in `main` |
| Using a global to pass data | Breaks the MP rules; hidden dependencies | Use parameters and return values |
| `int` for values that grow large | Overflow (`2x + 1` for x = 2³¹ − 1) | `long long` |
| Ambiguous encoded return value | Can't tell results apart (0 means both) | Use an encoding with no overlap |

---

## Quick Reference

```c
#include <stdio.h>

// prototypes
int    add(int a, int b);
void   greet(void);
double average(const int a[], int n);
void   fill(int a[], int n, int value);

int main() {
    int s = add(2, 3);                 // call and use the result
    greet();                           // void call
    return 0;
}

int add(int a, int b) {
    return a + b;
}

void greet(void) {
    printf("Hello\n");
}
```

| I want to... | Use |
|---|---|
| Call before defining | Prototype at the top |
| Give back one value | `return value;` |
| Give back nothing | `void` return type |
| Leave a `void` function early | `return;` |
| Let a function change an array | Pass the array; it is shared |
| Protect an array from changes | `const` parameter |
| Tell the function the array size | Extra `int n` parameter |
| Return two facts without pointers | Encode them into one value |
| Keep state between calls | `static` local (avoid in these MPs) |
