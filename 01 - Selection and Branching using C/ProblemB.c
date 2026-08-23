// HONOR CODE: I declare, upon my honor, that I did this machine problem 
// by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    float measurement;
    if (scanf("%f", &measurement) != 1) { 
        return 0;
    }
    if (measurement < 2.5) {
        printf("Rain is considered light\n");
    } else if (measurement >= 2.5 && measurement <= 7.5) {
        printf("Rain is considered moderate\n");
    } else if (measurement > 7.5 && measurement <= 15.0) {
        printf("Yellow warning\n");
    } else if (measurement > 15.0 && measurement <= 30.0) {
        printf("Orange warning\n");
    } else {
        printf("Red warning\n");
    }

    return 0;
}