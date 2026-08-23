// I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    int num, sum = 0;

    if (scanf("%d", &num) != 1 || num <= 0) {
        printf("INVALID INPUT");
        return 0;
    }

    // Compute sum of factors (excluding the number itself)
    for (int i = 1; i < num; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    // Check if perfect num sya
    if (sum == num)
        printf("YES");
    else
        printf("NO");

    return 0;
}
