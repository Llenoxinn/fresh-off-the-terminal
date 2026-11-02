// HONOR CODE:
// I declare, upon my honor, that I did this machine problem assignment 
// by myself using online resources from the following:
// https://www.ccbp.in/blog/articles/binary-search-in-c
// https://www.geeksforgeeks.org/c/c-c-program-for-linear-search/
// https://www.simplilearn.com/tutorials/c-tutorial/program-for-linear-search-in-c
// Further, my solution is not a copy from the aforementioned sources.


#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    
    for(unsigned int k = 0; k < t; k++) {
        int naur[20];
        int item;
        scanf("%d", &item);

        for(int i = 0; i < item; i++) {
            scanf("%d", &naur[i]);
        }
        
        // Linear search
        int foundyah = 0, count = 0;
        for(int i = 0; i < item; i++) {
            count++;
            if(naur[i] == i) {
                printf("YES %d\n", count);
                foundyah = 1;
                break;
            }
            if(naur[i] > i) break;
        }
        if(!foundyah)
            printf("NO %d\n", count);
        
        // Binary search
        int left = 0, right = item - 1;
        int uribina = 0, countered = 0;
        while(left <= right) {
            int middle = left + (right - left) / 2;
            countered++;
            if(naur[middle] == middle) {
                uribina = 1;
                break;
            } else if(naur[middle] < middle) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        if(uribina)
            printf("YES %d\n", countered);
        else
            printf("NO %d\n", countered);
    }
    return 0;
}