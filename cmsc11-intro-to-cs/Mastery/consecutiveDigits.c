// Check whether every pair of consecutive digits differs by exactly 1.
// Sample: 34567 -> YES, 123456543 -> YES, 231456 -> NO
// 1-digit numbers have no pairs, so the property cannot be detected.

#include <stdio.h>
#include <stdlib.h>

int main() {
    long long n;

    if (scanf("%lld", &n) != 1 || n < 0) {
        printf("INVALID INPUT");
        return 0;
    }

    if (n < 10) {
        printf("NOT APPLICABLE");
        return 0;
    }

    int ok = 1;
    // compare the last two digits, then drop the last one
    for (long long temp = n; temp >= 10; temp /= 10) {
        int a = temp % 10;
        int b = (temp / 10) % 10;
        if (abs(a - b) != 1) {
            ok = 0;
            break;
        }
    }

    printf("%s", ok ? "YES" : "NO");
    return 0;
}
