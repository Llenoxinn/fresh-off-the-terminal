/*
    I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.
*/

#include <stdio.h>

int isMyPrime1(long long n);
int isMyPrime2(long long n);
int isMyPrime3(long long n);

int main() {
    long long N;
    if (scanf("%lld", &N) != 1) return 0;
    
    if (N > 2 && N % 2 == 0) {
    printf("Nophie 0 0 0\n");
    return 0;
}

    int v1 = isMyPrime1(N);
    int v2 = isMyPrime2(N);
    int v3 = isMyPrime3(N);

    if (v1 >= 0) {
        long long soft = 2 * N + 1;
        int s1 = isMyPrime1(soft);
        int s2 = isMyPrime2(soft);
        int s3 = isMyPrime3(soft);

        int tot1 = v1 + (s1 < 0 ? -s1 : s1);
        int tot2 = v2 + (s2 < 0 ? -s2 : s2);
        int tot3 = v3 + (s3 < 0 ? -s3 : s3);

        if (s1 >= 0)
            printf("Sophie %d %d %d\n", tot1, tot2, tot3);
        else
            printf("Nophie %d %d %d\n", tot1, tot2, tot3);
    } else {
        printf("Nophie %d %d %d\n", -v1, -v2, -v3);
    }

    return 0;
}

int isMyPrime1(long long n) {
    int count = 0;
    if (n <= 1) return -0; // Not prime
    if (n == 2) return 0;  // Prime
    if (n % 2 == 0) return -0; // Even numbers > 2 are not prime

    for (long long cf = 3; cf < n; cf += 2) {
        count++;
        if (n % cf == 0) return -count;
    }
    return count;
}

int isMyPrime2(long long n) {
    int count = 0;
    if (n <= 1) return -0;
    if (n == 2) return 0;
    if (n % 2 == 0) return -0;

    for (long long cf = 3; cf < n/2; cf += 2) {
        count++;
        if (n % cf == 0) return -count;
    }
    return count;
}

int isMyPrime3(long long n) {
    int count = 0;
    if (n <= 1) return -0;
    if (n == 2) return 0;
    if (n % 2 == 0) return -0;

    for (long long cf = 3; cf * cf <= n; cf += 2) {
        count++;
        if (n % cf == 0) return -count;
    }
    return count;
}