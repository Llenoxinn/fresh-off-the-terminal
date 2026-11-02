# fresh-off-the-terminal

My source code from **CMSC 11** and **CMSC 21**, the two programming courses of my freshman year at the university (S.Y. 2025–2026).

These solutions aren't always the most optimized, and some have rough edges I'd write differently now. They show what I learned and how I worked through each problem at the time: from my first `if` statement in C to linked lists and my first C++ class.

---

## What's Inside

### [CMSC 11 — Introduction to Computer Science](cmsc11-intro-to-cs/)

The first course: programming fundamentals in **C**.

| Topic | Machine Problems |
|---|---|
| [Selection and Branching](cmsc11-intro-to-cs/01%20-%20Selection%20and%20Branching%20using%20C/) | Descending order, rainfall warnings, zodiac fortune teller |
| [Iterations](cmsc11-intro-to-cs/02%20-%20Iterations%20in%20C/) | Perfect numbers, powers, Fibonacci, factorial, guessing game |
| [Strings](cmsc11-intro-to-cs/03%20-%20Strings/) | Prefix check, hexadecimal validation |
| [Nested Loops](cmsc11-intro-to-cs/04%20-%20Nested%20Loops/) | First *n* perfect numbers, primality without modulo |
| [Arrays](cmsc11-intro-to-cs/05%20-%20Arrays/) | Linear vs. binary search |
| [Machine Problem Assignment](cmsc11-intro-to-cs/Machine%20Problem%20Assignment/) | FLAMES game and gene sequence search |
| [Mastery](cmsc11-intro-to-cs/Mastery/) | Rotating digits, consecutive-digit check |

### [CMSC 21 — Fundamentals of Programming](cmsc21-fundamentals/)

The second course: deeper C, data structures, and an introduction to **C++**.

| Topic | Machine Problems |
|---|---|
| [Functions](cmsc21-fundamentals/01%20-%20Functions/) | [Functions Galore](cmsc21-fundamentals/01%20-%20Functions/MPA%201%20-%20Functions%20Galore/), [Sophie's World](cmsc21-fundamentals/01%20-%20Functions/MP%201-1%20-%20Sophies%20World/), [Relatively Prime](cmsc21-fundamentals/01%20-%20Functions/MP%201-2%20-%20Relatively%20Prime/) |
| [Recursion](cmsc21-fundamentals/02%20-%20Recursion/) | [See Recursion](cmsc21-fundamentals/02%20-%20Recursion/MP%204%20-%20See%20Recursion/) |
| [Structures and Enumerations](cmsc21-fundamentals/03%20-%20Structures%20and%20Enumerations/) | [Terms of Endearment](cmsc21-fundamentals/03%20-%20Structures%20and%20Enumerations/MP%202%20-%20Terms%20of%20Endearment/), [Bantugans, Fight!](cmsc21-fundamentals/03%20-%20Structures%20and%20Enumerations/MPA%202%20-%20Bantugans%20Fight/), [Show Me the Money](cmsc21-fundamentals/03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/) |
| [Multidimensional Arrays](cmsc21-fundamentals/04%20-%20Multidimensional%20Arrays/) | [2 Dimensions](cmsc21-fundamentals/04%20-%20Multidimensional%20Arrays/MP%206-mini%20-%202%20Dimensions/), [Tic-Tac-Toe](cmsc21-fundamentals/04%20-%20Multidimensional%20Arrays/MP%206%20-%20Tic-Tac/), [Count the Objects](cmsc21-fundamentals/04%20-%20Multidimensional%20Arrays/MP%207%20-%20Count%20the%20Objects/) |
| [Dynamic Arrays](cmsc21-fundamentals/05%20-%20Dynamic%20Arrays/) | [Les Misérables (Vector)](cmsc21-fundamentals/05%20-%20Dynamic%20Arrays/MP%209%20-%20Les%20Miserables/) |
| [Linked Lists](cmsc21-fundamentals/06%20-%20Linked%20Lists/) | [The Polynomial has many Faces](cmsc21-fundamentals/06%20-%20Linked%20Lists/MP%2010%20-%20The%20Polynomial%20has%20many%20Faces/), [First and Foremost a Student](cmsc21-fundamentals/06%20-%20Linked%20Lists/MP%2011%20-%20First%20and%20Foremost%20a%20Student/) |
| [Classes (C++)](cmsc21-fundamentals/07%20-%20Classes%20%28C++%29/) | [Mambo Number Class](cmsc21-fundamentals/07%20-%20Classes%20%28C++%29/MP%2013%20-%20Mambo%20Number%20Class/) |

---

## How Each Folder Works

Every machine problem has its own `README.md` with:

- **The problem statement**, with the sample input and output
- **A walkthrough** of how the solution works
- **Notes on the topic**, written as a reference I can come back to
- **Edge cases and test cases** beyond the official samples
- **Notes on my solution**, including bugs or spec mismatches I found when reviewing it later

---

## Running the Code

You need a C compiler (and a C++ compiler for the last topic), such as **gcc/g++** through MinGW-w64 on Windows, Xcode Command Line Tools on macOS, or your package manager on Linux.

```bash
# a single C file
gcc -Wall -o program "cmsc11-intro-to-cs/03 - Strings/prefix.c"
./program < input.txt

# a C program split across files
gcc -Wall -o bank main.c bank.c

# C++
g++ -Wall -o number main.cpp number.cpp
```

Most programs read from standard input and print exactly what the problem expects, with no prompts, since they were checked automatically against expected output.

---

## What I Learned

Looking back across both courses:

- **Read the problem twice.** Most of my mistakes came from output that was almost right: a missing `!`, a lowercase letter, a trailing space.
- **Edge cases matter.** Zero, negatives, one element, the maximum size. The samples rarely cover them.
- **Choose the right type.** `int` overflows sooner than you'd think; `long long` saved several problems.
- **Structure makes code easier to reason about.** Going from everything-in-`main` to functions, structures, linked lists and finally classes changed how I think about writing programs.

---

## Academic Integrity

Every solution here was submitted under the course's **honor code**, and each file still carries its declaration. This repository is a personal archive of my own learning.

If you're currently taking these courses, please use it to **understand** the ideas, not to copy solutions. Working through the problems yourself is the whole point.
