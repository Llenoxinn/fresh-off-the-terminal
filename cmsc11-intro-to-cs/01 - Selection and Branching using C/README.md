# 01 - Selection and Branching using C

CMSC 11 machine problems on making decisions in C, followed by a reference covering everything you need to know about selection and branching.

## Contents

- [Machine Problems](#machine-problems)
  - [Problem A: Descending Order](#problem-a-descending-order--problemac)
  - [Problem B: Rainfall Warning](#problem-b-rainfall-warning--problembc)
  - [Problem C: Zodiac Fortune Teller](#problem-c-zodiac-fortune-teller--problemcc)
- [Selection and Branching in C](#selection-and-branching-in-c)
  1. [Conditions: true and false in C](#1-conditions-true-and-false-in-c)
  2. [Relational operators](#2-relational-operators)
  3. [Logical operators](#3-logical-operators)
  4. [`if`](#4-if)
  5. [`if` / `else`](#5-if--else)
  6. [`else if` chains](#6-else-if-chains)
  7. [Nested `if`](#7-nested-if)
  8. [`switch`](#8-switch)
  9. [The conditional (ternary) operator](#9-the-conditional-ternary-operator)
  10. [Operator precedence](#10-operator-precedence)
  11. [Validating input](#11-validating-input)
  12. [Common patterns](#12-common-patterns)
  13. [Common mistakes](#13-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | File | Concepts |
|---|---|---|
| A: Descending Order | [ProblemA.c](ProblemA.c) | Nested `if`, `&&`, comparing three values |
| B: Rainfall Warning | [ProblemB.c](ProblemB.c) | `else if` chains, ranges, `float` input |
| C: Zodiac Fortune Teller | [ProblemC.c](ProblemC.c) | Compound conditions with `&&` and `\|\|`, input validation, lookup arrays |

### Problem A: Descending Order · `ProblemA.c`

> Ask the user to enter 3 numbers, a, b, c. Print them in descending order.

**Sample runs**

| Input | Output |
|---|---|
| `1 2 3` | `3 2 1` |
| `5 3 7` | `7 5 3` |
| `10 4 3` | `10 4 3` |
| `2 3 1` | `3 2 1` |

**Approach:** first find which of `a`, `b`, `c` is the largest (`a >= b && a >= c`, and so on). Inside that branch, one more comparison decides the order of the remaining two. That gives 3 × 2 = 6 possible outputs, one for each ordering. Using `>=` instead of `>` makes ties fall into a branch instead of slipping through.

### Problem B: Rainfall Warning · `ProblemB.c`

> Ask the user to enter a rainfall measurement in mm. Determine what kind of warning should be broadcast.

Rainfall categories in the Philippines:

| Rainfall (mm) | Category | Warning | Meaning |
|---|---|---|---|
| less than 2.5 | Light | none | |
| 2.5 to 7.5 | Moderate | none | |
| more than 7.5 up to 15 | Heavy | Yellow | Flooding is possible |
| more than 15 up to 30 | Intense | Orange | Flooding is threatening |
| more than 30 | Torrential | Red | Serious flooding is expected in low-lying areas; residents are advised to evacuate |

**Sample runs**

| Input | Output |
|---|---|
| `1.7` | `Rain is considered light` |
| `3.8` | `Rain is considered moderate` |
| `12` | `Yellow warning` |
| `22.5` | `Orange warning` |
| `36` | `Red warning` |

**Approach:** an `else if` chain that checks the ranges from lowest to highest. Watch the boundaries: 2.5 and 7.5 are both *moderate*, while 15 and 30 belong to the lower warning. The program also checks that `scanf` returned `1`, so it stops cleanly if the input is not a number.

### Problem C: Zodiac Fortune Teller · `ProblemC.c`

> Ask the user to enter their birth month and day (in numerical format, e.g. 8 for August). Based on these inputs, tell them their zodiac sign and display a fortune. The fortune should come from the given list only (choose any 12 to serve as fortune or horoscope for the day) for the 12 zodiac signs.
>
> For this MP, there will be no evaluation, as you will be choosing from a number of possible horoscopes.

**Fortunes chosen for each sign**

| Sign | Dates | Fortune |
|---|---|---|
| Aquarius | Jan 20 – Feb 18 | Be different: conform. |
| Pisces | Feb 19 – Mar 20 | You are confused; but this is your normal state. |
| Aries | Mar 21 – Apr 19 | You will be reincarnated as a toad; and you will be much happier. |
| Taurus | Apr 20 – May 20 | Today is the tomorrow you worried about yesterday. |
| Gemini | May 21 – Jun 20 | You are going to have a new love affair. |
| Cancer | Jun 21 – Jul 22 | You are sick, twisted and perverted. I like that in a person. |
| Leo | Jul 23 – Aug 22 | Your lucky number is 3552664958674928. Watch for it everywhere. |
| Virgo | Aug 23 – Sep 22 | Be free and open and breezy! Enjoy! Things won't get any better so get used to it. |
| Libra | Sep 23 – Oct 22 | You two ought to be more careful--your love could drag on for years and years. |
| Scorpio | Oct 23 – Nov 21 | You definitely intend to start living sometime soon. |
| Sagittarius | Nov 22 – Dec 21 | Don't relax! It's only your tension that's holding you together. |
| Capricorn | Dec 22 – Jan 19 | You are number 6! Who is number one? |

<details>
<summary>Full list of fortunes to choose from</summary>

- A few hours grace before the madness begins again.
- A long-forgotten loved one will appear soon. Buy the negatives at any price.
- Abandon the search for Truth; settle for a good fantasy.
- After your lover has gone you will still have PEANUT BUTTER!
- Among the lucky, you are the chosen one.
- Are you a turtle?
- Be different: conform.
- Be free and open and breezy! Enjoy! Things won't get any better so get used to it.
- Best of all is never to have been born. Second best is to die soon.
- Caution: breathing may be hazardous to your health.
- Cheer Up! Things are getting worse at a slower rate.
- Do what comes naturally. Seethe and fume and throw a tantrum.
- Don't hate yourself in the morning -- sleep till noon.
- Don't kiss an elephant on the lips today.
- Don't look now, but there is a multi-legged creature on your shoulder.
- Don't relax! It's only your tension that's holding you together.
- Don't tell any big lies today. Small ones can be just as effective.
- Excellent day to have a rotten day.
- Excellent time to become a missing person.
- Expect the worst, it's the least you can do.
- You will be attacked next Wednesday at 3:15 p.m. by six samurai sword wielding purple fish glued to Harley-Davidson motorcycles. Oh, and have a nice day!
- Go to a movie tonight. Darkness becomes you.
- Good day to let down old friends who need help.
- Good news. Ten weeks from Friday will be a pretty good day.
- If you learn one useless thing every day, in a single year you'll learn 365 useless things.
- In the stairway of life, you'd best take the elevator.
- It is so very hard to be an on-your-own-take-care-of-yourself-because-there-is-no-one-else-to-do-it-for-you-grown-up.
- It was all so different before everything changed.
- Never look up when dragons fly overhead.
- Of course you have a purpose -- to find a purpose.
- Questionable day. Ask somebody something.
- Someone whom you reject today, will reject you tomorrow.
- There is a 20% chance of tomorrow.
- This will be a memorable month -- no matter how hard you try to forget it.
- Today is the tomorrow you worried about yesterday.
- Tomorrow will be canceled due to lack of interest.
- Tonight you will pay the wages of sin; Don't forget to leave a tip.
- What happened last night can happen again.
- You are a very redundant person, that's what kind of person you are.
- Write yourself a threatening letter and pen a defiant reply.
- You are confused; but this is your normal state.
- You are going to have a new love affair.
- You are not dead yet. But watch for further reports.
- You are number 6! Who is number one?
- You are scrupulously honest, frank, and straightforward. Therefore you have few friends.
- You are only young once, but you can stay immature indefinitely.
- You are sick, twisted and perverted. I like that in a person.
- You are standing on my toes.
- You are wise, witty, and wonderful, but you spend too much time reading this sort of trash.
- You definitely intend to start living sometime soon.
- You have the body of a 19 year old. Please return it before it gets wrinkled.
- You have the capacity to learn from mistakes. You'll learn a lot today.
- You should emulate your heroes, but don't carry it too far. Especially if they are dead.
- You two ought to be more careful--your love could drag on for years and years.
- You will be a winner today. Pick a fight with a four-year-old.
- You will be attacked by a beast who has the body of a wolf, the tail of a lion, and the face of Donald Duck.
- You will be reincarnated as a toad; and you will be much happier.
- You will be Told about it Tomorrow. Go Home and Prepare Thyself.
- You will pay for your sins. If you have already paid, please disregard this message.
- Your lucky number is 3552664958674928. Watch for it everywhere.

These fortunes come from `fortune`, a classic Unix command-line utility that displays random quotations, jokes and other snippets from a collection of "fortune cookie" files.

</details>

**Sample run**

```
Enter your birth month and day (e.g. 8 23): 8 23

		Virgo
		FORTUNE: Be free and open and breezy! Enjoy! Things won't get any better so get used to it.

Thank you for using the Zodiac Fortune Teller!
```

**Approach:**

1. **Validate the month** (1–12) and stop early if it is out of range.
2. **Validate the day** using a lookup array of days per month (`days_in_month[birth_month]`). February allows up to 29.
3. **Find the sign.** Each sign spans two months, so each condition has the shape
   `(month == M1 && day >= start) || (month == M2 && day <= end)`.

> Every problem required the honor code as a comment at the top of the source file.

---

## Selection and Branching in C

### 1. Conditions: true and false in C

C (before C99) has no separate boolean type. Any value can be used as a condition:

- **`0` is false.**
- **Any non-zero value is true** (`1`, `-5`, `3.7`, a non-null pointer).

Comparisons and logical operators always produce an `int`: `1` for true, `0` for false.

```c
printf("%d\n", 5 > 3);    // 1
printf("%d\n", 5 < 3);    // 0

int x = 7;
if (x) { ... }            // runs, because 7 is non-zero
```

Since C99 you can `#include <stdbool.h>` to use `bool`, `true` and `false`. They are still `1` and `0` underneath.

### 2. Relational operators

| Operator | Meaning | Example (`a = 5`, `b = 3`) |
|---|---|---|
| `==` | equal to | `a == b` → `0` |
| `!=` | not equal to | `a != b` → `1` |
| `>` | greater than | `a > b` → `1` |
| `<` | less than | `a < b` → `0` |
| `>=` | greater than or equal to | `a >= 5` → `1` |
| `<=` | less than or equal to | `b <= 2` → `0` |

`=` **assigns** a value. `==` **compares** two values. Mixing them up is the most common bug in this topic (see [section 13](#13-common-mistakes)).

### 3. Logical operators

| Operator | Name | True when |
|---|---|---|
| `&&` | AND | **both** sides are true |
| `\|\|` | OR | **at least one** side is true |
| `!` | NOT | the operand is false |

| `A` | `B` | `A && B` | `A \|\| B` | `!A` |
|---|---|---|---|---|
| 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 0 | 1 | 0 |
| 1 | 1 | 1 | 1 | 0 |

#### Short-circuit evaluation

C stops evaluating as soon as the answer is known:

- `A && B`: if `A` is false, `B` is **never evaluated**.
- `A || B`: if `A` is true, `B` is **never evaluated**.

This lets you guard a risky check with a safe one:

```c
if (count != 0 && total / count > 10) { ... }   // no division by zero
```

#### Checking a range

Math notation `1 <= x <= 12` does **not** work in C. Split it with `&&`:

```c
if (month >= 1 && month <= 12)   // inside the range
if (month < 1 || month > 12)     // outside the range
```

These two conditions are opposites (De Morgan's laws):

- `!(A && B)` is the same as `!A || !B`
- `!(A || B)` is the same as `!A && !B`

### 4. `if`

Runs a block only when the condition is true.

```c
if (score >= 60) {
    printf("Passed\n");
}
```

Without braces, only the **next single statement** belongs to the `if`. Using braces every time avoids surprises.

### 5. `if` / `else`

Picks exactly one of two paths.

```c
if (n % 2 == 0) {
    printf("Even\n");
} else {
    printf("Odd\n");
}
```

### 6. `else if` chains

Checks conditions **from top to bottom** and runs **only the first one** that is true. The final `else` catches everything left.

```c
if (grade >= 90) {
    printf("A\n");
} else if (grade >= 80) {
    printf("B\n");
} else if (grade >= 70) {
    printf("C\n");
} else {
    printf("F\n");
}
```

Because the branches are checked in order, each later branch already knows the earlier conditions were false. The `grade >= 80` branch doesn't need `&& grade < 90`. The same holds in Problem B: once `measurement < 2.5` has failed, the next branch could just test `measurement <= 7.5`.

**Order matters.** Put narrower or higher thresholds first when testing with `>=`, otherwise an early branch swallows everything:

```c
if (grade >= 70)      printf("C\n");   // 95 lands here: wrong
else if (grade >= 90) printf("A\n");   // never reached for 90+
```

### 7. Nested `if`

An `if` inside another `if`. Use it when a second decision only makes sense after the first one, as in Problem A.

```c
if (age >= 18) {
    if (hasID) {
        printf("Allowed\n");
    } else {
        printf("Bring an ID\n");
    }
} else {
    printf("Too young\n");
}
```

#### The dangling `else`

An `else` belongs to the **nearest unmatched `if`**, regardless of indentation:

```c
if (a > 0)
    if (b > 0)
        printf("both positive\n");
else                       // looks like it belongs to the first if...
    printf("a is not positive\n");   // ...but it belongs to `if (b > 0)`
```

Braces make the intent explicit and remove the ambiguity.

### 8. `switch`

Compares **one integer expression** against a list of **constant** values.

```c
switch (month) {
    case 1:
        printf("January\n");
        break;
    case 2:
        printf("February\n");
        break;
    // ...
    default:
        printf("Invalid month\n");
}
```

| Rule | Detail |
|---|---|
| Expression type | Integer types only: `int`, `char`, `long`, enums. **Not** `float`, `double` or strings |
| `case` labels | Must be constants (`case 3:`, `case 'A':`), not ranges or variables |
| `break` | Leaves the `switch`. Without it, execution **falls through** to the next case |
| `default` | Runs when no case matches. Optional, but good practice |

#### Fall-through on purpose

Stacking cases with no `break` between them lets several values share one block:

```c
switch (month) {
    case 4: case 6: case 9: case 11:
        days = 30;
        break;
    case 2:
        days = 28;
        break;
    default:
        days = 31;
}
```

#### `switch` vs. `else if`

| Use `switch` when... | Use `else if` when... |
|---|---|
| Testing one variable against exact values | Testing ranges (`x > 7.5`) |
| Values are integers or characters | Values are `float` / `double` |
| There are many discrete options (menus) | Conditions involve several variables (Problem C) |

### 9. The conditional (ternary) operator

`condition ? valueIfTrue : valueIfFalse` is an **expression** that produces a value, a compact `if`/`else`.

```c
int max = (a > b) ? a : b;
printf("%s\n", (n % 2 == 0) ? "Even" : "Odd");
printf("%d item%s\n", n, n == 1 ? "" : "s");
```

Use it for choosing between two **values**. For running different blocks of code, a normal `if`/`else` is easier to read. Nesting ternaries quickly becomes unreadable.

### 10. Operator precedence

From highest to lowest, for the operators in this topic:

| Precedence | Operators |
|---|---|
| 1 | `!` (and unary `-`) |
| 2 | `*` `/` `%` |
| 3 | `+` `-` |
| 4 | `<` `<=` `>` `>=` |
| 5 | `==` `!=` |
| 6 | `&&` |
| 7 | `\|\|` |
| 8 | `?:` |
| 9 | `=` `+=` `-=` ... |

So `a + 1 > b && c == d || e` means `(((a + 1) > b) && (c == d)) || e`.

`&&` binds tighter than `||`. Problem C's conditions are `(X && Y) || (Z && W)`. The parentheses aren't strictly needed, but they make the intent obvious. When in doubt, add parentheses.

### 11. Validating input

Check input **before** using it, and stop early when it is bad. This keeps the main logic simple.

```c
int month, day;

if (scanf("%d %d", &month, &day) != 2) {   // scanf returns how many values it read
    printf("Please enter two numbers.\n");
    return 0;
}
if (month < 1 || month > 12) {
    printf("Invalid month.\n");
    return 0;
}
```

A **lookup array** can replace a long chain of conditions. Problem C uses one for the number of days in each month:

```c
int days_in_month[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
if (day < 1 || day > days_in_month[month]) { /* invalid */ }
```

The extra `0` at index 0 lets `month` (1–12) be used directly as the index.

### 12. Common patterns

**Even or odd**

```c
if (n % 2 == 0) printf("Even\n");
else            printf("Odd\n");
```

**Divisible by**

```c
if (n % 3 == 0 && n % 5 == 0) printf("FizzBuzz\n");
```

**Leap year**

```c
if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    printf("Leap year\n");
```

**Largest of three**

```c
int max = a;
if (b > max) max = b;
if (c > max) max = c;
```

**Sign of a number**

```c
if (n > 0)      printf("Positive\n");
else if (n < 0) printf("Negative\n");
else            printf("Zero\n");
```

**Character category**

```c
if (ch >= 'A' && ch <= 'Z')      printf("Uppercase\n");
else if (ch >= 'a' && ch <= 'z') printf("Lowercase\n");
else if (ch >= '0' && ch <= '9') printf("Digit\n");
else                             printf("Other\n");
```

**Menu with `switch`**

```c
switch (choice) {
    case 1: printf("Start\n"); break;
    case 2: printf("Settings\n"); break;
    case 3: printf("Quit\n"); break;
    default: printf("Invalid choice\n");
}
```

### 13. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| `if (x = 5)` | Assigns 5 to `x`, and the condition is always true | `if (x == 5)` |
| `if (x > 0);` | The `;` ends the `if`; the block below always runs | Remove the semicolon |
| `if (1 <= x <= 12)` | Evaluates `(1 <= x)` to 0 or 1, then compares that to 12: always true | `if (x >= 1 && x <= 12)` |
| Missing braces on a multi-line body | Only the first line is controlled by the `if` | Always use `{ }` |
| Wrong `else if` order | An earlier, broader condition catches values meant for later branches | Order from most to least specific |
| Gaps or overlaps at boundaries (`< 7.5` then `> 7.5`) | `7.5` matches no branch, or two | Use `<` in one and `>=` in the next, or rely on `else if` order |
| Forgetting `break` in `switch` | Execution falls into the next case | Add `break` to each case |
| `switch` on a `float` or a string | Compile error | Use `else if` (and `strcmp` for strings) |
| `if (f == 0.1)` with a `float` | Floating-point values are approximate, so this can be false | Compare against a range, or use `fabs(f - 0.1) < 1e-6` |
| `if (x == 1 \|\| 2)` | `2` is always true, so the whole condition is true | `if (x == 1 \|\| x == 2)` |
| Dangling `else` | `else` attaches to the nearest `if`, not the one you meant | Use braces |

---

## Quick Reference

```c
if (condition) {
    ...
} else if (other) {
    ...
} else {
    ...
}

switch (intExpr) {
    case CONST1: ...; break;
    case CONST2: case CONST3: ...; break;
    default: ...;
}

result = condition ? valueIfTrue : valueIfFalse;
```

| I want to... | Use |
|---|---|
| Check equality | `==` (not `=`) |
| Require both conditions | `&&` |
| Accept either condition | `\|\|` |
| Negate a condition | `!` |
| Check a range | `x >= low && x <= high` |
| Pick between many exact integer values | `switch` |
| Pick between ranges | `else if` chain |
| Pick between two values inline | `? :` |
| Make sure `scanf` worked | `if (scanf(...) != expectedCount)` |
