# MP 10: The Polynomial has many Faces

CMSC 21 machine problem on **linked lists**: store a polynomial as a linked list of terms, then **simplify**, **add**, **subtract** and **multiply** polynomials, printing each result in standard form.

It builds on [MP 2: Terms of Endearment](../../03%20-%20Structures%20and%20Enumerations/MP%202%20-%20Terms%20of%20Endearment/), which multiplied single terms. Here a polynomial is a whole **list** of terms.

## Contents

- [Problem](#problem)
  - [Input](#input)
  - [Output](#output)
- [Sample](#sample)
- [Sample Walkthrough](#sample-walkthrough)
- [Problem with the Sample: Line 1](#problem-with-the-sample-line-1)
- [Why a Linked List](#why-a-linked-list)
- [Approach](#approach)
  - [The structures](#the-structures)
  - [Reading a polynomial](#reading-a-polynomial)
  - [Simplify](#simplify)
  - [Sort](#sort)
  - [Add, subtract, multiply](#add-subtract-multiply)
  - [Insert in order: simplify and sort in one step](#insert-in-order-simplify-and-sort-in-one-step)
  - [Display](#display)
- [Linked Lists in C](#linked-lists-in-c)
- [Edge Cases](#edge-cases)

---

## Problem

### Input

1. The number of test cases, `t`.
2. For each test case:
   - The **operation**:

     | Code | Operation | Polynomials |
     |---|---|---|
     | 1 | **Simplify** | 1 |
     | 2 | **Add** | 2 |
     | 3 | **Subtract** the second from the first | 2 |
     | 4 | **Multiply** | 2 |

   - The polynomial(s), **one per line**, each written as **coefficient–exponent pairs**:

     ```
     1 5 2 3 -10 2 -4 1     →   x^5 + 2x^3 − 10x^2 − 4x
     └─┘ └─┘ └──┘ └──┘
     x^5 2x^3 −10x^2 −4x
     ```

   The number of terms isn't given. A polynomial ends at the end of its line.

### Output

One line per test case: the resulting polynomial, in the form

```
c1x^e1 OP c2x^e2 OP ... OP cnx^en
```

where `OP` is `+` or `-`, with **no spaces**.

| Rule | Example | Printed |
|---|---|---|
| Terms in **decreasing order of exponent** | `3 2 5 4` | `5x^4+3x^2` |
| Coefficient **1**: leave it out | 1x³ | `x^3` |
| Exponent **1**: leave out `^1` | 5x¹ | `5x` |
| Exponent **0**: leave out `x` | 7x⁰ | `7` |
| Coefficient **0**: leave the term out | 0x⁴ | *(nothing)* |

---

## Sample

**Input**

```
6
1
7 8 4 4 23 1 100 0 3 5
1
7 8 3 5 -4 4 2 3 -23 1 100 0 4 4 -7 8 -95 0
2
1 5 2 3 -10 2 -4 1
19 5 -10 3 18 1
3
1 5 2 3 -10 2 -4 1
19 5 -10 3 18 1
4
1 2 -5 1 7 0
4 1
4
1 2 -5 1 7 0
2 3 10 1
```

**Output** (as given)

```
7x^8+4x^4+2x^3+23x+100+3x^5
3x^5+2x^3-23x+5
20x^5-8x^3-10x^2+14x
-18x^5+12x^3-10x^2-22x
4x^3-20x^2+28x
2x^5-10x^4+24x^3-50x^2+70x
```

> Line 1 doesn't follow the problem's own rules. By the rules it should be `7x^8+3x^5+4x^4+23x+100` ([details](#problem-with-the-sample-line-1)).

---

## Sample Walkthrough

**1. Simplify** `7x^8 + 4x^4 + 23x + 100 + 3x^5`

No two terms share an exponent, so simplifying only **sorts**: `7x^8+3x^5+4x^4+23x+100`.

**2. Simplify** `7x^8 + 3x^5 − 4x^4 + 2x^3 − 23x + 100 + 4x^4 − 7x^8 − 95`

| Exponent | Terms | Sum |
|---|---|---|
| 8 | 7, −7 | **0** (dropped) |
| 5 | 3 | 3 |
| 4 | −4, 4 | **0** (dropped) |
| 3 | 2 | 2 |
| 1 | −23 | −23 |
| 0 | 100, −95 | 5 |

→ `3x^5+2x^3-23x+5`

**3. Add** `(x^5 + 2x^3 − 10x^2 − 4x) + (19x^5 − 10x^3 + 18x)`

| Exponent | First | Second | Sum |
|---|---|---|---|
| 5 | 1 | 19 | 20 |
| 3 | 2 | −10 | −8 |
| 2 | −10 | – | −10 |
| 1 | −4 | 18 | 14 |

→ `20x^5-8x^3-10x^2+14x`

**4. Subtract** the same two: `(first) − (second)`

| Exponent | First | Second | Difference |
|---|---|---|---|
| 5 | 1 | 19 | −18 |
| 3 | 2 | −10 | 12 |
| 2 | −10 | – | −10 |
| 1 | −4 | 18 | −22 |

→ `-18x^5+12x^3-10x^2-22x`

**5. Multiply** `(x^2 − 5x + 7) · (4x)`

| | × 4x |
|---|---|
| x² | 4x³ |
| −5x | −20x² |
| 7 | 28x |

→ `4x^3-20x^2+28x`

**6. Multiply** `(x^2 − 5x + 7) · (2x^3 + 10x)`

| | × 2x³ | × 10x |
|---|---|---|
| x² | 2x⁵ | 10x³ |
| −5x | −10x⁴ | −50x² |
| 7 | 14x³ | 70x |

Combine like terms: 10x³ + 14x³ = 24x³.

→ `2x^5-10x^4+24x^3-50x^2+70x`

---

## Problem with the Sample: Line 1

The first expected output is:

```
7x^8+4x^4+2x^3+23x+100+3x^5
```

for the input `7 8 4 4 23 1 100 0 3 5`. It breaks two of the problem's rules:

| Problem | Detail |
|---|---|
| A term that isn't in the input | `2x^3`. The input has terms with exponents 8, 4, 1, 0 and 5, and **none** with exponent 3 (`2x^3` appears in the **second** test case) |
| Not sorted | `3x^5` comes last, after `100` |

A reference implementation following the rules produces lines 2–6 of the sample exactly, and for line 1 gives:

```
7x^8+3x^5+4x^4+23x+100
```

Line 1 is most likely an error in the sample. Don't try to match it.

---

## Why a Linked List

The number of terms isn't known ahead of time, and the operations constantly **merge**, **remove** and **insert** terms:

| Operation | Array | Linked list |
|---|---|---|
| Unknown number of terms | Must guess a maximum or resize | Grows one node at a time |
| Remove a zero term | Shift every later term left | Re-link one pointer |
| Insert a term in sorted position | Shift every later term right | Re-link two pointers |
| Access term `i` directly | Instant: `a[i]` | Walk `i` nodes |

Polynomials mostly need the first three, so a linked list fits.

---

## Approach

### The structures

The same **term** idea as MP 2, plus a `next` pointer that links the terms into a chain:

```c
typedef struct term {
    int coef;
    int exp;
    struct term *next;
} term;

typedef struct {
    term *head;
    int size;
} list;     // a polynomial
```

```
head ──► [ 7 | 8 | ●]──► [ 3 | 5 | ●]──► [ 4 | 4 | ●]──► NULL
           coef exp next
```

`struct term *next` must use the **struct tag** (`struct term`), because the `typedef` name `term` doesn't exist yet at that point.

### Reading a polynomial

Each polynomial is **one line** with an unknown number of pairs. Read the line, then pull pairs out of it until none are left:

```c
char line[1000];
fgets(line, sizeof line, stdin);

char *p = line;
int c, e, used;
while (sscanf(p, "%d %d%n", &c, &e, &used) == 2) {
    addTerm(&poly, c, e);
    p += used;              // move past the pair just read
}
```

`%n` stores how many characters `sscanf` has consumed so far. Advancing `p` by that amount makes the next `sscanf` start at the next pair.

Reading pairs with plain `scanf("%d %d")` doesn't work here. `scanf` skips newlines, so it can't tell where one polynomial ends and the next line starts.

After reading the operation number with `scanf`, consume the rest of that line (`getchar()` or `fgets`) before reading the polynomial line. Otherwise `fgets` reads the leftover newline as an empty polynomial.

### Simplify

The statement's hint:

```c
void simplify(list *l){
    int i, j, s = l->size;
    for(i = 0; i < s-1; i++){
        for(j = i+1; j < s; j++){
            if(itemAt(*l,i).exp == itemAt(*l,j).exp)
                //what operation will you simply call here?
        }
    }
}
```

**The answer:** add term `j`'s coefficient into term `i`, then **remove** term `j`.

```c
if (itemAt(*l, i).exp == itemAt(*l, j).exp) {
    setCoef(l, i, itemAt(*l, i).coef + itemAt(*l, j).coef);
    removeAt(l, j);
    s--;        // the list is one shorter
    j--;        // the next term slid into position j; check it too
}
```

Two details the hint doesn't show:

- **`s` is cached.** After a removal the list is shorter, so `s` must shrink too, and `j` must step back so the term that moved into position `j` isn't skipped.
- **Zeros.** Merging can produce a coefficient of 0 (`4x^4 − 4x^4`). Remove those terms afterwards, or skip them when displaying.

### Sort

Terms must be printed by **decreasing exponent**. On a linked list, the simplest sort is a **bubble sort that swaps the data** in the nodes, leaving the links alone:

```c
void sortDesc(list *l) {
    for (int pass = 0; pass < l->size - 1; pass++)
        for (term *t = l->head; t->next != NULL; t = t->next)
            if (t->exp < t->next->exp) {
                int c = t->coef, e = t->exp;
                t->coef = t->next->coef; t->exp = t->next->exp;
                t->next->coef = c;       t->next->exp = e;
            }
}
```

### Add, subtract, multiply

Each one **builds a result list**, then simplifies and sorts it:

| Operation | Build the result by |
|---|---|
| Add | Copy every term of A, then every term of B |
| Subtract | Copy every term of A, then every term of B with its **coefficient negated** |
| Multiply | For **every pair** (a from A, b from B), add the term `a.coef × b.coef`, `a.exp + b.exp` |

```c
// multiply
for (term *a = A.head; a != NULL; a = a->next)
    for (term *b = B.head; b != NULL; b = b->next)
        addTerm(&result, a->coef * b->coef, a->exp + b->exp);
simplify(&result);
sortDesc(&result);
```

Multiplying an `m`-term polynomial by an `n`-term one creates `m × n` terms before simplifying.

### Insert in order: simplify and sort in one step

Instead of simplifying and sorting afterwards, `addTerm` can keep the list **always sorted and simplified**:

1. Walk to the first node whose exponent is **≤** the new one.
2. If it's **equal**, add the coefficients. If the sum is 0, remove that node.
3. Otherwise, insert a new node **before** it.

```c
void addTerm(list *l, int coef, int exp) {
    if (coef == 0) return;
    term **pp = &l->head;                         // pointer to the link to update
    while (*pp != NULL && (*pp)->exp > exp)
        pp = &(*pp)->next;

    if (*pp != NULL && (*pp)->exp == exp) {       // like term: merge
        (*pp)->coef += coef;
        if ((*pp)->coef == 0) {                   // cancelled out: unlink it
            term *dead = *pp;
            *pp = dead->next;
            free(dead);
            l->size--;
        }
        return;
    }
    term *n = malloc(sizeof(term));               // new exponent: insert here
    n->coef = coef;
    n->exp = exp;
    n->next = *pp;
    *pp = n;
    l->size++;
}
```

Then **simplify** is just "insert every term". Add, subtract and multiply need no separate simplify or sort step.

`term **pp` is a **pointer to a pointer**: it points at whichever `next` field (or `head`) leads to the current node. Changing `*pp` re-links the list at that spot, so inserting at the front and in the middle are handled by the same code.

### Display

```c
void display(list l) {
    if (l.head == NULL) { printf("0\n"); return; }      // every term cancelled
    for (term *t = l.head; t != NULL; t = t->next) {
        int c = t->coef;
        if (c < 0)                printf("-");
        else if (t != l.head)     printf("+");          // no leading +
        int a = abs(c);

        if (t->exp == 0)          printf("%d", a);       // constant: always show the number
        else {
            if (a != 1)           printf("%d", a);       // hide a coefficient of 1
            printf("x");
            if (t->exp != 1)      printf("^%d", t->exp); // hide ^1
        }
    }
    printf("\n");
}
```

| Term | Printed |
|---|---|
| first term, −18x⁵ | `-18x^5` (no `+` before it) |
| later term, +12x³ | `+12x^3` |
| −1x³ | `-x^3` |
| 1x⁰ | `1` (the 1 stays for a constant) |
| −23x¹ | `-23x` |

The sign is printed **separately** from the number, using `abs(c)`, so negative terms show `-23x` and never `+-23x`.

---

## Linked Lists in C

A **linked list** is a chain of **nodes**. Each node holds data plus a pointer to the next node. The last node points to `NULL`.

```c
// create a node
term *n = malloc(sizeof(term));
n->coef = 5; n->exp = 2; n->next = NULL;

// insert at the front
n->next = l->head;
l->head = n;

// walk the list
for (term *t = l->head; t != NULL; t = t->next)
    printf("%d %d\n", t->coef, t->exp);

// remove the node after `prev`
term *dead = prev->next;
prev->next = dead->next;
free(dead);

// free the whole list
term *t = l->head;
while (t != NULL) {
    term *next = t->next;     // save before freeing
    free(t);
    t = next;
}
l->head = NULL;
```

| Mistake | Result |
|---|---|
| Losing `head` while traversing (`l->head = l->head->next` in a loop) | The front of the list is lost for good |
| Using `t->next` after `free(t)` | Undefined behavior. Save `next` first |
| Forgetting `next = NULL` on a new last node | The list "continues" into garbage memory |
| Not freeing lists between test cases | Memory leak |
| Dereferencing `NULL` (`t->next->exp` when `t->next` is `NULL`) | Crash. Check before following a link |

---

## Edge Cases

| Case | Example | Expected |
|---|---|---|
| Everything cancels | simplify `3 2 -3 2` | Not specified. `0` is a sensible output |
| Constant term of 1 | `1 0` | `1` (not empty) |
| Coefficient −1 | `-1 3` | `-x^3` |
| First term negative | `-4 2 1 0` | `-4x^2+1`, with no leading `+` |
| Subtracting a polynomial from itself | op 3, same polynomial twice | Everything cancels (see the first row) |
| Multiplying by a constant | `(x^2 − 5x + 7) · 3` | `3x^2-15x+21` |
| Exponents given out of order | `5 0 2 3` | `2x^3+5` |
| Zero coefficient in the input | `0 4 3 1` | `3x` |
