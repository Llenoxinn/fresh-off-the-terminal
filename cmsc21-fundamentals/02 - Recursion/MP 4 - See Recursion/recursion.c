/*

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/

#include <stdio.h>

int recursedMultiplication(int x, int y);
int palindromicArray(int *pal, int first, int last);

int main() {
    int x, y, n;
    scanf("%i %i", &x, &y);
    if(scanf("%i", &n)!= 1 || n < 0);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    printf("%i\n", recursedMultiplication(x, y));
    if(palindromicArray(arr, 0, n - 1)) {
        printf("The array is palindromic!\n");
    } else {
        printf("The array is not palindromic!\n");
    }
    return 0;
}

int recursedMultiplication(int x, int y) {
    if(x==1) {
        printf("Base case!\n");
        return y;
    }
    if (y == 1) {
        printf("Base case!\n");
        return x;
    }
    printf("Recursive case!\n");
    int halve = recursedMultiplication(x,y/2);
    return (y % 2 == 0) ? halve + halve : halve + halve + x;
    // if (y % 2 == 0)
    //     return halve+ halve;
    // else
    //     return halve + halve + x;
}

int palindromicArray(int *pal, int first, int last) {
    if (first >= last) {
        printf("Base case!\n");
        return 1;
    }

    if (pal[first] != pal[last]) {
        return 0;
    }
    printf("Recursive Case!\n");
    return palindromicArray(pal, first + 1, last - 1);
}
