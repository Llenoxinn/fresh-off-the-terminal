// HONOR CODE!
// I declare, upon my honor, that I did this machine problem by myself using references from the lecture notes and MPs.

#include <stdio.h>
#include <string.h>

// int prefix(char str1[],char str2[]) {
//     // should be equal OR like almost the same 
//     // if it is a prefix, return -1
//     // if it is not, return the index where it was stuck
//     int len1 = strlen(str1);
//     int len2 = strlen(str2);
    
//     for(int i = 0; i < len2; i++) {
//         if(i >= len1) {
//             return i;
//         }
        
//         if(str2[i] != str1[i]) {
//             return i;
//         }
//     }
//     return -1;
// }

int main(){
    char st1[500],st2[500];
    scanf("%s%s",st1,st2);
    // int x = prefix(st1,st2);
    int len1 = strlen(st1);
    int len2 = strlen(st2);
    int x = -1;
    
    for(int i = 0; i < len2; i++) {
        if(i >= len1) {
            x = i;
            break;
        }
        
        if(st2[i] != st1[i]) {
            x = i;
            break;
        }
    }
    x == - 1 ? printf("%s is a prefix of %s.\n",st2,st1) : printf("%s is not a prefix of %s because of index %i.\n",st2,st1,x);
    return 0;
}