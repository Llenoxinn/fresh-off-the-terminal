// I declare, upon my honor, that I did this machine problem assignment by myself using references from the lecture notes and MPs.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void) {
    int count = 0, n = 5;
    int magic;
    int guess = 0;
    // int limit = 100;
    
    // srand((unsigned int)time(NULL));
    // magic = 1 + rand() % limit;
    scanf("%d", &magic);
    
    // for(; count < n; count++) {
    //     scanf("%d", &guess);
        
    //     if(guess == magic) {
    //         printf("CONGRATULATIONS! YOU GUESSED IT!\n");
    //         return 0;
    //     }   
    //     else if (guess > magic) {
    //         printf("LOWER\n");
    //     }
    //     else if (guess < magic) {
    //         printf("HIGHER\n");
    //     }
    //     else {
    //         printf("INVALID INPUT!\n");
    //     }
    // }
    
    // looping if input is valid!
    while (scanf("%d", &guess) == 1) {
        if (guess == magic) {
            printf("CONGRATULATIONS. YOU GUESSED IT!\n");
            return 0;
        }
        // 0 < 4
        if (count < n - 1)
            printf("%s\n", guess > magic ? "LOWER" : "HIGHER");
        count++;
        // count = 1, 2, 3, 4
        if (count == n) break;
    }
    
    printf("SORRY. THE MAGIC NUMBER IS %d.\n", magic);
    return 0;
}