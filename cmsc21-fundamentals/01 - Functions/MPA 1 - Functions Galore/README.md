# MPA 1: Functions Galore

CMSC 21 machine problem assignment on **writing your own functions**. Twenty small tasks: rebuild common library functions (`floor`, `isalpha`, `toupper`, `atoi`, `strcpy`, `strcmp`, ...) from scratch, with **no library functions except `scanf` and `printf`**.

## Contents

- [Rules](#rules)
- [Input](#input)
- [Output](#output)
  - [Numbers (items 1–3, 14, 20)](#numbers-items-13-14-20)
  - [Characters (items 4–10)](#characters-items-410)
  - [Strings (items 11–13, 15–19)](#strings-items-1113-1519)
- [Sample](#sample)
- [Suggested Function Signatures](#suggested-function-signatures)
- [Approach per Item](#approach-per-item)
- [Edge Cases to Decide](#edge-cases-to-decide)
- [Testing Checklist](#testing-checklist)
- [Honor Code](#honor-code)

---

## Rules

- **One function per item.** Each item has its own function, and `main` calls it.
- **No library functions** except `scanf` and `printf`. No `strlen`, `strcpy`, `toupper`, `floor`, `pow`, `atoi`, and so on. You may call **your own** functions, including helper functions you write.
- **No printing inside the item functions.** They return (or fill in) a result. All input and output happens in `main`.

---

## Input

1. The first line is the number of test cases.
2. Each test case starts with the **item number** (1–20), followed by that item's input:

| Items | Input |
|---|---|
| 1, 14, 20 | an integer |
| 2, 3 | a `double` |
| 4–10 | a character |
| 11–13, 18, 19 | a string |
| 15, 16, 17 | two strings |

Strings contain **no spaces** and are **at most 50 characters** long, so `char s[51]` and `scanf("%50s", s)` are enough.

> The original statement lists two strings for "items 15 and 17", but item 16 (substring) also takes two strings.

---

## Output

### Numbers (items 1–3, 14, 20)

| # | Task | Examples |
|---|---|---|
| 1 | **Integer log base 10**: the integer part of log₁₀ n | `1000` → `3`, `850` → `2`, `1000000` → `6`, `123456` → `5` |
| 2 | **Floor** of a `double` | `12` → `12`, `12.3` → `12`, `12.9` → `12` |
| 3 | **Ceiling** of a `double` | `12` → `12`, `12.3` → `13`, `12.9` → `13` |
| 14 | **Absolute value** of an integer | `-7` → `7`, `7` → `7` |
| 20 | **Reverse an integer**, without using strings | `102` → `201`, `5300` → `35` |

### Characters (items 4–10)

| # | Task | Output | Examples |
|---|---|---|---|
| 4 | Is it **alphanumeric**? (`0`–`9`, `a`–`z`, `A`–`Z`) | `YES` / `NO` | `7` → `YES`, `#` → `NO` |
| 5 | Is it a **letter**? (`a`–`z`, `A`–`Z`) | `YES` / `NO` | `q` → `YES`, `7` → `NO` |
| 6 | Is it **uppercase**? (`A`–`Z`) | `YES` / `NO` | `Q` → `YES`, `q` → `NO` |
| 7 | Is it **lowercase**? (`a`–`z`) | `YES` / `NO` | `q` → `YES`, `Q` → `NO` |
| 8 | **To uppercase** if lowercase, else unchanged | the character | `q` → `Q`, `5` → `5` |
| 9 | **To lowercase** if uppercase, else unchanged | the character | `Q` → `q`, `5` → `5` |
| 10 | Is it **punctuation**? Only `.` `?` `!` `,` `;` `:` count | `YES` / `NO` | `?` → `YES`, `-` → `NO` |

### Strings (items 11–13, 15–19)

| # | Task | Output | Examples |
|---|---|---|---|
| 11 | **String to integer** (input is a valid integer) | the integer | `"1234"` → `1234` |
| 12 | **String to double** (at most 4 digits after the dot) | 4 decimal places | `"3.14"` → `3.1400`, `"25"` → `25.0000` |
| 13 | Is it a valid **float format**? | `YES` / `NO` | `"1.5678"` → `YES`, `"24"` → `YES`, `"0.5678"` → `YES`, `"1.25.78"` → `NO` |
| 15 | **Copy** the first string into the second | the destination string | `hello world` → `hello` |
| 16 | Is the first string a **substring** of the second? | `YES` / `NO` | `ell hello` → `YES`, `low hello` → `NO` |
| 17 | **Compare** two strings by ASCII order | `YES` if equal, else `BEFORE` / `AFTER` | `hello world` → `BEFORE`, `universe galaxy` → `AFTER`, `Zebra apple` → `BEFORE` |
| 18 | **"Camel case"**: alternate lower/upper, starting lowercase | the new string | `"HELLO"` → `"hElLo"` |
| 19 | **Reverse** the string | the reversed string | `"wonder"` → `"rednow"` |

**Item 15:** the second input string is the destination. It's read in first, then overwritten, so the output shows whether the copy really worked (including the `'\0'` at the end).

**Item 17:** `Zebra` comes **before** `apple` because uppercase letters have smaller ASCII codes (`'Z'` = 90, `'a'` = 97).

**Item 18:** this course's own definition of camel case, where every other character alternates: `wE aSsUmE tHaT tHe FiRsT cHaRaCtEr Of ThE sTrInG iS aLwAyS iN lOwEr CaSe`. The input contains letters only.

---

## Sample

**Input**

```
2
1 9
20 7
```

**Output**

```
0
7
```

- Item 1 with `9`: log₁₀ 9 ≈ 0.95, and its integer part is `0`.
- Item 20 with `7`: reversing a 1-digit number gives `7`.

---

## Suggested Function Signatures

Your names may differ. What matters is that each item has a function that returns its result instead of printing it.

```c
int    intLog10(int n);                       // 1
int    myFloor(double x);                     // 2
int    myCeil(double x);                      // 3
int    isAlnum(char c);                       // 4   returns 1 or 0
int    isAlpha(char c);                       // 5
int    isUpper(char c);                       // 6
int    isLower(char c);                       // 7
char   toUpper(char c);                       // 8
char   toLower(char c);                       // 9
int    isPunct(char c);                       // 10
int    strToInt(char s[]);                    // 11
double strToDouble(char s[]);                 // 12
int    isFloatFormat(char s[]);               // 13
int    absValue(int n);                       // 14
void   strCopy(char src[], char dest[]);      // 15  dest is filled in
int    isSubstring(char sub[], char s[]);     // 16
int    strCompare(char s1[], char s2[]);      // 17  0, negative or positive
void   camelCase(char s[]);                   // 18  changes s in place
void   reverseStr(char s[]);                  // 19  changes s in place
int    reverseInt(int n);                     // 20

int    strLength(char s[]);                   // helper used by several items
```

Functions that "return" a string can't return an array in C. Instead, they **modify the array passed in**, since arrays are passed by address.

`main` reads the item number and dispatches with a `switch`:

```c
switch (item) {
    case 1:  scanf("%d", &n);   printf("%d\n", intLog10(n)); break;
    case 4:  scanf(" %c", &c);  printf("%s\n", isAlnum(c) ? "YES" : "NO"); break;
    // ...
}
```

`" %c"` (with a space) skips the newline left over from the previous input. Without it, `%c` would read the `'\n'` instead of the character.

---

## Approach per Item

**1. Integer log₁₀:** count how many times you can divide by 10 before going below 10.

```c
int count = 0;
while (n >= 10) { n /= 10; count++; }
```

**2–3. Floor and ceiling:** casting to `int` **truncates toward zero**, which is the floor only for non-negative numbers.

| `x` | `(int) x` | floor | ceiling |
|---|---|---|---|
| 12.3 | 12 | 12 | 13 |
| 12.0 | 12 | 12 | 12 |
| −12.3 | −12 | −13 | −12 |

```c
int t = (int) x;
floor = (x < t) ? t - 1 : t;     // only negative non-integers need the -1
ceil  = (x > t) ? t + 1 : t;     // only positive non-integers need the +1
```

**4–7. Character tests:** compare against ranges. Build the bigger ones from the smaller ones:

```c
int isAlpha(char c) { return isUpper(c) || isLower(c); }
int isAlnum(char c) { return isAlpha(c) || (c >= '0' && c <= '9'); }
```

**8–9. Case conversion:** uppercase and lowercase letters are 32 apart in ASCII.

```c
char toUpper(char c) { return isLower(c) ? c - 'a' + 'A' : c; }
```

**10. Punctuation:** check the six allowed characters, `c == '.' || c == '?' || ...`.

**11. String to integer:** handle an optional leading `-`, then build the number digit by digit.

```c
value = value * 10 + (s[i] - '0');
```

**12. String to double:** build the integer part the same way. For the fraction, collect its digits **as an integer** and divide once at the end. This keeps the rounding error smaller than adding 0.1, 0.01, ... separately.

```
"3.1416" → whole = 3, frac = 1416, places = 4 → 3 + 1416 / 10000.0 = 3.1416
```

Print with `printf("%.4f\n", d)`.

**13. Float format:** walk the string and count. It's valid if every character is a digit or a dot, there's **at most one** dot, and there's at least one digit.

**14. Absolute value:** `n < 0 ? -n : n`.

**15. Copy:** copy characters until `'\0'`, then **copy the `'\0'` too**.

**16. Substring:** try every starting position in the longer string. At each one, compare character by character, the same nested loop as the gene search in CMSC 11's [Machine Problem Assignment](../../../cmsc11-intro-to-cs/Machine%20Problem%20Assignment/).

**17. Compare:** move forward while the characters are equal and not `'\0'`. The first difference decides the order. If one string runs out first, the shorter one comes **before** (`"app"` comes before `"apple"`, because `'\0'` < `'l'`).

```c
int i = 0;
while (s1[i] != '\0' && s1[i] == s2[i]) i++;
return s1[i] - s2[i];      // 0 = same, < 0 = BEFORE, > 0 = AFTER
```

**18. Camel case:** even index → lowercase, odd index → uppercase, using your own `toLower` / `toUpper`.

**19. Reverse string:** swap from both ends toward the middle, using your own `strLength`.

**20. Reverse integer:** build the reversed number from the last digit. Trailing zeros vanish on their own (`5300` → `35`).

```c
int rev = 0;
while (n > 0) { rev = rev * 10 + n % 10; n /= 10; }
```

---

## Edge Cases to Decide

The statement doesn't cover these. Pick a behavior and keep it consistent.

| Item | Case | Note |
|---|---|---|
| 1 | `n <= 0` | log₁₀ is undefined for 0 and negatives |
| 2, 3 | negative input | Truncation is wrong here; use the adjustment above |
| 11, 12 | leading `-` or `+` | "Correct integer format" may include a sign |
| 13 | `"-1.5"`, `".5"`, `"5."`, `"."` | Signs and a dot with no digits on one side aren't specified |
| 17 | one string is a prefix of the other | The shorter one is `BEFORE` |
| 20 | negative input | Reverse the absolute value and keep the sign: `-120` → `-21` |

---

## Testing Checklist

```
20
1 1000
1 9
2 12.9
3 12.3
4 #
5 7
6 Q
7 Q
8 q
9 5
10 ?
11 -1234
12 3.14
13 1.25.78
14 -7
15 hello world
16 ell hello
17 Zebra apple
18 HELLO
19 wonder
```

Expected:

```
3
0
12
13
NO
NO
YES
NO
Q
5
YES
-1234
3.1400
NO
7
hello
YES
BEFORE
hElLo
rednow
```

(The first line, `20`, is the number of test cases, and item 20 isn't included. Test it separately with `5300` → `35`.)

---

## Honor Code

Choose the appropriate declaration (or a combination) and write it as a comment in the first lines of the solution:

> I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

> I declare, upon my honor, that I did this machine problem assignment by myself using online resources from the following (please cite the online sources). Further, my solution is not a copy from the aforementioned sources.

> I declare, upon my honor, that I did this machine problem assignment as a collaboration with (enumerate your collaborators, maximum of 3 other collaborators). Further, my solution is not a copy of any of my collaborators' solutions.
