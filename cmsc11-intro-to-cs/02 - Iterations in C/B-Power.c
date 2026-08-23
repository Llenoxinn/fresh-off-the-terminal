// I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    int x, y, answer = 1, iteration = 0;
    
    if(scanf("%d %d", &x, &y) != 2 || (x == 0 && y == 0)) {
        printf("INDETERMINATE");
        return 0;
    }
    if (x == 0 && y < 0) {
        printf("UNDEFINED");
        return 0;
    }

    if (y > 0) {
        while (iteration < y) {
            answer = answer * x;
            iteration++;
        }
        printf("%d", answer);
    } else if (y < 0) {
        y = -y; // make y positive for looping
        while (iteration < y) {
            answer = answer * x;
            iteration++;
        }
        printf("1/%d", answer);
    } else { // y == 0
        printf("1");
    }
    return 0;
}