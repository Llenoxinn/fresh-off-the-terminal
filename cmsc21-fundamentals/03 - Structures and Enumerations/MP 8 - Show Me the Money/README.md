# MP 8: Show me the money!

CMSC 21 machine problem on **structures, enumerations and multi-file programs**: a small **bank simulation** that keeps a list of accounts in a structure and supports opening, closing, depositing and withdrawing, split across a header file, an implementation file and a `main` file.

## Contents

- [Source Files](#source-files)
- [Problem](#problem)
  - [Transactions](#transactions)
  - [Required functions](#required-functions)
  - [Files](#files)
  - [Input](#input)
  - [Output](#output)
  - [Rules](#rules)
- [Sample](#sample)
- [Startup Files](#startup-files)
  - [`bank.h`](#bankh)
  - [`bank.c`](#bankc)
  - [`main.c`](#mainc)
- [Approach](#approach)
  - [The structures](#the-structures)
  - [Generating account numbers](#generating-account-numbers)
  - [Each function](#each-function)
  - [`main`](#main)
- [Multi-File Programs](#multi-file-programs)
- [Notes on the Startup Files and Sample](#notes-on-the-startup-files-and-sample)
- [Testing Checklist](#testing-checklist)

---

## Source Files

| File | Description |
|---|---|
| [bank.h](bank.h) | The `account` and `list` structures, the enumerations, and the function declarations |
| [bank.c](bank.c) | The function definitions |
| [main.c](main.c) | Reads the transactions and processes them |

```bash
gcc -Wall -o bank main.c bank.c
./bank < input.txt
```

---

## Problem

Maintain a list of bank accounts in a `list` structure, defined in [`bank.h`](#bankh).

### Transactions

| Code | Transaction | Input after the code |
|---|---|---|
| `1` | **Open** an account | first name, middle name, last name, account type (`0` savings, `1` checking), opening balance |
| `2` | **Close** an account | account number |
| `3` | **Deposit** | account number, amount |
| `4` | **Withdraw** | account number, amount |

When opening an account:

- The **name** is read from standard input **in `main`** and stored in an `account` structure.
- The **account number** is **auto-generated**. The first account gets number **1**, and numbers must **never repeat**.

### Required functions

All declared in `bank.h` and defined in `bank.c`:

| Function | Purpose |
|---|---|
| `initList` | Initialize the list (empty) |
| `openAccount` | Add an account |
| `closeAccount` | Remove an account from the bank |
| `deposit` | Add money to an account |
| `withdraw` | Take money from an account |
| `display` | Print every account in the bank |
| `search` | Find whether an account with a given number exists |

### Files

| File | Contents |
|---|---|
| `bank.h` | The `account` and `list` structures, the enumerations, and the function **declarations** |
| `bank.c` | The function **definitions** |
| `main.c` | Reads the input and processes the transactions |

### Input

```
t                         number of test cases (transactions)
── each transaction ──
code                      1, 2, 3 or 4
...                       the data for that transaction (see the table above)
```

### Output

After **each** transaction, display the current list of accounts, followed by a line of dashes. Print error messages **before** the list.

Each account is shown as:

```
Account Number: <number>
Name: <first> <middle> <last>
Account Type: <Savings Account | Checking Account>
Balance: <balance with 2 decimals>
```

### Rules

| Transaction | Check | Message if the check fails |
|---|---|---|
| Open | No duplicate account numbers | – |
| Close | The account exists | `No such account exists.` |
| Deposit | The account exists | `No such account exists.` |
| Withdraw | The account exists | `No such account exists.` |
| Withdraw | The balance covers the amount | `No sufficient funds.` |

---

## Sample

**Input**

```
6
1
Judy Ann Santos
0
5000
1
Ryan Loric Agoncillo
0
20000
1
Alexandra Maniego Eala
0
3000
1
Leylah Exevea Fernandez
1
100000
3
10 1000
4
0 1000
```

| # | Transaction | Result |
|---|---|---|
| 1 | Open: Judy Ann Santos, savings, 5000 | Account **1** |
| 2 | Open: Ryan Loric Agoncillo, savings, 20000 | Account **2** |
| 3 | Open: Alexandra Maniego Eala, savings, 3000 | Account **3** |
| 4 | Open: Leylah Exevea Fernandez, checking, 100000 | Account **4** |
| 5 | Deposit 1000 into account 10 | `No such account exists.` |
| 6 | Withdraw 1000 from account 0 | `No such account exists.` |

**Output**

```
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
------------------------------------
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
Account Number: 2
Name: Ryan Loric Agoncillo
Account Type: Savings Account
Balance: 20000.00
------------------------------------
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
Account Number: 2
Name: Ryan Loric Agoncillo
Account Type: Savings Account
Balance: 20000.00
Account Number: 3
Name: Alexandra Maniego Eala
Account Type: Savings Account
Balance: 3000.00
------------------------------------
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
Account Number: 2
Name: Ryan Loric Agoncillo
Account Type: Savings Account
Balance: 20000.00
Account Number: 3
Name: Alexandra Maniego Eala
Account Type: Savings Account
Balance: 3000.00
Account Number: 4
Name: Leylah Exevea Fernandez
Account Type: Checking Account
Balance: 100000.00
------------------------------------
No such account exists.
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
Account Number: 2
Name: Ryan Loric Agoncillo
Account Type: Savings Account
Balance: 20000.00
Account Number: 3
Name: Alexandra Maniego Eala
Account Type: Savings Account
Balance: 3000.00
Account Number: 4
Name: Leylah Exevea Fernandez
Account Type: Checking Account
Balance: 100000.00
------------------------------------
No such account exists.
Account Number: 1
Name: Judy Ann Santos
Account Type: Savings Account
Balance: 5000.00
Account Number: 2
Name: Ryan Loric Agoncillo
Account Type: Savings Account
Balance: 20000.00
Account Number: 3
Name: Alexandra Maniego Eala
Account Type: Savings Account
Balance: 3000.00
Account Number: 4
Name: Leylah Exevea Fernandez
Account Type: Checking Account
Balance: 100000.00
------------------------------------
```

The separator is **36 dashes**. (The original sample ends with a 37-dash line, which looks like a typo, since every other separator has 36.)

---

## Startup Files

Provided by the instructor. They're reproduced here for reference.

### `bank.h`

```c
typedef enum{
    TRUE = 1,
    FALSE = 0
}boolean;

typedef enum{
    SAVINGS_ACCOUNT,
    CHECKING_ACCOUNT
}accountType;

typedef struct{
    int number;
    accountType type;
    char fname[30],mname[30],lname[30],PIN[7];
    double balance;
    
}account;

typedef struct{
    account accounts[100];
    int size;
}list;

void display(list);
void initList(list*);
boolean openAccount(list*,account);
boolean closeAccount(list*,int);
int search(list*,int);
boolean deposit(list*,int,double);
boolean withdraw(list*,int,double);
```

### `bank.c`

```c
#include "bank.h"
#include <string.h>

void initList(list* l){
    l->size = 0;
}

boolean openAccount(list* l,account acc){
    
}

boolean closeAccount(list* l,int num){
    
}

int search(list* l,int num){
    
}

boolean deposit(list* l,int num, double amt){
    
}

boolean withdraw(list*,int,double){
    
}

void display(list l){
    
}
```

### `main.c`

```c
#include "bank.h"
#include <stdio.h>

//this is where you will implement the "bank simulation"
//in this MP, we implement our very own "library"
//the declarations of the structures needed and operations/functions are found in the header file (bank.h file)
//the implementation of the operations/functions are found in the implementation file (bank.c)
//implement all the needed operations in the bank.c file
//to include user-defined header files, they are enclosed in double quotes instead of the angle brackets

int main(){
    
    return 0;
}
```

---

## Approach

### The structures

```
list
├── accounts[100]   ← an array of account structures
│     ├── [0]  { number, type, fname, mname, lname, PIN, balance }
│     ├── [1]  { ... }
│     └── ...
└── size            ← how many of the 100 slots are in use
```

| Type | Kind | Role |
|---|---|---|
| `boolean` | enum | `TRUE` / `FALSE` results for the transaction functions |
| `accountType` | enum | `SAVINGS_ACCOUNT` (0) or `CHECKING_ACCOUNT` (1), matching the input codes |
| `account` | struct | One account. `PIN` isn't used by this MP |
| `list` | struct | The bank: up to 100 accounts plus a count |

This is an **array-based list**: the accounts sit in `accounts[0]` to `accounts[size - 1]`, with no gaps.

### Generating account numbers

"Based on size" suggests `size + 1`. That works until an account is **closed**:

| Step | Accounts | `size` | `size + 1` | Problem |
|---|---|---|---|---|
| Open, open | 1, 2 | 2 | – | |
| Close 1 | 2 | 1 | – | |
| Open | 2, **2** | 1 | **2** | Duplicate |

Since new accounts are always added at the end and the list stays in order, **one more than the last account's number** is always unique:

```c
acc.number = (l->size == 0) ? 1 : l->accounts[l->size - 1].number + 1;
```

| Step | Accounts | Next number |
|---|---|---|
| Open, open | 1, 2 | 3 |
| Close 1 | 2 | 3 |
| Open | 2, **3** | 4 |

Edge case: if the **last** account is closed, its number can come back (open 1, 2, close 2, open → 2 again). The number 2 then belongs to nobody else, so it's still never a duplicate. If numbers must never be reused at all, keep a separate counter in `main` that only goes up.

### Each function

**`search`:** return the **index** of the account with that number, or **−1** if there isn't one. The other functions all build on it.

```c
int search(list* l, int num) {
    for (int i = 0; i < l->size; i++)
        if (l->accounts[i].number == num)
            return i;
    return -1;
}
```

**`openAccount`:** refuse if all 100 slots are used. Otherwise assign the number and add the account at index `size`.

```c
boolean openAccount(list* l, account acc) {
    if (l->size == 100) return FALSE;
    acc.number = (l->size == 0) ? 1 : l->accounts[l->size - 1].number + 1;
    l->accounts[l->size] = acc;      // structures can be copied with =
    l->size++;
    return TRUE;
}
```

**`closeAccount`:** find it, then **shift every later account one slot left** to close the gap.

```c
boolean closeAccount(list* l, int num) {
    int i = search(l, num);
    if (i == -1) return FALSE;
    for (; i < l->size - 1; i++)
        l->accounts[i] = l->accounts[i + 1];
    l->size--;
    return TRUE;
}
```

**`deposit` and `withdraw`:** find the account, then change its balance. `withdraw` also checks the funds.

```c
boolean withdraw(list* l, int num, double amt) {
    int i = search(l, num);
    if (i == -1 || l->accounts[i].balance < amt) return FALSE;
    l->accounts[i].balance -= amt;
    return TRUE;
}
```

`withdraw` returns `FALSE` for **two** different reasons, but each needs its own message. Have `main` call `search` first to tell them apart:

```c
if (search(&bank, num) == -1)
    printf("No such account exists.\n");
else if (!withdraw(&bank, num, amt))
    printf("No sufficient funds.\n");
```

**`display`:** print each account, then the separator. It receives the list **by value** (`list l`), so it uses `.`; the others receive a **pointer** (`list* l`), so they use `->`.

```c
void display(list l) {
    for (int i = 0; i < l.size; i++) {
        account a = l.accounts[i];
        printf("Account Number: %d\n", a.number);
        printf("Name: %s %s %s\n", a.fname, a.mname, a.lname);
        printf("Account Type: %s\n", a.type == SAVINGS_ACCOUNT ? "Savings Account" : "Checking Account");
        printf("Balance: %.2f\n", a.balance);
    }
    printf("------------------------------------\n");
}
```

### `main`

```c
int main() {
    list bank;
    initList(&bank);

    int t;
    scanf("%d", &t);
    while (t--) {
        int code;
        scanf("%d", &code);

        if (code == 1) {
            account acc;
            int type;
            scanf("%29s %29s %29s %d %lf", acc.fname, acc.mname, acc.lname, &type, &acc.balance);
            acc.type = (accountType) type;
            openAccount(&bank, acc);
        }
        else if (code == 2) { ... closeAccount ... }
        else if (code == 3) { ... deposit ... }
        else if (code == 4) { ... search, then withdraw ... }

        display(bank);
    }
    return 0;
}
```

- `%29s` reads one word, at most 29 characters, leaving room for `'\0'` in `char[30]`. The three name parts are on one line, separated by spaces, so three `%s` read them in order.
- `%lf` reads a `double` with `scanf`. (`printf` uses `%f` for both `float` and `double`.)
- The account type is read into an `int`, then cast to the enum.
- `display(bank)` copies the whole list (100 accounts, about 11 KB) for every call. That's fine here, but `display(const list *l)` would avoid the copy. The startup file fixes the signature as `display(list)`.

---

## Multi-File Programs

This MP builds its own small **library**: an interface (`bank.h`) and an implementation (`bank.c`), used by a program (`main.c`).

| Piece | Holds | Included / compiled |
|---|---|---|
| Header `bank.h` | Types and function **declarations** (what exists) | `#include "bank.h"` in both `.c` files |
| `bank.c` | Function **definitions** (how it works) | Compiled |
| `main.c` | The program that uses the library | Compiled |

**`"bank.h"` vs. `<stdio.h>`:** double quotes search the **current folder** first, for your own headers. Angle brackets search the **system** include folders, for the standard library.

**Compiling:** both `.c` files go to the compiler together, and the header is **not** listed:

```bash
gcc -Wall -o bank main.c bank.c
./bank < input.txt
```

Compiling only `main.c` fails at the **linking** stage with errors like `undefined reference to 'openAccount'`. `main.c` knows the function exists (from the header), but its code is in `bank.c`.

**Include guards:** the startup header has none. That's fine while each `.c` file includes it once. If a header might be included twice (directly and through another header), wrap it so the second inclusion is skipped:

```c
#ifndef BANK_H
#define BANK_H
/* ... contents of bank.h ... */
#endif
```

---

## Notes on the Startup Files and Sample

| Item | Note |
|---|---|
| `boolean withdraw(list*,int,double){` in `bank.c` | A **definition** with no parameter names. Standard C only allows this from C23 on, and even then the function can't use its parameters. Name them: `withdraw(list* l, int num, double amt)` |
| Empty function bodies | A non-`void` function that falls off the end without `return` returns garbage. Fill in every one before testing |
| `bank.c` includes `<string.h>` but not `<stdio.h>` | `display` needs `printf`, so add `#include <stdio.h>` to `bank.c` |
| `PIN[7]` | Part of the structure, but not used by this MP |
| Separator length | 36 dashes. The sample's final separator has 37, which looks like a typo |
| `4 ` with a trailing space in the sample input | Harmless: `scanf("%d")` skips whitespace |
| Empty bank | `display` prints only the separator |
| `bank.h` has no include guards | Fine here; see [Include guards](#multi-file-programs) |

---

## Testing Checklist

| Scenario | Input transactions | Expected |
|---|---|---|
| The sample | 4 opens, deposit to #10, withdraw from #0 | Accounts 1–4, two `No such account exists.` |
| Valid deposit | open (5000), `3` / `1 1000` | Balance `6000.00` |
| Valid withdrawal | open (5000), `4` / `1 1000` | Balance `4000.00` |
| Insufficient funds | open (5000), `4` / `1 9000` | `No sufficient funds.`, balance unchanged |
| Withdraw everything | open (5000), `4` / `1 5000` | Balance `0.00` (allowed: `5000 < 5000` is false) |
| Close an account | open ×3, `2` / `2` | Accounts 1 and 3 remain, in order |
| Close a missing account | `2` / `7` | `No such account exists.` |
| No duplicate numbers | open, open, close `1`, open | Accounts **2** and **3** |
| Close everything | open, close `1` | Only the separator is printed |
| Checking account | open with type `1` | `Account Type: Checking Account` |
