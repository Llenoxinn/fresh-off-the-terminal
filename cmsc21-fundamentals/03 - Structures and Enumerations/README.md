# 03 - Structures and Enumerations

CMSC 21 machine problems on **structures** (`struct`) and **enumerations** (`enum`), followed by a reference covering everything you need to know about grouping data in C.

## Contents

- [Machine Problems](#machine-problems)
- [Structures and Enumerations in C](#structures-and-enumerations-in-c)
  1. [Why structures](#1-why-structures)
  2. [Declaring a structure](#2-declaring-a-structure)
  3. [`typedef`](#3-typedef)
  4. [Creating and initializing](#4-creating-and-initializing)
  5. [Accessing members: `.` and `->`](#5-accessing-members--and--)
  6. [Copying and comparing](#6-copying-and-comparing)
  7. [Structures and functions](#7-structures-and-functions)
  8. [Arrays of structures](#8-arrays-of-structures)
  9. [Structures inside structures](#9-structures-inside-structures)
  10. [Enumerations](#10-enumerations)
  11. [Enums with `switch` and lookup tables](#11-enums-with-switch-and-lookup-tables)
  12. [A list as a structure](#12-a-list-as-a-structure)
  13. [Header files and multi-file programs](#13-header-files-and-multi-file-programs)
  14. [Common mistakes](#14-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 2: Terms of Endearment | [MP 2 - Terms of Endearment](MP%202%20-%20Terms%20of%20Endearment/) | A term as a `struct`, returning a structure from `multiply`, parsing `4x^3` |
| MPA 2: Bantugans, Fight! | [MPA 2 - Bantugans Fight](MPA%202%20-%20Bantugans%20Fight/) | A warrior `struct`, weapon and shield `enum`s, pointers to structures, a turn-based simulation |
| MP 8: Show me the money! | [MP 8 - Show Me the Money](MP%208%20-%20Show%20Me%20the%20Money/) | An array-based list of account structures, a `boolean` enum, header + implementation files |

---

## Structures and Enumerations in C

### 1. Why structures

Without structures, related data lives in separate variables that only *happen* to belong together:

```c
int hp1, mana1, weapon1, shield1;      // warrior 1
int hp2, mana2, weapon2, shield2;      // warrior 2
```

A **structure** groups them into **one type**:

```c
struct Bantugan {
    int hp, mana, weapon, shield;
};

struct Bantugan timan, dua;            // two warriors, each with all four fields
```

Now a warrior can be passed to a function, stored in an array, or copied as a single value.

### 2. Declaring a structure

```c
struct Term {
    int coefficient;
    int exponent;
};                       // ← the semicolon is required
```

This declares a **type**, like a blueprint. No memory is used until you create a variable of that type.

The members can be any type: numbers, characters, arrays, pointers, enums, even other structures.

### 3. `typedef`

`typedef` gives a type a shorter name, so you can write `Term` instead of `struct Term`:

```c
typedef struct {
    int coefficient;
    int exponent;
} Term;

Term t;                  // instead of: struct Term t;
```

If the structure needs to **refer to itself** (as linked-list nodes do), give it a tag too:

```c
typedef struct node {
    int data;
    struct node *next;   // the typedef name doesn't exist yet here
} node;
```

### 4. Creating and initializing

```c
Term a = {4, 3};                              // in declaration order: 4x^3
Term b = {.exponent = 2, .coefficient = 5};   // by name (C99): 5x^2
Term c = {0};                                 // every member zero
Term d;                                       // uninitialized: garbage
```

### 5. Accessing members: `.` and `->`

| You have | Use | Example |
|---|---|---|
| A structure | `.` | `t.coefficient = 4;` |
| A **pointer** to a structure | `->` | `p->coefficient = 4;` |

`p->x` is shorthand for `(*p).x`. The parentheses matter: `*p.x` means `*(p.x)`.

```c
Bantugan timan = {10, 10, 1, 1};
Bantugan *attacker = &timan;

attacker->hp -= 3;       // changes timan.hp
printf("%d\n", timan.hp);  // 7
```

### 6. Copying and comparing

Structures can be **assigned** with `=`. Every member is copied, **including arrays inside**:

```c
account a = ..., b;
b = a;                   // b is an independent copy of a
```

Structures **cannot** be compared with `==`. Compare the members you care about:

```c
if (a.number == b.number && strcmp(a.lname, b.lname) == 0) ...
```

If a structure holds a **pointer**, copying it copies the **address**, not what it points to. Both copies then share the same data. This matters for MP 9's vector, whose `items` pointer is shared by every copy.

### 7. Structures and functions

Structures are passed **by value** (copied) by default, like `int`s.

| Parameter | Function gets | Can change the caller's structure? | Cost |
|---|---|---|---|
| `Term t` | A copy | No | Copies every byte |
| `Term *t` | The address | **Yes** | One pointer |
| `const Term *t` | The address | No (enforced by the compiler) | One pointer |

```c
Term multiply(Term a, Term b) {         // MP 2: copies in, a new structure out
    Term p = { a.coefficient * b.coefficient, a.exponent + b.exponent };
    return p;
}

void attack(Bantugan *atk, Bantugan *def) {   // MPA 2: must change both warriors
    def->hp -= damage(atk->weapon, def->shield);
}
```

**Returning** a structure is allowed and copies it out. That's how a function can effectively return several values at once, which MP 1-1 and MP 1-2 had to work around before structures were allowed.

### 8. Arrays of structures

```c
account accounts[100];

accounts[0].balance = 5000.0;
for (int i = 0; i < size; i++)
    printf("%s\n", accounts[i].lname);
```

`accounts[i].balance` reads as "the `balance` of the `i`-th account".

### 9. Structures inside structures

```c
typedef struct { int day, month, year; } Date;

typedef struct {
    char name[50];
    Date birthday;
} Person;

Person p;
p.birthday.year = 2006;
```

Chain the dots from the outside in.

### 10. Enumerations

An **enumeration** gives names to a set of related integer constants:

```c
typedef enum {
    WOODEN_SPEAR = 1,    // explicit start
    SILVER_AX,           // 2
    DIAMOND_SCYTHE       // 3
} Weapon;

Weapon w = SILVER_AX;
```

| Rule | Detail |
|---|---|
| Default values | Start at 0 and count up by 1 |
| Explicit values | `= value` sets that constant; later ones continue from it |
| Underlying type | An integer: enums can be compared, used in `switch`, and used as array indices |
| Converting input | `w = (Weapon) inputCode;` |

Enums replace **magic numbers**: `if (shield == DIAMOND)` explains itself, and `if (shield == 3)` doesn't.

**A `boolean` enum** (as in MP 8) gives C `TRUE`/`FALSE` names:

```c
typedef enum { FALSE = 0, TRUE = 1 } boolean;
```

(`<stdbool.h>` provides the standard `bool`, `true` and `false` since C99.)

### 11. Enums with `switch` and lookup tables

```c
switch (b->weapon) {
    case WOODEN_SPEAR:   name = "Wooden Spear";   break;
    case SILVER_AX:      name = "Silver Ax";      break;
    case DIAMOND_SCYTHE: name = "Diamond Scythe"; break;
}
```

Since enum values are small integers, an **array indexed by the enum** does the same in one line:

```c
const char *WEAPON_NAME[] = { "", "Wooden Spear", "Silver Ax", "Diamond Scythe" };
printf("%s\n", WEAPON_NAME[b->weapon]);
```

The empty string at index 0 is there because the enum starts at 1.

### 12. A list as a structure

MP 8 bundles an array **and its size** into one structure:

```c
typedef struct {
    account accounts[100];   // capacity
    int size;                // how many are in use
} list;
```

Passing a `list *` to a function hands over **both** the items and the count, so they can't get out of sync. This is the idea that later becomes the [vector](../05%20-%20Dynamic%20Arrays/) (an array that grows) and the [linked list](../06%20-%20Linked%20Lists/).

### 13. Header files and multi-file programs

MP 8 splits the program into three files:

| File | Contains |
|---|---|
| `bank.h` | Types (`struct`, `enum`, `typedef`) and function **declarations** |
| `bank.c` | Function **definitions** (`#include "bank.h"`) |
| `main.c` | The program (`#include "bank.h"`) |

```bash
gcc -Wall -o bank main.c bank.c      # list every .c file; never the .h
```

Use **include guards** in headers so a second `#include` of the same file is skipped:

```c
#ifndef BANK_H
#define BANK_H
/* ... */
#endif
```

### 14. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Missing `;` after the closing `}` of a `struct` | Confusing errors on the following lines | `};` |
| `p.x` when `p` is a pointer | Compile error | `p->x` |
| `*p.x` | Means `*(p.x)` | `(*p).x` or `p->x` |
| Passing a structure by value to a function that should change it | Only the copy changes | Pass a pointer |
| `a == b` on structures | Compile error | Compare the members |
| `struct node *next` written as `node *next` inside a `typedef` | `node` isn't defined yet | Use the struct tag inside |
| Using enum values as array indices when the enum starts at 1 | Off-by-one | Leave index 0 unused, or start the enum at 0 |
| Reading an enum directly with `scanf("%d", &w)` | Works on most compilers but isn't guaranteed | Read into an `int`, then cast |

---

## Quick Reference

```c
typedef enum { RED, GREEN, BLUE } Color;        // 0, 1, 2

typedef struct {
    int id;
    char name[30];
    Color favorite;
} Person;

Person p = {1, "Ana", GREEN};
Person *q = &p;

p.id = 2;                 // structure: .
q->id = 3;                // pointer: ->
Person copy = p;          // copies every member

void update(Person *x);   // can change the caller's Person
void show(Person x);      // gets a copy
```

| I want to... | Use |
|---|---|
| Group related data | `typedef struct { ... } Name;` |
| Name a set of options | `typedef enum { A, B, C } Name;` |
| Change a structure in a function | Pass `Name *` and use `->` |
| Return several values | Return a structure |
| Keep an array with its size | A structure holding both |
| Turn an enum into text | A `const char *` array indexed by the enum |
