# MP 6: Tic-Tac, Refreshment to be Shared — But no can do for Tic-Tac-Toe

CMSC 21 machine problem on **2D arrays**: simulate a game of **tic-tac-toe** on a `3 × 3` `char` board, draw the board with box-drawing characters after every move, and detect a **winner** or a **draw**.

## Contents

- [Files](#files)
- [Problem](#problem)
  - [Input](#input)
  - [Output](#output)
- [Sample](#sample)
- [Startup File](#startup-file)
- [Approach](#approach)
  - [The board](#the-board)
  - [Converting input to indices](#converting-input-to-indices)
  - [Whose turn it is](#whose-turn-it-is)
  - [Checking for a winner or a draw](#checking-for-a-winner-or-a-draw)
  - [The main loop](#the-main-loop)
- [Box-Drawing Characters](#box-drawing-characters)
- [Things the Statement Leaves Open](#things-the-statement-leaves-open)
- [Testing Checklist](#testing-checklist)
- [About This Solution](#about-this-solution)

---

## Files

| File | Description |
|---|---|
| [tictactoe.c](tictactoe.c) | Solution: the game loop, `display` from the [startup file](#startup-file), `checkWin` and `checkDraw` |

```bash
gcc -Wall -o tictactoe tictactoe.c
./tictactoe < moves.txt
```

The startup file itself is reproduced [below](#startup-file) only. It isn't a separate file in this folder.

---

## Problem

Simulate tic-tac-toe. The **first player uses `x`**, the **second player uses `o`**.

- **Display the board after each move**, using the `display` function from the [startup file](#startup-file).
- Implement **another function** that checks whether there's a **winner**, a **draw**, or the game **hasn't finished** yet.
- The game ends when someone wins, or in a **draw** once all 9 cells are filled with no winner.

### Input

Multiple lines, each with **two integers from 1 to 3**: the **row** and **column** of the cell the current player takes. Players alternate, starting with player 1 (`x`).

### Output

- After each move: the move, then the board.
- If there's a winner:

  ```
  What a refreshing moment with Player <playerNumber> unleashing their creativity!
  ```

- If there's a draw:

  ```
  Freshest moment! Both players unleashing their creativity!
  ```

> The statement also says: *"In your implementation of the diagonals, generate a random number from negative 1 billion to positive 1 billion. DO NOT PRINT IT."* This is the same line as in [MP 6-mini](../MP%206-mini%20-%202%20Dimensions/), and it appears to have been carried over. If you follow it, generate the number in the function that checks the diagonals for a win, and never print it. See [The random number](../MP%206-mini%20-%202%20Dimensions/#the-random-number) for a version that covers the full range on Windows too.

---

## Sample

**Input**

```
1 1
2 1
1 2
2 2
1 3
```

**Output**

```
1 1
╔═══╦═══╦═══╗
║ x ║   ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╚═══╩═══╩═══╝
2 1
╔═══╦═══╦═══╗
║ x ║   ║   ║
╠═══╬═══╬═══╣
║ o ║   ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╚═══╩═══╩═══╝
1 2
╔═══╦═══╦═══╗
║ x ║ x ║   ║
╠═══╬═══╬═══╣
║ o ║   ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╚═══╩═══╩═══╝
2 2
╔═══╦═══╦═══╗
║ x ║ x ║   ║
╠═══╬═══╬═══╣
║ o ║ o ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╚═══╩═══╩═══╝
1 3
╔═══╦═══╦═══╗
║ x ║ x ║ x ║
╠═══╬═══╬═══╣
║ o ║ o ║   ║
╠═══╬═══╬═══╣
║   ║   ║   ║
╚═══╩═══╩═══╝
What a refreshing moment with Player 1 unleashing their creativity!
```

| Move | Player | Cell | Result |
|---|---|---|---|
| 1 | 1 (`x`) | row 1, col 1 | |
| 2 | 2 (`o`) | row 2, col 1 | |
| 3 | 1 (`x`) | row 1, col 2 | |
| 4 | 2 (`o`) | row 2, col 2 | |
| 5 | 1 (`x`) | row 1, col 3 | **Row 1 complete: Player 1 wins** |

**Note:** each board is preceded by the move (`1 1`, `2 1`, ...). When you type the moves in a terminal, that's just your input showing on screen. But if the input is fed from a file or a checker, it **won't** appear unless the program prints it. To produce the sample output exactly, print the move before each board:

```c
printf("%d %d\n", row, col);
```

---

## Startup File

Provided by the instructor. It draws a board, here filled with a sample diagonal of `x`s:

```c
#include <stdio.h>

void display(char table[3][3]);

int main(){
    char ta[3][3]={{'x',' ',' '},{' ','x',' '},{' ',' ','x'}};
    display(ta);
}

void display(char table[3][3]){
    //201 203 187 188 185 204 205 206 186
    printf("╔═══╦═══╦═══╗\n");
    printf("║ %c ║ %c ║ %c ║\n",table[0][0],table[0][1],table[0][2]);
    printf("╠═══╬═══╬═══╣\n");
    printf("║ %c ║ %c ║ %c ║\n",table[1][0],table[1][1],table[1][2]);
    printf("╠═══╬═══╬═══╣\n");
    printf("║ %c ║ %c ║ %c ║\n",table[2][0],table[2][1],table[2][2]);
    printf("╚═══╩═══╩═══╝\n");
}
```

Running it prints:

```
╔═══╦═══╦═══╗
║ x ║   ║   ║
╠═══╬═══╬═══╣
║   ║ x ║   ║
╠═══╬═══╬═══╣
║   ║   ║ x ║
╚═══╩═══╩═══╝
```

`display` is used **as is**. The MP adds the game loop and the win/draw check around it.

---

## Approach

### The board

```c
char board[3][3] = { {' ', ' ', ' '},
                     {' ', ' ', ' '},
                     {' ', ' ', ' '} };
```

Empty cells must hold a **space** `' '`, not `'\0'`. `display` prints each cell with `%c`, and the borders only line up if every cell is exactly one visible-width character.

### Converting input to indices

The input counts from **1**, arrays count from **0**:

```c
board[row - 1][col - 1] = mark;
```

| Input | Index |
|---|---|
| `1 1` (top-left) | `board[0][0]` |
| `2 3` (middle-right) | `board[1][2]` |
| `3 3` (bottom-right) | `board[2][2]` |

### Whose turn it is

Count the moves. Even counts are player 1, odd counts are player 2:

```c
char mark = (moves % 2 == 0) ? 'x' : 'o';
int player = (moves % 2 == 0) ? 1 : 2;
```

### Checking for a winner or a draw

There are **8 winning lines**: 3 rows, 3 columns, 2 diagonals. A line wins if its three cells are equal **and not empty**.

```
rows        columns       diagonals
■ ■ ■       ■ · ·         ■ · ·     · · ■
· · ·       ■ · ·         · ■ ·     · ■ ·
· · ·       ■ · ·         · · ■     ■ · ·
```

One function returning a status code covers all three outcomes:

| Return | Meaning |
|---|---|
| `1` | Player 1 (`x`) wins |
| `2` | Player 2 (`o`) wins |
| `0` | Draw: 9 moves, no winner |
| `-1` | Game still going |

```c
int checkStatus(char b[3][3], int moves) {
    for (int i = 0; i < 3; i++) {
        // row i
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2])
            return b[i][0] == 'x' ? 1 : 2;
        // column i
        if (b[0][i] != ' ' && b[0][i] == b[1][i] && b[1][i] == b[2][i])
            return b[0][i] == 'x' ? 1 : 2;
    }
    // both diagonals pass through the center
    if (b[1][1] != ' ' &&
        ((b[0][0] == b[1][1] && b[1][1] == b[2][2]) ||
         (b[0][2] == b[1][1] && b[1][1] == b[2][0])))
        return b[1][1] == 'x' ? 1 : 2;

    return (moves == 9) ? 0 : -1;
}
```

- The `!= ' '` check matters: without it, an **empty** row of three spaces counts as "three in a row".
- Check for a winner **before** checking for a draw. A win on the 9th move is a win, not a draw.
- Every line is checked against `b[1][1]` for the diagonals, because both diagonals go through the center.

### The main loop

```c
int row, col, moves = 0, status = -1;

while (status == -1 && scanf("%d %d", &row, &col) == 2) {
    printf("%d %d\n", row, col);                       // echo the move (see the note above)
    board[row - 1][col - 1] = (moves % 2 == 0) ? 'x' : 'o';
    moves++;
    display(board);
    status = checkStatus(board, moves);
}

if (status == 0)
    printf("Freshest moment! Both players unleashing their creativity!\n");
else if (status > 0)
    printf("What a refreshing moment with Player %d unleashing their creativity!\n", status);
```

- `status == -1` stops the loop as soon as the game ends, even if more input lines follow.
- `scanf(...) == 2` stops the loop when the input runs out.
- If the input ends before the game does, neither message prints.

---

## Box-Drawing Characters

The board uses Unicode **box-drawing** characters, written as `\u` escapes in the strings:

| Escape | Char | Name | | Escape | Char | Name |
|---|---|---|---|---|---|---|
| `╔` | ╔ | top-left corner | | `╗` | ╗ | top-right corner |
| `╚` | ╚ | bottom-left corner | | `╝` | ╝ | bottom-right corner |
| `═` | ═ | horizontal | | `║` | ║ | vertical |
| `╦` | ╦ | T pointing down | | `╩` | ╩ | T pointing up |
| `╠` | ╠ | T pointing right | | `╣` | ╣ | T pointing left |
| `╬` | ╬ | cross | | | | |

The comment in the startup file (`//201 203 187 ...`) lists the same characters' codes in the old IBM PC character set (code page 437), where ╔ was 201.

**If the board shows up as garbage** (`â•”` or `?`), the terminal isn't decoding UTF-8:

- **Windows Command Prompt / PowerShell:** run `chcp 65001` before the program, or in C call `SetConsoleOutputCP(65001);` from `<windows.h>`.
- **gcc** converts `\u` escapes in strings to UTF-8 by default, so the program itself is fine.
- **VPL** and most Linux and macOS terminals use UTF-8 already.

---

## Things the Statement Leaves Open

| Situation | Suggestion |
|---|---|
| A player picks a cell that is already taken | Not covered. Either ignore the move (same player goes again) or overwrite it. Ignoring is closer to the real game |
| Row or column outside 1–3 | Not covered. Writing `board[3][0]` is out of bounds, so skipping invalid moves is safer |
| More input lines after the game ends | Stop reading; don't display more boards |
| Input ends before the game ends | Print the boards so far and no final message |
| Echoing the move before each board | Needed to reproduce the sample when input comes from a file ([note](#sample)) |

---

## Testing Checklist

| Game | Moves | Expected result |
|---|---|---|
| The sample (row win) | `1 1`, `2 1`, `1 2`, `2 2`, `1 3` | Player 1 |
| Column win for `o` | `1 1`, `1 2`, `2 1`, `2 2`, `3 3`, `3 2` | Player 2 (column 2) |
| Main diagonal | `1 1`, `1 2`, `2 2`, `1 3`, `3 3` | Player 1 |
| Anti-diagonal | `1 3`, `1 1`, `2 2`, `1 2`, `3 1` | Player 1 |
| Draw | `1 1`, `1 2`, `1 3`, `2 2`, `2 1`, `2 3`, `3 2`, `3 1`, `3 3` | Draw |
| Win on the 9th move | `1 1`, `1 2`, `1 3`, `2 1`, `2 2`, `2 3`, `3 2`, `3 1`, `3 3` | Player 1 (main diagonal), **not** a draw |
| Extra input after a win | The sample plus `3 3` | The game stops after `1 3`; no 6th board |

Final board of the draw:

```
╔═══╦═══╦═══╗
║ x ║ o ║ x ║
╠═══╬═══╬═══╣
║ x ║ o ║ o ║
╠═══╬═══╬═══╣
║ o ║ x ║ x ║
╚═══╩═══╩═══╝
Freshest moment! Both players unleashing their creativity!
```

---

## About This Solution

[tictactoe.c](tictactoe.c) produces the right boards and the right result for every game in the [testing checklist](#testing-checklist), including the win on the 9th move and the extra input after a win.

| Piece | Role |
|---|---|
| `#define SIZE 3` | Board size, used in the parameter types and loops |
| `player` | `'x'` or `'o'`, switched after each valid move. The player number comes from it: `player == 'x' ? 1 : 2` |
| `display` | Unchanged from the startup file |
| `checkWin(table)` | Returns 1 if any row, column or diagonal has three equal, non-empty cells. Each loop iteration checks column `i` and row `i` together |
| `checkDraw(table)` | Returns 1 if no cell is `' '`. It's called only after `checkWin` fails, so a full board with a winner counts as a win |
| Main loop | Echoes the move, converts to 0-based indices, places the mark, displays, then checks for a win and a draw |

Unlike the single `checkStatus` in [the approach above](#checking-for-a-winner-or-a-draw), the solution splits the check into **two functions**. The win check doesn't need to know who won: the player who just moved is the only one who could have.

**Taken cell:** if the cell is already filled, the board is shown again unchanged and the **same player** moves again. This follows the first suggestion in [Things the Statement Leaves Open](#things-the-statement-leaves-open).

**Issues found when testing:**

| Issue | What happens | Fix |
|---|---|---|
| Input ends before the game does | `scanf` fails, `r` and `c` keep their old values (a taken cell), and `do { ... } while(1)` redisplays the board **forever**. It printed over 800,000 lines in 3 seconds | `if (scanf("%i %i", &r, &c) != 2) break;` |
| Row or column outside 1–3 | `tableS[r][c]` reads and writes outside the array | Skip the move if `r` or `c` is outside 0–2 after the `--` |
| No newline after the final message | The last line ends without `\n` | Add `\n` to both final `printf`s |

The first issue only affects input where the game never finishes, which the sample doesn't include. A checker that sends such input would see the program hang until it times out.
