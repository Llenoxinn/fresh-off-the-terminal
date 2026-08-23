// HONOR CODE: I declare, upon my honor, that I did this machine problem by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    // Determine descending order without swapping
    if (a >= b && a >= c) {
        if (b >= c)
               printf("%d %d %d", a, b, c);
        else
            printf("%d %d %d", a, c, b);
    }
    else if (b >= a && b >= c) {
        if (a >= c)
            printf("%d %d %d", b, a, c);
        else
            printf("%d %d %d", b, c, a);
    }
    else {
        if (a >= b)
            printf("%d %d %d", c, a, b);
        else
            printf("%d %d %d", c, b, a);
    }

    return 0;
}