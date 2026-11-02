// I declare, upon my honor, that I did this machine problem by myself using references from the lecture notes and MPs.

#include <stdio.h>

int main() {
    char str[100];
    int i;
    
    scanf("%s", str);
    // hexa is 0-F
    for(i = 0; str[i] != '\0' ; i++) {
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))) {
            // THATS INVALIDDD!
            printf("%d\n", i);
            return 0;
        }
    }
    printf("%d\n", i);
    return 0;
}