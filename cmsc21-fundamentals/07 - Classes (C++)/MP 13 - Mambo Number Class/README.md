# MP 13: This is Mambo Number Class

CMSC 21 machine problem introducing **C++ classes**: build a `Number` class that stores an integer along with its **sign**, **parity** and **primality**, keeping that data **private** behind constructors, setters, getters and a display function.

## Contents

- [Problem](#problem)
  - [Properties](#properties)
  - [Required members](#required-members)
  - [Input and output](#input-and-output)
- [Sample](#sample)
- [Startup Files](#startup-files)
  - [`main.cpp`](#maincpp)
  - [`number.h`](#numberh)
  - [`number.cpp`](#numbercpp)
- [Notes on the Startup Files](#notes-on-the-startup-files)
- [Approach](#approach)
  - [The property rules](#the-property-rules)
  - [Private helpers](#private-helpers)
  - [Constructors, `set` and `get`](#constructors-set-and-get)
  - [`display`](#display)
- [From C to C++](#from-c-to-c)
  - [Classes vs. structures](#classes-vs-structures)
  - [Constructors](#constructors)
  - [The `::` operator](#the--operator)
  - [Input and output with `cin` and `cout`](#input-and-output-with-cin-and-cout)
  - [Compiling](#compiling)
- [Why Keep the Data Private](#why-keep-the-data-private)
- [Testing Checklist](#testing-checklist)

---

## Problem

### Properties

Besides its **value** (an integer), a `Number` keeps three properties:

| Property | Possible values |
|---|---|
| Sign | positive, negative, or **neither** (zero) |
| Parity | even, odd, or **neither**. For this MP, **negative numbers have no parity** |
| Primality | prime, composite, or **neither** |

**All of this data is private.**

### Required members

- A **default constructor**
- An **overloaded constructor** (taking the value)
- **Setter** and **getter** functions
- **Sign**, **parity** and **primality** functions
- A **display** function

### Input and output

**Input:** two integers. The first creates the `Number`, and the second resets its value.

**Output:** the number's value and all its properties, before and after the reset, followed by the final value from `get()`.

---

## Sample

**Input**

```
10 12
```

**Output**

```
10
POSITIVE
EVEN
COMPOSITE
12
POSITIVE
EVEN
COMPOSITE
12
```

| Lines | Printed by |
|---|---|
| 1–4 | `n.display()` after `Number n(10)` |
| 5–8 | `n.display()` after `n.set(12)` |
| 9 | `cout << n.get() << endl;` |

---

## Startup Files

Provided by the instructor. They're reproduced here for reference.

### `main.cpp`

```cpp
//the main file is now a cpp file
#include "number.h" //similar to including a user-defined header file in c
#include <iostream> //this is for input output in cpp

using namespace std;

int main(){ //this is the same main function as with c
    //since we read 2 inputs and both are integers, we need to declare them
    int x, y; //c and c++ support the same primitive types
    
    cin>>x>>y; //this is reading 2 inputs from the console
    
    Number n(x); //makes use of the overloaded constructor
    n.display(); //should display the information about the number
    n.set(y); //resets the number to the second input
    n.display(); //since number was reset, we call display again
    cout<<n.get()<<endl;
    return 0;
}
```

### `number.h`

```cpp
class Number{
private:
    int value; //the actual value of the number
    int sign; //you can use -1 for negative, 0 for neither, 1 for positive
    int parity; //you can use 0 for neither, 1 for odd, 2 for even
    int primality; //you can use 0 for neither, 1 for prime, 2 for composite
    //you may also use the data type string to represent sign, parity, and primality
    //like so
    //string sign;
    //string parity;
    //string primality;
    //yes, there is a type called string in cpp (instead of using an array of characters)
    void setPrimality();
    void setSign();
    void setParity();
public:
    Number(); //default constructor
    Number(int); //overloaded constructor
    void set(int); //sets the value to a new one
    int get(); //simply returns the value of the number
    void display(); //displays the number's properties
};
```

### `number.cpp`

```cpp
#include "number.h"
#include <iostream>

using namespace std;

void Number::setPrimality(){
    //check if value is prime or not and set primality accordingly
}
void Number::setSign(){
    //check if value is positive, negative or neither and set sign accordingly
}
void Number::setParity(){
    //check if value is even, odd or neither and set parity accordingly
}

Number::Number(){//default constructor set the value to 0
//this means every time a new number is constructed, it is the number 0.
    value = 0;
    sign = 0;
    parity = 2
    primality = 0;
    
}

Number::Number(int n){ //overloaded constructor
    value = n;
    //call the private setter functions that set the properties of the number
    setSign();
    setParity();
    setPrimality();
}

void Number::set(int n){ //sets the value to a new one
    value = n;
    //since everytime this set is called or used
    //the value changes
    //and therefore we need to update the properties
    //luckily, there are functions that have been set for these
    //use those
}

int Number::get(){ //simply returns the
    
}

void Number::display(){ //displays the number's properties
    //to printf use cout
    //cout<<"Hello World\n"; prints the string in the double quotes on the console
    //cout<<value<<endl; prints the value of the variable value/endl prints a line
}
```

---

## Notes on the Startup Files

| Where | Issue | Fix |
|---|---|---|
| `Number::Number()` | `parity = 2` is missing its semicolon. The file doesn't compile: `error: expected ';' before 'primality'` | `parity = 2;` |
| `Number::get()` | Empty body in a function that returns `int`. The caller gets garbage | `return value;` |
| `Number::set(int)` | Only updates `value`, so the properties go stale after a reset | Call `setSign()`, `setParity()` and `setPrimality()` |
| Default constructor | Sets `parity = 2` (even) for 0 | Correct: 0 is even. 0 is neither positive nor negative, and neither prime nor composite |
| `number.h` | No `#include <string>`, though the comments suggest using `string` | Add `#include <string>` if you switch to `string` members |
| `number.h` | No include guards | Fine here, since each `.cpp` includes it once. See [MP 8](../../03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/#multi-file-programs) |

---

## Approach

### The property rules

| Value | Sign | Parity | Primality |
|---|---|---|---|
| Negative (e.g. −7) | NEGATIVE | **NEITHER** (by this MP's rule) | NEITHER |
| 0 | NEITHER | EVEN | NEITHER |
| 1 | POSITIVE | ODD | NEITHER |
| 2 | POSITIVE | EVEN | PRIME |
| 7 | POSITIVE | ODD | PRIME |
| 10 | POSITIVE | EVEN | COMPOSITE |

- **Prime:** an integer **greater than 1** whose only divisors are 1 and itself.
- **Composite:** an integer greater than 1 that **isn't** prime.
- **Neither:** everything below 2, i.e. 0, 1 and all negatives.

The sample only shows `POSITIVE`, `EVEN` and `COMPOSITE`. The other words aren't given, so `NEGATIVE`, `ODD`, `PRIME` and `NEITHER` (in the same uppercase style) are the natural choices.

### Private helpers

Each helper looks at `value` and sets one property, using the codes suggested in `number.h`:

```cpp
void Number::setSign() {
    if (value > 0)      sign = 1;
    else if (value < 0) sign = -1;
    else                sign = 0;
}

void Number::setParity() {
    if (value < 0)              parity = 0;     // negatives: neither
    else if (value % 2 == 0)    parity = 2;     // even
    else                        parity = 1;     // odd
}

void Number::setPrimality() {
    if (value < 2) { primality = 0; return; }   // 0, 1, negatives: neither
    primality = 1;                              // prime until a divisor is found
    for (int d = 2; d <= value / d; d++)        // d <= √value, without overflow
        if (value % d == 0) { primality = 2; return; }
}
```

`d <= value / d` is the same test as `d * d <= value` (stop at the square root), but it can't overflow when `value` is near `INT_MAX`.

The helpers are **private**: only the class's own functions call them, so the properties are always computed from the current value and can't be set to something inconsistent from outside.

### Constructors, `set` and `get`

```cpp
Number::Number() {
    value = 0; sign = 0; parity = 2; primality = 0;
}

Number::Number(int n) {
    set(n);                      // one place that updates everything
}

void Number::set(int n) {
    value = n;
    setSign();
    setParity();
    setPrimality();
}

int Number::get() {
    return value;
}
```

Having the overloaded constructor call `set` keeps the "update all properties" logic in **one** place. The startup file repeats the three calls in the constructor instead, and both work.

### `display`

```cpp
void Number::display() {
    cout << value << endl;
    cout << (sign > 0 ? "POSITIVE" : sign < 0 ? "NEGATIVE" : "NEITHER") << endl;
    cout << (parity == 2 ? "EVEN" : parity == 1 ? "ODD" : "NEITHER") << endl;
    cout << (primality == 1 ? "PRIME" : primality == 2 ? "COMPOSITE" : "NEITHER") << endl;
}
```

Using `string` members instead (as the header's comments suggest) makes `display` just four `cout` lines, at the cost of comparing strings elsewhere.

---

## From C to C++

### Classes vs. structures

A C `struct` only groups data. A C++ `class` groups data **and the functions that work on it**, and controls who can access what:

| | C `struct` | C++ `class` |
|---|---|---|
| Holds data | Yes | Yes |
| Holds functions | No (functions take the struct as a parameter) | Yes (**member functions**) |
| Access control | Everything is visible | `private`, `public` (and `protected`) |
| Default access | – | `private` |
| Initialization | Manual (`initList(&l)`) | Automatic, through a **constructor** |

Compare MP 8's C style with this MP's C++ style:

```c
// C: the data is passed to the functions
list bank;
initList(&bank);
deposit(&bank, 1, 500.0);
```

```cpp
// C++: the functions belong to the object
Number n(10);       // constructor runs automatically
n.set(12);          // member function, called on n
n.display();
```

Inside a member function, the object's fields are used by name (`value`, `sign`). There's no `l->` or `v.` in front, because the function already belongs to one particular object.

### Constructors

A **constructor** has the **same name as the class** and **no return type**. It runs automatically when an object is created:

| Declaration | Constructor that runs |
|---|---|
| `Number a;` | Default: `Number()` → the value 0 |
| `Number b(10);` | Overloaded: `Number(int)` → the value 10 |

Having two constructors with the same name but different parameters is **overloading**. C++ allows it and C doesn't. (It's also why C++ wouldn't have MP 9's `remove` name clash in the same way.)

**Careful:** `Number a();` with empty parentheses does **not** create an object. C++ reads it as the declaration of a function named `a` that returns a `Number`. Use `Number a;`.

### The `::` operator

In `number.cpp`, each function is defined with `Number::` in front:

```cpp
void Number::set(int n) { ... }
```

`Number::set` means "the `set` that belongs to the class `Number`". Without it, the compiler would treat `set` as an ordinary standalone function, and `value` wouldn't be in scope.

### Input and output with `cin` and `cout`

| C | C++ |
|---|---|
| `#include <stdio.h>` | `#include <iostream>` |
| `scanf("%d %d", &x, &y);` | `cin >> x >> y;` |
| `printf("%d\n", x);` | `cout << x << endl;` |
| Format specifiers (`%d`, `%s`, `%lf`) | Not needed: the type decides how it's printed |
| `&` before variables | Not needed |

`using namespace std;` lets you write `cin`, `cout` and `endl` instead of `std::cin`, `std::cout` and `std::endl`.

### Compiling

Use `g++` (the C++ compiler), and list both `.cpp` files:

```bash
g++ -Wall -o number main.cpp number.cpp
echo "10 12" | ./number
```

Compiling with `gcc` instead usually fails at the linking stage, with errors about `std::cout`, because `gcc` doesn't link the C++ standard library by default.

---

## Why Keep the Data Private

If `value` were public, any code could do:

```cpp
n.value = 7;        // value is now 7...
n.display();        // ...but sign, parity and primality still describe the old value
```

With the data private, the **only** way to change the value is `set`, which always recomputes the properties. The object can never get into an inconsistent state. This is **encapsulation**: the class guards its own rules.

Trying to access a private member from outside the class is a **compile error**:

```
error: 'int Number::value' is private within this context
```

---

## Testing Checklist

| Input | Expected output (one value per line) |
|---|---|
| `10 12` | The sample |
| `7 9` | `7 POSITIVE ODD PRIME`, `9 POSITIVE ODD COMPOSITE`, `9` |
| `0 1` | `0 NEITHER EVEN NEITHER`, `1 POSITIVE ODD NEITHER`, `1` |
| `-7 2` | `-7 NEGATIVE NEITHER NEITHER`, `2 POSITIVE EVEN PRIME`, `2` |
| `2147483647 -1` | `2147483647 POSITIVE ODD PRIME` (the largest `int` is prime), `-1 NEGATIVE NEITHER NEITHER`, `-1` |

The `2147483647` case checks that the primality loop doesn't overflow. With `d * d <= value`, `d * d` would pass `INT_MAX` before the loop ends.
