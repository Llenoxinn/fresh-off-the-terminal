/*
    I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.
*/


#include<stdio.h>

void lastColumn(int n, int miniNums[n][n]);
void lastRow(int n, int miniNums[n][n]);
void diagonals(int n, int miniNums[n][n]);

int main() {
    int size;
    scanf("%i", &size);
    int miniNums[size][size];

    for(int i=0; i<size; i++) {
        for(int j = 0; j<size; j++) {
            scanf("%i", &miniNums[i][j]);
        }
    }

    lastColumn(size, miniNums);
    lastRow(size, miniNums);
    diagonals(size, miniNums);

    return 0;
}

void lastColumn(int n, int miniNums[n][n]) {
    for(int i = 0, j=n-1; i<n; i++) {
        printf("%i\n", miniNums[i][j]);
    }
}

void lastRow(int n, int miniNums[n][n]) {
    for(int i = n-1, j=0; j<n; j++) {
        printf("%i ", miniNums[i][j]);
    }
    printf("\n");
}

void diagonals(int n, int miniNums[n][n]) {
    // first diagonal
    for(int i=0;i<n;i++)
        printf("%i ", miniNums[i][i]);

    // second diagonal
    printf("\n");
    for(int i=0;i<n;i++)
        printf("%i ", miniNums[i][n-i-1]);

}
