// I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    int n;
    unsigned long long factorial = 1;

    if (scanf("%d", &n) != 1 || n < 0 || n > 12) {
        printf("INVALID INPUT");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    printf("%llu", factorial);
    return 0;
}