// I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    unsigned int n;
    unsigned long long first = 1, second = 1, next;

    // Input validation
    if (scanf("%u", &n) != 1 || n == 0 || n > 47) {
        printf("INVALID INPUT");
        return 0;
    }

    // the first 1s
    if (n == 1 || n == 2) {
        printf("1");
        return 0;
    }

    // Compute nth Fibo
    for (unsigned int i = 3; i <= n; i++) {
        next = first + second;
        first = second;
        second = next;
    }
    
    //printingg
    printf("%llu", second);
    return 0;
}