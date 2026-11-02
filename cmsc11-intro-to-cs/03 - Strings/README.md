# 03 - Strings

CMSC 11 machine problems on strings in C, followed by a reference covering everything you need to know about C strings.

## Contents

- [Machine Problems](#machine-problems)
  - [prefix](#prefix--prefixc)
  - [isHexadecimal](#ishexadecimal--hexadecimalc)
- [Strings in C](#strings-in-c)
  1. [What a string is](#1-what-a-string-is)
  2. [Declaring and initializing](#2-declaring-and-initializing)
  3. [Arrays vs. pointers vs. literals](#3-arrays-vs-pointers-vs-literals)
  4. [Reading strings](#4-reading-strings)
  5. [Printing strings](#5-printing-strings)
  6. [Walking through a string](#6-walking-through-a-string)
  7. [`<string.h>` functions](#7-stringh-functions)
  8. [`<ctype.h>` character functions](#8-ctypeh-character-functions)
  9. [Converting between strings and numbers](#9-converting-between-strings-and-numbers)
  10. [Arrays of strings](#10-arrays-of-strings)
  11. [Passing strings to functions](#11-passing-strings-to-functions)
  12. [Common patterns](#12-common-patterns)
  13. [Common mistakes](#13-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | File | Concepts |
|---|---|---|
| prefix | [prefix.c](prefix.c) | `strlen`, comparing characters by index, early exit |
| isHexadecimal | [hexadecimal.c](hexadecimal.c) | Walking to `'\0'`, character range checks |

### prefix · `prefix.c`

Ask for **two input strings** of up to **500 characters** each. Check whether the second string is a **prefix** of the first.

- If it **is** a prefix, say so.
- If it is **not**, print the **index in the second string** where the mismatch happens.

**Sample runs**

| String 1 | String 2 | Output |
|---|---|---|
| `mastery` | `master` | `master is a prefix of mastery.` |
| `mastery` | `mastery` | `mastery is a prefix of mastery.` |
| `master` | `mastery` | `mastery is not a prefix of master because of index 6.` |
| `excellence` | `exert` | `exert is not a prefix of excellence because of index 2.` |

**Approach:** loop over every index of string 2. Stop at the first index where string 1 has already ended (`i >= len1`) or the characters differ (`st2[i] != st1[i]`). If the loop finishes without stopping, string 2 is a prefix.

### isHexadecimal · `hexadecimal.c`

Ask for a string that can hold up to **100 actual characters**.

- If every character is a hexadecimal digit (`0`–`9`, `A`–`F`, uppercase only), print the **length** of the string.
- Otherwise, print the **position of the first invalid character**.

**Sample runs**

| Input | Output | Why |
|---|---|---|
| `234ABF0` | `7` | All valid, so the length is printed |
| `FFB$23` | `3` | `$` is at index 3 |
| `ACZFFR01` | `2` | `Z` is at index 2 |

**Approach:** walk the string until `'\0'`. The first character outside `'0'..'9'` and `'A'..'F'` ends the loop early and its index is printed. If the loop reaches the end, the loop counter `i` already equals the length.

> **Note on buffer sizes:** "100 actual characters" needs `char str[101]`, and "500 characters" needs `char st[501]`. The extra slot holds the `'\0'` terminator (see [section 1](#1-what-a-string-is)).

---

## Strings in C

### 1. What a string is

C has no built-in string type. A **string is an array of `char` that ends with the null character `'\0'`** (ASCII value 0). Every string function relies on that terminator to know where the string stops.

```c
char word[] = "cat";
```

| Index | 0 | 1 | 2 | 3 |
|---|---|---|---|---|
| Value | `'c'` | `'a'` | `'t'` | `'\0'` |

So `"cat"` has a **length of 3** but takes **4 bytes**. Always give your array **one more slot than the longest string** you plan to store.

`'a'` (single quotes) is one `char`. `"a"` (double quotes) is a string made of two bytes: `'a'` and `'\0'`.

### 2. Declaring and initializing

```c
char a[20];                         // uninitialized: holds garbage, not a valid string yet
char b[20] = "hello";               // 'h','e','l','l','o','\0', and the rest filled with '\0'
char c[]   = "hello";               // size is computed for you: 6
char d[6]  = {'h','e','l','l','o','\0'};  // same as c, written out character by character
char e[5]  = "hello";               // compiles, but there is NO room for '\0', so it is not a string
```

You **cannot assign** to an array after it is declared:

```c
char name[20];
name = "Dexter";          // error: arrays are not assignable
strcpy(name, "Dexter");   // correct
```

### 3. Arrays vs. pointers vs. literals

```c
char arr[] = "hello";   // a modifiable copy that lives in the array
char *ptr  = "hello";   // points at a string literal stored in read-only memory
```

| | `char arr[] = "hello";` | `char *ptr = "hello";` |
|---|---|---|
| Can modify characters? | Yes: `arr[0] = 'H';` | **No.** This is undefined behavior and usually crashes |
| `sizeof` | 6 (whole array) | 4 or 8 (size of a pointer) |
| Can point elsewhere? | No | Yes: `ptr = "bye";` |

Use `const char *ptr = "hello";` so the compiler stops you from modifying a literal by accident.

When an array is passed to a function or used in most expressions, it **decays** into a pointer to its first element. That is why `char s[]` and `char *s` mean the same thing as function parameters.

### 4. Reading strings

#### `scanf("%s", ...)`: one word

```c
char word[51];
scanf("%50s", word);   // no & needed: word already acts as an address
```

- Stops at the first **whitespace** (space, tab, newline), so `"hello world"` reads only `"hello"`.
- Always give a **width** (`%50s` for a 51-slot array). Without one, long input overflows the array.

#### `fgets`: a whole line, safely

```c
char line[101];
fgets(line, sizeof line, stdin);   // reads at most 100 characters + '\0'
line[strcspn(line, "\n")] = '\0';  // remove the trailing newline fgets keeps
```

- Reads spaces too and stops at a newline or when the buffer is full.
- **Keeps the `'\n'`** if it fits, so strip it as shown.
- Returns `NULL` on end-of-file or error.

#### `scanf("%[^\n]", ...)`: a line without the newline

```c
scanf(" %100[^\n]", line);   // leading space skips leftover whitespace
```

#### Never use `gets`

`gets` has no size limit and was removed from the C standard in C11. Use `fgets`.

#### Mixing `scanf` and `fgets`

`scanf("%d", &n)` leaves the `'\n'` in the input. A following `fgets` reads that empty line immediately. Clear the leftover first:

```c
scanf("%d", &n);
while (getchar() != '\n');   // discard the rest of the line
fgets(line, sizeof line, stdin);
```

### 5. Printing strings

```c
printf("%s\n", name);      // print the whole string
puts(name);                // same, adds '\n' automatically
printf("%10s|\n", name);   // right-aligned in a 10-character field
printf("%-10s|\n", name);  // left-aligned
printf("%.3s\n", name);    // only the first 3 characters
printf("%c\n", name[0]);   // a single character
```

Passing a char array **without** a `'\0'` to `%s` makes `printf` keep reading past the end of the array.

### 6. Walking through a string

Loop until you hit `'\0'`. You don't need the length first.

```c
for (int i = 0; s[i] != '\0'; i++) {
    // s[i] is the current character
}
```

When the loop ends, `i` equals the length. `hexadecimal.c` uses this to print the length without calling `strlen`.

Avoid calling `strlen` in the loop condition (`i < strlen(s)`): it scans the whole string again on every iteration. Store it once:

```c
int len = strlen(s);
for (int i = 0; i < len; i++) { ... }
```

Characters are small integers, so you can do arithmetic on them:

```c
'7' - '0'     // 7: digit character to its number
'C' - 'A'     // 2: position in the alphabet
'a' - 'A'     // 32: the gap between lowercase and uppercase in ASCII
```

### 7. `<string.h>` functions

`#include <string.h>`

#### Length

| Function | Does | Notes |
|---|---|---|
| `strlen(s)` | Number of characters before `'\0'` | Returns `size_t`. Not the same as `sizeof` |

```c
char s[50] = "hi";
strlen(s);   // 2
sizeof s;    // 50
```

#### Copying

| Function | Does | Notes |
|---|---|---|
| `strcpy(dest, src)` | Copies `src` into `dest`, including `'\0'` | `dest` must be large enough |
| `strncpy(dest, src, n)` | Copies at most `n` characters | Does **not** add `'\0'` if `src` has `n` or more characters |

```c
strncpy(dest, src, sizeof dest - 1);
dest[sizeof dest - 1] = '\0';   // always terminate yourself
```

#### Joining (concatenation)

| Function | Does | Notes |
|---|---|---|
| `strcat(dest, src)` | Appends `src` to the end of `dest` | `dest` must already be a valid string with room left |
| `strncat(dest, src, n)` | Appends at most `n` characters, always adds `'\0'` | Room needed: `strlen(dest) + n + 1` |

```c
char full[50] = "Hello";
strcat(full, ", ");
strcat(full, "world");   // "Hello, world"
```

#### Comparing

| Function | Returns |
|---|---|
| `strcmp(a, b)` | `0` if equal, `< 0` if `a` comes first, `> 0` if `b` comes first |
| `strncmp(a, b, n)` | Same, but only compares the first `n` characters |

Comparison is by ASCII value, so `"Zebra"` comes before `"apple"` (uppercase letters have smaller codes).

```c
if (strcmp(a, b) == 0) { /* equal */ }
if (strncmp(s, "pre", 3) == 0) { /* s starts with "pre" */ }
```

`a == b` compares **addresses**, not contents. It is almost always wrong for strings.

#### Searching

| Function | Returns |
|---|---|
| `strchr(s, c)` | Pointer to the first `c` in `s`, or `NULL` |
| `strrchr(s, c)` | Pointer to the last `c` in `s`, or `NULL` |
| `strstr(s, sub)` | Pointer to the first occurrence of `sub`, or `NULL` |
| `strcspn(s, set)` | Index of the first character in `s` that is in `set` (or the length if none) |
| `strspn(s, set)` | Length of the starting run of `s` made only of characters in `set` |

Turn a returned pointer into an index by subtracting the start:

```c
char *p = strchr(s, '@');
if (p != NULL) {
    int index = p - s;
}
```

`strspn` solves isHexadecimal in one line:

```c
int pos = strspn(str, "0123456789ABCDEF");   // first invalid index, or the length if all valid
```

#### Splitting (tokenizing)

```c
char text[] = "red,green,blue";
char *tok = strtok(text, ",");
while (tok != NULL) {
    printf("%s\n", tok);
    tok = strtok(NULL, ",");   // NULL means "continue the same string"
}
```

`strtok` **modifies** the string (it writes `'\0'` over each delimiter), so never call it on a string literal.

#### Memory functions

| Function | Does |
|---|---|
| `memset(s, c, n)` | Sets the first `n` bytes to `c` (e.g. `memset(s, 0, sizeof s)`) |
| `memcpy(dest, src, n)` | Copies exactly `n` bytes. Regions must not overlap |
| `memmove(dest, src, n)` | Like `memcpy`, but safe when regions overlap |
| `memcmp(a, b, n)` | Compares `n` bytes, does not stop at `'\0'` |

### 8. `<ctype.h>` character functions

`#include <ctype.h>`. These take one character and work on `int`.

| Test | True for | | Convert | Result |
|---|---|---|---|---|
| `isalpha(c)` | letters | | `toupper(c)` | uppercase version, or `c` unchanged |
| `isdigit(c)` | `0`–`9` | | `tolower(c)` | lowercase version, or `c` unchanged |
| `isxdigit(c)` | `0`–`9`, `a`–`f`, `A`–`F` | | | |
| `isalnum(c)` | letters or digits | | | |
| `isspace(c)` | space, `\t`, `\n`, `\r`, `\v`, `\f` | | | |
| `isupper(c)` / `islower(c)` | upper/lowercase letters | | | |
| `ispunct(c)` | punctuation | | | |

```c
for (int i = 0; s[i] != '\0'; i++)
    s[i] = toupper((unsigned char) s[i]);   // whole string to uppercase
```

The `(unsigned char)` cast avoids undefined behavior for characters with negative values.

`isxdigit` accepts lowercase `a`–`f`, so it would be **too lenient** for isHexadecimal, which allows only uppercase.

### 9. Converting between strings and numbers

#### String to number

| Function | Example | Notes |
|---|---|---|
| `atoi(s)` | `atoi("42")` → `42` | `<stdlib.h>`. No error checking: `atoi("abc")` is `0` |
| `atof(s)` | `atof("3.14")` → `3.14` | `<stdlib.h>` |
| `strtol(s, &end, base)` | `strtol("1F", &end, 16)` → `31` | `<stdlib.h>`. `end` points at the first character not used |
| `sscanf(s, fmt, ...)` | `sscanf("7 8", "%d %d", &a, &b)` | Returns how many values it read |

Converting by hand, which is the core of many machine problems:

```c
int value = 0;
for (int i = 0; s[i] != '\0'; i++)
    value = value * 10 + (s[i] - '0');          // decimal "123" -> 123

int hex = 0;
for (int i = 0; s[i] != '\0'; i++) {
    int digit = isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
    hex = hex * 16 + digit;                      // hex "1F" -> 31
}
```

#### Number to string

```c
char buf[32];
sprintf(buf, "%d", 123);                 // "123"
snprintf(buf, sizeof buf, "%.2f", 3.14159);  // "3.14", and never overflows buf
```

Prefer `snprintf`, which takes the buffer size.

### 10. Arrays of strings

A 2D `char` array holds several strings of fixed maximum length:

```c
char names[3][20] = {"Ana", "Ben", "Cara"};   // 3 strings, each up to 19 characters

for (int i = 0; i < 3; i++)
    printf("%s\n", names[i]);

scanf("%19s", names[1]);   // names[i] is itself a string
names[0][0] = 'E';         // a single character: "Ena"
```

An array of pointers to literals is lighter, but the strings are read-only:

```c
const char *days[] = {"Mon", "Tue", "Wed"};
```

### 11. Passing strings to functions

The function receives a pointer, so it **can modify** the caller's array, and it **cannot know the array size**. Pass the size if the function writes into the buffer.

```c
int countVowels(const char s[]) {          // const: promises not to modify
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
        if (strchr("aeiouAEIOU", s[i]))
            count++;
    return count;
}

void toUpper(char s[]) {                   // modifies the caller's string
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = toupper((unsigned char) s[i]);
}
```

**Never return a local array.** It is destroyed when the function returns:

```c
char *bad(void) {
    char s[20] = "oops";
    return s;              // dangling pointer: undefined behavior
}
```

Instead, have the caller pass in the buffer to fill.

### 12. Common patterns

**Reverse in place**

```c
int len = strlen(s);
for (int i = 0, j = len - 1; i < j; i++, j--) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}
```

**Palindrome check**

```c
int isPalindrome(const char s[]) {
    int i = 0, j = strlen(s) - 1;
    while (i < j)
        if (s[i++] != s[j--])
            return 0;
    return 1;
}
```

**Prefix check**, the library version of `prefix.c`

```c
int isPrefix(const char s[], const char pre[]) {
    return strncmp(s, pre, strlen(pre)) == 0;
}
```

**Suffix check**

```c
int isSuffix(const char s[], const char suf[]) {
    int ls = strlen(s), lf = strlen(suf);
    return lf <= ls && strcmp(s + ls - lf, suf) == 0;
}
```

**Count occurrences of a character**

```c
int count = 0;
for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == target)
        count++;
```

**Remove a character** (two indexes: read and write)

```c
int w = 0;
for (int r = 0; s[r] != '\0'; r++)
    if (s[r] != ' ')
        s[w++] = s[r];
s[w] = '\0';
```

**Count words**

```c
int words = 0, inWord = 0;
for (int i = 0; s[i] != '\0'; i++) {
    if (isspace((unsigned char) s[i]))
        inWord = 0;
    else if (!inWord) {
        inWord = 1;
        words++;
    }
}
```

### 13. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Array exactly as big as the text (`char s[5] = "hello"`) | No `'\0'`, so functions read past the end | Size it `length + 1` |
| `scanf("%s", s)` with no width | Long input overflows the array | `scanf("%99s", s)` for `char s[100]` |
| `scanf("%s", &s)` | Wrong type (pointer to array); works by accident | `scanf("%s", s)` |
| `if (a == b)` for strings | Compares addresses | `strcmp(a, b) == 0` |
| `s = "text";` on an array | Compile error | `strcpy(s, "text");` |
| Modifying a string literal through `char *` | Crash or undefined behavior | Use `char s[] = "..."` |
| `strncpy` with a long source | Result has no `'\0'` | Terminate manually |
| `strcat` onto an uninitialized array | Searches garbage for `'\0'` | Start with `char s[50] = "";` |
| Forgetting `fgets` keeps `'\n'` | Comparisons fail, output has extra lines | `s[strcspn(s, "\n")] = '\0';` |
| `sizeof s` on a function parameter | Gives pointer size, not array size | Pass the size as another parameter |
| Returning a local array | Dangling pointer | Let the caller provide the buffer |

---

## Quick Reference

```c
#include <stdio.h>    // printf, scanf, fgets, puts, sprintf, snprintf, sscanf
#include <string.h>   // strlen, strcpy, strcat, strcmp, strchr, strstr, strspn, strtok
#include <ctype.h>    // isalpha, isdigit, isxdigit, isspace, toupper, tolower
#include <stdlib.h>   // atoi, atof, strtol
```

| I want to... | Use |
|---|---|
| Get the length | `strlen(s)` |
| Copy | `strcpy(dest, src)` |
| Join | `strcat(dest, src)` |
| Check if equal | `strcmp(a, b) == 0` |
| Check a prefix | `strncmp(s, pre, strlen(pre)) == 0` |
| Find a character | `strchr(s, c)` |
| Find a substring | `strstr(s, sub)` |
| Read a word | `scanf("%99s", s)` |
| Read a line | `fgets(s, sizeof s, stdin)` |
| Convert to a number | `atoi(s)` or `strtol(s, &end, base)` |
| Convert from a number | `snprintf(buf, sizeof buf, "%d", n)` |
| Change case | `toupper(c)` / `tolower(c)` per character |
