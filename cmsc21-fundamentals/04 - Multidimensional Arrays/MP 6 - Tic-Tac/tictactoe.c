/*

I declare, upon my honor, that I did this machine problem assignment by myself
using online resources, except LLMs, from the following:
    https://www.w3schools.com/c/c_conditions_short_hand.php
    https://www.freecodecamp.org/news/c-ternary-operator/
    https://www.w3schools.com/c/c_arrays_multi.php
    https://stackoverflow.com/questions/27816722/some-box-drawing-character-in-mobile-browser-doesnt-work
Further, my solution is not a copy from the aforementioned sources.


*/

#include <stdio.h>
#define SIZE 3
void display(char table[SIZE][SIZE]);
int checkWin(char table[SIZE][SIZE]);
int checkDraw(char table[SIZE][SIZE]);
int main(){
    char tableS[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    int r, c;
    char player = 'x';
    do {

        scanf("%i %i", &r,&c);
        printf("%i %i\n", r,c);
        r--;
        c--;

        if(tableS[r][c] != ' ') {
            display(tableS);
            continue;
        }
        tableS[r][c] = player;
        display(tableS);
        if(checkWin(tableS)) {
            int playernum = (player=='x') ? 1 : 2;
            printf("What a refreshing moment with Player %d unleashing their creativity!", playernum);
            break;
        }

        if(checkDraw(tableS)){
            printf("Freshest moment! Both players unleashing their creativity!");
            break;
        }

        if(player == 'x') {
            player='o';
        }
        else
            player='x';
    }while(1);

    return 0;
}

void display(char table[SIZE][SIZE]){
    //201 203 187 188 185 204 205 206 186
    printf("╔═══╦═══╦═══╗\n");
    printf("║ %c ║ %c ║ %c ║\n",table[0][0],table[0][1],table[0][2]);
    printf("╠═══╬═══╬═══╣\n");
    printf("║ %c ║ %c ║ %c ║\n",table[1][0],table[1][1],table[1][2]);
    printf("╠═══╬═══╬═══╣\n");
    printf("║ %c ║ %c ║ %c ║\n",table[2][0],table[2][1],table[2][2]);
    printf("╚═══╩═══╩═══╝\n");
}

int checkWin(char table[SIZE][SIZE]) {
    // check horizontal win
    for(int i = 0; i<SIZE; i++)
        if((table[0][i] == table[1][i] && table[1][i] == table[2][i] && table[0][i] != ' ') ||
            (table[i][0] == table[i][1] && table[i][1] == table[i][2] && table[i][0] != ' ')) {
                return 1;
            }

    // check diagonal win
    if((table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[0][0] != ' ') ||
        (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[0][2] != ' ')) {
            return 1;
        }
    // else not yet
    return 0;
}
int checkDraw(char table[SIZE][SIZE]) {
    for(int i = 0; i<SIZE;i++)
        for(int j=0; j<SIZE;j++)
            if(table[i][j] == ' ') {
                return 0;
            }
    // draw
    return 1;
}
