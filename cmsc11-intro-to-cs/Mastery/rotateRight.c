// Rotate a number to the right once: the last digit moves to the front.
// Sample: 34567 -> 73456, 231456 -> 623145

#include <stdio.h>

int main() {
    long long n;

    if (scanf("%lld", &n) != 1 || n < 0) {
        printf("INVALID INPUT");
        return 0;
    }

    // place = 10^(digits - 1), the place value of the first digit
    long long place = 1;
    for (long long temp = n; temp >= 10; temp /= 10)
        place *= 10;

    long long last = n % 10;
    long long rest = n / 10;
    long long rotated = last * place + rest;

    printf("%lld", rotated);
    return 0;
}
