# 06 - Linked Lists

CMSC 21 machine problems on **linked lists**, followed by a reference covering everything you need to know about building and using linked lists in C.

## Contents

- [Machine Problems](#machine-problems)
- [Linked Lists in C](#linked-lists-in-c)
  1. [What a linked list is](#1-what-a-linked-list-is)
  2. [The node structure](#2-the-node-structure)
  3. [Creating nodes](#3-creating-nodes)
  4. [Traversing](#4-traversing)
  5. [Inserting](#5-inserting)
  6. [Removing](#6-removing)
  7. [Searching](#7-searching)
  8. [Pointer-to-pointer: one case for everything](#8-pointer-to-pointer-one-case-for-everything)
  9. [Keeping a list sorted](#9-keeping-a-list-sorted)
  10. [Freeing a list](#10-freeing-a-list)
  11. [Doubly linked lists](#11-doubly-linked-lists)
  12. [Linked list vs. array](#12-linked-list-vs-array)
  13. [Common mistakes](#13-common-mistakes)
- [Quick Reference](#quick-reference)

---

## Machine Problems

| Problem | Folder | Concepts |
|---|---|---|
| MP 10: The Polynomial has many Faces | [MP 10 - The Polynomial has many Faces](MP%2010%20-%20The%20Polynomial%20has%20many%20Faces/) | A polynomial as a list of terms; simplify, add, subtract, multiply; sorted insertion |
| MP 11: I am, first and foremost, a STUDENT | [MP 11 - First and Foremost a Student](MP%2011%20-%20First%20and%20Foremost%20a%20Student/) | A class list of student records; insert at a position, remove, search, edit, filter |

---

## Linked Lists in C

### 1. What a linked list is

A **linked list** stores items in separate **nodes** scattered around memory. Each node holds its data and a **pointer to the next node**. The last node points to `NULL`.

```
head
 │
 ▼
[ 7 | ●]──►[ 3 | ●]──►[ 4 | ●]──► NULL
  data next
```

The list itself is just a pointer to the first node, the **head**. An empty list has `head == NULL`.

### 2. The node structure

```c
typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct {
    node *head;
    int size;           // optional, but handy
} list;
```

The node refers to its own type, so it needs a **struct tag** (`struct node`): the `typedef` name `node` doesn't exist yet inside the braces.

The data can be anything: a term (`coef`, `exp`) in MP 10, a whole `student` structure in MP 11.

### 3. Creating nodes

Nodes live on the **heap**, so they survive after the function that made them returns:

```c
node *newNode(int value) {
    node *n = malloc(sizeof(node));
    n->data = value;
    n->next = NULL;
    return n;
}
```

### 4. Traversing

Follow the `next` pointers until `NULL`, using a **separate** pointer so `head` is never lost:

```c
for (node *cur = l->head; cur != NULL; cur = cur->next)
    printf("%d ", cur->data);
```

There's no `l[i]`. Reaching the `i`-th item means walking `i` nodes.

### 5. Inserting

**At the front:** O(1).

```c
node *n = newNode(x);
n->next = l->head;
l->head = n;
```

**After a given node `prev`:** O(1) once you have `prev`.

```c
node *n = newNode(x);
n->next = prev->next;     // 1. new node points to what came after prev
prev->next = n;           // 2. prev points to the new node
```

The **order matters**: doing step 2 first would lose the rest of the list.

```
before:  [prev]──────────►[B]
after:   [prev]──►[ n ]──►[B]
```

**At position `p`:** walk to the node at `p − 1`, then insert after it. Position 0 is the front, a special case unless you use [section 8](#8-pointer-to-pointer-one-case-for-everything).

**At the end:** walk to the last node (`cur->next == NULL`), or keep a `tail` pointer for O(1) appends.

### 6. Removing

Removing a node means making its **predecessor** skip over it, then freeing it:

```c
// remove the node after prev
node *dead = prev->next;
prev->next = dead->next;
free(dead);
```

```
before:  [prev]──►[dead]──►[B]
after:   [prev]──────────►[B]        (dead freed)
```

Removing the **head** is a special case: `l->head = l->head->next;`.

### 7. Searching

```c
node *find(list *l, int value) {
    for (node *cur = l->head; cur != NULL; cur = cur->next)
        if (cur->data == value)
            return cur;
    return NULL;               // not found
}
```

For strings (student numbers, programs), compare with `strcmp(...) == 0`, never `==`.

### 8. Pointer-to-pointer: one case for everything

Inserting or removing at the head needs different code from the middle, because the head is changed through `l->head`, and the middle through `prev->next`. A **pointer to the link** removes the difference:

```c
node **pp = &l->head;          // points at the link we might change
while (*pp != NULL && (*pp)->data != value)
    pp = &(*pp)->next;         // move to the next link

if (*pp != NULL) {             // found: remove it
    node *dead = *pp;
    *pp = dead->next;          // re-link, whether pp is &head or &prev->next
    free(dead);
}
```

`*pp` is "whatever link currently points at this node". Assigning to it re-links the list at that spot, so the head needs no special code. MP 10's sorted insert and MP 11's insert and remove use this pattern.

### 9. Keeping a list sorted

Insert each item **before the first node that should come after it**:

```c
void insertSorted(list *l, int x) {          // ascending
    node **pp = &l->head;
    while (*pp != NULL && (*pp)->data < x)
        pp = &(*pp)->next;
    node *n = newNode(x);
    n->next = *pp;
    *pp = n;
}
```

MP 10 does this by **decreasing exponent**, and **merges** a term into an existing node when the exponents are equal. That way the polynomial is always sorted and simplified, with no separate sort step.

Sorting an existing list: the simplest way is a bubble sort that **swaps the data** between neighboring nodes and leaves the links alone. Merge sort is the efficient choice for long lists.

### 10. Freeing a list

Save `next` **before** freeing each node:

```c
void destroy(list *l) {
    node *cur = l->head;
    while (cur != NULL) {
        node *next = cur->next;    // read it while cur is still valid
        free(cur);
        cur = next;
    }
    l->head = NULL;
    l->size = 0;
}
```

Free each test case's lists before the next one, or memory keeps growing.

### 11. Doubly linked lists

Each node also points **back**:

```c
typedef struct dnode {
    int data;
    struct dnode *prev, *next;
} dnode;
```

```
NULL◄──[ 7 ]◄═►[ 3 ]◄═►[ 4 ]──►NULL
```

| | Singly linked | Doubly linked |
|---|---|---|
| Walk backwards | No | Yes |
| Remove a node you have a pointer to | Need its predecessor | Directly: `n->prev->next = n->next; n->next->prev = n->prev;` |
| Pointers to update on insert | 2 | 4 |
| Memory per node | Less | One extra pointer |

Keeping both a `head` and a `tail` pointer gives O(1) inserts and removals at **both** ends.

### 12. Linked list vs. array

| Operation | Array / vector | Linked list |
|---|---|---|
| Access the `i`-th item | **O(1)** | O(n): walk `i` nodes |
| Insert/remove at the front | O(n): shift everything | **O(1)** |
| Insert/remove in the middle (once you're there) | O(n): shift | **O(1)**: re-link |
| Append | O(1) amortized | O(1) with a tail pointer |
| Memory | Compact, contiguous | Extra pointer per node, scattered |
| Size | Fixed, or resize with `realloc` | Grows one node at a time |
| Binary search | Yes (if sorted) | No |

Choose a **linked list** when items are inserted and removed often and accessed in order, as with polynomial terms and class lists. Choose an **array** when you need fast access by position.

### 13. Common mistakes

| Mistake | What happens | Fix |
|---|---|---|
| Moving `head` while traversing | The front of the list is lost | Traverse with a separate `cur` |
| Following `cur->next` without checking `cur` | Crash on `NULL` | Check `cur != NULL` (and `cur->next != NULL` when looking ahead) |
| Linking in the wrong order on insert | The rest of the list is lost | Set `n->next` **before** `prev->next` |
| Forgetting the head case | Inserting or removing at position 0 fails | Special-case it, or use a pointer-to-pointer |
| Using a node after `free` | Undefined behavior | Save `next` first |
| New last node without `next = NULL` | The list "continues" into garbage | Set `next = NULL` when creating nodes |
| Comparing strings with `==` | Never matches | `strcmp(a, b) == 0` |
| Not freeing lists | Memory leak | Free every node |

---

## Quick Reference

```c
typedef struct node { int data; struct node *next; } node;

node *n = malloc(sizeof(node));          // create
n->data = x; n->next = NULL;

n->next = head; head = n;                // insert at front

for (node *c = head; c; c = c->next)     // traverse
    ...;

node **pp = &head;                       // find the link to change
while (*pp && (*pp)->data != x) pp = &(*pp)->next;
if (*pp) { node *d = *pp; *pp = d->next; free(d); }   // remove

while (head) { node *nx = head->next; free(head); head = nx; }   // free all
```

| I want to... | Do |
|---|---|
| Add to the front | `n->next = head; head = n;` |
| Add after `p` | `n->next = p->next; p->next = n;` |
| Remove after `p` | `d = p->next; p->next = d->next; free(d);` |
| Handle the head and middle the same way | Use `node **pp` |
| Keep it sorted | Insert before the first larger item |
| Walk backwards | Use a doubly linked list |
