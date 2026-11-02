/*

HONOR CODEEE!!>

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/

#include <stdio.h>

int countObjects(int[100][100], int rn, int cn);
void labeling(int[100][100], int rn, int cn, int row_column, int column_row, int label);
int main() {
    int t;
    scanf("%i", &t);
    while(t--) {
        int rn, cn;
        scanf("%i %i", &rn, &cn);
        // px[rn][cn] = dili mugana idk why
        int px[100][100];
        for(int i = 0; i<rn; i++) {
            for(int j = 0; j<cn; j++) {
                scanf("%i",&px[i][j]);
            }
        }
        // for(int i = 0; i<rn; i++) {
        //      for(int j = 0; j<cn; j++) {
        //          printf("%i ", px[i][j]);
        //      }
        // }
        int objects=countObjects(px, rn, cn);
        printf("%i %s found\n", objects, objects>1 ? "objects" : "object");
    }
    return 0;
}

int countObjects(int px[100][100], int rn, int cn) {
    int labelpx=2;
    // label++ after labeling stuff
    for(int i = 0; i<rn; i++) {
        for(int j = 0; j<cn; j++) {
            if(px[i][j] == 1) {
                labeling(px, rn, cn, i,j,labelpx);
                labelpx++;
            }
        }
    }
    return labelpx-2;
    // implement recursion labeling here
}
void labeling(int px[100][100], int rn, int cn, int row, int column, int label) {
    if(row < 0 || row >= rn || column < 0 || column >= cn) return;
    if(px[row][column]!=1) {
        return;
    }
    int directionrow[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int directioncolumn[] = {-1,0,1,-1,1,-1,0,1};
    px[row][column] = label;

    // THIS IS DFS METHOD DAW
    // // 1. top left
    // labeling(px, rn, cn, row-1, column-1, label);
    // // 2. top
    // labeling(px, rn, cn, row-1, column, label);
    // // 3. top right
    // labeling(px, rn, cn, row-1, column+1, label);
    // // left
    // labeling(px, rn, cn, row, column-1, label);
    // // right
    // labeling(px, rn, cn, row, column+1, label);
    // // bottom left
    // labeling(px, rn, cn, row+1, column-1, label);
    // // bottom
    // labeling(px, rn, cn, row+1, column, label);
    // // bottom right
    // labeling(px, rn, cn, row+1, column+1, label);

    for(int zq=0; zq<8; zq++) {
        labeling(px, rn, cn, row+directionrow[zq], column+directioncolumn[zq], label);
    }
}
