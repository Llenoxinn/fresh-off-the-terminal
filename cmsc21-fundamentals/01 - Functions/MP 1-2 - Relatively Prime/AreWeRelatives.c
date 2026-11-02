/*
    I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.
*/

#include<stdio.h>

int amINaiveForYou(int, int);
int euclideanAlgae(int, int);

int main() {
    
    int O, P;
    
    do{
        scanf("%i", &O);
    }while(O<0);
    
    do{
        scanf("%i", &P);
    }while(P<0);
    
    int ive=amINaiveForYou(O,P);
    if(ive > 0) printf("Yes %i\n", ive);
    else printf("No %i\n", -ive);
    
    int clid = euclideanAlgae(O,P);
    if(clid>0) printf("Yes %i\n", clid);
    else printf("No %i\n", -clid);
    
    return 0;
}

int amINaiveForYou(int p, int q) {
    int bareminimum = (p < q) ? p : q;
    int count = 0;
    int naivebaby = 1;
    
    for (int candifact = bareminimum; candifact >= 2; candifact--) {
        count++;
        if (p % candifact == 0 && q % candifact == 0) {
            naivebaby = 0;
            break;
        }
    }

    return (naivebaby == 1) ? count : -count;
}

int euclideanAlgae(int r, int s) {
    
    long long a = (r > s) ? r : s;
    long long b = (r < s) ? r : s;
    long long rem;
    int count=0;
        
    if (b == 0) return 0;
        
        while (1) {
            count++;
            rem = a % b;
            if (rem == 0) break;
            a = b;
            b = rem;
        }
        
        return (b == 1) ? count : -count;
        
    }