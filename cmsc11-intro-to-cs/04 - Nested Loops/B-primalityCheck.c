// HONOR CODE!
// I declare, upon my honor, that I did this machine problem assignment by myself 
// using online resources from the following:
// https://stackoverflow.com/questions/32649594/c-program-to-find-prime-number
// https://www.w3schools.com/c/ref_math_sqrt.php
// https://www.w3schools.com/c/c_ref_math.php
// Book: BEGINNING C FROM BEGINNER TO PRO 7TH EDITION BY GERMAN GONZALEZ- MORRIS AND IVOR HORTON
// Further, my solution is not a copy from the aforementioned sources.


#include <stdio.h>
#include <math.h> 

int main() {
    long long n, temp, remainder;
    long long cf;
    int count;
    int cfCount = 0;
    int isPrime = 1;

    if (scanf("%lld", &n) != 1 || n <= 0) {
        printf("INVALID INPUT");
        return 0;
    }
    if(n == 1 || n == 2) {
        printf("Iterations inside the loop per candidate factor: 0\n");
        printf("Iterations of the outer loop: 0\n");
        if(n == 1) {
            isPrime = 0;
        } else 
            isPrime = 1;
        printf("%s, %lld %s prime.\n", isPrime == 0 ? "NO" : "YES", n, isPrime == 0 ? "is not" : "is");
        return 0;
    }
    // if (n == 1) {
    //     printf("Iterations inside the loop per candidate factor: 0\n");
    //     printf("Iterations of the outer loop: 0\n");
    //     printf("NO, 1 is not prime.\n");
    //     return 0;
    // }

    // if (n == 2) {
    //     printf("Iterations inside the loop per candidate factor: 0\n");
    //     printf("Iterations of the outer loop: 0\n");
    //     printf("YES, 2 is prime.\n");
    //     return 0;
    // }

    printf("Iterations inside the loop per candidate factor:\n");

cf = 3;
while (1) {
    long long square = 0;
    long long add = 0;
    while (add < cf) {
        square += cf;
        add++;
    }

    if (square >= n) break;

    temp = n;
    remainder = temp;
    count = 0;

    while (remainder >= cf) {
        remainder -= cf;
        count++;
    }

    printf("%d\n", count);
    cfCount++;

    if (remainder == 0) {
        isPrime = 0;
        break;
    }

    cf += 2;
}


// FOR TEST 8 HUHU IDK NA
// VS CODE MY SAVIOR SINCE LAGGY ANG UVEC VPL
if (isPrime) {
    long long last_cf_squared = 0;
    long long last_add = 0;
    while (last_add < cf) {
        last_cf_squared += cf;
        last_add++;
    }

    if (last_cf_squared == n) {
        long long factor = cf;
        
        long long final_count = 0;
        long long final_remainder = n;
        while (final_remainder >= factor) {
            final_remainder -= factor;
            final_count++;
        }
        
        printf("%lld\n", final_count);
        
        isPrime = 0;
    }
}

    printf("Iterations of the outer loop: %d\n", cfCount);
    
    // whatifff tinamaran style
    printf("%s, %lld %s prime.\n", isPrime ? "YES" : "NO", n, isPrime ? "is" : "is not");
    // if (isPrime)
    //     printf("YES, %lld is prime.\n", n);
    // else
    //     printf("NO, %lld is not prime.\n", n);

    return 0;
}