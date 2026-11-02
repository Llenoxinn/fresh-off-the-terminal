# 07 - Classes (C++)

CMSC 21 machine problem introducing **C++** and **classes**, followed by a reference covering the C++ you need coming from C: classes, objects, constructors, encapsulation and `iostream`.

## Contents

- [Machine Problems](#machine-problems)
- [C++ Classes for C Programmers](#c-classes-for-c-programmers)
  1. [From C to C++](#1-from-c-to-c)
  2. [Classes and objects](#2-classes-and-objects)
  3. [Access: `private` and `public`](#3-access-private-and-public)
  4. [Member functions](#4-member-functions)
  5. [Constructors](#5-constructors)
  6. [Getters and setters](#6-getters-and-setters)
  7. [Splitting a class across files](#7-splitting-a-class-across-files)
  8. [Input and output with `iostream`](#8-input-and-output-with-iostream)
  9. [`string`](#9-string)
  10. [Overloading](#10-overloading)
  11. [`const` member functions](#11-const-member-functions)
  12. [Destructors](#12-destructors)
  13. [`struct` vs. `class` in C++](#13-struct-vs-class-in-c)
  14. [Compiling C++](#14-compiling-c)
  15. [Common mistakes](#15-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 13: This is Mambo Number Class | [MP 13 - Mambo Number Class](MP%2013%20-%20Mambo%20Number%20Class/) | A `Number` class with private value, sign, parity and primality; default and overloaded constructors; setters, getters and `display` |

---

## C++ Classes for C Programmers

### 1. From C to C++

C++ started as "C with classes". Almost all C code is valid C++, so everything from the earlier topics still applies. What's new:

| C | C++ |
|---|---|
| `struct` holds data only | `class` holds data **and** functions |
| Every field is accessible | `private` hides data from outside code |
| `initList(&l)` called by hand | A **constructor** runs automatically |
| `printf` / `scanf` | `cout` / `cin` (the C versions still work) |
| `char name[30]` | `string name` |
| One function per name | **Overloading**: same name, different parameters |
| `#include <stdio.h>` | `#include <iostream>` |
| `.c` files, `gcc` | `.cpp` files, `g++` |

### 2. Classes and objects

A **class** is a type that bundles **data** (member variables) with the **functions that work on it** (member functions). An **object** is a variable of that type.

```cpp
class Number {
private:
    int value;              // data
public:
    void set(int n);        // functions that work on that data
    int get();
};

Number a, b;                // two objects, each with its own value
a.set(10);
b.set(20);
```

Compare the C style from [MP 8](../03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/):

```c
deposit(&bank, 1, 500.0);   // C: the data is passed to the function
```

```cpp
bank.deposit(1, 500.0);     // C++: the function belongs to the object
```

### 3. Access: `private` and `public`

| Label | Accessible from |
|---|---|
| `private` | Only the class's own member functions |
| `public` | Anywhere |

```cpp
Number n;
n.set(7);        // OK: set is public
n.value = 7;     // error: 'int Number::value' is private within this context
```

**Encapsulation:** data is private, and the only way to change it is through public functions that enforce the class's rules. In MP 13, `set` always recomputes sign, parity and primality, so a `Number` can never describe a value it doesn't hold.

Helper functions that outside code shouldn't call (like `setSign`) can be private too.

### 4. Member functions

Inside a member function, the object's members are used **by name**, with no `l->` or `v.` in front:

```cpp
int Number::get() {
    return value;            // this object's value
}
```

Every member function secretly receives a pointer to the object it was called on, named `this`. `value` is short for `this->value`. You rarely need to write `this` explicitly, except when a parameter has the same name as a member:

```cpp
void Number::set(int value) {
    this->value = value;     // member = parameter
}
```

### 5. Constructors

A **constructor** has the class's name and **no return type**. It runs automatically when an object is created, so an object always starts in a valid state.

```cpp
class Number {
public:
    Number();            // default constructor
    Number(int n);       // overloaded constructor
};

Number a;                // calls Number()     → value 0
Number b(10);            // calls Number(int)  → value 10
```

**Member initializer lists** set members before the constructor body runs:

```cpp
Number::Number() : value(0), sign(0), parity(2), primality(0) { }
```

**Careful:** `Number a();` declares a **function** named `a` that returns a `Number`. It doesn't create an object. Write `Number a;`.

If you define **no** constructors, C++ provides an empty default one. If you define **any**, it doesn't, so `Number a;` stops compiling unless you also write `Number()`.

### 6. Getters and setters

```cpp
int Number::get() { return value; }

void Number::set(int n) {
    value = n;
    setSign();               // keep every derived property in sync
    setParity();
    setPrimality();
}
```

A setter is the right place to **validate** or **update dependent data**. A getter exposes a value without allowing changes.

### 7. Splitting a class across files

| File | Contains |
|---|---|
| `number.h` | The class **declaration**: members and function prototypes |
| `number.cpp` | The member function **definitions**, each prefixed with `Number::` |
| `main.cpp` | The program that uses the class |

```cpp
// number.cpp
#include "number.h"

void Number::set(int n) { ... }     // "the set that belongs to Number"
```

Without `Number::`, the compiler treats `set` as an unrelated standalone function, and `value` isn't in scope.

**Include guards** (or `#pragma once`) keep a header from being processed twice:

```cpp
#ifndef NUMBER_H
#define NUMBER_H
class Number { ... };
#endif
```

### 8. Input and output with `iostream`

```cpp
#include <iostream>
using namespace std;

int x, y;
cin >> x >> y;                        // like scanf("%d %d", &x, &y)
cout << "x = " << x << endl;          // like printf("x = %d\n", x)
```

| | C | C++ |
|---|---|---|
| Read | `scanf("%d", &x)` | `cin >> x` |
| Print | `printf("%d\n", x)` | `cout << x << endl` (or `"\n"`) |
| Format specifiers | Required | Not needed: the type decides |
| `&` on variables | Required | Not needed |
| Read a whole line | `fgets` | `getline(cin, s)` |
| Two decimal places | `%.2f` | `cout << fixed << setprecision(2) << x` (`<iomanip>`) |

`using namespace std;` lets you write `cout` instead of `std::cout`.

### 9. `string`

C++'s `string` (`#include <string>`) replaces character arrays for most uses:

```cpp
string s = "BS";
s += " Computer Science";           // concatenation, no strcat
if (s == "BS Computer Science")     // comparison with ==, no strcmp
    cout << s.length() << endl;     // no strlen
```

It grows automatically, so there's no buffer size to overflow.

### 10. Overloading

C++ allows several functions with the **same name** if their **parameter lists differ**:

```cpp
Number();               // no parameters
Number(int);            // one int
void print(int);
void print(double);
void print(string);
```

The compiler picks the version from the arguments. (This is why C++ wouldn't have MP 9's `remove` name clash in the same way.) Return types alone can't distinguish overloads.

### 11. `const` member functions

A member function that **doesn't change** the object should say so:

```cpp
int get() const;            // declaration
int Number::get() const {   // definition
    return value;
}
```

Only `const` member functions can be called on a `const Number` (or through a `const Number &` parameter).

### 12. Destructors

A **destructor** (`~ClassName()`) runs automatically when an object is destroyed: when it goes out of scope, or when it's `delete`d. It's where a class releases what it acquired:

```cpp
class Vector {
    int *items;
public:
    Vector()  { items = new int[5]; }
    ~Vector() { delete[] items; }       // freed automatically, every time
};
```

This is how C++ avoids the manual `free` calls from [Dynamic Arrays](../05%20-%20Dynamic%20Arrays/). In C++, `new`/`delete` replace `malloc`/`free`.

### 13. `struct` vs. `class` in C++

In C++ they're almost identical. Both can have member functions, constructors and access labels. The only difference is the **default access**:

| | Default access |
|---|---|
| `struct` | `public` |
| `class` | `private` |

By convention, `struct` is used for plain bundles of data and `class` for types with rules to protect.

### 14. Compiling C++

```bash
g++ -Wall -o number main.cpp number.cpp
./number
```

- Use **`g++`**, not `gcc`. `gcc` doesn't link the C++ standard library, so you get linker errors about `std::cout`.
- List every `.cpp` file, never the `.h`.
- `-std=c++17` (or newer) enables modern C++ features.

### 15. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Missing `;` after the class's closing `}` | Confusing errors in the next file or line | `};` |
| Forgetting `ClassName::` in a definition | "`value` was not declared" | `void Number::set(int n)` |
| `Number a();` | Declares a function, not an object | `Number a;` |
| Accessing a private member from `main` | Compile error | Use a public getter or setter |
| Defining an overloaded constructor but no default one | `Number a;` stops compiling | Also define `Number()` |
| A setter that doesn't update derived data | Properties go stale | Recompute them in the setter |
| Non-`void` member function with no `return` | Garbage result | Return a value on every path |
| Compiling with `gcc` | `undefined reference to std::cout` | Use `g++` |

---

## Quick Reference

```cpp
// number.h
class Number {
private:
    int value;
    void helper();                 // private helper
public:
    Number();                      // default constructor
    Number(int n);                 // overloaded constructor
    void set(int n);               // setter
    int get() const;               // getter
    void display();
};

// number.cpp
#include "number.h"
#include <iostream>
using namespace std;

Number::Number() : value(0) { }
Number::Number(int n) { set(n); }
void Number::set(int n) { value = n; helper(); }
int Number::get() const { return value; }
void Number::display() { cout << value << endl; }
```

| I want to... | Use |
|---|---|
| Hide data | `private:` |
| Let outside code use it safely | `public:` getters and setters |
| Set up an object automatically | A constructor |
| Several ways to construct | Overloaded constructors |
| Clean up automatically | A destructor `~ClassName()` |
| Define a member outside the class | `ReturnType ClassName::name(...)` |
| Read / print | `cin >>` / `cout <<` |
| Text without buffer sizes | `string` |
