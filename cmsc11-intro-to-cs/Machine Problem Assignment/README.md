# Machine Problem Assignment: Flame it on the Gene

CMSC 11 machine problem assignment that combines everything so far (selection, loops, nested loops, arrays and strings) into two tasks: the **FLAMES** game and finding **"gene sequences"** in a sample **"genome"**.

## Contents

- [Files](#files)
- [Problem Statement](#problem-statement)
  - [Input](#input)
  - [Option 1: FLAMES](#option-1-flames)
  - [Option 2: Gene Sequences](#option-2-gene-sequences)
  - [Sample](#sample)
- [Solution Walkthrough](#solution-walkthrough)
  - [Reading the input](#reading-the-input)
  - [FLAMES: cancelling letters](#flames-cancelling-letters)
  - [FLAMES: from count to result](#flames-from-count-to-result)
  - [Genes: substring search](#genes-substring-search)
- [Concepts Used](#concepts-used)
  1. [Mixing `scanf` and `fgets`](#1-mixing-scanf-and-fgets)
  2. [Case-insensitive comparison](#2-case-insensitive-comparison)
  3. [Marking characters as used](#3-marking-characters-as-used)
  4. [Cycling with `%`](#4-cycling-with-)
  5. [Mapping numbers to messages](#5-mapping-numbers-to-messages)
  6. [Substring search and overlapping matches](#6-substring-search-and-overlapping-matches)
  7. [Storing results in an array](#7-storing-results-in-an-array)
  8. [Exact output matching](#8-exact-output-matching)
- [Testing Checklist](#testing-checklist)

---

## Files

| File | Description |
|---|---|
| [flamesAndGenes.c](flamesAndGenes.c) | Full solution: reads `t` test cases and runs FLAMES (option 1) or gene search (option 2) for each |

---

## Problem Statement

### Input

1. The first line contains the number of test cases, `n`.
2. Each test case has **three lines**:
   - A number: `1` for FLAMES, `2` for gene sequences.
   - **Option 1:** the names of the two people, one per line.
   - **Option 2:** a longer string (the genome), then a shorter string (the sequence to find).

### Option 1: FLAMES

Simulate the game **FLAMES**: **F**riends, **L**overs, **A**cceptance, **M**arriage, **E**ngagement and **S**weethearts.

Display the result for the first person, then the result for the second person, and finally the overall result.

**Counting rules**

- The count is the number of **similar letters**, meaning the letters cancelled out because they appear in both names.
- Uppercase and lowercase are the same: `'A'` matches `'a'`.
- Spaces are not counted.

**Example:** `Sam Milby` and `Piolo Pascual`

| Name | Letters cancelled | Count | Result |
|---|---|---|---|
| Sam Milby | s, a, i, l | 4 | MARRIED |
| Piolo Pascual | i, l, l, a, a, s | 6 | SWEETHEARTS |
| Total | | 10 | MARRIED couple |

> Sam Milby wants to be MARRIED to Piolo Pascual.
> Piolo Pascual wants to be SWEETHEARTS with Sam Milby.
> They will end up as a MARRIED couple.

**Output messages**

| Count | Letter | Per person | Overall |
|---|---|---|---|
| 1 | **F** | `... wants to be FRIENDS with ...` | `They will end up as FRIENDS.` |
| 2 | **L** | `... wants to be LOVERS with ...` | `They will end up as LOVERS.` |
| 3 | **A** | `... wants to ACCEPT their fate with ...` | `They will ACCEPT their fate, whatever it is.` |
| 4 | **M** | `... wants to be MARRIED to ...` | `They will end up as a MARRIED couple.` |
| 5 | **E** | `... wants to be ENGAGED to ...` | `They will be ENGAGED.` |
| 6 | **S** | `... wants to be SWEETHEARTS with ...` | `They will end up as SWEETHEARTS.` |

Counts above 6 wrap around: 7 is F again, 10 is M, 12 is S ([how](#4-cycling-with-)).

### Option 2: Gene Sequences

The human genome has about 3 billion DNA base pairs built from 4 bases: **A**denine, **G**uanine, **C**ytosine and **T**hymine. A stretch of it looks like `AGCTCTAGAGCTCTCTAGAGAGCT`, but much longer.

Check whether the **shorter string** occurs in the **longer string**. If it does, print:

1. `YES`
2. How many times it occurs.
3. The (0-based) indices where each occurrence starts.

If it does not occur, print `NO`.

**Example:** finding `CT` in `AGCTCTAGAGCTCTCTAGAGAGCT`

```
Index:  0         1         2
        012345678901234567890123
        AGCTCTAGAGCTCTCTAGAGAGCT
          ^ ^     ^ ^ ^       ^
```

`CT` occurs **6** times, at indices **2, 4, 10, 12, 14, 22**.

### Sample

**Input**

```
3
1
Ryan Agoncillo
Judy Ann Santos
2
AGCTCTAGAGCTCTCTAGAGAGCT
AGAG
2
AGCTCTAGAGCTCTCTAGAGAGCT
CTAGCTAG
```

**Output**

```
Ryan Agoncillo wants to be FRIENDS with Judy Ann Santos.
Judy Ann Santos wants to be FRIENDS with Ryan Agoncillo.
They will end up as LOVERS.
YES
3
6 16 18
NO
```

**Why:**

- **Ryan Agoncillo / Judy Ann Santos.** The shared letters are `y`, `a`, `n` and `o`.
  - Ryan Agoncillo has 1 y + 2 a + 2 n + 2 o = **7** of them, which is FRIENDS.
  - Judy Ann Santos has 1 y + 2 a + 3 n + 1 o = **7** of them, which is FRIENDS.
  - The total is 14, which wraps around to LOVERS.
- **AGAG** starts at indices 6, 16 and 18. The matches at 16 and 18 **overlap** (`AGAGAG`), and both count.
- **CTAGCTAG** never appears, so the output is `NO`.

---

## Solution Walkthrough

### Reading the input

```c
scanf("%d", &t);
getchar();                       // eat the '\n' left by scanf

for (int u = 0; u < t; u++) {
    scanf("%d", &Dashin);
    getchar();
    if (Dashin == 1) { /* FLAMES */ }
    else if (Dashin == 2) { /* genes */ }
}
```

Names contain spaces, so they are read with `fgets` (a whole line), not `scanf("%s")` (one word). The trailing newline that `fgets` keeps is removed with `strcspn` ([details](#1-mixing-scanf-and-fgets)).

### FLAMES: cancelling letters

1. **Keep a copy** of both names (`ft_a`, `ft_b`) for printing, because the working copies get modified.
2. For each letter in name A (skipping spaces and letters already cancelled):
   - Look for the same letter, in lowercase, anywhere in name B.
   - If found, replace **every** occurrence of that letter in **both** names with a marker `'&'`.
3. Count the `'&'` characters in each name. These are the per-person counts.
4. The total is the sum of both counts.

Replacing every occurrence at once is what makes `Piolo Pascual` count **both** `l`s and **both** `a`s.

Tracing `Sam Milby` and `Piolo Pascual`:

| Letter from A | In B? | Name A after | Name B after |
|---|---|---|---|
| `s` | yes | `&am Milby` | `Piolo Pa&cual` |
| `a` | yes | `&&m Milby` | `Piolo P&&cu&l` |
| `m` | no | – | – |
| `M` → `m` | no | – | – |
| `i` | yes | `&&m M&lby` | `P&olo P&&cu&l` |
| `l` | yes | `&&m M&&by` | `P&o&o P&&cu&&` |
| `b`, `y` | no | – | – |

Name A has **4** `'&'`, name B has **6**, and the total is **10**.

The solution also handles a total of **0** (no letters in common) with its own message, which the problem statement does not cover.

### FLAMES: from count to result

```c
int result = count % 6;
if (result == 0) result = 6;     // multiples of 6 land on S
```

Then a `switch` (per person) and an `else if` chain (overall) print the matching message from [the table above](#option-1-flames).

### Genes: substring search

A nested loop tries every starting position in the long string:

```c
int len1 = strlen(gene_1), len2 = strlen(gene_2);
for (int i = 0; i <= len1 - len2; i++) {          // every possible start
    int match = 1;
    for (int j = 0; j < len2; j++) {              // compare character by character
        if (gene_1[i + j] != gene_2[j]) {
            match = 0;
            break;
        }
    }
    if (match)
        index[count++] = i;                       // remember where it starts
}
```

- The outer loop stops at `len1 - len2`. Starting any later, the short string would run past the end.
- The outer loop moves forward by **1**, not by `len2`, so **overlapping** matches are found.
- The indices go into an array, so the count can be printed **before** the list of indices.

---

## Concepts Used

This assignment builds on every earlier topic:

| Topic | Used for |
|---|---|
| [01 - Selection and Branching](../01%20-%20Selection%20and%20Branching%20using%20C/) | Choosing the option, mapping counts to messages |
| [02 - Iterations](../02%20-%20Iterations%20in%20C/) | The test-case loop, counting |
| [03 - Strings](../03%20-%20Strings/) | `fgets`, `strlen`, `strcpy`, `strcspn`, `tolower` |
| [04 - Nested Loops](../04%20-%20Nested%20Loops/) | Comparing every letter with every letter, substring search |
| [05 - Arrays](../05%20-%20Arrays/) | Storing match indices |

### 1. Mixing `scanf` and `fgets`

`scanf("%d", &x)` reads the number but leaves the `'\n'` after it in the input. A following `fgets` would read that empty line instead of the name.

```c
scanf("%d", &option);
getchar();                               // consume the leftover '\n'
fgets(name, sizeof name, stdin);
name[strcspn(name, "\n")] = '\0';        // remove the '\n' that fgets keeps
```

`getchar()` removes exactly one character. If the input might contain trailing spaces after the number, this skips the rest of the line instead:

```c
while (getchar() != '\n');
```

On Windows, lines can end with `"\r\n"`. To strip both characters, use `strcspn(name, "\r\n")`.

### 2. Case-insensitive comparison

`tolower` (from `<ctype.h>`) turns `'A'`–`'Z'` into `'a'`–`'z'` and leaves everything else unchanged. Compare the lowercase versions:

```c
if (tolower(a[i]) == tolower(b[j]))
```

### 3. Marking characters as used

To "cancel" a character without deleting it from the array (which would mean shifting everything after it), overwrite it with a marker that can't appear in a name:

```c
name[k] = '&';
```

Then skip markers in later passes and count them at the end. Keep an untouched copy (`strcpy`) if you still need the original for printing.

### 4. Cycling with `%`

FLAMES counts around a circle of 6 letters. `count % 6` gives a value from 0 to 5. Since the letters are numbered 1 to 6, a remainder of 0 means the count landed exactly on the 6th letter:

| Count | `count % 6` | Letter |
|---|---|---|
| 1 | 1 | F |
| 4 | 4 | M |
| 6 | 0 → 6 | S |
| 7 | 1 | F |
| 10 | 4 | M |
| 14 | 2 | L |

The same idea in one line: `((count - 1) % 6) + 1`. With a string, `"FLAMES"[(count - 1) % 6]` gives the letter directly.

### 5. Mapping numbers to messages

A `switch` on the result keeps each message on its own line. An array of strings removes the branching entirely:

```c
const char *personMsg[] = {
    "", "be FRIENDS with", "be LOVERS with", "ACCEPT their fate with",
    "be MARRIED to", "be ENGAGED to", "be SWEETHEARTS with"
};
printf("%s wants to %s %s.\n", nameA, personMsg[result], nameB);
```

Index 0 is left empty so `result` (1–6) can be used directly.

### 6. Substring search and overlapping matches

The nested-loop search above is the **naive** (brute-force) algorithm. For a long string of length `n` and a pattern of length `m`, it does at most about `n × m` character comparisons.

`strstr` from `<string.h>` does the same search. Advance by **1** past each match to also find overlapping ones:

```c
char *p = genome;
while ((p = strstr(p, pattern)) != NULL) {
    printf("%d ", (int)(p - genome));    // pointer difference = index
    p++;                                 // p += strlen(pattern) would skip overlaps
}
```

| Advance by | `AGAG` in `...AGAGAG...` finds |
|---|---|
| 1 | indices 16 **and** 18 (overlapping) |
| pattern length | index 16 only |

The problem's expected output (`6 16 18`) requires advancing by 1.

### 7. Storing results in an array

The output prints the **count before the indices**, but you only know the count after the search is done. So either:

- store each index in an array while searching, then print the count and the array, **or**
- search twice: once to count, once to print.

The array needs room for the worst case: a one-character pattern can match at every position, so its capacity should be at least the length of the long string.

### 8. Exact output matching

Machine problems are usually checked by comparing your output with the expected output **character by character**. Watch for:

- **Exact wording.** `MARRIED to`, not `MARRIED with`. `wants to ACCEPT`, not `wants to be ACCEPT`.
- **Trailing spaces** at the end of a line, such as after the last index. Some checkers ignore them, some don't.
- **Missing or extra newlines**, especially after the last line.
- **Upper and lower case.** `YES`, not `Yes`.

Printing a separator only **between** items avoids trailing spaces:

```c
for (int k = 0; k < count; k++)
    printf(k == 0 ? "%d" : " %d", index[k]);
printf("\n");
```

---

## Testing Checklist

| Case | Input | Expected |
|---|---|---|
| Sample FLAMES | `Ryan Agoncillo` / `Judy Ann Santos` | FRIENDS, FRIENDS, LOVERS |
| Spec FLAMES | `Sam Milby` / `Piolo Pascual` | MARRIED **to**, SWEETHEARTS **with**, MARRIED couple |
| Mixed case | `ANNA` / `anna` | All letters cancel: 4 and 4, total 8 |
| No shared letters | `Bob` / `Kim` | Total 0 (not covered by the spec) |
| Overlapping genes | `AGCTCTAGAGCTCTCTAGAGAGCT` / `AGAG` | `YES`, `3`, `6 16 18` |
| Many matches | `AGCTCTAGAGCTCTCTAGAGAGCT` / `CT` | `YES`, `6`, `2 4 10 12 14 22` |
| No match | `AGCTCTAGAGCTCTCTAGAGAGCT` / `CTAGCTAG` | `NO` |
| Match at index 0 and at the end | `ACGTAC` / `AC` | `YES`, `2`, `0 4` |
| Pattern longer than genome | `ACG` / `ACGTT` | `NO` |
