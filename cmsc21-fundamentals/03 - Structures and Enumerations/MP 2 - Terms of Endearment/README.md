# MP 2: Terms of Endearment

CMSC 21 machine problem on **structures**: read two algebraic terms like `4x^3`, store each in a `struct`, multiply them, and print the product in proper math notation.

## Contents

- [Problem](#problem)
  - [Requirements](#requirements)
  - [Input](#input)
  - [Output](#output)
- [Sample](#sample)
- [Multiplying Terms](#multiplying-terms)
- [Reading a Term](#reading-a-term)
  - [The shapes a term can take](#the-shapes-a-term-can-take)
  - [Parsing by finding `x`](#parsing-by-finding-x)
  - [Parsing with `strtok`](#parsing-with-strtok)
- [Displaying a Term](#displaying-a-term)
- [Suggested Structure and Functions](#suggested-structure-and-functions)
- [Edge Cases](#edge-cases)
- [Testing Checklist](#testing-checklist)

---

## Problem

### Requirements

- Implement a **term** as a **structure**. A term has a **coefficient**, an **exponent**, and an independent variable. The variable is always `x` in this MP, so storing it is optional.
- Write **at least two functions**:
  1. **Multiply:** takes **two term arguments** and **returns** their product (a term).
  2. **Display:** prints a term.
- To convert the input string to a term, you **may** use `atoi` and `strtok`, but you don't have to.

### Input

1. A positive integer `t`, the number of test cases.
2. `t` lines, each with **two terms** separated by a space.

Terms use `x` as the variable and `^` for the exponent: `4x^3` means 4x³.

### Output

For each test case, the **product** of the two terms on its own line. Watch the display rules: a coefficient of 1, an exponent of 1, an exponent of 0, and so on ([details](#displaying-a-term)).

---

## Sample

| Input | Math | Output |
|---|---|---|
| `x 4x^3` | x · 4x³ = 4x⁴ | `4x^4` |
| `45 2x^3` | 45 · 2x³ = 90x³ | `90x^3` |
| `x^9 5x` | x⁹ · 5x = 5x¹⁰ | `5x^10` |
| `2 x^3` | 2 · x³ = 2x³ | `2x^3` |
| `2 10` | 2 · 10 = 20 | `20` |

**Full input**

```
5
x 4x^3
45 2x^3
x^9 5x
2 x^3
2 10
```

**Full output**

```
4x^4
90x^3
5x^10
2x^3
20
```

---

## Multiplying Terms

Multiply the coefficients and **add** the exponents:

$$a x^m \cdot b x^n = (a \cdot b)\, x^{m+n}$$

```c
Term multiply(Term a, Term b) {
    Term product;
    product.coef = a.coef * b.coef;
    product.exp  = a.exp + b.exp;
    return product;
}
```

Structures are passed and returned **by value**, as copies. So `multiply` can take two terms and give back a third without pointers.

---

## Reading a Term

### The shapes a term can take

A missing coefficient means **1**. A missing `^` with an `x` present means exponent **1**. No `x` at all means exponent **0** (a constant).

| Input | Coefficient | Exponent | Why |
|---|---|---|---|
| `4x^3` | 4 | 3 | Both written |
| `x^9` | 1 | 9 | No coefficient, so 1 |
| `5x` | 5 | 1 | No `^`, so exponent 1 |
| `x` | 1 | 1 | Neither written |
| `45` | 45 | 0 | No `x`: a constant |
| `-x^2` | −1 | 2 | Only a sign, so −1 |
| `-3x` | −3 | 1 | |

### Parsing by finding `x`

The most reliable way: find where `x` is, then look at what's before and after it.

```
   coefficient   x   ^exponent
   └─ before ─┘     └─ after ─┘
```

```c
Term parse(char s[]) {
    Term t;
    int i = 0;
    while (s[i] != '\0' && s[i] != 'x') i++;   // find x

    if (s[i] == '\0') {                        // no x: constant
        t.coef = atoi(s);
        t.exp = 0;
        return t;
    }

    // coefficient: the text before x
    if (i == 0)                         t.coef = 1;     // "x..."
    else if (i == 1 && s[0] == '-')     t.coef = -1;    // "-x..."
    else if (i == 1 && s[0] == '+')     t.coef = 1;     // "+x..."
    else {
        s[i] = '\0';                    // cut the string at x
        t.coef = atoi(s);
        s[i] = 'x';                     // put it back
    }

    // exponent: the text after x
    if (s[i + 1] == '^')  t.exp = atoi(&s[i + 2]);
    else                  t.exp = 1;

    return t;
}
```

`atoi` (from `<stdlib.h>`) stops at the first non-digit. So `atoi("4x^3")` is already `4`, and cutting at `x` is only for clarity. `&s[i + 2]` is the address of the character after `^`, so `atoi` reads the exponent from there.

### Parsing with `strtok`

`strtok` (from `<string.h>`) splits a string into **tokens** wherever it finds any of the **delimiter characters**:

```c
char str[] = "Hello,Six,Seven,Tennis";
char *token = strtok(str, ",");      // first call: pass the string
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");       // later calls: pass NULL to continue
}
```

```
Hello
Six
Seven
Tennis
```

For terms, use `"x^"` as the delimiters, so `4x^3` splits into `4` and `3`.

**Be careful:** `strtok` **skips delimiters at the start** and never returns empty tokens. You can't tell the shapes apart from the tokens alone:

| Input | Tokens with `"x^"` | Problem |
|---|---|---|
| `4x^3` | `4`, `3` | fine |
| `x^9` | `9` | The first token is the **exponent**, not the coefficient |
| `5x` | `5` | Looks the same as the constant `5` |
| `x` | *(none)* | `strtok` returns `NULL` |

So with `strtok`, check **where `x` is** first (`s[0] == 'x'`, and whether `x` and `^` appear at all) before deciding what each token means.

Also:

- `strtok` **modifies** the string, writing `'\0'` over each delimiter. Copy it first if you still need the original.
- `strtok` keeps hidden state between calls, so finish splitting one string before starting on another.

---

## Displaying a Term

| Case | Rule | Product | Printed |
|---|---|---|---|
| Coefficient 0 | The whole term is 0 | 0x³ | `0` |
| Exponent 0 | Print only the coefficient | 20x⁰ | `20` |
| Coefficient 1 | Leave out the `1` | 1x⁴ | `x^4` |
| Coefficient −1 | Print only the `-` | −1x⁴ | `-x^4` |
| Exponent 1 | Leave out `^1` | 5x¹ | `5x` |
| Coefficient 1, exponent 1 | Both left out | 1x¹ | `x` |
| Coefficient 1, exponent 0 | The constant 1 must stay | 1x⁰ | `1` |
| General | | 90x³ | `90x^3` |

Check the cases **in this order**: zero coefficient, then zero exponent, then the coefficient, then the exponent.

```c
void display(Term t) {
    if (t.coef == 0 || t.exp == 0) {          // constant (or zero)
        printf("%d\n", t.exp == 0 ? t.coef : 0);
        return;
    }
    if (t.coef == -1)      printf("-");
    else if (t.coef != 1)  printf("%d", t.coef);
    printf("x");
    if (t.exp != 1)        printf("^%d", t.exp);
    printf("\n");
}
```

---

## Suggested Structure and Functions

```c
typedef struct {
    int coef;
    int exp;
    // char var;     optional: always 'x' in this MP
} Term;

Term parse(char s[]);               // string → Term (optional helper)
Term multiply(Term a, Term b);      // required: 2 term arguments, returns the product
void display(Term t);               // required

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        char s1[51], s2[51];
        scanf("%50s %50s", s1, s2);
        display(multiply(parse(s1), parse(s2)));
    }
    return 0;
}
```

`typedef struct { ... } Term;` lets you write `Term` instead of `struct Term` everywhere.

---

## Edge Cases

The statement only shows positive terms. Decide how to handle these:

| Case | Example | Expected |
|---|---|---|
| Negative coefficient | `-3x 2x` | `-6x^2` |
| Coefficient is only `-` | `-x x` | `-x^2` |
| Product coefficient −1 | `-x x^2` | `-x^3` |
| Zero coefficient | `0 5x^2` | `0` |
| Exponents add to 1 | `x 3` | `3x` |
| Product is the constant 1 | `1 1` | `1` |
| Negative exponent | `x^-2 x^5` | `x^3` (`atoi` handles the `-`) |
| Exponents cancel | `2x^-3 3x^3` | `6` |
| Large coefficients | `100000 100000` | 10¹⁰ overflows `int`. Use `long long` if inputs can be that big |

---

## Testing Checklist

```
12
x 4x^3
45 2x^3
x^9 5x
2 x^3
2 10
x x
1 1
-x x
-3x 2x
0 5x^2
x 3
2x^-3 3x^3
```

Expected:

```
4x^4
90x^3
5x^10
2x^3
20
x^2
1
-x^2
-6x^2
0
3x
6
```
