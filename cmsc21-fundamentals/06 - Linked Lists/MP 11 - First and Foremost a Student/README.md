# MP 11: I am, first and foremost, a STUDENT

CMSC 21 machine problem on **linked lists**: keep a class list of students in a singly or doubly linked list, and support inserting, removing, looking up, editing and filtering students.

It's the linked-list version of [MP 8: Show me the money!](../../03%20-%20Structures%20and%20Enumerations/MP%208%20-%20Show%20Me%20the%20Money/), which kept bank accounts in an array-based list.

## Contents

- [Problem](#problem)
  - [Student information](#student-information)
  - [Input](#input)
  - [Operations](#operations)
  - [Output](#output)
- [Sample](#sample)
- [Reading the Sample Input](#reading-the-sample-input)
- [Sample Walkthrough](#sample-walkthrough)
- [What the Statement Leaves Open](#what-the-statement-leaves-open)
- [Approach](#approach)
  - [The structures](#the-structures)
  - [Reading text with spaces](#reading-text-with-spaces)
  - [Each operation](#each-operation)
  - [Comparing strings](#comparing-strings)
- [Singly vs. Doubly Linked](#singly-vs-doubly-linked)
- [Edge Cases](#edge-cases)

---

## Problem

### Student information

| Field | Example | Note |
|---|---|---|
| Student number | `1997-12345` | Contains a `-`, so store it as a **string**, not an `int` |
| First name | `Judy` | |
| Middle name | `Ann` | |
| Last name | `Santos` | |
| Program | `BS Culinary Arts` | Contains **spaces** |
| Year level | `3` | |

### Input

```
t                         number of students to enroll
── t times ──
student number
first middle last
program
year level
── then ──
k                         number of additional operations
── k operations ──
```

### Operations

| Code | Operation | Additional input |
|---|---|---|
| 1 | **Insert** a student at a position | a full student record (4 lines), then the position |
| 2 | **Remove** a student | student number |
| 3 | **Access** a student's information | student number |
| 4 | **Edit** a student's information | student number, then `1` (program) or `2` (year level) |
| 5 | **Display** all students in a program | program |
| 6 | **Display** all students in a year level | year level |

### Output

- After operations **1 to 4**, display the **entire class list**.
- Operations **5 and 6** display only the matching students.
- Each list ends with a separator of **36 dashes**.

Each student is shown as:

```
Student Number: <number>
Name: <first> <middle> <last>
Program: <program>
Year Level: <year>
```

---

## Sample

**Input**

```
3
1997-12345
Judy Ann Santos
BS Culinary Arts
3
1998-50000
Ryan Loric Agoncillo
BS Management
4
2021-20000
Alexandra Maniego Eala
BS Sports Science
1
5
1
2019-98765
Leylah Exevea Fernandez
BS Sports Science
1
2
2 1998-50000
3 1998-50000
5 BS Sports Science
6 1
```

**Output**

```
Student Number: 1997-12345
Name: Judy Ann Santos
Program: BS Culinary Arts
Year Level: 3
Student Number: 1998-50000
Name: Ryan Loric Agoncillo
Program: BS Management
Year Level: 4
Student Number: 2019-98765
Name: Leylah Exevea Fernandez
Program: BS Sports Science
Year Level: 1
Student Number: 2021-20000
Name: Alexandra Maniego Eala
Program: BS Sports Science
Year Level: 1
------------------------------------
Student Number: 1997-12345
Name: Judy Ann Santos
Program: BS Culinary Arts
Year Level: 3
Student Number: 2019-98765
Name: Leylah Exevea Fernandez
Program: BS Sports Science
Year Level: 1
Student Number: 2021-20000
Name: Alexandra Maniego Eala
Program: BS Sports Science
Year Level: 1
------------------------------------
Student not enrolled.
Student Number: 1997-12345
Name: Judy Ann Santos
Program: BS Culinary Arts
Year Level: 3
Student Number: 2019-98765
Name: Leylah Exevea Fernandez
Program: BS Sports Science
Year Level: 1
Student Number: 2021-20000
Name: Alexandra Maniego Eala
Program: BS Sports Science
Year Level: 1
------------------------------------
Student Number: 2019-98765
Name: Leylah Exevea Fernandez
Program: BS Sports Science
Year Level: 1
Student Number: 2021-20000
Name: Alexandra Maniego Eala
Program: BS Sports Science
Year Level: 1
------------------------------------
Student Number: 2019-98765
Name: Leylah Exevea Fernandez
Program: BS Sports Science
Year Level: 1
Student Number: 2021-20000
Name: Alexandra Maniego Eala
Program: BS Sports Science
Year Level: 1
------------------------------------
```

---

## Reading the Sample Input

The input is easy to misread, because the operation lines run straight on from the student records:

```
3                         ← 3 students
1997-12345                ┐
Judy Ann Santos           │ student 1
BS Culinary Arts          │
3                         ┘ (year level)
1998-50000                ┐
Ryan Loric Agoncillo      │ student 2
BS Management             │
4                         ┘
2021-20000                ┐
Alexandra Maniego Eala    │ student 3
BS Sports Science         │
1                         ┘ ← Alexandra's year level, not an operation
5                         ← 5 operations follow
1                         ← op 1: insert
2019-98765                ┐
Leylah Exevea Fernandez   │ the new student
BS Sports Science         │
1                         ┘
2                         ← at position 2
2 1998-50000              ← op 2: remove
3 1998-50000              ← op 3: access
5 BS Sports Science       ← op 5: by program
6 1                       ← op 6: by year level
```

---

## Sample Walkthrough

| # | Operation | Class list after | Printed |
|---|---|---|---|
| start | – | Judy, Ryan, Alexandra | *(nothing)* |
| 1 | Insert Leylah at position **2** | Judy, Ryan, **Leylah**, Alexandra | the whole list |
| 2 | Remove `1998-50000` | Judy, Leylah, Alexandra | the whole list |
| 3 | Access `1998-50000` | *(unchanged)* | `Student not enrolled.`, then the whole list |
| 5 | Program `BS Sports Science` | *(unchanged)* | Leylah, Alexandra |
| 6 | Year level `1` | *(unchanged)* | Leylah, Alexandra |

What the sample confirms:

- **Positions start at 0.** Position 2 puts Leylah **third**, after Judy (0) and Ryan (1).
- **Not found** prints `Student not enrolled.` **before** the list, and the list is still displayed.
- Operations 5 and 6 also end with the separator, even though they don't print the whole list.
- An operation and its argument share a line (`2 1998-50000`), except op 1, whose student record spans the following lines.

---

## What the Statement Leaves Open

| Question | Notes |
|---|---|
| Op 3 output when the student **is** found | Not shown. Following "display the entire class list" for ops 1–4, print the list. Printing the student's record first is also reasonable |
| Op 4 input format | Only "student number, then 1 (program) or 2 (year level)" is given. Presumably the **new value** comes next: a program line, or a year number |
| Op 2 or 4 with an unknown student number | Not shown. `Student not enrolled.` (as in op 3), then the list |
| Insert at an invalid position (negative, or past the end) | Not specified. Inserting at the end, or rejecting the insert, are both reasonable |
| Op 5 or 6 with no matches | Probably just the separator |
| Op 6's argument | The operation list doesn't mention it, but the sample (`6 1`) shows it takes a year level |
| Duplicate student numbers | Not specified |

---

## Approach

### The structures

```c
typedef struct {
    char number[20];
    char first[30], middle[30], last[30];
    char program[60];
    int  year;
} student;

typedef struct node {
    student data;
    struct node *next;
} node;

typedef struct {
    node *head;
    int size;
} list;
```

Keeping `student` separate from `node` means the student data can be read, passed and copied without dragging the link along, the same way `account` and `list` were separate in MP 8.

### Reading text with spaces

The fields mix **single words** (student number), **three words** (the name) and **any number of words** (the program). Reading **line by line** with `fgets` handles all of them:

```c
void readLine(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\r\n")] = '\0';        // strip the newline (and \r on Windows)
}

student readStudent(void) {
    student s;
    char line[200];
    readLine(s.number, sizeof s.number);
    readLine(line, sizeof line);
    sscanf(line, "%29s %29s %29s", s.first, s.middle, s.last);
    readLine(s.program, sizeof s.program);    // keeps the spaces: "BS Sports Science"
    readLine(line, sizeof line);
    s.year = atoi(line);
    return s;
}
```

For the operation lines, read the whole line, then split off the code:

```c
char line[200], arg[160] = "";
int op;
readLine(line, sizeof line);
sscanf(line, "%d %159[^\n]", &op, arg);       // "5 BS Sports Science" → op 5, arg "BS Sports Science"
```

`%[^\n]` reads **everything up to the newline**, spaces included, which `%s` can't do.

**Don't mix `scanf("%d")` and `fgets` carelessly.** `scanf` leaves the newline behind, and the next `fgets` reads an empty line. Reading every line with `fgets` (and converting numbers with `atoi` or `sscanf`) avoids the problem entirely.

### Each operation

**Insert at position `p`:** walk to the link that should point to the new node, then splice it in. With a pointer-to-pointer, position 0 (the head) needs no special case:

```c
void insertAt(list *l, student s, int p) {
    node *n = malloc(sizeof(node));
    n->data = s;

    node **pp = &l->head;
    while (p > 0 && *pp != NULL) {             // stops at the end if p is too big
        pp = &(*pp)->next;
        p--;
    }
    n->next = *pp;
    *pp = n;
    l->size++;
}
```

```
insert Leylah at position 2:

head ─► [Judy] ─► [Ryan] ─► [Alexandra] ─► NULL
                        ╲                ╱
                         ─► [Leylah] ───
```

**Search** by student number, returning the node (or `NULL`):

```c
node *search(list *l, const char *number) {
    for (node *n = l->head; n != NULL; n = n->next)
        if (strcmp(n->data.number, number) == 0)
            return n;
    return NULL;
}
```

**Remove** by student number: find the link pointing to the node, re-link around it, free it.

```c
int removeStudent(list *l, const char *number) {
    node **pp = &l->head;
    while (*pp != NULL && strcmp((*pp)->data.number, number) != 0)
        pp = &(*pp)->next;
    if (*pp == NULL) return 0;                 // not enrolled

    node *dead = *pp;
    *pp = dead->next;
    free(dead);
    l->size--;
    return 1;
}
```

**Edit:** `search`, then overwrite `program` (with `strcpy`) or `year`.

**Display all / by program / by year:** one traversal, printing every node or only those that match, then the separator.

```c
void displayStudent(student s) {
    printf("Student Number: %s\n", s.number);
    printf("Name: %s %s %s\n", s.first, s.middle, s.last);
    printf("Program: %s\n", s.program);
    printf("Year Level: %d\n", s.year);
}

void displayByProgram(list l, const char *program) {
    for (node *n = l.head; n != NULL; n = n->next)
        if (strcmp(n->data.program, program) == 0)
            displayStudent(n->data);
    printf("------------------------------------\n");
}
```

### Comparing strings

Student numbers and programs are strings, so compare them with `strcmp`, never `==`:

| Code | Compares |
|---|---|
| `a == b` | The **addresses** of the two arrays: almost always false |
| `strcmp(a, b) == 0` | The **contents**: true when the text is identical |

`strcmp` is case-sensitive and exact, so `"BS Sports Science"` doesn't match `"BS Sports Science "` (trailing space) or `"bs sports science"`. Stripping the newline (and any `\r`) from every line read keeps comparisons reliable.

---

## Singly vs. Doubly Linked

The statement allows either.

| | Singly linked | Doubly linked |
|---|---|---|
| Node | `data`, `next` | `data`, `next`, `prev` |
| Remove a node | Needs the node **before** it (or a pointer-to-pointer, as above) | Can unlink a node directly: `n->prev->next = n->next; n->next->prev = n->prev;` |
| Walk backwards | No | Yes |
| Pointers to update on insert | 2 | 4 |
| Memory per node | Less | One extra pointer |

For this MP, singly linked is enough: every operation walks forward from the head.

---

## Edge Cases

| Case | Expected |
|---|---|
| Insert at position 0 | The new student becomes the head |
| Insert at position `size` | Appended at the end |
| Remove the first student | `head` moves to the second node |
| Remove the last remaining student | `head` becomes `NULL`; the list prints only the separator |
| Remove or access an unknown number | `Student not enrolled.`, then the list |
| Program filter with extra spaces in the input | Won't match unless lines are read and trimmed consistently |
| Op 5/6 with no matching students | Only the separator |
| `t = 0` | Start with an empty list |
